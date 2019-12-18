
use Database::KineticData;
exit;
use strict;

my $dir = shift;
my $method = shift;

opendir(DIR, $dir) or die "cannot open $dir";
my @files = readdir(DIR);
closedir(DIR);

foreach my $file (@files) {
	if($file =~ /.ddrf$/) {
		Database::KineticData::update_table( "$dir$file", $method); 
	 	print $file, "\t", $method, "\n";
	}
}