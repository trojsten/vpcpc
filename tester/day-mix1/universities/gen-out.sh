#!/bin/bash

for i in test/*.in ; do
	o=${i/in}out

	echo  $i ": "

	echo "mimino: "
	(time ./sol-mimino-ok < $i > $o) 2>&1 | grep "user"
	echo "fhlasek: "
	(time ./sol-fhlasek-better-ok < $i > temp.out) 2>&1 | grep "user"

	diff $o temp.out

	echo ""
done

rm temp.out
