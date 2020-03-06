int fact(int x)
{
  if (x < 1) return 1;
  else return fact(x-1) * x;
}

int main(void)
{
  int x; int y;
  x = input();
  y = fact(x);
  output(y);
  return 0;
}
