

all: tests


tests: tests.o c_datetime.o
	gcc -o $@ tests.o c_datetime.o


tests.o: tests.c
	gcc -c $< -o $@


c_datetime.o: /home/burnin/Embedded/c_datetime/c_datetime.c
	gcc -c $< -o $@


.PHONY: clean
clean:
	rm *.o tests

