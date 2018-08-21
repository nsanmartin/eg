#include <iostream>
#include <string>
#include <chrono>

#include <cstring>

void print_usage(char * program) {
     std::cout << "use: " << program << " TIMES BUFFER_SIZE"
               << std::endl
               << "The program outputs:" << std::endl
               << "times-called buffer-size "
               <<  "time-for-retarg time-for-modref"
               << std::endl;
}

std::string retarg(int times, int sz) {
     std::string s;
     return std::string(sz, '\0');
}

void modref (std::string& s, int times) {
     s = std::string(s.size(), '\0');
     return;
}

int main (int argc, char ** argv) {
     if (argc < 3) { print_usage(argv[0]); }
     else {
          
          int times = std::stoi(argv[1]);
          int bufsz = std::stoi(argv[2]);
          std::cout << times << " " << bufsz << " ";
          
          auto start_copy = std::chrono::steady_clock::now();

          for (int i = 0; i < times; i++)
               std::string s = retarg(times, bufsz);

          auto end_copy = std::chrono::steady_clock::now();
          auto diff_copy = end_copy - start_copy;
          std::cout << std::chrono::duration <double, std::milli> (diff_copy).count()
                    << " ";


          std::string t(bufsz, '\0');
          auto start_ref = std::chrono::steady_clock::now();

          for (int i = 0; i < times; i++)
               modref(t, times);
          
          auto end_ref = std::chrono::steady_clock::now();
          auto diff_ref = end_ref - start_ref;
          std::cout << std::chrono::duration <double, std::milli> (diff_ref).count()
                    << std::endl;
     }
     
}
