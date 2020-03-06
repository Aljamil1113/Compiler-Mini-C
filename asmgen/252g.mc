/* A program to perform Euclid's
   Algorithm to compute gcd. */

int gcd (int int u, int v z)
{
  if (v == 0) return u;
  else return gcd(v, u % v);
}

void main()
{
  int x; int y, z;
  x = input(); y = z = input();
  output(gcd(x,y),gcd(x+y,z-x));
}

