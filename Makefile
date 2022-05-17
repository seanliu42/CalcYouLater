###
### Makefile for CalcYouLater Project
### CalcYouLater is an RPN calculator
###
### Author:  Sean Liu

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

# This rule builds CalcYouLater
CalcYouLater: main.o RPNCalc.o DatumStack.o Datum.o parser.o 
	$(CXX) $(LDFLAGS) -o CalcYouLater main.o RPNCalc.o DatumStack.o \
	Datum.o parser.o 
	
# This rule builds main.o
main.o: main.cpp RPNCalc.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# This rule builds RPNCalc.o
RPNCalc.o: RPNCalc.cpp RPNCalc.h DatumStack.h Datum.h parser.h
	$(CXX) $(CXXFLAGS) -c RPNCalc.cpp
	
# This rule builds DatumStack.o
DatumStack.o: DatumStack.cpp DatumStack.h Datum.h 
	$(CXX) $(CXXFLAGS) -c DatumStack.cpp
	
# This rule builds parser.o
parser.o: parser.cpp parser.h  
	$(CXX) $(CXXFLAGS) -c parser.cpp
	
# The below rule will be used by unit_test.
# Please add any other .o files that are needed by DatumStack,
# and any other .o files you wish to test. 
unit_test: unit_test_driver.o Datum.o DatumStack.o
		$(CXX) $(CXXFLAGS) $^ 

# This rule provides your submission 
# NOTE: Don't forget to add any additional files you want to submit to this
#       rule! If you do not add them, they will not be submitted.
provide:
	provide comp15 proj1_calcyoulater \
	DatumStack.h DatumStack.cpp \
	RPNCalc.h  RPNCalc.cpp \
	main.cpp README \
	Makefile parser.cpp \
	parser.h unit_tests.h \
	parsertest.cpp test1.cylc \
	test2.cylc test3.cylc \
	myOutput1.txt myOutput2.txt \
	myOutput3.txt theOutput1.txt \
	theOutput2.txt theOutput3.txt
	
# remove executables, object code, and temporary files from the current
# folder -- the executable created by unit_test is called a.out
clean: 
	rm RPNCalc.o DatumStack.o main.o parser.o *~ a.out

##
## Here is a rule for compiling .cyl files for use in your testing
##
%.cylc:  %.cyl
	./cylc $^
