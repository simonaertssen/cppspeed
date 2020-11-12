#ifndef KARATSUBA_H
#define KARATSUBA_H

#include <math.h>
using namespace std;

int number_size(unsigned long long n){
  int count = 0;
  while (n > 0){
    count++;
    n /= 10;
  }
  return count;
}

int number_size(unsigned long long *n){
  int count = 0;
  while (*n > 0){
    count++;
    *n /= 10;
  }
  return count;
}

double karatsuba_multiplication(double X, double Y){
  if (X < 10 && Y < 10) return X * Y;

  double size, n, p, a, b, c, d, ac, bd, e;
  size = (double)fmax(number_size(X), number_size(Y));

  n = (double)ceil(size / 2.0);
  p = (double)pow(10, n);
  a = (double)floor(X / (double)p);
  b = fmod(X, p);
  c = (double)floor(Y / (double)p);
  d = fmod(Y, p);

  ac = karatsuba_multiplication(a, c);
  bd = karatsuba_multiplication(b, d);
  e = karatsuba_multiplication(a + b, c + d) - ac - bd;

  return (double)(pow(10 * 1L, 2 * n) * ac + pow(10 * 1L, n) * e + bd);
}


unsigned long long *karatsuba_multiplication(unsigned long long *X, unsigned long long *Y){
  unsigned long long *result = NULL;
  if (*X < 10 && *Y < 10){
    *result = (*X) * (*Y);
    return result;
  }

  unsigned long long size, n, p, a, b, c, d, ac, bd, e;
  size = (unsigned long long)fmax(number_size(*X), number_size(*Y));

  n = (unsigned long long)ceil(size / 2.0);
  p = (unsigned long long)pow(10, n);
  a = (unsigned long long)floor(*X / (unsigned long long)p);
  b = *X % p;
  c = (unsigned long long)floor(*Y / (unsigned long long)p);
  d = *Y % p;

  ac = karatsuba_multiplication(a, c);
  bd = karatsuba_multiplication(b, d);
  e = karatsuba_multiplication(a + b, c + d) - ac - bd;

  // return the equation
  *result = (unsigned long long)(pow(10 * 1L, 2 * n) * ac + pow(10 * 1L, n) * e + bd);
  return result;
}


#endif /* KARATSUBA_H */
