// mutex example
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex
#include <vector>

using namespace std;
mutex mtx;           // mutex for critical section
int global = 0;

void th_foo (int n, int veces) {
     for (int i=0; i < veces; ++i) { ; }
     //std::cout << n << " ";

}

int main (int argc, char ** argv) {
     if (argc < 3) {
          cout << "Indicar numero de threads y cantidad de numeros a imprimir\n";
          exit(0);
     }
     int nthreads = atoi (argv[1]);
     int veces = atoi (argv[2]);

     std::vector<thread> threads;
     for (int i = 0; i < nthreads; i++)
          threads.push_back(thread(th_foo, i, veces));

     for (int i = 0; i < nthreads; i++)
          threads[i].join();

 
     return 0;
}
