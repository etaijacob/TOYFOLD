package Database::DoubleDomainFreeFoldKinetics;

use strict;
use base 'Database::BSP2_DB';


__PACKAGE__->table('DoubleDomainFreeFoldKinetics');
__PACKAGE__->columns(All => qw/idDoubleDomainFreeFoldKinetics ddseq seq1 seq2 percentFolded1 percentFolded2 lowerMEpercent epsilon q1 q2 reffile temperature/);

__PACKAGE__->add_constructor(get_sorted_by_lowerMEpercent => 'epsilon=? and percentFolded1>=? and percentFolded2>=? and lowerMEpercent >= ? order by lowerMEpercent desc');

__PACKAGE__->add_constructor(get_random_by_lowerMEpercent => 'epsilon=? and percentFolded1>=? and percentFolded2>=? and lowerMEpercent >= ? order by rand() limit ?');
1;