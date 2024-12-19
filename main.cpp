#include "main.h"

using namespace std;

string prog_name = "formatter";

// print commands
void printHelp(int argc, ...)
{
	if (argc > 0)
	{
		va_list args;
		va_start(args, argc);

		for (int i = 0; i < argc; i++)
		{
			const char *arg = va_arg(args, const char *);	// Get each
															// argument as a
															// const char*
			// Print the specific help for this argument
			if (helpArgs.find(arg) != helpArgs.end())
			{
				cout << "USAGE: " << prog_name << " " << arg << " " <<
					helpArgs[arg] << "\n";
			}
			else
			{
				cout << "Unknown argument: " << arg << "\n";
			}
		}

		va_end(args);
	}
	else
	{
		// No arguments, print general help
		cout << "USAGE: " << prog_name << " [options] <...>\n\n";
	  for (const auto & desc:helpDesc)
		{
			cout << desc.first << " " << desc.second << "\n";
		}
	}
}

unordered_map < string, function < int (int argc, char **...) >> cmds = {
	{"help", printHelp},

	{"ana", autoNewline},
	{"auto-newline", autoNewline}
};

vector < pair < string, string > >helpDesc = {
	{"help", "Prints this message."},
	{"ana, auto-newline",
	 "Re-newlines documents to fit within a certain horizontal width."}
};

map < string, string > helpArgs = {
	{"help", ""},				// no arguments
	{"ana", "<input file> <output file> <max character limit>"},
	{"auto-newline", "<input file> <output file> <max character limit>"}
};

int main(int argc, char *argv[])
{
	if (argv[0][0] != NULL)		// from standard ISO C11: argv[0][0] shall be
								// the null character if the program name is
								// not available from the host environment.
	{
		char *last_slash;
		last_slash = strrchr(argv[0], '/');
		if (last_slash != NULL)
			prog_name = string(last_slash);
		else
			prog_name = string(argv[0]);
	}

	cout << "formatter (c) Mileter under MIT License; " << F_BUILD_TYPE << " "
		<< F_BUILD_VER << "\n";
	string request;
	if (argc > 1)
		request = argv[1];
	else
	{
		request = "help";

		return 0;
	}

	if (cmds.find(request) == cmds.end())
		request = "help";

	int result = cmds[request] (argc - 2, argv[2]);

	if (result == ERR_IMPROPER_ARGS)
		cerr << "The routine failed with error: improper arguments.\n"
			<< "RUN " << prog_name << " help " << request <<
			"to check whether all arguments were passed.";

	return 0;
}
