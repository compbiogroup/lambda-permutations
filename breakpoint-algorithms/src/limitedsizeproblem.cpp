#include "../include/limitedsizeproblem.h"

LimitedSizeProblem::LimitedSizeProblem (){}

LimitedSizeProblem::LimitedSizeProblem (vector<int> perm, int lambda){
  if (perm.empty())
    n = 0;
  else{
    if (perm[0] != 0){
      pi.push_back(0);
      for (int i = 0; i < perm.size(); i++)
        pi.push_back(perm[i]);
    }else
      pi = perm;
    n = pi.size()-1;
    pi.push_back(n+1); 
    this->lambda = lambda; 
    total_bp = 0; //have to be setted in the childrens
    update_inv(); 
  }
}

void LimitedSizeProblem::update_inv(){
  this->inv_pi = 0;
  for (int i = 1; i <= n; i++){
    for(int j = i+1; j <= n; j++){
      if(abs(pi[i]) > abs(pi[j])) {//i is always less than j
        this->inv_pi += 1;
      }
    }
  }
}

void LimitedSizeProblem::update_vecs(){
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

void LimitedSizeProblem::reset_problem(vector<int> perm, int lambda){
  if (perm.empty())
    n = 0;
  else{
    if (perm[0] != 0){
      pi.push_back(0);
      for (int i = 0; i < perm.size(); i++)
        pi.push_back(perm[i]);
    }else
      pi = perm;
    n = pi.size()-1;
    pi.push_back(n+1); 
    this->lambda = lambda; 
    total_bp = 0; //have to be setted in the childrens
    update_inv(); 
  }
}

bool LimitedSizeProblem::is_lambda(vector<int> perm, int begin, int end){
  for(int i = begin; i <= end; i++){
    if(abs(abs(perm[i]) - i ) >= this->lambda){
      return false;
    }
  }
  return true;
}

void LimitedSizeProblem::show_pi(){
  printf("(");
  for (int i = 1; i <= n; i++){
    if (pi[i] > 0)
      printf ("+%d ", pi[i]);
    else
      printf ("%d ", pi[i]);
  }
  puts(")");
}

int LimitedSizeProblem::get_lambda(){
  return lambda;
}

vector<int> LimitedSizeProblem::get_pi(){
  return pi;
}

int LimitedSizeProblem::get_inv(){
  return inv_pi;
}

int LimitedSizeProblem::get_number_breakpoints(){
  return total_bp;
}

int LimitedSizeProblem::get_first_out_of_place(){
  int mini = n+1; 
  for (int i = 1; i <= n; i++){
    if (pi[i] != i and abs(pi[i]) < abs(pi[mini])){
      mini = i; 
    }
  }
  return mini; 
}
