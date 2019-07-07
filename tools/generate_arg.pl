#!/usr/bin/env perl

use strict;
use warnings;

my $strings = [qw(@ A R T a c  e f l r t u -- ~/ ../ . DOESNOTEXIST)];

sub combine;
sub permute;

if (!($ARGV[0]))
{
	print "usage: ./generate_arg.pl [OPTION]\nOptions: combine, permute\n";
	exit (0);
}
elsif (!($ARGV[0] cmp 'combine'))
{
	print "@$_\n" for combine $strings, 2;
}
elsif (!($ARGV[0] cmp 'permute'))
{
	print "@$_\n" for permute $strings, 2;
}
else
{
	print "usage: ./generate_arg.pl [OPTION]\nOptions: combine, permute\n";
	exit(0);
}

sub combine {

	my ($list, $n) = @_;
	die "Insufficient list members" if $n > @$list;

	return map [$_], @$list if $n <= 1;

	my @comb;

	for (my $i = 0; $i+$n <= @$list; ++$i) {
		my $val  = $list->[$i];
		my @rest = @$list[$i+1..$#$list];
		push @comb, [$val, @$_] for combine \@rest, $n-1;
	}

	return @comb;
}

sub permute {

	my ($list, $n) = @_;
	die "Insufficient list members" if $n > @$list;

	return map [$_], @$list if $n <= 1;

	my @comb;

	for my $i (0 .. $#$list) {
		my @rest = @$list;
		my $val  = splice @rest, $i, 1;
		push @comb, [$val, @$_] for permute \@rest, $n-1;
	}

	return @comb;
}
