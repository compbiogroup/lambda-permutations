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

vector< vector<int> > read_permutations(string path){
  vector< vector<int> > vperm;
  vector<int> perm;
  char line[32000];

  FILE *file_in = fopen(path.c_str(), "r");
  if (file_in == NULL){
    puts("It was not possible to open the input files, please verify if the path is correct.");
    return vperm;
  }
  while (fgets(line, sizeof line, file_in) != NULL){
    int sz_line = strlen(line);
    int elem = 0;
    int mult = 1;
    if (sz_line > 0){
      perm.push_back(0);
      for (int i = 0; i < sz_line; i++){
        if (line[i] == '-')
          mult = -1;
        else{
          if (line[i] < '0' or line[i] > '9'){
            elem *= mult;
            if (elem != 0)
              perm.push_back(elem);
            elem = 0;
            mult = 1;
          }else
            elem = (elem * 10 + (line[i]-'0'));
        }
      }
      //print_permutation (perm);
      vperm.push_back(perm);
      perm.clear();
    }
  }
  fclose(file_in);
  return vperm;
}

int main (int argc, char** argv){
  if (argc < 10){
    printf ("%d\n",argc);
    printf ("Usage: %s path begin_n incr_n end_n begin_lambda incr_lambda end_lambda "
        "name_file_output probs_list\n"
        "where: path should has all input files for signed and unsigned permutations\n"
        "named as {begin_n, begin_n+incr_n, ..., end_n}.in\n"
        "probs_lists should be a sequence with one or more strings in {(r|rt)_uns | (r|rt)_sig | t}", argv[0]);
    return 0;
  }

  int nperm = 1000;

  string path = string(argv[1]);
  bool is_from_identity = atoi(argv[2]) != 0? true : false;
  int begin_n = atoi(argv[3]);
  int incr_n = atoi(argv[4]);
  int end_n = atoi(argv[5]);
  int begin_lambda = atoi(argv[6]);
  int incr_lambda = atoi(argv[7]);
  int end_lambda = atoi(argv[8]);
  string file_out_name = string(argv[9]);
  string path_cur;
  vector<string> arr_prob_ids;
  for (int i = 10; i < argc; i++){
    arr_prob_ids.push_back(string(argv[i]));
  }

  vector<vector<int>> arr_perm;
  vector<int> sigma;

  SbLUR *sbr = new SbLUR();
  SbLSR *sbsr = new SbLSR();
  SbLT *sbt = new SbLT();
  SbLURT *sbrt = new SbLURT();
  SbLSRT *sbsrt = new SbLSRT();
  //sbrT is the same algorithm of sbrt
  int cnt_op, total_perm;
  float average;
  FILE *file_out, *detail_out;

  //iterating among the problems
  for (auto prob_id : arr_prob_ids){
    //iterating among the files with the permutations
    for (int n = begin_n; n <= end_n; n += incr_n){
      detail_out = fopen(("outputs/details_for_n"+to_string(n)+"_lamb"+to_string(begin_lambda)+"_to_"+to_string(end_lambda)+"_with_incr"+to_string(incr_lambda)+"."+prob_id).c_str(), "w");
      file_out = fopen ((file_out_name+"_"+prob_id.c_str()).c_str(), "w");
      printf("Writting on file %s\n", file_out_name.c_str());
      //headers of each output
      fprintf(file_out, "Breakpoints-based#Algorithm\n");
      fprintf(file_out, "$\\lambda$ Average#Amount#of#Operations Average#Approximation#Factor Maximum#Approximation#Factor Minimum#Approximation#Factor\n");
      fprintf(detail_out, "perm_id lambda amount_op amount_bp lower_bound approx\n");

      for (int lambda = begin_lambda ; lambda <= end_lambda and lambda <= n;
          lambda += incr_lambda){

        //getting the path of current file
        string preffix_prob = "" ; 
        preffix_prob.push_back(prob_id[0]);
        if (prob_id.size() > 1 and prob_id[1] == 't') {
          preffix_prob.push_back('t');
        }
        puts(preffix_prob.c_str());

        auto it = prob_id.find("sig");
        if (it != string::npos){
          if (is_from_identity){
            path_cur = path + "signed/" + preffix_prob + "/n" + to_string(n) + "-" + to_string(nperm) + "/" + "lamb" + to_string(lambda) + "-n" + to_string(n) + "-" + to_string(nperm);
          }else
            path_cur = path + "signed/n" + to_string(n) + "-" + to_string(nperm) + "/" + "lamb" + to_string(lambda) + "-n" + to_string(n) + "-" + to_string(nperm);
        }else
          if (is_from_identity){
            path_cur = path + "unsigned/" + preffix_prob + "/n" + to_string(n) + "-" + to_string(nperm) + "/" + "lamb" + to_string(lambda) + "-n" + to_string(n) + "-" + to_string(nperm);
          }else{
            path_cur = path + "unsigned/n" + to_string(n) + "-" + to_string(nperm) + "/" + "lamb" + to_string(lambda) + "-n" + to_string(n) + "-" + to_string(nperm);
          }
        //reading the permutations of that file
        arr_perm = read_permutations(path_cur + ".lp");

        total_perm = arr_perm.size();
        if (arr_perm.empty()){
          printf ("%s could not be opened. Experiment failed.\n", path_cur.c_str());
          return 0;
        }
        printf ("Processing: %s\n", path_cur.c_str());
        cout << path_cur << endl;

        printf ("Current Lambda: %d\n", lambda);

        average = 0;
        float average_approx = 0.0, max_approx = 0., min_approx = 999999999., approx;
        int distance = 0;
        int lower_bound;
        int amount_bp;

        //TODO: Refactor code in order to make the for loops inside if cases as one only generic function
        if(prob_id == "r_uns"){
          for (int i = 0; i < total_perm; i++){
            sbr->reset(arr_perm[i], lambda);
            lower_bound = sbr->lower_bound();
            //printf ("Inversions: %d\n", sbr->get_inv());
            amount_bp = sbr->get_number_breakpoints();
            distance = sbr->sort_greedy();
            average += distance;
            approx = distance/(lower_bound*1.);
            average_approx += approx; 
            max_approx = max (approx, max_approx); 
            min_approx = min(approx, min_approx); 
            fprintf (detail_out, "%d %d %d %d %d %.2f\n", i, lambda, (int)distance, (int) amount_bp, (int)lower_bound, approx); 
          }
        }else if(prob_id == "r_sig"){
          for (int i = 0; i < total_perm; i++){
            sbsr->reset(arr_perm[i], lambda);
            lower_bound = sbsr->lower_bound();
            amount_bp = sbsr->get_number_breakpoints();
            distance = sbsr->sort_greedy();
            average += distance;
            approx = distance/(lower_bound*1.);
            average_approx += approx; 
            max_approx = max (approx, max_approx); 
            min_approx = min(approx, min_approx); 
            fprintf (detail_out, "%d %d %d %d %d %.2f\n", i, lambda, (int)distance, (int) amount_bp, (int)lower_bound, approx); 
          }
        }else if(prob_id == "rt_sig"){
          for (int i = 0; i < total_perm; i++){
            sbsrt->reset(arr_perm[i], lambda);
            lower_bound = sbsrt->lower_bound();
            amount_bp = sbsrt->get_number_breakpoints();
            distance = sbsrt->sort();
            average += distance;
            approx = distance/(lower_bound*1.);
            average_approx += approx; 
            max_approx = max (approx, max_approx); 
            min_approx = min(approx, min_approx); 
            fprintf (detail_out, "%d %d %d %d %d %.2f\n", i, lambda, (int)distance, (int) amount_bp, (int)lower_bound, approx); 
          }
        }else if(prob_id == "rt_uns"){
          for (int i = 0; i < total_perm; i++){
            sbrt->reset(arr_perm[i], lambda);
            lower_bound = sbrt->lower_bound();
            amount_bp = sbrt->get_number_breakpoints();
            distance = sbrt->sort();
            average += distance;
            approx = distance/(lower_bound*1.);
            average_approx += approx; 
            max_approx = max (approx, max_approx); 
            min_approx = min(approx, min_approx); 
            fprintf (detail_out, "%d %d %d %d %d %.2f\n", i, lambda, (int)distance, (int) amount_bp, (int)lower_bound, approx); 
          }
        }else if(prob_id == "t"){
          for (int i = 0; i < total_perm; i++){
            sbt->reset(arr_perm[i], lambda);
            lower_bound = sbt->lower_bound();
            amount_bp = sbt->get_number_breakpoints();
            distance = sbt->sort();
            average += distance;
            approx = distance/(lower_bound*1.);
            average_approx += approx; 
            max_approx = max (approx, max_approx); 
            min_approx = min(approx, min_approx); 
            fprintf (detail_out, "%d %d %d %d %d %.2f\n", i, lambda, (int)distance, (int) amount_bp, (int)lower_bound, approx); 
          }
        }
        average /= (float) total_perm;
        average_approx /= (float) total_perm;

        fprintf (file_out, "%d %.2f %.2f %.2f %.2f\n", lambda,average, average_approx, max_approx, min_approx);
        fflush(file_out);
        fflush(detail_out);
        //end loop of lambda
      }
      puts("done.");
      fclose(file_out);
      fclose(detail_out);
    }//end loop of n
  }//end loop of problems ids
  delete(sbr);
  delete(sbsr);
  delete(sbt);
  delete(sbrt);
  delete(sbsrt);
}
