
#ifndef		CPP_GOMOKU_CORE_HPP
# define	CPP_GOMOKU_CORE_HPP

# include	"Model.hpp"
# include	"View.hpp"
# include	"Player.hpp"

class Core
{
  View		*m_view;
  Model		*m_model;
  MAPTYPE	**m_map;
  unsigned int	m_round;

  Player	*m_currentPlayer;
  Player	*m_winner;
  Player	*m_player1;
  Player	*m_player2;
  Player	*m_nullPlayer;

  config	m_config;

  void		resetGame();
  void		resetMap();

  void		updateCoup(const ResultCoup &, const Pos &);
  bool		checkIfWinner(const bool);
  bool		checkIfMatchNull() const;

  void		updateBoard(const ResultCoup &, const Pos &);
  void		verifyPutStone(const Pos &, Pos &);

  void		execEvent(const myEvent &, bool &, Pos &);
  void		execAiRound(Pos &);

public:
  Core();
  ~Core();

  void		loopGame();
};

#endif
