my @result = ();
my $skip = 1;

while (<>) {
	if (/^\s*$/) {
		if ($skip == 0) {
			push(@result, "\n");
		}
		$skip = 1;
	} else {
		s/^\s*(.*?)\s*$/\1/;
		s/\s+/ /g;

		push(@result, $_ . "\n");
		$skip = 0;
	}
}

while ((scalar @result) != 0 && @result[(scalar @result) - 1] =~ /^\s*$/) { pop(@result); }

foreach (@result) {
	print $_;
}