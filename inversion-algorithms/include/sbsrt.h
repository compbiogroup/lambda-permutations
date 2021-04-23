#ifndef __SbSRT_H
#define __SbSRT_H
#include "problem.h"

class SbSRT : public Problem {
  public:
    SbSRT ();
    SbSRT (bool is_from_identity);
    SbSRT (vector<int> perm, int lambda);
    //returns the distance
    int sort();
    int lower_bound_inv();
    int lower_bound_bp();
    int lower_bound();
};

#endif
