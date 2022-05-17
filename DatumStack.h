/* 
 * DatumStack.h
 * 
 * CS15 HW2
 * by Sean Liu, October 2021
 * 
 * Interface for DatumStack. Defines DatumStack as a class that 
 * stores Datum objects.
 * 
 */

#ifndef DATUMSTACK_H
#define DATUMSTACK_H

#include "Datum.h"
#include <iostream>
#include <vector>

using namespace std;

class DatumStack {
public:
        DatumStack();
        DatumStack(Datum arrayOfData[], int size); 
        
        bool isEmpty();
        void clear();
        int size();
        Datum top();
        void pop();
        void push(Datum datum);
        
private:
        vector<Datum> stackOfDatum;
        
};

#endif
