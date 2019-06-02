# ===============================@kangkang===============================
#!/bin/perl -w

use strict;

use POSIX;

die("Usage:\n\t--perl main.pl [option] -[command] [parameter_value]\noption: crosstalk [intensity_file] [cycle] [out_file]\n\timage [infile] [outfile]\n\tintensity [infile] [outfile]\n") if(@ARGV < 1);
my $option = shift;
if($option eq "crosstalk"){
die("Usage:\n\t--perl main.pl crosstalk [intensity_file] [cycle] [out_file]\n") unless(@ARGV == 3);
my $intensityFile = shift;
my $cycle = shift;
my $out_file = shift;
my $prefix = 4;
my $bsize = 4;

my $R = "png(\"${out_file}_cycle$cycle.png\")\ndata=read.table(\"$intensityFile\")\npar(mfrow=c(3,2))";

my $counter = 1;
for(my $i =($cycle - 1) * $bsize + 1 + $prefix; $i < $cycle * $bsize + 1 + $prefix; $i ++){
    for(my $j = $i + 1; $j < $cycle * $bsize + 1 + $prefix; $j ++){
        my $t1 = POSIX::ceil($counter / 3);
        my $t2 = $counter;
        if($counter > 3){
             $t2 -= 3;
        }
$R .= "\nplot(data[,$i],data[,$j],xlab=\"intensity\",ylab=\"intensity\",main=\"crosstalk\",pch=16,cex=1)";
        $counter ++;
    }
}

open OU, ">${out_file}_cycle$cycle.R" or die("cat open file ${out_file}_cycle$cycle.R:$!\n");
print OU "$R\n";
close OU;
system("Rscript ${out_file}_cycle$cycle.R");
}

