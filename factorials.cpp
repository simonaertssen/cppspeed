#include <iostream>
#include "timer.h"
using namespace std;

// Investigate which computing approaches compute the factorial function the fastest.
#define MAXNUM 500
unsigned long long factorial_iteration(unsigned int n);
unsigned long long factorial_recursion(unsigned long n);

int main(int argc, char *argv[])
{
    cout << "Testing factorial algorithms:" << endl;
    unsigned int ni = 60;
    unsigned long long result;
    result = factorial_iteration(ni);
    cout << "Iteration: " << ni << "! = " << result << endl;

    unsigned long nl = 60;
    result = factorial_recursion(nl);
    cout << "Recursion: " << nl << "! = " << result << endl;

    cout << "The results are correct, let's time the performance:" << endl;
    unsigned int maxevals = 1.0e8;
    timeme(factorial_iteration, ni, maxevals);
    timeme(factorial_recursion, nl, maxevals);

    return 0;
}

unsigned long long factorial_iteration(unsigned int n){
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
