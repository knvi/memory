#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>

class Board {
public:
    int rows, cols;
    std::vector<std::vector<char>> board;
    std::vector<std::vector<bool>> revealed;

    Board(int rows, int cols) : rows(rows), cols(cols) {
        board = std::vector<std::vector<char>>(rows, std::vector<char>(cols));
        revealed = std::vector<std::vector<bool>>(rows, std::vector<bool>(cols, false));
    }

    void initialize() {
        std::vector<char> cards;
        for (char c = 'A'; c < 'A' + rows * cols / 2; ++c) {
            cards.push_back(c);
            cards.push_back(c);
        }
        random_shuffle(cards.begin(), cards.end());

        int index = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                board[i][j] = cards[index++];
                revealed[i][j] = false;
            }
        }
    }

    void display() {
        std::cout << "  ";
        for (int i = 0; i < cols; ++i) {
            std::cout << i << " ";
        }

        std::cout << std::endl;

        for (int i = 0; i < rows; ++i) {
            std::cout << i << " ";
            for (int j = 0; j < cols; ++j) {
                if (revealed[i][j]) {
                    std::cout << board[i][j] << " ";
                } else {
                    std::cout << "* ";
                }
            }
            std::cout << std::endl;
        }
    }

    bool isValidMove(int x, int y) {
        return x >= 0 && x < rows && y >= 0 && y < cols && !revealed[x][y];
    }

    void setSize(int x, int y) {
        rows = x;
        cols = y;
        board.resize(rows, std::vector<char>(cols));
        revealed.resize(rows, std::vector<bool>(cols, false));
    }
};

#endif