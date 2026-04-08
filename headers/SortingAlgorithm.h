//
// Created by BSI on 08/04/2026.
//

#ifndef SORTINGVISUALIZER_SORTINGALGORITHM_H
#define SORTINGVISUALIZER_SORTINGALGORITHM_H
#pragma once
#include <SFML/Graphics.hpp>
#include "Rectangle.h"



class SortingAlgorithm {
public:
  virtual ~SortingAlgorithm() = default;
  virtual void step(std::vector<Rectangle>& rectangles) = 0;
  virtual void reset() = 0;
  virtual bool isSort() = 0;
};

class BubbleSort : public SortingAlgorithm {
private:
  int i = 0, j = 0;
  bool isSorted = false;
public:
  void step(std::vector<Rectangle>& rectangles) override {
    if (isSorted || rectangles.empty()) return;
    int n = rectangles.size();
    rectangles[j].setColor(sf::Color::Red);
    rectangles[j + 1].setColor(sf::Color::Red);
    if (rectangles[j].getHeight() > rectangles[j + 1].getHeight()) {
      std::swap(rectangles[j], rectangles[j + 1]);
    }


    j++;

    if (j >= n - i - 1) {
      j = 0;
      i++;
    }

    if (i >= n - 1) {
      isSorted = true;
    }
  }
  void reset() override{
    i = 0;
    j = 0;
    isSorted = false;
  }
  bool isSort() override {
    return isSorted;
  }
};

class SelectionSort : public SortingAlgorithm {
private:
  int i = 0, j = 0, minIndex = 0;
  bool isSorted = false;
public:
  void step(std::vector<Rectangle>& rectangles) override {
    if (isSorted || rectangles.empty()) return;
    int n = rectangles.size();
    rectangles[j].setColor(sf::Color::Red);
    rectangles[j + 1].setColor(sf::Color::Red);
    if (rectangles[j].getHeight() < rectangles[minIndex].getHeight()) {
    minIndex = j;
    }

    j++;

    if (j >= n) {
    std::swap(rectangles[i], rectangles[minIndex]);
    i++;
    j = i;
    minIndex = i;
    }

    if (i >= n - 1) {
    isSorted = true;
    }
  }
  void reset() override {
    i = 0;
    j = 0;
    minIndex = 0;
    isSorted = false;
  }
  bool isSort() override {
    return isSorted;
  }
};

class InsertionSort : public SortingAlgorithm {
private:
  int i = 1;
  int j = 0;
  bool isSorted = false;

public:
  void step(std::vector<Rectangle>& rectangles) override {
    if (isSorted || rectangles.empty()) return;
    int n = rectangles.size();

    if (j >= 0 && rectangles[j].getHeight() > rectangles[j + 1].getHeight()) {
      rectangles[j].setColor(sf::Color::Red);
      rectangles[j + 1].setColor(sf::Color::Red);
      std::swap(rectangles[j], rectangles[j + 1]);
      j--;
    }
    else {
      i++;
      j = i - 1;
    }

    if (i >= n) {
      isSorted = true;
    }
  }

  void reset() override {
    i = 1;
    j = 0;
    isSorted = false;
  }
  bool isSort() override {
    return isSorted;
  }
};

class MergeSort : public SortingAlgorithm {
private:
    bool isSorted = false;
    int currentSize = 1;
    int leftStart = 0;

    // State variables for the current merge
    int mergeLeft = 0;
    int mergeMid = 0;
    int mergeRight = 0;
    int i = 0, j = 0, k = 0;
    std::vector<Rectangle> temp;

