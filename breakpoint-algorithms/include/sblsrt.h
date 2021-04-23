#ifndef __SBLSRT_H
#define __SBLSRT_H
#include "sblt.h"

class SbLSRT : public SbLT {
  public: 
    SbLSRT (); 
    SbLSRT (vector<int> perm, int lambda); 
    
    //returns the distance
    int sort ();
    int lower_bound();
    int lower_bound_inv();
    int lower_bound_bp();
};

#endif
