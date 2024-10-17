#ifndef GRA_H
#define GRA_H

#include "tablica.h"

class Gra
{
public:
    Gra() : plansza(2, 2), wynik1(0), wynik2(0) {
        wymiaryPlanszy();
    }

    void wymiaryPlanszy()
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

        plansza.ustawRozmiar(x, y);
    }

    bool ruchGracza()
    {
        int x1, y1, x2, y2;

        while (true)
        {
            std::cout << "Podaj koordynaty pierwszej karty (rzad i kolumne oddzielone spacja): ";
            std::cin >> x1 >> y1;
            if (plansza.sprawdzRuch(x1, y1))
                break;
            std::cout << "Nieprawidlowy ruch. Sprobuj ponownie." << std::endl;
        }

        plansza.odkryte[x1][y1] = true;
        plansza.wyswietl();

        while (true)
        {
            std::cout << "Podaj koordynaty drugiej karty (rzad i kolumne oddzielone spacja): ";
            std::cin >> x2 >> y2;
            if (plansza.sprawdzRuch(x2, y2))
                break;
            std::cout << "Nieprawidlowy ruch. Sprobuj ponownie." << std::endl;
        }

        plansza.odkryte[x2][y2] = true;
        plansza.wyswietl();

        if (plansza.plansza[x1][y1] == plansza.plansza[x2][y2])
        {
            std::cout << "Znaleziono pare!" << std::endl;
            if (kolejGracza1)
            {
                wynik1++;
            }
            else
            {
                wynik2++;
            }
            return true;
        }
        else
        {
            std::cout << "Brak pary." << std::endl;
            plansza.odkryte[x1][y1] = false;
            plansza.odkryte[x2][y2] = false;
            return false;
        }
    }

    void koniec_gry() {
        std::cout << "Koniec gry!" << std::endl;
        std::cout << "Wynik gracza 1: " << wynik1 << " pary" << std::endl;
        std::cout << "Wynik gracza 2: " << wynik2 << " pary" << std::endl;

        if (wynik1 > wynik2)
        {
            std::cout << "Gracz 1 wygrywa!" << std::endl;
        }
        else if (wynik2 > wynik1)
        {
            std::cout << "Gracz 2 wygrywa!" << std::endl;
        }
        else
        {
            std::cout << "Remis!" << std::endl;
        }
    }

    void petla_gry() {
        std::cout << "Zaczynamy gre!" << std::endl;

        int wszystkiePary = plansza.rzedy * plansza.kolumny / 2;

        while (wynik1 + wynik2 < wszystkiePary)
        {
            plansza.wyswietl();
            if (kolejGracza1)
            {
                std::cout << "Kolej gracza 1." << std::endl;
                if (!ruchGracza())
                {
                    kolejGracza1 = false;
                }
            }
            else
            {
                std::cout << "Kolej gracza 2." << std::endl;
                if (!ruchGracza())
                {
                    kolejGracza1 = true;
                }
            }
        }

        koniec_gry();
    }

    void przygotowanie()
    {
        srand(time(0));

        plansza.przygotowanie();

        wynik1 = 0;
        wynik2 = 0;
        kolejGracza1 = true;

        petla_gry();
    }
private:
    Plansza plansza;
    int wynik1;
    int wynik2;
    bool kolejGracza1;
};

#endif