#include "Model.hpp"

int Model::dist_to_spaceRight(int x, int y, const char Player)
{
  int		i = 0;

  while (x <= MAP_MAX && m_map[y][x] != EMPTY)
    {
      if (m_map[y][x] == FOE(Player))
	return (-1);
      x++;
      i++;
    }
  if (x == MAP_MAX + 1)
    return (-1);
  return (i);
}

int Model::dist_to_spaceLeft(int x, int y, const char Player)
{
  int		i = 0;

  while (x >= MAP_MIN && m_map[y][x] != EMPTY)
    {
      if (m_map[y][x] == FOE(Player))
	return (-1);
      x--;
      i++;
    }
  if (x == MAP_MIN - 1)
    return (-1);
  return (i);
}

int Model::dist_to_spaceDown(int x, int y, const char Player)
{
  int		i = 0;

  while (y <= MAP_MAX && m_map[y][x] != EMPTY)
    {
      if (m_map[y][x] == FOE(Player))
	return (-1);
      y++;
      i++;
    }
  if (y == MAP_MAX + 1)
    return (-1);
  return (i);
}

int Model::dist_to_spaceUp(int x, int y, const char Player)
{
  int		i = 0;

  while (y >= MAP_MIN && m_map[y][x] != EMPTY)
    {
      if (m_map[y][x] == FOE(Player))
	return (-1);
      y--;
      i++;
    }
  if (y == MAP_MIN - 1)
    return (-1);
  return (i);
}

int Model::dist_to_spaceUpRight(int x, int y, const char Player)
{
  int		i = 0;

  while (y >= MAP_MIN && x <= MAP_MAX && m_map[y][x] != EMPTY)
    {
      if (m_map[y][x] == FOE(Player))
	return (-1);
      y--;
      x++;
      i++;
    }
  if (y == MAP_MIN - 1 || x == MAP_MAX + 1)
    return (-1);
  return (i);
}

int Model::dist_to_spaceDownLeft(int x, int y, const char Player)
{
  int		i = 0;

  while (y <= MAP_MAX && x >= MAP_MIN && m_map[y][x] != EMPTY)
    {
      if (m_map[y][x] == FOE(Player))
	return (-1);
      y++;
      x--;
      i++;
    }
  if (y == MAP_MAX + 1 || x == MAP_MIN - 1)
    return (-1);
  return (i);
}

int Model::dist_to_spaceUpLeft(int x, int y, const char Player)
{
  int		i = 0;

  while (y >= MAP_MIN && x >= MAP_MIN && m_map[y][x] != EMPTY)
    {
      if (m_map[y][x] == FOE(Player))
	return (-1);
      y--;
      x--;
      i++;
    }
  if (y == MAP_MIN - 1 || x == MAP_MIN - 1)
    return (-1);
  return (i);
}

int Model::dist_to_spaceDownRight(int x, int y, const char Player)
{
  int		i = 0;

  while (y <= MAP_MAX && x <= MAP_MAX && m_map[y][x] != EMPTY)
    {
      if (m_map[y][x] == FOE(Player))
	return (-1);
      y++;
      x++;
      i++;
    }
  if (y == MAP_MAX + 1 || x == MAP_MAX + 1)
    return (-1);
  return (i);
}

int	Model::checkPattern21longHorizontal(int x, int y, const char Player, int incr)
{
  int max = x + (4 * incr);
  int min = x - incr;

  if (m_map[y][x + (3 * incr)] == Player && m_map[y][max] == EMPTY && m_map[y][min] == EMPTY)
    {
      if (m_map[y][x + incr] == Player && m_map[y][x + (2 * incr)] == EMPTY)
	{
	  five.first.first = x + incr;
	  five.first.second = y;
	  five.second.first = x + (3 * incr);
	  five.second.second = y;
	  return 1;
	}
      else if (m_map[y][x + incr] == EMPTY && m_map[y][x + (2 * incr)] == Player)
	{
	  five.first.first = x + (2 * incr);
	  five.first.second = y;
	  five.second.first = x + (3 * incr);
	  five.second.second = y;
	  return 2;
	}
    }
  return 0;
}

