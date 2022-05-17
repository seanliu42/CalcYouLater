/* 
 * RPNCalc.cpp
 * 
 * CS15 HW2
 * by Sean Liu, October 2021
 * 
 * Implementation for the RPNCalc interface. RPNCalc is a stack that stores 
 * Datum elements. Its functions add and remove Datum elements, often with 
 * intermediate operations to modify or create new Datum elements. If there is
 * an issue with elements being added to the stack incorrectly, check the 
 * definition of the specific command functions used. The issue is typically
 * a result of incorrect execution of operations or mishandling of the Datum 
 * elements when popping or pushing.
 * 
 */

#include "RPNCalc.h"
#include "DatumStack.h"
#include "Datum.h"
#include "parser.h"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/* Purpose: Initializes the RPNCalc object */
RPNCalc::RPNCalc() {

}

/* Purpose: Recycles the memory used in the RPNCalc object */
RPNCalc::~RPNCalc() {

}

/*    Purpose: Calls the command loop function with cin as the input stream
 * Parameters: none
 *    Returns: none
 */
void RPNCalc::run() {
    commandLoop(cin);
    cerr << "Thank you for using CalcYouLater.\n"; 
}

/*    Purpose: Calls the functions corresponding to input 
 * Parameters: An input stream
 *    Returns: none
 */
void RPNCalc::commandLoop(istream & input) {
    string command;
    int integer;
    // Continues until exit flag is set to true or input stream ends
    while (not exit and input >> command) {
        try { // Run these commands at the risk of throwing an error
            if (command == "quit") {
                exit = true;
            } else if (got_int(command, & integer) == true) {
                calculator.push(Datum(integer)); 
            } else if (command == "print") {
                print();
            } else if (command == "#t") {
                calculator.push(Datum(true));
            } else if (command == "#f") {
                calculator.push(Datum(false));
            } else if (command == "not") {
                notFunction();
            } else if (command == "print") {
                print();
            } else if (command == "clear") {
                clear();
            } else if (command == "drop") {
                drop();
            } else if (command == "dup") {
                dup();
            } else if (command == "swap") {
                swap();
            } else if (command == "+" or command == "-" or command == "*" or 
                       command == "/" or command == "mod") {
                arithmeticOperator(command);
            } else if (command == "<" or command == ">" or command == "<=" or
                       command == ">=" or command == "==") {
                comparisonOperator(command);
            } else if (command == "exec") {
                exec();
            } else if (command == "file") {
                file();
            } else if (command == "if") {
                ifFunction();
            } else if (command == "{") {
                string rstring = parseRString(input);
                calculator.push(Datum(rstring));
            } else {
                cerr << command << ": unimplemented\n";
            }
        }
        catch (runtime_error &error) { // Handle errors and continue running
            cerr << "Error: " << error.what() << "\n";
        }
    }
}

/*    Purpose: Replaces the top element of the stack with the opposite boolean
 * Parameters: none
 *    Returns: none
 */
void RPNCalc::notFunction() {
    Datum curr = calculator.top(); // Prevent element from being lost
    calculator.pop();
    
    bool currStatus = curr.getBool();
    if (currStatus == true) {
        calculator.push(Datum(false));
    }
    if (currStatus == false) {
        calculator.push(Datum(true));
    }
}

/*    Purpose: Prints the value of the element on the top of the stack
 * Parameters: none
 *    Returns: none
 */
void RPNCalc::print() {    
    // Determine output format based on the Datum type of the top element
    if (calculator.top().isInt()) {
        cout << calculator.top().getInt() << "\n";
    } else if (calculator.top().isBool()) {
        if (calculator.top().getBool() == true) {
            cout << "#t\n"; 
        } else {
            cout << "#f\n";
        }
    } else {
        cout << calculator.top().getRString() << "\n";
    }
}

/*    Purpose: Clears the calculator, emptying the stack
 * Parameters: none
 *    Returns: none
 */
void RPNCalc::clear() {
    calculator.clear();
}

/*    Purpose: Removes the top element on the stack
 * Parameters: none
 *    Returns: none
 */
void RPNCalc::drop() {
    calculator.pop();
}

/*    Purpose: Duplicates the top element on the stack
 * Parameters: none
 *    Returns: none
 */
void RPNCalc::dup() {
    Datum duplicate = calculator.top();
    calculator.push(duplicate);
}

/*    Purpose: Swaps the top two elements on the stack
 * Parameters: none
 *    Returns: none
 */
void RPNCalc::swap() {
    Datum notLast = calculator.top(); // Prevent element from being lost
    calculator.pop();
    Datum newLast = calculator.top(); // Prevent element from being lost
    calculator.pop();

    // Push the elements back on in the new order
    calculator.push(notLast);
    calculator.push(newLast);
}

/*    Purpose: pops the top two elements on the stack and pushes the integer 
 *             result of the operation on the top of the stack
 * Parameters: The command as a string from input
 *    Returns: none
 */
