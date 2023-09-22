#!/bin/bash

make bonus && ./pipex_bonus infile "cat" "xargs -I {} ping -c 1 {}" "grep PING" outfile
< infile cat | xargs -I {} ping -c 1 {} | grep PING > output
diff outfile output
if [ $? -eq 0 ]; then 
	echo "success"
else 
	echo "failure"
fi

# ./pipex_bonus infile "cat" "xargs -I {} ping -c 1 {}" "grep PING" "wc -w" outfile
# < infile cat | xargs -I {} ping -c 1 {} | grep PING | wc -w > output
# diff outfile output
# if [ $? -eq 0 ]; then 
# 	echo "success"
# else 
# 	echo "failure"
# fi
