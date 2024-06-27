#include <iostream>
#include <functional>
#include <unordered_map>
#include <fstream>
#include <string>
#include <cstdio>

#include "kern/kern.h"

using namespace std;

void printHelp()
{
  cout << "USAGE:\n"
       << "formatter [options] <...>\n\n"
	   << "          --help\n"
	   << "          ^ Displays this message.\n\n"
	   << "          auto-newline [input filename] [output filename] [maximun column legnth]\n"
	   << "          ana          (^ Same as above.)\n"
	   << "          reformats to have specified column legnths (specified in maximun column legnth.)";
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

unordered_map<string, function<void()>> cmds = {
  {"--help", printHelp}
};

unordered_map<string, function<void(const string&, const string&, const int&)>> fcmds = {
  {"ana", autoNewline},
  {"auto-newline", autoNewline}
};

int main(int argc, char* argv[]) 
{
  string request;
  if(argc > 1)
    request = argv[1];
  else
  {
    cerr << "Dear user, please provide a task for me to do! :-)\n"
         << "Use `--help` for more information.\n";
    
    return 0;
  }

  cout << "You have requested `" << request << "`.\n";

  if(argc == 2 && cmds.find(request) != cmds.end())
    cmds[request]();
  else if(argc == 5 && fcmds.find(request) != fcmds.end())
    fcmds[request](argv[2], argv[3], stoi(argv[4]));
  else
    cerr << "Dear user, your request command `" << request << "` with " << argc - 2 << " extra request details, simply does not exist.\nPlease check your spelling again.";

  return 0;
}

