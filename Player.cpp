
#include	<vector>
#include	<future>
#include	<iostream>

#include	<time.h>

#include	"Player.hpp"

Player::Player(const std::string &name, const MAPTYPE color, Model *model,
	       const MAPTYPE **map, const bool isAI) :
  m_name(name), m_model(model), m_map(map)
{
  m_wins = 0;
  m_color = color;
  m_stonesTaken = 0;
  m_isAI = isAI;
  m_mapTmp = new MAPTYPE*[27];
  for (int y = 0; y < 27; y++)
    m_mapTmp[y] = new MAPTYPE[27];
}

Player::~Player()
{
  for (int y = 0; y < 27; y++)
    delete[] m_mapTmp[y];
  delete[] m_mapTmp;
}

void	Player::addWin()
{
  m_wins++;
}

void	Player::disableAI()
{
  m_isAI = false;
}

void	Player::resetWin()
{
  m_wins = 0;
}

void	Player::resetStonesTaken()
{
  m_stonesTaken = 0;
}

void	Player::addStonesTaken()
{
  m_stonesTaken += 1;
}

void	Player::changeColor()
{
  if (m_color == WHITE)
    m_color = BLACK;
  else
    m_color = WHITE;
}

void	Player::setColor(const MAPTYPE color)
{
  m_color = color;
}

void	Player::changeAI()
{
  m_isAI = !m_isAI;
}

const std::string	&Player::getName() const
{
  return m_name;
}

int		Player::getWins() const
{
  return m_wins;
}

bool		Player::getAI() const
{
  return m_isAI;
}

MAPTYPE		Player::getColor() const
{
  return m_color;
}

int		Player::getStonesTaken() const
{
  return m_stonesTaken;
}

void		Player::setName(const std::string &name)
{
  m_name = name;
}

unsigned long	Player::gameThread(const Pos &pos, int priseAdv)
{
  config conf;
  conf.double3 = false;
  conf.broken5 = false;

  ResultCoup	res;
  res.winner = false;

  for (int y = 0; y < 27; y++)
    for (int x = 0; x < 27; x++)
      m_mapTmp[y][x] = m_map[y][x];
      
  Pos	tmp = pos;
  MAPTYPE	pl = m_color;
  Model	modelTmp((const MAPTYPE **)m_mapTmp, &conf);
  int	myPrise = m_stonesTaken;

  while (!res.winner)
    {
      if (checkPlayValidity((const MAPTYPE **)m_mapTmp, tmp, 2) == true)
	{
	  res = modelTmp.verifCoordonnee(pl, tmp);
	  if (res.is_good)
	    {
	      m_mapTmp[tmp.y][tmp.x] = pl;
	      if (pl == m_color)
		{
		  myPrise += res.taken.size();
		  if (myPrise >= 10)
		    res.winner = true;
		}
	      else
		{
		  priseAdv += res.taken.size();
		  if (priseAdv >= 10)
		    res.winner = true;
		}
	      if (!res.winner)
		pl = (pl == WHITE ? BLACK : WHITE);
	    }
	}
      tmp.x = rand() % 19 + MAP_MIN;
      tmp.y = rand() % 19 + MAP_MIN;
    }
  if (pl == m_color)
    return 1;
  return 0;
}

bool		Player::checkEmptyBoard(const MAPTYPE **map)
{
  for (int y = MAP_MIN; y < MAP_MAX; y++)
    for (int x = MAP_MIN; x < MAP_MAX; x++)
      if (map[y][x] != EMPTY)
	return (false);
  return (true);
}

bool		Player::checkPlayValidity(const MAPTYPE **map,
					  const Pos & coup, const int interval)
{
  for (int y = coup.y - interval; y < coup.y + interval; y++)
    for (int x = coup.x - interval; x < coup.x + interval; x++)
      if (map[y][x] == BLACK || map[y][x] == WHITE)
	      return (true);
  if (checkEmptyBoard(map) == true)
    return (true);
  return (false);
}

bool		Player::checkIfWin(const Pos &pos)
{
  Model modelTmp(*m_model, m_map);

  ResultCoup res = modelTmp.verifCoordonnee(m_color, pos);
  if (res.winner || m_stonesTaken + res.taken.size() >= 10)
    return (true);
  return (false);
}

bool		Player::putStoneHere(const int x, const int y, Pos &ret, ResultCoup &res)
{
  ret = Pos(x, y);
  res = m_model->verifCoordonnee(m_color, ret);
  return (res.is_good);
}

