#include <algorithm>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#include <list>
#include <iostream>
#include <dirent.h> 

//using namespace std;

void dir_files(std::vector<std::string>& files, char * dirpath) {
    DIR *d;
    if ( d = opendir (dirpath)) {
        struct dirent *dentry;
        while ((dentry = readdir(d)) != NULL) {
            files.push_back(std::string(dentry -> d_name));
        }
        closedir(d);
    } else {
        std::cerr << "error: no pude abrir" << dirpath
                  << std::endl;
    }
    return;
}

int main (int argc, char ** argv) {
     if (argc < 3)
         std::cout << "uso: " << argv[0]
                   << " FILE [FILE ...] DIR"
                   << std::endl;
     else {
          int si, no;
          si = no = 0;
          std::vector<std::string> files;
          dir_files (files, argv[argc - 1 ]);
          sort(files.begin(), files.end());
          for (int i = 1; i < argc - 1; i++) {
              int test = binary_search (
                  files.begin(), files.end(),
                  std::string(argv[i]));
                                        
               si += test;
               no += 1 - test;
               std::cout << (test ? "si": "no")
                         << " esta " << argv[i]
                         << std::endl;
          }
          std::cout << "si: " << si << " no: " << no << std::endl;
     }
     return 0;
}
