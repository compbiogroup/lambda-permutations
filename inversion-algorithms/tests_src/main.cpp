#include "../include/sbr.h"
#include "../include/sbsr.h"
#include "../include/sbt.h"
#include "../include/sbrt.h"
#include "../include/sbsrt.h"
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
using namespace std;

int main (int argc, char** argv){
  const int n = atoi(argv[1]);
  const int lambda = atoi(argv[2]);
  const int total_perms = atoi(argv[3]); 
  int elem, max_amount_op = 0; 
  vector<int> pi, hard_perm; ; 
  SbR *sbr = new SbR (); 

  for (int j = 0; j < total_perms; j++) { 
    pi = {0}; 
    for (int i = 0; i < n; i++) {
      cin >> elem ;
      pi.push_back(elem); 
    }
    sbr->reset(pi, lambda); 
    int amount_op = sbr->sort(); 
    if (amount_op > max_amount_op){ 
      max_amount_op = amount_op; 
      hard_perm = pi; 
    }
  }

  sbr->reset(hard_perm, lambda);
  print_permutation(hard_perm);
  cout << sbr->get_inv() << endl;
  int amount_op = sbr->sort_verbose(); 
  cout << amount_op << endl;
  delete (sbr); 
}
