#include <iostream>
#include "timer.h"
using namespace std;

// Investigate which computing approaches compute the fibonacci number the fastest.
double fibonacci_iteration(unsigned int n);
double fibonacci_recursion(unsigned int n);

int main(int argc, char *argv[])
{
    cout.precision(0);
    int n = 22;

    cout << "Testing fibonacci algorithms using naive multiplication:" << endl;
    double result = fibonacci_iteration(n);
    cout << "Iteration:  " << n << "! = " << result << endl;

    result = fibonacci_recursion(n);
    cout << "Recursion:  " << n << "! = " << result << endl;


    return 0;
}

double fibonacci_iteration(unsigned int n){
  if (n == 0) return 0.0;
  if (n == 1) return 1.0;
  double prior = 1, previous = 1, current = prior + previous;
  // unsigned int i;
  // for (i = 2; i < n; i++){
  //   current = x + y;
  //   x = y;
  // }
  return current;
}


double fibonacci_recursion(unsigned int n){
  if (n == 0) return 0;
  if (n == 1) return 1;
  return fibonacci_recursion(n-1) + fibonacci_recursion(n-2);
}
