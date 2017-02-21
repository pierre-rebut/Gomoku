
#include <string>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include "View.hpp"

bool		checkClickBtn(const Pos &event,
			    const sf::Vector2f &pos, const sf::Vector2f &size)
{
  if (event.x > pos.x && event.x < (pos.x + size.x))
    {
      if (event.y > pos.y && event.y < (pos.y + size.y))
	return (true);
    }
  return (false);
}

View::View(const MAPTYPE **map, Player * const pl1, Player * const pl2) :
  m_map(map), m_player1(pl1), m_player2(pl2)
{
  m_window = new sf::RenderWindow;
  if (m_window == NULL)
    throw std::runtime_error("sfml: can't init window");
  if (!m_font.loadFromFile("ressources/CaviarDreams_Italic.ttf"))
    std::cerr << "Warning display: No police available" << std::endl;
  m_icon = *new sf::Image();

  m_menu = MAINMENU;
  m_window->create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Gomoku", sf::Style::Close);
    m_window->clear(sf::Color::Black);
    if (!m_icon.loadFromFile("ressources/icon2.png"))
        std::cout << "cant load icon" << std::endl;
    else
        m_window->setIcon(32, 32, m_icon.getPixelsPtr());
    m_muted = false;
  m_volume = 100;
  for (int i = 0; i < NUM_TEXTURE; i++)
    m_lstTexture.push_back(new sf::Texture);
  for (int i = 0; i < NUM_MUSIC; i++)
    m_lstMusic.push_back(new sf::Music);
  m_lstMusic.at(MUSIC)->setLoop(true);
  m_lstMusic.at(MUSIC)->openFromFile("ressources/sound_music.ogg");
  m_lstMusic.at(SUGOI)->openFromFile("ressources/sound_sugoi.ogg");
  m_lstMusic.at(ERROR_COUP)->openFromFile("ressources/sound_error.ogg");
  m_lstMusic.at(WINNER)->openFromFile("ressources/sound_winner.ogg");
    if (loadTexture() == 0)
        throw std::runtime_error("sfml: can't load ressource");
    setBtnMenu();
    m_window->clear();
}

View::~View()
{
  m_window->close();
  delete m_window;
  for (int i = 0; i < NUM_TEXTURE; i++)
    delete m_lstTexture.at(i);
  for (int i = 0; i < NUM_MUSIC; i++)
    delete m_lstMusic.at(i);
}

int View::loadTexture() {
    if (!m_lstTexture.at(TEX_BACKGROUND)->loadFromFile("ressources/background.png") ||
        !m_lstTexture.at(TEX_BLACKSTONE)->loadFromFile("ressources/black_rock_go.png") ||
        !m_lstTexture.at(TEX_WHITESTONE)->loadFromFile("ressources/white_rock_go.png") ||
        !m_lstTexture.at(TEX_FOND)->loadFromFile("ressources/japan.jpg") ||
        !m_lstTexture.at(TEX_LOGO)->loadFromFile("ressources/logo.png") ||
        !m_lstTexture.at(TEX_CHECKED)->loadFromFile("ressources/checkbox.png") ||
        !m_lstTexture.at(TEX_UNCHECKED)->loadFromFile("ressources/uncheckbox.png") ||
        !m_lstTexture.at(TEX_PLAYERWHITE)->loadFromFile("ressources/player_white.png") ||
        !m_lstTexture.at(TEX_PLAYERBLACK)->loadFromFile("ressources/player_black.png"))
    return 0;
    return 1;
}

#include <iostream>

void		View::moveStone(const Player *pl)
{
  Pos		pos;

    pos.x = ((double)sf::Mouse::getPosition(*m_window).x - POS_MAP_X) / SCALE_MAP;
    pos.y = ((double)sf::Mouse::getPosition(*m_window).y - POS_MAP_Y) / SCALE_MAP;
  if (pos.x >= 0 && pos.x < 19 && pos.y >= 0 && pos.y < 19)
    {
      if (m_map[pos.y + MAP_MIN][pos.x + MAP_MIN] == EMPTY)
	drawPlayer(pl, POS_MAP_X + pos.x * SCALE_MAP,
		   POS_MAP_Y + pos.y * SCALE_MAP, 120);
    }
}

