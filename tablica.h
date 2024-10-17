#ifndef TABLICA_H
#define TABLICA_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>

class Plansza {
public:
    int rzedy, kolumny;
    std::vector<std::vector<char>> plansza;
    std::vector<std::vector<bool>> odkryte;

    Plansza(int rzedy, int kolumny) : rzedy(rzedy), kolumny(kolumny) {
        plansza = std::vector<std::vector<char>>(rzedy, std::vector<char>(kolumny));
        odkryte = std::vector<std::vector<bool>>(rzedy, std::vector<bool>(kolumny, false));
    }

    void przygotowanie() {
        std::vector<char> karty;
        for (char c = 'A'; c < 'A' + rzedy * kolumny / 2; ++c) {
            karty.push_back(c);
            karty.push_back(c);
        }
        random_shuffle(karty.begin(), karty.end());

        int index = 0;
        for (int i = 0; i < rzedy; ++i) {
            for (int j = 0; j < kolumny; ++j) {
                plansza[i][j] = karty[index++];
                odkryte[i][j] = false;
            }
        }
    }

    void wyswietl() {
        std::cout << "  ";
        for (int i = 0; i < kolumny; ++i) {
            std::cout << i << " ";
        }

        std::cout << std::endl;

        for (int i = 0; i < rzedy; ++i) {
            std::cout << i << " ";
            for (int j = 0; j < kolumny; ++j) {
                if (odkryte[i][j]) {
                    std::cout << plansza[i][j] << " ";
                } else {
                    std::cout << "* ";
                }
            }
            std::cout << std::endl;
        }
    }

    bool sprawdzRuch(int x, int y) {
        return x >= 0 && x < rzedy && y >= 0 && y < kolumny && !odkryte[x][y];
    }

    void ustawRozmiar(int x, int y) {
        rzedy = x;
        kolumny = y;
        plansza.resize(rzedy, std::vector<char>(kolumny));
        odkryte.resize(rzedy, std::vector<bool>(kolumny, false));
    }
};

#endif