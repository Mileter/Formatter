#include <iostream>
#include "kern.h"
using namespace std;

// did'j'a use MS-WORD? 

// TODO: initnewline: Add support for paragraph breaks. (Don't ignore \n\n)

// this function shall be private
bool isParagraphBreak(istream & input)
{
	// check for paragraph breaks (\n\n\n)
	// nessecery data
	char first = input.get();
	char second = input.get();
	
	// safety check
	if(input.fail()) return false;
	
	// make sure that the data is not corrupted
	input.putback(second);
	input.putback(first);
	
	// the check
	return first == '\n' && second == '\n' ? true : false;
}

void initnewline(istream & input,  // any input  stream works... cin,  ifstream
                 ostream & output, // any output stream works... cout, ofstream...
                 int maxKerning)
{
  int lineCharCount = 0;
  while(true)
  {
	if(isParagraphBreak(input))
	{
		output << "\n\n";
		lineCharCount = 0;
	}
    string word;
    if(!(input >> word)) // no more chars
      break; 
    if(lineCharCount + word.size() - 1 > maxKerning) // to many words
    {                            // ^ -1 to not account for the last space
      output << endl;
      lineCharCount = 0;                             // carridge return (restart to col 0)
    }
    output << word << " ";
    lineCharCount += word.size() + 1;                // account for words and spaces
  }
}

void renewline(istream & input,
               ostream & output,
               int maxKerning)
{
  initnewline(input, output, maxKerning);
}

void autoNewline(string fileIn, string fileOut, int maxKerning)
{
  string temp = fileOut+".bak"; 
  ifstream fin(fileIn);
  ofstream fout(temp);
  renewline(fin, fout, maxKerning);
  fin.close();
  fout.close();
  if (rename(temp.c_str(), fileOut.c_str()))
  {
	char field;
	while(field != 'A' && field != 'O')
	{
	  cerr << "\nFile already exists.\nOverwrite, Abort?";
      field = cin.get();
    }
    if(field == 'A') return; // abort
    // overwrite
	if(remove(fileOut.c_str()))
	{
	  cerr << "\nAccess denied. Aborting.";
	  return;
	}
	rename(temp.c_str(), fileOut.c_str());
  }
}