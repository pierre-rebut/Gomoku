
#ifndef		CPP_GOMOKU_RESULTCOUP_HPP
# define	CPP_GOMOKU_RESULTCOUP_HPP

# include	<list>
# include	<utility>

enum		Error
  {
    NONE,
    OCCUPIED,
    DOUBLE3
  };

struct		ResultCoup
{
  bool		is_good;
  bool		winner;
  Error		error;
  bool		capture;
  std::list<std::pair<int, int>> taken;
};

#endif