void View::setBtnMenu() {
    m_btn.clear();
    m_btn.push_back(Bouton(sf::Vector2f(SCREEN_WIDTH / 2 - 150, 300), sf::Vector2f(300, 50), START, sf::Color(190, 190, 190, 220)));
    m_btn.push_back(Bouton(sf::Vector2f(SCREEN_WIDTH / 2 - 150, 400), sf::Vector2f(300, 50), EXIT, sf::Color(190, 190, 190, 220)));
    m_btn.push_back(Bouton(sf::Vector2f(450, 600), sf::Vector2f(40, 40), DOUBLE_3,  sf::Color(190, 190, 190, 190)));
    m_btn.push_back(Bouton(sf::Vector2f(450, 670), sf::Vector2f(40, 40), BROKEN_5,  sf::Color(190, 190, 190, 190)));
    m_btn.push_back(Bouton(sf::Vector2f(950, 600), sf::Vector2f(40, 40), PLAYER1_IA,  sf::Color(190, 190, 190, 190)));
    m_btn.push_back(Bouton(sf::Vector2f(950, 670), sf::Vector2f(40, 40), PLAYER2_IA,  sf::Color(190, 190, 190, 190)));
    m_btn.push_back(Bouton(sf::Vector2f(1020, 770), sf::Vector2f(40, 40), SOUND_MUTE, sf::Color(190, 190, 190, 190)));
    m_btn.push_back(Bouton(sf::Vector2f(290, 770), sf::Vector2f(40, 40), SOUND_MOIN, sf::Color(190, 190, 190, 190)));
    m_btn.push_back(Bouton(sf::Vector2f(500, 770), sf::Vector2f(40, 40), SOUND_PLUS, sf::Color(190, 190, 190, 190)));
}

void View::setBtnPause() {
    m_btn.clear();
    m_btn.push_back(Bouton(sf::Vector2f(SCREEN_WIDTH / 2 - 150, 300), sf::Vector2f(300, 50), START, sf::Color(190, 190, 190, 220)));
    m_btn.push_back(Bouton(sf::Vector2f(SCREEN_WIDTH / 2 - 150, 400), sf::Vector2f(300, 50), MENU_MAIN, sf::Color(190, 190, 190, 220)));
    m_btn.push_back(Bouton(sf::Vector2f(SCREEN_WIDTH / 2 - 150, 500), sf::Vector2f(300, 50), EXIT, sf::Color(190, 190, 190, 220)));
    m_btn.push_back(Bouton(sf::Vector2f(1020, 770), sf::Vector2f(40, 40), SOUND_MUTE,  sf::Color(190, 190, 190, 190)));
    m_btn.push_back(Bouton(sf::Vector2f(290, 770), sf::Vector2f(40, 40), SOUND_MOIN, sf::Color(190, 190, 190, 190)));
    m_btn.push_back(Bouton(sf::Vector2f(500, 770), sf::Vector2f(40, 40), SOUND_PLUS, sf::Color(190, 190, 190, 190)));
}

void		View::dropStone(const sf::Event &evt, const Player *pl)
{
  Pos		pos;

  (void)pl;
  pos.x = static_cast<double>((evt.mouseButton.x - POS_MAP_X) / SCALE_MAP);
  pos.y = static_cast<double>((evt.mouseButton.y - POS_MAP_Y) / SCALE_MAP);
  if (pos.x >= 0 && pos.x < 19 && pos.y >= 0 && pos.y < 19)
    {
      pos.x += MAP_MIN;
      pos.y += MAP_MIN;
      myEvent myEvt;
      myEvt.type = PUT_STONE;
      myEvt.pos = pos;
      throw myEvt;
    }
}

