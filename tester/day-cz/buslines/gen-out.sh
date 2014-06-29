#!/bin/bash

for i in test/*.in ; do
	o=${i/in}out

	echo  $i ": "

	(time ./sol-fhlasek-no-recursion-ok < $i > $o) 2>&1 | grep "user"

	# diff $o temp.out

	echo ""
done

# rm temp.out
