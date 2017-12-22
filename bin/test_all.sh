#!/bin/bash

verbose=0

# check flags
while getopts ":v" opt; do
  case $opt in
    v)
      verbose=1
      ;;
    \?)
      echo "Invalid option: -$OPTARG" >&2
      ;;
  esac
done

# find tests
tests=$(find ./target/tests -type f)

# initiate counters
run_counter=0
success_counter=0
fail_counter=0

# loop through tests
for t in $tests
do
	if [ $verbose -eq 1 ]; then
		$t
	else
		$t 2>/dev/null 1>&2
	fi
	if [ $? -ne 0 ]; then
		echo "test $t failed"
		fail_counter=$(($fail_counter+1))
	else
		success_counter=$(($success_counter+1))
	fi
	run_counter=$(($run_counter+1))
done

# print results

echo "Tests run: $run_counter"
echo "Failures: $fail_counter"
