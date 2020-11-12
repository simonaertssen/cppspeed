#include <iostream>
#include "timer.h"
using namespace std;

// Investigate which computing approaches compute the factorial function the fastest.
#define MAXNUM 500
unsigned long long factorial_iteration(int n);
unsigned long long factorial_recursion(int n);
int factorial_precision(int n);

int main(int argc, char *argv[])
{
    cout << "Testing factorial algorithms:" << endl;
    int arr, n = 60;
    unsigned long long result;
    result = factorial_iteration(n);
    cout << "Iteration: " << n << "! = " << result << endl;

    result = factorial_recursion(n);
    cout << "Recursion: " << n << "! = " << result << endl;

    arr = factorial_precision(n);
    int i;
    cout << "Precision: " << n << "! = "; for (i = res_size-1; i>=0; i--)
        cout << res[i];

    unsigned int maxevals = 1.0e8;
    cout << "The results are correct, let's time the performance for " << maxevals << " evaluations:" << endl;
    cout << "Iteration: "; timeme(factorial_iteration, n, maxevals);
    cout << "Recursion: "; timeme(factorial_recursion, n, maxevals);

    return 0;
}

unsigned long long factorial_iteration(int n){
  unsigned long result = 1;
  if (n < 2) return result;

  int i;
  for (i = 2; i < n+1; i++){
    result *= i;
  }
  return result;
}

unsigned long long factorial_recursion(int n){
  if (n == 0){
     return 1;
  }
  return n*factorial_recursion(n-1);
}

void factorial_precision(int n){
  int res[MAX];
  res[0] = 1;
  int i, j, carry, prod, size = 1;

  for (i = 2; i <= n; i++){
    for (j = 0; j < size; j++){
      carry = 0;
      prod = res[j] * i + carry;
      res[i] = prod % 10;
      carry  = prod/10;
    }
    while (carry){
      res[size] = carry%10;
      carry = carry/10;
      size++;
    }
  }
}
