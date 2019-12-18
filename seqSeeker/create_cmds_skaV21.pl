
open(IN, "seqperm 23 10000 50 30 10 10 | grep \"^\\[\" | sort -u |") or die;
my @lines = <IN>;
close(IN);
for(my $i = 1; $i <= 10; $i++) {
	print "../bin/skaV21 25 ../outputdir/seq_25_50_30_10_10_itr$i.seq ../outputdir/25mer_1_1.bindb > ../outputdir/seq_25_50_30_10_10_itr$i.fdb\n";
}




