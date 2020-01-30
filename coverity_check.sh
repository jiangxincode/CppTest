#!/bin/bash
mkdir build_coverity && cd build_coverity
cmake ..
make clean all
cat /home/travis/build/jiangxincode/CppTest/cov-int/scm_log.txt
cd ..