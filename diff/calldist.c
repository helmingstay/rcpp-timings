#include <R.h>
#include <Rinternals.h>

SEXP CallDist(
  SEXP sData,
  SEXP sCodes,
  SEXP sNumObjects,   
  SEXP sNumVars,
  SEXP sNumCodes
) {
  int
    i, j, k,
    numObjects = *INTEGER(sNumObjects), 
    numCodes = *INTEGER(sNumCodes),
    numVars = *INTEGER(sNumVars);

  double
    dist, tmp, *mindist,
    *data = REAL(sData),
    *codes = REAL(sCodes);

  SEXP output = PROTECT(allocVector(REALSXP, 1));
  mindist = REAL(output);
  *mindist = 10000.0;

  for (i = 0; i < numObjects; i++) {
    for (j = 0; j < numCodes; j++) {
      dist = 0;
      for (k = 0; k < numVars; k++) {
        if (!ISNAN(data[i * numVars + k])) {
          tmp = data[i * numVars + k] - codes[j * numVars + k];
          dist += tmp * tmp;
        }
      }
      if (dist < *mindist) {
        *mindist = dist;
      }
    }
  }

  UNPROTECT(1);
  return output;
}
