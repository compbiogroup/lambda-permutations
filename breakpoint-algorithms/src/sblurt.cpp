#include "../include/sblurt.h"

SbLURT::SbLURT():SbLUR(){} 

SbLURT::SbLURT(vector<int> perm, int lambda):SbLUR(perm, lambda){
}

//returns the distance (todo in the future: implement this in limitedsizeproblem class)
int SbLURT::sort (){
  int cnt_operation = 0; 

  while (total_bp > 0){
    int j = get_first_out_of_place(); 
    int i = pi[j]; 

    vector<int> right_strip = strip_starting_at(j); 
    if (right_strip.size() == 1){
      vector<int> left_strip = strip_ending_at(j); 
      int k = j - left_strip.size() + 1; 
      if (k == i){ //it is not a singleton, since k = j - 1 + 1 = j != i
        //print_reversal(i,j);
        pi = apply_uns_reversal(pi, i, j); 
        cnt_operation++;
      }else{
        //print_transposition(i,k,j+1);
        pi = apply_transposition(pi, i, k, j+1); 
        cnt_operation ++; 
        if (left_strip.size() > 1){ //it is a decr strip
          //print_reversal(i,i+(j-k));
          pi = apply_uns_reversal(pi, i, i + (j-k)); 
          cnt_operation ++; 
        }
      }
    }else{
      int floor_lamb = lambda/2; 
      //Segments A, B, C, D, where {A,B} in segment i .. j-1
      //and {C,D} in right_strip
      vector<pair<int,int>> seg(4); 

      //All segments has size <= floor(lambda/2)
      //Index of start and end of each segment were done in case of 
      //we want to apply each lambda-transposition in the future 
      seg[0].first = i;
      if (seg[0].first + floor_lamb >= j){
        seg[0].second = j; //ends at position j (not inclusive) 
        seg[1].first = seg[1].second = -1; //there is no B in this case
      }else{
        seg[1].first = seg[0].second = seg[0].first + floor_lamb; 
        seg[1].second = j; 
      }
      seg[2].first = j; 
      if (j + floor_lamb >= j + right_strip.size()){
        seg[2].second = j + right_strip.size(); 
        seg[3].first = seg[3].second = -1; 
      }else{
        seg[3].first = seg[2].second = seg[2].first + floor_lamb;
        seg[3].second = j + right_strip.size(); 
      }

      if (seg[1].first == -1 and seg[3].first == -1){
        cnt_operation ++; //tau (A, C)
      }else{
        if (seg[1].first == -1 or seg[3].first == -1){
          cnt_operation += 2; //tau(A,C) . tau(A,D) or tau(B,C) . tau(A,C)
        }else
          cnt_operation += 4; //tau (B, C) . tau(A,C) . tau(B,D) . tau(A,D)
      }

      //It is not a lambda-transposition, the cases above is to count
      //the number of operations needed to obtain this operation
      //note that it is a 2(lambda-1)-transposition
      //print_transposition(i, j, j + right_strip.size());
      pi = apply_transposition(pi, i, j, j + right_strip.size()); 
    }
    update_total_bp (); 
  }
  return cnt_operation;
}

int SbLURT::lower_bound_inv(){
  this->update_inv();
  int max_variation = (lambda*(lambda-1))/2;
  return ceil(this->inv_pi/(max_variation*1.0));
}

int SbLURT::lower_bound_bp(){
  this->update_total_bp(); 
  return ceil(total_bp/3.); 
}

int SbLURT::lower_bound(){
  return max(lower_bound_bp(), lower_bound_inv());
}
