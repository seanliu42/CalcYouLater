/* 
 * RPNCalc.h
 * 
 * CS15 HW2
 * by Sean Liu, October 2021
 * 
 * Interface for RPNCalc. This class utilizes the DatumStack class to store
 * Datum elements. This class has the most versatility in modifying Datum
 * elements. This class defines the driver function of CalcYouLater, and
 * allows the user to modify Datum elements by calling its functions through
 * the driver.
 *
 */

#ifndef RPNCALC_H
#define RPNCALC_H

#include "DatumStack.h"
#include "parser.h"
#include <iostream>

using namespace std;

class RPNCalc {
public:

    // Constructors
    RPNCalc();
    ~RPNCalc();
        
    // Driver function
    void run();
        
private:    
    // Stack of Datum that serves as the calculator
    DatumStack calculator;
    
    // Flag which updates whenever quit is called in the calculator
    bool exit = false;
    
    // Helper function that processes inputted commands
    void commandLoop(istream &input);
    
    // Calculator commands
    void notFunction();
    void print();
    void clear();
    void drop();
    void dup();
    void swap();
    void quit();
    void arithmeticOperator(string input);
    void comparisonOperator(string input);
    void exec();
    void file();
    void ifFunction();
    
    // Helper functions
    bool got_int(string s, int *resultp);
    void comparisonHelper(bool status); 
    
};

#endif
