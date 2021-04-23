#include <bits/stdc++.h>
using namespace std;

bool max_bpt (vector<int> perm){ 
  int bp = 0; 

  perm.push_back (perm.size()) ; //inserting n+1 
  for (int i = 0; i < perm.size()-1; i++) {
    if (perm[i+1] - perm[i] != 1) 
      bp ++; 
  }
  return (bp == perm.size()-1);
}

bool max_bpr (vector<int> perm){ 
  int bp = 0; 

  perm.push_back (perm.size()) ; //inserting n+1 
  for (int i = 0; i < perm.size()-1; i++) {
    if (abs(perm[i+1] - perm[i]) != 1) 
      bp ++; 
  }
  return (bp == perm.size()-1);
}

bool marked_perm(vector< vector<int> > all_perm, vector<int> perm){
  for (int i = 0; i < all_perm.size(); i++){
    bool equal = true;
    for (int j = 1; j < all_perm[i].size() and equal; j++){
      if (perm[j]!=all_perm[i][j])
        equal = false; 
    }
    if (equal)
      return true;
  }
  return false;
}

vector<int> random_unique_perm(vector< vector<int> > all_perm, bool
    is_signed, int n, int lambda){
  vector<int> pi; 
  vector<bool> vis; 

  do{
    pi = vector<int>(n+1,0);
    vis = vector<bool>(n+1,false);
    //Generating a lambda-permutation
    for (int i = 1; i <= n; i++){
      int minimum = max(1, i-lambda+1);
      int maximum = min(i+lambda-1, n);
      int sign_mult = rand()%2 == 0? -1 : 1; 
      if (!is_signed)
        sign_mult = 1;
      if (i - lambda + 1> 0 and !vis[minimum]){ //the first element of the range should be put now
        pi[i] = minimum * sign_mult; 
        vis[minimum] = true;

      }else{
        int cnt = 0; //count the number of elements that still are available
        for (int j = minimum; j <= maximum; j++){
          if (!vis[j])
            cnt ++;
        }
        int r = rand()%cnt+1;
        //printf ("r = %d\n",r);&
        cnt = 0;
        for (int j = minimum; j <= maximum; j++){
          if (!vis[j]) {
            cnt ++;
            if (cnt == r){
              //printf ("pi[%d] = %d\n",i,j); 
              pi[i] = j * sign_mult;
              vis[j] = true;
            }
          }
        }
      }
    }
    //Verify if pi was not generated yet
  }while(marked_perm(all_perm,pi));
  return pi;
}

int main (int argc, char **argv){
  if (argc < 6){
    printf("usage: %s signed sz_perm lim_sz_op total_perm verb\n",argv[0]);
    puts("where signed is one or zero, for signed and unsigned respectively");
    puts ("and verb (if 1) will print a first line describing number of each"
        "generated permutation");
    return 0;
  }
  srand(1);

  bool is_signed = strcmp(argv[1], "0")==0? 0 : 1; 
  int n = atoi(argv[2]); 
  int lambda = atoi(argv[3]);
  int m = atoi(argv[4]);
  int verb = atoi(argv[5]);

  vector<int> perm;
  vector< vector<int> > all_perm; 
  for (int k = 0; k < m; k++){
    if (verb==1)
      printf ("#%d",k);
    perm = random_unique_perm(all_perm, is_signed, n, lambda);
    all_perm.push_back(perm);
  }
  if (verb)
    puts("");
  for (int i = 0; i < m; i++){
    bool break_line = false ; 
    for (int j = 1; j <= n; j++){
      if (max_bpr(all_perm[i])) { 
        printf("%d ", all_perm[i][j]);
        break_line = true; 
      }
    }
    if (break_line)
      puts("");
  }
}
