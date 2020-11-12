#include <iostream>
#include "timer.h"
#include "karatsuba.h"

using namespace std;
#define MAXNUM 500

// Investigate which computing approaches compute the factorial function the fastest.
// Some computations are only accurate to up to 15 digits due to the double type,
// but using the Karatsuba algorithm we can increase the precision.

double factorial_iteration(short n);
double *factorial_iteration_pointer(short *n);
double factorial_recursion(short n);
double accumulator(short n, double acc);
double factorial_accumulate(short n);

double factorial_iteration_karatsuba(short n);
unsigned long long *factorial_iteration_pointer_karatsuba(short *n);
void factorial_precision(short *result);

int main(int argc, char *argv[]){
    cout.precision(0);
    short n = 20;

    cout << "Testing factorial algorithms using naive multiplication:" << endl;
    double result = factorial_iteration(n);
    cout << "Iteration:  " << n << "! = " << fixed << result << endl;

    double *resultp = factorial_iteration_pointer(&n);
    cout << "Iteration*: " << n << "! = " << fixed << *resultp << endl;

    result = factorial_recursion(n);
    cout << "Recursion:  " << n << "! = " << result << endl;

    result = factorial_accumulate(n);
    cout << "Accumulate: " << n << "! = " << result << endl;


    cout << "Testing factorial algorithms using smart multiplication:" << endl;
    double smart_result = factorial_iteration_karatsuba(n);
    cout << "Iteration:  " << n << "! = " << fixed << smart_result << endl;

    unsigned long long *smart_resultp = factorial_iteration_pointer_karatsuba(&n);
    cout << "Iteration:  " << n << "! = " << fixed << *smart_resultp << endl;

    short *arr = new short[MAXNUM];
    arr[0] = n;
    factorial_precision(arr);
    cout << "Precision:  " << n << "! = ";
    int i;
    for (i = arr[MAXNUM-1]-1; i >= 0; i--) cout << *(arr + i);
    cout << endl << endl;

    // cout << "This method is currently precise to up to " << MAXNUM << " digits:" << endl;
    // arr[0] = 200;
    // factorial_precision(arr);
    // cout << "Precision:  " << 50 << "! = ";
    // for (i = arr[MAXNUM-1]-1; i >= 0; i--) cout << *(arr + i);
    // cout << endl << endl;

    unsigned int maxevals = 1.0e4;
    cout.precision(5);
    cout << "Let's time the performance for " << maxevals << " evaluations:" << endl;
    cout << "Iteration:  "; timeme(factorial_iteration, n, maxevals);
    cout << "Iteration*: "; timeme(&factorial_iteration_pointer, &n, maxevals);
    cout << "Recursion:  "; timeme(factorial_recursion, n, maxevals);
    cout << "Accumulate: "; timeme(factorial_accumulate, n, maxevals);
    cout << "Karatsuba:  "; timeme(factorial_iteration_karatsuba, n, maxevals);
    cout << "Karatsuba*: "; timeme(&factorial_iteration_pointer_karatsuba, &n, maxevals);
    cout << "Precision:  "; timeme(factorial_precision, arr, maxevals);

    return 0;
}


double factorial_iteration(short n){
  double result = 1;
  if (n < 2) return result;

  short i;
  for (i = 2; i < n+1; i++){
    result *= i;
  }
  return result;
}

double factorial_iteration_karatsuba(short n){
  double result = 1;
  if (n < 2) return result;

  double i;
  for (i = 2; i < n+1; i++){
    result = karatsuba_multiplication(result, i);
  }
  return result;
}

double *factorial_iteration_pointer(short *n){
  double start = 1;
  double *result = &start;
  if (*n < 2) return result;

  short i;
  for (i = 2; i < *n+1; i++){
    (*result) *= i;
  }
  return result;
}

unsigned long long *factorial_iteration_pointer_karatsuba(short *n){
  unsigned long long start = 1;
  unsigned long long *result = &start, *mult = NULL;
  if (*n < 2) return result;

  unsigned long long i;
  for (i = 2; i < *n+1; i++){
    mult = &i;
    *result = karatsuba_multiplication(*result, *mult);
  }
  return result;
}

double factorial_recursion(short n){
  if (n == 0){
     return 1;
  }
  return n*factorial_recursion(n-1);
}


double accumulator(short n, double acc){
  if (n == 0){
    return acc;
  } else {
    return accumulator(n - 1, n*acc);
  }
}


double factorial_accumulate(short n){
  double start = 1;
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
