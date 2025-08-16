#include<iostream>
//#include<stack>
#include<random>
#include<chrono>
using namespace std::chrono;
using namespace std;
mt19937_64 gen(time(0));
double sumtime = 0;
int opnum=0;

template<class T>
class stack {
private:
	int topIndex = -1;
	int capacity = 10;
	T* data = nullptr;

	void resize(int newCapacity) {
		T* newData = new T[newCapacity];
		copy(data, data + topIndex + 1, newData);
		delete[] data;
		data = newData;
		capacity = newCapacity;
	}

public:
	stack(int initCapacity = 10) :
		capacity(initCapacity),
		data(new T[initCapacity]) {}

	~stack() { delete[] data; }

	stack(const stack&) = delete;
	stack& operator=(const stack&) = delete;

	void push(const T& val) {
		if (topIndex == capacity - 1)
			resize(capacity * 2);
		data[++topIndex] = val;
	}

	void pop() {
		if (empty())
			throw runtime_error("Pop empty stack");
		--topIndex;
		if (topIndex < capacity / 4 && capacity > 10)
			resize(capacity / 2);
	}

	T& top() {
		if (empty())
			throw runtime_error("Access empty stack");
		return data[topIndex];
	}

	bool empty() const { return topIndex == -1; }
	int size() const { return topIndex + 1; }
};


struct node {
	node* next;
	node* down;
	int val;
	node(node* next1 = NULL, node* down1 = NULL, int val1=-1) {
		next = next1;
		down = down1;
		val = val1;
	}
};

class erfen {
private:
	int n;
	int* a;
	int binarySearch(int target) {
		int left = 0, right = n - 1;
		while (left <= right) {
			int mid = (right + left) / 2;
			if (a[mid] == target) return mid;
			if (a[mid] < target) left = mid + 1;
			else right = mid - 1;
		}
		return -1;//O(log n)
	}
public:
	erfen(int n1=10,int* a1=NULL){
		if(a1==NULL){
			n = n1;
			a = new int[n];
		}
		else {
			a = a1;
			n = n1;
			for (int i = 0; i < n - 1; i++) {
				for (int j = 0; j < n - i - 1; j++) {
					if (a[j] > a[j + 1]) {
						int t = a[j];
						a[j] = a[j + 1];
						a[j + 1] = t;
					}
				}
			}//冒泡排序  O(n^2)
		}
	}
	~erfen(){
		delete[] a;
	}
	void intialize(int* x, int n1) {
		delete[] a;
		a = x;
		n = n1;
		for (int i = 0; i < n-1; i++) {
			for (int j = 0; j < n - i-1; j++) {
				if (a[j] > a[j + 1]) {
					int t = a[j];
					a[j] = a[j + 1];
					a[j + 1] = t;
				}
			}
		}//冒泡排序 O(n^2)
	}
	bool serach(int target) {
		int left = 0, right = n - 1;
		while (left <= right) {
			int mid = left + (right - left) / 2;
			if (a[mid] == target) return true;
			if (a[mid] < target) left = mid + 1;
			else right = mid - 1;
		}
		return false;
		//O(log n)
	}
	void insert(int target) {
		int left = 0, right = n - 1;
		int pos = n; 

		while (left <= right) {
			int mid = left + (right - left) / 2;
			if (a[mid] >= target) {
				pos = mid;
				right = mid - 1;
			}
			else {
				left = mid + 1;
			}
			//O(log n)
		}

		int* new_arr = new int[n + 1];

		for (int i = 0; i < pos; ++i)
			new_arr[i] = a[i];

		new_arr[pos] = target;

		for (int i = pos; i < n; ++i)
			new_arr[i + 1] = a[i];

		delete[] a; 

		a = new_arr;
		n++;
		//O(n)
	}
	void erase(int target) {
		//auto start = high_resolution_clock::now();

		int pos = binarySearch(target);
		if (pos == -1) {
			cout << "元素不存在" << endl;
			return;
		}

		// 创建新数组
		int* newArr = new int[n - 1];
		for (int i = 0; i < pos; ++i)
			newArr[i] = a[i];
		for (int i = pos; i < n - 1; ++i)
			newArr[i] = a[i + 1];

		// 更新数据
		delete[] a;
		a = newArr;
		--n;//O(n)

		//auto end = high_resolution_clock::now();
		//double time = duration_cast<nanoseconds>(end - start).count();
		//printf("删除操作耗时: %.3f ns\n", time);
	}

