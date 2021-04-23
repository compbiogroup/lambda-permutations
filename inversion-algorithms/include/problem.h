#ifndef __PROBLEM_H
#define __PROBLEM_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "operations.h"

class Problem{
  protected:
    int lambda;
    int n;
    int inv_pi;
    int neg_pi;
    int vec_even_neg; 
    int vec_odd_pos; 
    vector<int> pi;
    //swap two elements by applying a sequence of lambda operations
    //returns size of that sequence
    void update_inv();
    void update_neg();
    void update_vecs();
    int calc_rev_bp(); //for SbR, SbRT and SbSRT
    int calc_transp_bp(); //for SbT and SbSR
    int calc_vec_variation(vector<int>p2, int begin, int end);
    int calc_inv_variation(vector<int>p2, int begin, int end);
    int calc_inv_individual(int begin, int end, int element);
    int calc_neg_variation(vector<int>perm, int begin, int end);
    int is_lambda(vector<int>pi2, int begin, int end);
  public:
    Problem ();
    Problem (vector<int> perm, int lambda);
    void reset(vector<int> perm, int lambda);
    int get_inv();
    int get_lambda();
    vector<int> get_pi();
    void show_pi();
};

#endif
