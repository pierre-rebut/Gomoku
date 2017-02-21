
#ifndef		CPP_GOMOKU_MYEVENT_HPP
# define	CPP_GOMOKU_MYEVENT_HPP

# include	"pos.hpp"

enum          btnVal
  {
    EXIT,
    START,
    PLAYER1_IA,
    PLAYER2_IA,
    DOUBLE_3,
    BROKEN_5,
    SOUND_MUTE,
    SOUND_PLUS,
    SOUND_MOIN,
    MENU_MAIN
  };

enum		eventType : char
  {
    EXIT_EVT,
    PUT_STONE,
    RESET_WINNER,
    RESET_GAME
  };

struct		myEvent
{
  eventType	type;
  Pos		pos;
};

struct		config
{
  bool		double3;
  bool		broken5;
};

#endif
