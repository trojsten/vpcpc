#!/bin/bash

for i in test/*.in ; do
	o=${i/in}out

	echo  $i ": "

	echo -n "sysel: "
	(time ./sol-sysel-ok < $i > $o) 2>&1 | grep "user"

	echo ""
done

for i in test/*.in ; do
	o=${i/in}out

	echo  $i ": "

	echo -n "sysel-kvad: "
	(time ./sol-sysel-kvad < $i > temp.out) 2>&1 | grep "user"

	diff $o temp.out

	echo ""
done

rm temp.out