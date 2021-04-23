#ifndef __LIMITEDSIZEPROBLEM_H
#define __LIMITEDSIZEPROBLEM_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "operations.h"

class LimitedSizeProblem{
  protected:
    int lambda; 
    int total_bp; // number of breakpoints in pi 
    int n;
    int inv_pi; 
    int vec_even_neg;
    int vec_odd_pos;
    vector<int> pi; 
    //swap two elements by applying a sequence of lambda operations
    //returns size of that sequence
    void update_entropy();
    void update_inv (); 
    void update_neg();
    void update_vecs();
    bool is_lambda(vector<int> perm, int begin, int end);
    int get_first_out_of_place(); 
    void reset_problem(vector<int> perm, int lambda); 
  public:
    LimitedSizeProblem ();
    LimitedSizeProblem (vector<int> perm, int lambda);
    virtual int sort(){}; //all problems should implement this function
    int get_lambda();
    int get_number_breakpoints();
    vector<int> get_pi();
    int get_inv();
    void show_pi();
};

#endif
