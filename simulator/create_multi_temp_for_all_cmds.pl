#!/opt/compugen/perl/5.8.8/bin/perl -w


use strict;

use Getopt::PrmArgv;
use FileHandle;
use Database::DoubleDomainFreeFoldKinetics;


autoflush STDERR 1;
autoflush STDOUT 1;

####  Global variables  #####################################################

# my $DEBUG_LEVEL;
my $Prog = "create_doubleDomainRestrictedFold_cmds.pl" ;

####  The main section  #####################################################

my $ddir = "/dir/leads_test/etai/SIMU/DB/restricted_dkinetics";
my $times = 4000000;
my $prefix = "freeFoldMultiTempDouble";
my $tmpdir = "/dir/leads_test/etai/SIMU/DB/tmp/";
my $fdbfile = "/dir/leads_test/etai/SIMU/DB/fdb/ddseq_25_50_30_10_10_v1.0.fdb";
my $numOfSimu = 100;
my $sample_size = 100;
 

#epsilon=? and percentFolded1>=? and percentFolded2>=? and lowerMEpercent >= ?
# my @list = Database::DoubleDomainFreeFoldKinetics->get_sorted_by_lowerMEpercent(-3.75, 10, 10, 50);

#epsilon=? and percentFolded1>=? and percentFolded2>=? and lowerMEpercent >= ?
my @list = Database::DoubleDomainFreeFoldKinetics->get_random_by_lowerMEpercent(-3.75, 50, 50, 50, $sample_size);

my $cnt = 0;

my @T = qw/0.25 0.5 0.75 1 1.25 1.5 1.75 2/;

foreach my $T (@T) {
	foreach my $dd (@list) {
		$cnt++;
		my $ddseq = $dd->ddseq;
		my ($outputfile, $stdoutfile);
		my $outfilePrefix = "$ddir/$cnt.$prefix";
		my $stdoutPrefix = "$tmpdir/$cnt.$prefix";
		
	#UF->FF
		$outputfile = "$outfilePrefix.t$T.UF-FF.";
		$stdoutfile = "$stdoutPrefix.t$T.UF-FF.stdout";
		print "/dir/leads_test/etai/SIMU/EXE/V21 -freeFoldMultiTempDouble 55 $times 5 $numOfSimu $outputfile $ddseq 1 25 31 55 $T 1 0 1 B $fdbfile 0 1>$stdoutfile 2>&1\n";
	
	#FU->FF:
		$outputfile = "$outfilePrefix.t$T.FU-FF.";
		$stdoutfile = "$stdoutPrefix.t$T.FU-FF.stdout";
		print "/dir/leads_test/etai/SIMU/EXE/V21 -freeFoldMultiTempDouble 55 $times 5 $numOfSimu $outputfile $ddseq 1 25 31 55 0 1 $T 1 A $fdbfile 0 1>$stdoutfile 2>&1\n";
	
	#UU->UF:
		$outputfile = "$outfilePrefix.t$T.UU-UF.";
		$stdoutfile = "$stdoutPrefix.t$T.UU-UF.stdout";
		print "/dir/leads_test/etai/SIMU/EXE/V21 -freeFoldMultiTempDouble 55 $times 5 $numOfSimu $outputfile $ddseq 1 25 31 55 10 0.05 $T 1 1>$stdoutfile 2>&1\n";
	
	#UU->FU:
		$outputfile = "$outfilePrefix.t$T.UU-FU.";
		$stdoutfile = "$stdoutPrefix.t$T.UU-FU.stdout";
		print "/dir/leads_test/etai/SIMU/EXE/V21 -freeFoldMultiTempDouble 55 $times 5 $numOfSimu $outputfile $ddseq 1 25 31 55 $T 1 10 0.05 1>$stdoutfile 2>&1\n";
		
		$outputfile = "$outfilePrefix.t$T.XX-XX.";
		$stdoutfile = "$stdoutPrefix.t$T.XX-XX.stdout";
		print "/dir/leads_test/etai/SIMU/EXE/V21 -freeFoldDouble 55 $times 5 $numOfSimu $T $outputfile $ddseq 1 25 31 55 1> $stdoutfile 2>&1\n"
	
	}
}
