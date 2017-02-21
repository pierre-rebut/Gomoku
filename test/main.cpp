#include <iostream>
#include <utility>

int	tab[][5]
{
  {-1, 0},
    {1, 0},
      {-1, 1},
	{5, 1},
	  {-1, -1},
	    {5, 1}
};

/*std::pair<int, int>		checkAround(std::pair<int, int> elem)
{
  for ():
  throw -1;
  }*/

bool		hori_case(std::pair<std::pair<int, int>, std::pair<int,int> > five)
{
  if (five.first.first + tab[0][0], five.first.second + tab[0][1])
    return true;
  if (five.second.first + tab[1][0], five.second.second + tab[1][1])
    return true;
  for (int i = five.first.first + tab[2][0] ; i < five.first.first + tab[3][0]; i++)
    ;
  for (int i = five.first.first + tab[4][0] ; i < five.first.first + tab[5][0]; i++)
    ;
}

void		fiveBroken()
{
  std::pair<std::pair<int, int>, std::pair<int,int> > five;
  std::pair<int, int> top (1,1);
  std::pair<int, int> bot (6,1);
  five.first = top;
  five.second = bot;
  if (five.first.first < five.second.first)
    {
      if (hori_case(five) == true)
	std::cout << "is ok" << std::endl;
    }
  /* for (int i = five.first.first - 1 ; i < five.second.first - 1 ; i++)
    {
    }
  for (int i = five.first.first - 1 ; i < five.second.first + 1 ; i++)
    {
    }*/
}

int		main()
{
  fiveBroken();
}
