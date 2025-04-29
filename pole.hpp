#include <iostream>
#include <sstream>

class Exception {
    int eNum;

public:
    Exception();
    Exception(int number) {
        eNum = number;
    }

    void throwE() {
        switch (eNum)
        {
        case 3:
            std::cerr << "Rozdílná velikost polí!" << std::endl;
            break;
        
        default:
            std::cerr << "Nastala chyba! Nepovím jaká! (Výchozí chyba)" << std::endl;
            break;
        }
        exit(eNum);
    }
};

template <class T> class Pole {
public:
    T *e;
    int l;

public:
    Pole() {
        l = 0;
        e = nullptr;
    }
    Pole(int len) {
        l = len;
        e = new T[l];
    }
    Pole(int len, T* arr) : Pole(len) {
        for (size_t i = 0; i < l; i++) {
            e[i] = arr[i];
        }
    }
    Pole(Pole<T> &X) { // copy-constructor
        l = X.l;
        e = new T[l];
        for (size_t i = 0; i < l; i++) {
            e[i] = X.e[i];
        }
    }
    Pole(T value) : Pole(1) { // converse-constructor
        l = 1;
        e[0] = value;
    }
    ~Pole() {
        delete[] e;
    }
    T* operator[](int i) {
        return e[i];
    }

    template<class P> friend std::ostream& operator<<(std::ostream &out, Pole<P> &X) {
        std::cout << '[';
        for (size_t i = 0; i < X.l; i++) {
            std::cout << X.e[i];
            if (i != (X.l-1)) {
                std::cout << ",";
            }
        }
        std::cout << "]";
        return out;
    }
    template<class P> friend std::istream& operator>>(std::istream &in, Pole<P> &X) {   
        std::string line; 
        std::getline(in, line);
        std::istringstream iss(line);
        P value;

        int temp = 0;
        
        while (iss >> value) {
            temp++;
        }

        delete[] X.e;
        X.l = temp;
        X.e = new T[temp];

        iss.clear(); // reset
        iss.str(line);

        int i = 0;
        while (iss >> value) {
            X.e[i] = value;
            i++;
        }

        return in;
    }
    friend Pole<T> operator+(const Pole<T> &X, const Pole<T> &Y) {
        if (X.l != Y.l) {
            Exception err(3);
            std::cout << "ERROR! Chyba při sčítání dvou polí.";
            err.throwE();
        }
        int len = X.l;
        Pole<T> result(len);
        for (size_t i = 0; i < len; i++) {
            result.e[i] = X.e[i] + Y.e[i];
        }
        
        return result;
    }
};