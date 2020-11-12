#ifndef TIMER_H // include guard
#define TIMER_H

#include <sys/time.h>
using namespace std;

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
  cout << time_taken << "s" << endl;
}

#endif /* TIMER_H */
