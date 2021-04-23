#include "../include/sblur.h"

SbLUR::SbLUR():LimitedSizeProblem(){} 

SbLUR::SbLUR(vector<int> perm, int lambda):LimitedSizeProblem(perm, lambda){
  update_total_bp(); 
}


void SbLUR::reset(vector<int> perm, int lambda){
  reset_problem(perm, lambda); 
  update_total_bp(); 
}

void SbLUR::update_total_bp (){
  total_bp = 0; 
  for (int i = 0; i <= n; i++){
    if (abs(pi[i+1]-pi[i])!=1)
      total_bp ++; 
  }
}

vector<int> SbLUR::strip_starting_at (int start_pos){
  int i = start_pos; 
  vector<int> strip = {pi[start_pos]} ; 
  while (i < pi.size()-1 and abs(pi[i+1]-pi[i]) == 1){
    strip.push_back(pi[++i]); 
  }
  return strip;
}

vector<int> SbLUR::strip_ending_at (int end_pos){
  int i = end_pos; 
  vector<int> strip = {pi[end_pos]}; 
  while (i > 0 and abs(pi[i]-pi[i-1]) == 1){
    strip.push_back(pi[--i]); 
  }
  reverse(strip.begin(), strip.end()); 
  return strip;
}

int SbLUR::revert_all_decreasing_strips(){
  //firstly, we revert all decreasing strips
  //note that size max of a strip is lambda-1, so operations are lambda-reversals
  int strip_start = 1, strip_end = 1, cnt_operation=0; 
  for (int i = 1; i <= n; i++){ //pi[n] < pi[n+1], so line 47 worstart_revs
    if (pi[i] == pi[i+1] + 1){
      strip_end = i+1; 
    }else{
      if (strip_end-strip_start+1 > 1){
        pi = apply_uns_reversal(pi, strip_start, strip_end); 
        cnt_operation ++; 
      }
      strip_start = i+1; 
      strip_end = i+1; 
    }
  }
  update_total_bp();
  return cnt_operation ;
}

int SbLUR::get_best_start_reversal(int end_rev){
  // (end_rev-start_reversal)+1 <= lambda
  for (int start = max(-lambda+end_rev+1,1); start < end_rev; start++){
    vector<int> aux = apply_uns_reversal(pi, start, end_rev); 
    if (is_lambda(aux, start, end_rev))
      return start; 
  }
  return -1; 
}

int SbLUR::sort_greedy (){
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
        pi = apply_uns_reversal(pi, start_rev, end_rev); 
        if (!is_lambda(pi, start_rev, end_rev))
            puts("IT IS NOT A LAMBDA PERMUTATION!");
        //print_permutation(pi);
        cnt_operation ++; 
        //see if we need to revert again elements from R
        if (end_rev - (start_rev+sz_subseg) + 1 > 1){
          //print_reversal(start_rev+sz_subseg, end_rev);
          pi = apply_uns_reversal(pi, start_rev+sz_subseg, end_rev);
          if (!is_lambda(pi, start_rev+sz_subseg, end_rev))
              puts("IT IS NOT A LAMBDA PERMUTATION!");
          //print_permutation(pi);
          cnt_operation ++; 
        }
        j = start_rev; 
        end_rev = j+sz_subseg-1;
        start_rev = max(i, get_best_start_reversal(end_rev));
      }
      if (sz_subseg > 1 and pi[i] == pi[i+1]+1){
        //print_reversal(start_rev+sz_subseg, end_rev);
        pi = apply_uns_reversal(pi, i, i+sz_subseg-1);
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
int SbLUR::sort (){
  //first of all, pi should has only increasing strips
  int cnt_operation = revert_all_decreasing_strips(); 

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
      int start_rev = max(i, j-sz_subseg);
      while (j > start_rev){
        pi = apply_uns_reversal(pi, start_rev, j+sz_subseg-1); 
        cnt_operation ++; 
        if ((j+sz_subseg-1) - (start_rev+sz_subseg) + 1 > 1){
          pi = apply_uns_reversal(pi, start_rev+sz_subseg, j+sz_subseg-1);
          cnt_operation ++; 
        }
        j = start_rev; 
        start_rev = max(i, j-sz_subseg);
      }
      if (sz_subseg > 1 and pi[i] == pi[i+1]+1){
        pi = apply_uns_reversal(pi, i, i+sz_subseg-1);
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

int SbLUR::lower_bound_bp(){
  this->update_total_bp(); 
  return ceil(total_bp/2.); 
}

int SbLUR::lower_bound_inv(){
  this->update_inv();
  int max_variation = (lambda*(lambda-1))/2;
  return ceil(this->inv_pi/(max_variation*1.0));
}

int SbLUR::lower_bound(){
  return max(lower_bound_bp(), lower_bound_inv());
}

