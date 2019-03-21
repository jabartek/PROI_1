#include <stdexcept>
#include <cmath>
#include <random>

#include "matrix.h"
#include "utils.h"


void testAction(int action) {
    if (action == 1) {
        int size;
        std::cout << "Dodawanie.\nPodaj wielkosc macierzy: ";
        size = readInt();
        size = ((size > 0) ? size : 1);
        Matrix m1(size);
        Matrix m2(size);
        std::cout << "Wprowadz 1. macierz o wielkosci " << size << "x" << size << ": ";
        std::cin >> m1;
        std::cout << "Wprowadz 2. macierz o wielkosci " << size << "x" << size << ": ";
        std::cin >> m2;
        std::cout << "Dodawanie:\n" << m1 << "+\n" << m2 << "=\n" << m1 + m2;
    }
    if (action == 2) {
        int size;
        std::cout << "Odejmowanie.\nPodaj wielkosc macierzy: ";
        size = readInt();
        size = ((size > 0) ? size : 1);
        Matrix m1(size);
        Matrix m2(size);
        std::cout << "Wprowadz 1. macierz o wielkosci " << size << "x" << size << ": ";
        std::cin >> m1;
        std::cout << "Wprowadz 2. macierz o wielkosci " << size << "x" << size << ": ";
        std::cin >> m2;
        std::cout << "Odejmowanie:\n" << m1 << "-\n" << m2 << "=\n" << m1 - m2;
    }
    if (action == 3) {
        int size;
        int coeff;
        std::cout << "Mnozenie przez stala.\nPodaj wielkosc macierzy: ";
        size = readInt();
        size = ((size > 0) ? size : 1);
        Matrix m1(size);
        Matrix m2(size);
        std::cout << "Wprowadz macierz o wielkosci " << size << "x" << size << ": ";
        std::cin >> m1;
        std::cout << "Wprowadz stala: ";
        std::cin >> coeff;
        std::cout << "Mnozenie przez stala:\n" << m1 << "*\n" << coeff << "=\n" << m1 * coeff;
    }
    if (action == 4) {
        int size;
        std::cout << "Mnozenie macierzy.\nPodaj wielkosc macierzy: ";
        size = readInt();
        size = ((size > 0) ? size : 1);
        Matrix m1(size);
        Matrix m2(size);
        std::cout << "Wprowadz 1. macierz o wielkosci " << size << "x" << size << ": ";
        std::cin >> m1;
        std::cout << "Wprowadz 2. macierz o wielkosci " << size << "x" << size << ": ";
        std::cin >> m2;
        std::cout << "Mnozenie macierzy:\n" << m1 << "*\n" << m2 << "=\n" << m1 * m2;
        std::cout << "Mnozenie macierzy:\n" << m2 << "*\n" << m1 << "=\n" << m2 * m1;
    }
    if (action == 5) {
        int size;
        std::cout << "Wyznacznik.\nPodaj wielkosc macierzy: ";
        size = readInt();
        size = ((size > 0) ? size : 1);
        Matrix m1(size);
        std::cout << "Wprowadz macierz o wielkosci " << size << "x" << size << ": ";
        std::cin >> m1;
        std::cout << "\n" << m1.calcDet() << " - to wyznacznik wprowadzonej macierzy\n";
    }

};

int userMenu() {
    std::cout
            << "1 - dodawanie, 2 - odejmowanie, 3 - mnozenie przez stala,\n4 - mnozenie macierzy, 5 - wyznacznik, 6 - zakoncz\nWybierz akcje: ";
    int action = readInt();
    if (action != 1 && action != 2 && action != 3 && action != 4 && action != 5)
        return 1;
    testAction(action);
    return 0;
}

int readInt() {
    std::string temp;
    int action = 0;
    bool error = false;
    do {
        std::cin >> temp;
        try {
            action = std::stoi(temp);
            error = false;
        }
        catch (std::invalid_argument) {
            std::cout << "\nInvalid input! Try again: ";
            error = true;
        }
    } while (error);

    return action;
}