	// 删除最小元素
	void erasemin() {
		if (n == 0) {
			cout << "数组为空" << endl;
			return;
		}

		// 直接删除第一个元素
		int* newArr = new int[n - 1];
		for (int i = 0; i < n - 1; ++i)
			newArr[i] = a[i + 1];

		delete[] a;
		a = newArr;
		--n;//O(n)
		//cout << "已删除最小元素" << endl;
	}

	// 删除最大元素
	void erasemax() {
		if (n == 0) {
			cout << "数组为空" << endl;
			return;
		}

		// 直接删除最后一个元素
		int* newArr = new int[n - 1];
		for (int i = 0; i < n - 1; ++i)
			newArr[i] = a[i];

		delete[] a;
		a = newArr;
		--n;
		cout << "已删除最大元素" << endl;//O(1)
	}

	
	/*void display() {
		cout << "当前数组[ ";
		for (int i = 0; i < n; ++i)
			cout << a[i] << " ";
		cout << "]" << endl;
	}*/
};


class skiplist {
private:
	node* head;
	const int maxlevel=32;
	//stack<node*> stack1;
public:
	skiplist() {
		node* below = nullptr;
		for (int i = 0; i < maxlevel; i++) {
			head = new node(nullptr, below, -1); // 创建多层头节点
			below = head;
		}
	}
	~skiplist() {
		node* curr = head;
		while (curr) {
			node* temp = curr;
			while (temp->next) {
				node* del = temp->next;
				temp->next = del->next;
				delete del;
			}
			node* down = curr->down;
			delete curr;
			curr = down;
		}
	}
	bool search(int target);
	void initialize(int* x,int size);
	void insert(int target);
	void erase(int target);
	void erasemin();
	void erasemax();
	void print();
	void rebuild();
};

bool skiplist::search(int target) {//O(log n)
	node* p = head;
	while (p) {
		while (p->next && p->next->val < target) {
			p = p->next;
		}
		if (!p->next || p->next->val > target) {
			p = p->down;
		}
		else {
			return true;
		}
	}
	return false;
}

void skiplist::insert(int target) {
	//auto start = high_resolution_clock::now();
	stack<node*> stack1;
	node* p = head;
	while (p) {
		while (p->next && p->next->val < target) {
			p = p->next;
		}
		stack1.push(p);
		p = p->down;
	}

	bool insertup = true;
	node* newp = NULL;
	while (insertup && !stack1.empty()) {
		node* insert = stack1.top();
		stack1.pop();
		insert->next = new node(insert->next, newp, target);
		newp = insert->next;
		if ((gen() & 1) == 0) {
			insertup = false;//停止向上继续进一层
		}
	}
	if (insertup) {
		head = new node(new node(NULL, newp, NULL), head, -1);
	}//O(log n)
}

void skiplist::erase(int target) {
	node* p = head;
	bool found = false;
	while (p) {//遍历整个链表
		while (p->next && p->next->val < target) {
			p = p->next;
		}
		if (!p->next || p->next->val > target) {
			p = p->down;
		}
		else {//找到这个值所在的位置
			found = true;
			node* todelete = p->next;
			p->next = p->next->next;
			p = p->down;
			delete todelete;
		}
	}
	if (!found) {
		cout << -1 << endl;
	}//O(log n)
}

void skiplist::initialize(int* x,int size) {
	/*for (int i = 0; i < size-1; i++) {
		for (int j = 0; j < size-1-i; j++) {
			if (x[j] > x[j + 1]) {
				int t = x[j];
				x[j] = x[j + 1];
				x[j + 1] = t;
			}
		}
	}*/
	//auto start = high_resolution_clock::now();
	node* cur = head;
	while (cur) {
		node* tmp = cur->down;
		while (cur->next) {
			node* del = cur->next;
			cur->next = del->next;
			delete del;
		}
		delete cur;
		cur = tmp;
	}
	node* below = nullptr;
	for (int i = 0; i < maxlevel; i++) {
		below = new node(nullptr, below, -1);
	}
	head = below; // 最高层头节点
	for (int i = 0; i < size; i++) {
		insert(x[i]); // 复用 insert 函数保证随机层数
	}//O(n log n)
}

