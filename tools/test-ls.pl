#!/usr/bin/env perl
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test-ls.pl                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/24 12:39:54 by abarthel          #+#    #+#              #
#    Updated: 2019/06/24 12:40:40 by abarthel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

use warnings;
use strict;
use 5.010;
use Term::ANSIColor;

sub logError{

	my $digits = sprintf("%02d", $_[2]); 

	my $filename1 = "error_ls${digits}.log";
	open(FH, '>', $filename1) or die $!;
	print FH $_[0];
	close(FH);
	
	my $filename2 = "error_ftls${digits}.log";
	open(FH, '>', $filename2) or die $!;
	print FH $_[1];
	close(FH);
	
	# Comment these two lines to avoid making the diff and removing output files
	system("diff ${filename1} ${filename2} > diff_test${digits}.log");
	system("rm -f error_*");
}

sub compareOutput{

	my $lsOutput = $_[0];
	my $ftlsOutput = $_[1];

	if (($ftlsOutput ne $lsOutput))
	{
		print colored( 'KO', 'red' ), "\n";
		#print "\t\t", colored('ls output:', 'red underline'), "\n";
		#print "$lsOutput";
		#print "\t\t", colored('./ft_ls output:', 'red underline'), "\n";
		#print "$ftlsOutput";
		logError($lsOutput, $ftlsOutput, $_[2]);
	}
	else
	{
		print colored( 'OK', 'green' ), "\n";
	}
}

sub testFile{

	if (not -e '../src/ft_ls') {
		print colored( 'ft_ls does not exist, please compile it !', 'red' ), "\n";
		exit(1);
	}
}

testFile;
system("rm -f diff_*");
open my $in, "<:encoding(utf8)", $ARGV[0] or die "$ARGV[0]: $!";
my @lines = <$in>;
close $in;
my $testnb = -1;
for my $line (@lines) {
	$testnb++;
	my $ls=`/bin/ls ${line}`;
	my $ftls=`../src/ft_ls ${line}`;
	print colored("Test${testnb}: ${line}", 'rgb222');
	compareOutput($ls, $ftls, $testnb);
	print "\n";
}
