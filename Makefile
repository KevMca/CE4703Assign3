# Module subdirectories
POLYNOMIAL := Polynomial

# Use vpath to find source and header files in module directories
vpath %.c $(POLYNOMIAL)
vpath %.h $(POLYNOMIAL)

# Make all
.PHONY: all
all: polyFuncTest polyOpTest polynomialMain
	mv *.o ./object/
	./polynomialMain

# Main polynomial interface
polynomialMain: polyOp.o polyFunc.o main.c
	gcc -Wall -ggdb -o $@ $^

# Polynomial operations source compilation
polyOp.o: polyOp.c polynomial.h
	gcc -Wall -ggdb -c $<

# Polynomial functions source compilation
polyFunc.o: polyFunc.c polynomial.h
	gcc -Wall -ggdb -c $<

# Polynomial functions test application
polyFuncTest: polyFuncTest.c polyOp.o polyFunc.o
	gcc -Wall -ggdb -o $@ $^

# Polynomial operations test application
polyOpTest: polyOpTest.c polyOp.o polyFunc.o
	gcc -Wall -ggdb -o $@ $^

# Rule for cleaning everything
.PHONY: clean
clean: cleanObject 
	rm -f -r *.dSYM
	rm -f *.o polyFuncTest* polyOpTest* polynomialMain* *~

# Rule for cleaning up the 3D shapes directory
cleanObject:
	rm -f object/*.o

