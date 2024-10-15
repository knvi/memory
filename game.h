#ifndef GAME_H
#define GAME_H

#include "board.h"

class Game
{
public:
    Game() : board(2, 2), player1Score(0), player2Score(0) {
        getBoardDimensions();
    }

    void getBoardDimensions()
    {
        std::cout << "Podaj liczbe wierszy i kolumn planszy (parzyste liczby od 2 do 20): ";
        int x, y; // wymiary planszy
        std::cin >> x >> y;
        while (x < 2 || x > 20 || y < 2 || y > 20 || x % 2 != 0 || y % 2 != 0)
        {
            std::cout << "Nieprawidlowe wymiary planszy. Sprobuj ponownie." << std::endl;
            std::cout << "Podaj liczbe wierszy i kolumn planszy (parzyste liczby od 2 do 20): ";
            std::cin >> x >> y;
        }

        board.setSize(x, y);
    }

    bool playerMove()
    {
        int x1, y1, x2, y2;

        while (true)
        {
            std::cout << "Podaj koordynaty pierwszej karty (rzad i kolumne oddzielone spacja): ";
            std::cin >> x1 >> y1;
            if (board.isValidMove(x1, y1))
                break;
            std::cout << "Nieprawidlowy ruch. Sprobuj ponownie." << std::endl;
        }

        board.revealed[x1][y1] = true;
        board.display();

        while (true)
        {
            std::cout << "Podaj koordynaty drugiej karty (rzad i kolumne oddzielone spacja): ";
            std::cin >> x2 >> y2;
            if (board.isValidMove(x2, y2))
                break;
            std::cout << "Nieprawidlowy ruch. Sprobuj ponownie." << std::endl;
        }

        board.revealed[x2][y2] = true;
        board.display();

        if (board.board[x1][y1] == board.board[x2][y2])
        {
            std::cout << "Znaleziono pare!" << std::endl;
            if (player1Turn)
            {
                player1Score++;
            }
            else
            {
                player2Score++;
            }
            return true;
        }
        else
        {
            std::cout << "Brak pary." << std::endl;
            board.revealed[x1][y1] = false;
            board.revealed[x2][y2] = false;
            return false;
        }
    }

    void end_game() {
        std::cout << "Koniec gry!" << std::endl;
        std::cout << "Wynik gracza 1: " << player1Score << " pary" << std::endl;
        std::cout << "Wynik gracza 2: " << player2Score << " pary" << std::endl;

        if (player1Score > player2Score)
        {
            std::cout << "Gracz 1 wygrywa!" << std::endl;
        }
        else if (player2Score > player1Score)
        {
            std::cout << "Gracz 2 wygrywa!" << std::endl;
        }
        else
        {
            std::cout << "Remis!" << std::endl;
        }
    }

    void game_loop() {
        std::cout << "Zaczynamy gre!" << std::endl;

        int totalPairs = board.rows * board.cols / 2;

        while (player1Score + player2Score < totalPairs)
        {
            board.display();
            if (player1Turn)
            {
                std::cout << "Kolej gracza 1." << std::endl;
                if (!playerMove())
                {
                    player1Turn = false;
                }
            }
            else
            {
                std::cout << "Kolej gracza 2." << std::endl;
                if (!playerMove())
                {
                    player1Turn = true;
                }
            }
        }

        end_game();
    }

    void init()
    {
        srand(time(0));

        board.initialize();

        player1Score = 0;
        player2Score = 0;
        player1Turn = true;

        game_loop();
    }
private:
    Board board;
    int player1Score;
    int player2Score;
    bool player1Turn;
};

#endif