#!/bin/bash

if [ -z "$1" ]; then
	echo Must provide test folder name as an argument to get report for it
	exit
fi

#NAME="SampleBundle"
NAME="$1"

cd $NAME
lcov --directory . --base-directory . --gcov-tool ../llvm-gcov.sh --capture -o cov.info
lcov --remove cov.info "/usr*" -o cov.info
lcov --remove cov.info "/dependencies*" -o cov.info
genhtml cov.info -o build
cd ..

open $NAME/build/index.html