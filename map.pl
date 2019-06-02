#!/bin/perl -w

use File::Path;
use strict;

my $QSystem = 64;
my $project = "st_bi";
my $storage = 4;

die("Usage:\n\tperl map.pl [fq_infile] [ref_infile] [map_outpath] [qsub:Y|N]\nExample:\n\t--perl /home/test/L001/a.fq /home/test/L001/a_reference.fa /home/test Y\nFunction:Get the map rate and mismatachrate of lane!\nWarning:Default Q_system $QSystem | Default project $project | Default storage $storage(G)\n") unless @ARGV == 4;

my $fq = shift;
my $ref = shift;
my $map = shift;
my $qs = shift;
my $dir;

if(rindex($fq, "/") != -1){
	$dir = substr($fq, rindex($fq, "/") + 1, length($fq));
}else{
	$dir = $fq;
}
#$dir =~ s/\.\(w+)//g;
$dir =~ s/.gz//g;
$dir = $map . "/" . $dir . "_res";

if(-e $dir){
	print "Result_Path:$dir\n";
}else{
	eval{mkpath($dir,0,0755)};
	if($@){
		warn("Make path [$dir] failed:\n$@\n");
	}
	print "Result_Path:$dir\n";
}

my $cm;
unless($fq =~ /.gz$/){
	$cm = "gzip -c $fq > $dir/fastq_raw.fq.gz";
}else{
	$cm = "cp $fq $dir/fastq_raw.fq.gz";
}
$fq = "$dir/fastq_raw.fq.gz";

my $filter = "/home/xuweibin/software/mine/software/analysis/fastq_filter.out";
my $bwa = "/home/xuweibin/software/mine/software/bwa";
my $sam_sta = "/home/xuweibin/software/mine/software/Sam_sta.V1.04.pl";
my $software = "/home/xuweibin/software/mine/software";

my $s = "#!/bin/bash\necho begin time `date +%F'  '%H:%M`\n\n";

$s .= "$cm\necho finish gz\n";
#print $s;
$s .= "time -p $filter -F $fq -N 0.1 -Q_system $QSystem -Q_filter 20 -O ";
my $cfq = $fq;
$cfq =~ s/fastq_raw/fastq_clean/g;
$s .= $cfq . "\necho finish filter\n";

my $sai = $cfq;
$sai =~ s/.gz/.sai/g;
$s .= "time -p $bwa aln -n 2 -t 4 -k 2 -i 15 -l 31 -q 20  -L $ref $cfq > $sai\necho finish sai\n";

my $sam = $cfq;
$sam =~ s/.gz/.sam/g;
$s .= "time -p $bwa samse $ref $sai $cfq > $sam\necho finish sam\n";

$s .= "time -p $sam_sta -sam $sam  -map  SE -dupd Y -sf $software -out $dir\necho finish map\n";
my $rmap = $cfq;
$rmap =~ s/.gz/.map/g;
$s .= "sed -n \"4p\" $rmap\n";
$s .= "sed -n \"6p\" $rmap\n";

$s .= "\necho end time `date +%F'  '%H:%M`\n";

open OU, ">$dir/map.sh" or die("can't write file $dir/map.sh:$!\n");
print OU $s;

if($qs eq "Y"){
	my $qsub = "qsub  -e $dir/map.sh.e -o $dir/map.sh.o -cwd -l vf=" . $storage . "G -P $project $dir/map.sh";
	system($qsub);
	print "qsub successfully!\n";
}else{
	print "write $dir/map.sh successfully!\n";
}


