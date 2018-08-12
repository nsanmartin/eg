#include <stdio.h>
#include <string>
#include <list>
#include <iostream>
#include <dirent.h> 

using std::string;
using std::cerr;
using std::cout;
using std::endl;
using std::list;

int ls(string dirpath) {
    list<string> lista;
    DIR *d;
    if ( d = opendir (dirpath.c_str())) {
        struct dirent *dentry;
        while ((dentry = readdir(d)) != NULL) {
            lista.push_back(string(dentry -> d_name));
        }
        closedir(d);
    } else {
        cerr << "error: no pude abrir " << dirpath << endl;
        return 1;
    }

    list<string>::const_iterator s;
    for (s = lista.begin(); s != lista.end(); s++) {
        cout << *s << endl;
    }
    return 0;
}

int main (int argc, char ** argv ) {
    if (argc < 2) {
        cout << "uso: " << argv[0] << " DIR [DIR...]" << endl;
    } else {
        for (int i = 1; i < argc; i++) {
            ls(argv[i]);
        }
    }

}
