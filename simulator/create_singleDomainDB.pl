#!/opt/perl/5.8.8/bin/perl -w


use strict;

use Getopt::PrmArgv;
use FileHandle;
use Database::SingleDomain;

autoflush STDERR 1;
autoflush STDOUT 1;

####  Global variables  #####################################################

# my $DEBUG_LEVEL;
my $Prog = "create_singleDomainDB.pl" ;

####  The main section  #####################################################

my ($kineticDBdir, $fileSuffix, $sequenceLength, $fdbFile, $maxMinimalStructs, $singleDomainDBdir, $tmpfile, $workdir) ;

PrmArgv("kineticDBdir =  /dir/leads_test/etai/SIMU/DB/skinetics %s ! kinetic single domain outputdir",\$kineticDBdir,
				"fileSuffix =  freeFold_fc-itr2000000.data %s ! suffix of files to take domains and link them",\$fileSuffix,
				"singleDomainDBdir = /dir/leads_test/etai/SIMU/DB/singleDomain %s ! single domains for the output of this program", \$singleDomainDBdir,
				"tmpfile = /dir/leads_test/etai/SIMU/DB/tmp/create_singleDomainDB.123.tmpfile %s ! temporary file to process data", \$tmpfile,
				"fdbfile = /dir/leads_test/etai/SIMU/DB/fdb/seq_25_50_30_10_10_itr1-10.fdb %s ! fdb file (single domain src thrmodynamic DB)",\$fdbFile,
				"sequenceLength = 25 %d ! sequence of signle domain length", \$sequenceLength,
				"maxMinimalStructs = 10000 %d ! maximum minimal structre to take per domain", \$maxMinimalStructs,
				"workdir = /dir/leads_test/etai/SIMU/work %s ! working dir for tmo files", \$workdir,
       );

# check needed variables
my %NeededVars = (kineticDBdir => $kineticDBdir, fileSuffix => $fileSuffix, 
									sequenceLength => $sequenceLength, fdbFile => $fdbFile);

# Segment->set_DEBUG ($DEBUG_LEVEL);

foreach my $var (keys %NeededVars){
  die "$Prog\::FATAL:Missing parameter '$var'"
    if (! defined $NeededVars{$var} || $NeededVars{$var} eq "");
}

opendir(DIR, $kineticDBdir) or die "$kineticDBdir directory cannot be open";
my @files = readdir(DIR);
closedir(DIR);


my @outputs;
open(CMD, ">$tmpfile.cmds") or die;
my $cmdcnt = 0;
foreach my $file (@files) {
	if($file =~ /$fileSuffix/) {
		unless(-e "$tmpfile-$file") {
			print CMD "../bin/V21 -RMSDsingle $sequenceLength $kineticDBdir/$file $fdbFile $maxMinimalStructs 1> $tmpfile-$file 2>&1\n";
			$cmdcnt++
		}
		push @outputs, "$tmpfile-$file";
	}
}
close(CMD);

if($cmdcnt > 0) {
	print STDERR "have $cmdcnt cmds to run\n";
	my $cmd = "run_commands.pl -port 19850 -cmds $tmpfile.cmds -hosts 4\@blade:11-23 -mail_to etai\@compugen.co.il -cookie $tmpfile.cmds.cookie -bad_file $tmpfile.cmds.bad_file -status_file $tmpfile.cmds.status_file 1> $tmpfile.cmds.runner 2>&1";
	if(system($cmd) != 0) {
		die "could not run properly:\n$cmd"; 
	}
}
else {
	print STDERR "No files to execute\n";
}

foreach my $output (@outputs) {
	
	# 	print "$isMinimal, $seq, $fraction $output\n";
	for(my $nas = 0; $nas < $maxMinimalStructs; $nas++) {
		my ($isMinimal, $seq, $fraction, $minimalEnergy, $struct) = isMinimalStruct("$output", $nas);
		last unless(defined($isMinimal));
		my %singleDomainSeqs;	
		
		$singleDomainSeqs{output} = $output;
		$singleDomainSeqs{reffile} = "$singleDomainDBdir/$seq.sdrf"; #single domain reference file
		unless(-e $singleDomainSeqs{reffile}) {
			if(system("cp $singleDomainSeqs{output} $singleDomainSeqs{reffile}") != 0) {
				print STDERR "could not cp file $singleDomainSeqs{output} to $singleDomainSeqs{reffile}\n";
				exit(1);
			}
		}
		
		$singleDomainSeqs{fraction} = $fraction;
		$singleDomainSeqs{isMinimal} = $isMinimal;
		$singleDomainSeqs{minimalEnergy} = $minimalEnergy;
		
		my $SingleDomainObj = Database::SingleDomain->find_or_create(seq => $seq, nativeStructIndex => $nas);
		$SingleDomainObj->reffile($singleDomainSeqs{reffile});
		$SingleDomainObj->isMinimal($singleDomainSeqs{isMinimal});
		$SingleDomainObj->percentFolded($singleDomainSeqs{fraction});
		$SingleDomainObj->minimalEnergy($singleDomainSeqs{minimalEnergy});
		$SingleDomainObj->domainStruct($struct);
		$SingleDomainObj->update;
		
	}
	
}

print STDERR "Finsihed Working..\n";



sub isMinimalStruct {
	my $fname = shift;
	my $nas = shift;
# 	print $fname, "\n";
	open(IN, $fname) or die "cannot open $fname (isMinimalStruct)";
	
	my $isMinimal = 1;
	my $minimalEnergy;
	my $totalCnt = 0;
	my $zeroRmsd = 0;
	my $seq;
	my $struct;
	
	while(<IN>) {
		if(/^#SEQ\s+(\S+):/) {
			$seq = $1;
			last;
		}
	}
	while(<IN>) {
		if(/^#NAS\s+$nas/) {
			while(<IN>) {
				if(/^\[\d+/) {
					$struct = $_;
					last;
				}
			}
			while(<IN>) {
				if(/Additional minimal structures/) {
					last;
				}
				else {
					if(/^Max: \S+, Min: (\S+), Low Range counter: \S+/) {
						$minimalEnergy = $1;
					}
					$struct .= $_;
				}
			}
			print $struct;
			last;		
		}
		else {
			close(IN);
			return;
		}
	}
	while(<IN>) {
		if(/^#NAS\s+\d+/) {
			last;
		}
		#DATA   RMSD: 1.63987, pairwise error percent: 70, Struct Energy: -12.25, MCS: 350908
		#DATA   RMSD: 0.296412, pairwise error percent: 7, Struct Energy: -13, MCS: 745486
		elsif(/^#DATA\s+RMSD: (\S+),.+Struct Energy: (\S+), MCS:.+/) {
			my $rmsd = $1;
			my $kenergy = $2;
# 			print "$rmsd $kenergy $seq $minimalEnergy!\n";
			$totalCnt++;
			if($rmsd == 0 and $kenergy == $minimalEnergy) {
				$zeroRmsd++;
			}
			elsif($rmsd > 0 and $kenergy < $minimalEnergy) {
				$isMinimal = 0;
			}
		}
	}
	close(IN);
# 	print $totalCnt, "!!!!!!!!!!!!!! $seq $zeroRmsd\n";
	return($isMinimal, $seq, int($zeroRmsd/$totalCnt*100), $minimalEnergy, $struct);
}






