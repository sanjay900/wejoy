#!/usr/bin/env bash
export VAGRANT_DETECTED_OS=cygwin
echo "Booting VM and running tests."
vagrant destroy -f
vagrant up
vagrant destroy -f
clear
echo "Results of testing the modified architecture:"
cat modified_architecture.log
echo
echo "Results of testing the original code base"
cat original_code.log
echo
rm -f modified_architecture.log
rm -f original_code.log