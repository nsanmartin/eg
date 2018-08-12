
int maximoComunDivisor(int x, int y)
{
   if (x == 0 || y == 0)
      return x > y ? x : y;
   int min = abs(x) < abs(y) ? abs(x) : abs(y);
   int mcd = 1;
   for(int i = 2; i <= min; i++)
   {
      if( x % i == 0 && y % i == 0)
	 mcd = i;
   }
   return mcd;
}