void RPNCalc::arithmeticOperator(string command) {
    Datum secondDatum = calculator.top(); // Prevent element from being lost
    calculator.pop();
    Datum firstDatum = calculator.top();  // Prevent element from being lost
    calculator.pop();
    
    int result = 0;
    // Execute the operation corresponding to the command
    if (command == "+") {  
        result = firstDatum.getInt() + secondDatum.getInt();
    } else if (command == "-") {
        result = firstDatum.getInt() - secondDatum.getInt();
    } else if (command == "*") {
        result = firstDatum.getInt() * secondDatum.getInt();
    } else if (command == "/") {
        if (secondDatum.getInt() == 0) { // Diving by zero is undefined
            cerr << "Error: division by 0.\n";
            return;
        }
        result = firstDatum.getInt() / secondDatum.getInt();
    } else {
        if (secondDatum.getInt() == 0) { // Diving by zero is undefined
            cerr << "Error: division by 0.\n";
            return;
        }
        result = firstDatum.getInt() % secondDatum.getInt();
    }
    calculator.push(Datum(result));
}

/*    Purpose: Pops the top two elements on the stack and pushes the boolean 
 *             result of the operation on the top of the stack
 * Parameters: The command as a string from input
 *    Returns: none
 *      Notes: The helper function called pushes the result onto the stack
 */
void RPNCalc::comparisonOperator(string command) {
    Datum secondDatum = calculator.top(); // Prevent element from being lost
    calculator.pop();
    Datum firstDatum = calculator.top(); // Prevent element from being lost
    calculator.pop();
    
    bool status = false; // Initialize boolean for the helper function
    // Execute the operation corresponding to the command and update the bool
    if (command == "<") {
        if (firstDatum.getInt() < secondDatum.getInt()) { 
            status = true;
        } 
    } else if (command == ">") {
        if (firstDatum.getInt() > secondDatum.getInt()) {
            status = true;
        } 
    } else if (command == "<=") {
        if (firstDatum.getInt() <= secondDatum.getInt()) {
            status = true; 
        } 
    } else if (command == ">=") {
        if (firstDatum.getInt() >= secondDatum.getInt()) {
            status = true;
        } 
    } else if (command == "==") {
        if (firstDatum.getInt() == secondDatum.getInt()) {
            status = true;
        } 
    }
    comparisonHelper(status);
}

/*    Purpose: Pushes the corresponding bool Datum on to the stack
 * Parameters: Boolean status of the comparison operator
 *    Returns: none
 */
void RPNCalc::comparisonHelper(bool status) {
    if (status == false) {
        calculator.push(Datum(false));
    } else {
        calculator.push(Datum(true));
    }
}

/*    Purpose: Removes the topmost element on the stack, which should be an 
 *             rstring, and processes its contents as a sequence of commands
 * Parameters: none
 *    Returns: none
 */
void RPNCalc::exec() { 
    Datum curr = calculator.top(); // Prevent element from being lost
    calculator.pop();

    if (not curr.isRString()) {
        cerr << "Error: cannot execute non rstring\n";
        return;
    }

    // Turn the rstring in to commands without the brackets into stringstream
    string rstring = curr.getRString();    
    string adjustedString = rstring.substr(2, rstring.size()-3);
    stringstream sstream(adjustedString);
    commandLoop(sstream); // Enter the stream as commands to the commandLoop
}

/*    Purpose: Removes the topmost element, which should be an rstring, on the
 *             stack and processes the contents of the file from the rstring
 * Parameters: none
 *    Returns: none
 */
void RPNCalc::file() {
    Datum curr = calculator.top(); // Prevent element from being lost
    calculator.pop(); 
    
    if (not curr.isRString()) {
        cerr << "Error: file operand not rstring\n";
        return;
    }

    // Turn the rstring in to commands without the brackets into stringstream
    string rstring = curr.getRString();
    string adjustedString = rstring.substr(2, rstring.size()-4);
    stringstream sstream(adjustedString);

    string filename;
    sstream >> filename; // Set the name of the file to open as the rstring

    ifstream infile;
    infile.open(filename); // Open the file

    if (infile.fail()) {
        cerr << "Unable to read " << filename << "\n";
        return;
    }

    commandLoop(infile); // Feed file contents as commands to the commandLoop

    infile.close();
}

/*    Purpose: Removes the top three elements, two rstrings and a boolean
 *             respectfully, on the stack then executes the first removed 
 *             rstring if the boolean is false, and executes the second removed
 *             rstring if the boolean is true
 * Parameters: none
 *    Returns: none
 */
void RPNCalc::ifFunction() {
    Datum falseCase = calculator.top(); // Prevent element from being lost
    calculator.pop();
    Datum trueCase = calculator.top(); // Prevent element from being lost
    calculator.pop();
    Datum condition = calculator.top(); // Prevent element from being lost
    calculator.pop();
    
    // If the condition case cannot be used print an error message
    if (not condition.isBool()) { 
        cerr << "Error: expected boolean in if test\n";
        return;
    }
    // If the boolean cases cannot be executed print an error message
    if (not falseCase.isRString() or not trueCase.isRString()) {
        cerr << "Error: expected rstring in if branch\n";
        return;
    }
    
    // Execute the rstring corresponding to the condition case
    if (condition.getBool() == true) {
        calculator.push(trueCase);
        exec();
    } else {
        calculator.push(falseCase);
        exec();
    }
}
 
/*    Purpose: Processes numbers inputted as strings into integers so that
 *             they can be pushed onto the stack as proper Datum elements
 * Parameters: none
 *    Returns: none
 */
bool RPNCalc::got_int(string s, int * resultp) {
    // Holds the first non-whitespace character after the integer
    char extra;

    return sscanf(s.c_str(), " %d %c", resultp, & extra) == 1;
}