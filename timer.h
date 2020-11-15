#ifndef TIMER_H
#define TIMER_H

#include <sys/time.h>
using namespace std;

/* void timeme:
F f:                    a function handle to be called within the timing loop
X input:                input to the function f
unsigned int maxevals:  number of evaluations for the timer
*/
template <typename F, typename X>
void timeme(F f, X input, unsigned int maxevals){
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);
  ios_base::sync_with_stdio(false);

  unsigned int i;
  // unsigned long long test = 0;
  for (i = 0; i < maxevals; i++) f(input);
  // cout << "Check: " << test << endl;

  clock_gettime(CLOCK_MONOTONIC, &end);
  // Calculating total time taken by the program.
  double time_taken = ( end.tv_sec - start.tv_sec ) + ( end.tv_nsec - start.tv_nsec ) * 1.0e-9;
  cout << time_taken * 1000 << " ms" << endl;
}

#endif /* TIMER_H */