bool	Model::checkPattern21shortHorizontal(int x, int y, const char Player, int incr)
{
  int	max = x + (3 * incr);
  int	min = x - (2 * incr);

  if (m_map[y][min] == EMPTY && m_map[y][x - incr] == Player && m_map[y][x + incr] == EMPTY && m_map[y][x + (2 * incr)] == Player && m_map[y][max] == EMPTY)
    {
      five.first.first = x - incr;
      five.first.second = y;
      five.second.first = x + (2 * incr);
      five.second.second = y;
      return (true);
    }
  return false;
}

int	Model::checkPattern21longVertical(int x, int y, const char Player, int incr)
{
  int max = y + (4 * incr);
  int min = y - incr;

  if (m_map[y + (3 * incr)][x] == Player && m_map[max][x] == EMPTY && m_map[min][x] == EMPTY)
    {
      if (m_map[y + incr][x] == Player && m_map[y + (2 * incr)][x] == EMPTY)
	{
	  five.first.first = x;
	  five.first.second = y + incr;
	  five.second.first = x;
	  five.second.second = y + (3 * incr);
	  return 1;
	}
      else if (m_map[y + incr][x] == EMPTY && m_map[y + (2 * incr)][x] == Player)
	{
	  five.first.first = x;
	  five.first.second = y + (2 * incr);
	  five.second.first = x;
	  five.second.second = y + (3 * incr);
	  return 2;
	}
    }
  return 0;
}

bool	Model::checkPattern21shortVertical(int x, int y, const char Player, int incr)
{
  int	max = y + (3 * incr);
  int	min = y - (2 * incr);

  if (m_map[min][x] == EMPTY && m_map[y - incr][x] == Player && m_map[y + incr][x] == EMPTY && m_map[y + (2 * incr)][x] == Player && m_map[max][x] == EMPTY)
    {
      five.first.first = x;
      five.first.second = y - incr;
      five.second.first = x;
      five.second.second = y + (2 * incr);
      return (true);
    }
  return false;
}

int	Model::checkPattern21longDiagonal(int x, int y, const char Player, int incr_x, int incr_y)
{
  int max_x = x + (4 * incr_x);
  int min_x = x - incr_x;
  int max_y = y + (4 * incr_y);
  int min_y = y - incr_y;

  if (m_map[y + (3 * incr_y)][x + (3 * incr_x)] == Player && m_map[max_y][max_x] == EMPTY && m_map[min_y][min_x] == EMPTY)
    {
      if (m_map[y + incr_y][x + incr_x] == Player && m_map[y + (2 * incr_y)][x + (2 * incr_x)] == EMPTY)
	{
	  five.first.first = x + incr_x;
	  five.first.second = y + incr_y;
	  five.second.first = x + (3 * incr_x);
	  five.second.second = y + (3 * incr_y);
	  return 1;
	}
      else if (m_map[y + incr_y][x + incr_x] == EMPTY && m_map[y + (2 * incr_y)][x + (2 * incr_x)] == Player)
	{
	  five.first.first = x + (2 * incr_x);
	  five.first.second = y + (2 * incr_y);
	  five.second.first = x + (3 * incr_x);
	  five.second.second = y + (3 * incr_y);
	  return 2;
	}
    }
  return 0;
}

bool	Model::checkPattern21shortDiagonal(int x, int y, const char Player, int incr_x, int incr_y)
{
  int	max_x = x + (3 * incr_x);
  int	min_x = x - (2 * incr_x);
  int	max_y = y + (3 * incr_y);
  int	min_y = y - (2 * incr_y);

  if (m_map[min_y][min_x] == EMPTY && m_map[y - incr_y][x - incr_x] == Player && m_map[y + incr_y][x + incr_x] == EMPTY && m_map[y + (2 * incr_y)][x + (2 * incr_x)] == Player && m_map[max_y][max_x] == EMPTY)
    {
      five.first.first = x - incr_x;
      five.first.second = y - incr_y;
      five.second.first = x + (2 * incr_x);
      five.second.second = y + (2 * incr_y);
      return (true);
    }
  return false;
}

#include <iostream>

