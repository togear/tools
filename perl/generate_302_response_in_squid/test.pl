#!/usr/bin/perl
$|=1;
while (<>)
{

	if(/(\w+):\/\/([^\/]+)\/(\S*)/){

        my $prot  = $1;
        my $hostname = $2;
        my $uri = $3;


        if($prot eq "http" || $prot eq "HTTP"){
            my $redi_ret =  "302:http:/$hostname/$uri\n";
            print $redi_ret;

        }
        else{
            print $_;
        }
    }
    else{
        print $_;
    }
}

