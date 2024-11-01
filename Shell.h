#pragma once
#include"NamedPipe.h"

class Shell {
private:
	NamedPipe& namedPipe;
public:
	Shell(NamedPipe& namePipe);
	void commandLine();

	void outputError(string message);
};