int		Model::check3libreHorizontal(int x, int y, const char Player)
{
  int		resRight = dist_to_spaceRight(x + 1, y, Player);
  int		resLeft = dist_to_spaceLeft(x - 1, y, Player);

  if (resRight == - 1 || resLeft == -1)
    return 0;
  int res = resRight + resLeft + 1;
  if (res < 3)
    {
      switch (checkPattern21longHorizontal(x, y, Player, 1))
      {
        case 1:
        {
          if (checkPattern21longHorizontal(five.second.first, five.second.second, Player, 1))
            return 2;
          return 1;
        }
        case 2:
        {
          if (checkPattern21longHorizontal(x, y, Player, -1))
            return 2;
          return 1;
        }
      }
      if (checkPattern21shortHorizontal(x, y, Player, 1))
      {
        if (checkPattern21longHorizontal(five.second.first, five.second.second, Player, 1) == 2)
          return 2;
        return 1;
      }
      switch (checkPattern21longHorizontal(x, y, Player, -1))
      {
        case 1:
        {
          if (checkPattern21longHorizontal(five.second.first, five.second.second, Player, -1))
            return 2;
          return 1;
        }
        case 2:
        {
          if (checkPattern21longHorizontal(x, y, Player, 1))
            return 2;
          return 1;
        }
      }
      if (checkPattern21shortHorizontal(x, y, Player, -1))
      {
        if (checkPattern21longHorizontal(five.second.first, five.second.second, Player, -1) == 2)
          return 2;
        return 1;
      }
    }
  else if (res == 3)
    {
      switch (resRight){
        case 0:
        {
          five.first.first = x - 1;
          five.first.second = y;
          five.second.first = x - 2;
          five.second.second = y;
          break;
        }
        case 1:
        {
          five.first.first = x - 1;
          five.first.second = y;
          five.second.first = x + 1;
          five.second.second = y;
          break;
        }
        case 2:
        {
          five.first.first = x + 1;
          five.first.second = y;
          five.second.first = x + 2;
          five.second.second = y;
          break;
        }
      }
      return 1;
    }
  return 0;
}

int		Model::check3libreVertical(int x, int y, const char Player)
{
  int		resUp = dist_to_spaceUp(x, y - 1, Player);
  int		resDown = dist_to_spaceDown(x, y + 1, Player);

  if (resUp == - 1 || resDown == -1)
    return 0;
  int res = resUp + resDown + 1;
  if (res < 3)
    {
      switch (checkPattern21longVertical(x, y, Player, 1))
      {
        case 1:
        {
          if (checkPattern21longVertical(five.second.first, five.second.second, Player, 1))
            return 2;
          return 1;
        }
        case 2:
        {
          if (checkPattern21longVertical(x, y, Player, -1))
            return 2;
          return 1;
        }
      }
      if (checkPattern21shortVertical(x, y, Player, 1))
      {
        if (checkPattern21longVertical(five.second.first, five.second.second, Player, 1) == 2)
          return 2;
        return 1;
      }
      switch (checkPattern21longVertical(x, y, Player, -1))
      {
        case 1:
        {
          if (checkPattern21longVertical(five.second.first, five.second.second, Player, -1))
            return 2;
          return 1;
        }
        case 2:
        {
          if (checkPattern21longVertical(x, y, Player, 1))
            return 2;
          return 1;
        }
      }
      if (checkPattern21shortVertical(x, y, Player, -1))
      {
        if (checkPattern21longVertical(five.second.first, five.second.second, Player, -1) == 2)
          return 2;
        return 1;
      }
    }
  else if (res == 3)
    {
      switch (resUp){
        case 0:
        {
          five.first.first = x;
          five.first.second = y + 1;
          five.second.first = x;
          five.second.second = y + 2;
          break;
        }
        case 1:
        {
          five.first.first = x;
          five.first.second = y + 1;
          five.second.first = x;
          five.second.second = y - 1;
          break;
        }
        case 2:
        {
          five.first.first = x;
          five.first.second = y - 1;
          five.second.first = x;
          five.second.second = y - 2;
          break;
        }
      }
      return 1;
    }
  return 0;
}

