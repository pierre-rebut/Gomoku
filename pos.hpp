
#ifndef		CPP_GOMOKU_POS_HPP
# define	CPP_GOMOKU_POS_HPP

# define	MAP_MIN		4
# define	MAP_MAX		23

enum MAPTYPE : char
  {
    BLACK = -1,
    WHITE = 1,
    EMPTY,
    LIMIT
  };

enum MENU : char
  {
    PAUSE,
    MAINMENU,
    GAME,
    WINNER
  };

# define FOE(x) ((x == WHITE) ? (BLACK) : (WHITE))

struct		Pos
{
  int		x;
  int		y;

  Pos(int a = 0, int b = 0)
  {
    x = a;
    y = b;
  }
  bool	operator==(const Pos &tmp)
  {
    if (x == tmp.x && y == tmp.y)
      return (true);
    return (false);
  }
};

#endif
