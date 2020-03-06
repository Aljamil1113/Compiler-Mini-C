int count(int x[])
{
  int i;
  i = 0;
  while (x[i] != -1)
   i = i + 1;
  return i;
}

void main(void)
{
  int x[5]; int y;

  x[0] = 3;
  x[1] = x[0] - 5;
  x[2] = x[1] + x[0];
  x[3] = 10;
  x[4] = -1;

  y = count(x);

  output(y);
}
