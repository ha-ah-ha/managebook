#include<iostream>
#include<fstream>
#include<string>
#include<random>
#include <climits>
using namespace std;
std::random_device rd;
mt19937_64 gen(time(0));


struct player {
	int id;//编号
	int element;//元素
	bool operator<=(const player& p) const {
		if (id != p.id) {
			return id < p.id;
		} else {
			return element <= p.element;
		}
	}
};

template<class T>
class losertree {
public:
	virtual ~losertree(){}
	virtual void initialize(T* theplayer, int number) = 0;
	virtual int getthewinner() const = 0;
	virtual void replay(int theplayer, T newvalue) = 0;
};

template<class T >
class minlosertree:public losertree<T> {
private:
	int* tree;//内部节点，tree[0]是最终的赢者下标
	int* leave;//外节点，记录晋级的成员
	T* players;//参加比赛的元素
	int k;//选手个数
	int file_count;//文件数目
	int low1;//最底层外部节点的个数，2*（n-s）
	int offset;//2*s-1

	void play(int p, int leftchild, int rightchild);
	int loser(int x, int y) {//分数小的获胜，返回分数小的
		return players[x] <= players[y] ? y : x;
	}
	int winner(int x, int y) {
		return players[x] <= players[y] ? x : y;
	}
public:
	minlosertree(T* theplayer=NULL,int thenumberofplayers=0){
		tree = NULL;
		leave = NULL;
		initialize(theplayer, thenumberofplayers);
	}
	~minlosertree() {
		delete[] tree;
		delete[] leave;
	}
	void initialize(T* theplayer, int number);
	int getthewinner() const {
		return tree[0];
	}
	void replay(int theplayer, T newvalue);
	
};

template<class T>
void minlosertree<T>::play(int p, int leftchild, int rightchild) {
	tree[p] = loser(leftchild, rightchild);
	leave[p] = winner(leftchild, rightchild);
	while (p % 2 == 1 && p > 1) {
		tree[p / 2] = loser(leave[p - 1], leave[p]);
		leave[p / 2] = winner(leave[p - 1], leave[p]);
		p = p / 2;
	}
}

template<class T>
void minlosertree<T>::initialize(T* theplayer, int number) {
	int n = number;
	if (n < 2) {
		cout << "error!" << endl;
		return;
	}
	players = theplayer;//需要比较的元素
	k = n;
	delete[] tree;
	delete[] leave;
	tree = new int[n + 1];
	leave = new int[n + 1];

	int s;
	for (s = 1; 2 * s <= n - 1; s += s);//找到最底层最左端的内部节点
	low1 = 2 * (n - s);//最底层外部节点的数量(偶数个）
	offset = 2 * s - 1;//计算父节点的索引
	for (int i = 2; i <= low1; i += 2) //比较n-s次
		play((i + offset) / 2, i - 1, i);//全部比较完了
	int temp = 0;
	if (n % 2 == 1) {//如果有奇数个节点
		play(n / 2, leave[n - 1], low1 + 1);//比较更新最后的父节点
		temp = low1 + 3;
	}
	else
		temp = low1 + 2;
	for (int i = temp; i <= n; i += 2) {//处理剩余的外部节点
		play((i - low1 + n - 1) / 2, i - 1, i);
	}
	tree[0] = leave[1];
};

template<class T>
void minlosertree<T>::replay(int theplayer, T newvalue) {
	int n = k;
	if (theplayer <= 0 || theplayer > n) {
		cout << "error!!" << endl;
		return;
	}
	players[theplayer] = newvalue;
	int matchs, leftchild, rightchild;//将要比赛的场次，左儿子、右儿子
	if (theplayer <= low1) {//如果要比赛的结点在最下层
		matchs = (offset + theplayer) / 2;
		leftchild = 2 * matchs - offset;
		rightchild =leftchild+1;
	}
	else {//要比赛的结点在次下层
		matchs = (theplayer - low1 + n - 1) / 2;
		if (2 * matchs == n - 1) {//特殊情况，其中一方是晋级后的人
			leftchild = leave[2 * matchs];
			rightchild = theplayer;
		}
		else {
			leftchild = 2 * matchs - n + 1 + low1;
			rightchild = leftchild + 1;
		}
	}
	//确定要比赛的场次以及比赛的选手
	if (theplayer == tree[0]) {//如果改变的是最后的赢家
		for (; matchs >= 1; matchs /= 2) {
			int oldlosernode = tree[matchs];
			tree[matchs] = loser(oldlosernode, theplayer);
			leave[matchs] = winner(oldlosernode, theplayer);//比较旧败者和新胜者
			theplayer = leave[matchs];//向上传递，继续处理更高层父节点
		}
	}
	else {
		//更新当前父节点的败者和胜者
		tree[matchs] = loser(leftchild, rightchild);
		leave[matchs] = winner(leftchild, rightchild);
		//处理奇数节点的情况
		if (matchs == n - 1 && n % 2 == 1) {
			matchs /= 2;
			tree[matchs] = loser(leave[n - 1], low1 + 1);
			leave[matchs] = winner(leave[n - 1], low1 + 1);
		}
		//向上更新所有祖先节点
		matchs /= 2;
		for (; matchs >= 1; matchs /= 2) {
			tree[matchs] = loser(leave[matchs * 2], leave[matchs * 2 + 1]);
			leave[matchs] = winner(leave[matchs * 2], leave[matchs * 2 + 1]);
		}
	}
	tree[0] = leave[1];
}


