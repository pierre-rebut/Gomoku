#include "Model.hpp"
#include <iostream>

int	tab[][5] = {
  {-1, -1},//blanc
  {-2, -2},//noir
  {1, 1},//empty
  {0, -1},//blanc
  {0, -2},//noir
  {0, 1},//empty
  {1, -1},//blanc
  {2, -2},//noir
  {-1, 1}//empty
};

Model::Model(const MAPTYPE **map, const config *conf) : m_map(map), m_config(conf)
{
}

Model::Model(const Model &mod, const MAPTYPE **map): m_map(map), m_config(mod.m_config)
{
  fives = mod.fives;
  five = mod.five;
}

int		Model::countUp(int x, int y, const char Player)
{
  int		count;

  count = 0;
  while (y >= MAP_MIN && m_map[y][x] == Player)
    {
      y--;
      count++;
    }
  return (count);
}

int		Model::countDown(int x, int y, const char Player)
{
  int		count;

  count = 0;
  while (y <= MAP_MAX && m_map[y][x] == Player)
    {
      y++;
      count++;
    }
  return (count);
}

int		Model::countRight(int x, int y, const char Player)
{
  int		count;

  count = 0;
  while (x <= MAP_MAX && m_map[y][x] == Player)
    {
      x++;
      count++;
    }
  return (count);
}

int		Model::countLeft(int x, int y, const char Player)
{
  int		count;

  count = 0;
  while (x >= MAP_MIN && m_map[y][x] == Player)
    {
      x--;
      count++;
    }
  return (count);
}

int		Model::countUpRight(int x, int y, const char Player)
{
  int		count;

  count = 0;
  while (y >= MAP_MIN && x <= MAP_MAX && m_map[y][x] == Player)
    {
      x++;
      y--;
      count++;
    }
  return (count);
}

int		Model::countUpLeft(int x, int y, const char Player)
{
  int		count;

  count = 0;
  while (y >= MAP_MIN && x >= MAP_MIN && m_map[y][x] == Player)
    {
      x--;
      y--;
      count++;
    }
  return (count);
}

int		Model::countDownRight(int x, int y, const char Player)
{
  int		count;

  count = 0;
  while (y <= MAP_MAX && x <= MAP_MAX && m_map[y][x] == Player)
    {
      x++;
      y++;
      count++;
    }
  return (count);
}

int		Model::countDownLeft(int x, int y, const char Player)
{
  int		count;

  count = 0;
  while (y <= MAP_MAX && x >= MAP_MIN && m_map[y][x] == Player)
    {
      x--;
      y++;
      count++;
    }
  return (count);
}

void		Model::takeUp(int x, int y, const char Player, ResultCoup &toto)
{
  char		foe = FOE(Player);

  if (m_map[y - 1][x] == foe && m_map[y - 2][x] == foe && m_map[y - 3][x] == Player)
    {
      toto.capture = true;
      toto.taken.push_front(std::make_pair(x, y - 1));
      toto.taken.push_front(std::make_pair(x, y - 2));
    }
}

void		Model::takeDown(int x, int y, const char Player, ResultCoup &toto)
{
  char		foe = FOE(Player);

  if (m_map[y + 1][x] == foe && m_map[y + 2][x] == foe && m_map[y + 3][x] == Player)
    {
      toto.capture = true;
      toto.taken.push_front(std::make_pair(x, y + 1));
      toto.taken.push_front(std::make_pair(x, y + 2));
    }
}

void		Model::takeLeft(int x, int y, const char Player, ResultCoup &toto)
{
  char		foe = FOE(Player);

  if (m_map[y][x - 1] == foe && m_map[y][x - 2] == foe && m_map[y][x - 3] == Player)
    {
      toto.capture = true;
      toto.taken.push_front(std::make_pair(x - 1, y));
      toto.taken.push_front(std::make_pair(x - 2, y));
    }
}

void		Model::takeRight(int x, int y, const char Player, ResultCoup &toto)
{
  char		foe = FOE(Player);

  if (m_map[y][x + 1] == foe && m_map[y][x + 2] == foe && m_map[y][x + 3] == Player)
    {
      toto.capture = true;
      toto.taken.push_front(std::make_pair(x + 1, y));
      toto.taken.push_front(std::make_pair(x + 2, y));
    }
}

