#include <iostream>
#include <fstream>
using namespace std;


string Xor_OP(char * str) {
    const char a[5] = {'C', 'S', '5', '7', '9'};

    string rtn_s = "";

    for (int i = 0; i < 5; i++) {
        rtn_s += a[i] ^ str[i];
    }

    return rtn_s;
};

int malware() {

    ofstream yourData("YourData.txt");
    yourData << "Brent";

    yourData.close();

    ifstream read_Data("YourData.txt");

    string s;
    string Xor_s;
    while (getline(read_Data, s)) {
        Xor_s.append(Xor_OP(s.data())).append("\n");
    };

    cout << s;


    cout << Xor_s;

    ofstream MyFile("MyFile.txt");
    MyFile << "We have your data\n" + Xor_s;
    MyFile.close();
    return 0;
};

int main() {

    malware();
    return 0;
}