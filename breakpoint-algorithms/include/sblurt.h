#ifndef __SBLURT_H
#define __SBLURT_H
#include "sblur.h"

class SbLURT : public SbLUR {
  public: 
    SbLURT (); 
    SbLURT (vector<int> perm, int lambda); 
    //returns the distance
    int sort ();
    int lower_bound(); 
    int lower_bound_inv();
    int lower_bound_bp();
};

#endif
