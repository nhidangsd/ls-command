myls: myls.c
	gcc -o myls myls.c

clean: 
	rm -f *.o ${PROGRAM}