int		Model::check3libreDiagonalUpRight(int x, int y, const char Player)
{
/// UpRight + DownLeft

  int		resUp = dist_to_spaceUpRight(x + 1, y - 1, Player);
  int		resDown = dist_to_spaceDownLeft(x - 1, y + 1, Player);
  int		res;

  if (resDown == - 1 || resUp == -1)
    return 0;
  res = resDown + resUp + 1;
  if (res < 3)
    {
      switch (checkPattern21longDiagonal(x, y, Player, 1, -1))
      {
        case 1:
        {
          if (checkPattern21longDiagonal(five.second.first, five.second.second, Player, 1, -1))
            return 2;
          return 1;
        }
        case 2:
        {
          if (checkPattern21longDiagonal(x, y, Player, -1, 1))
            return 2;
          return 1;
        }
      }
      if (checkPattern21shortDiagonal(x, y, Player, 1, -1))
      {
        if (checkPattern21longDiagonal(five.second.first, five.second.second, Player, 1, -1) == 2)
          return 2;
        return 1;
      }
      switch (checkPattern21longDiagonal(x, y, Player, -1, 1))
      {
        case 1:
        {
          if (checkPattern21longDiagonal(five.second.first, five.second.second, Player, -1, 1))
            return 2;
          return 1;
        }
        case 2:
        {
          if (checkPattern21longDiagonal(x, y, Player, 1, -1))
            return 2;
          return 1;
        }
      }
      if (checkPattern21shortDiagonal(x, y, Player, -1, 1))
      {
        if (checkPattern21longDiagonal(five.second.first, five.second.second, Player, -1, 1) == 2)
          return 2;
        return 1;
      }
    }
  else if (res == 3)
    {
      switch (resUp){
        case 0:
        {
          five.first.first = x - 1;
          five.first.second = y + 1;
          five.second.first = x - 2;
          five.second.second = y + 2;
          break;
        }
        case 1:
        {
          five.first.first = x - 1;
          five.first.second = y + 1;
          five.second.first = x + 1;
          five.second.second = y - 1;
          break;
        }
        case 2:
        {
          five.first.first = x + 1;
          five.first.second = y - 1;
          five.second.first = x + 2;
          five.second.second = y - 2;
          break;
        }
      }
      return 1;
    }
  return 0;
}

int		Model::check3libreDiagonalDownRight(int x, int y, const char Player)
{
  /// DownRight + UpLeft

  int		resDown = dist_to_spaceDownRight(x + 1, y + 1, Player);
  int		resUp = dist_to_spaceUpLeft(x - 1, y - 1, Player);
  int		res;

  if (resDown != - 1 && resUp != -1)
  {
      res = resDown + resUp + 1;
      if (res < 3)
	   {
      switch (checkPattern21longDiagonal(x, y, Player, 1, 1))
      {
        case 1:
        {
          if (checkPattern21longDiagonal(five.second.first, five.second.second, Player, 1, 1))
            return 2;
          return 1;
        }
        case 2:
        {
          if (checkPattern21longDiagonal(x, y, Player, -1, -1))
            return 2;
          return 1;
        }
      }
      if (checkPattern21shortDiagonal(x, y, Player, 1, 1))
      {
        if (checkPattern21longDiagonal(five.second.first, five.second.second, Player, 1, 1) == 2)
          return 2;
        return 1;
      }
      switch (checkPattern21longDiagonal(x, y, Player, -1, -1))
      {
        case 1:
        {
          if (checkPattern21longDiagonal(five.second.first, five.second.second, Player, -1, -1))
            return 2;
          return 1;
        }
        case 2:
        {
          if (checkPattern21longDiagonal(x, y, Player, 1, 1))
            return 2;
          return 1;
        }
      }
      if (checkPattern21shortDiagonal(x, y, Player, -1, -1))
      {
        if (checkPattern21longDiagonal(five.second.first, five.second.second, Player, -1, -1) == 2)
          return 2;
        return 1;
      }
	   }
    else if (res == 3)
	  {
	    switch (resUp){
      case 0:
      {
        five.first.first = x + 1;
        five.first.second = y + 1;
        five.second.first = x + 2;
        five.second.second = y + 2;
        break;
      }
      case 1:
      {
        five.first.first = x - 1;
        five.first.second = y - 1;
        five.second.first = x + 1;
        five.second.second = y + 1;
        break;
      }
      case 2:
      {
        five.first.first = x - 1;
        five.first.second = y - 1;
        five.second.first = x - 2;
        five.second.second = y - 2;
        break;
      }
      }
      return 1;
	  }
  }
  return (0);
}

