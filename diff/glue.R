testdist <- function(data1, data2, what = c("C", "Call", "Cpp")) {
  what <- match.arg(what)
  nvariables <- nrow(data1)
  if (nvariables != nrow(data2)) {
    stop("Both data matrices should have the same number of rows")
  }
  nobjects1 <- ncol(data1)
  nobjects2 <- ncol(data2)
  switch(what,
         C = {
           mindist <- -1  
           res = .C("CDist",
                    data = as.double(data1),
                    codes = as.double(data2),
                    pNumObjects = as.integer(nobjects1),
                    pNumVars = as.integer(nvariables),
                    pNumCodes = as.integer(nobjects2),
                    mindist = as.double(mindist))
           res$mindist
         },
         Call = .Call("CallDist",
                      data1,
                      data2,
                      nobjects1,
                      nvariables,
                      nobjects2),
         Cpp = RcppDist(mat1, mat2, nobjects1, nvariables, nobjects2)
  )
}

if (is.loaded(paste("cdist", .Platform$dynlib.ext, sep=""))) {
  dyn.unload(paste("cdist", .Platform$dynlib.ext, sep=""))
}
system(paste("R CMD SHLIB cdist.c", sep=""))
dyn.load(paste("cdist", .Platform$dynlib.ext, sep=""))

if (is.loaded(paste("calldist", .Platform$dynlib.ext, sep=""))) {
  dyn.unload(paste("calldist", .Platform$dynlib.ext, sep=""))
}
system(paste("R CMD SHLIB calldist.c", sep=""))
dyn.load(paste("calldist", .Platform$dynlib.ext, sep=""))

library(Rcpp)
sourceCpp("rcppdist.cpp")

ncol1 <- as.integer(10000)   ## nr of objects in data
nvar <- as.integer(50)      ## nr of variables
ncol2 <- as.integer(100)    ## nr of codes

set.seed(31)
mat1 <- matrix(rnorm(ncol1*nvar), ncol = ncol1)
mat2 <- matrix(rnorm(ncol2*nvar), ncol = ncol2)

testdist(mat1, mat2, what = "C")
testdist(mat1, mat2, what = "Call")
testdist(mat1, mat2, what = "Cpp")

require(microbenchmark)
tm <- microbenchmark(
  testdist(mat1, mat2, what = "C"),
  testdist(mat1, mat2, what = "Call"),
  testdist(mat1, mat2, what = "Cpp"),
  times = 100L)

require(ggplot2)
png("benchmark.png")
print(autoplot(tm))
dev.off()

set.seed(33)
niter <- 100L
ncols1 <- 100 * c(1, 2, 4, 8, 16, 32)
tms <- lapply(ncols1,
              function(ncol1) {
                mat1 <- matrix(rnorm(ncol1*nvar), ncol = ncol1)
                microbenchmark(testdist(mat1, mat2, what = "C"),
                               testdist(mat1, mat2, what = "Call"),
                               testdist(mat1, mat2, what = "Cpp"),
                               times = niter)
              })

library(lattice)
tms.df <- data.frame(ncols = rep(ncols1, each = niter * 3),
                     expr = c(sapply(tms, "[[", "expr")),
                     time = c(sapply(tms, "[[", "time")))
png("timings.png")
p <- xyplot(time ~ ncols, groups = expr, data = tms.df, type = c("p", "a"),
       xlab="Number of columns in mat1", auto.key = TRUE)
print(p)
dev.off()