void		View::execPause(const sf::Event &evt, const unsigned int round,
				const Player *pl)
{
  myEvent	myEvt;

  if (evt.type == sf::Event::KeyPressed && (evt.key.code == sf::Keyboard::Escape))
    m_menu = GAME;
  else if (evt.type == sf::Event::MouseButtonPressed) {
      Pos tmp(evt.mouseButton.x, evt.mouseButton.y);
      switch (checkEvent(tmp)) {
          case START:
              m_menu = GAME;
              break;
          case EXIT:
              myEvt.type = EXIT_EVT;
              throw myEvt;
          case MENU_MAIN:
              setBtnMenu();
              m_lstMusic.at(MUSIC)->setVolume(m_volume);
              m_menu = MAINMENU;
              myEvt.type = RESET_GAME;
              throw myEvt;
          default:;
      };
  }
  drawPause(round, pl);
}

void		View::execWinner(const sf::Event &evt, const Player *winner)
{
  myEvent	myEvt;

  if (evt.type == sf::Event::MouseButtonPressed) {
      Pos tmp(evt.mouseButton.x, evt.mouseButton.y);
      switch (checkEvent(tmp)) {
          case START:
              myEvt.type = RESET_WINNER;
              throw myEvt;
          case EXIT:
              myEvt.type = EXIT_EVT;
              throw myEvt;
          case MENU_MAIN:
              setBtnMenu();
              m_lstMusic.at(MUSIC)->setVolume(m_volume);
              m_menu = MAINMENU;
              myEvt.type = RESET_GAME;
              m_player1->disableAI();
              m_player2->disableAI();
              throw myEvt;
          case SOUND_MUTE:
              m_muted = !m_muted;
              if (m_muted)
                  m_lstMusic.at(MUSIC)->stop();
              else
                  m_lstMusic.at(MUSIC)->play();
              break;
          case SOUND_PLUS:
              if (m_volume < 100) {
                  m_volume += 10;
                  m_lstMusic.at(MUSIC)->setVolume(m_volume * GAME_VOLUME / 100);
              }
              break;
          case SOUND_MOIN:
              if (m_volume > 0) {
                  m_volume -= 10;
                  m_lstMusic.at(MUSIC)->setVolume(m_volume * GAME_VOLUME / 100);
              }
              break;
          default:;
      };
  }
  drawWinner(winner);
}

int		View::checkEvent(const Pos &event) {
    for ( auto it = m_btn.begin();it != m_btn.end(); it++)
    {
        if (it->click(event.x , event.y)) {
            return it->getClickVal();
        }
    }
    return -1;
}

void View::drawBtn()
{
    for ( auto it = m_btn.begin();it != m_btn.end(); it++)
        it->draw(*m_window);
}

void		View::execMenu(const sf::Event &evt, config &conf)
{
  myEvent	myEvt;

  if (evt.type == sf::Event::MouseButtonPressed) {
      Pos tmp(evt.mouseButton.x, evt.mouseButton.y);
      switch (checkEvent(tmp)) {
          case EXIT:
              myEvt.type = EXIT_EVT;
              throw myEvt;
          case START:
              this->m_btn.clear();
              myEvt.type = RESET_GAME;
              m_menu = GAME;
              m_lstMusic.at(MUSIC)->setVolume(m_volume * GAME_VOLUME / 100);
              throw myEvt;
          case DOUBLE_3:
              conf.double3 = !conf.double3;
              break;
          case BROKEN_5:
              conf.broken5 = !conf.broken5;
              break;
          case SOUND_MUTE:
              m_muted = !m_muted;
              if (m_muted)
                  m_lstMusic.at(MUSIC)->stop();
              else
                  m_lstMusic.at(MUSIC)->play();
              break;
          case SOUND_PLUS:
              if (m_volume < 100) {
                  m_volume += 10;
                  m_lstMusic.at(MUSIC)->setVolume(m_volume);
              }
              break;
          case SOUND_MOIN:
              if (m_volume > 0) {
                  m_volume -= 10;
                  m_lstMusic.at(MUSIC)->setVolume(m_volume);
              }
              break;
          case PLAYER1_IA:
              m_player1->changeAI();
              break;
          case PLAYER2_IA:
              m_player2->changeAI();
              break;
          default:;
      };
  }
  drawMenu(conf);
}

