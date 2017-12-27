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
	success=0
	# verbose
	if [ $verbose -eq 1 ]; then
		echo "-----------------------------------------------------------------------"
		echo $t:
		if $t
		then
			success=1
		fi 2>/dev/null
		echo ""
	else
	# unverbose
		if $($t &>/dev/null) &>/dev/null
		then
			success=1
		fi
	fi
	if [ $success -eq 0 ]; then
		echo "test $t failed"
		fail_counter=$(($fail_counter+1))
	else
		success_counter=$(($success_counter+1))
	fi
	run_counter=$(($run_counter+1))
done

# print results

echo ""
echo "Tests run: $run_counter"
echo "Failures: $fail_counter"
