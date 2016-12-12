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
mb <- microbenchmark(
  rcpp <- CountNans(x),
  call <- .Call("CountNans", x, n),
  times = 10000
)

library(ggplot2)
autoplot(mb)

