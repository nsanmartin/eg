#include <algorithm>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#include <list>
#include <iostream>
#include <dirent.h> 

using namespace std;

void dir_files(vector<string>& files, char * dirpath) {
    DIR *d;
    if ( d = opendir (dirpath)) {
        struct dirent *dentry;
        while ((dentry = readdir(d)) != NULL) {
            files.push_back(string(dentry -> d_name));
        }
        closedir(d);
    } else { cerr << "error: no pude abrir" << dirpath << endl; }
    return;
}

int main (int argc, char ** argv) {
     if (argc < 3)
         cout << "uso: " << argv[0] << " FILE [FILE ...] DIR" << endl;
     else {
          int si, no;
          si = no = 0;
          vector<string> files;
          dir_files (files, argv[argc - 1 ]);
          sort(files.begin(), files.end());
          for (int i = 1; i < argc - 1; i++) {
              int test = binary_search (
                  files.begin(), files.end(), string(argv[i]));
                                        
               si += test;
               no += 1 - test;
               cout << (test ? "si": "no")
                    << " esta " << argv[i]
                    << endl;
          }
          cout << "si: " << si << " no: " << no << endl;
     }
     return 0;
}
