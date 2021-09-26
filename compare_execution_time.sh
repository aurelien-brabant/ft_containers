#! /bin/bash

./ft > /dev/null
./std > /dev/null

cc misc/compare_time.c -o compare_time

stdTimes=()
ftTimes=()
testNames=()

while read -r p; do
	testNames+=("$p")
done < ./.castorno/tests.txt

while read p; do
	ftTimes+=($p)
done < ./.castorno/ft.time.txt

while read p; do
	stdTimes+=($p)
done < ./.castorno/std.time.txt

#printf "\033[30m------------------------------------------------------------------------------------------------------------------------\033[0m\n"
for i in ${!testNames[@]}; do
	printf "\033[1m%-50s\033[0m" "${testNames[$i]}"
	./compare_time "${stdTimes[$i]}" "${ftTimes[$i]}"
	printf " (std: %-8s ms | ft: %-8s ms)\n" "${stdTimes[$i]}" "${ftTimes[$i]}"
	#printf "\033[30m------------------------------------------------------------------------------------------------------------------------\033[0m\n"
done

rm -rf compare_time
