/* Return smallest distance between two sets of vectors */
#include <Rcpp.h>
using namespace Rcpp;
 
// [[Rcpp::export]]
double RcppDist(NumericMatrix data,
        NumericMatrix codes,
        int numObjects,
        int numVars,
        int numCodes   
) {
  int
    i, j, k;
  
  double
    dist, tmp, mindist; 
    //*data = REAL(sData1),
    //*codes = REAL(sData2);
  
  mindist = 10000.0;
  NumericVector dat;
  
  for (i = 0; i < numObjects; i++) {
    if(any(is_nan(data(_,i)))) {
      continue;
    }
    for (j = 0; j < numCodes; j++) {
      dist = 0;
      for (k = 0; k < numVars; k++) {
        //if (!Rcpp::is_nan()) {
          tmp = data[i * numVars + k] - codes[j * numVars + k];
          dist += tmp * tmp;
        //}
      }
      if (dist < mindist) {
        mindist = dist;
      }
    }
  }

  return mindist;
}
