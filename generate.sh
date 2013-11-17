#!/bin/bash

# Generates packaging for packagemonkey

rm -f Makefile rpmpackage/libdeep.spec

packagemonkey -n "libdeep" --version "1.00" --cmd --dir "." -l "bsd" -e "Bob Mottram (4096 bits) <bob@robotics.uk.to>" --brief "Library for deep learning" --desc "Makes using deep learning easy to include within any C/C++ application." --homepage "https://github.com/fuzzgun/libdeep" --repository "https://github.com/fuzzgun/libdeep.git" --section "libs" --categories "Development/ArtificialIntelligence" --cstandard "c99" --compile "-lpng -lm -fopenmp" --dependsdeb "gnuplot, libpng-dev" --dependsarch "gnuplot, libpng" --dependsrpm "gnuplot, libpng-devel"
