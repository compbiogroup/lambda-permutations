#ifndef __SbR_H
#define __SbR_H
#include "problem.h"

class SbR : public Problem {
  public:
    SbR ();
    SbR (bool is_from_identity);
    SbR (vector<int> perm, int lambda);
    //returns the distance
    int sort();
    int sort_verbose();
    int lower_bound_inv();
    int lower_bound_bp();
    int lower_bound();
};

#endif
