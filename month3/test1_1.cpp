#include<bits/stdc++.h>
using namespace std;
int n;
int r, c;
int sym_r, sym_c;//记录点
vector<string> note(1);
bool flag = false;//选中状态
bool zhan = false;
vector<string> ban;
int ro, co, sr, sc;
 
void erase_it()//删除选中内容
{
	flag = false;
	if (sym_r == r)//同一行
	{
		note[r].erase(co, sc - co);
		c = co;
	}
	else //两行以上
	{
		note[ro] = note[ro].substr(0, co);//存前面的
		string tem = note[sr].substr(sc);//后半部分
		note.erase(note.begin() + sr);
 
		for (int i = ro + 1; i < sr; ++i)
		{
			note.erase(note.begin() + ro + 1);
		}
		note[ro] = note[ro] + tem;
 
		r = ro; c = co;//更新光标
	}
}

//光标移动
void mov()
{
	if (flag) { flag = false;  }//退出选中状态
	string comd;
	cin >> comd;
	if (comd == "Home")//把光标移动到当前行的开头
	{
		c = 0;
	}
	else if (comd == "End")//把光标移动到当前行的末尾
	{
		c = note[r].size();
	}
	else if (comd == "Up")//光标移动到上一行的相同列
	{
		if (r == 0) return;
		r--;
		if (note[r].size() < c)
		{
			c = note[r].size();
		}
 
	}
	else if (comd == "Down")//光标移动到下一行的相同列
	{
		if (r == note.size() - 1) return;
		r++;
		if (note[r].size() < c)
		{
			c = note[r].size();
		}
	}
	else if (comd == "Left")//光标左移一位
	{
		if (r == 0 && c == 0) return;
 
		if (c == 0)//移到上一行末尾
		{
			r--;
			c = note[r].size();
			return;
		}
		c--;
	}
	else if(comd=="Right")//光标右移一位
	{
		if (r == note.size() - 1 && c == note[r].size()) return;
 
		if (c == note[r].size())//移到下一行开头
		{
			r++;
			c = 0;
			return;
		}
		c++;
	}
 
}
 
//输入
void inser()
{
	if (flag) { erase_it(); }
 
	string comd;
	cin >> comd;
	if (comd == "Char")//输入一个字符
	{
		string word;
		cin >> word;
		note[r].insert(c, word);
 
		c++;//向右移
	}
	else if (comd == "Enter")//输入换行符，并进行换行
	{
		string a = note[r].substr(0, c);//前
		string b = note[r].substr(c);//后
		note[r] = a;
		note.insert(note.begin() + r + 1, b);
		c = 0; r++;
	}
	else if (comd == "Space")//输入空格
	{
		note[r].insert(c, " ");
		c++;
	}
	else if (comd == "Paste")//在当前光标后，插入粘贴板中的内容，若粘贴板中无内容，则忽略当前操作
	{
		if (ban.size() == 0) return;
		if (ban.size() == 1)
		{
			note[r].insert(c, ban[0]);
 
			c += ban[0].size();
		}
		else if (ban.size() == 2)
		{
			string a = note[r].substr(0, c) + ban[0];
			string b = ban[1] + note[r].substr(c);
			note[r] = a;
			note.insert(note.begin() + r + 1, b);
 
			r++; c = ban[1].size();
		}
		else
		{
			string a = note[r].substr(0, c) + ban[0];
			string b = ban[ban.size()-1] + note[r].substr(c);
			note[r] = a;
			note.insert(note.begin() + r + 1, b);
 
			for (int i = 1; i < ban.size() - 1; ++i)
			{
				note.insert(note.begin() + r + i, ban[i]);//插入到第r+1行前面
			}
 
			r += ban.size() - 1; 
			c = ban[ban.size() - 1].size();
		}
	}
}
 
