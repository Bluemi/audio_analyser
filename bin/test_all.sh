#!/bin/bash

verbose=0

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

tests=$(find ./target/tests -type f)
run_counter=0
success_counter=0
fail_counter=0
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

echo "runs : $run_counter"
echo "fails: $fail_counter"
