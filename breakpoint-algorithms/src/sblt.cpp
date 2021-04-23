#include "../include/sblt.h"

SbLT::SbLT():LimitedSizeProblem(){} 

SbLT::SbLT(vector<int> perm, int lambda):LimitedSizeProblem(perm, lambda){
  update_total_bp(); 
}

int SbLT::lower_bound_bp (){
  this->update_total_bp(); 
  return ceil(total_bp/3.);
}

int SbLT::lower_bound_inv(){
  this->update_inv();
  int max_variation = 0;

  for(int i = 1; i < lambda; i++){
    int s1 = i;
    int s2 = lambda-i;
    if(s1*s2>max_variation){
      max_variation = s1*s2;
    }
  }
  return ceil(this->inv_pi/(max_variation*1.0));
}

int SbLT::lower_bound(){
  return max(lower_bound_inv(), lower_bound_bp());
}

void SbLT::reset(vector<int>perm, int lamb){
  reset_problem(perm,lamb);
  update_total_bp(); 
}

void SbLT::update_total_bp (){
  total_bp = 0; 
  for (int i = 0; i <= n; i++){
    if (pi[i+1]-pi[i]!=1)
      total_bp ++; 
  }
}

vector<int> SbLT::strip_starting_at (int start_pos){
  int i = start_pos; 
  vector<int> strip = {pi[start_pos]} ; 
  while (i < pi.size()-1 and pi[i+1]-pi[i] == 1){
    strip.push_back(pi[++i]); 
  }
  return strip;
}

vector<int> SbLT::strip_ending_at (int end_pos){
  int i = end_pos; 
  vector<int> strip = {pi[end_pos]}; 
  while (i > 0 and pi[i]-pi[i-1] == 1){
    strip.push_back(pi[--i]); 
  }
  reverse(strip.begin(), strip.end()); 
  return strip;
}

//returns the distance (todo in the future: implement this in limitedsizeproblem class)
int SbLT::sort (){
  int cnt_operation = 0; 

  while (total_bp > 0){
    int j = get_first_out_of_place(); 
    vector<int> right_strip = strip_starting_at(j); 
    vector<int> left_strip = strip_ending_at(j-1); 

    int floor_lamb = lambda/2; 
    //Segments A, B, C, D, where {A,B} in left_strip
    //and {C,D} in right_strip
    vector<pair<int,int>> seg(4); 

    //All segments has size <= floor(lambda/2)
    //Index of start and end of each segment were done in case of 
    //we want to apply each lambda-transposition in the future 
    seg[0].first = j-left_strip.size();
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

    
    /*cout << seg[0].first << ' ' << seg[0].second << endl; 
    cout << seg[1].first << ' ' << seg[1].second << endl; 
    cout << seg[2].first << ' ' << seg[2].second << endl; 
    cout << seg[3].first << ' ' << seg[3].second << endl;*/ 
    
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
    //print_transposition(pi[j], j, j+ right_strip.size());
    pi = apply_transposition(pi, pi[j], j, j + right_strip.size()); 
    update_total_bp (); 
  }

  return cnt_operation;
}
