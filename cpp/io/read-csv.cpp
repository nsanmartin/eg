#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

typedef vector<vector<string>> tabla;

void read_csv  (tabla & t, const string& filename) ;

int main (int argc, char ** argv) {
     for (int i = 1; i < argc; i++) {
          tabla t;
          read_csv(t, argv[i]);
          for (tabla::const_iterator fila = t.begin();
               fila != t.end();
               fila++) {
               for (vector<string>::const_iterator celda = fila->begin();
                    celda != fila->end();
                    celda++)
                    cout << *celda << " ";
               cout << endl;
          }
     }
}

void read_csv (tabla & t, const string& filename) {
     string line;
     ifstream infile(filename);

     while (getline(infile, line)) {
          vector<string> fila;
          istringstream iss(line);
          string s;
          while (iss >> s) 
               fila.push_back(s);

          t.push_back(fila);
     }
     infile.close();
}
     

