
use Database::SingleDomain;

use strict;
my $bin = 25;
my $length = 25;
my @header;

for(my $i = 1; $i <= $length; $i++) {
	push @header, "res_$i";
}
push @header, "Contact_0_1";
for(my $i = 0; $i <= $length - 2; $i++) { 
	for(my $j = $i + 2; $j <= $length; $j++) { 
		push @header, "Contact_$i\_$j";
	}
}
for(my $i = 1; $i <= 8; $i++) {
	push @header, "thrmo_sdv_$i";
}
push @header, "class";

print join("\t", @header), "\n";

my @domains = Database::SingleDomain->search(nativeStructIndex => 0);
my $fdbfile = "/dir/leads_test/etai/SIMU/DB/fdb/seq_25_50_30_10_10_itr1-10.fdb";
foreach my $domain (@domains) {
# 	print $domain->seq, "\t", $domain->percentFolded, "\n";
	my $cmd = "/dir/leads_test/etai/SIMU/EXE/V21.1 -getSingleDomainContactMap 25 $fdbfile 1 ".$domain->seq;
	open(IN,  "$cmd |") or die "cannot open...";
# 	print $cmd, "\n";
	my @sdv;
	while(<IN>) {
		chomp;
		if(/^Low range SDV/) {
			for(my $i = 0; $i < 8; $i++) {
				my $str = <IN>;
				if($str =~ /(\S+)\s+(\d+)/) {
					push @sdv, $2;
				}
			}
		}
		if(/^\$Contact vector/) {
			my $str = <IN>; $str = <IN>; $str = <IN>; 
# 			print "$str\n";
			chomp $str;
			my @contacts = split(/ /, $str);
			my @seq = split(//, $domain->seq);
			print join("\t", (@seq, @contacts, @sdv)), "\t", "FR_", int(($domain->percentFolded == 0 ? 0 : $domain->percentFolded - 1)/$bin)*$bin, "\n"; 
		} 
	}
	close(IN);
	
}
