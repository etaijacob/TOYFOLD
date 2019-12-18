#!/opt/compugen/perl/5.8.8/bin/perl -w


use strict;

use Getopt::PrmArgv;
use FileHandle;
use Database::DoubleDomain;
use Database::SingleDomain;
use Database::DoubleDomainFreeFoldKinetics;


autoflush STDERR 1;
autoflush STDOUT 1;

####  Global variables  #####################################################

# my $DEBUG_LEVEL;
my $Prog = "create_doubleDomainKineticFiles.pl" ;

####  The main section  #####################################################

my ($kineticDBdir, $fileSuffix, $linkerLength, $sequenceLength, $fdbFile, $maxMinimalStructs, $doubleDomainDBdir, $tmpfile, $workdir, $EPSILON, $temperature) ;

PrmArgv("kineticDBdir =  /dir/leads_test/etai/SIMU/DB/dkinetics2 %s ! kinetic single domain outputdir",\$kineticDBdir,
				"fileSuffix =  freeFoldDouble_fc-itr5000000.data %s ! suffix of files to take domains and link them",\$fileSuffix,
				"doubleDomainDBdir = /dir/leads_test/etai/SIMU/DB/doubleDomain %s ! doubleDomain DB dir for the output of this program", \$doubleDomainDBdir,
				"tmpfile = /dir/leads_test/etai/SIMU/DB/tmp2/create_doubleDomainKineticFiles.123.tmpfile %s ! temporary file to process data", \$tmpfile,
				"fdbFile = /dir/leads_test/etai/SIMU/DB/fdb/ddseq_25_50_30_10_10_v1.0.t1.5.fdb %s ! fdb file (output for this program. If doesn't exists, creates one)",\$fdbFile,
				"sequenceLength = 25 %d ! sequence of signle domain length", \$sequenceLength,
				"epsilon = 0.0 %f ! the energy gap tolerance between energy of two domains and the total minimal energy of the double domain", \$EPSILON,
				"maxMinimalStructs = 1 %d ! maximum minimal structre to take per domain", \$maxMinimalStructs,
				"linkerLength =  5 %s ! length of polar linker between domains",\$linkerLength,
				"temperature = 1.5 %f ! temperature of this batch run", \$temperature,
				"workdir = /dir/leads_test/etai/SIMU/work %s ! working dir for tmo files", \$workdir,
       );

# check needed variables
my %NeededVars = (kineticDBdir => $kineticDBdir, fileSuffix => $fileSuffix, 
									linkerLength => $linkerLength, sequenceLength => $sequenceLength, fdbFile => $fdbFile);

# Segment->set_DEBUG ($DEBUG_LEVEL);

foreach my $var (keys %NeededVars){
  die "$Prog\::FATAL:Missing parameter '$var'"
    if (! defined $NeededVars{$var} || $NeededVars{$var} eq "");
}
my $ddsize = $sequenceLength*2 + $linkerLength;

opendir(DIR, $kineticDBdir) or die "$kineticDBdir directory cannot be open";
my @files = readdir(DIR);
closedir(DIR);

# my $ddsize = $sequenceLength*2 + $linkerLength;
my %ddseqs;
unless(-e $fdbFile) {
	foreach my $file (@files) {
		if($file =~ /$fileSuffix/) {
			open(IN, "$kineticDBdir/$file") or die "cannot open file: $kineticDBdir/$file";
			while(<IN>) {
				if(/^\[$ddsize\](\S+)/) {
					my $seq = $1;
# 					print $seq, "\n";
					$ddseqs{$seq} = $file;
					last;
				}
			}
			close(IN);
		}
	}
	open(FDB, ">$fdbFile") or die "cannot open $fdbFile for writing";
	print STDERR "FDB file doesn't exist or size = 0, producing fdb file: $fdbFile\n";
	foreach my $ddseq (keys %ddseqs) {
		my @fdbs = Database::DoubleDomain->search(ddseq => $ddseq);
		foreach my $fdb (@fdbs) {
			my @struct = split(/\n/, $fdb->domainStruct);
			foreach my $line (@struct) {
				$line =~ s/^\s//;
				print FDB $line, "\n";
			}
		}
	}
	close(FDB);
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
# 			print CMD "/dir/leads_test/etai/SIMU/EXE/V21 -RMSDsingle $sequenceLength $kineticDBdir/$file $fdbFile $maxMinimalStructs 1> $tmpfile-$file 2>&1\n";
			print CMD "/dir/leads_test/etai/SIMU/EXE/V21 -RMSDdouble $ddsize $kineticDBdir/$file $fdbFile $maxMinimalStructs $sequenceLength $linkerLength 1> $tmpfile-$file 2>&1\n";
			$cmdcnt++
		}
		push @outputs, "$tmpfile-$file";
	}
}
close(CMD);

if($cmdcnt > 0) {
	my $cmd = "run_commands.pl -port 19710 -cmds $tmpfile.cmds -hosts 4\@blade:11-23 -mail_to etai\@compugen.co.il -cookie $tmpfile.cmds.cookie -bad_file $tmpfile.cmds.bad_file -status_file $tmpfile.cmds.status_file 1> $tmpfile.cmds.runner 2>&1";
	if(system($cmd) != 0) {
		die "could not run properly:\n$cmd"; 
	}
}
else {
	print STDERR "No files to execute on runcommands (RMSDdouble). Continuing\n";
}

