#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int main(){
    ifstream fin("input.txt");
    if (!fin) { // 检查输入文件是否打开成功
        cerr << "无法打开 input.txt！" << endl;
        return 1;
    }
    string line;
    ofstream fout("output.txt");
    if (!fout) {
        cerr << "Error: Cannot create output.txt!" << endl;
        return 1;
    }
   //fout<<line<<endl;
  while (getline(fin, line)) { // 逐行读取所有内容
    fout << line << endl;    // 写入时保留换行符
}
}