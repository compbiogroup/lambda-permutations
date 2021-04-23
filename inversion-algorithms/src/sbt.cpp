#include "../include/sbt.h"

SbT::SbT():Problem(){}

SbT::SbT(vector<int> perm, int lambda):Problem(perm, lambda){}

int SbT::sort(){
  int distance = 0;
  while(this->inv_pi > 0){
    int best_i, best_j, best_k, best_inv;
    best_i = best_j = best_k = best_inv = 0;
    int begin = 1, end = n;
    while(abs(this->pi[begin]) == begin) begin++;
    while(abs(this->pi[end]) == end) end--;

    for(int i = begin; i < end; i++){
      for(int j = i+1; (j-i+1) <= this->lambda && j<=end; j++){
        int inv_variation = 0;
        for(int k = j+1; (k-i) <= this->lambda && k<=end+1; k++){
          vector<int> aux = apply_transposition(this->pi, i, j, k);
          inv_variation += calc_inv_individual(i, j-1, k-1);
          if(is_lambda(aux, i, k-1) && inv_variation > best_inv){
            best_i = i;
            best_j = j;
            best_k = k;
            best_inv = inv_variation;
          }
        }
      }
    }

    this->pi = apply_transposition(this->pi, best_i, best_j, best_k);
    distance++;
    this->update_inv();
  }

  // this->show_pi();
  return distance;
}

int SbT::lower_bound_inv(){
  this->update_inv();
  int max_variation = (lambda*(lambda-1))/2;
  return ceil(this->inv_pi/(max_variation*1.0));
}

int SbT::lower_bound_bp(){ 
  int total_bp = calc_transp_bp(); 
  return ceil(total_bp/3.);
}

int SbT::lower_bound(){
  return max(lower_bound_bp(), lower_bound_inv()); 
}
