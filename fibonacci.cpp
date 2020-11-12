#include <iostream>
#include "timer.h"
using namespace std;

// Investigate which computing approaches compute the fibonacci number the fastest.
unsigned int fibonacci_iteration(unsigned int n);
unsigned int fibonacci_recursion(unsigned int n);

int main(int argc, char *argv[])
{
    cout << "Testing fibonacci algorithms:" << endl;
    int i, n = 15;
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
    for (i = arr[MAXNUM-1]-1; i >= 0; i--) cout << *(arr + i);
    cout << endl << endl;

    cout << "This method is also precise to up to " << MAXNUM << " digits:" << endl;
    arr[0] = 50;
    factorial_precision(arr);
    cout << "Precision:  " << 50 << "! = ";
    for (i = arr[MAXNUM-1]-1; i >= 0; i--) cout << *(arr + i);
    cout << endl << endl;

    unsigned int maxevals = 1.0e6;
    cout << "The results are correct, let's time the performance for " << maxevals << " evaluations:" << endl;
    cout << "Iteration:  "; timeme(factorial_iteration, n, maxevals);
    cout << "Recursion:  "; timeme(factorial_recursion, n, maxevals);
    cout << "Accumulate: "; timeme(factorial_accumulate, n, maxevals);
    cout << "Precision:  "; timeme(factorial_precision, arr, maxevals);

    return 0;
}

unsigned long long fibonacci_iteration(unsigned int n){
  unsigned long result = 1;
  if (n < 2) return result;

  int i;
  for (i = 2; i < n+1; i++){
    result *= i;
  }
  return result;
}


unsigned long long fibonacci_recursion(unsigned int n){
  if (n == 0){
     return 1;
  }
  return n*factorial_recursion(n-1);
}