    // State machine tracker
    enum MergeState {
        INIT_MERGE,
        MERGING,
        COPYING_BACK
    };
    MergeState state = INIT_MERGE;

public:
    void step(std::vector<Rectangle>& rectangles) override {
        if (isSorted || rectangles.empty()) return;
        int n = rectangles.size();

        if (currentSize >= n) {
            isSorted = true;
            return;
        }

        switch(state) {
            case INIT_MERGE:
                mergeLeft = leftStart;
                mergeMid = std::min(leftStart + currentSize - 1, n - 1);
                mergeRight = std::min(leftStart + 2 * currentSize - 1, n - 1);

                if (mergeMid >= mergeRight) {
                    advanceChunk(n);
                    break;
                }

                temp.resize(mergeRight - mergeLeft + 1);
                i = mergeLeft;
                j = mergeMid + 1;
                k = 0;
                state = MERGING;
                break;

            case MERGING:
                rectangles[i].setColor(sf::Color::Red);
                rectangles[j].setColor(sf::Color::Red);

                if (rectangles[i].getHeight() <= rectangles[j].getHeight()) {
                    temp[k++] = rectangles[i++];
                } else {
                    temp[k++] = rectangles[j++];
                }
                if (i > mergeMid) {
                    while (j <= mergeRight) temp[k++] = rectangles[j++];
                    state = COPYING_BACK;
                    k = 0;
                } else if (j > mergeRight) {
                    while (i <= mergeMid) temp[k++] = rectangles[i++];
                    state = COPYING_BACK;
                    k = 0;
                }
                break;

            case COPYING_BACK:
                rectangles[mergeLeft + k] = temp[k];

                // Highlight the element being written back
                rectangles[mergeLeft + k].setColor(sf::Color::Green);

                k++;

                if (k >= temp.size()) {
                    advanceChunk(n);
                }
                break;
        }
    }

    void reset() override {
        currentSize = 1;
        leftStart = 0;
        isSorted = false;
        state = INIT_MERGE;
        temp.clear();
    }

    bool isSort() override {
        return isSorted;
    }

private:
    void advanceChunk(int n) {
        leftStart += 2 * currentSize;
        if (leftStart >= n - 1) {
            currentSize *= 2;
            leftStart = 0;
        }
        state = INIT_MERGE;
    }
};

class QuickSort : public SortingAlgorithm {
private:
        bool isSorted = false;
        std::vector<std::pair<int, int>> stack; // Stack to hold subarray indices
        int pivotIndex = -1;
        int i = -1, j = -1;
        enum QuickState {
          INIT_PARTITION,
          PARTITIONING,
          SWAPPING,
          PARTITION_DONE
        };
        QuickState state = INIT_PARTITION;
public:
    void step(std::vector<Rectangle>& rectangles) override {
        if (isSorted || rectangles.empty()) return;

        if (stack.empty()) {
            stack.push_back({0, static_cast<int>(rectangles.size() - 1)});
        }

        auto [low, high] = stack.back();

        switch(state) {
            case INIT_PARTITION:
                pivotIndex = high;
                i = low - 1;
                j = low;
                state = PARTITIONING;
                break;

            case PARTITIONING:
                if (j < high) {
                    rectangles[j].setColor(sf::Color::Red);
                    rectangles[pivotIndex].setColor(sf::Color::Green);
                    if (rectangles[j].getHeight() < rectangles[pivotIndex].getHeight()) {
                        i++;
                        std::swap(rectangles[i], rectangles[j]);
                    }
                    j++;
                } else {
                    state = SWAPPING;
                }
                break;

            case SWAPPING:
                std::swap(rectangles[i + 1], rectangles[pivotIndex]);
                state = PARTITION_DONE;
                break;

            case PARTITION_DONE:
                int pi = i + 1;
                stack.pop_back();
                if (pi - 1 > low) stack.push_back({low, pi - 1});
                if (pi + 1 < high) stack.push_back({pi + 1, high});
                if (stack.empty()) isSorted = true;
                state = INIT_PARTITION;
                break;
        }
    }

    void reset() override {
        isSorted = false;
        stack.clear();
        pivotIndex = -1;
        i = -1;
        j = -1;
        state = INIT_PARTITION;
    }

    bool isSort() override {
        return isSorted;
    }

};

#endif //SORTINGVISUALIZER_SORTINGALGORITHM_H
