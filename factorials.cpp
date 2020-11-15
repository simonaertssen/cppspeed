#include <iostream>
#include "timer.h"

using namespace std;
#define MAXNUM 500

// Investigate which computing approaches compute the factorial function the fastest.
// Wehn using the IEEE-754 64-bit double precision floating point number type,
// one can only expect a precision of 53 bits in the mantissa, which corresponds
// to about log(2^53) ~ 15.955 decimal digits.
// However, we can use some

double factorial_iteration(int n);
double *factorial_iteration_p(int *n);
double factorial_recursion(int n);
double accumulator(int n, double acc);
double factorial_accumulate(int n);

void factorial_precision(int *result);

int main(int argc, char *argv[]){
    cout.precision(0);
    int n = 22;

    cout << "Testing factorial algorithms using naive multiplication:" << endl;
    double result = factorial_iteration(n);
    cout << "Iteration:  " << n << "! = " << fixed << result << endl;

    double *resultp = factorial_iteration_p(&n);
    cout << "Iteration*: " << n << "! = " << fixed << *resultp << endl;

    result = factorial_recursion(n);
    cout << "Recursion:  " << n << "! = " << result << endl;

    result = factorial_accumulate(n);
    cout << "Accumulate: " << n << "! = " << result << endl;
    cout << endl << endl;

    cout << "Testing factorial algorithms using arbitrary precision:" << endl;
    int *arr = new int[MAXNUM];
    arr[0] = n;
    factorial_precision(arr);
    cout << "Precision:  " << n << "! = ";
    int i;
    for (i = arr[MAXNUM-1]-1; i >= 0; i--) cout << *(arr + i);
    cout << endl << endl;

    unsigned int maxevals = 1.0e3;
    cout.precision(5);
    cout << "Let's time the performance for " << maxevals << " evaluations:" << endl;
    cout << "Iteration:  "; timeme(factorial_iteration, n, maxevals);
    cout << "Iteration*: "; timeme(&factorial_iteration_p, &n, maxevals);
    cout << "Recursion:  "; timeme(factorial_recursion, n, maxevals);
    cout << "Accumulate: "; timeme(factorial_accumulate, n, maxevals);
    cout << "Precision:  "; timeme(factorial_precision, arr, maxevals);

    return 0;
}


double factorial_iteration(int n){
  double result = 1;
  if (n < 2) return result;

  int i;
  for (i = 2; i < n+1; i++){
    result *= i;
  }
  return result;
}


double *factorial_iteration_p(int *n){
  double start = 1;
  double *result = &start;
  if (*n < 2) return result;

  int i;
  for (i = 2; i < *n+1; i++){
    (*result) *= i;
  }
  return result;
}


double factorial_recursion(int n){
  if (n == 0){
     return 1;
  }
  return n*factorial_recursion(n-1);
}


double accumulator(int n, double acc){
  if (n == 0){
    return acc;
  } else {
    return accumulator(n - 1, n*acc);
  }
}


double factorial_accumulate(int n){
  double start = 1;
  return accumulator(n, start);
}


void factorial_precision(int *result){
  int n = result[0];
  result[0] = 1;
  int i, j, prod, carry, size = 1;

  for (i = 2; i <= n; i++){
    carry = 0;
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
