#!/usr/bin/perl
system("rm testresults/allresults.log");
system("tail -n 1 testresults/test_0001_example.log >> testresults/allresults.log");