int		View::showSplash(const config &conf)
{
  sf::Event	evt;
  sf::Music	sound;
  sf::Texture	texture[112];
  int		u;
  int		time;

  sound.openFromFile("ressources/sound_splash.ogg");
  for (int i = 0; i < 112; i++)
    texture[i].loadFromFile("ressources/splash/lapin_" + std::to_string(i) + ".png");
  u = 0;
  time = 0;
  sound.play();

  while (u < 112)
    {
      if (m_window->pollEvent(evt)) {
          if ((evt.type == sf::Event::KeyPressed || evt.type == sf::Event::MouseButtonPressed))
              break;
          else if (evt.type == sf::Event::Closed)
              return 1;
      }
      if (time <= 0)
	{
	  time = 700;
	  m_window->clear();
	  sf::Sprite sprite(texture[u]);
	  sprite.setScale(SCREEN_WIDTH / 1280, SCREEN_HEIGHT / 720);
	  m_window->draw(sprite);
	  m_window->display();
	  u++;
	}
      time--;
      usleep(100);
    }
  sound.stop();
  m_lstMusic.at(MUSIC)->play();
  m_window->clear();
  drawHeader(1, m_player1);
  drawMap();
  drawMenu(conf);
  m_window->display();
    return 0;
}

void		View::updateGame(const unsigned int round, const Player *pl)
{
  m_window->clear();
  drawHeader(round, pl);
  drawMap();
}

void		View::show() const
{
  m_window->display();
}

void		View::loopView(const unsigned int round, const Player *pl,
			       const Player *winner, config &conf)
{
  sf::Event	evt;
    myEvent	myEvt;


  while (m_window->waitEvent(evt))
    {
        if (evt.type == sf::Event::Closed)
        {
            myEvt.type = EXIT_EVT;
            throw myEvt;
        }
      updateGame(round, pl);
      if (winner != NULL) {
          setBtnPause();
          execWinner(evt, winner);
      }
      else if (m_menu == GAME)
	{
	  if (evt.type == sf::Event::MouseButtonPressed)
	    dropStone(evt, pl);
	  else if (evt.type == sf::Event::KeyPressed && (evt.key.code == sf::Keyboard::Escape))
	    m_menu = PAUSE;
	  else
	    moveStone(pl);
	}
      else if (m_menu == PAUSE) {
          setBtnPause();
          execPause(evt, round, pl);
      }
      else {
          execMenu(evt, conf);
      }
      show();
    }
}

void		View::playSound(const int sound, const bool disableAll)
{
  if (!m_muted)
    {
      if (disableAll)
	for(int i = 1; i < NUM_MUSIC; i++)
	  m_lstMusic.at(i)->stop();
      m_lstMusic.at(sound)->play();
    }
}

void		View::drawRectangle(const sf::Vector2f &pos, const sf::Vector2f &size,
				    const sf::Color &color) const
{
  sf::RectangleShape rec(size);

  rec.setFillColor(color);
  rec.move(pos);
  m_window->draw(rec);
}

void			View::printText(const std::string &str,
					const sf::Vector2f &pos, const size_t size,
					const sf::Color &color) const
{
  sf::Text		text;

  text.setCharacterSize(size);
  text.setColor(color);
  text.setString(str);
  text.move(pos.x, pos.y);
  text.setFont(m_font);
  m_window->draw(text);
}

