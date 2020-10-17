#include "MainFunctions.h"

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		return 1;
	}

	std::cout << "Searching " << argv[1] << " for graphstore.txt\n";

	char path[_MAX_PATH];
	strcpy_s(path,_MAX_PATH, argv[1]);
	Run(path);

	return 0;
}