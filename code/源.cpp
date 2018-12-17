#include<iostream>
#include <fstream>
#include <stdlib.h>
#include <cassert>
#include <string>
#include <map>
#include <vector>
#include <string.h>

using namespace std;

#define N 4

string x86Resgiter[N] = { "eax","ebx","ecx","edx" };
string mipsResgiter[N] = { "t1","t2","t3","t4" };

map<string, string> strMap;	//�Ĵ���֮���ӳ��� 

vector<string> readTxt(string file){
	ifstream infile;
	infile.open(file.data());   //���ļ����������ļ��������� 
	assert(infile.is_open());   //��ʧ��,�����������Ϣ,����ֹ�������� 
	vector<string> res;
	string s;
	while (getline(infile, s)) {
		int len = s.size();
		//�����β�ġ�����
		s = s.at(len - 1) == ';' ? s.substr(0, len - 1) : s;
		res.insert(res.end(), s);
	}
	infile.close();             //�ر��ļ������� 
	return res;
}

void init() {
	//������ 
	for (int i = 0; i < N; i++) {
		strMap[x86Resgiter[i]] = mipsResgiter[i];
	}
}

vector<string> split(const string& str, const string& delim) {
	vector<string> res;
	if ("" == str) return res;
	//�Ƚ�Ҫ�и���ַ�����string����ת��Ϊchar*����
	char * strs = new char[str.length() + 1]; //��Ҫ����
	strcpy(strs, str.c_str());
	char * d = new char[delim.length() + 1];
	strcpy(d, delim.c_str());
	char *p = strtok(strs, d);
	while (p) {
		string s = p; //�ָ�õ����ַ���ת��Ϊstring����
		res.push_back(s); //����������
		p = strtok(NULL, d);
	}
	return res;
}

void writeTxt(char *file,string content){
	ofstream outfile(file); 
	outfile << content;
	outfile.close();
} 

int main() {
	vector<string> readStr = readTxt("../data/X86Str.txt");	
	string writeRes = "";
	init();
	int len = readStr.size();
	int pos;
	for (int i = 0; i < len; i++) {
		string str = readStr[i];
		string lineStr = "";
		
		//������Ϊ add 
		pos = readStr[i].find("add");
		if (pos != -1) {
			string temp = readStr[i].substr(pos+4);
			//cout << temp << endl;
			vector<string> params = split(temp, ",");
			if (params.size() == 2) {	//�������Ĵ������������δ����������
				lineStr += "lw $" +strMap[params[0]]+"\n";
				lineStr += "lw $" + strMap[params[1]] + "\n";
				lineStr += "addu $" + strMap[params[0]] + ",$"+ strMap[params[0]] + ",$" + strMap[params[1]];
			}	
			//����չ 
		}
		writeRes += lineStr + "\n";
	}
	cout << writeRes << endl;
	writeTxt("../data/MipsStr.txt",writeRes);
	return 0;
}
