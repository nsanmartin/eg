// mutex example
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex
#include <vector>
#include <chrono>

using namespace std;
mutex mtx;           // mutex for critical section
int global = 0;

#define CANTIDAD_ITERACIONES 1000

void th_foo_lock (int n, int veces) {
     mtx.lock();
     for (int i=0; i < veces; ++i) { ; }
     mtx.unlock();
}

void th_foo_nolock (int n, int veces) {
     for (int i=0; i < veces; ++i) { ; }
}

void exp_lock(int nthreads, int veces) {
     std::vector<thread> threads;
     for (int i = 0; i < nthreads; i++)
          threads.push_back(thread(th_foo_lock, i, veces));
     for (int i = 0; i < nthreads; i++)
          threads[i].join();
     return;
}

void exp_nolock(int nthreads, int veces) {
     std::vector<thread> threads;
     for (int i = 0; i < nthreads; i++)
          threads.push_back(thread(th_foo_nolock, i, veces));
     for (int i = 0; i < nthreads; i++)
          threads[i].join();
     return;
}


int main (int argc, char ** argv) {
     if (argc < 3) {
          cout << "Indicar numero de threads y cantidad de numeros a imprimir\n";
          exit(0);
     }
     int nthreads = atoi (argv[1]);
     int veces = atoi (argv[2]);
     
     auto start_lock = chrono::steady_clock::now();
     for (int i = 0; i < CANTIDAD_ITERACIONES; i++)
          exp_lock(nthreads, veces);
     auto end_lock = chrono::steady_clock::now();

     auto start_nolock = chrono::steady_clock::now();
     for (int i = 0; i < CANTIDAD_ITERACIONES; i++)
          exp_nolock(nthreads, veces);
     auto end_nolock = chrono::steady_clock::now();
     
     cout << chrono::duration<double, milli>(
          (end_lock - start_lock) / CANTIDAD_ITERACIONES ).count()
          << " "
          << chrono::duration<double, milli>(
               (end_nolock - start_nolock) / CANTIDAD_ITERACIONES).count()
          << endl;
          
     return 0;
}

          
