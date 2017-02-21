
#ifndef		CPP_GOMOKU_FIVE_HPP
# define	CPP_GOMOKU_FIVE_HPP

enum		Direction
  {
    HORI,
    VERTI,
    DIA_1,
    DIA_2
  };

struct		Five
{
  std::pair<std::pair<int, int>, std::pair<int,int> > five;
  Direction dir;
};

#endif
