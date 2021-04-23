#ifndef __SbT_H
#define __SbT_H
#include "problem.h"

class SbT : public Problem {
  public:
    SbT ();
    SbT (vector<int> perm, int lambda);
    //returns the distance
    int sort();
    int lower_bound_inv();
    int lower_bound_bp();
    int lower_bound();
};

#endif
