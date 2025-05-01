#include <stdio.h>
#include <stdlib.h>
#include "pole.hpp"
#include <iostream>
#include <cmath>
#include <string.h>
#include <sstream>
#include <vector>
#include <fstream>

int main(int argc, char const *argv[])
{
    std::ifstream fileA;
    Pole<int> A;

    fileA.open(argv[1]);

    fileA >> A;

    fileA.close();

    int delka = 5;
    int *p2 = new int[delka];
    p2[0] = 5;
    p2[1] = 10;
    p2[2] = 15;
    p2[3] = 20;
    p2[4] = 25;
    
    Pole<int> B(delka, p2);
    delete[] p2;

    std::cout << "Načtená pole: \n";
    std::cout << "A: " << A << std::endl;
    std::cout << "B: " << B << std::endl;

    std::cout << "\nAritmetické operace: \n";
    std::cout << "A + B = " << A+B << std::endl;
    std::cout << "A * B = " << A*B << std::endl;
    std::cout << "A - B = " << A-B << std::endl;
    std::cout << "B - A = " << B-A << std::endl;
    std::cout << "A / B = " << A/B << std::endl;
    std::cout << "B / A = " << B/A << std::endl;
    std::cout << "A % B = " << A%B << std::endl;
    std::cout << "B % A = " << B%A << std::endl;

    std::cout << "\nAritmetické operace s konstantou: \n";
    std::cout << "A + 42 = " << A + 42 << std::endl;
    std::cout << "42 % A = " << 42 % A << std::endl;

    std::cout << "\nOperátor nerovnosti: \n";
    std::cout << "-A = " << -A << std::endl;

    std::cout << "\nOperace rovnosti: \n";
    std::cout << "A == A = " << (A == A) << std::endl;
    std::cout << "A != A = " << (A != A) << std::endl;
    std::cout << "A == B = " << (A == B) << std::endl;
    std::cout << "A != B = " << (A != B) << std::endl;

    std::cout << "\nOperátory na statistiku: \n";
    std::cout << "Suma A = " << A.sum() << std::endl;
    std::cout << "Průměr A = " << A.mean() << std::endl;
    std::cout << "Směrodatná odchylka A = " << A.stddev() << std::endl;

    std::cout << "\nSeřazení pole: \n";
    A.sortD();
    std::cout << "Sestupně A: " << A << std::endl;
    A.sortA();
    std::cout << "Vzestupně A: " << A << std::endl;

    std::cout << "\nKonkatenace dvou polí: \n";
    std::cout << "A . B = " << A.concat(B) << std::endl;

    std::ofstream fileC;

    fileC.open("output.txt");

    fileC << (A - 9) + B * 9;

    return 0;
}