void			View::drawPlayer(const Player *pl, const int x, const int y,
					 const int alpha = 255) const
{
  if (pl->getColor() == WHITE)
    drawSprite(m_lstTexture.at(TEX_WHITESTONE), x, y, alpha);
  else
    drawSprite(m_lstTexture.at(TEX_BLACKSTONE), x, y, alpha);
}

void			View::drawSprite(const sf::Texture *texture,
					 const int x, const int y,
					 const int alpha = 255) const
{
  sf::Vector2u		size;
  sf::Sprite		sprite;
  double		coeffx;
  double		coeffy;

  size = texture->getSize();
  sprite.setTexture(*texture);
  coeffx = 768 / size.x;
  coeffy = 768 / size.y;
  sprite.setScale(0.05 * coeffx, 0.05 * coeffy);
  sprite.move(x, y);
  sprite.setColor(sf::Color(255, 255, 255, alpha));
  m_window->draw(sprite);
}

void			View::drawMap() const
{
  sf::Vector2u		size;
  sf::Sprite		sprite;

  size = m_lstTexture.at(TEX_BACKGROUND)->getSize();
  sprite.setTexture(*m_lstTexture.at(TEX_BACKGROUND));
  sprite.move(250, 60);
  sprite.setScale((double)WIDTH / size.x, (double)(HEIGHT) / size.y);
  m_window->draw(sprite);
  for (int y = 0; y < 19; y++)
    for (int x = 0; x < 19; x++)
      {
	int tmpx = x + MAP_MIN;
	int tmpy = y + MAP_MIN;
	if (m_map[tmpy][tmpx] == WHITE)
	  drawSprite(m_lstTexture.at(TEX_WHITESTONE), POS_MAP_X + x * SCALE_MAP,
		     POS_MAP_Y + y * SCALE_MAP);
	else if (m_map[tmpy][tmpx] == BLACK)
	  drawSprite(m_lstTexture.at(TEX_BLACKSTONE), POS_MAP_X + x * SCALE_MAP,
		     POS_MAP_Y + y * SCALE_MAP);
      }
}

void			View::drawHeader(const unsigned int round, const Player *player)
{
  std::ostringstream	str;
  sf::Sprite		bg(*m_lstTexture.at(TEX_FOND));

  bg.move(-150, 0);
  m_window->draw(bg);
  str << "Match: " << round;
  printText(str.str(), sf::Vector2f(400, 20), 25, sf::Color::Red);
  printText("Player: " + player->getName(), sf::Vector2f(750, 20), 25, sf::Color::Red);
  drawRectangle(sf::Vector2f(35, 90), sf::Vector2f(190, 290), sf::Color(100, 100, 100));
  printText(m_player1->getName(), sf::Vector2f(85, 100), 25, sf::Color::Red);
  int val = m_player1->getStonesTaken();
  sf::Texture *tmp1, *tmp2, *tmp;
  tmp1 = m_lstTexture.at(TEX_BLACKSTONE);
  tmp2 = m_lstTexture.at(TEX_WHITESTONE);
  if (m_player1->getColor() == BLACK)
    {
      tmp = tmp2;
      tmp2 = tmp1;
      tmp1 = tmp;
    }    
  for (int i = 0; i < val && i < 10; i++)
    drawSprite(tmp1, 80 + (i % 2) * 60, 150 + (i / 2) * 45);
  printText("WIN : " + std::to_string(m_player1->getWins()),
	    sf::Vector2f(85, 500), 30, sf::Color::Red);
  drawRectangle(sf::Vector2f(1080, 90), sf::Vector2f(190, 290), sf::Color(100, 100, 100));
  printText(m_player2->getName(), sf::Vector2f(1135, 100), 25, sf::Color::Red);
  val = m_player2->getStonesTaken();
  for (int i = 0; i < val && i < 10; i++)
    drawSprite(tmp2, 1125 + (i % 2) * 60, 150 + (i / 2) * 45);
  printText("WIN : " + std::to_string(m_player2->getWins()),
	    sf::Vector2f(1135, 500), 30, sf::Color::Red);
  
  sf::Sprite  imgPlayer;
  if (player == m_player1)
    imgPlayer.setPosition(60, 650);
  else
    imgPlayer.setPosition(1110, 650);
  if (player->getColor() == WHITE)
    imgPlayer.setTexture(*m_lstTexture.at(TEX_PLAYERWHITE));
  else
    imgPlayer.setTexture(*m_lstTexture.at(TEX_PLAYERBLACK));
  imgPlayer.scale(0.4, 0.4);
  m_window->draw(imgPlayer);
}

