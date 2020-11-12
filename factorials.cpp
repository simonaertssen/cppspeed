#include <iostream>
#include "timer.h"
using namespace std;
#define MAXNUM 500

// Investigate which computing approaches compute the factorial function the fastest.
unsigned long long factorial_iteration(short n);
unsigned long long factorial_recursion(short n);
unsigned long long accumulator(short n, unsigned long long acc);
unsigned long long factorial_accumulate(short n);
void factorial_precision(int *result);

int main(int argc, char *argv[])
{
    cout << "Testing factorial algorithms:" << endl;
    short n = 15;
    unsigned long long result;
    result = factorial_iteration(n);
    cout << "Iteration:  " << n << "! = " << result << endl;

    result = factorial_recursion(n);
    cout << "Recursion:  " << n << "! = " << result << endl;

    result = factorial_accumulate(n);
    cout << "Accumulate: " << n << "! = " << result << endl;

    int *arr = new int[MAXNUM];
    arr[0] = n;
    factorial_precision(arr);
    cout << "Precision:  " << n << "! = ";
    int i;
    for (i = arr[MAXNUM-1]-1; i >= 0; i--) cout << *(arr + i);
    cout << endl << endl;

    cout << "This method is also precise to up to " << MAXNUM << " digits:" << endl;
    arr[0] = 50;
    factorial_precision(arr);
    cout << "Precision:  " << 50 << "! = ";
    for (i = arr[MAXNUM-1]-1; i >= 0; i--) cout << *(arr + i);
    cout << endl << endl;

    unsigned int maxevals = 1.0e7;
    cout << "The results are correct, let's time the performance for " << maxevals << " evaluations:" << endl;
    cout << "Iteration:  "; timeme(factorial_iteration, n, maxevals);
    cout << "Recursion:  "; timeme(factorial_recursion, n, maxevals);
    cout << "Accumulate: "; timeme(factorial_accumulate, n, maxevals);
    cout << "Precision:  "; timeme(factorial_precision, arr, maxevals);

    return 0;
}

unsigned long long factorial_iteration(short n){
  unsigned long result = 1;
  if (n < 2) return result;

  short i;
  for (i = 2; i < n+1; i++){
    result *= i;
  }
  return result;
}


unsigned long long factorial_recursion(short n){
  if (n == 0){
     return 1;
  }
  return n*factorial_recursion(n-1);
}


unsigned long long accumulator(short n, unsigned long long acc){
  if (n == 0){
    return acc;
  } else {
    return accumulator(n - 1, n*acc);
  }
}


unsigned long long factorial_accumulate(short n){
  unsigned long long start = 1;
  return accumulator(n, start);
}


void factorial_precision(int *result){
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
