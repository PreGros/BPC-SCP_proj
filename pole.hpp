#include <iostream>
#include <sstream>
#include <math.h>

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

        case 4:
            std::cerr << "Dělení nulou!" << std::endl;
            break;

        case 5:
            std::cerr << "Velikost pole je 0!" << std::endl;
            break;

        case 6:
            std::cerr << "Obě pole mají nulovou délku!" << std::endl;
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
    Pole(int len, T* arr) {
        e = new T[len];
        l = len;
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
    Pole(T value) { // converse-constructor
        l = 1;
        e = new T[1];
        e[0] = value;
    }
    ~Pole() {
        delete[] e;
    }
    T* operator[](int i) {
        return e[i];
    }

    T sum() {
        if (l == 0) {
            Exception err(5);
            std::cout << "Chyba při výpočtu součtu." << std::endl;
            err.throwE();
        }
        T sum = T();
        for (size_t i = 0; i < l; i++) {
            sum += e[i];
        }
        return sum;
    }

    double mean() {
        if (l == 0) {
            Exception err(5);
            std::cout << "Chyba při výpočtu průměru." << std::endl;
            err.throwE();
        }
        return sum() / l;
    }

    double stddev() {
        if (l == 0) {
            Exception err(5);
            std::cout << "Chyba při výpočtu průměru." << std::endl;
            err.throwE();
        }
        double meanVal = mean();
        double var = 0.0;
        for (size_t i = 0; i < l; i++) {
            var += pow(e[i] - meanVal, 2);
        }
        var /= l;
        return sqrt(var);
    }

    void sortA() {
        if (l == 0) {
            Exception err(5);
            std::cout << "Chyba při seřazování pole!";
            err.throwE();
        }
        for (size_t i = 0; i < l - 1; i++) {
            for (size_t j = 0; j < l - i - 1; j++) {
                if (e[j] > e[j + 1]) {
                    T temp = e[j];
                    e[j] = e[j + 1];
                    e[j + 1] = temp;
                }
            }
        }
    }

    void sortD() {
        if (l == 0) {
            Exception err(5);
            std::cout << "Chyba při seřazování pole!" << std::endl;
            err.throwE();
        }
        for (size_t i = 0; i < l - 1; i++) {
            for (size_t j = 0; j < l - i - 1; j++) {
                if (e[j] < e[j + 1]) {
                    T temp = e[j];
                    e[j] = e[j + 1];
                    e[j + 1] = temp;
                }
            }
        }
    }

    Pole<T> concat(const Pole<T> &X) {
        if (!l || !X.l) {
            if (!l && !X.l) {
                Exception err(6);
                std::cout << "Chyba při konkatenaci polí!" << std::endl;
                err.throwE();
            }
            else if (!l) {
                return Pole<T>(X.l, X.e);
            }
            else {
                return Pole<T>(l, e);
            }
        }
        
        Pole<T> result;
        result.l = l + X.l;
        result.e = new T[result.l];
        for (size_t i = 0; i < l; i++) {
            result.e[i] = e[i];
        }
        for (size_t i = 0; i < X.l; i++) {
            result.e[l + i] = X.e[i];
        }
        return result;
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
    template<typename Op> bool applyEOperation(const Pole<T> &X, Op operation) {
        if (l != X.l) {
            return false;
        }
        for (size_t i = 0; i < l; i++) {
            if (!operation(e[i], X.e[i])) {
                return false;
            }
        }
        return true;
    }
    bool operator==(const Pole<T> &X) {
        return applyEOperation(X, [](T a, T b) { return a == b; });
    }
    bool operator!=(const Pole<T> &X) {
        return !(*this == X);
    }

    Pole<T> operator-() {
        Pole<T> result(l,e);
        for (size_t i = 0; i < l; i++) {
            result.e[i] = -result.e[i];
        }
        return result;
    }


    template<class P> friend std::ostream& operator<<(std::ostream &out, const Pole<P> &X) {
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

    template<typename Op> friend Pole<T> applyAOperation(const Pole<T> &X, const Pole<T> &Y, Op operation) {
        const Pole<T>& longer = (X.l >= Y.l) ? X : Y;
        const Pole<T>& shorter = (X.l < Y.l) ? X : Y;

        int len = longer.l;
        Pole<T> result;
        result.l = len;
        result.e = new T[len];
        for (size_t i = 0; i < len; i++) {
            result.e[i] = longer.e[i];
        }

        if (shorter.l == 1) // if one of the args is type T, then apply operation to all longer elems with single value (from arg with type T)
            for (size_t i = 0; i < longer.l; i++)
                if (Y.l == 1)
                    result.e[i] = operation(result.e[i], shorter.e[0]);   
                else
                    result.e[i] = operation(shorter.e[0], result.e[i]); 
        else
            for (size_t i = 0; i < shorter.l; i++)
                if (&X == &longer)
                    result.e[i] = operation(result.e[i], shorter.e[i]);
                else
                    result.e[i] = operation(shorter.e[i], result.e[i]);

        return result;
    }

    friend Pole<T> operator+(const Pole<T> &X, const Pole<T> &Y) {
        return applyAOperation(X, Y, [](T a, T b) { return a + b; });
    }

    friend Pole<T> operator-(const Pole<T> &X, const Pole<T> &Y) {
        return applyAOperation(X, Y, [](T a, T b) { return a - b; });
    }

    friend Pole<T> operator*(const Pole<T> &X, const Pole<T> &Y) {
        return applyAOperation(X, Y, [](T a, T b) { return a * b; });
    }

    friend Pole<T> operator%(const Pole<T> &X, const Pole<T> &Y) {
        return applyAOperation(X, Y, [](T a, T b) { return a % b; });
    }

    friend Pole<T> operator/(const Pole<T> &X, const Pole<T> &Y) {
        return applyAOperation(X, Y, [](T a, T b) {
            if (b == 0) {
                Exception err(4);
                std::cout << "ERROR! Chyba při binární operaci nad dvě poli.";
                err.throwE();
            }
            return a / b;
        });
    }
};