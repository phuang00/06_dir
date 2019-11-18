all: dir.o
	gcc -o test_dir dir.o

dir.o: dir.c
	gcc -c dir.c

run:
	./test_dir ~

clean:
	rm *.o
	rm *~

memcheck:
	valgrind --leak-check:yes ./test_dir
