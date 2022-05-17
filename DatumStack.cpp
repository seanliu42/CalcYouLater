/* 
 * DatumStack.cpp
 * 
 * CS15 HW2
 * by Sean Liu, October 2021
 * 
 * Implementation for the DatumStack interface. 
 * 
 */
 
 #include "DatumStack.h"
 #include "Datum.h"
 #include <vector>
 #include <stdexcept>
 
 using namespace std;
 
 /* Purpose: initializes an empty DatumStack */
 DatumStack::DatumStack() {
     
 }
 
 /*    Purpose: initializes a DatumStack with elements from an array of Datum
  * Parameters: an array of Datum objects and its size
  */
 DatumStack::DatumStack(Datum arrayOfData[], int size) {
     for(int i = 0; i < size; i++) {
         stackOfDatum.push_back(arrayOfData[i]);
     }
 }
 
 /*    Purpose: Checks if the current stack has any Datum objects
  * Parameters: none
  *    Returns: A boolean -- true if the stack is empty, false if it isn't
  */
 bool DatumStack::isEmpty() {
     if (not stackOfDatum.empty()) {
         return false;
     }
     
     return true;
 }
 
 /*    Purpose: Makes the current stack into an empty stack
  * Parameters: none
  *    Returns: none
  */
 void DatumStack::clear() {
     stackOfDatum.clear();
 }

 /*    Purpose: Return the number of Datum elements on the stack
  * Parameters: none
  *    Returns: An integer value of the number of Datum elements on the stack
  */
 int DatumStack::size() {
     return stackOfDatum.size();
 }
 
 /*    Purpose: Returns the top Datum element on the stack
  * Parameters: none
  *    Returns: The top Datum element on the stack
  */
 Datum DatumStack::top() {
     if (stackOfDatum.empty()) {
         throw runtime_error("empty_stack"); 
     }
     
     return stackOfDatum.back();
 }
 
 /*    Purpose: Removes the top element of the stack
  * Parameters: none
  *    Returns: none
  */
 void DatumStack::pop() {
     if (stackOfDatum.empty()) {
         throw runtime_error("empty_stack"); 
     }

     stackOfDatum.pop_back();
 }
 
 /*    Purpose: Takes a Datum element and puts it on the top of the stack
  * Parameters: none
  *    Returns: none
  */
 void DatumStack::push(Datum datum) {
     stackOfDatum.push_back(datum);
 }