void		Model::takeUpRight(int x, int y, const char Player, ResultCoup &toto)
{
  char		foe = FOE(Player);

  if (m_map[y - 1][x + 1] == foe && m_map[y - 2][x + 2] == foe && m_map[y - 3][x + 3] == Player)
    {
      toto.capture = true;
      toto.taken.push_front(std::make_pair(x + 1, y - 1));
      toto.taken.push_front(std::make_pair(x + 2, y - 2));
    }
}

void		Model::takeUpLeft(int x, int y, const char Player, ResultCoup &toto)
{
  char		foe = FOE(Player);

  if (m_map[y - 1][x - 1] == foe && m_map[y - 2][x - 2] == foe && m_map[y - 3][x - 3] == Player)
    {
      toto.capture = true;
      toto.taken.push_front(std::make_pair(x - 1, y - 1));
      toto.taken.push_front(std::make_pair(x - 2, y - 2));
    }
}

void		Model::takeDownRight(int x, int y, const char Player, ResultCoup &toto)
{
  char		foe = FOE(Player);

  if (m_map[y + 1][x + 1] == foe && m_map[y + 2][x + 2] == foe && m_map[y + 3][x + 3] == Player)
    {
      toto.capture = true;
      toto.taken.push_front(std::make_pair(x + 1, y + 1));
      toto.taken.push_front(std::make_pair(x + 2, y + 2));
    }
}

void		Model::takeDownLeft(int x, int y, const char Player, ResultCoup &toto)
{
  char		foe = FOE(Player);

  if (m_map[y + 1][x - 1] == foe && m_map[y + 2][x - 2] == foe && m_map[y + 3][x - 3] == Player)
    {
      toto.capture = true;
      toto.taken.push_front(std::make_pair(x - 1, y + 1));
      toto.taken.push_front(std::make_pair(x - 2, y + 2));
    }
}

bool		Model::diago_down_case(const char Player)
{
  int y = five.first.first;
  int x = five.first.second;
  int y2 = five.second.first;
  int count = 0;

  int j = x;
  for (int i = y ; i <= y2; i++)
    {
      if (m_map[i + tab[5][0]][j + tab[5][1]] == Player && ((m_map[i + tab[4][0] * -1][j + tab[4][1] * -1] == FOE(Player) && m_map[i + tab[3][0]][j + tab[3][1]] == EMPTY) || (m_map[i + tab[4][0] * -1][j + tab[4][1] * -1] == EMPTY && m_map[i + tab[3][0]][j + tab[3][1]] == FOE(Player))))
	if (y2 - i < 5)
	  return false;
	else
	  count = 0;
      else if (m_map[i + tab[2][0]][j + tab[2][1]] == Player && ((m_map[i + tab[1][0] * -1][j + tab[1][1] * -1] == FOE(Player) && m_map[i + tab[0][0]][j + tab[0][1]] == EMPTY) || (m_map[i + tab[1][0] * -1][j + tab[1][1] * -1] == EMPTY && m_map[i + tab[0][0]][j + tab[0][1]] == FOE(Player))))
	if (y2 - i < 5)
	  return false;
	else
	  count = 0;
      else if (m_map[i + tab[5][1]][j + tab[5][0]] == Player && ((m_map[i + tab[4][1] * -1][j + tab[4][0] * -1] == FOE(Player) && m_map[i + tab[3][1]][j + tab[3][0]] == EMPTY) || (m_map[i + tab[4][1] * -1][j + tab[4][0] * -1] == EMPTY && m_map[i + tab[3][1]][j + tab[3][0]] == FOE(Player))))
	if (y2 - i < 5)
	  return false;
	else
	  count = 0;
      else if (m_map[i + tab[3][1]][j + tab[3][0]] == Player && ((m_map[i + tab[4][1]][j + tab[4][0]] == FOE(Player) && m_map[i + tab[5][1]][j + tab[5][0]] == EMPTY) || (m_map[i + tab[4][1]][j + tab[4][0]] == EMPTY && m_map[i + tab[5][1]][j + tab[5][0]] == FOE(Player))))
	if (y2 - i < 5)
	  return false;
	else
	  count = 0;
      else if (m_map[i + tab[0][0]][j + tab[0][1]] == Player && ((m_map[i + tab[1][0]][j + tab[1][1]] == FOE(Player) && m_map[i + tab[2][0]][j + tab[2][1]] == EMPTY) || (m_map[i + tab[1][0]][j + tab[1][1]] == EMPTY && m_map[i + tab[2][0]][j + tab[2][1]] == FOE(Player))))
	if (y2 - i < 5)
	  return false;
	else
	  count = 0;
      else if (m_map[i + tab[3][0]][j + tab[3][1]] == Player && ((m_map[i + tab[4][0]][j + tab[4][1]] == FOE(Player) && m_map[i + tab[5][0]][j + tab[5][1]] == EMPTY) || (m_map[i + tab[4][0]][j + tab[4][1]] == EMPTY && m_map[i + tab[5][0]][j + tab[5][1]] == FOE(Player))))
	if (y2 - i < 5)
	  return false;
	else
	  count = 0;
      else
	count++;
      if (count == 5)
	return true;
      j--;
    }
  return true;
}

