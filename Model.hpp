#ifndef		CPP_GOMOKU_MODEL_HPP
# define	CPP_GOMOKU_MODEL_HPP

# include	"pos.hpp"
# include	"myEvent.hpp"
# include	"ResultCoup.hpp"
# include	"Five.hpp"

class		Model
{
public:
  int		check3libreHorizontal(int x, int y, const char Player);
  int		check3libreDiagonalDownRight(int x, int y, const char Player);
  int		check3libreDiagonalUpRight(int x, int y, const char Player);
  int		check3libreVertical(int x, int y, const char Player);

  int		countUp(int x, int y, const char Player);
  int		countDown(int x, int y, const char Player);
  int		countRight(int x, int y, const char Player);
  int		countLeft(int x, int y, const char Player);
  int		countUpRight(int x, int y, const char Player);
  int		countUpLeft(int x, int y, const char Player);
  int		countDownRight(int x, int y, const char Player);
  int		countDownLeft(int x, int y, const char Player);

private:
  std::pair<std::pair<int, int>, std::pair<int,int> > five;
  const MAPTYPE	**m_map;
  void		takeUp(int x, int y, const char Player, ResultCoup &toto);
  void		takeDown(int x, int y, const char Player, ResultCoup &toto);
  void		takeLeft(int x, int y, const char Player, ResultCoup &toto);
  void		takeRight(int x, int y, const char Player, ResultCoup &toto);
  void		takeUpRight(int x, int y, const char Player, ResultCoup &toto);
  void		takeUpLeft(int x, int y, const char Player, ResultCoup &toto);
  void		takeDownRight(int x, int y, const char Player, ResultCoup &toto);
  void		takeDownLeft(int x, int y, const char Player, ResultCoup &toto);
  int		dist_to_spaceRight(int x, int y, const char Player);
  int		dist_to_spaceLeft(int x, int y, const char Player);
  int		checkPattern21longHorizontal(int x, int y, const char Player, int incr);
  bool		checkPattern21shortHorizontal(int x, int y, const char Player, int incr);
  int		dist_to_spaceUp(int x, int y, const char Player);
  int		dist_to_spaceDown(int x, int y, const char Player);
  int		checkPattern21longVertical(int x, int y, const char Player, int incr);
  bool		checkPattern21shortVertical(int x, int y, const char Player, int incr);
  int		dist_to_spaceUpRight(int x, int y, const char Player);
  int		dist_to_spaceUpLeft(int x, int y, const char Player);
  int		dist_to_spaceDownRight(int x, int y, const char Player);
  int		dist_to_spaceDownLeft(int x, int y, const char Player);
  int		checkPattern21longDiagonal(int x, int y, const char Player, int incr_x, int incr_y);
  bool		checkPattern21shortDiagonal(int x, int y, const char Player, int incr_x, int incr_y);
  bool		diago_down_case(const char Player);
  bool		diago_up_case(const char Player);
  bool		hori_case(const char Player, int mult);
  bool		verti_case(const char Player, int mult);
  bool		checkdouble3(int x, int y, const char player);
  bool		isFull(Direction direction, const char tmp, auto it);

  const	config	*m_config;

public:
  Model(const MAPTYPE **map, const config *);
  Model(const Model &, const MAPTYPE **map);
  
  std::list<Five> fives;
  char	check_five();
  ResultCoup	verifCoordonnee(const char player, const Pos &position);
  bool		checkCoordonnee(const char player, const Pos &pos);
};

#endif
