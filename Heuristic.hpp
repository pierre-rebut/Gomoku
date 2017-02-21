#ifndef		HEURISTIC_HPP
# define	HEURISTIC_HPP

# define	OFFENSIVE_FIVE	0
# define	OFFENSIVE_TAKE	1
# define	DEFENSIVE_FIVE	2
# define	DEFENSIVE_TAKE	3
# define	WIN		9000
# define	LOSE		-9000

# include	<array>
# include	"pos.hpp"

class		Heuristic
{
  int			playStyle;
  std::array<int, 6>	align;
  std::array<int, 6>	alignFoe;
  std::array<int, 6>	rocksTaken;
  std::array<int, 6>	rocksTakenFoe;

  int	checkAlign(MAPTYPE** map, MAPTYPE player, bool foe, int x, int y);

public:
  Heuristic(const int playStyle);
  ~Heuristic();

  int	evaluate(MAPTYPE **map, MAPTYPE player, int rTaken, int rTakenFoe);
};

#endif		/* HEURISTIC_HPP! */
