#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <random>
#include <memory>
#include <string>
#include "headers/Rectangle.h"
#include "headers/Rectangles.h"
#include "headers/SortingAlgorithm.h"

std::unique_ptr<SortingAlgorithm> createAlgorithm(const std::string& type) {
  if (type == "bubble") {
    return std::make_unique<BubbleSort>();
  } else if (type == "merge") {
    return std::make_unique<MergeSort>();
  }
  else if (type == "selection") {
    return std::make_unique<SelectionSort>();
  }
  else if (type == "insertion") {
    return std::make_unique<InsertionSort>();
  }
  else if (type == "quick") {
    return std::make_unique<QuickSort>();
  }
  return std::make_unique<MergeSort>();
};

int main(int argc, char* argv[] ) {
    std::vector<std::string> all_args(argv, argv + argc);



    sf::RenderWindow window(sf::VideoMode({800, 600}), "Sorting Visualizer");

    window.setFramerateLimit(60);

    int numBars = 100;
    float windowWidth = 800.0f;
    float windowHeight = 600.0f;
    std::unique_ptr<SortingAlgorithm> algorithm = std::make_unique<MergeSort>();
    if (argc > 1) {
      algorithm = createAlgorithm(all_args[1]);
      if (argc > 2) {
        numBars = std::stoi(all_args[2]);
      }
    }
    float barWidth = windowWidth / numBars;
    std::vector<Rectangle> rawRectangles;
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> dist(10.0f, windowHeight - 10.0f);

    for (int i = 0; i < numBars; ++i) {
        Rectangle rect(barWidth, dist(gen), sf::Color::White);
        rawRectangles.push_back(rect);
    }

    Rectangles rectManager(rawRectangles);


    while (window.isOpen()) {

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
              if (keyPressed->code == sf::Keyboard::Key::R) {

                rawRectangles.clear();

                for (int i = 0; i < numBars; ++i) {
                  Rectangle rect(barWidth - 1.0f, dist(gen), sf::Color::White);
                  rawRectangles.push_back(rect);
                }

                rectManager = Rectangles(rawRectangles);

                algorithm = createAlgorithm(all_args[1]);
              }
            }
        }

        rectManager.resetColors();

        if (!algorithm->isSort()) {
            rectManager.step(*algorithm);
        }

        window.clear(sf::Color::Black);


        rectManager.updatePositions(windowWidth, windowHeight);

        rectManager.draw(window);

        window.display();
    }

    return 0;
}