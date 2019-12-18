#!/opt/compugen/perl/5.8.8/bin/perl -w


use strict;

use Getopt::PrmArgv;
use FileHandle;
use Database::DoubleDomain;


autoflush STDERR 1;
autoflush STDOUT 1;

####  Global variables  #####################################################

# my $DEBUG_LEVEL;
my $Prog = "create_doubleDomainFreeFold_cmds.pl" ;

####  The main section  #####################################################

my $sample_size = 100;
my $ddir = "/dir/leads_test/etai/SIMU/DB/dkinetics2";
my $times = 5000000;
my $prefix = "freeFoldDouble";
my $tmpdir = "/dir/leads_test/etai/SIMU/DB/tmp2/";
my $numOfSimu = 100;
my $temperature = 1.5;

my $cnt = 0;
my %seqs;
for(my $i = 25; $i <= 75; $i+=25) {
	for(my $j = 25; $j <= 75; $j+=25) {
		print STDERR "Doing : $i, $j\n";
  	my @quarter = Database::DoubleDomain->get_random($i, $i+25, $j, $j+25, $sample_size);
  	
  	foreach my $obj (@quarter) {
  		
  		my $ddseq = $obj->ddseq;
  		next if(exists($seqs{"$ddseq"}));
  		$seqs{"$ddseq"} = 1;
  		$cnt++;
  		my $fprefix = "$ddir/$cnt.q$i-q$j-t$temperature-$prefix\_";
  		print "/dir/leads_test/etai/SIMU/EXE/V21 -freeFoldDouble 55 $times 5 $numOfSimu $temperature $fprefix $ddseq 1 25 31 55 1> $tmpdir/$cnt.$prefix.stdout 2>&1\n"
#   		print $obj->ddseq, "\t", $obj->percentFolded1, "\t", $obj->percentFolded2, "\n";
  	}
  }
}