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
    int delka = 4;
    double *p2 = new double[delka];
    p2[0] = 0.0;
    p2[1] = 5.0;
    p2[2] = 10.0;
    p2[3] = 25.0;
    
    Pole<double> A(delka, p2);

    delete[] p2;




    std::ifstream fileB;
    Pole<double> B;

    fileB.open(argv[1]);

    fileB >> B;

    Pole<double> C = A + B * 10;

    std::string odpoved;

    if (A == B) {
        odpoved = "Ano, rovna";
    }
    else {
        odpoved = "Ne, nerovna";
    }
    
    std::cout << C << std::endl;

    std::ofstream fileC;
    fileC.open("output.txt");

    fileC << C;

    fileC.close();

    return 0;
}
