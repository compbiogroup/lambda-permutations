#include "../include/sbsr.h"

SbSR::SbSR():Problem(){}

SbSR::SbSR(vector<int> perm, int lambda):Problem(perm, lambda){}

int SbSR::sort(){
  int distance = 0;
  while(this->inv_pi > 0){
    int best_i, best_j, best_score;
    best_i = best_j = best_score = 0;
    for(int i = 1; i <= n; i++){
      int inv_variation = 0;
      for(int j = i; (j-i+1) <= this->lambda && j<=n ;j++){
        vector<int> aux = apply_sig_reversal(this->pi, i, j);
        int vec_variation = calc_vec_variation(aux, i, j);
        inv_variation += calc_inv_individual(i, j-1, j);
        //if it is not a lambda-permutation, vec_variation = -(n^2)
        if((inv_variation + vec_variation) > best_score){
          best_i = i;
          best_j = j;
          best_score = (inv_variation + vec_variation);
        }
      }
    }

    this->pi = apply_sig_reversal(this->pi, best_i, best_j);
    distance++;
    this->update_inv();
  }

  this->update_neg();
  if(this->neg_pi > 0){
    for(int i = 1; i <= n; i++){
      if(this->pi[i] < 0){
        this->pi = apply_sig_reversal(this->pi, i, i);
      }
    }
    distance += this->neg_pi;
  }
  this->update_neg();

  // this->show_pi();
  return distance;
}

int SbSR::lower_bound_inv(){
  this->update_inv();
  this->update_vecs();
  int max_variation = (lambda*(lambda-1))/2;
  return
    ceil((this->inv_pi+this->vec_even_neg+this->vec_odd_pos)/(max_variation*1. + lambda)) ; 
}

int SbSR::lower_bound_bp(){ 
  int total_bp = calc_transp_bp(); 
  return ceil(total_bp/2.);
}

int SbSR::lower_bound(){
  return max(lower_bound_bp(), lower_bound_inv()); 
}
