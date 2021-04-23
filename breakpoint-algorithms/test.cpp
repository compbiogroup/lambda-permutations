#include "../include/sblur.h"
#include "../include/sblsr.h"
#include "../include/sblt.h"
#include "../include/sblurt.h"
#include "../include/sblsrt.h"
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
using namespace std;

int main (int argc, char** argv){
  //SbLSR *sbr = new SbLSR({4, 5, 6, 1, 2, 3}, 4);
  SbLT *sbr = new SbLT({4, 5, 1, 2, 3}, 5);

  cout << sbr->sort() << endl;
}
