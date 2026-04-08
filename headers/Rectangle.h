//
// Created by BSI on 08/04/2026.
//
#pragma once

#ifndef SORTINGVISUALIZER_RECTANGLE_H
#define SORTINGVISUALIZER_RECTANGLE_H
#include <SFML/Graphics.hpp>


class Rectangle {
private:
  float width, height ;
  sf::Color color = sf::Color::White;
public:
  sf::RectangleShape shape;
  Rectangle() = default;
  Rectangle(float w , float h , sf::Color c): width(w), height(h) , color(c) {
    shape.setSize({w,h});
    shape.setOutlineThickness(-1.0f); // Negative thickness grows inward
    shape.setOutlineColor(sf::Color::Black);
    shape.setFillColor(c);
  }
  float getWidth(){return width;}
  float getHeight(){return height;}
  sf::Color getColor(){return color;}
  void setColor(sf::Color c) {
    color = c;
    shape.setFillColor(c);
  }
  void update() {

  }
  void draw(sf::RenderWindow& window) {
    window.draw(shape);
  }
};



#endif //SORTINGVISUALIZER_RECTANGLE_H
