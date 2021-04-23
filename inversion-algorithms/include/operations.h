#ifndef __OPERATIONS_H
#define __OPERATIONS_H

#include <math.h>
#include <vector>
#include <algorithm>
#include <stdio.h>
using namespace std;

vector<int> apply_uns_reversal (vector<int> p, int i, int j);
vector<int> apply_sig_reversal (vector<int> p, int i, int j);
vector<int> apply_transposition(vector<int> p, int i, int j, int k);
void print_reversal (int i, int j);
void print_transposition (int i, int j, int k);
void print_permutation (vector<int> p);
#endif
