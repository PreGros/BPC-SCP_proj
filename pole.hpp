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
            std::cerr << "Chyba při čtení elementů ze streamu." << std::endl;
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
    Pole<T>& operator=(const Pole<T>& X) { // copy-assignment operator
        if (this != &X) {
            delete[] e;
            l = X.l;
            e = new T[l];
            for (size_t i = 0; i < l; i++) {
                e[i] = X.e[i];
            }
        }
        return *this;
    }

    template<class P> friend std::ostream& operator<<(std::ostream &out, Pole<P> &X) {
        out << '[';
        for (size_t i = 0; i < X.l; i++) {
            out << X.e[i];
            if (i != (X.l-1)) {
                out << ",";
            }
        }
        out << "]";
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

        if (iss.fail() && !iss.eof()) {
            Exception err(3);
            std::cout << "Chyba načítání pole!" << std::endl;
            err.throwE();
        }

        delete[] X.e;
        X.l = temp;
        X.e = new P[temp];

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
        const Pole<T>& longer = (X.l >= Y.l) ? X : Y;
        const Pole<T>& shorter = (X.l < Y.l) ? X : Y;

        int len = longer.l;
        Pole<T> result(len);
        for (size_t i = 0; i < len; i++) {
            result.e[i] = longer.e[i];
        }

        for (size_t i = 0; i < shorter.l; i++) {
            result.e[i] += shorter.e[i];
        }
        
        return result;
    }
};