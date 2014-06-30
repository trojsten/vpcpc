#!/bin/bash

for i in test/*.in ; do
	o=${i/in}out

	echo  $i ": "

	echo -n "sysel: "
	(time ./sol-sysel-ok < $i > $o) 2>&1 | grep "user"

	echo -n "misof: "
	(time ./sol-misof-sqrt < $i > temp.out) 2>&1 | grep "user"

	diff $o temp.out

	echo ""
done

rm temp.out