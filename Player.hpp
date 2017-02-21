#ifndef		CPP_GOMOKU_PLAYER_HPP
# define	CPP_GOMOKU_PLAYER_HPP

# include	<string>
# include	<thread>
# include	<mutex>
# include	<condition_variable>
# include	<list>

# include	"pos.hpp"
# include	"myEvent.hpp"
# include	"Model.hpp"

# define	TIME_LIMIT	5

# define	NB_PARTY       2000
# define	NB_THREAD	5
# define	LOSE_VALUE 1000
# define	NB_COUP   30000

class		Player
{
  std::string		m_name;
  Model			*m_model;
  const MAPTYPE		**m_map;
  unsigned int		m_wins;
  bool			m_isAI;
  MAPTYPE 		m_color;
  unsigned int		m_stonesTaken;

  MAPTYPE		**m_mapTmp;

  bool			checkIfWin(const Pos &);
  unsigned long		gameThread(const Pos &, int);
  int			play_game(const Pos &);
  bool			checkEmptyBoard(const MAPTYPE **);
  bool			checkPlayValidity(const MAPTYPE **, const Pos &, const int interval);

  bool			check4libre(const Pos &, Pos &, ResultCoup &);
  bool			check3libre(const Pos &, Pos &, ResultCoup &);
  bool			putStoneHere(const int, const int, Pos &, ResultCoup &);

public:
  Player(const std::string &, const MAPTYPE, Model *,
	 const MAPTYPE **, const bool ia = false);
  ~Player();

  void		addWin();
  void		resetWin();
  void		changeColor();
  void		setColor(const MAPTYPE);
  void		changeAI();
  void		resetStonesTaken();
  void		addStonesTaken();

  void		disableAI();
  void		setName(const std::string &);

  const std::string	&getName() const;
  int			getWins() const;
  bool			getAI() const;
  MAPTYPE		getColor() const;
  int			getStonesTaken() const;

  Pos		execAiRound(ResultCoup &res, const Pos &last, const int);
};

#endif