if($option eq "image"){
die("Usage:\n\t--perl main.pl image [infile] [outfile]\n") unless(@ARGV == 2);
my $infile = shift;
my $outfile = shift;
my $R = "a=read.table(\"$infile\")\n";
$R .= "png(\"${outfile}_tatol.png\")\n";
$R .= "rg=max(a[,2],a[,3],a[,4],a[,5])\n";
$R .= "plot(a[,1],a[,2],ylim=c(0,rg),xlab=\"cycle\",ylab=\"sum\",main=\"Image Sum\",type=\"l\",col=\"blue\",lwd=2)\npar(new=TRUE)\n";
$R .= "plot(a[,1],a[,3],ylim=c(0,rg),xlab=\"cycle\",ylab=\"sum\",main=\"Image Sum\",type=\"l\",col=\"red\",lwd=2)\npar(new=TRUE)\n";
$R .= "plot(a[,1],a[,4],ylim=c(0,rg),xlab=\"cycle\",ylab=\"sum\",main=\"Image Sum\",type=\"l\",col=\"green\",lwd=2)\npar(new=TRUE)\n";
$R .= "plot(a[,1],a[,5],ylim=c(0,rg),xlab=\"cycle\",ylab=\"sum\",main=\"Image Sum\",type=\"l\",col=\"black\",lwd=2)\npar(new=TRUE)\n";
$R .= "legend(\"topright\",lty=1,col=c(\"blue\",\"red\",\"green\",\"black\"),legend=c(\"A\",\"T\",\"C\",\"G\"))\n";

$R .= "png(\"${outfile}_ave.png\")\n";
$R .= "rg=max(a[,6],a[,7],a[,8],a[,9])\n";
$R .= "plot(a[,1],a[,6],ylim=c(0,rg),xlab=\"cycle\",ylab=\"ave\",main=\"Image Ave\",type=\"l\",col=\"blue\",lwd=2)\npar(new=TRUE)\n";
$R .= "plot(a[,1],a[,7],ylim=c(0,rg),xlab=\"cycle\",ylab=\"ave\",main=\"Image Ave\",type=\"l\",col=\"red\",lwd=2)\npar(new=TRUE)\n";
$R .= "plot(a[,1],a[,8],ylim=c(0,rg),xlab=\"cycle\",ylab=\"ave\",main=\"Image Ave\",type=\"l\",col=\"green\",lwd=2)\npar(new=TRUE)\n";
$R .= "plot(a[,1],a[,9],ylim=c(0,rg),xlab=\"cycle\",ylab=\"ave\",main=\"Image Ave\",type=\"l\",col=\"black\",lwd=2)\npar(new=TRUE)\n";
$R .= "legend(\"topright\",lty=1,col=c(\"blue\",\"red\",\"green\",\"black\"),legend=c(\"A\",\"T\",\"C\",\"G\"))\n";

$R .= "png(\"${outfile}_variance.png\")\n";
$R .= "rg=max(a[,10],a[,11],a[,12],a[,13])\n";
$R .= "plot(a[,1],a[,10],ylim=c(0,rg),xlab=\"cycle\",ylab=\"variance\",main=\"Image Variance\",type=\"l\",col=\"blue\",lwd=2)\npar(new=TRUE)\n";
$R .= "plot(a[,1],a[,11],ylim=c(0,rg),xlab=\"cycle\",ylab=\"variance\",main=\"Image Variance\",type=\"l\",col=\"red\",lwd=2)\npar(new=TRUE)\n";
$R .= "plot(a[,1],a[,12],ylim=c(0,rg),xlab=\"cycle\",ylab=\"variance\",main=\"Image Variance\",type=\"l\",col=\"green\",lwd=2)\npar(new=TRUE)\n";
$R .= "plot(a[,1],a[,13],ylim=c(0,rg),xlab=\"cycle\",ylab=\"variance\",main=\"Image Variance\",type=\"l\",col=\"black\",lwd=2)\npar(new=TRUE)\n";
$R .= "legend(\"topright\",lty=1,col=c(\"blue\",\"red\",\"green\",\"black\"),legend=c(\"A\",\"T\",\"C\",\"G\"))\n";

$R .= "png(\"${outfile}_gradient.png\")\n";
$R .= "rg=max(a[,14],a[,15],a[,16],a[,17])\n";
$R .= "plot(a[,1],a[,14],ylim=c(0,rg),xlab=\"cycle\",ylab=\"gradient\",main=\"Image Gradient\",type=\"l\",col=\"blue\",lwd=2)\npar(new=TRUE)\n";
$R .= "plot(a[,1],a[,15],ylim=c(0,rg),xlab=\"cycle\",ylab=\"gradient\",main=\"Image Gradient\",type=\"l\",col=\"red\",lwd=2)\npar(new=TRUE)\n";
$R .= "plot(a[,1],a[,16],ylim=c(0,rg),xlab=\"cycle\",ylab=\"gradient\",main=\"Image Gradient\",type=\"l\",col=\"green\",lwd=2)\npar(new=TRUE)\n";
$R .= "plot(a[,1],a[,17],ylim=c(0,rg),xlab=\"cycle\",ylab=\"gradient\",main=\"Image Gradient\",type=\"l\",col=\"black\",lwd=2)\npar(new=TRUE)\n";
$R .= "legend(\"topright\",lty=1,col=c(\"blue\",\"red\",\"green\",\"black\"),legend=c(\"A\",\"T\",\"C\",\"G\"))\n";

open OU, ">${outfile}_image.R" or die("cat open file ${outfile}_image.R:$!\n");
print OU "$R\n";
close OU;
system("Rscript ${outfile}_image.R");
}

