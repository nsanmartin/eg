long partition (char* a, long p, long r){
     char x = a[r];
     long i = p - 1;
     for (long j = p; j < r; j++) {
          if (a[j] <= x) {
               i++;
               char tmp = a[i];
               a[i] = a[j];
               a[j] = tmp;
          }
     }
     char tmp = a[i + 1];
     a[i + 1] = a[r];
     a[r] = tmp;
     return i + 1;
}

void quicksort_aux(char* a, long p, long r) {

     if ( p < r ) {
          long q = partition (a, p, r);
          quicksort_aux(a, p, q - 1);
          quicksort_aux(a, q + 1, r);
     }
}


void quicksort(char* a, long len) {
     quicksort_aux(a, 0, len - 1);
}
