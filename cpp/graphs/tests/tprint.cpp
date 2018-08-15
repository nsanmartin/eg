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
               file.seekg(0);
               Graph::adjlist g_adjlist(file);
               file.seekg(0);
               Graph::edgelist g_edgelist(file);
               file.close();
               //g_adjmatrix.print();
               //g_adjlist.print();
               g_edgelist.print();
          }
     }

     return 0;
}
