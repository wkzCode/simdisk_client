#include"Shell.h"

void outputError(string errorMessage);

int main() {
	//用于登录的命名管道
	NamedPipe* namedPipe = NULL;
	try {
		namedPipe = new NamedPipe("\\\\.\\pipe\\NamedPipe");
	}
	catch (const string errorMessage) {
		outputError(errorMessage);
		return 1;
	}

	//获取用户ID
	cout << "please input userID(0~255): ";
	int userID;
	cin >> userID;
	if (userID < 0 || userID>255) {
		return 1;
	}
	string s;
	getline(cin, s);

	namedPipe->write(to_string(userID));
	string message = namedPipe->read();
	if (message.size()) {
		cerr << "user already login" << endl;
		return 1;
	}
	namedPipe->~NamedPipe();

	Sleep(1000);//等待后端程序创建用于执行指令的命名管道

	//连接用于执行指令的命名管道
	string pipeName = "\\\\.\\pipe\\NamedPipe" + to_string(userID);
	try {
		namedPipe = new NamedPipe(pipeName);
	}
	catch (const string errorMessage) {
		outputError(errorMessage);
		return 1;
	}
	Shell shell(*namedPipe);
	try {
		shell.commandLine();
	}
	catch (const string errorMessage) {
		shell.outputError(errorMessage);
	}
	return 0;
}

void outputError(string errorMessage) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);                                      // 获取控制台句柄
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);               // 设置文本颜色为红色 (FOREGROUND_RED)
	cerr << errorMessage << endl;
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 重置为默认颜色
}