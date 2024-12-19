#pragma once
#include <iostream>
using namespace std;

void initnewline(istream & input,  // any input  stream works... cin,  ifstream
                 ostream & output, // any output stream works... cout, ofstream...
                 int maxKerning);

void renewline(istream & input,
               ostream & output,
               int maxKerning);

void autoNewline(string fileIn, string fileOut, int maxKerning);