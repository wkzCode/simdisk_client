#include "Shell.h"

Shell::Shell(NamedPipe& pipe) :namedPipe(pipe) {}

void Shell::commandLine() {
	string message;
	while (true) {
		cout << "Simdisk:$ ";
		getline(cin, message);
		if (message == "clear") {
			system("cls");
			continue;
		}
		namedPipe.write(message);
		string buffer;
		if (message == "EXIT") {
			break;
		}

		else if (!message.find("cat")) {
			cout << "The maximum file size supported for opening is 266KB\n";
			Sleep(1000);
			buffer = namedPipe.read(1);
		}
		else if (!message.find("rd")) {
			buffer = namedPipe.read();
			if (buffer.size()) {
				if (buffer.find("-e")) {
					cout << buffer;
					getline(cin, message);
					namedPipe.write(message);
					buffer = namedPipe.read();
				}
			}
		}
		else {
			buffer = namedPipe.read();
		}
		if (!buffer.find("-e")) {
			outputError(buffer);
		}
		else {
			cout << buffer;
		}
	}
}

void Shell::outputError(string errorMessage) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);                                      // 获取控制台句柄
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);               // 设置文本颜色为红色 (FOREGROUND_RED)
	cerr << errorMessage.substr(2);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 重置为默认颜色
}
