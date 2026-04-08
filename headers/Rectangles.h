//
// Created by BSI on 08/04/2026.
//

#ifndef SORTINGVISUALIZER_RECTANGLES_H
#define SORTINGVISUALIZER_RECTANGLES_H
#include "Rectangle.h"
#include "SortingAlgorithm.h"
#include <vector>


class Rectangles {
private:
  std::vector<Rectangle> rectangles;
public:
  Rectangles() = default;
  Rectangles(std::vector<Rectangle> rects) : rectangles(rects) {}
  void addRectangle(Rectangle r) {
    rectangles.push_back(r);
  }
  void step(SortingAlgorithm& algorithm) {
    algorithm.step(rectangles);
  }
  void updatePositions(float windowWidth, float windowHeight) {
        int n = rectangles.size();
        float barWidth = windowWidth / n;
        for (int i = 0; i < n; ++i) {
          rectangles[i].update();
          sf::Vector2f position(i * barWidth, windowHeight - rectangles[i].getHeight());
          rectangles[i].shape.setPosition(position);
        }
  }
  void resetColors() {
    for (int i = 0; i < rectangles.size(); i++) {
      rectangles[i].setColor(sf::Color::White);
    }
  }
  void draw(sf::RenderWindow& window) {
    for (Rectangle r : rectangles) {
      r.draw(window);
    }
  }
  void update() {
    for (Rectangle r : rectangles) {
      r.update();
    }
  }
};



#endif //SORTINGVISUALIZER_RECTANGLES_H
