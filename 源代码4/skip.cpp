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
			}//ð������  O(n^2)
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
		}//ð������ O(n^2)
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
			cout << "Ԫ�ز�����" << endl;
			return;
		}

		// ����������
		int* newArr = new int[n - 1];
		for (int i = 0; i < pos; ++i)
			newArr[i] = a[i];
		for (int i = pos; i < n - 1; ++i)
			newArr[i] = a[i + 1];

		// ��������
		delete[] a;
		a = newArr;
		--n;//O(n)

		//auto end = high_resolution_clock::now();
		//double time = duration_cast<nanoseconds>(end - start).count();
		//printf("ɾ��������ʱ: %.3f ns\n", time);
	}

	// ɾ����СԪ��
	void erasemin() {
		if (n == 0) {
			cout << "����Ϊ��" << endl;
			return;
		}

		// ֱ��ɾ����һ��Ԫ��
		int* newArr = new int[n - 1];
		for (int i = 0; i < n - 1; ++i)
			newArr[i] = a[i + 1];

		delete[] a;
		a = newArr;
		--n;//O(n)
		//cout << "��ɾ����СԪ��" << endl;
	}

	// ɾ�����Ԫ��
	void erasemax() {
		if (n == 0) {
			cout << "����Ϊ��" << endl;
			return;
		}

		// ֱ��ɾ�����һ��Ԫ��
		int* newArr = new int[n - 1];
		for (int i = 0; i < n - 1; ++i)
			newArr[i] = a[i];

		delete[] a;
		a = newArr;
		--n;
		cout << "��ɾ�����Ԫ��" << endl;//O(1)
	}

	
	/*void display() {
		cout << "��ǰ����[ ";
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
			head = new node(nullptr, below, -1); // �������ͷ�ڵ�
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
			insertup = false;//ֹͣ���ϼ�����һ��
		}
	}
	if (insertup) {
		head = new node(new node(NULL, newp, NULL), head, -1);
	}//O(log n)
}

void skiplist::erase(int target) {
	node* p = head;
	bool found = false;
	while (p) {//������������
		while (p->next && p->next->val < target) {
			p = p->next;
		}
		if (!p->next || p->next->val > target) {
			p = p->down;
		}
		else {//�ҵ����ֵ���ڵ�λ��
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
	head = below; // ��߲�ͷ�ڵ�
	for (int i = 0; i < size; i++) {
		insert(x[i]); // ���� insert ������֤�������
	}//O(n log n)
}

void skiplist::erasemin() {
	/*if (head->down == NULL) {
		cout << "����Ϊ��,�޷�ɾ��" << endl;
		return;
	}*/
	node* p = head;
	while (p->down) {
		p = p->down;
	}
	if (!p->next) {
		cout << "����Ϊ��,�޷�ɾ��!" << endl;
		return;
	}
	int minval = p->next->val;//�ҵ�ֵ��С��Ԫ��
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
	cout << "�ɹ�ɾ���ؼ�����С��Ԫ��:" << minval << endl;
}

void skiplist::erasemax() {
	node* p = head;
	while (p->down) {
		p = p->down;
	}
	if (p->next==NULL) {
		cout << "����Ϊ��" << endl;
	}
	while (p->next) {
		p = p->next;
	}
	int maxval = p->val;
	erase(maxval);
	cout << "�ɹ�ɾ���ؼ�������Ԫ��:" << maxval << endl;
	//O(log n)
}

