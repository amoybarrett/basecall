#!/bin/perl -w

use lib "/libPath";
use PerlIO::gzip;
use strict;

my $leng = @ARGV;

if($leng < 3){
        die("Example:\n\t--perl merge.pl [dest_file] [source_file] [flag 1 for AG, 2 for CT, 3 for AG and CT]\n");
}

my $destfile = shift;

open OUT, ">:gzip",$destfile or die("can't open file $destfile:$!\n");

my $file;

$file = shift;
if($file =~ /\.gz$/){
        open IN, "gzip -dc $file |" or die("Can't read file with gzip:$file\n");
}else{
        open IN, "<$file" or die("Can't read file with gzip:$file\n");
}

my $flag = shift;

my $line;
while($line = <IN>){
      print OUT $line;
      $line = <IN>;
      if($flag eq "1"){
          $line =~ tr/AG/GA/;
      }
      if($flag eq "2"){
          $line =~ tr/CT/TC/;
      }
      if($flag eq "3"){
          $line =~ tr/AG/GA/;
          $line =~ tr/CT/TC/;
      }
      print OUT $line;
      $line = <IN>;
      print OUT $line;
      $line = <IN>;
      print OUT $line;
}

close IN;
close OUT;