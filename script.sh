#!/bin/bash

make bonus && ./pipex_bonus infile "head -n 1" "xargs -I {} ping -c 1 {}" "grep PING" outfile0
< infile head -n 1 | xargs -I {} ping -c 1 {} | grep PING > output0
diff outfile0 output0
if [ $? -eq 0 ]; then 
	echo "success"
else 
	echo "failure"
fi

./pipex_bonus infile "head -n 1" "xargs -I {} ping -c 1 {}" "grep PING" "wc -w" outfile1
< infile head -n 1 | xargs -I {} ping -c 1 {} | grep PING | wc -w > output1
diff outfile1 output1
if [ $? -eq 0 ]; then 
	echo "success"
else 
	echo "failure"
fi

./pipex_bonus infile "head -n 2" "sort" "uniq" "grep google"  outfile2
< infile head -n 2 | sort | uniq | grep google > output2
diff outfile2 output2
if [ $? -eq 0 ]; then 
	echo "success"
else 
	echo "failure"
fi

./pipex_bonus infile "grep pattern1" "sort -r" "head -n 10"  outfile2
< infile grep "pattern1" | sort -r | head -n 10 > output3
diff outfile3 output3
if [ $? -eq 0 ]; then 
	echo "success"
else 
	echo "failure"
fi
