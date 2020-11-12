#include <iostream>
#include "timer.h"
using namespace std;
#define MAXNUM 500

// Investigate which computing approaches compute the factorial function the fastest.
// These computations are only accurate to up to 18 digits.
long double factorial_iteration(short n);
long double *factorial_iteration_pointer(short *n);
long double factorial_recursion(short n);
long double accumulator(short n, long double acc);
long double factorial_accumulate(short n);
void factorial_precision(short *result);

int main(int argc, char *argv[]){
    cout.precision(0);

    cout << "Testing factorial algorithms:" << endl;
    short n = 30;
    long double result;
    long double *resultp;

    result = factorial_iteration(n);
    cout << "Iteration:  " << n << "! = " << fixed << result << endl;

    resultp = factorial_iteration_pointer(&n);
    cout << "Iteration*: " << n << "! = " << fixed << result << endl;

    result = factorial_recursion(n);
    cout << "Recursion:  " << n << "! = " << result << endl;

    result = factorial_accumulate(n);
    cout << "Accumulate: " << n << "! = " << result << endl;

    short *arr = new short[MAXNUM];
    arr[0] = n;
    factorial_precision(arr);
    cout << "Precision:  " << n << "! = ";
    int i;
    for (i = arr[MAXNUM-1]-1; i >= 0; i--) cout << *(arr + i);
    cout << endl << endl;

    cout << "This method is also precise to up to " << MAXNUM << " digits:" << endl;
    arr[0] = 200;
    factorial_precision(arr);
    cout << "Precision:  " << 50 << "! = ";
    for (i = arr[MAXNUM-1]-1; i >= 0; i--) cout << *(arr + i);
    cout << endl << endl;

    unsigned int maxevals = 1.0e7;
    cout.precision(5);
    cout << "The results are correct, let's time the performance for " << maxevals << " evaluations:" << endl;
    cout << "Iteration:  "; timeme(factorial_iteration, n, maxevals);
    cout << "Iteration*: "; timeme(&factorial_iteration_pointer, &n, maxevals);
    cout << "Recursion:  "; timeme(factorial_recursion, n, maxevals);
    cout << "Accumulate: "; timeme(factorial_accumulate, n, maxevals);
    cout << "Precision:  "; timeme(factorial_precision, arr, maxevals);

    return 0;
}

long double factorial_iteration(short n){
  long double result = 1;
  if (n < 2) return result;

  short i;
  for (i = 2; i < n+1; i++){
    result *= i;
  }
  return result;
}

long double *factorial_iteration_pointer(short *n){
  long double start = 1;
  long double *result = &start;
  if (*n < 2) return result;

  short i;
  for (i = 2; i < *n+1; i++){
    (*result) *= i;
  }
  return result;
}


long double factorial_recursion(short n){
  if (n == 0){
     return 1;
  }
  return n*factorial_recursion(n-1);
}


long double accumulator(short n, long double acc){
  if (n == 0){
    return acc;
  } else {
    return accumulator(n - 1, n*acc);
  }
}


long double factorial_accumulate(short n){
  long double start = 1;
  return accumulator(n, start);
}


void factorial_precision(short *result){
  short n = result[0];
  result[0] = 1;
  int i, j, prod, carry, size = 1;

  for (i = 2; i <= n; i++){
    for (j = 0; j < size; j++){
      prod = result[j] * i + carry;
      result[j] = prod % 10;
      carry  = prod/10;
    }
    while (carry){
      result[size] = carry%10;
      carry = carry/10;
      size++;
    }
  }
  result[MAXNUM-1] = size;
}
