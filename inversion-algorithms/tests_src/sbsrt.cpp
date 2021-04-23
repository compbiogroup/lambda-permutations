#include "../include/sbsrt.h"

SbSRT::SbSRT():Problem(){}

SbSRT::SbSRT(vector<int> perm, int lambda):Problem(perm, lambda){}

int SbSRT::sort(){
  int distance = 0;
  while(this->inv_pi > 0){
    int best_i, best_j, best_k, best_score;
    best_i = best_j = best_k = best_score = 0;
    int begin = 1, end = n;
    while(this->pi[begin] == begin) begin++;
    while(this->pi[end] == end) end--;

    for(int i = begin; i < end; i++){
      int inv_variation_reversals = 0;
      for(int j = i+1; (j-i+1) <= this->lambda && j<=end; j++){
        vector<int> aux = apply_sig_reversal(this->pi, i, j);
        int vec_variation_reversals = calc_vec_variation(aux, i, j);
        inv_variation_reversals += calc_inv_individual(i, j-1, j);
        //if it is not a lambda-permutation, vec_variation = -(n^2)
        if((inv_variation_reversals + vec_variation_reversals) > best_score){
          best_i = i;
          best_j = j;
          best_k = -1;
          best_score = (inv_variation_reversals + vec_variation_reversals);
        }

        int inv_variation_trans = 0;
        for(int k = j+1; (k-i) <= this->lambda && k<=end+1; k++){
          vector<int> aux = apply_transposition(this->pi, i, j, k);
          int vec_variation_transpositions = calc_vec_variation(aux, i, k-1);
          inv_variation_trans += calc_inv_individual(i, j-1, k-1);
          //if it is not a lambda-permutation, vec_variation = -(n^2)
          if((inv_variation_trans + vec_variation_transpositions) > best_score){
            best_i = i;
            best_j = j;
            best_k = k;
            best_score = (inv_variation_trans + vec_variation_transpositions);
          }
        }
      }
    }
    if(best_k != -1){
      this->pi = apply_transposition(this->pi, best_i, best_j, best_k);
    }else{
      this->pi = apply_sig_reversal(this->pi, best_i, best_j);
    }
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
    distance+=this->neg_pi;
  }
  this->update_neg();

  // this->show_pi();
  return distance;
}

int SbSRT::lower_bound_inv(){
  this->update_inv();
  this->update_vecs();
  int max_variation = (lambda*(lambda-1))/2;
  return
    ceil((this->inv_pi+this->vec_even_neg+this->vec_odd_pos)/(max_variation*1.
          + lambda)) ; 
}

int SbSRT::lower_bound_bp(){
  int total_bp = calc_transp_bp(); 
  return ceil(total_bp/3.);
}

int SbSRT::lower_bound(){
  return max(lower_bound_bp(), lower_bound_inv());
}
