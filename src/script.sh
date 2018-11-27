#!/bin/bash
./parser ./../dcf_codes/prime.dcf; lli outfile > answer
./parser ./../dcf_codes/even.dcf; lli outfile >> answer
./parser ./../dcf_codes/maxmin.dcf; lli outfile >> answer
./parser ./../dcf_codes/arraysum.dcf; lli outfile >> answer
./parser ./../dcf_codes/linear.dcf; lli outfile >> answer
./parser ./../extra_sample_codes/fib.dcf; lli outfile >> answer
./parser ./../extra_sample_codes/fact.dcf; lli outfile >> answer
./parser ./../extra_sample_codes/gcd.dcf; lli outfile >> answer
./parser ./../extra_sample_codes/merge.dcf; lli outfile >> answer
./parser ./../extra_sample_codes/quick.dcf; lli outfile >> answer
./parser ./../extra_sample_codes/hanoi.dcf; lli outfile >> answer
./parser ./../extra_sample_codes/vecadd.dcf; lli outfile >> answer
./parser ./../extra_sample_codes/break.dcf; lli outfile >> answer
./parser ./../extra_sample_codes/bubble.dcf; lli outfile >> answer
