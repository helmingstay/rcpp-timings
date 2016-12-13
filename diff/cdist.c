/* Return smallest distance between two sets of vectors */
#include <R.h>

void CDist(double *data,
	   double *codes,
	   Sint *pNumObjects,
	   Sint *pNumVars,
	   Sint *pNumCodes,
	   double *mindist
 ) {
  int
    i, j, k,
    numObjects = *pNumObjects, 
    numCodes = *pNumCodes,
    numVars = *pNumVars;

  double
    dist, tmp;

  *mindist = 10000.0;

  for (i = 0; i < numObjects; i++) {
    for (j = 0; j < numCodes; j++) {
      dist = 0;
      for (k = 0; k < numVars; k++) {
        //if (!ISNAN(data[i * numVars + k])) {
          tmp = data[i * numVars + k] - codes[j * numVars + k];
          dist += tmp * tmp;
        //}
      }
      if (dist < *mindist) {
        *mindist = dist;
      }
    }
  }
}
