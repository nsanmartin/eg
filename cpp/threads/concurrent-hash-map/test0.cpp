#include <iostream>
#include <fstream>

#include <pthread.h>

#include "ConcurrentHashMap.hpp"

using namespace std;
 
int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Filenames missing" << endl;
        exit(0);
    }

    for (int i= 1; i < argc; i++) {
        std::string filename = argv[i];
        std::ifstream file(filename, std::fstream::in);
        ConcurrentHashMap h(file); 
        file.close();
        
        for (int i = 0; i < 26; i++) 
            for (auto iter = h._listas[i].begin();
                 iter != h._listas[i].end();
                 ++iter) 
                cout << iter->first << " " << iter->second
                     << endl;
    }
	return 0;
}

