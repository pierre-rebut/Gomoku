
#ifndef		CPP_GOMOKU_VIEW_HPP
# define	CPP_GOMOKU_VIEW_HPP

# include	<vector>
# include	<SFML/Graphics.hpp>
# include	<SFML/Window.hpp>
# include	<SFML/Audio/Music.hpp>

# include	"myEvent.hpp"
# include	"Player.hpp"
# include	"pos.hpp"
#include "Bouton.hpp"

# define	SCREEN_WIDTH	1300
# define	SCREEN_HEIGHT	860
# define	WIDTH		800
# define	HEIGHT		800

# define	POS_MAP_X	253
# define	POS_MAP_Y	63
# define	SCALE_MAP	42

# define	GAME_VOLUME	35
# define	NUM_MUSIC	4
# define	MUSIC		0
# define	SUGOI		1
# define	WINNER		2
# define	ERROR_COUP	3

# define	NUM_TEXTURE	9
# define	TEX_BACKGROUND	0
# define	TEX_BLACKSTONE	1
# define	TEX_WHITESTONE	2
# define	TEX_FOND	3
# define	TEX_LOGO	4
# define	TEX_UNCHECKED	5
# define	TEX_CHECKED	6
# define	TEX_PLAYERWHITE	7
# define	TEX_PLAYERBLACK	8

class		View
{
  float				m_volume;
  bool				m_muted;
  std::vector<sf::Texture*>	m_lstTexture;
  std::vector<sf::Music*>	m_lstMusic;
  std::vector<Bouton> m_btn;
    sf::Image m_icon;

  sf::RenderWindow	*m_window;
  sf::Font		m_font;

  const MAPTYPE		**m_map;
  Player	 	* const m_player1;
  Player		* const m_player2;
  MENU			m_menu;

  void		printText(const std::string &, const sf::Vector2f &, const size_t,
			  const sf::Color &) const;
  void		drawRectangle(const sf::Vector2f &pos, const sf::Vector2f &size,
			      const sf::Color &color) const;

  void		drawHeader(const unsigned int, const Player *);
  void		drawMap() const;
  void		drawMenu(const config &);
  void		drawWinner(const Player *);
  void		drawPause(const unsigned int, const Player *);
  void		drawPlayer(const Player *, const int, const int, const int) const;
  void		drawSprite(const sf::Texture *, const int, const int, const int) const;
  int loadTexture();

    int checkEvent(const Pos &event);
	void drawBtn();

	void		moveStone(const Player *);
  void		dropStone(const sf::Event &, const Player *);
  void		execPause(const sf::Event &, const unsigned int, const Player *);
  void		execWinner(const sf::Event &, const Player *);
  void		execMenu(const sf::Event &, config &);

public:
  View(const MAPTYPE **map, Player * const, Player * const);
  ~View();

  void		playSound(const int, const bool = false);
  int		showSplash(const config &);
  void		updateGame(const unsigned int, const Player *);
  void		show() const;
  void		loopView(const unsigned int, const Player *, const Player *, config &);

    void setBtnMenu();
    void setBtnPause();
};

#endif
