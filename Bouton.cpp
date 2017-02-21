//
// Created by pavot_m on 06/12/16.
//


#include <iostream>
#include "Bouton.hpp"
#include "View.hpp"



Bouton::Bouton(sf::Vector2f pos,
               sf::Vector2f size,
               btnVal val, sf::Color color) {

    clickVal = val;

    sizeX = size.x;
    sizeY = size.y;

    topL = *new std::pair<size_t , size_t >(pos.x, pos.y);
    topR = *new std::pair<size_t , size_t >(pos.x + size.x, pos.y);

    botL = *new std::pair<size_t , size_t >(pos.x, pos.y + size.y);
    botR = *new std::pair<size_t , size_t >(pos.x + size.x, pos.y + size.y);

    this->color = color;
}

Bouton::~Bouton() {

}


bool Bouton::click(float x, float y) {
    return  (x > topL.first && y > topL.second && x < botR.first && y < botR.second);
}

btnVal Bouton::getClickVal() {
    return clickVal;
}

bool Bouton::draw(sf::RenderWindow &win) {
    (void)win;
    sf::RectangleShape rec(sf::Vector2<float>(sizeX, sizeY));
    rec.setFillColor(color);
    rec.move(sf::Vector2<float>(topL.first, topL.second));
    win.draw(rec);
    return false;
}