void skiplist::erasemin() {
	/*if (head->down == NULL) {
		cout << "链表为空,无法删除" << endl;
		return;
	}*/
	node* p = head;
	while (p->down) {
		p = p->down;
	}
	if (!p->next) {
		cout << "链表为空,无法删除!" << endl;
		return;
	}
	int minval = p->next->val;//找到值最小的元素
	//O(log n)
	
	/*delete p;
	p = head;
	while (p) {
		node* cur = p;
		if (p->next && p->next->val == minval) {
			node* deletemin = cur->next;
			cur->next = deletemin->next;
			delete deletemin;
		}
		p = p->down;
	}*/
	erase(minval);
	cout << "成功删除关键词最小的元素:" << minval << endl;
}

void skiplist::erasemax() {
	node* p = head;
	while (p->down) {
		p = p->down;
	}
	if (p->next==NULL) {
		cout << "跳表为空" << endl;
	}
	while (p->next) {
		p = p->next;
	}
	int maxval = p->val;
	erase(maxval);
	cout << "成功删除关键词最大的元素:" << maxval << endl;
	//O(log n)
}

void skiplist::print() {
	node* layer = head;
	int level = maxlevel;
	while (layer) {
		if(layer->next)
		{
			cout << "Lv" << level << ":\t";
			node* curr = layer->next; // 跳过头节点
			while (curr) {
				cout << curr->val;
				if (curr->next) cout << " -> ";
				curr = curr->next;
			}
			cout << endl;
		}	
		layer = layer->down;
		level--;
	}
}

void skiplist::rebuild() {
	stack<int> elements;

	// 收集元素（正序）
	node* p = head;
	while (p->down)
		p = p->down;
	p = p->next;
	if (p == NULL) {
		cout << "链表为空" << endl;
		return;
	}
	while (p) {
		elements.push(p->val);
		p = p->next;
	}

	stack<int> temp;// 重建跳表
	while (!elements.empty()) {
		temp.push(elements.top());
		elements.pop();
	}
	// 清除旧数据
	initialize(nullptr, 0);

	// 插入新数据
	while (!temp.empty()) {
		insert(temp.top());
		temp.pop();
	}
	cout << "跳表重建完成，层级已优化" << endl;
}

int randint(int l, int r) {
	return gen() % (r - l + 1) + l;//生成l至r之间的随机数。
}

