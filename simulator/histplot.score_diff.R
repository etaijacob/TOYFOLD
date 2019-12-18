
#select (percentFolded1+percentFolded2)/2, abs(percentFolded1-percentFolded2)/(percentFolded1+percentFolded2+1) as score from DoubleDomainFreeFoldKinetics where epsilon=-3.75 order by score into outfile '/dir/tmp/score.1.tmp';


v <- read.table("score.1.tmp", header=F);

mean(abs(v[,2]))
[1] 0.3565019
mean(abs(v[1:120,1]))
[1] 31.68333
> mean(abs(v[960:1080,1]))
[1] 16.23967

mean(abs(v[,1]))
[1] 29.11528
mean(abs(v[1:120,2]))
[1] 0.02399917
mean(abs(v[960:1080,2]))
[1] 0.9544992


N <- c(0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80)
jpeg("score.1.jpeg");
par(mfrow=c(3,1))
hist(v[,1],breaks=N,xlim=c(0,80),ylim=c(0,0.08),xlab="% folded",freq=FALSE,col='red',main='All double domain sequences (mean=29)')
hist(v[1:120,1],breaks=N,xlim=c(0,80),ylim=c(0,0.08),xlab="% folded",freq=FALSE,col='red',main='The 120 sequences with the smallest difference in % folded between domains (mean=32)')
hist(v[960:1080,1],breaks=N,xlim=c(0,80),ylim=c(0,0.08),xlab="% folded",freq=FALSE,col='red',main='The 120 sequences with the largest difference in % folded between domains (mean=16)')
dev.off()
