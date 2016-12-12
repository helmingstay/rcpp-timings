#include <R.h>
#include <Rinternals.h>

SEXP CountNans(SEXP sX, SEXP sLength) {
  int i, n = *INTEGER(sLength);
  int *nanCount;
  double *x = REAL(sX);

  SEXP output = PROTECT(allocVector(INTSXP, 1));
  nanCount = INTEGER(output);
  *nanCount = 0;
  for (i = 0; i < n; i++) {
    if (ISNAN(x[i])) {
      *nanCount += 1;
    }
  }
  
  UNPROTECT(1);
  return output;
}
