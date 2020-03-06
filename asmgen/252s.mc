  ! " # $ % & ' ( ) * + , 
- . / 0 1 2 3 4 5 6 7 8 9 : ; 
< = > ? @ A B C D E F G H I J 
K L M N O P Q R S T U V W X Y 
Z [ \ ] ^ _ ` a b c d e f g h 
i j k l m n o p q r s t u v w 
x y z { | } ~  
   ¡ ¢ £ ¤ 
¥ ¦ § ¨ © ª « ¬ ­ ® ¯ ° ± ² ³ 
´ µ ¶ · ¸ ¹ º » ¼ ½ ¾ ¿ À Á Â 
Ã Ä Å Æ Ç È É Ê Ë Ì Í Î Ï Ð Ñ 
Ò Ó Ô Õ Ö × Ø Ù Ú Û Ü Ý Þ ß à 
á â ã ä å æ ç è é ê ë ì í î ï 
ð ñ ò ó ô õ ö ÷ ø ù ú û ü ý þ 
"hello there"' xy 1.3e+10- /* comment here */
412.3e+3$1+e3
/*
   hello there */
56 # + x
/* A program to perform Euclid's
   Algorithm to compute gcd. */

int gcd (int u, int v)
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

/* A program to perform selection sort on a 
   10 element array. */

int x[10];

int minloc (int a[], int low, int high)
{
  int i; int x; int k;
  k = low;
  x = a[low];
  i = low + 1;
  while (i < high)
  {
    if (a[i] < x)
    {  
      x = a[i];
      k = i;
    }
    i = i + 1;
  }
  return k;
}

void sort (int a[], int low, int high)
{
  int i; int k;
  i = low;
  while (i < high-1)
  {
    int t;
    k = minloc(a, i, high);
    t = a[k];
    a[k] = a[i];
    a[i] = t;
    i = i + 1;
  }
}

void main( void )
{
  int i;
  i = 0;
  while (i < 10)
  {
    x[i] = input();
    i = i + 1;
  }
  sort(x, 0, 10);
  i = 0;
  while ( i < 10)
  {
    output(x[i]);
    i = i + 1;
  }
}

/* Hello there