bool		Model::diago_up_case(const char Player)
{
  int y = five.first.first;
  int x = five.first.second;
  int y2 = five.second.first;
  int count = 0;

  int j = x;
  for (int i = y ; i <= y2; i++)
    {
      if (m_map[i + tab[3][1]][j + tab[3][0]] == Player && ((m_map[i + tab[4][1]][j + tab[4][0]] == FOE(Player) && m_map[i + tab[5][1]][j + tab[5][0]] == EMPTY) || (m_map[i + tab[4][1]][j + tab[4][0]] == EMPTY && m_map[i + tab[5][1]][j + tab[5][0]] == FOE(Player))))
	if (y2 - i < 5)
	  return false;
	else
	  count = 0;
      else if (m_map[i + tab[8][0]][j + tab[8][1]] == Player && ((m_map[i + tab[7][1]][j + tab[7][0]] == FOE(Player) && m_map[i + tab[6][0]][j + tab[6][1]] == EMPTY) || (m_map[i + tab[7][1]][j + tab[7][0]] == EMPTY && m_map[i + tab[6][0]][j + tab[6][1]] == FOE(Player))))
	if (y2 - i < 5)
	  return false;
	else
	  count = 0;
      else if (m_map[i + tab[5][0]][j + tab[5][1]] == Player && ((m_map[i + tab[4][0]][j + tab[4][1] * -1] == FOE(Player) && m_map[i + tab[3][0]][j + tab[3][1]] == EMPTY) || (m_map[i + tab[4][1]][j + tab[4][0]] == EMPTY && m_map[i + tab[3][0]][j + tab[3][1]] == FOE(Player))))
	if (y2 - i < 5)
	  return false;
	else
	  count = 0;
      else if (m_map[i + tab[3][1] * -1][j + tab[3][0] * -1] == Player && ((m_map[i + tab[4][1] * -1][j + tab[4][0] * -1] == FOE(Player) && m_map[i + tab[5][1] * -1][j + tab[5][0] * -1] == EMPTY) || (m_map[i + tab[4][1] * -1][j + tab[4][0] * -1] == EMPTY && m_map[i + tab[5][1] * -1][j + tab[5][0] * -1] == FOE(Player))))
	if (y2 - i < 5)
	  return false;
	else
	  count = 0;
      else if (m_map[i + tab[8][0] * -1][j + tab[8][1] * -1] == Player && ((m_map[i + tab[7][1] * -1][j + tab[7][0] * -1] == FOE(Player) && m_map[i + tab[6][0] * -1][j + tab[6][1] * -1] == EMPTY) || (m_map[i + tab[7][1] * -1][j + tab[7][0] * -1] == EMPTY && m_map[i + tab[6][0] * -1][j + tab[6][1] * -1] == FOE(Player))))
	if (y2 - i < 5)
	  return false;
	else
	  count = 0;
      else if (m_map[i + tab[5][0] * -1][j + tab[5][1] * -1] == Player && ((m_map[i + tab[4][0] * -1][j + tab[4][1]] == FOE(Player) && m_map[i + tab[3][0] * -1][j + tab[3][1] * -1] == EMPTY) || (m_map[i + tab[4][0] * -1][j + tab[4][1]] == EMPTY && m_map[i + tab[3][0] * -1][j + tab[3][1] * -1] == FOE(Player))))
	if (y2 - i < 5)
	  return false;
	else
	  count = 0;
      else
	count++;
      if (count == 5)
	return true;
      j++;
    }
  return true;
}

