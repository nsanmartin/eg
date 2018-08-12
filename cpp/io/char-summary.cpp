#include <algorithm>
#include <map>
#include <vector>
#include <iostream>
#include <stdio.h>
//#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

char maxCountIndx(std::map <char, long long> mapa);
int nOrden(long long i, std::map<char, long long> mapa);
void getOrder(std::map<char, long long> desorden,
	      std::vector<int>& orden);
void mostrarTablaSinOrden(std::map<char, long long> desorden);
void mostrarTablaConOrden(std::map<char, long long> desorden,
			   std::map<char, unsigned int> orden);

void makeOrder(std::map<char, long long> desorden,
	       std::map<char, unsigned int> &orden);

int main( int argc, char *argv[] )  
{
  
  bool sorted = false;
  char c;
  
  while ((c = getopt (argc, argv, "sabc")) != -1) {
    switch (c) {
    case 's':
      sorted = true;
      break;
    case 'a':
      std::cout << "caso a\n";
      return 0;
      break;
    case 'b':
      std::cout << "caso b\n";
      return 0;
    case 'c':
      return 0;
      break;
    case '?':
      if (optopt == 'd' || optopt == 'o') {
      }
      else if (isprint (optopt)) {
	fprintf (stderr, "Unknown option `-%c'.\n", optopt);
      }
      else
	fprintf (stderr,
		 "Unknown option character `\\x%x'.\n",
		 optopt);
      return 1;
    default:
      abort ();
    }
  }
  // termina getopt

  // saco cuentas
  std::map<char, long long> charsCount;
  while (std::cin.get(c))
    charsCount[c] += 1;

  //muestro tabla
  std::cout << "dec: \tcount: \t char:\n";
  if (sorted) {
    std::map<char, unsigned int> orden;
    makeOrder(charsCount, orden);
    mostrarTablaConOrden(charsCount, orden);
  }
  else
    mostrarTablaSinOrden(charsCount);
  
  return 0;
}

char maxCountIndx(std::map <char, unsigned int> mapa) {
  char c = CHAR_MIN, res = CHAR_MIN;
  do{
    if(mapa[c] > mapa[res]) res = c;
  } while(++c != CHAR_MIN) ;
  
  return res;
}

unsigned char maxVal(std::map <char, unsigned int> mapa) {
  char c = CHAR_MIN;
  unsigned char max = mapa[c];
  while(++c != CHAR_MIN)
    if (mapa[c] > max) max = mapa[c];
  return max;
}

int nOrden(long long i, std::map<char, long long> mapa) {
  int  res = 1;
  std::map<char, long long>::iterator it;

  for( it = mapa.begin(); it != mapa.end(); it++) {
    if (i < it->second) res++;
  }
  return res;
}

void getOrder(std::map<char, long long> desorden,
	      std::vector<int>& orden) {


  std::map<char, long long>::iterator itdes = desorden.begin();
  std::vector<int>::iterator itord = orden.begin();
  for(; itdes != desorden.end(); itdes++, itord++) {
    *itord = nOrden(itdes->second, desorden);
  }
}


void mostrarTablaSinOrden(std::map<char, long long> desorden) {
  char c = CHAR_MIN;
  do {
    if (desorden[c] > 0)
      printf("%d \t%lld \t%c\n", c, desorden[c], c);
  } while(++c != CHAR_MIN);
}

void makeOrder(std::map<char, long long> desorden,
	       std::map<char, unsigned int> &orden)
{
  char c = CHAR_MIN;
  do {
    orden[c] = nOrden(desorden[c], desorden);
  } while(++c != CHAR_MIN) ;
}

void mostrarTablaConOrden(std::map<char, long long> desorden,
			   std::map<char, unsigned int> orden) {
  char i = CHAR_MIN, j = CHAR_MIN;
  unsigned char ordMax = maxVal(orden);
  
  do {
    do {
      if (orden[j] == i)
	printf("%d \t%lld \t%c\n", j, desorden[j], j);
    } while (++j != CHAR_MIN);
  } while (++i < ordMax);
  std::cout << std::endl;
}

