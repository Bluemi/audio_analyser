#!/bin/bash

verbose=0

echo ""

# for pretty output
RED="\033[0;31m"
GREEN="\033[0;32m"
NO_COLOR="\033[0m"

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
tests=$(find ./build/debug/tests/bin/passive/ -type f)

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

		START=$(date +%s.%N)

		if $t
		then
			success=1
		fi 2>/dev/null

		END=$(date +%s.%N)
		DIFF=$(echo "$END - $START" | bc)
		echo ""
		echo "$DIFF sec"
		echo ""
	else
	# unverbose
		if $($t &>/dev/null) &>/dev/null
		then
			success=1
		fi
	fi
	if [ $success -eq 0 ]; then
		echo -e "${RED}Failure:${NO_COLOR} test $t failed\n"
		fail_counter=$(($fail_counter+1))
	else
		success_counter=$(($success_counter+1))
	fi
	run_counter=$(($run_counter+1))
done

# print results

echo "Tests run: $run_counter"
echo "Failures:  $fail_counter"

echo

if [ $fail_counter -eq 0 ]; then
	echo -e "${GREEN}SUCCESS${NO_COLOR}"
else
	echo -e "${RED}FAILURE${NO_COLOR}"
fi

echo
