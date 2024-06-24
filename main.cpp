#include <iostream>
#include "kern/kern.h"
using namespace std;

int main(int argc, char* argv[]) 
{
  string cmd;
  if(argc > 1)
    cmd = argv[1];
  else cerr << "The program has given up.\n";
  cout << "You have requested `" << cmd << "`.";
  
  return 0;
}