if($option eq "intensity"){
die("Usage:\n\t--perl main.pl image [infile] [outfile]\n") unless(@ARGV == 2);
my $infile = shift;
my $outfile = shift;
my $R = "a=read.table(\"$infile\")\n";
$R .= "png(\"${outfile}_max.png\")\n";
$R .= "rg=max(a[,2],a[,3],a[,4],a[,5])\n";
$R .= "plot(a[,1],a[,2],ylim=c(0,rg),xlab=\"cycle\",ylab=\"max\",main=\"Max ATCG\",type=\"l\",col=\"blue\",lwd=2)\npar(new=TRUE)\n";
$R .= "plot(a[,1],a[,3],ylim=c(0,rg),xlab=\"cycle\",ylab=\"max\",main=\"Max ATCG\",type=\"l\",col=\"red\",lwd=2)\npar(new=TRUE)\n";
$R .= "plot(a[,1],a[,4],ylim=c(0,rg),xlab=\"cycle\",ylab=\"max\",main=\"Max ATCG\",type=\"l\",col=\"green\",lwd=2)\npar(new=TRUE)\n";
$R .= "plot(a[,1],a[,5],ylim=c(0,rg),xlab=\"cycle\",ylab=\"max\",main=\"Max ATCG\",type=\"l\",col=\"black\",lwd=2)\npar(new=TRUE)\n";
$R .= "legend(\"topright\",lty=1,col=c(\"blue\",\"red\",\"green\",\"black\"),legend=c(\"A\",\"T\",\"C\",\"G\"))\n";

$R .= "png(\"${outfile}_colquantile.png\")\n";
$R .= "rg=max(a[,6],a[,7],a[,8],a[,9])\n";
$R .= "plot(a[,1],a[,6],ylim=c(0,rg),xlab=\"cycle\",ylab=\"colquantile\",main=\"Colum Quantile 95\",type=\"l\",col=\"blue\",lwd=2)\npar(new=TRUE)\n";
$R .= "plot(a[,1],a[,7],ylim=c(0,rg),xlab=\"cycle\",ylab=\"colquantile\",main=\"Colum Quantile 95\",type=\"l\",col=\"red\",lwd=2)\npar(new=TRUE)\n";
$R .= "plot(a[,1],a[,8],ylim=c(0,rg),xlab=\"cycle\",ylab=\"colquantile\",main=\"Colum Quantile 95\",type=\"l\",col=\"green\",lwd=2)\npar(new=TRUE)\n";
$R .= "plot(a[,1],a[,9],ylim=c(0,rg),xlab=\"cycle\",ylab=\"colquantile\",main=\"Colum Quantile 95\",type=\"l\",col=\"black\",lwd=2)\npar(new=TRUE)\n";
$R .= "legend(\"topright\",lty=1,col=c(\"blue\",\"red\",\"green\",\"black\"),legend=c(\"A\",\"T\",\"C\",\"G\"))\n";

$R .= "png(\"${outfile}_ave_atcg.png\")\n";
$R .= "rg=max(a[,10],a[,11],a[,12],a[,13])\n";
$R .= "plot(a[,1],a[,10],ylim=c(0,rg),xlab=\"cycle\",ylab=\"average atcg\",main=\"Average ATCG\",type=\"l\",col=\"blue\",lwd=2)\npar(new=TRUE)\n";
$R .= "plot(a[,1],a[,11],ylim=c(0,rg),xlab=\"cycle\",ylab=\"average atcg\",main=\"Average ATCG\",type=\"l\",col=\"red\",lwd=2)\npar(new=TRUE)\n";
$R .= "plot(a[,1],a[,12],ylim=c(0,rg),xlab=\"cycle\",ylab=\"average atcg\",main=\"Average ATCG\",type=\"l\",col=\"green\",lwd=2)\npar(new=TRUE)\n";
$R .= "plot(a[,1],a[,13],ylim=c(0,rg),xlab=\"cycle\",ylab=\"average atcg\",main=\"Average ATCG\",type=\"l\",col=\"black\",lwd=2)\npar(new=TRUE)\n";
$R .= "legend(\"topright\",lty=1,col=c(\"blue\",\"red\",\"green\",\"black\"),legend=c(\"A\",\"T\",\"C\",\"G\"))\n";

$R .= "png(\"${outfile}_ave_base.png\")\n";
$R .= "rg=max(a[,14])\n";
$R .= "plot(a[,1],a[,14],ylim=c(0,rg),xlab=\"cycle\",ylab=\"average\",main=\"Average Base\",type=\"l\",col=\"blue\",lwd=2)\n";

open OU, ">${outfile}_intensity.R" or die("cat open file ${outfile}_intensity.R:$!\n");
print OU "$R\n";
close OU;
system("Rscript ${outfile}_intensity.R");
}

if($option eq "phasingPrephasing"){

}