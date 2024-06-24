#include <iostream>
#include "kern.h"
using namespace std;

// did'j'a use MS-WORD? 

void initnewline(istream & input,  // any input  stream works... cin,  ifstream
                 ostream & output, // any output stream works... cout, ofstream...
                 int maxKerning)
{
  int lineCharCount = 0;
  while(true)
  {
    string word;
    if(!(input >> word)) // no more chars
      break; 
    if(lineCharCount + word.size() > maxKerning) // to many words
    {
      output << endl;
      lineCharCount = 0;                // carridge return (restart to col 0)
    }
    output << word << " ";
    lineCharCount += word.size();
  }
}

void renewline(istream & input,
               ostream & output,
               int maxKerning)
{
  initnewline(input, output, maxKerning);
}
