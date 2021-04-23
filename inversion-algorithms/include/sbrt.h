#ifndef __SbRT_H
#define __SbRT_H
#include "problem.h"

class SbRT : public Problem {
  public:
    SbRT ();
    SbRT (vector<int> perm, int lambda);
    //returns the distance
    int sort();
    int lower_bound_inv();
    int lower_bound_bp();
    int lower_bound();
};

#endif
