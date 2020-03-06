/* A program to perform Euclid's
   Algorithm to compute gcd. */

int gcd (int u, int v z)
{
  if (v == 0) return u;
  else return gcd(v, u % v);
}

void main(void)
{
  int x; int y;
  x = input(); y = input();
  output(gcd(x,y));
}
