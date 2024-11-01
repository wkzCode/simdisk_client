#include"Shell.h"

void outputError(string errorMessage);

int main() {
	//���ڵ�¼�������ܵ�
	NamedPipe* namedPipe = NULL;
	try {
		namedPipe = new NamedPipe("\\\\.\\pipe\\NamedPipe");
	}
	catch (const string errorMessage) {
		outputError(errorMessage);
		return 1;
	}

	//��ȡ�û�ID
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

	Sleep(1000);//�ȴ���˳��򴴽�����ִ��ָ��������ܵ�

	//��������ִ��ָ��������ܵ�
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
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);                                      // ��ȡ����̨���
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);               // �����ı���ɫΪ��ɫ (FOREGROUND_RED)
	cerr << errorMessage << endl;
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // ����ΪĬ����ɫ
}