void			View::drawWinner(const Player *winner)
{
  std::string color = "BLANC";
  if (winner->getColor() == BLACK)
    color = "NOIR";
  drawRectangle(sf::Vector2f(0, 0), sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT),
		sf::Color(0, 0, 0, 200));
  printText(winner->getName() + "(" + color + ")" + " is WINNER !!",
	    sf::Vector2f(320, 200), 60, sf::Color::Red);

    drawBtn();

  printText("Restart", sf::Vector2f(600, 310), 24, sf::Color::Blue);
  printText("Main menu", sf::Vector2f(585, 410), 24, sf::Color::Blue);
  printText("Quitter", sf::Vector2f(600, 510), 24, sf::Color::Blue);
}

void			View::drawPause(const unsigned int round, const Player *player)
{
  sf::Sprite	box_off;
  sf::Sprite	box_on;
  sf::Sprite	selected;

  box_off.setTexture(*m_lstTexture.at(TEX_UNCHECKED));
  box_on.setTexture(*m_lstTexture.at(TEX_CHECKED));
  box_off.scale(0.133, 0.133);
  box_on.scale(0.08, 0.08);

  drawRectangle(sf::Vector2f(0, 0), sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT),
		sf::Color(0, 0, 0, 200));

    drawBtn();

    drawRectangle(sf::Vector2f(350, 770), sf::Vector2f(130, 40), sf::Color(190, 190, 190, 255));
    drawRectangle(sf::Vector2f(820, 770), sf::Vector2f(130, 40), sf::Color(190, 190, 190, 255));

    printText("Match : " + std::to_string(round), sf::Vector2f(500, 150), 35, sf::Color::Red);
    printText("Tour:" + player->getName(), sf::Vector2f(500, 200), 35, sf::Color::Red);
    printText("Resume", sf::Vector2f(600, 310), 24, sf::Color::Blue);
    printText("Main menu", sf::Vector2f(585, 410), 24, sf::Color::Blue);
    printText("Quitter", sf::Vector2f(600, 510), 24, sf::Color::Blue);


  drawRectangle(sf::Vector2f(300, 785), sf::Vector2f(20, 7), sf::Color::Red);
  drawRectangle(sf::Vector2f(510, 785), sf::Vector2f(20, 7), sf::Color::Red);
  drawRectangle(sf::Vector2f(517, 780), sf::Vector2f(7, 20), sf::Color::Red);



    printText("Volume :", sf::Vector2f(360, 730), 26, sf::Color::Red);
    printText(std::to_string((int)m_volume),
              sf::Vector2f(380, 780), 22, sf::Color::Blue);

  printText("Sound Mute", sf::Vector2f(830, 780), 18, sf::Color::Blue);
  if (m_muted)
    selected = box_on;
  else
    selected = box_off;
  selected.setPosition(1020, 770);
  m_window->draw(selected);
}

