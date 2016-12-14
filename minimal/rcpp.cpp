#include <R.h>
#include <Rcpp.h>
#include <math.h>

using namespace Rcpp;


// [[Rcpp::plugins(cpp11)]]

inline bool isnan_macro(double x) {
    return ISNAN(x);
}

inline bool isnan_expr(double x) {
    // R-core macro
    return isnan(x)!=0;
}

inline bool isnan_11(double x) {
    // different behavior from ISNAN
    return std::isnan(x);
}

// [[Rcpp::export]]
void CountNans_macro(NumericVector x) {
  int nanCount = 0;
  for (double xx : x) {
    if (ISNAN(xx)) {
      nanCount++;
    }
  }
}

// same as _macro?
// [[Rcpp::export]]
void CountNans_fn(NumericVector x) {
  int nanCount = 0;
  for (double xx : x) {
    if (R_isnancpp(xx)) {
      nanCount++;
    }
  }
}

// why so fast?
// [[Rcpp::export]]
void CountNans_expr(NumericVector x) {
  int nanCount = 0;
  for (double xx : x) {
    if (isnan_expr(xx)) {
      nanCount++;
    }
  }
}

// slow
// [[Rcpp::export]]
int CountNans_sug(NumericVector x) {
  return sum(is_nan(x));
}

// [[Rcpp::export]]
int CountNans_std_macro(NumericVector x) {
  int n = x.length();
  int nanCount = std::count_if( x.begin(), x.end(), isnan_macro) ;
  return nanCount;
}

// [[Rcpp::export]]
int CountNans_std_expr(NumericVector x) {
  int n = x.length();
  int nanCount = std::count_if( x.begin(), x.end(), isnan_expr) ;
  return nanCount;
}

// different sense - does *not* count NAs?
// [[Rcpp::export]]
int CountNans_std_11(NumericVector x) {
  int n = x.length();
  int nanCount = std::count_if( x.begin(), x.end(), isnan_11) ;
  return nanCount;
}
