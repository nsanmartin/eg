#include <string>
#include <iostream>
#include <fstream>

#include "../graph.hpp"

using namespace std;

void open_file(std::ifstream& file, char * filename) {
     file.open(filename);
     if (!file) {
          cerr << "No se pudo leer " << filename << endl;
          exit(1);
     }
}

int main (int argc, char** argv) {
     if (argc < 2 ) {
          cout << "files cointaing graph representation "
               << "must be indicated" << endl;
     } else {
          
          for (int i = 1; i < argc; i++) {
               ifstream file;
               char* filename = argv[i];
               open_file(file, filename);
               Graph::adjmatrix g_adjmatrix(file);
               file.close();

               // Graph::distances_matrix dmdan
               //      = g_adjmatrix.dantzig();
               // dmdan.print();

               Graph::distances_matrix dmfloyd
                    = g_adjmatrix.floyd();
               dmfloyd.print();

               
               
          }
     }

     return 0;
}
