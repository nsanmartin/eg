/*
TOTO: arreglar excepcion
*/

#include <algorithm>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#include <list>
#include <iostream>
#include <dirent.h> 

#include <sys/stat.h>
#include <cstring>
#include <unistd.h>

using namespace std;

void dir_files(vector<string>& files, char * dirpath) {
    DIR *d;
    if ( d = opendir (dirpath)) {
        struct dirent *dentry;
        while ((dentry = readdir(d)) != NULL) {
            files.push_back(string(dentry -> d_name));
        }
        closedir(d);
    } else {
        cerr << "error: no pude abrir" << dirpath << endl;
        abort();
    }
    return;
}

bool es_subdirectorio (struct dirent * dentry) {
    return strcmp(".", dentry -> d_name) != 0
        && strcmp("..", dentry -> d_name) != 0;
    
    
}

unsigned long count_bytes_recursive(string dirpath, bool verbose) { 
    DIR *d;
    unsigned long count = 0;
    if ( d = opendir (dirpath.c_str())) {
        struct dirent *dentry;
        while ((dentry = readdir(d)) != NULL) {
            string path = dirpath;

            if (dirpath == "/")
                path += string(dentry -> d_name);
            else 
                path += "/" + string(dentry -> d_name);
            
            if (dentry -> d_type == DT_DIR) {
                if (!es_subdirectorio(dentry))
                    continue;
                count += count_bytes_recursive(path.c_str(), verbose);
                
            } else if (dentry -> d_type == DT_REG) {
                
                struct stat stat_buf;
                if (stat(path.c_str(), &stat_buf) == 0)
                    count += stat_buf.st_size;
                else
                    cout << "error leyendo size of file"
                         << path << endl;
                        
                
            } else if (verbose) {
                cout << "no cuento file: "
                     << dentry -> d_name << endl;
            }
        }
        closedir(d);
    } else {
        cerr << "error: no pude abrir '" << dirpath << "'"
             << endl;
        abort();
    }
    return count;
    

}

unsigned long count_bytes_recursive2(string dirpath, bool verbose) { 
    DIR *d;
    unsigned long count = 0;
    try {
        d = opendir (dirpath.c_str());
        struct dirent *dentry;
        while ((dentry = readdir(d)) != NULL) {
            string path = dirpath;

            if (dirpath == "/")
                path += string(dentry -> d_name);
            else 
                path += "/" + string(dentry -> d_name);
            
            if (dentry -> d_type == DT_DIR) {
                if (!es_subdirectorio(dentry))
                    continue;
                count += count_bytes_recursive2(path.c_str(), verbose);
                
            } else if (dentry -> d_type == DT_REG) {
                
                struct stat stat_buf;
                if (stat(path.c_str(), &stat_buf) == 0)
                    count += stat_buf.st_size;
                else
                    cout << "error leyendo size of file"
                         << path << endl;
                        
                
            } else if (verbose) {
                cout << "no cuento file: "
                     << dentry -> d_name << endl;
            }
        }
        closedir(d);
    } catch (int e) {
        cerr << "error: no pude abrir '" << dirpath << "'"
             << "exeption: " << e << endl;
    }
    return count;

}

int main (int argc, char ** argv) {
     if (argc < 2)
         cout << "uso: " << argv[0] << " DIR" << endl;
     else {
         bool verbose = false;
         char c;
         
         while ( (c = getopt (argc, argv, "v")) != -1) 
             switch (c) {
             case 'v':
                 verbose = true;
                 break;
             case '?':
                 cerr << "unknown option " << optopt;
                 return 1;
             default:
                 abort();
         }
         
         for (int i = optind; i < argc ; i++) {
             cout << count_bytes_recursive2(string(argv[i]), verbose) << endl;
         }
     }
     return 0;
}
