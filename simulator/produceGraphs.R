
library("geneplotter")  ## from BioConductor
require("RColorBrewer") ## from CRAN
require(Hmisc)

plotScatter <- function(fname) {
	v <- read.table(fname, header=T);
  x1 <- v[,c(1,3)];
  x2 <- v[,c(5,7)];

  layout(matrix(1:4, ncol=2, byrow=TRUE))
  op <- par(mar=rep(2,4))

  smoothScatter(x1, nrpoints=0)
  smoothScatter(x1)
   smoothScatter(x1, nrpoints=Inf,
                 colramp=colorRampPalette(brewer.pal(9,"YlOrRd")),
                 bandwidth=40)
  colors  <- densCols(x1)
  plot(x1, col=colors, pch=20)
par(op)

}

plotDots <- function (fname) {
	v <- read.table(fname, header=T);
	plot(v[,c(1,3)], ann=FALSE, type="n"); points(v[,c(1,3)], bg="limegreen", pch=21); points(v[,c(5,7)], bg="red", pch=21);
	title(main="Scatter plot of folding",
				xlab="First passage time (FPT)", ylab="RMSD");
}

plotHists <- function(fname) {

	options(digits=3) 
	set.seed(1)
	
	
	v <- read.table(fname, header=T);
	leftDomain <- v[,3];
  rightDomain <- v[,7];
# 	age <- rnorm(1000,50,10) 
# 	sex <- sample(c('female','male'),1000,TRUE) 
# xlim=c(-.06,.06),
	out <- histbackback(leftDomain, rightDomain,probability=TRUE, ylab="RMSD", main = 'Hist RMSD to native structure')
	#! just adding color
	barplot(-out$left, col="limegreen" , horiz=TRUE, space=0, add=TRUE, axes=FALSE) 
	barplot(out$right, col="red", horiz=TRUE, space=0, add=TRUE, axes=FALSE) 

}

plotDensityRMSD <- function(fname) {
	v <- read.table(fname, header=T);
	x1 <- density(v[,3]);
  x2 <- density(v[,7]);
	plot(range(min(min(x1$x), min(x2$x)), max(max(x1$x), max(x2$x))), range(min(min(x1$y), min(x2$y)), max(max(x1$y), max(x2$y))), type = "n", main = "RMSD Density function",xlab = "RMSD", ylab = "Density"); 
	lines(x1, col="limegreen"); lines(x2, col="red");
}

plotDensityENERGY <- function(fname) {
	v <- read.table(fname, header=T);
	x1 <- density(v[,2])
  x2 <- density(v[,6])
	plot(range(min(min(x1$x), min(x2$x)), max(max(x1$x), max(x2$x))), range(min(min(x1$y), min(x2$y)), max(max(x1$y), max(x2$y))), type = "n", main = "ENERGY Density function",xlab = "MINIMAL ENERGY", ylab = "Density"); 
	lines(x1, col="limegreen"); lines(x2, col="red");
}

plotDensity2VecsPvals <- function(fname1, fname2) {
	s <- read.table(fname1, header=F);
	f <- read.table(fname2, header=F);
	x1 <- density(s[,6])
  x2 <- density(f[,6])
	plot(range(min(min(x1$x), min(x2$x)), max(max(x1$x), max(x2$x))), range(min(min(x1$y), min(x2$y)), max(max(x1$y), max(x2$y))), type = "n", main = "Chi-sqr test p-val Density function",xlab = "P-value", ylab = "Density"); 
	lines(x1, col="blue"); lines(x2, col="red");
	legend("topright", c("Slow","Fast"), col=c("blue","red"), lty=c(1,1), lwd=c(2.5,2.5), inset = .02)
}

plotHists2VecsPvals <- function(fname1, fname2) {

	options(digits=3) 
	set.seed(1)

	s <- read.table(fname1, header=T);
	f <- read.table(fname2, header=T);
	Slow <- s[,6];
  Fast <- f[,6];
	out <- histbackback(Slow, Fast, probability=TRUE, ylab="P-value", main = 'Hist of P-value of Chi-sqr')
	#! just adding color
	barplot(-out$left, col="blue" , horiz=TRUE, space=0, add=TRUE, axes=FALSE) 
	barplot(out$right, col="red", horiz=TRUE, space=0, add=TRUE, axes=FALSE) 

}


plotAll <- function(fname, fout) {
jpeg(file=fout);
par(mfrow=c(2,2))
plotDots(fname)
plotHists(fname)
plotDensityRMSD(fname)
plotDensityENERGY(fname)
dev.off();
}

plotChiSqr <- function(fname) {

}

getChiSqrPval <- function(fname) {
v <- read.table(fname, header=T);
freq = c(sum(v[,3]==0), sum(v[,3]>0));
probs = c(sum(v[,7]==0), sum(v[,7]>0))/length(v[,7]);
chst <- chisq.test(freq, p=probs, simulate.p.value = TRUE, B = 1000)
return(c(freq, probs, chst$p.value));
}