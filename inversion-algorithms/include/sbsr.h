#ifndef __SbSR_H
#define __SbSR_H
#include "problem.h"

class SbSR : public Problem {
  public:
    SbSR ();
    SbSR (vector<int> perm, int lambda);
    //returns the distance
    int sort();
    int lower_bound_inv();
    int lower_bound_bp();
    int lower_bound(); 
};

#endif
