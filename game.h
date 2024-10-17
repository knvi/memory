#ifndef GAME_H
#define GAME_H

#include <limits>
#include "board.h"
#include "utils.h"

class Game
{
public:
    Game() : board(2, 2), player1Score(0), player2Score(0)
    {
        getBoardDimensions();
    }

    void start()
    {
        srand(time(0));

        board.initialize();

        player1Score = 0;
        player2Score = 0;
        player1Turn = true;

        petla_gry();
    }

private:
    Board board;
    int player1Score;
    int player2Score;
    bool player1Turn;

    void getBoardDimensions()
    {
        int x, y; // wymiary planszy
        while (true)
        {
            std::cout << "Podaj liczbe wierszy planszy (liczba od 2 do 20): ";
            while (!(std::cin >> x) || x < 2 || x > 20)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Nieprawidlowa liczba wierszy. Sprobuj ponownie." << std::endl;
            }

            std::cout << "Podaj liczbe kolumn planszy (liczba od 2 do 20): ";
            while (!(std::cin >> y) || y < 2 || y > 20)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Nieprawidlowa liczba kolumn. Sprobuj ponownie." << std::endl;
            }

            if ((x * y) % 2 != 0)
            {
                std::cout << "Iloczyn wierszy i kolumn musi byc parzysty. Sprobuj ponownie." << std::endl;
                continue;
            }
            else
            {
                break;
            }
        }

        board.setSize(x, y);
    }

    bool playerMove()
    {
        int x1, y1, x2, y2;

        std::cout << "Podaj koordynaty pierwszej karty (rzad i kolumne oddzielone spacja): ";
        while (true)
        {
            getValidNumbers(x1, y1);

            if (board.checkMove(x1, y1))
            {
                break;
            }

            std::cout << "Nieprawidlowe koordynaty. Sprobuj ponownie." << std::endl;
        }

        board.revealed[x1][y1] = true;
        board.display();

        while (true)
        {
            std::cout << "Podaj koordynaty drugiej karty (rzad i kolumne oddzielone spacja): ";
            getValidNumbers(x2, y2);
            if (board.checkMove(x2, y2))
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

    void koniec_gry()
    {
        std::cout << "Koniec gry!" << std::endl;
        std::cout << "Wynik Gracza 1: " << player1Score << " pary" << std::endl;
        std::cout << "Wynik Gracza 2: " << player2Score << " pary" << std::endl;

        int result = (player1Score > player2Score) - (player1Score < player2Score);

        switch (result)
        {
        case 1:
            std::cout << "Gracz 1 wygrywa!" << std::endl;
            break;
        case -1:
            std::cout << "Gracz 2 wygrywa!" << std::endl;
            break;
        case 0:
            std::cout << "Remis!" << std::endl;
            break;
        }
    }

    void petla_gry()
    {
        std::cout << "Zaczynamy gre!" << std::endl;

        int totalPairs = board.rows * board.columns / 2;
        int revealedPairs = 0;

        while (revealedPairs < totalPairs)
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

            revealedPairs = player1Score + player2Score;
        }

        koniec_gry();
    }
};

#endif