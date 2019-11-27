# Module subdirectories
POLYNOMIAL := Polynomial

# Use vpath to find source and header files in module directories
vpath %.c $(POLYNOMIAL)
vpath %.h $(POLYNOMIAL)

# Make all
.PHONY: all
all: polynomialTest PolynomialMain

PolynomialMain: polynomial.o main.c
	gcc -Wall -ggdb -o $@ $^

polynomial.o: polynomial.c polynomial.h
	gcc -Wall -ggdb -c $<

polynomialTest: polynomialTest.c polynomial.o
	gcc -Wall -ggdb -o $@ $^

.PHONY: clean
clean:
	rm -f -r *.dSYM
	rm -f *.o polynomialTest* *~
