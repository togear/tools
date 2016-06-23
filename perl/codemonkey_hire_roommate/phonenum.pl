#!/usr/bin/perl
@a = qw/8 2 1 0 3/;
@b = qw/2 0 3 2 4 0 1 3 2 3 3/;
print join("",map{$a[$_]} @b),"\n";
