#include <random>
#include <vector>
#include <iostream>
#include <time.h>
#include <stdlib.h>

#define NPUNTOS 80
using namespace std;

class Punto {
     int x, y;
     
     static random_device seed_generator;
     static unsigned seed;
     static mt19937 mersenne_generator;
     static uniform_int_distribution<unsigned> distribution;
public:
     Punto() {
          x = distribution(mersenne_generator);
          y = distribution(mersenne_generator);
     }
     Punto(int x, int y) : x(x), y(y) {}
     friend ostream &operator<<(ostream &os, Punto& p) ;
};

random_device Punto::seed_generator;
unsigned Punto::seed = seed_generator();
uniform_int_distribution<unsigned> Punto::distribution(0, 256);
mt19937 Punto::mersenne_generator(Punto::seed);


ostream &operator<<(ostream &os, Punto& p) {
     os << "(" << p.x << "," << p.y << ")";
     return os;
}

int main () {

     vector<Punto> v;
     v.push_back(Punto(0,0));
     cout << "Puntos random" << endl;
     
     for (int i = 0; i < NPUNTOS; i++) {
          v.push_back(Punto());
     }
     
     vector<Punto>::iterator it;
     for (it = v.begin(); it != v.end(); it++) {
          cout << *it << " ";
     }

     cout << endl;
}
