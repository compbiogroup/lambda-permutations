#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <math.h>
#define _GNU_SOURCE

int min(int val1, int val2){ 
  return val1 < val2? val1 : val2; 
}

int max(int val1, int val2){
  return val1 > val2? val1 : val2; 
}

void opReversal(int size, int* pi, int i, int j, int isUnsigned){
    int * copy = malloc((size + 1) * sizeof (int));
    memcpy(copy, pi, (size + 1) * sizeof(int));

    int x, y = j;
    for(x = i; x <= j; x++){
        if(isUnsigned){
            pi[x] = copy[y];
        }else{
            pi[x] = -copy[y];
        }
        y--;
    }
    free(copy);
}

char isLambdaPerm(int *aux, int begin, int end, int lambda){
  for(int i = begin; i <= end; i++){
    if(abs(abs(aux[i]) - i ) >= lambda){
      return 0;
    }
  }
  return 1;
}

void arrayCopy (int* copy, int* original, int sz){
  for (int i = 0; i < sz; i++){ 
    copy[i] = original[i]; 
  }
}

void opTransposition(int size, int* pi, int i, int j, int k){
    int * copy = malloc((size + 1) * sizeof (int));
    memcpy(copy, pi, (size + 1) * sizeof(int));

    int a = i, b = i+(k-j);

    while(a <= j-1){
        pi[b] = copy[a];
        a++;
        b++;
    }

    a = j;
    b = i;
    while(a <= k-1){
        pi[b] = copy[a];
        a++;
        b++;
    }
    free(copy);

}

void print(int size, int *permutation){
    for (int i = 1; i < size; i++) {
        printf("%d,", permutation[i]);
    }
    printf("%d\n", permutation[size]);
}

//It returns the size of the generated operation by value and the operation by reference i, j and (maybe) k
int generateOp(int size, int lambda, int *i, int *j, int *k, int isUnsigned, char* alg){
    int isReversal;
    if(!strcmp(alg, "r")){
        isReversal = 1;
    }else if(!strcmp(alg, "t")){
        isReversal = 0;
    }else{
        isReversal = rand() % 2;
    }

    if(isReversal == 1){
        *i = 1 + (rand() % (size - isUnsigned));//if it is unsigned i < n
        if(isUnsigned){
          *j = min(*i + 1 + (rand() % (lambda - 1)), size); 
        }else{
          *j = min(*i + (rand() % lambda), size);
        }
        //printf ("%d,%d\n", *i,*j);
        return *j-*i+1;
    }

    *i = 1 + (rand() % (size - 1)); //at most n-1
    *j = min(*i + 1 + (rand() % (lambda-1)), size); //at most n
    *k = min(*j + 1 + (rand() % max(lambda-1 - (*j-*i),1)), size+1);
    return *k-*i; 
}

int main(int argc, char *argv[]){
    extern char *optarg;
    char op;
    int size = 15, nperms = 50, nop = 1, uns = 1, lambda = 2;
    int n, m;
    int *permutation, *identity, *copy;
    char * alg = "r";
    struct option longopts[] = {
        {"size", 1, NULL, 'n'},
        {"nperms", 1, NULL, 'q'},
        {"nop", 1, NULL, 'o'},
        {"uns", 1, NULL, 'u'},
        {"alg", 1, NULL, 'a'},
        {"lambda", 1, NULL, 'l'},
        {"help", 0, NULL, 'h'}
    };

    while ((op = getopt_long(argc, argv, "n:q:o:u:a:l:h", longopts, NULL)) != -1) {/*{{{*/
        switch (op) {
            case 'n': size = atoi(optarg); break;
            case 'q': nperms = atoi(optarg); break;
            case 'o': nop = atoi(optarg); break; 
            case 'u': uns = atoi(optarg); break;
            case 'a': alg = optarg; break;
            case 'l': lambda = atoi(optarg); break;
            case 'h':
                printf("usage: %s [options] \n", argv[0]);
                printf("options: \n");
                printf("\t--size or -n: permutation size (default = 15)\n");
                printf("\t--nop or -o: number of random operations to apply (default = 10)\n");
                printf("\t--uns or -u: 1 for unsigned and 0 for signed (default = 1)\n");
                printf("\t--alg or -a: algorithm (default = r)\n");
                printf("\t--nperms or -q: number of permutations to be created (default = 50)\n");
                printf("\t--lambda or -l: number of permutations to be created (default = 2)\n");
                exit(0);
        }
    }/*}}}*/

    permutation = malloc((size + 1) * sizeof (int));
    copy = malloc((size + 1) * sizeof (int));
    identity = malloc((size + 1) * sizeof (int));


    for(m = 0; m<= size; m++){
        identity[m] = m;
    }

    for (n = 0; n < nperms; n++) {
        memcpy(permutation, identity, (size + 1) * sizeof(int));
        memcpy(copy, identity, (size+1) * sizeof(int));

        for(m = 0; m < nop; m++){
            // printf("%d, %d, %d\n", i, j, k);
            char valid = 0; 
            while (!valid){ 
              int i, j, k = 0;
              int szOp = generateOp(size, lambda, &i, &j, &k, uns, alg);
              if (szOp > lambda) {
                 printf ("ERROR! An non lambda-operation were generated!!!\n");
                 exit(0);
              }
             
              arrayCopy (copy, permutation, size+1); 

              if(k > 0){
                opTransposition(size, copy, i, j, k);
              }else{
                opReversal(size, copy, i, j, uns);
              }   
              if (isLambdaPerm(copy, i, max(j,k-1), lambda)){ 
                valid = 1;
                int* temp = permutation;
                permutation = copy;
                copy = temp;
              }
            }
            // print(size, permutation);
        }
        print(size, permutation);
        if (!isLambdaPerm(permutation, 1, size, lambda)){
           printf ("ERROR! An non lambda-permutation were generated!!!\n");
           exit(0);
        }
    }

    free(identity);
    free(permutation);
    free(copy);
}
