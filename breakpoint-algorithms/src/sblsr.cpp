#include "../include/sblsr.h"

SbLSR::SbLSR():SbLT(){} 

SbLSR::SbLSR(vector<int> perm, int lambda):SbLT(perm, lambda){
}


int SbLSR::revert_all_decreasing_strips(){
  int cnt_operation = 0; 
  //firstly, we revert all negative strips
  //note that size max of a strip is lambda-1, so operations are lambda-reversals
  int strip_start = 1, strip_end = 1; 
  //show_pi();
  for (int i = 1; i <= n; i++){ //pi[n] < pi[n+1], so line 47 works
    if (pi[i] < 0 and pi[i] == pi[i+1] - 1){
      strip_end = i+1; 
    }else{
      if (pi[strip_end]<0){
        pi = apply_sig_reversal(pi, strip_start, strip_end); 
        cnt_operation ++; 
      }
      strip_start = i+1; 
      strip_end = i+1; 
    }
  }
  update_total_bp();
  return cnt_operation;
}

int SbLSR::get_best_start_reversal(int end_rev){
  // (end_rev-start_reversal)+1 <= lambda
  for (int start = max(-lambda+end_rev+1,1); start <= end_rev; start++){
    vector<int> aux = apply_sig_reversal(pi, start, end_rev); 
    if (is_lambda(aux, start, end_rev))
      return start; 
  }
  cout << "Something was wrong in get_best_start_reversal function \n";
  return -1; 
}

int SbLSR::sort_greedy (){
  //first of all, pi should has only increasing strips
  int cnt_operation = revert_all_decreasing_strips(); 

  while (total_bp > 0){
    int j = get_first_out_of_place(); 
    int i = pi[j]; 

    vector<int> right_strip = strip_starting_at(j); 
    int sz_strip = right_strip.size();
    int sz_subseg = min ((int)right_strip.size(), lambda/2);
    int init_subseg = j; 
    int start_rev, end_rev; 

    //inside the loop, j always is the position of the first element out of place
    while (sz_strip >= 1){
      j = init_subseg; 
      end_rev = j+sz_subseg-1;
      start_rev = max(i, get_best_start_reversal(end_rev));

      while (j > start_rev){
        //print_reversal(start_rev, end_rev);
        pi = apply_sig_reversal(pi, start_rev, end_rev); 
        if (!is_lambda(pi, start_rev, end_rev))
            puts("IT IS NOT A LAMBDA PERMUTATION!");
        //print_permutation(pi);
        cnt_operation ++; 
        //see if we need to revert again elements from R
        //print_reversal(start_rev+sz_subseg, end_rev);
        pi = apply_sig_reversal(pi, start_rev+sz_subseg, end_rev);
        if (!is_lambda(pi, start_rev+sz_subseg, end_rev))
            puts("IT IS NOT A LAMBDA PERMUTATION!");
        //print_permutation(pi);
        cnt_operation ++; 
        j = start_rev; 
        end_rev = j+sz_subseg-1;
        start_rev = max(i, get_best_start_reversal(end_rev));
      }
      if (pi[i]<0){
        //print_reversal(i, i+sz_subseg-1);
        pi = apply_sig_reversal(pi, i, i+sz_subseg-1);
        if (!is_lambda(pi, i, i+sz_subseg-1))
            puts("IT IS NOT A LAMBDA PERMUTATION!");
        //print_permutation(pi);
        cnt_operation++;
      }
      sz_strip -= sz_subseg; 
      init_subseg += sz_subseg; //The remaining elements are starting at init_subseg
      i += sz_subseg; //And should be moved until position i + sz_subseg
      sz_subseg = sz_strip; 
    }
    update_total_bp (); 
  }

  return cnt_operation;
}

//returns the distance
int SbLSR::sort (){
  int cnt_operation = 0; 
  
  update_total_bp();
  while (total_bp > 0){
    int j = get_first_out_of_place(); 
    int i = pi[j]; 

    vector<int> right_strip = strip_starting_at(j); 
    int sz_strip = right_strip.size();
    int sz_subseg = min ((int)right_strip.size(), lambda/2);
    int init_subseg = j; 
    while (sz_strip >= 1){
      j = init_subseg;
      int k = max(i, j-sz_subseg);
      while (j > k){
        pi = apply_sig_reversal(pi, k, j+sz_subseg-1); 
        cnt_operation ++; 
        pi = apply_sig_reversal(pi, k+sz_subseg, j+sz_subseg-1);
        cnt_operation ++; 
        j = k; 
        k = max(i, j-sz_subseg);
      }
      if (pi[i] < 0){
        pi = apply_sig_reversal(pi, i, i+sz_subseg-1);
        cnt_operation++;
      }
      sz_strip -= sz_subseg; 
      init_subseg += sz_subseg;
      i += sz_subseg;
      sz_subseg = sz_strip; 
    }
    update_total_bp (); 
  }
  return cnt_operation;
}

int SbLSR::lower_bound_inv(){
  this->update_inv();
  this->update_vecs();
  int max_variation = (lambda*(lambda-1))/2;
  return
    ceil((this->inv_pi+this->vec_even_neg+this->vec_odd_pos)/(max_variation*1. + lambda)) ; 
}

int SbLSR::lower_bound_bp (){
  return ceil(total_bp/2.);
}

int SbLSR::lower_bound(){
  return max(lower_bound_bp(), lower_bound_inv()); 
}
