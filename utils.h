#ifndef UTILS_H
#define UTILS_H

// funkcja aby pozwalac tylko na podawanie liczb
template <typename... Args> 
void getValidNumbers(Args &...args) // funkcja szablonowa, aby przyjmowac dowolna liczbe argumentow
{
    while (true)
    {
        (std::cin >> ... >> args); // przypisanie wartosci do zmiennych
        if (std::cin.fail()) // jesli wprowadzono niepoprawne dane
        {
            std::cin.clear(); // czyszczenie flagi bledu
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignorowanie blednych znakow
            std::cout << "Nieprawidlowe dane. Sprobuj ponownie." << std::endl; // komunikat o bledzie
        }
        else
        {
            break;
        }
    }
}

#endif