foreach my $output (@outputs) {
	for(my $nas = 0; $nas < $maxMinimalStructs; $nas++) {
		my($isMinimal, $seq, $seq1, $seq2, $frac1, $frac2, $lowerMEcntr, $struct1, $struct2) = isMinimalDoubleStruct("$output", $nas);
		last unless(defined($isMinimal));
		my $reffile = "$doubleDomainDBdir/$seq.ddrf";
		unless(-e $reffile) {
			if(system("cp $output $reffile") != 0) {
				print STDERR "could not cp file $output to $reffile\n";
				exit(1);
			}
		}
		if($output =~ /.q(\d+)-q(\d+)-/) {
			print "$seq, $seq1, $seq2, $frac1, $frac2, $lowerMEcntr, $EPSILON, $1, $2, $reffile\n";
			Database::DoubleDomainFreeFoldKinetics->find_or_create({ddseq => $seq, seq1 => $seq1, seq2 => $seq2, percentFolded1 => $frac1, percentFolded2 => $frac2, lowerMEpercent => $lowerMEcntr, epsilon => $EPSILON, q1 => $1, q2 => $2, reffile => $reffile, temperature => $temperature});
		}
	}
}

sub isMinimalDoubleStruct {
	my $fname = shift;
	my $nas = shift;
# 	print $fname, "\n";
	open(IN, $fname) or die "cannot open $fname (isMinimalStruct)";
	
	my $isMinimal = 1;
	my $minimalEnergy;
	my $totalCnt = 0;
	my $lowerMEcntr = 0;
	my ($zeroRMSD_1, $zeroRMSD_2) = (0, 0);
	my $seq;
	my ($struct1, $struct2, $seq1, $seq2);
	
	while(<IN>) {
		if(/^#SEQ\s+(\S+):/) {
			$seq = $1;
			last;
		}
	}
	while(<IN>) {
		if(/^#NAS\s+$nas/) {
			while(<IN>) {
				if(/^\[\d+](\S+)/) {
					$seq1 = $1;
					$struct1 = $_;
					last;
				}
			}
			while(<IN>) {
				if(/\$/) {
					$struct2 .= $_;
					last;
				}
				else {
					$struct1 .= $_;
				}
			}
			while(<IN>) {
				if(/^\[\d+](\S+)/) {
					$seq2 = $1;
					$struct2 = $_;
					last;
				}
			}
			while(<IN>) {
				if(/\$/) {
					$struct2 .= $_;
					last;
				}
				else {
					$struct2 .= $_;
				}
			}
			last;		
		}
		else {
			close(IN);
			return;
		}
	}
	my @sd1 = Database::SingleDomain->search(seq => $seq1, nativeStructIndex => $nas);
	my @sd2 = Database::SingleDomain->search(seq => $seq2, nativeStructIndex => $nas);
	my $ME1 = $sd1[0]->minimalEnergy;
	my $ME2 = $sd2[0]->minimalEnergy;
	my $MED = $ME1 + $ME2 + $EPSILON;
# 	print "$seq1\t$ME1\n";
# 	print "$seq2\t$ME2\n";
	
	while(<IN>) {
		if(/^#NAS\s+\d+/) {
			last;
		}
		
		#DATA   DOMAIN_DOUBLE   Struct-D Energy: -29.25, MCS: 3607974
		elsif(/^#DATA\s+DOMAIN_DOUBLE\s+Struct-D Energy: (\S+), MCS:.+/) {
			my $kenergy = $1;
# 			print "$rmsd $kenergy $seq $minimalEnergy!\n";
			$totalCnt++;
# 			print $kenergy-$MED, "\n";
			if($kenergy < $MED) {
				$isMinimal = 0;
			}
			else {
				$lowerMEcntr++;
			}
		}
		#DATA   DOMAIN_1        RMSD: 0.986829, pairwise error percent: 75, Struct-A Energy: -10, MCS: 117561
		elsif(/^#DATA\s+DOMAIN_1\s+RMSD: (\S+), pairwise error percent: (\d+), Struct-A Energy: (\S+), MCS: (\d+)/) {
			my $rmsd = $1;
			my $pwerror = $1;
			my $kenergy = $3;
			if($rmsd == 0 and $kenergy == $ME1) {
				$zeroRMSD_1++;
			}
		}
		elsif(/^#DATA\s+DOMAIN_2\s+RMSD: (\S+), pairwise error percent: (\d+), Struct-B Energy: (\S+), MCS: (\d+)/) {
			my $rmsd = $1;
			my $pwerror = $1;
			my $kenergy = $3;
			if($rmsd == 0 and $kenergy == $ME2) {
				$zeroRMSD_2++;
			}
		}
	}
	close(IN);
# 	print $totalCnt, "!!!!!!!!!!!!!! $seq $zeroRmsd\n";
	return($isMinimal, $seq, $seq1, $seq2, int($zeroRMSD_1/$totalCnt*100), int($zeroRMSD_2/$totalCnt*100), int($lowerMEcntr/$totalCnt*100), $struct1, $struct2);
}






