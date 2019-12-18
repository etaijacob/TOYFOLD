#!/opt/compugen/perl/5.8.8/bin/perl -w


use strict;

use Getopt::PrmArgv;
use FileHandle;
use Database::DoubleDomain;

autoflush STDERR 1;
autoflush STDOUT 1;

####  Global variables  #####################################################

# my $DEBUG_LEVEL;
my $Prog = "create_doubleDomainDB.pl" ;

####  The main section  #####################################################

my ($kineticDBdir, $fileSuffix, $linkerLength, $sequenceLength, $fdbFile, $maxMinimalStructs, $doubleDomainDBdir, $tmpfile, $workdir) ;

PrmArgv("kineticDBdir =  /dir/leads_test/etai/SIMU/DB/skinetics %s ! kinetic single domain outputdir",\$kineticDBdir,
				"fileSuffix =  freeFold_fc-itr2000000.data %s ! suffix of files to take domains and link them",\$fileSuffix,
				"doubleDomainDBdir = /dir/leads_test/etai/SIMU/DB/singleDomain %s ! single domains of doubleDomain DB dir for the output of this program", \$doubleDomainDBdir,
				"tmpfile = /dir/leads_test/etai/SIMU/DB/tmp/create_doubleDomainDB.123.tmpfile %s ! temporary file to process data", \$tmpfile,
				"fdbfile = /dir/leads_test/etai/SIMU/DB/seq_25_50_30_10_10_itr1-10.fdb %s ! fdb file (single domain src thrmodynamic DB)",\$fdbFile,
				"sequenceLength = 25 %d ! sequence of signle domain length", \$sequenceLength,
				"maxMinimalStructs = 1 %d ! maximum minimal structre to take per domain", \$maxMinimalStructs,
				"linkerLength =  5 %s ! length of polar linker between domains",\$linkerLength,
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

opendir(DIR, $kineticDBdir) or die "$kineticDBdir directory cannot be open";
my @files = readdir(DIR);
closedir(DIR);


my @outputs;
open(CMD, ">$tmpfile.cmds") or die;
my $cmdcnt = 0;
foreach my $file (@files) {
	if($file =~ /$fileSuffix/) {
		unless(-e "$tmpfile-$file") {
			print CMD "/dir/leads_test/etai/SIMU/EXE/V21 -RMSDsingle $sequenceLength $kineticDBdir/$file $fdbFile $maxMinimalStructs 1> $tmpfile-$file 2>&1\n";
			$cmdcnt++
		}
		push @outputs, "$tmpfile-$file";
	}
}
close(CMD);

if($cmdcnt > 0) {
	my $cmd = "run_commands.pl -port 19850 -cmds $tmpfile.cmds -hosts 4\@super:1-7 -mail_to etai\@compugen.co.il -cookie $tmpfile.cmds.cookie -bad_file $tmpfile.cmds.bad_file -status_file $tmpfile.cmds.status_file 1> $tmpfile.cmds.runner 2>&1";
	if(system($cmd) != 0) {
		die "could not run properly:\n$cmd"; 
	}
}
else {
	print STDERR "No files to execute\n";
}
# 		my $cmd = "/dir/leads_test/etai/SIMU/EXE/V21 -RMSD $sequenceLength $kineticDBdir/$file $fdbFile $maxMinimalStructs|";
my %singleDomainSeqs;		
foreach my $output (@outputs) {
	my ($isMinimal, $seq, $fraction, $minimalEnergy) = isMinimalStruct("$output");
# 	print "$isMinimal, $seq, $fraction $output\n";
	if($isMinimal and $fraction >= 25) {
		$singleDomainSeqs{$seq}{output} = $output;
		$singleDomainSeqs{$seq}{reffile} = "$doubleDomainDBdir/$seq.sdrf"; #single domain reference file
		unless(-e $singleDomainSeqs{$seq}{reffile}) {
			if(system("cp $singleDomainSeqs{$seq}{output} $singleDomainSeqs{$seq}{reffile}") != 0) {
				print STDERR "could not cp file $singleDomainSeqs{$seq}{output} to $singleDomainSeqs{$seq}{reffile}\n";
				exit(1);
			}
		}
		$singleDomainSeqs{$seq}{fraction} = $fraction;
		$singleDomainSeqs{$seq}{isMinimal} = $isMinimal;
		$singleDomainSeqs{$seq}{minimalEnergy} = $minimalEnergy;
	}
}

print STDERR "Working on ",scalar keys %singleDomainSeqs, " of >= 25% folded and isMinimal == 1.\n";

foreach my $domain1 (keys %singleDomainSeqs) {
	foreach my $domain2 (keys %singleDomainSeqs) {
		if($domain1 ne $domain2) {
			my $cmd = "/dir/leads_test/etai/SIMU/EXE/V21 -generateDoubleDomain $sequenceLength $singleDomainSeqs{$domain1}{reffile} $singleDomainSeqs{$domain2}{reffile} $linkerLength 0 0 1> $workdir/tmp.generateDoubleDomain.output";
			if(system("$cmd") != 0) {
				die "could not run properly:\n$cmd";
			}
			open(IN, "$workdir/tmp.generateDoubleDomain.output") or die "cannot open $workdir/tmp.generateDoubleDomain.output";
			my @dd_data = <IN>;
			my @gout = grep /No edges to create structure/, @dd_data;
			close(IN);
			if(@gout == 0) {
				my $ddseq = "$domain1\PPPPP$domain2";
# 				print "#SEQ\t$domain1\PPPPP$domain2\t$singleDomainSeqs{$domain1}{fraction}\t$singleDomainSeqs{$domain2}{fraction}\n";
# 				print "#DOMAIN_1\t$domain1\tminimal: $singleDomainSeqs{$domain1}{isMinimal}\t\%folded: $singleDomainSeqs{$domain1}{fraction}\treffile: $singleDomainSeqs{$domain1}{reffile}\n";
# 				print "#DOMAIN_2\t$domain2\tminimal: $singleDomainSeqs{$domain2}{isMinimal}\t\%folded: $singleDomainSeqs{$domain2}{fraction}\treffile: $singleDomainSeqs{$domain2}{reffile}\n";
# 				print "#DSTRUCTURE\n\n@dd_data\n";
				my $DoubleDomainObj = Database::DoubleDomain->find_or_create(ddseq => $ddseq, domainStruct => "@dd_data", domain1 => $domain1, domain2 => $domain2);
				my %toDB;
# 				idDoubleDomain sequence domain1 isMinimal1 percentFolded1 reffile1 domain2 isMinimal2 percentFolded2 reffile2
# 				$DoubleDomainObj->domain1($domain1);
				$DoubleDomainObj->reffile1($singleDomainSeqs{$domain1}{reffile});
				$DoubleDomainObj->isMinimal1($singleDomainSeqs{$domain1}{isMinimal});
				$DoubleDomainObj->percentFolded1($singleDomainSeqs{$domain1}{fraction});
				$DoubleDomainObj->minimalEnergy1($singleDomainSeqs{$domain1}{minimalEnergy});
				
# 				$DoubleDomainObj->domain2($domain2);
				$DoubleDomainObj->reffile2($singleDomainSeqs{$domain2}{reffile});
				$DoubleDomainObj->isMinimal2($singleDomainSeqs{$domain2}{isMinimal});
				$DoubleDomainObj->percentFolded2($singleDomainSeqs{$domain2}{fraction});
				$DoubleDomainObj->minimalEnergy2($singleDomainSeqs{$domain2}{minimalEnergy});
				$DoubleDomainObj->update;
				 
			}
			else {
				print STDERR "no edges for $domain1, $domain2, continuing @gout\n";
			}
				
		}
	}
}



sub isMinimalStruct {
	my $fname = shift;
# 	print $fname, "\n";
	open(IN, $fname) or die "cannot open $fname (isMinimalStruct)";
	
	my $isMinimal = 1;
	my $minimalEnergy;
	my $totalCnt = 0;
	my $zeroRmsd = 0;
	my $seq;
	while(<IN>) {
		if(/^#SEQ\s+(\S+):/) {
			$seq = $1;
		}
		elsif(/^Max: \S+, Min: (\S+), Low Range counter: \S+/) {
			$minimalEnergy = $1;
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
	return($isMinimal, $seq, int($zeroRmsd/$totalCnt*100), $minimalEnergy);
}






