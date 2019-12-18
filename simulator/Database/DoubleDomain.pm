package Database::DoubleDomain;

use strict;
use base 'Database::BSP2_DB';


__PACKAGE__->table('DoubleDomain');
__PACKAGE__->columns(All => qw/idDoubleDomain ddseq domainStruct domain1 isMinimal1 minimalEnergy1 percentFolded1 reffile1 domain2 isMinimal2 minimalEnergy2 percentFolded2 reffile2/);

__PACKAGE__->add_constructor(get_random => 'percentFolded1 >= ? and percentFolded1 <= ? and percentFolded2 >=? and percentFolded2 <= ? order by rand() limit ?');

1;