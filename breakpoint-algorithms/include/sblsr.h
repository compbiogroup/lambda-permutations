#ifndef __SBLSR_H
#define __SBLSR_H
#include "sblt.h"

class SbLSR : public SbLT {
  private:
    int get_best_start_reversal(int end_rev);
    int revert_all_decreasing_strips();
  public: 
    SbLSR (); 
    SbLSR (vector<int> perm, int lambda); 
    //returns the distance
    int sort ();
    int sort_greedy ();
    int lower_bound(); 
    int lower_bound_inv();
    int lower_bound_bp();
};

#endif