void skiplist::print() {
	node* layer = head;
	int level = maxlevel;
	while (layer) {
		if(layer->next)
		{
			cout << "Lv" << level << ":\t";
			node* curr = layer->next; // ����ͷ�ڵ�
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

	// �ռ�Ԫ�أ�����
	node* p = head;
	while (p->down)
		p = p->down;
	p = p->next;
	if (p == NULL) {
		cout << "����Ϊ��" << endl;
		return;
	}
	while (p) {
		elements.push(p->val);
		p = p->next;
	}

	stack<int> temp;// �ؽ�����
	while (!elements.empty()) {
		temp.push(elements.top());
		elements.pop();
	}
	// ���������
	initialize(nullptr, 0);

	// ����������
	while (!temp.empty()) {
		insert(temp.top());
		temp.pop();
	}
	cout << "�����ؽ���ɣ��㼶���Ż�" << endl;
}

int randint(int l, int r) {
	return gen() % (r - l + 1) + l;//����l��r֮����������
}

int main() {
	cout << "****************************" << "\n";
	cout << "***** �����ʵ������� *****" << "\n";
	cout << "****************************" << "\n";
	skiplist list1;
	erfen arr1;
	while (true) {
		int x;
		cout << "*������ָ��" << "\n" << "0->�˳�" << "\n";
		cout << "1->��ʼ��" << "\n";
		cout << "2->����Ԫ��" << "\n";
		cout << "3->��ѯ" << "\n";
		cout << "4->ɾ��" << "\n";
		cout << "5->ɾ���ؼ�����С��Ԫ��" << "\n";
		cout << "6->ɾ���ؼ�������Ԫ��" << "\n";
		cout << "7->�������ṹ" << "\n";
		cout << "8->����ʱ�Լ�ƽ����ʱ" << "\n";
		cout << "9->������������۰������Ա�" << "\n";
		cout << "10->�ؽ�����" << "\n";
		cin >> x;
		switch (x)
		{
		case 0:
		{
			cout << "��������";
			return 0;
		}
		case 1:
		{
			int y;
			cout << "��ѡ��0->�������n�����ֳ�ʼ��" << "\n";
			cout << "        1->�������ֳ�ʼ��" << "\n";
			cin >> y;
			switch (y)
			{
			case 0:
			{
				cout << "������n��";
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
				printf("��ʱΪ: %.3f ns\n", time);
				cout << "������ϣ�"<<"\n";
				sumtime += time;
				opnum++;
				arr1.intialize(a,n);
				break;
			}
			case 1: 
			{
				
				int z;
				cout << "�������������ֵĸ�����";
				cin >> z;
				int* a = new int[z];
				cout << "����������Ҫ�������������(�Կո���)��";
				for (int i = 0; i < z; i++) {
					cin >> a[i];
				}
				auto start = high_resolution_clock::now();
				list1.initialize(a, z);
				auto end = high_resolution_clock::now();
				double time = duration_cast<nanoseconds>(end - start).count();
				printf("��ʱΪ: %.3f ns\n", time);
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
			cout << "������׼�������Ԫ�أ�";
			int y;
			cin >> y;
			auto start = high_resolution_clock::now();
			list1.insert(y);
			auto end = high_resolution_clock::now();
			double time = duration_cast<nanoseconds>(end - start).count();
			cout << "����ɹ�" << "\n";
			printf("��ʱΪ: %.3f ns\n", time);
			sumtime += time;
			opnum++;
			arr1.insert(y);
			break;
		}
		case 3:
		{
			int y;
			cout << "������׼����ѯ�����֣�";
			cin >> y;
			auto start = high_resolution_clock::now();
			if (list1.search(y)) {
				cout << "��ѯ�ɹ���" << "\n";
			}
			else {
				cout << "��ѯʧ��" << "\n";
			}
			auto end = high_resolution_clock::now();
			double time = duration_cast<nanoseconds>(end - start).count();
			printf("��ʱΪ: %.3f ns\n", time);
			sumtime += time;
			opnum++;
			break;
		}
		case 4:
		{
			int y;
			cout << "������׼��ɾ�������֣�";
			cin >> y;
			auto start = high_resolution_clock::now();
			list1.erase(y);
			auto end = high_resolution_clock::now();
			double time = duration_cast<nanoseconds>(end - start).count();
			printf("��ʱΪ: %.3f ns\n", time);
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
			printf("��ʱΪ: %.3f ns\n", time);
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
			printf("��ʱΪ: %.3f ns\n", time);
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
			printf("��ʱΪ: %.3f ns(��ʱ�䲻������ʱ��)\n ", time);
			break;
		}
		case 8:
		{
			printf("����ʱΪ: %.3f ns\n", sumtime);
			printf("ƽ����ʱΪ: %.3f ns\n", sumtime/(double)opnum);
			break;
		}
		case 9:
		{
			int y;
			cout << "������׼����ѯ�����֣�";
			cin >> y;
			auto start = high_resolution_clock::now();
			if (list1.search(y)) {
				cout << "��ѯ�ɹ���" << "\n";
			}
			else {
				cout << "��ѯʧ��" << "\n";
			}
			auto end = high_resolution_clock::now();
			double time = duration_cast<nanoseconds>(end - start).count();
			printf("������ʱΪ: %.3f ns\n", time);
			sumtime += time;
			opnum++;
			
			auto start1 = high_resolution_clock::now();
			if (arr1.serach(y)) {
				cout << "��ѯ�ɹ���" << "\n";
			}
			else {
				cout << "��ѯʧ��" << "\n";
			}
			auto end1 = high_resolution_clock::now();
			double time1 = duration_cast<nanoseconds>(end1 - start1).count();
			printf("����������۰������ʱΪ: %.3f ns(��ʱ�䲻������ʱ��)\n", time1);
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