#include <iostream>
#include <fstream>
#include <random>
#include "matrix.h"


int main() {

    int size1, size2, size3;
    double coeff;
    size1 = 4;
    size2 = 6;
    size3 = 9;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000);
    coeff = double(dis(gen)) / 100;
    Matrix matrix1(size1, 2);
    Matrix matrix1p(size1, 2);
    Matrix matrix2(size2, 2);
    Matrix matrix3(size3, 2);
    std::cout<<"Stworzone losowo wypelnione macierze o wielkosciach "<< size1<<", "<< size1<<", "<<size2<<", "<<size3<<":\n"<<matrix1<<"\n"<<matrix1p<<"\n"<<matrix2<<"\n"<<matrix3;
    std::cout<<"Sprawdzenie operatorow:";
    std::cout<<"\nMnozenie macierzy\n"<<matrix1<<"*\n"<<matrix1p<<"=\n"<<matrix1*matrix1p;
    std::cout<<"\nMnozenie przez stala\n"<<matrix1<<"*\n"<<coeff<<"=\n"<<matrix1*coeff;
    std::cout<<"\nDodawanie macierzy\n"<<matrix1<<"+\n"<<matrix2<<"=\n"<<matrix1+matrix2;
    std::cout<<"\nDodawanie macierzy\n"<<matrix3<<"+\n"<<matrix2<<"=\n"<<matrix3+matrix2;
    std::cout<<"\nOdejmowanie macierzy\n"<<matrix1<<"-\n"<<matrix2<<"=\n"<<matrix1-matrix2;
    std::cout<<"\nOdejmowanie macierzy\n"<<matrix3<<"-\n"<<matrix2<<"=\n"<<matrix3-matrix2;
    std::cout<<"\nWyznacznik macierzy\n"<<matrix3<<"\n"<<matrix3.calcDet()<<" - to wyznacznik macierzy matrix3\n";
    int newOrder;
    std::cout<<"\nWprowadz wielkosc wlasnej macierzy: ";
    std::cin>>newOrder;
    Matrix ownMatrix(newOrder);
    std::cout<<"\nWprowadz macierz "<<newOrder<<"x"<<newOrder<<":\n";
    std::cin>>ownMatrix;
    std::cout<<"Wprowadzona macierz:\n"<<ownMatrix<<ownMatrix.calcDet()<<" - to wyznacznik wprowadzonej macierzy\n";
    delete(&ownMatrix);
    std::cout<<"Powyzej wywolano destruktor wprowadzonej macierzy.\n";



    return 0;

}