int main() {
	cout << "****************************" << "\n";
	cout << "***** 跳表的实现与分析 *****" << "\n";
	cout << "****************************" << "\n";
	skiplist list1;
	erfen arr1;
	while (true) {
		int x;
		cout << "*请输入指令" << "\n" << "0->退出" << "\n";
		cout << "1->初始化" << "\n";
		cout << "2->插入元素" << "\n";
		cout << "3->查询" << "\n";
		cout << "4->删除" << "\n";
		cout << "5->删除关键字最小的元素" << "\n";
		cout << "6->删除关键字最大的元素" << "\n";
		cout << "7->输出跳表结构" << "\n";
		cout << "8->总用时以及平均用时" << "\n";
		cout << "9->与排序数组的折半查找相对比" << "\n";
		cout << "10->重建跳表" << "\n";
		cin >> x;
		switch (x)
		{
		case 0:
		{
			cout << "结束运行";
			return 0;
		}
		case 1:
		{
			int y;
			cout << "请选择：0->随机生成n个数字初始化" << "\n";
			cout << "        1->输入数字初始化" << "\n";
			cin >> y;
			switch (y)
			{
			case 0:
			{
				cout << "请输入n：";
				int n;
				cin >> n;
				int* a=new int[n];
				for (int i = 0; i < n; i++) {
					a[i] = randint(0,100000000);
				}
				auto start = high_resolution_clock::now();
				list1.initialize(a,n);
				auto end = high_resolution_clock::now();
				double time = duration_cast<nanoseconds>(end - start).count();
				printf("用时为: %.3f ns\n", time);
				cout << "生成完毕！"<<"\n";
				sumtime += time;
				opnum++;
				arr1.intialize(a,n);
				break;
			}
			case 1: 
			{
				
				int z;
				cout << "请输入输入数字的个数：";
				cin >> z;
				int* a = new int[z];
				cout << "请依次输入要加入跳表的数字(以空格间隔)：";
				for (int i = 0; i < z; i++) {
					cin >> a[i];
				}
				auto start = high_resolution_clock::now();
				list1.initialize(a, z);
				auto end = high_resolution_clock::now();
				double time = duration_cast<nanoseconds>(end - start).count();
				printf("用时为: %.3f ns\n", time);
				sumtime += time;
				opnum++;
				arr1.intialize(a, z);
				break;
			}
			default:
				break;
			}
			break;
		}
		case 2:
		{
			cout << "请输入准备插入的元素：";
			int y;
			cin >> y;
			auto start = high_resolution_clock::now();
			list1.insert(y);
			auto end = high_resolution_clock::now();
			double time = duration_cast<nanoseconds>(end - start).count();
			cout << "插入成功" << "\n";
			printf("用时为: %.3f ns\n", time);
			sumtime += time;
			opnum++;
			arr1.insert(y);
			break;
		}
		case 3:
		{
			int y;
			cout << "请输入准备查询的数字：";
			cin >> y;
			auto start = high_resolution_clock::now();
			if (list1.search(y)) {
				cout << "查询成功！" << "\n";
			}
			else {
				cout << "查询失败" << "\n";
			}
			auto end = high_resolution_clock::now();
			double time = duration_cast<nanoseconds>(end - start).count();
			printf("用时为: %.3f ns\n", time);
			sumtime += time;
			opnum++;
			break;
		}
		case 4:
		{
			int y;
			cout << "请输入准备删除的数字：";
			cin >> y;
			auto start = high_resolution_clock::now();
			list1.erase(y);
			auto end = high_resolution_clock::now();
			double time = duration_cast<nanoseconds>(end - start).count();
			printf("用时为: %.3f ns\n", time);
			sumtime += time;
			opnum++;
			arr1.erase(y);
			break;
		}
		case 5:
		{
			auto start = high_resolution_clock::now();
			list1.erasemin();
			auto end = high_resolution_clock::now();
			double time = duration_cast<nanoseconds>(end - start).count();
			printf("用时为: %.3f ns\n", time);
			sumtime += time;
			opnum++;
			arr1.erasemin();
			break;
		}
		case 6:
		{
			auto start = high_resolution_clock::now();
			list1.erasemax();
			auto end = high_resolution_clock::now();
			double time = duration_cast<nanoseconds>(end - start).count();
			printf("用时为: %.3f ns\n", time);
			sumtime += time;
			opnum ++;
			arr1.erasemax();
			break;
		}
		case 7:
		{
			auto start = high_resolution_clock::now();
			list1.print();
			auto end = high_resolution_clock::now();
			double time = duration_cast<nanoseconds>(end - start).count();
			printf("用时为: %.3f ns(该时间不计入总时间)\n ", time);
			break;
		}
		case 8:
		{
			printf("总用时为: %.3f ns\n", sumtime);
			printf("平均用时为: %.3f ns\n", sumtime/(double)opnum);
			break;
		}
		case 9:
		{
			int y;
			cout << "请输入准备查询的数字：";
			cin >> y;
			auto start = high_resolution_clock::now();
			if (list1.search(y)) {
				cout << "查询成功！" << "\n";
			}
			else {
				cout << "查询失败" << "\n";
			}
			auto end = high_resolution_clock::now();
			double time = duration_cast<nanoseconds>(end - start).count();
			printf("跳表用时为: %.3f ns\n", time);
			sumtime += time;
			opnum++;
			
			auto start1 = high_resolution_clock::now();
			if (arr1.serach(y)) {
				cout << "查询成功！" << "\n";
			}
			else {
				cout << "查询失败" << "\n";
			}
			auto end1 = high_resolution_clock::now();
			double time1 = duration_cast<nanoseconds>(end1 - start1).count();
			printf("有序数组的折半查找用时为: %.3f ns(该时间不计入总时间)\n", time1);
			break;
		}
		case 10:
		{
			list1.rebuild();
			sumtime = 0;
			opnum = 0;
			break;
		}
		default:
			break;
		}
	}
}