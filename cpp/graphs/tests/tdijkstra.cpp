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
               // Graph::edgelist h(file);
               file.close();
               vector<int> ddij = g.dijkstra(0);
               vector<int> dbfor = g.bellman_ford(0);
               std::cout << filename << std::endl;
               for (int i : ddij)
                    std::cout << i << " ";
               std::cout << std::endl;
               for (int i : dbfor)
                    std::cout << i << " ";
               std::cout << std::endl;
               cout << "------" << endl;
               
               if (ddij != dbfor) {
                    std::cerr << "error: algorithms differ"
                              << endl;
                    exit(1);

               }
          }
     }

     return 0;
}
