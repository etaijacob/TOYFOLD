#!/opt/compugen/perl/5.8.8/bin/perl
use strict;
use R;
use RReferences;


BEGIN {

  # R initializing

  R::initR("--no-save","--silent");
# 	R::library("geneplotter");  ## from BioConductor
# 	R::require("RColorBrewer"); ## from CRAN
# 	R::require("Hmisc");
	R::source("~/My\ Documents/grid/simulator/produceGraphs.R"); 
	
	R::eval (q/
		getPvalue <<- function(fname) {
		return(getChiSqrPval(fname));
	}
	/);
	
	R::eval (q/
		plotGraphs <<- function(fname, fout) {
		plotAll(fname, fout);
	}
	/);
}


# print R::getPvalue(shift);
R::plotGraphs(shift,shift);
# gtesting();
# printPvals(shift);
sub printPvals {
	my $dir = shift;
	opendir(DIR, $dir);
	my @files = readdir(DIR);
	closedir(DIR);

 
	foreach my $file (@files) {
# 		print "$file\n";
		if($file =~ /fast.(\d+).txt.td/) {
			my $name = $1;
# 			print "$dir$file\n";
			my @vals = R::getPvalue("$dir$file");
			print "$name ";
			print "$_ " for(@vals[0..3]); 
			if($vals[-1] eq "nan" or $vals[-1] eq "NA") {
				print "1.0\n";
			}
			else {
				print "$vals[-1]\n";
			}
		}
	}	

}



