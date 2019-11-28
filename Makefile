# Module subdirectories
POLYNOMIAL := Polynomial

# Use vpath to find source and header files in module directories
vpath %.c $(POLYNOMIAL)
vpath %.h $(POLYNOMIAL)

# Make all
.PHONY: all
all: polyFuncTest polyOpTest polynomialMain
	./polynomialMain

polynomialMain: polynomial.o main.c
	gcc -Wall -ggdb -o $@ $^

polynomial.o: polynomial.c polynomial.h
	gcc -Wall -ggdb -c $<

polyFuncTest: polyFuncTest.c polynomial.o
	gcc -Wall -ggdb -o $@ $^

polyOpTest: polyOpTest.c polynomial.o
	gcc -Wall -ggdb -o $@ $^

.PHONY: clean
clean:
	rm -f -r *.dSYM
	rm -f *.o polyFuncTest* polyOpTest* polynomialMain* *~
