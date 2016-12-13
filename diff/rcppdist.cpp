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
  
  for (i = 0; i < numObjects; i++) {
    for (j = 0; j < numCodes; j++) {
      dist = 0;
      for (k = 0; k < numVars; k++) {
        //if (!ISNAN(data[i * numVars + k])) {
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
