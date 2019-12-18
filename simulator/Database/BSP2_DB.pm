package Database::BSP2_DB;

use strict;
use warnings;
use base 'Class::DBI';

my ($dsn, $username, $password) = getConfig();

Database::BSP2_DB->set_db('Main',
                             $dsn,
                             $username,
                             $password,
                             {AutoCommit=>1},
                            );

sub getConfig {
       return ('dbi:mysql:BSP2:datacenter', 'etai', 'etai123');
}

1;