void   		View::drawMenu(const config &conf)
{
  sf::Sprite	box_off;
  sf::Sprite	box_on;
  sf::Sprite	selected;
  sf::Sprite	logo;

  logo.setTexture(*m_lstTexture.at(TEX_LOGO));
  box_off.setTexture(*m_lstTexture.at(TEX_UNCHECKED));
  box_on.setTexture(*m_lstTexture.at(TEX_CHECKED));
  box_off.scale(0.133, 0.133);
  box_on.scale(0.08, 0.08);

  drawRectangle(sf::Vector2f(0, 0), sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT),
		sf::Color(0, 0, 0, 200));

  logo.setPosition(320, 60);
  logo.scale(0.5, 0.5);
  m_window->draw(logo);
  drawRectangle(sf::Vector2f(SCREEN_WIDTH / 2 - 150, 300),
		sf::Vector2f(300, 50), sf::Color(190, 190, 190, 220));
  printText("Play", sf::Vector2f(620, 310), 24, sf::Color::Blue);

  drawRectangle(sf::Vector2f(SCREEN_WIDTH / 2 - 150, 400),
		sf::Vector2f(300, 50), sf::Color(190, 190, 190, 220));
  printText("Quitter Gomusku", sf::Vector2f(565, 410), 24, sf::Color::Blue);

  drawRectangle(sf::Vector2f(250, 600), sf::Vector2f(130, 40), sf::Color(190, 190, 190, 190));
  printText("Double trois", sf::Vector2f(260, 610), 20, sf::Color::Blue);
  if (conf.double3)
    selected = box_on;
  else
    selected = box_off;
  selected.setPosition(450, 600);
  m_window->draw(selected);
  
  drawRectangle(sf::Vector2f(250, 670), sf::Vector2f(130, 40), sf::Color(190, 190, 190, 190));
  printText("Cinq cassable", sf::Vector2f(260, 680), 18, sf::Color::Blue);
  if (conf.broken5)
    selected = box_on;
  else
    selected = box_off;
  selected.setPosition(450, 670);
  m_window->draw(selected);

  drawRectangle(sf::Vector2f(750, 600), sf::Vector2f(130, 40), sf::Color(190, 190, 190, 190));
  printText("Joueur 1 IA", sf::Vector2f(760, 610), 18, sf::Color::Blue);
  if (m_player1->getAI())
    selected = box_on;
  else
    selected = box_off;
  selected.setPosition(950, 600);
  m_window->draw(selected);

  drawRectangle(sf::Vector2f(750, 670), sf::Vector2f(130, 40), sf::Color(190, 190, 190, 190));
  printText("Joueur 2 IA", sf::Vector2f(760, 680), 18, sf::Color::Blue);
  if (m_player2->getAI())
    selected = box_on;
  else
    selected = box_off;
  selected.setPosition(950, 670);
  m_window->draw(selected);

  printText("Volume :", sf::Vector2f(360, 730), 26, sf::Color::Red);
  drawRectangle(sf::Vector2f(350, 770), sf::Vector2f(130, 40), sf::Color(190, 190, 190, 190));
  printText(std::to_string((int)m_volume),
	    sf::Vector2f(380, 780), 22, sf::Color::Blue);
  drawRectangle(sf::Vector2f(290, 770), sf::Vector2f(40, 40), sf::Color(190, 190, 190, 190));
  drawRectangle(sf::Vector2f(300, 785), sf::Vector2f(20, 7), sf::Color::Red);
  drawRectangle(sf::Vector2f(500, 770), sf::Vector2f(40, 40), sf::Color(190, 190, 190, 190));
  drawRectangle(sf::Vector2f(510, 785), sf::Vector2f(20, 7), sf::Color::Red);
  drawRectangle(sf::Vector2f(517, 780), sf::Vector2f(7, 20), sf::Color::Red);

  drawRectangle(sf::Vector2f(820, 770), sf::Vector2f(130, 40), sf::Color(190, 190, 190, 190));
  printText("Sound Mute", sf::Vector2f(830, 780), 18, sf::Color::Blue);
  if (m_muted)
    selected = box_on;
  else
    selected = box_off;
  selected.setPosition(1020, 770);
  m_window->draw(selected);
}