bool		Model::hori_case(const char Player, int mult)
{
  int y = five.first.first;
  int x = five.first.second;
  int x2 = five.second.second;
  int count = 0;

  for (int i = x ; i <= x2; i++)
    {
      if (m_map[y + tab[0][1] * mult][i + tab[0][0] * mult] == Player && ((m_map[y + tab[1][1] * mult][i + tab[1][0] * mult] == FOE(Player) && m_map[y + tab[2][1] * mult][i + tab[2][0] * mult] == EMPTY) || (m_map[y + tab[1][1] * mult][i + tab[1][0] * mult] == EMPTY && m_map[y + tab[2][1] * mult][i + tab[2][0] * mult] == FOE(Player))))
	if (x2 - i < 5)
	  return false;
	else
	  count = 0;
      else if (m_map[y + tab[3][1] * mult][i + tab[3][0] * mult] == Player && ((m_map[y + tab[4][1] * mult][i + tab[4][0] * mult] == FOE(Player) && m_map[y + tab[5][1] * mult][i + tab[5][0] * mult] == EMPTY) || (m_map[y + tab[4][1] * mult][i + tab[4][0] * mult] == EMPTY && m_map[y + tab[5][1] * mult][i + tab[5][0] * mult] == FOE(Player))))
	if (x2 - i < 5)
	  return false;
	else
	  count = 0;
      else if (m_map[y + tab[6][1] * mult][i + tab[6][0] * mult] == Player && ((m_map[y + tab[7][1] * mult][i + tab[7][0] * mult] == FOE(Player) && m_map[y + tab[8][1] * mult][i + tab[8][0] * mult] == EMPTY) || (m_map[y + tab[7][1] * mult][i + tab[7][0] * mult] == EMPTY && m_map[y + tab[8][1] * mult][i + tab[8][0] * mult] == FOE(Player))))
	if (x2 - i < 5)
	  return false;
	else
	  count = 0;
      else
	count++;
      if (count == 5)
	return true;
    }
  return true;
}

bool		Model::verti_case(const char Player, int mult)
{
  int y = five.first.first;
  int x = five.first.second;
  int y2 = five.second.first;
  int count = 0;

  for (int i = y ; i <= y2; i++)
    {
      if (m_map[i + tab[0][0] * mult][x + tab[0][1] * mult] == Player && ((m_map[i + tab[1][0] * mult][x + tab[1][1] * mult] == FOE(Player) && m_map[i + tab[2][0] * mult][x + tab[2][1] * mult] == EMPTY) || (m_map[i + tab[1][0] * mult][x + tab[1][1] * mult] == EMPTY && m_map[i + tab[2][0] * mult][x + tab[2][1] * mult] == FOE(Player))))
	if (y2 - i < 5)
	  return false;
	else
	  count = 0;
      else if (m_map[i + tab[3][0] * mult][x + tab[3][1] * mult] == Player && ((m_map[i + tab[4][0] * mult][x + tab[4][1] * mult] == FOE(Player) && m_map[i + tab[5][0] * mult][x + tab[5][1] * mult] == EMPTY) || (m_map[i + tab[4][0] * mult][x + tab[4][1] * mult] == EMPTY && m_map[i + tab[5][0] * mult][x + tab[5][1] * mult] == FOE(Player))))
	if (y2 - i < 5)
	  return false;
	else
	  count = 0;
      else if (m_map[i + tab[6][0] * mult][x + tab[6][1] * mult] == Player && ((m_map[i + tab[7][0] * mult][x + tab[7][1] * mult] == FOE(Player) && m_map[i + tab[8][0] * mult][x + tab[8][1] * mult] == EMPTY) || (m_map[i + tab[7][0] * mult][x + tab[7][1] * mult] == EMPTY && m_map[i + tab[8][0] * mult][x + tab[8][1] * mult] == FOE(Player))))
	if (y2 - i < 5)
	  return false;
	else
	  count = 0;
      else
	count++;
      if (count == 5)
	return true;
    }
  return true;
}

bool		Model::isFull(Direction direction, const char tmp, auto it)
{
  if (direction == VERTI)
    {
      for (int i = five.first.first; i <= five.second.first; i++)
	if (m_map[i][five.first.second] != tmp)
	  {
	    fives.erase(it);
	    return false;
	  }
      return true;
    }
  else if (direction == HORI)
    {
      for (int i = five.first.second; i <= five.second.second; i++)
	if (m_map[five.first.first][i] != tmp)
	  {
	    fives.erase(it);
	    return false;
	  }
      return true;
    }
  else if (direction == DIA_1)
    {
      int j = five.first.second;
      for (int i = five.first.first; i <= five.second.first; i++)
	{
	  if (m_map[i][j] != tmp)
	    {
	      fives.erase(it);
	      return false;
	    }
	  j++;
	}
      return true;
    }
  else if (direction == DIA_2)
    {
      int j = five.first.second;
      for (int i = five.first.first; i <= five.second.first; i++)
	{
	  if (m_map[i][j] != tmp)
	    {
	      fives.erase(it);
	      return false;
	    }
	  j--;
	}
      return true;
    }
  return true;
}

