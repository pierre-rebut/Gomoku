
#include "Heuristic.hpp"

Heuristic::Heuristic(const int _playStyle)
{
  /*static const int[] classicAlign = {0, 0, 10, 30, 90, WIN};
  static const int[] classicTake = {0, 20, 50, 100, 200, WIN};
  static const int[] classicAlignFoe = {0, 0, -10, -30, -90, LOSE};
  static const int[] classicTakeFoe = {0, -20, -50, -100, -200, LOSE};
  static const int[] specialAlign = {0, 0, 20, 50, 150, WIN};
  static const int[] specialTake = {0, 30, 100, 250, 500, WIN};
  static const int[] specialAlignFoe = {0, 0, -20, -50, -150, LOSE};
  static const int[] specialTakeFoe = {0, -30, -100, -250, -500, LOSE};*/


  if (_playStyle == OFFENSIVE_FIVE)
    {
      // Values for own player alignement
      align[0] = 0;
      align[1] = 0;
      align[2] = 20;
      align[3] = 50;
      align[4] = 150;
      align[5] = WIN;
      // Values for other player alignement
      alignFoe[0] = 0;
      alignFoe[1] = 0;
      alignFoe[2] = -10;
      alignFoe[3] = -30;
      alignFoe[4] = -90;
      alignFoe[5] = LOSE;
      // Values for own player takes
      rocksTaken[0] = 0;
      rocksTaken[1] = 20;
      rocksTaken[2] = 50;
      rocksTaken[3] = 100;
      rocksTaken[4] = 200;
      rocksTaken[5] = WIN;
      // Values for other player takes
      rocksTakenFoe[0] = 0;
      rocksTakenFoe[1] = -20;
      rocksTakenFoe[2] = -50;
      rocksTakenFoe[3] = -100;
      rocksTakenFoe[4] = -200;
      rocksTakenFoe[5] = LOSE;
    }
  else if (_playStyle == OFFENSIVE_TAKE)
    {
      // Values for own player alignement
      align[0] = 0;
      align[1] = 0;
      align[2] = 10;
      align[3] = 30;
      align[4] = 90;
      align[5] = WIN;
      // Values for other player alignement
      alignFoe[0] = 0;
      alignFoe[1] = 0;
      alignFoe[2] = -10;
      alignFoe[3] = -30;
      alignFoe[4] = -90;
      alignFoe[5] = LOSE;
      // Values for own player takes
      rocksTaken[0] = 0;
      rocksTaken[1] = 30;
      rocksTaken[2] = 100;
      rocksTaken[3] = 250;
      rocksTaken[4] = 500;
      rocksTaken[5] = WIN;
      // Values for other player takes
      rocksTakenFoe[0] = 0;
      rocksTakenFoe[1] = -20;
      rocksTakenFoe[2] = -50;
      rocksTakenFoe[3] = -100;
      rocksTakenFoe[4] = -200;
      rocksTakenFoe[5] = LOSE;
    }
  else if (_playStyle == DEFENSIVE_FIVE)
    {
      // Values for own player alignement
      align[0] = 0;
      align[1] = 0;
      align[2] = 10;
      align[3] = 30;
      align[4] = 90;
      align[5] = WIN;
      // Values for other player alignement
      alignFoe[0] = 0;
      alignFoe[1] = 0;
      alignFoe[2] = -20;
      alignFoe[3] = -50;
      alignFoe[4] = -150;
      alignFoe[5] = LOSE;
      // Values for own player takes
      rocksTaken[0] = 0;
      rocksTaken[1] = 20;
      rocksTaken[2] = 50;
      rocksTaken[3] = 100;
      rocksTaken[4] = 200;
      rocksTaken[5] = WIN;
      // Values for other player takes
      rocksTakenFoe[0] = 0;
      rocksTakenFoe[1] = -20;
      rocksTakenFoe[2] = -50;
      rocksTakenFoe[3] = -100;
      rocksTakenFoe[4] = -200;
      rocksTakenFoe[5] = LOSE;
    }
  else if (_playStyle == DEFENSIVE_TAKE)
    {
      // Values for own player alignement
      align[0] = 0;
      align[1] = 0;
      align[2] = 10;
      align[3] = 30;
      align[4] = 90;
      align[5] = WIN;
      // Values for other player alignement
      alignFoe[0] = 0;
      alignFoe[1] = 0;
      alignFoe[2] = -10;
      alignFoe[3] = -30;
      alignFoe[4] = -90;
      alignFoe[5] = LOSE;
      // Values for own player takes
      rocksTaken[0] = 0;
      rocksTaken[1] = 20;
      rocksTaken[2] = 50;
      rocksTaken[3] = 100;
      rocksTaken[4] = 200;
      rocksTaken[5] = WIN;
      // Values for other player takes
      rocksTakenFoe[0] = 0;
      rocksTakenFoe[1] = -30;
      rocksTakenFoe[2] = -100;
      rocksTakenFoe[3] = -250;
      rocksTakenFoe[4] = -500;
      rocksTakenFoe[5] = LOSE;
    }
  else
    throw std::range_error("Heuristic must take a valid playstyle in parameter (OFFENSIVE_FIVE, OFFENSIVE_TAKE, DEFENSIVE_FIVE, DEFENSIVE_TAKE)");
  playStyle = _playStyle;
}

Heuristic::~Heuristic()
{
}

int	Heuristic::checkAlign(MAPTYPE **map, MAPTYPE color, bool foe, int x_keep, int y_keep)
{
  int	hor, ver, diag1, diag2;
  int	x = x_keep;
  int	y = y_keep;

  hor = 0;
  while (map[y][x] == color)
    {
      if (hor < 5)
	hor++;
      x--;
    }
  x = x_keep + 1;
  while (map[y][x] == color)
    {
      if (hor < 5)
	hor++;
      x++;
    }
  x = x_keep;

  ver = 0;
  while (map[y][x] == color)
    {
      if (ver < 5)
	ver++;
      y--;
    }
  y = y_keep + 1;
  while (map[y][x] == color)
    {
      if (ver < 5)
	ver++;
      y++;
    }
  y = y_keep;

  diag1 = 0;
  while (map[y][x] == color)
    {
      if (diag1 < 5)
	diag1++;
      x--;
      y--;
    }
  x = x_keep + 1;
  y = y_keep + 1;
  while (map[y][x] == color)
    {
      if (diag1 < 5)
	diag1++;
      x++;
      y++;
    }
  x = x_keep;
  y = y_keep;

  diag2 = 0;
  while (map[y][x] == color)
    {
      if (diag1 < 5)
	diag1++;
      x--;
      y++;
    }
  x = x_keep + 1;
  y = y_keep - 1;
  while (map[y][x] == color)
    {
      if (diag1 < 5)
	diag1++;
      x++;
      y--;
    }

  if (foe == true)
    return (alignFoe[hor] + alignFoe[ver] + alignFoe[diag1] + alignFoe[diag2]);
  return (align[hor] + align[ver] + align[diag1] + align[diag2]);
}

int	Heuristic::evaluate(MAPTYPE **map, MAPTYPE player, int rTaken, int rTakenFoe)
{
  int		ret = rocksTaken[rTaken] + rocksTakenFoe[rTakenFoe];
  MAPTYPE	opponent = BLACK;

  if (player == BLACK)
    opponent = WHITE;
  for (int y = MAP_MIN; y < MAP_MAX; y++)
    for (int x = MAP_MIN; x < MAP_MAX; x++)
      {
	if (map[y][x] == player)
	  ret += checkAlign(map, player, false, x, y);
	else
	  ret += checkAlign(map, player, true, x, y);
      }
  return (ret);
}