//删除
void remove()
{
	if (flag) { erase_it(); return; }
	string comd;
	cin >> comd;
	if (comd == "Del")//删除当前光标位置之后的一个字符
	{
		if (r == note.size() - 1 && c == note[r].size()) return;
		else if (c == note[r].size())//如果为换行符
		{
			note[r] = note[r] + note[r + 1];
			note.erase(note.begin() + r + 1, note.begin() + r + 2);
 
			return;
		}
		note[r].erase(c, 1);
	}
	else//删除当前光标位置之前的一个字符
	{
		if (r == 0 && c == 0) return;
		else if (c == 0)
		{
			note[r] = note[r - 1] + note[r];
			c = note[r - 1].size();
			note.erase(note.begin() + r - 1, note.begin() + r);
			r--;
			return;
		}
		note[r].erase(c - 1, 1);
		c--;
	}
}
 
 
//粘滞功能
void shift()
{
	if (zhan)//关闭粘滞功能
	{
		if (sym_c != c || sym_r != r)//光标位置与记录点位置不同
		{
			sc = sym_c; sr = sym_r; co = c; ro = r;
 
			if (sr < ro) //保持sr>=ro
			{ 
				swap(sr, ro); swap(sc, co);
			}
			else if (sr == ro && sc < co) { swap(sc, co); }
			flag = true;//进入选中状态
		}
		zhan = false;
	}
	else//启动粘滞功能
	{
		if (flag)//
		{
			flag = false;
 
		}
		else 
		{
			sym_c = c; sym_r = r;//更新记录点
		}
		zhan = true;
	}
 
}
 
 
//查找
void find_it()
{
	string word;
	cin >> word;
	int coun = 0;
	if(flag)//处于选中状态
	{
		if (ro != sr)
		{
			for (int i = co; i + word.size() <= note[ro].size(); i++)//第一排
			{
				string tem = note[ro].substr(i, word.size());
				if (tem == word) coun++;
			}
			for (int i = 0; i + word.size() <= sc; ++i)//最后一排
			{
				string tem = note[sr].substr(i, word.size());
				if (tem == word) coun++;
			}
			for (int i = ro + 1; i < sr; ++i)
			{
				for (int j = 0; j + word.size() <= note[i].size(); ++j)
				{
					string tem = note[i].substr(j, word.size());
					if (tem == word) coun++;
				}
			}
		}
		else//在同一排
		{
			for (int i = co; i + word.size() <= sc; ++i)
			{
				string tem = note[ro].substr(i, word.size());
				if (tem == word) coun++;
			}
		}
	}
	else
	{
		for (int i = 0; i <= note.size() - 1; ++i)
		{
			for (int j = 0; j + word.size() <= note[i].size(); ++j)
			{
				string tem = note[i].substr(j, word.size());
				if (tem == word) coun++;
			}
		}
	}
	cout << coun << endl;
 
}
 
//字数统计
void count_char()
{
	int res_c=0;
	if (flag)//处于选中状态
	{
		if (sr != ro)
		{
			for (int i = ro + 1; i < sr; ++i)
			{
				for (int j = 0; j < note[i].size(); ++j)
				{
					if (note[i][j] != ' ') res_c++;
				}
			}
			for (int i = co; i < note[ro].size(); ++i)
			{
				if (note[ro][i] != ' ') res_c++;
			}
			for (int i = 0; i < sc; ++i)
			{
				if(note[sr][i]!=' ') res_c++;
			}
		}
		else//同一行
		{
			for (int i = co; i < sc; ++i)
			{
				if (note[ro][i] != ' ') res_c++;
			}
		}
	}
	else//不处于选中状态，统计记事本中所有字符
	{
		for (int i = 0; i < note.size(); ++i)
		{
			for (int j = 0; j < note[i].size(); ++j)
			{
				if (note[i][j] != ' ') res_c++;
			}
		}
	}
	cout << res_c << endl;
}
 
//复制
void notey_now()
{
	//ban.clear();
	if (flag)//
	{
		ban.clear();
		if (sr == ro)//在同一行
		{
			string tem = note[ro].substr(co, sc - co);
			ban.push_back(tem);
		}
		else
		{
			string a = note[ro].substr(co);
			ban.push_back(a);
			for (int i = ro + 1; i < sr; ++i)
			{
				ban.push_back(note[i]);
			}
			string b = note[sr].substr(0, sc);
			ban.push_back(b);
		}
	}
	else if(note[r].size()!=0)//复制当前行
	{
		ban.clear();
		ban.push_back(note[r]);
	}
}
 
 
//打印
void print()
{
	for (int i = 0; i != note.size(); ++i)
	{
		cout << note[i] << endl;
	}
 
}
 
int main()
{
	FILE* outfp;
	//freopen_s(&outfp, "out.txt", "w", stdout);
	cin >> n;
	
	for (int i = 0; i < n+50; ++i)
	{
		string op;
		cin >> op;
		if (op == "MOVE") mov();
		else if (op == "INSERT") inser();
		else if (op == "REMOVE") remove();
		else if (op == "SHIFT") shift();
		else if (op == "FIND") find_it();
		else if (op == "COUNT") count_char();
		else if (op == "noteY") notey_now();
		else if (op == "PRINT") print();
		
	}
	
	//fclose(stdout);//关闭文件
	return 0;
}