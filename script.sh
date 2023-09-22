#!/bin/bash

make bonus && ./pipex_bonus infile "cat" "xargs -I {} ping -c 1 {}" "grep PING" outfile1
< infile cat | xargs -I {} ping -c 1 {} | grep PING > output1
diff outfile1 output1
if [ $? -eq 0 ]; then 
	echo "success"
else 
	echo "failure"
fi

./pipex_bonus infile "cat" "xargs -I {} ping -c 1 {}" "grep PING" "wc -w" outfile
< infile cat | xargs -I {} ping -c 1 {} | grep PING | wc -w > output
diff outfile output
if [ $? -eq 0 ]; then 
	echo "success"
else 
	echo "failure"
fi

./pipex_bonus infile "grep p" "grep b" "grep c" "grep d" "grep e" outfile2
< infile | grep p | grep b | grep c | grep d | grep e > output2
diff outfile2 output2
if [ $? -eq 0 ]; then 
	echo "success"
else 
	echo "failure"
fi