void external_sort() {
	string path;
	string infile;
	string outfile;
	int buffer=0;//缓冲区大小
	int numbers = 0;//个数
	int count = 0;//访问磁盘次数
	//string filename = "input.txt";
	cout << "请输入想要模拟的磁盘文件路径(例如C:/Users/hit/Desktop/,若选择默认测试样例文件路径请输入0):";
	cin >> path;
	cout << "请输入缓冲区大小：";
	cin >> buffer;
	if (path == "0")
		path = "";
	infile = path + "input.txt";
	outfile = path + "output.txt";
	ofstream file(infile);
	if (!file.is_open()) {
		cerr << "无法打开txt!!" << endl;
		return;
	}
	cout << "随机创建文本请输入0,手动输入请输入1:";
	int a = -1;
	cin >> a;
	if (a == 0) {
		cout << "请输入想要在磁盘中初始化数字的个数：";
		cin >> numbers;
		cout << "磁盘初始内容为:";
		for (int i = 1; i <= numbers; i++) {
			int x = gen() % 1000 + 1;
			file << x<<' ';
			cout << x << ' ';
		}
	}
	else if(a==1){
		cout << "请输入想要在磁盘中初始化数字的个数：";
		cin >> numbers;
		cout << "请输入：";
		for (int i = 1; i <= numbers; i++) {
			int x;
			cin >> x;
			file << x << ' ';
		}
	}
	file.close();

	ifstream fin(infile);//打开文件
	player* playerss=new player[numbers+1];
	//int runnum = (numbers + buffer - 1) / buffer;//总共的run文件数量
	for (int i = 1; i <= buffer&&fin>>playerss[i].element; i++) {
		playerss[i].id = 1;
		count++;
	}//依次读取磁盘中的数字进入缓冲区
	minlosertree<player> tree1(playerss, buffer);
	int num = 0;
	int merger = 0;
	for (int i = 0; i < numbers; i++) {
		if (!(fin >> num)) {
			num = INT_MAX;  // 使用 INT_MAX 作为文件结束标志
		} else {
			count++;
		}
		player tempwinner;
		tempwinner.element = playerss[tree1.getthewinner()].element;
		tempwinner.id = playerss[tree1.getthewinner()].id;
		player tempnum;
		tempnum.element = num;
	
		if (num != INT_MAX && num >= tempwinner.element) {
			tempnum.id = tempwinner.id;  // 沿用当前顺串编号
		} else {
			tempnum.id = tempwinner.id + 1;  // 生成新顺串
		}
	
		tree1.replay(tree1.getthewinner(), tempnum);
		string test1 = path + "test" + to_string(tempwinner.id) + ".txt";
		merger = max(merger, tempwinner.id);  // 更新归并路数
		ofstream fout(test1, ios::app);
		if (num != INT_MAX) {
			fout << tempwinner.element << ' ';  // 写入实际数据
		
		}
		fout.close();
		count++;
	}
	fin.close();
	cout<<endl;
	cout << "顺串生成完毕,一共生成"<<merger<<"个顺串如下：" << endl;
	for (int i = 1; i <= merger; i++) {
		string test= path + "test" + to_string(i) + ".txt";
		ifstream fin(test);
		int temp = 0;
		cout << "test" + to_string(i) + ".txt:";
		while (fin >> temp) {
			cout << temp << ' ';
		}
		cout << endl;
		fin.close();
	}

	ofstream fout(outfile);
	if (merger == 1) {
		string test = path + "test" + to_string(1) + ".txt";
		ifstream fin(test);
		int tempnumber;
		cout << "最终排序结果如下：";
		while (fin >> tempnumber) {
			fout << tempnumber << ' ';
			cout << tempnumber << ' ';
			count += 2;
		}
		fout.close();
		fin.close();
		cout<<"访存次数为："<<count<<endl;
		return;
	}
	else {
		//cout << "将这些文件进行" << merger << "路归并，结果如下：" << endl;
		int* dplayer = new int[merger + 10];
		int* pointer = new int[merger + 10];
		for (int i = 1; i <= merger; i++) {//分别从各个顺串中读取数据进行排序
			string test = path + "test" + to_string(i) + ".txt";
			ifstream fin(test);
			fin >> dplayer[i];
			pointer[i] = fin.tellg();
			fin.close();
			count++;
		}
		minlosertree<int> tree2(dplayer, merger);
		int cnt = 0;
		while (cnt < numbers) {
			cnt++;
			int temp = tree2.getthewinner();//得到胜者后
			int tempwinner = dplayer[temp];
			if(tempwinner!=INT_MAX){fout << tempwinner << ' ';}
			//cout << tempwinner << ' ';
			count++;
			string test = path + "test" + to_string(temp) + ".txt";//继续读入新的数据进行排序
			ifstream fin(test);
			fin.clear();
			fin.seekg(pointer[temp] + 1);
			int tempnum;
			if (pointer[temp] + 1 == 0)
				tempnum = INT_MAX;
			else {
				fin >> tempnum;
				pointer[temp] = fin.tellg();//保存上次在顺串中读到的位置
				if (pointer[temp] + 1 == 0)
					tempnum = INT_MAX;
			}
			tree2.replay(temp, tempnum);//重新得出胜者
			fin.close();
			count++;
			if(tempwinner==INT_MAX){
				break;
			}
			
		}
		cout << "将这些文件进行" << merger << "路归并，结果如下：" << endl;
		int t;
		fout.close();
		ifstream fout(outfile);
		while(fout>>t){cout << t << ' ';}
		fout.close();
		cout<<"访存次数为："<<count<<endl;
	}
}

int main() {
	external_sort();
}