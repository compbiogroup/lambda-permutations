#ifndef __SBLUR_H
#define __SBLUR_H
#include "limitedsizeproblem.h"

class SbLUR : public LimitedSizeProblem {
  protected:
    void update_total_bp(); 
    vector<int> strip_ending_at (int end_pos);
    vector<int> strip_starting_at (int start_pos);
    int revert_all_decreasing_strips();
    int get_best_start_reversal(int end_rev);

  public: 
    SbLUR (); 
    SbLUR (vector<int> perm, int lambda); 
    //returns the distance
    void reset(vector<int>perm, int lamb); 
    virtual int sort ();
    virtual int lower_bound();
    virtual int lower_bound_bp();
    virtual int lower_bound_inv();
    int sort_greedy ();
};

#endif
