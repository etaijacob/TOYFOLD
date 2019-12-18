package Database::KineticData;

use strict;
use base 'Database::BSP2_DB';


__PACKAGE__->table('KineticData');
__PACKAGE__->columns(All => qw/idKineticData seq seq1 seq2 lowestEnergy lowestEnergy1 lowestEnergy2 MCS MCS1 MCS2 RMSD1 RMSD2 pairwiseError1 																	 pairwiseError2 method foldingDomain temperature perturbation krun reffile/);

sub update_table {
	my $file = shift;
	my $method = shift;
	my $temp = shift;
	my $perturb = shift;
	my $foldingDomain = shift;
	
	unless(open(IN, $file)) {
		print STDERR "Cannot find file $file\n";
		return;
	}
	
	my (%data, $curr_seq);
	while(<IN>) {
		if(/^#KRUN\s+(\d+)/) {
			$data{krun} = $1;
		}
		if(/^\[\d+\](\S+)/) {
			$curr_seq = $1;
		}
		if(/^#DATA\s+DOMAIN_DOUBLE\s+Struct-D Energy: (\S+), MCS: (\d+)/) {
			$data{lowestEnergy} = $1;
			$data{MCS} = $2;
			$data{seq} = $curr_seq;
		}
		if(/^#DATA\s+DOMAIN_1\s+RMSD: (\S+), pairwise error percent: (\d+), Struct-A Energy: (\S+), MCS: (\d+)/) {
			$data{RMSD1} = $1;
			$data{pairwiseError1} = $2;
			$data{lowestEnergy1} = $3; 
			$data{MCS1} = $4;
			$data{seq1} = $curr_seq;
		}
		if(/^#DATA\s+DOMAIN_2\s+RMSD: (\S+), pairwise error percent: (\d+), Struct-B Energy: (\S+), MCS: (\d+)/) {
			$data{RMSD2} = $1;
			$data{pairwiseError2} = $2;
			$data{lowestEnergy2} = $3; 
			$data{MCS2} = $4;
			$data{seq2} = $curr_seq;
			$data{reffile} = $file;
			$data{method} = $method;
			$data{perturbation} = $perturb if(defined($perturb));
			$data{temperature} = $temp if(defined($temp));
			
			
			my $obj = __PACKAGE__->find_or_create(%data);
			$data{foldingDomain} = $foldingDomain if(defined($foldingDomain));
			$obj->foldingDomain($foldingDomain);
			$obj->update;
# 			print "$data{seq}\n";
			%data = ();
		}
	}
	close(IN);
	return 1;
}


1;