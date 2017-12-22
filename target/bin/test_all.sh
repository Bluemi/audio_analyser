#!/bin/bash

tests=$(find ./target/tests -type f)
run_counter=0
success_counter=0
fail_counter=0
for t in $tests
do
	$t
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
