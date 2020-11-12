#include <iostream>
#include "timer.h"
using namespace std;

// Investigate which computing approaches compute the factorial function the fastest.
#define MAXNUM 500
unsigned long long factorial_iteration(unsigned long n);
unsigned long long factorial_recursion(unsigned long n);
unsigned long long factorial_precision(unsigned long n);

int main(int argc, char *argv[])
{
    cout << "Testing factorial algorithms:" << endl;
    unsigned long n = 60;
    unsigned long long result;
    result = factorial_iteration(n);
    cout << "Iteration: " << n << "! = " << result << endl;

    result = factorial_recursion(n);
    cout << "Recursion: " << n << "! = " << result << endl;

    unsigned int maxevals = 1.0e8;
    cout << "The results are correct, let's time the performance for " << maxevals << " evaluations:" << endl;
    cout << "Iteration: "; timeme(factorial_iteration, n, maxevals);
    cout << "Recursion: "; timeme(factorial_recursion, n, maxevals);

    return 0;
}

unsigned long long factorial_iteration(unsigned long n){
  unsigned long result = 1;
  if (n < 2) return result;

  unsigned long i;
  for (i = 2; i < n+1; i++){
    result *= i;
  }
  return result;
}

unsigned long long factorial_recursion(unsigned long n){
  if (n == 0){
     return 1;
  }
  return n*factorial_recursion(n-1);
}

unsigned long long factorial_precision(unsigned int n){
  return n;
}
