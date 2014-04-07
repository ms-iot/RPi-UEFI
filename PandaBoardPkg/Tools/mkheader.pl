#!/usr/bin/perl

my $size = -s "$ARGV[0]";
#my $addr = 0x80008000;
my $addr = 0x80008208;

open OUTPUT_FILE, ">$ARGV[1]";
open INPUT_FILE, "<$ARGV[0]";

binmode OUTPUT_FILE;
binmode INPUT_FILE;

$size-=0x200;
$size-=8;

print OUTPUT_FILE chr($size&0xFF);
$size>>=8;
print OUTPUT_FILE chr($size&0xFF);
$size>>=8;
print OUTPUT_FILE chr($size&0xFF);
$size>>=8;
print OUTPUT_FILE chr($size&0xFF);

print OUTPUT_FILE chr($addr&0xFF);
$addr>>=8;
print OUTPUT_FILE chr($addr&0xFF);
$addr>>=8;
print OUTPUT_FILE chr($addr&0xFF);
$addr>>=8;
print OUTPUT_FILE chr($addr&0xFF);

seek INPUT_FILE, 520, 0;

while(<INPUT_FILE>) {
  print OUTPUT_FILE $_;
}

close OUTPUT_FILE;
close INPUT_FILE;
