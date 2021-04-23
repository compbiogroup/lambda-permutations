#include "../include/sbrt.h"

SbRT::SbRT():Problem(){}

SbRT::SbRT(vector<int> perm, int lambda):Problem(perm, lambda){}

int SbRT::sort(){
  int distance = 0;
  while(this->inv_pi > 0){
    int best_i, best_j, best_k, best_inv;
    best_i = best_j = best_k = best_inv = 0;
    int begin = 1, end = n;
    while(abs(this->pi[begin]) == begin) begin++;
    while(abs(this->pi[end]) == end) end--;

    for(int i = begin; i < end; i++){
      int inv_variation_reversals = 0;
      for(int j = i+1; (j-i+1) <= this->lambda && j<=end; j++){
        vector<int> aux = apply_uns_reversal(this->pi, i, j);
        inv_variation_reversals += calc_inv_individual(i, j-1, j);
        if(is_lambda(aux, i, j) && inv_variation_reversals > best_inv){
          best_i = i;
          best_j = j;
          best_k = -1;
          best_inv = inv_variation_reversals;
        }

        int inv_variation_trans = 0;
        for(int k = j+1; (k-i) <= this->lambda && k<=end+1; k++){
          vector<int> aux = apply_transposition(this->pi, i, j, k);
          inv_variation_trans += calc_inv_individual(i, j-1, k-1);
          if(is_lambda(aux, i, k-1) && inv_variation_trans > best_inv){
            best_i = i;
            best_j = j;
            best_k = k;
            best_inv = inv_variation_trans;
          }
        }
      }
    }
    if(best_k != -1){
      this->pi = apply_transposition(this->pi, best_i, best_j, best_k);
    }else{
      this->pi = apply_uns_reversal(this->pi, best_i, best_j);
    }
    distance++;
    this->update_inv();
  }

  // this->show_pi();
  return distance;
}

int SbRT::lower_bound_inv(){
  this->update_inv();
  int max_variation = (lambda*(lambda-1))/2;
  return ceil(this->inv_pi/(max_variation*1.0));
}

int SbRT::lower_bound_bp (){
  int total_bp = this->calc_rev_bp(); 
  return ceil(total_bp/3.); 
}

int SbRT::lower_bound(){ 
  return max(lower_bound_bp(), lower_bound_inv());
}
