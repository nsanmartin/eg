#include <string>
#include <iostream>
#include <fstream>

#include "../graph.hpp"

using namespace std;
int main (int argc, char** argv) {
     if (argc < 2 ) {
          cout << "files cointaing graph representation "
               << "must be indicated" << endl;
     } else {
          int sum_prim, sum_kruskal;

              for (int i = 1; i < argc; i++) {
                  string filename = argv[i];
                  ifstream file;
                  file.open(filename);
                  if (!file) {
                      cerr << "No se pudo leer "
                           << filename << endl;
                      exit(1);
                  }

                  
                  Graph::adjlist g(file);
                  file.seekg(0);
                  Graph::edgelist h(file);
                  file.close();
                  sum_prim = g.prim();
                  sum_kruskal = h.kruskal();
                  cout << filename << "\t" << sum_prim
                       << "\t" << sum_kruskal << endl;
              }
              if (sum_prim != sum_kruskal) {
                   std::cerr << "error: sums differ" << endl;
                   exit(1);
              }
     }

     return 0;
}
