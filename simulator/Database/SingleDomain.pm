package Database::SingleDomain;

use strict;
use base 'Database::BSP2_DB';


__PACKAGE__->table('SingleDomain');
__PACKAGE__->columns(All => qw/idSingleDomain nativeStructIndex seq domainStruct isMinimal minimalEnergy percentFolded reffile/);

1;