#include "../include/operations.h"

void print_reversal (int i, int j){
  printf ("rho(%d,%d)\n",i,j);
}

void print_transposition (int i, int j, int k){
  printf ("tau(%d,%d,%d)\n",i,j,k);
}

void print_permutation (vector<int> p){
  printf ("(");
  for (int i = 1; i < p.size(); i++){
    printf (" %d ", p[i]);
  }puts(")");
}

vector<int> apply_uns_reversal (vector<int> p, int i, int j){
  reverse(p.begin()+i, p.begin()+j+1);
  return p;
}

vector<int> apply_sig_reversal (vector<int> p, int i, int j){
  //print_permutation(p);
  for (int k = i, q = j; k <= q; q--, k++){
    p[k] = -p[k];
    if (k != q)
      p[q] = -p[q];
    swap(p[k],p[q]);
  }
  //print_permutation(p);
  return p;
}

vector<int> apply_transposition(vector<int> p, int i, int j, int k) {
  int t, l, seg1, seg2;
  vector<int> aux(p.size(),0); 
  seg1 = j - i;
  seg2 = k - j;

  if (seg2 < seg1) {
    for (t = i; t <= seg2 + i - 1; t++) {
      aux[t-i] = p[t];
      p[t] = p[j + t - i];
    }
    l = 0;
    for (t = i + seg2; t < j; t++) {
      aux[t-i] = p[t];
      p[t] = aux[l++];
    }
    for (t = j; t < k; t++) {
      p[t] = aux[l++];
    }
  } else {
    for (t = i; t < j; t++) {
      aux[t-i] = p[t];
      p[t] = p[j + t - i];
    }
    for (t = j; t <= i + seg2 - 1; t++) {
      p[t] = p[t + seg1];
    }
    l = 0;
    for (t = i + seg2; t < k; t++) {
      p[t] = aux[l++];
    }
  }
  return p;
}
