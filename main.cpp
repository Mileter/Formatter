#include "main.h"

using namespace std;

// print commands
void printHelp(int argc, ...)
{
	cout << "USAGE: formatter [options] <...>\n\n";
	for(int i = 0; i < helpDesc.size(); i++)
		cout << helpDesc[i].first << " " << helpDesc[i].second << "\n";
}

unordered_map < string, function < int (int argc, string ...) >> cmds = {
	{"help", printHelp},

	{"ana", autoNewline},
	{"auto-newline", autoNewline}
};

vector < pair<string, string> > helpDesc = {
	{"help", "Prints this message."},
	{"ana, auto-newline", "Re-newlines documents to fit within a certain horizontal width."}
};

int main(int argc, char *argv[])
{
	cout << "Formatter (c) Mileter under MIT License; " << F_BUILD_TYPE << " "
		<< F_BUILD_VER << "\n";
	string request;
	if (argc > 1)
		request = argv[1];
	else
	{
		request = "help";

		return 0;
	}

	cmds[request]();

	return 0;
}
