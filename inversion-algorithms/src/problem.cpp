#include "../include/problem.h"

Problem::Problem (){ }

Problem::Problem (vector<int> perm, int lambda){
  if (perm.empty()){
    n = 0;
  }else{
    if (perm[0] != 0){
      pi.push_back(0);
      for (int i = 0; i < perm.size(); i++)
        pi.push_back(perm[i]);
    }else{
      pi = perm;
    }
    n = pi.size()-1;
    this->lambda = lambda;
    update_inv();
    //For now, we are only using the vectors for get the lower
    //bounds, so we do not need to update
    this->vec_even_neg = 0;
    this->vec_odd_pos = 0;
    update_neg();
  }
}

void Problem::reset(vector<int> perm, int lambda){
  if (perm.empty()){
    n = 0;
  }else{
    if (perm[0] != 0){
      pi.push_back(0);
      for (int i = 0; i < perm.size(); i++){
        pi.push_back(perm[i]);
      }
    }else{
      pi = perm;
    }
    n = pi.size()-1;
    this->lambda = lambda;
    update_inv();
    update_neg();
  }
}

int Problem::calc_vec_variation(vector<int>p2, int begin, int end){
  int even_neg_pi = 0;
  int odd_pos_pi = 0;
  int even_neg_pi2 = 0;
  int odd_pos_pi2 = 0;

  for(int i = begin; i <= end; i++){
    //check if it is a lambda-permutation
    if(abs(abs(p2[i]) - i) >= this->lambda){
      return -(n*n); //forces the score function to be less than 0
    }

    //calculate |V_odd^+| and |V_even^-|
    if((abs(abs(pi[i]) - i) % 2 == 0) && (pi[i] < 0)){
      even_neg_pi++;
    }else if((abs(abs(pi[i]) - i) % 2 == 1) && (pi[i] > 0)){
      odd_pos_pi++;
    }

    if((abs(abs(p2[i]) - i) % 2 == 0) && (p2[i] < 0)){
      even_neg_pi2++;
    }else if((abs(abs(p2[i]) - i) % 2 == 1) && (p2[i] > 0)){
      odd_pos_pi2++;
    }
  }
  return (even_neg_pi + odd_pos_pi) - (even_neg_pi2 + odd_pos_pi2);
}

void Problem::update_inv(){
  this->inv_pi = 0;
  for (int i = 1; i <= n; i++){
    for(int j = i+1; j <= n; j++){
      if(abs(pi[i]) > abs(pi[j])) {//i is always less than j
        this->inv_pi += 1;
      }
    }
  }
}

int Problem::is_lambda(vector<int> aux, int begin, int end){
  for(int i = begin; i <= end; i++){
    if(abs(abs(aux[i]) - i ) >= this->lambda){
      return false;
    }
  }
  return true;
}

//this method simulates the variation of putting element `element` before the sequence `begin` ... `end`
int Problem::calc_inv_individual(int begin, int end, int element){
  int inv_after = 0;
  int inv = 0;
  for(int i = begin; i <= end; i++){
    if(abs(pi[element]) > abs(pi[i])){
      inv_after++;
    }else if(abs(pi[element]) < abs(pi[i])){
      inv++;
    }
  }

  return inv-inv_after;
}

int Problem::calc_inv_variation(vector<int>pi2, int begin, int end){
  int inv_pi_1 = 0;
  int inv_pi_2 = 0;

  for(int i = begin; i <= end; i++){
    for(int j = i+1; j <= end; j++){
      if(abs(pi[i]) > abs(pi[j])) {//i is always less than j
        inv_pi_1 += 1;
      }

      if(abs(pi2[i]) > abs(pi2[j])){
        inv_pi_2 += 1;
      }
    }
  }

  return inv_pi_1 - inv_pi_2;
}

void Problem::update_neg(){
  neg_pi = 0;
  for (int i = 1; i <= n; i++)
    if (pi[i] < 0)
      neg_pi++;
}

void Problem::update_vecs(){
  this->vec_even_neg = 0;
  this->vec_odd_pos = 0;

  for(int i = 1; i <= n; i++){
    //calculate |V_odd^+| and |V_even^-|
    if((abs(abs(pi[i]) - i) % 2 == 0) && (pi[i] < 0)){
      this->vec_even_neg++;
    }else if((abs(abs(pi[i]) - i) % 2 == 1) && (pi[i] > 0)){
      this->vec_odd_pos++;
    }
  }
}

int Problem::calc_neg_variation(vector<int> perm, int begin, int end){
  int neg_pi_ij = 0, neg_pi2_ij = 0;
  for (int i = begin; i <= end; i++){
    if (perm[i] < 0)
      neg_pi2_ij ++;
    if (pi[i] < 0)
      neg_pi_ij ++;
  }
  return neg_pi_ij-neg_pi2_ij;
}

//for SbUR and SbURT
int Problem::calc_rev_bp (){
  int total_bp = 0; 
  for (int i = 0; i <= n; i++){
    if (abs(pi[i+1]-pi[i])!=1)
      total_bp ++; 
  }
  return total_bp; 
}

//for SbSR, SbT and SbSRT
int Problem::calc_transp_bp (){
  int total_bp = 0; 
  for (int i = 0; i <= n; i++){
    if (pi[i+1]-pi[i]!=1)
      total_bp ++; 
  }
  return total_bp; 
}

void Problem::show_pi(){
  printf("(");
  for (int i = 1; i <= n; i++){
    if (pi[i] > 0)
      printf ("+%d ", pi[i]);
    else
      printf ("%d ", pi[i]);
  }
  puts(")");
}

int Problem::get_inv(){
  return inv_pi;
}

int Problem::get_lambda(){
  return lambda;
}

vector<int> Problem::get_pi(){
  return pi;
}
