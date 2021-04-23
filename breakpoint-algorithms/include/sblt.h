#ifndef __SBLT_H
#define __SBLT_H
#include "limitedsizeproblem.h"

class SbLT : public LimitedSizeProblem {
  
  protected:
    void update_total_bp(); 
    vector<int> strip_ending_at (int end_pos);
    vector<int> strip_starting_at (int start_pos);

  public: 
    SbLT (); 
    SbLT (vector<int> perm, int lambda); 
    //returns the distance
    virtual int sort ();
    void reset(vector<int> perm, int lambda); 
    virtual int lower_bound();
    virtual int lower_bound_inv();
    virtual int lower_bound_bp();
};

#endif
