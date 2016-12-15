library(Rcpp)
library(microbenchmark)

sourceCpp('rcpp.cpp')

if (is.loaded(paste("call", .Platform$dynlib.ext, sep=""))) {
  dyn.unload(paste("call", .Platform$dynlib.ext, sep=""))
}
system(paste("R CMD SHLIB call.c", sep=""))
dyn.load(paste("call", .Platform$dynlib.ext, sep=""))

n <- as.integer(100000)
x <- rnorm(n)
x[1:100] <- NaN
x[101:120] <- NA
mb <- microbenchmark(
  macro <- CountNans_macro(x),
  fn <- CountNans_fn(x),
  expr <- CountNans_expr(x),
  sug <- CountNans_sug(x),
  std_macro <- CountNans_std_macro(x),
  std_expr <- CountNans_std_expr(x),
  std_11 <- CountNans_std_11(x),
  call <- .Call("CountNans", x, n),
  times = 1000
)

library(ggplot2)
autoplot(mb)
print(mb)
