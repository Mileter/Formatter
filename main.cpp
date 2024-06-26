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
       << "";
}

void autoNewline(string fileIn, string fileOut, int maxKerning)
{
  const char* bak = ".bak";
  ifstream fin(fileIn);
  ofstream fout(fileOut+".bak");
  renewline(fin, fout, maxKerning);
  fin.close();
  fout.close();
  rename(fileOut+bak, fileOut.c_str());
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

