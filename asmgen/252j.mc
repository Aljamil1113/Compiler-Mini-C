void multiply(int k, int x[], int n)
{
  int i;
  i = 0;
  while (i < n)
  {
    x[i] = k * x[i]; 
    i = i + 1;
  }
}

void main(void)
{
  int x[5]; int y;

  x[0] = 3;
  x[1] = x[0] - 5;
  x[2] = x[1] + x[0];
  x[3] = 10;
  x[4] = -1;

  multiply(3, x, 5);

  y = 0;
  while (y < 5)
  {
    output(x[y]);
    y = y + 1;
  }
}