bool		Player::check4libre(const Pos &last, Pos &ret, ResultCoup &res)
{
  int		resUp = m_model->countUp(last.x, last.y, FOE(m_color));
  int		resDown = m_model->countDown(last.x, last.y, FOE(m_color));
  if (resUp + resDown + 1 >= 4)
    {
      if (putStoneHere(last.x, last.y + resDown, ret, res))
	return (true);
      if (putStoneHere(last.x, last.y - resUp, ret, res))
	return (true);
    }

  int		resLeft = m_model->countLeft(last.x, last.y, FOE(m_color));
  int		resRight = m_model->countRight(last.x, last.y, FOE(m_color));
  if (resLeft + resRight + 1 >= 4)
    {
      if (putStoneHere(last.x + resRight, last.y, ret, res))
	return (true);
      if (putStoneHere(last.x - resLeft, last.y, ret, res))
	return (true);
    }

  int		resUpRight = m_model->countUpRight(last.x, last.y, FOE(m_color));
  int		resDownLeft = m_model->countDownLeft(last.x, last.y, FOE(m_color));
  if (resUpRight + resDownLeft + 1 >= 4)
    {
      if (putStoneHere(last.x + resUpRight, last.y - resUpRight, ret, res))
	return (true);
      if (putStoneHere(last.x - resDownLeft, last.y + resDownLeft, ret, res))
	return (true);
    }

  int		resUpLeft = m_model->countUpLeft(last.x, last.y, FOE(m_color));
  int		resDownRight = m_model->countDownRight(last.x, last.y, FOE(m_color));
  if (resUpLeft + resDownRight + 1 >= 4)
    {
      if (putStoneHere(last.x - resUpLeft, last.y - resUpLeft, ret, res))
	return (true);
      if (putStoneHere(last.x + resDownRight, last.y + resDownRight, ret, res))
	return (true);
    }
  return (false);
}

bool		Player::check3libre(const Pos &last, Pos &ret, ResultCoup &res)
{
  if (m_model->check3libreHorizontal(last.x, last.y, FOE(m_color)) > 0)
    {
      if (putStoneHere(last.x - 1, last.y, ret, res))
	return (true);
      if (putStoneHere(last.x + 1, last.y, ret, res))
	return (true);
      if (putStoneHere(last.x + 2, last.y, ret, res))
	return (true);
    }

  if (m_model->check3libreVertical(last.x, last.y, FOE(m_color)) > 0)
    {
      if (putStoneHere(last.x, last.y - 1, ret, res))
	return (true);
      if (putStoneHere(last.x, last.y + 1, ret, res))
	return (true);
      if (putStoneHere(last.x, last.y + 2, ret, res))
	return (true);
    }

  if (m_model->check3libreDiagonalDownRight(last.x, last.y, FOE(m_color)) > 0)
    {
      if (putStoneHere(last.x - 1, last.y - 1, ret, res))
	return (true);
      if (putStoneHere(last.x + 1, last.y + 1, ret, res))
	return (true);
      if (putStoneHere(last.x + 2, last.y + 2, ret, res))
	return (true);
    }

  if (m_model->check3libreDiagonalUpRight(last.x, last.y, FOE(m_color)) > 0)
    {
      if (putStoneHere(last.x + 1, last.y - 1, ret, res))
	return (true);
      if (putStoneHere(last.x - 1, last.y + 1, ret, res))
	return (true);
      if (putStoneHere(last.x + 2, last.y - 2, ret, res))
	return (true);
    }
 
  return (false);
}

Pos		Player::execAiRound(ResultCoup &resCoup, const Pos &last, const int priseAdv)
{
  Pos			ret, tmp;
  
  if (last.x == -1)
    {
      ret = Pos(MAP_MIN + 9, MAP_MIN + 9);
      resCoup = m_model->verifCoordonnee(m_color, ret);
      return ret;
    }

  unsigned long		game_percent;
  std::vector<std::pair<Pos, unsigned long> > tab;

  time_t	begin;

  time(&begin);
  while (begin + TIME_LIMIT >= time(NULL))
    {
      bool	result = false;
      while (!result)
	{
	  tmp.x = rand() % 19 + MAP_MIN;
	  tmp.y = rand() % 19 + MAP_MIN;
	  if (checkPlayValidity((const MAPTYPE **)m_map, tmp, 1) == true)
	    result = m_model->checkCoordonnee(m_color, tmp);
	}
      if (checkIfWin(tmp))
	{
	  resCoup = m_model->verifCoordonnee(m_color, tmp);
	  return ret;
	}
      game_percent = gameThread(tmp, priseAdv);
      auto it = tab.begin();
      for (; it != tab.end(); ++it)
	{
	  if (it->first == tmp)
	    {
	      it->second += game_percent;
	      break;
	    }
	}
      if (it == tab.end())
	tab.push_back(std::pair<Pos, unsigned long>(tmp, game_percent));
    }
  if (last.x != -1 && (check4libre(last, ret, resCoup) || check3libre(last, ret, resCoup)))
    return ret;
  unsigned long 	percent = 0;
  for (auto it = tab.begin(); it != tab.end(); ++it)
    {
      if (percent <= it->second)
	{
	  ret = it->first;
	  percent = it->second;
	}
    }
  resCoup = m_model->verifCoordonnee(m_color, ret);
  return ret;
}
