//
// Created by pavot_m on 06/12/16.
//

#ifndef GOMOKU_BOUTON_HPP
#define GOMOKU_BOUTON_HPP


#include <cstddef>
#include <utility>
# include	<SFML/Graphics.hpp>
# include	<SFML/Window.hpp>
# include	<SFML/Audio/Music.hpp>
#include "myEvent.hpp"

class Bouton {

    std::pair<float, float > topR;
    std::pair<float, float > topL;

    std::pair<float, float > botR;
    std::pair<float, float > botL;

    btnVal clickVal;

    float sizeX;
    float sizeY;

    sf::Color color;
public:

    Bouton(sf::Vector2f pos, sf::Vector2f size, btnVal val, sf::Color color);
    ~Bouton();

    bool click(float x, float y);
    btnVal getClickVal();
    bool draw(sf::RenderWindow &win);

};



#endif //GOMOKU_BOUTON_HPP
