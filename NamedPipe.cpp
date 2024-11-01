#include "NamedPipe.h"

NamedPipe::NamedPipe(const string& pipeName) {
	wstring name(pipeName.begin(), pipeName.end());
	namedPipe = CreateFile(
		name.c_str(),
		GENERIC_READ | GENERIC_WRITE, //可读可写
		0,                            //不共享文件
		NULL,
		OPEN_EXISTING,                //打开已经存在的命名管道
		0,
		NULL
	);
	if (namedPipe == INVALID_HANDLE_VALUE) {
		throw string("Error connecting to named pipe!" + to_string(GetLastError()));
	}
}

void NamedPipe::write(string message) {
	const char* s = message.c_str();
	WriteFile(namedPipe, s, strlen(s) + 1, &bytesWritten, NULL);
}

string NamedPipe::read(bool cat) {
	if (cat) {
		char c[512 * 1024];
		if (ReadFile(namedPipe, c, sizeof(c), &bytesRead, NULL)) {
			buffer = c;
			return buffer;
		}
	}
	else {
		char c[1024];
		if (ReadFile(namedPipe, c, sizeof(c), &bytesRead, NULL)) {
			buffer = c;
			return buffer;
		}
	}
}

NamedPipe::~NamedPipe() {
	CloseHandle(namedPipe);
}
