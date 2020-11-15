#include <iostream>
#include "timer.h"

using namespace std;
#define MAXNUM 500

// Investigate which computing approaches compute the n-th fibonacci number the fastest.
// When using the IEEE-754 64-bit double precision floating point number type,
// one can only expect a precision of 53 bits in the mantissa, which corresponds
// to about log(2^53) ~ 15.955 decimal digits.
// However, we can use some arbitrary precision arithmetic to produce the right results quickly.

double fibonacci_iteration(unsigned int n);
double *fibonacci_iteration_p(unsigned int *n);
double fibonacci_recursion(unsigned int n);
void fibonacci_precision(int *result);

int main(int argc, char *argv[])
{
    cout.precision(0);
    unsigned int n = 10;

    cout << "Testing fibonacci algorithms using naive multiplication:" << endl;
    double result = fibonacci_iteration(n);
    cout << "Iteration:  fib(" << n << ") = " << fixed << result << endl;

    double *resultp = fibonacci_iteration_p(&n);
    cout << "Iteration*: fib(" << n << ") = " << *resultp << endl;

    result = fibonacci_recursion(n);
    cout << "Recursion:  fib(" << n << ") = " << result << endl;

    cout << "Testing fibonacci algorithms using arbitrary precision:" << endl;
    int *arr = new int[MAXNUM];
    arr[0] = n;
    fibonacci_precision(arr);
    cout << "Precision:  fib(" << n << ") = ";
    int i;
    for (i = arr[MAXNUM-1]-1; i >= 0; i--) cout << *(arr + i);
    cout << endl << endl;

    unsigned int maxevals = 1.0e9;
    cout.precision(5);
    cout << "Let's time the performance for " << maxevals << " evaluations:" << endl;
    cout << "Iteration:  "; timeme(fibonacci_iteration, n, maxevals);
    cout << "Iteration*: "; timeme(&fibonacci_iteration_p, &n, maxevals);
    // cout << "Recursion:  "; timeme(fibonacci_recursion, n, maxevals);

    return 0;
}

double fibonacci_iteration(unsigned int n){
  double previous = 1, current = 0;
  unsigned int i;
  for (i = 0; i < n; i++){
    current += previous;
    previous = current - previous;
  }
  return current;
}


double *fibonacci_iteration_p(unsigned int *n){
  double startprevious = 1, startcurrent = 0;
  double *previous = &startprevious, *current = &startcurrent;
  unsigned int i;
  for (i = 0; i < *n; i++){
    *current += (*previous);
    *previous = *current - (*previous);
  }
  return current;
}


double fibonacci_recursion(unsigned int n){
  if (n == 0) return 0;
  if (n == 1) return 1;
  return fibonacci_recursion(n-1) + fibonacci_recursion(n-2);
}


// void factorial_precision(int *result){
//   int n = result[0];
//   result[0] = 1;
//   int i, j, prod, carry, size = 1;
//
//   for (i = 2; i <= n; i++){
//     carry = 0;
//     for (j = 0; j < size; j++){
//       prod = result[j] * i + carry;
//       result[j] = prod % 10;
//       carry  = prod/10;
//     }
//     while (carry > 0){
//       if (size > MAXNUM){
//         printf("Overflow encountered. Exiting. \n");
//         return;
//       }
//       result[size] = carry%10;
//       carry = carry/10;
//       size++;
//     }
//   }
//   result[MAXNUM-1] = size;
// }


void fibonacci_precision(int *current){
  int n = current[0];
  current[0] = 0;
  int *previous = new int[MAXNUM];
  previous[0] = 1;
  int i, j, res, carry, previoussize = 1, currentsize = 1;

  for (i = 0; i < n; i++){
    // Perform addition: current += previous
    carry = 0;
    for (j = 0; j < currentsize; j++){
        res = current[j] + previous[j] + carry;
        current[j] = res % 10;
        carry = res/10;
    }
    while (carry > 0){
      if (currentsize > MAXNUM){
        printf("Overflow encountered. Exiting. \n");
        return;
      }
      current[currentsize] = carry%10;
      carry = carry/10;
      currentsize++;
    }
    // Perform subtraction: previous = current - previous
    carry = 0;
    for (j = 0; j < previoussize; j++){
        res = current[j] - previous[j] + carry;
        previous[j] = res % 10;
        carry = res/10;
    }
    while (carry > 0){
      if (previoussize > MAXNUM){
        printf("Overflow encountered. Exiting. \n");
        return;
      }
      previous[previoussize] = carry%10;
      carry = carry/10;
      previoussize++;
    }
  }
  current[MAXNUM-1] = currentsize;
}
