/* 
 * parser.cpp
 * 
 * CS15 HW2
 * by Sean Liu, October 2021
 * 
 * Implementation of the parseRString function. 
 * 
 */

#include <iostream>
#include <string>
#include "parser.h"

using namespace std;

/*    Purpose: Reads an input stream once an open bracket is encountered
 *             and turns the input into a string with open and closed brackets 
 *             around it
 * Parameters: An input stream
 *    Returns: A string
 */
string parseRString(istream &input) {
    int openBrackets = 1;
    int closedBrackets = 0;
    
    // Initialize the rstring to have the bracket preceding the function call
    string rstring = "{"; 
    
    string processedInput;
    while (openBrackets != closedBrackets) {
        input >> processedInput;
        
        // Puts spaces between the brackets and the contents of the rstring
        rstring.push_back(' '); 
        
        int length = processedInput.length();
        
        // Adds each character from the stringstream into the return string 
        for(int i = 0; i < length; i++) {
            rstring.push_back(processedInput.at(i));
        }
        
        if (processedInput == "{") {
            openBrackets++;
        }
        if (processedInput == "}") {
            closedBrackets++;
        }
    }
    return rstring;
}