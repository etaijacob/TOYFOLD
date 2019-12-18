package Database::foldingRateData;

use strict;
use base 'Database::BSP2_DB';

# +-------------------+--------------+------+-----+---------+----------------+
# | Field             | Type         | Null | Key | Default | Extra          |
# +-------------------+--------------+------+-----+---------+----------------+
# | idfoldingRateData | int(11)      | NO   | PRI | NULL    | auto_increment |
# | seq               | char(56)     | YES  | MUL | NULL    |                |
# | seq1              | char(26)     | YES  | MUL | NULL    |                |
# | seq2              | char(26)     | YES  | MUL | NULL    |                |
# | percentFolded1    | int(11)      | YES  |     | NULL    |                |
# | percentFolded2    | int(11)      | YES  |     | NULL    |                |
# | method            | varchar(128) | YES  |     | NULL    |                |
# | foldingDomain     | varchar(128) | YES  |     | NULL    |                |
# | temperature       | float(6,3)   | YES  |     | NULL    |                |
# | perturbation      | float(6,3)   | YES  |     | NULL    |                |
# | reffile           | varchar(512) | YES  |     | NULL    |                |
# +-------------------+--------------+------+-----+---------+----------------+


__PACKAGE__->table('foldingRateData');
__PACKAGE__->columns(All => qw/idfoldingRateData seq seq1 seq2 percentFolded1 percentFolded2 method foldingDomain temperature perturbation reffile/);

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
	my $cntr = 0;
	my ($RMSD1, $RMSD2) = (0, 0);
	while(<IN>) {
		if(/^#KRUN\s+(\d+)/) {
			$cntr++;
		}
		if(/^\[\d+\](\S+)/) {
			$curr_seq = $1;
		}
		if(/^#DATA\s+DOMAIN_DOUBLE\s+Struct-D Energy: (\S+), MCS: (\d+)/) {
			$data{seq} = $curr_seq;
		}
		if(/^#DATA\s+DOMAIN_1\s+RMSD: (\S+), pairwise error percent: (\d+), Struct-A Energy: (\S+), MCS: (\d+)/) {
			$RMSD1++ if($1 == 0);
			$data{seq1} = $curr_seq;
		}
		if(/^#DATA\s+DOMAIN_2\s+RMSD: (\S+), pairwise error percent: (\d+), Struct-B Energy: (\S+), MCS: (\d+)/) {
			$RMSD2++ if($1 == 0);
			$data{seq2} = $curr_seq;
		}
	}
	close(IN);
	
	$data{reffile} = $file;
	$data{method} = $method;
	$data{perturbation} = $perturb if(defined($perturb));
	$data{temperature} = $temp if(defined($temp));
	$data{foldingDomain} = $foldingDomain if(defined($foldingDomain));		
	$data{percentFolded1} = $RMSD1;
	$data{percentFolded2} = $RMSD2;
	__PACKAGE__->find_or_create(%data);
	return 1;
}


1;