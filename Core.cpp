#include <ctime>
#include <unistd.h>
#include <iostream>
#include <stdexcept>

#include "Core.hpp"

Core::Core()
{
  m_map = new MAPTYPE*[27];
  if (m_map == NULL)
    throw std::runtime_error("Can't init tab");
  for (int y = 0; y < 27; y++)
    {
      m_map[y] = new MAPTYPE[27];
      if (m_map[y] == NULL)
	throw std::runtime_error("Can't malloc line");
      for (int x = 0; x < 27; x++)
	m_map[y][x] = LIMIT;
    }
  m_model = new Model((const MAPTYPE **)m_map, &m_config);
  m_player1 = new Player("Player 1", BLACK, m_model, (const MAPTYPE **)m_map);
  m_player2 = new Player("Player 2", WHITE, m_model, (const MAPTYPE **)m_map);
  m_nullPlayer = new Player("Match null", EMPTY, NULL, NULL);
    try {
        m_view = new View((const MAPTYPE **) m_map, m_player1, m_player2);
    }
    catch (std::exception e)
    {
        std::cout << e.what() << std::endl;
        throw std::runtime_error("core :  can't generate display");
    }
  resetGame();
  m_config.double3 = true;
  m_config.broken5 = true;
}

Core::~Core()
{
  for (int i = 0; i < 27; i++)
    delete[] m_map[i];
  delete[] m_map;
  delete m_view;
  delete m_player1;
  delete m_player2;
  delete m_nullPlayer;
  delete m_model;
}

void		Core::resetGame()
{
  m_currentPlayer = m_player1;
  m_player1->resetWin();
  m_player2->resetWin();
  m_player1->setColor(BLACK);
  m_player2->setColor(WHITE);
  m_round = 1;
  resetMap();
}

void		Core::resetMap()
{
  m_winner = NULL;
  m_player1->resetStonesTaken();
  m_player2->resetStonesTaken();
  for (int y = MAP_MIN; y < MAP_MAX; y++)
    for (int x = MAP_MIN; x < MAP_MAX; x++)
      m_map[y][x] = EMPTY;
}

void		Core::updateCoup(const ResultCoup &coup, const Pos &pos)
{
  m_map[pos.y][pos.x] = m_currentPlayer->getColor();
  if (coup.capture)
    m_view->playSound(SUGOI);
  for (auto it = coup.taken.begin(); it != coup.taken.end(); ++it)
    {
      m_currentPlayer->addStonesTaken();
      m_map[it->second][it->first] = EMPTY;
    }
}

bool		Core::checkIfWinner(const bool winner)
{
  const char tmp_player = m_model->check_five();
  if (m_currentPlayer->getStonesTaken() >= 10 || winner == true || (m_config.broken5 && tmp_player != EMPTY))
    {
      m_currentPlayer->addWin();
      if (tmp_player != EMPTY)
	if (m_player1->getColor() == tmp_player)
	  m_winner = m_player1;
	else
	  m_winner = m_player2;
      else
	m_winner = m_currentPlayer;
    }
  else if (checkIfMatchNull())
    {
      m_winner = m_nullPlayer;
    }
  else
    return (false);
  m_round ++;
  m_model->fives.clear();
  return (true);
}

bool		Core::checkIfMatchNull() const
{
  for (int y = MAP_MIN; y < MAP_MAX; y++)
    for (int x = MAP_MIN; x < MAP_MAX; x++)
      if (m_map[y][x] == EMPTY)
	return (false);
  return (true);
}

void		Core::updateBoard(const ResultCoup &coup, const Pos &position)
{
  updateCoup(coup, position);
  if (checkIfWinner(coup.winner))
    m_view->playSound(WINNER, true);
  else if (m_currentPlayer == m_player1)
    m_currentPlayer = m_player2;
  else
    m_currentPlayer = m_player1;
}

void		Core::verifyPutStone(const Pos &position, Pos &lastPos)
{
  ResultCoup coup = m_model->verifCoordonnee(m_currentPlayer->getColor(), position);
  if (coup.is_good == true)
    {
      updateBoard(coup, position);
      lastPos = position;
    }
  else
    m_view->playSound(ERROR_COUP, true);
}

void		Core::execEvent(const myEvent &event, bool &loopPlay, Pos &lastPos)
{
  if (event.type == EXIT_EVT)
    loopPlay = false;
  else if (event.type == PUT_STONE)
    verifyPutStone(event.pos, lastPos);
  else if (event.type == RESET_WINNER)
    {
      lastPos = Pos(-1, -1);
      resetMap();
      m_player1->changeColor();
      m_player2->changeColor();
      m_currentPlayer = m_player1;
      if (m_player1->getColor() == WHITE)
	m_currentPlayer = m_player2;
    }
  else
    {
      resetGame();
      lastPos = Pos(-1, -1);
    }
}

void		Core::execAiRound(Pos &lastPos)
{
  m_view->updateGame(m_round, m_currentPlayer);
  m_view->show();
  
  ResultCoup	res;
  int priseAdv = (m_currentPlayer == m_player1 ? m_player2->getStonesTaken() :
		  m_player1->getStonesTaken());
  Pos tmp = m_currentPlayer->execAiRound(res, lastPos, priseAdv);

  lastPos = tmp;
  updateBoard(res, tmp);
  m_view->updateGame(m_round, m_currentPlayer);
  m_view->show();
}

void		Core::loopGame()
{
  Pos		lastPos(-1, -1);
  bool		loopPlay = true;

  srand(time(NULL));
  if (m_view->showSplash(m_config) == 1)
    return;
  while (loopPlay)
    {
      try
	{
	  if (m_winner == NULL && m_currentPlayer->getAI() == true)
	    execAiRound(lastPos);
	  else
	    m_view->loopView(m_round, m_currentPlayer, m_winner, m_config);
	}
      catch (const myEvent &event)
	{
	  execEvent(event, loopPlay, lastPos);
	}
    }
}
