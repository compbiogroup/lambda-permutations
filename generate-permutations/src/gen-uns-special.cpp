#include <bits/stdc++.h>
using namespace std;

/* Verify if there exists at least a pair of elements such that:
 * pi_j = i, pi_i >= j and j > i
 * or
 * pi_j = i, pi_i <= j and j < i
*/

bool verify(vector<int>pi){
  for (int j = 1; j < pi.size();j++){
    if (pi[pi[j]] >= j and j > pi[j]){
      //printf ("j = %d, i = %d, pi_j = %d, pi_i = %d",j,pi[j],pi[j],pi[pi[j]]);
      return true;
    }
    if (pi[pi[j]] <= j and j < pi[j]){
      //printf ("j = %d, i = %d, pi_j = %d, pi_i = %d",j,pi[j],pi[j],pi[pi[j]]);
      return true;
    }
  }
  return false;
}

int main (int argc, char **argv){
  vector<int> perm, aux; 
  if (argc != 2){
    printf ("Usage: %s n \n", argv[0]);
    return 0;
  }

  int n = atoi(argv[1]); 
  perm.push_back(0);
  for (int i = 1; i <= n; i++){
    perm.push_back(i);
  }
  do{
    bool is_special = true;
    for (int i = 1; i < perm.size(); i++){
      if ((i < perm.size()-1) and (perm[i] > i and perm[i+1] < i+1)){
        is_special = false;
      }
    }
    if (is_special){
      for(int i = 1; i < perm.size();i++){
        printf ("%d ", perm[i]);
      }
      verify(perm);
      puts("");
      //puts(verify(perm)?" ok":"NOT OK");
    }
  }while(next_permutation(perm.begin(),perm.end()));

  return 0;
}

