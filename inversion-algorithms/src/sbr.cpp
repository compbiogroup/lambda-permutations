#include "../include/sbr.h"

SbR::SbR():Problem(){}

SbR::SbR(vector<int> perm, int lambda):Problem(perm, lambda){}

int SbR::sort(){
  // show_pi();
  int distance = 0;
  while(this->inv_pi > 0){
    int best_i, best_j, best_inv;
    best_i = best_j = best_inv = 0;
    for(int i = 1; i <= n; i++){
      int inv_variation = 0;
      for(int j = i; (j-i+1) <= this->lambda && j<=n ;j++){
        vector<int> aux = apply_uns_reversal(this->pi, i, j);

        inv_variation += calc_inv_individual(i, j-1, j);
        
        if(is_lambda(aux, i, j) && inv_variation > best_inv){
          best_i = i;
          best_j = j;
          best_inv = inv_variation;
        }
      }
    }
    //print_reversal(best_i,best_j);
    this->pi = apply_uns_reversal(this->pi, best_i, best_j);
    //print_permutation(pi); 
    distance++;
    this->update_inv();
  }

  // this->show_pi();
  return distance;
}

int SbR::lower_bound_bp(){
  int total_bp = this->calc_rev_bp(); 
  return ceil(total_bp/2.); 
}

int SbR::lower_bound_inv(){
  this->update_inv();
  int max_variation = (lambda*(lambda-1))/2;
  return ceil(this->inv_pi/(max_variation*1.0));
}

int SbR::lower_bound(){
  return max(lower_bound_bp(), lower_bound_inv());
}
