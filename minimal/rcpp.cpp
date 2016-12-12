#include <R.h>
#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
int CountNans(NumericVector x) {
  int n = x.length();
  int nanCount = 0;
  for (int i = 0; i < n; i++) {
    if (ISNAN(x[i])) {
      nanCount++;
    }
  }
  return nanCount;
}
