#include <iostream>
#include <string>
#include <chrono>

#include <cstring>

void print_usage(char * program) {
     std::cout << "use: " << program << " TIMES BUFFER_SIZE"
               << std::endl
               << "The program outputs:" << std::endl
               << "times-called buffer-size "
               <<  "time-for-copy time-for-ref"
               << std:: endl;
     
}

void fit_ascii(char * a, int n) {
    for (int i = 0; i < n; i++) {
          unsigned char d = 0x20 + (a[i] & 0x3f);
          a[i] = d;
     }
}

void copy_string(std::string s, int times) {
     if (times < 0)
          return;
     copy_string(s, times - 1);
}

void ref_string(std::string& s, int times) {
     if (times < 0)
          return;
     ref_string(s, times - 1);
}

int main (int argc, char ** argv) {
     

     if (argc < 3) {
          print_usage(argv[0]);
     } else {

          int times = std::stoi(argv[1]);
          int bufsz = std::stoi(argv[2]);
          char array[bufsz];
          fit_ascii(array, bufsz);
          std::string s(array);


          std::cout << times << " " << bufsz << " ";
          
          auto start_copy = std::chrono::steady_clock::now();
          copy_string(s, times);
          auto end_copy = std::chrono::steady_clock::now();
          auto diff_copy = end_copy - start_copy;
          std::cout << std::chrono::duration <double, std::milli> (diff_copy).count()
                    << " ";

          auto start_ref = std::chrono::steady_clock::now();
          ref_string(s, times);
          auto end_ref = std::chrono::steady_clock::now();
          auto diff_ref = end_ref - start_ref;
          std::cout << std::chrono::duration <double, std::milli> (diff_ref).count()
                    << std::endl;


          
     }
     
}
