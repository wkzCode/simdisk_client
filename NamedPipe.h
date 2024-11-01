#pragma once
#include"CommonUse.h"

class NamedPipe {
private:
	HANDLE namedPipe;
	wstring pipeName;
	string buffer;
	DWORD bytesRead;
	DWORD bytesWritten;
public:
	NamedPipe(const string& pipeName);

	void write(string message);
	string read(bool cat = 0);

	~NamedPipe();
};

