#!/bin/bash

# clear window
tput reset

echo "Active Tests"
echo ""

# find tests
tests=$(find ./build/debug/tests/bin/active/ -type f)

echo "choose a test:"
echo ""

# print tests
counter=0
for i in $tests
do
	tests_[$counter]=$i
	echo "["$counter"]" $i
	counter=$(($counter+1))
done

echo -n "> "
read test_index

# find waves
waves=$(find ./res/*.wav -type f)

echo ""
echo "choose a wave:"
echo ""

# print waves
counter=0
for i in $waves
do
	waves_[$counter]=$i
	echo "["$counter"]" $i
	counter=$(($counter+1))
done

echo -n "> "
read wave_index

${tests_[$test_index]} ${waves_[$wave_index]}
