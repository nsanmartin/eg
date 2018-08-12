#include <algorithm>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#include <list>
#include <iostream>
#include <dirent.h> 
#include <sys/stat.h>
#include <time.h>

#define DATEBUFSIZE 80
using namespace std;


char date[DATEBUFSIZE];

void print_ctime(string filename) {
     struct stat stat_buf;

     if (stat(filename.c_str(), &stat_buf) == 0) {
          struct tm * timeinfo = localtime(&stat_buf.st_ctime);
          strftime(date, DATEBUFSIZE, "%Y-%m-%d %H:%M:%S", timeinfo);
          cout <<  date  << " "
               << filename << endl;
     } else {
          cerr << "error leyendo archivo"
               << filename << endl;
     }
     return;
}
                

int main (int argc, char ** argv) {
     if (argc < 2)
         cout << "uso: " << argv[0] << " FILE [FILE ...]" << endl;
     else {
          for (int i = 1; i < argc; i++)
               print_ctime(argv[i]);
     }
     return 0;
}
