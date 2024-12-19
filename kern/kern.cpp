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
	if (input.fail())
		return false;

	// make sure that the data is not corrupted
	input.putback(second);
	input.putback(first);

	// the check
	return first == '\n' && second == '\n' ? true : false;
}

void initnewline(istream & input,	// any input stream works... cin, ifstream
				 ostream & output,	// any output stream works... cout,
				 // ofstream...
				 int maxKerning)
{
	int lineCharCount = 0;
	while (true)
	{
		if (isParagraphBreak(input))
		{
			output << "\n\n";
			lineCharCount = 0;
		}
		string word;
		if (!(input >> word))	// no more chars
			break;
		if (lineCharCount + word.size() - 1 > maxKerning)	// to many words
		{						// ^ -1 to not account for the last space
			output << endl;
			lineCharCount = 0;	// carridge return (restart to col 0)
		}
		output << word << " ";
		lineCharCount += word.size() + 1;	// account for words and spaces
	}
}

void renewline(istream & input, ostream & output, int maxKerning)
{
	initnewline(input, output, maxKerning);
}

int autoNewline(int argc, ...)
{
	// Check that we have exactly 3 arguments
	if (argc != 3)
	{
		return ERR_IMPROPER_ARGS;
	}

	va_list args;
	va_start(args, argc);		// Corrected: use argc instead of undefined
								// `n`

	// Read the arguments
	std::string fileIn = std::string(va_arg(args, char *));
	std::string fileOut = std::string(va_arg(args, char *));

	int maxKerning;

	try
	{
		// Convert the 3rd argument to an integer (maxKerning)
		maxKerning = std::stoi(va_arg(args, char *));	// Use std::stoi for
														// string to int
														// conversion
	}
	catch( ...)					// Catch all exceptions
	{
		va_end(args);			// Clean up va_list
		return ERR_IMPROPER_ARGS;
	}

	// Clean up va_list
	va_end(args);

	string temp = fileOut + ".bak";
	ifstream fin(fileIn);
	ofstream fout(temp);
	renewline(fin, fout, maxKerning);
	fin.close();
	fout.close();
	if (rename(temp.c_str(), fileOut.c_str()))
	{
		char field;
		while (field != 'A' && field != 'O')
		{
			cerr << "\nFile already exists.\nOverwrite, Abort?";
			field = cin.get();
		}
		if (field == 'A')
			return;				// abort
		// overwrite
		if (remove(fileOut.c_str()))
		{
			return ERR_FILEIO_DENIED;
		}
		rename(temp.c_str(), fileOut.c_str());
	}

	return ERR_OK;
}