bool		Model::checkdouble3(int x, int y, const char player)
{
  switch (check3libreHorizontal(x, y, player))
    {
      case 2:
      {
        five.first.first = -1;
        five.first.second = -1;
        five.second.first = -1;
        five.second.second = -1;
        return true;
      }
      case 1:
      {
        if (check3libreVertical(five.first.first, five.first.second, player) > 0 ||
	         check3libreVertical(five.second.first, five.second.second, player) > 0 ||
            check3libreVertical(x, y, player) > 0 ||
	          check3libreDiagonalDownRight(five.first.first, five.first.second, player) > 0 ||
	          check3libreDiagonalDownRight(five.second.first, five.second.second, player) > 0 ||
	          check3libreDiagonalDownRight(x, y, player) > 0 ||
            check3libreDiagonalUpRight(x, y, player) > 0 ||
            check3libreDiagonalUpRight(five.first.first, five.first.second, player) > 0 ||
	          check3libreDiagonalUpRight(five.second.first, five.second.second, player) > 0)
	       {
	         five.first.first = -1;
	         five.first.second = -1;
	         five.second.first = -1;
	         five.second.second = -1;
	         return (true);
	       }
      }
    }
  switch (check3libreVertical(x, y, player))
    {
      case 2:
      {
        five.first.first = -1;
        five.first.second = -1;
        five.second.first = -1;
        five.second.second = -1;
        return (true);
      }
      case 1:
      {
        if (check3libreHorizontal(five.first.first, five.first.second, player) > 0 ||
	   check3libreHorizontal(five.second.first, five.second.second, player) > 0 ||
      check3libreHorizontal(x, y, player) > 0 ||
	   check3libreDiagonalDownRight(five.first.first, five.first.second, player) > 0 ||
	    check3libreDiagonalDownRight(five.second.first, five.second.second, player) > 0 ||
     check3libreDiagonalDownRight(x, y, player) > 0 ||
     check3libreDiagonalUpRight(x, y, player) > 0 ||
	    check3libreDiagonalUpRight(five.first.first, five.first.second, player) > 0 ||
	   check3libreDiagonalUpRight(five.second.first, five.second.second, player) > 0)
  	   {
  	   five.first.first = -1;
  	   five.first.second = -1;
  	   five.second.first = -1;
  	   five.second.second = -1;
  	   return (true);
  	   }
      }
    }
  switch (check3libreDiagonalDownRight(x, y, player))
    {
      case 2:
      {
        five.first.first = -1;
        five.first.second = -1;
        five.second.first = -1;
        five.second.second = -1;
        return (true);
      }
      case 1:
      {
        if (check3libreHorizontal(five.first.first, five.first.second, player) > 0 ||
	     check3libreHorizontal(five.second.first, five.second.second, player) > 0 ||
        check3libreHorizontal(x, y, player) > 0 ||
	     check3libreVertical(five.first.first, five.first.second, player) > 0 ||
	     check3libreVertical(five.second.first, five.second.second, player) > 0 ||
        check3libreVertical(x, y, player) > 0 ||
        check3libreDiagonalUpRight(x, y, player) > 0 ||
	     check3libreDiagonalUpRight(five.first.first, five.first.second, player) > 0 ||
	     check3libreDiagonalUpRight(five.second.first, five.second.second, player) > 0)
	     {
	       five.first.first = -1;
	       five.first.second = -1;
	       five.second.first = -1;
	       five.second.second = -1;
	       return (true);
	     }
      }
    }
  switch (check3libreDiagonalUpRight(x, y, player))
    {
      case 2:
      {
        five.first.first = -1;
        five.first.second = -1;
        five.second.first = -1;
        five.second.second = -1;
        return (true);
      }
      case 1:
      {
        if (check3libreHorizontal(five.first.first, five.first.second, player) > 0 ||
	       check3libreHorizontal(five.second.first, five.second.second, player) > 0 ||
          check3libreHorizontal(x, y, player) > 0 ||
	       check3libreVertical(five.first.first, five.first.second, player) > 0 ||
	       check3libreVertical(five.second.first, five.second.second, player) > 0 ||
          check3libreVertical(x, y, player) > 0 ||
          check3libreDiagonalDownRight(x, y, player) > 0 ||
	       check3libreDiagonalDownRight(five.first.first, five.first.second, player) > 0 ||
	       check3libreDiagonalDownRight(five.second.first, five.second.second, player) > 0)
        {
          five.first.first = -1;
          five.first.second = -1;
          five.second.first = -1;
          five.second.second = -1;
          return (true);
        }
      }
    }
  return (false);
}
