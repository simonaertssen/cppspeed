#include <iostream>
#include "timer.h"
using namespace std;

// Investigate which computing approaches compute the fibonacci number the fastest.
unsigned long long fibonacci_iteration(unsigned int n);
unsigned long long fibonacci_recursion(unsigned int n);

int main(int argc, char *argv[])
{
    cout << "Testing fibonacci algorithms:" << endl;
    unsigned int n = 15;
    unsigned long long result;
    result = fibonacci_iteration(n);
    cout << "Iteration:  " << n << "! = " << result << endl;

    result = fibonacci_recursion(n);
    cout << "Recursion:  " << n << "! = " << result << endl;

    // result = factorial_accumulate(n);
    // cout << "Accumulate: " << n << "! = " << result << endl;
    //
    // int *arr = new int[MAXNUM];
    // arr[0] = n;
    // factorial_precision(arr);
    // cout << "Precision:  " << n << "! = ";
    // for (i = arr[MAXNUM-1]-1; i >= 0; i--) cout << *(arr + i);
    // cout << endl << endl;
    //
    // cout << "This method is also precise to up to " << MAXNUM << " digits:" << endl;
    // arr[0] = 50;
    // factorial_precision(arr);
    // cout << "Precision:  " << 50 << "! = ";
    // for (i = arr[MAXNUM-1]-1; i >= 0; i--) cout << *(arr + i);
    // cout << endl << endl;
    //
    // unsigned int maxevals = 1.0e6;
    // cout << "The results are correct, let's time the performance for " << maxevals << " evaluations:" << endl;
    // cout << "Iteration:  "; timeme(factorial_iteration, n, maxevals);
    // cout << "Recursion:  "; timeme(factorial_recursion, n, maxevals);
    // cout << "Accumulate: "; timeme(factorial_accumulate, n, maxevals);
    // cout << "Precision:  "; timeme(factorial_precision, arr, maxevals);

    return 0;
}

unsigned long long fibonacci_iteration(unsigned int n){
  if (n == 0) return 0;
  if (n == 1) return 1;
  unsigned long long x = 1, y = 1;
  unsigned int i;
  for (i = 0; i < n; i++){

  }
  return x;
}


unsigned long long fibonacci_recursion(unsigned int n){
  if (n == 0) return 0;
  if (n == 1) return 1;
  return factorial_recursion(n-1) + fibonacci_recursion(n-2);
}