char		Model::check_five()
{
  for (auto it = fives.begin(); it != fives.end(); it++)
    {
      five = (*it).five;
      const char tmp = m_map[five.first.first][five.first.second];
      if (isFull((*it).dir, tmp, it) == true)
      	{
	  if ((*it).dir == VERTI)
	    {
	      if (verti_case(tmp, 1) == true && verti_case(tmp, -1) == true)
		return tmp;
	    }
	  else if ((*it).dir == HORI)
	    {
	      if (hori_case(tmp, 1) == true && hori_case(tmp, -1) == true)
		return tmp;
	    }
	  else if ((*it).dir == DIA_1)
	    {
	      if (diago_up_case(tmp) == true)
		return tmp;
	    }
	  else if ((*it).dir == DIA_2)
	    {
	      if (diago_down_case(tmp) == true)
		return tmp;
	    }
      	}
      else
	return (const char)EMPTY;
    }
  return (const char)EMPTY;
}

bool		Model::checkCoordonnee(const char player, const Pos &pos)
{
  if (m_map[pos.y][pos.x] != EMPTY || (m_config->double3 &&
				       checkdouble3(pos.x, pos.y, player)))
    return false;
  return true;
}

ResultCoup	Model::verifCoordonnee(const char player, const Pos &pos)
{
  ResultCoup	toto;
  int		x = pos.x;
  int		y = pos.y;

  toto.winner = false;
  toto.capture = false;
  if (m_map[y][x] != EMPTY || (m_config->double3 && checkdouble3(x, y, player)))
    {
      toto.is_good = false;
      toto.error = OCCUPIED;
      return (toto);
    }
  toto.error = NONE;
  int		up = countUp(x, y - 1, player);
  int		down = countDown(x, y + 1, player);
  int		left = countLeft(x - 1, y, player);
  int		right = countRight(x + 1, y, player);
  int		upLeft = countUpLeft(x - 1, y - 1, player);
  int		downRight = countDownRight(x + 1, y + 1, player);
  int		upRight = countUpRight(x + 1, y - 1, player);
  int		downLeft = countDownLeft(x - 1, y + 1, player);
  if (up + down + 1 >= 5)
    {
      five.first.first = y - up;
      five.first.second = x;
      five.second.first = y + down;
      five.second.second = x;
      if (!m_config->broken5 ||
	  (verti_case(player, 1) == true && verti_case(player, -1) == true))
	toto.winner = true;
      else
	{
	  Five *elem = new Five;
	  (*elem).five = five;
	  (*elem).dir = VERTI;
	  fives.push_back(*elem);
	}
    }
  if (left + right + 1 >= 5)
    {
      five.first.first = y;
      five.first.second = x - left;
      five.second.first = y;
      five.second.second = x + right;
      if (!m_config->broken5 ||
	  (hori_case(player, 1) == true && hori_case(player, -1) == true))
	toto.winner = true;
      else
	{
	  Five *elem = new Five;
	  (*elem).five = five;
	  (*elem).dir = HORI;
	  fives.push_back(*elem);
	}
    }
  if (upLeft + downRight + 1 >= 5)
    {
      five.first.first = y - upLeft;
      five.first.second = x - upLeft;
      five.second.first = y + downRight;
      five.second.second = x + downRight;
      if (!m_config->broken5 || diago_up_case(player) == true)
	toto.winner = true;
      else
	{
	  Five *elem = new Five;
	  (*elem).five = five;
	  (*elem).dir = DIA_1;
	  fives.push_back(*elem);
	}
    }
  if (upRight + downLeft + 1 >= 5)
    {
      five.first.first = y - upRight;
      five.first.second = x + upRight;
      five.second.first = y + downLeft;
      five.second.second = x - downLeft;
      if (!m_config->broken5 || diago_down_case(player) == true)
	toto.winner = true;
      else
	{
	  Five *elem = new Five;
	  (*elem).five = five;
	  (*elem).dir = DIA_2;
	  fives.push_back(*elem);
	}
    }
  takeUp(x, y, player, toto);
  takeDown(x, y, player, toto);
  takeLeft(x, y, player, toto);
  takeRight(x, y, player, toto);
  takeUpRight(x, y, player, toto);
  takeUpLeft(x, y, player, toto);
  takeDownLeft(x, y, player, toto);
  takeDownRight(x, y, player, toto);
  toto.is_good = true;
  return (toto);
}
