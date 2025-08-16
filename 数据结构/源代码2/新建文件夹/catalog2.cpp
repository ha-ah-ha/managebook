#include<iostream>
#include<string>
#include<sstream>
#include<stack>
#include<queue>
#include<fstream>
using namespace std;
typedef long long ll;
//文件系统节点结构体
struct node
{
    node* parent;//父节点指针（指向上一级目录）
    node* leftchild;//左孩子（指向第一个子节点）
    node* brother;//兄弟节点指针9指向同级的下一个节点）
    int filetype;//1是目录，0是文件
    string filename;//目录/文件名
    node(node* p=NULL,node* left=NULL,node* bro=NULL,int type=1,string name=""):
        parent(p),leftchild(left),brother(bro),filetype(type),filename(name){}
};

class catalogtree{//CatalogTree
private:
    node* root;//根节点
    node* cur;//当前目录项指针
    string getAbsolutePath(node* node) {//得到node的绝对路径
        if (node == root) return "/";
        stack<string> pathStack;
        while (node != root) {
            pathStack.push(node->filename);
            node = node->parent;
        }

        string path;
        while (!pathStack.empty()) {
            path += "/" + pathStack.top();
            pathStack.pop();
        }
        return path.empty() ? "/" : path;
    }
public:
    catalogtree(){
        root=new node();//初始化根节点
        root->filename="";//名为空
        root->filetype=1;
        cur=root;//当前目录指针指向根节点
    }
    void cleartree(node* node1){
        if(!node1)
            return;
        cleartree(node1->leftchild);//递归删除左子树
        cleartree(node1->brother);//递归删除兄弟子树
        delete node1;//释放当前节点
    }
    ~catalogtree(){
        cleartree(root);//释放整个目录树的内容
    }
    queue<string> splitpath(const string& path){
        queue<string> parts;
        bool isabsolute=false;
        if(!path.empty()&&path[0]=='/'){//判断是否为绝对路径
            isabsolute=true;
        }
        int i=0;
        if(path[0]=='/'){
            i=1;//跳过绝对路径开头的“/”
        }
        string current;
        for(i;i<path.size();i++){//遍历path，按照“/”分割
            if(path[i]=='/'){
                if(!current.empty()){
                    parts.push(current);
                    current="";
                }
            }
            else{
                current+=path[i];
            }
        }
        if(!current.empty()){//将最后一个没有压入的current压入
            parts.push(current);
        }
        if(isabsolute==1){//如果为绝对路径
            queue<string> absparts;
            absparts.push("");//在开头压入一个空字符串，标记其为绝对路径
            while(!parts.empty()){
                absparts.push(parts.front());
                parts.pop();
            }
            return absparts;
        }
        return parts;//不是绝对路径则直接返回
    }
    node* findpath(queue<string>& parts);//根据路径队列确定目标节点的位置
    void dir();//列出当前目录下的所有子项
    void cd(const string& path);//实现功能2-4
    bool mkdir(const string& name);//创建目录
    bool mkfile(const string& name);//创建文件
    bool delete1(const string& name);//删除指定目录/文件
    void saveToFile(const string& filename);//保存到文件中
    void loadFromFile(const string& filename);//从文件中读取目录结构
    string getcurrentpath(){//用于系统的模拟显示
        return getAbsolutePath(cur);
    }
};

node* catalogtree::findpath(queue<string>& parts){
    node* cur1;
    if(parts.front()==""){//是绝对路径，从根节点开始
        cur1=root;
        parts.pop();
    }
    else{//相对路径从当前节点开始
        cur1=cur;
    }
    while(!parts.empty()&&cur1!=nullptr){//开始遍历找寻
        string part=parts.front();
        parts.pop();
        if(cur1->filetype==0){//是文件，返回
            return nullptr;
        }
        node* child=cur1->leftchild;//指向左孩子
        while(child!=nullptr&&child->filename!=part)//遍历所有孩子，直到找到对用的孩子
            child=child->brother;
        if(child==nullptr) return nullptr;//没有找到匹配项
        cur1=child;//指向该孩子，继续向下找，直到队列为空
    }
    return cur1;//返回节点
}

void catalogtree::dir(){
    if(cur->filetype==0){//当前节点是文件
        cout<<"不是一个文件夹"<<endl;
        return;
    }
    node* child=cur->leftchild;
    while(child!=nullptr){//遍历所有孩子节点
        cout << child->filename << (child->filetype ? " (dir)" : " (file)") << endl; // 显示所有子节点以及类别
        child=child->brother;
    }
}

void catalogtree::cd(const string& path){
    if(path.empty()){//输出当前的绝对路径
        if(cur==root){
            cout<<"/";
        }
        else{
            node* cur1=cur;
            stack<string> path1;
            while(cur1!=root){
                path1.push(cur1->filename);
                cur1=cur1->parent;
            }
            cout<<'/';
            while(!path1.empty()){
                cout<<path1.top()<<"/";
                path1.pop();
            }
        }
        cout<<endl;
        return;
    }
    else if(path==".."){//更新cur指向cur的父节点
        if(cur!=root){
            cur=cur->parent;
        }
        return;
    }
    else{
        queue<string> parts=splitpath(path);//解析路径
        node* target=findpath(parts);//找到将要切换的位置
        if(target!=nullptr&&target->filetype==1){
            cur=target;//指向该位置
        }
        else{
            cout<<"没有该文件"<<endl;
        }
    }
}

bool catalogtree::mkdir(const string& path){
    queue<string> parts1=splitpath(path);//分析路径
    queue<string> parts;
    while(parts1.size()>1){//如果是绝对路径，那么长度一定大于2
        //将除了将要创建目录项的名称之外的所有节点名再放入parts中
        parts.push(parts1.front());
        parts1.pop();
    }
    string name=parts1.front();//将要创建的目录名
    //parts.push(parts1.front());
    node* target;
    if(parts.empty()){//如果是相对路径
        target=cur;//从当前的节点开始
    }
    else{
        target=findpath(parts);//找到相对路径中的位置
    }
    //排除错误情况
    if(!target){
        cout<<"该路径不存在"<<endl;
    }
    if(target->filetype==0){
        cout<<"应在目录下创建目录"<<endl;
        return false;
    }
    node* child=target->leftchild;//遍历孩子，避免出现重名
    while(child!=nullptr){
        if(child->filename==name){
            cout<<"存在重名"<<endl;
            return false;
        }
        child=child->brother;
    }
    // 创建新节点并更新链表
    node* newnode=new node(target, nullptr, target->leftchild, 1, name);
    target->leftchild = newnode;
    return true;
}

bool catalogtree::mkfile(const string& path){//与mkdir基本一致
    queue<string> parts1=splitpath(path);
    queue<string> parts;
    while(parts1.size()>1){
        parts.push(parts1.front());
        parts1.pop();
    }
    string name=parts1.front();
    //parts.push(parts1.front());
    node* target;
    if(parts.empty()){
        target=cur;
    }
    else{
        target=findpath(parts);
    }
    if(!target){
        cout<<"该路径不存在"<<endl;
    }
    if(target->filetype==0){
        cout<<"应在目录下创建文件"<<endl;
        return false;
    }
    node* child=target->leftchild;
    while(child!=nullptr){
        if(child->filename==name){
            cout<<"存在重名"<<endl;
            return false;
        }
        child=child->brother;
    }
    node* newnode =new node(target,nullptr,target->leftchild,0,name);
    target->leftchild=newnode;
    return true;
}

bool catalogtree::delete1(const string& path){
    queue<string> parts1=splitpath(path);
    queue<string> parts;
    while(parts1.size()>1){
        parts.push(parts1.front());
        parts1.pop();
    }
    string name=parts1.front();
    //parts.push(parts1.front());
    node* target;
    if(parts.empty()){
        target=cur;
    }
    else{
        target=findpath(parts);
    }
    if(!target){
        cout<<"该路径不存在"<<endl;
    }
    if(target->filetype==0){
        cout<<"应在目录下删除"<<endl;
        return false;
    }//同样是找到对应的目录位置
    node* prev=nullptr;
    node* child=target->leftchild;
    while(child!=nullptr&&child->filename!=name){//找到将要删除的节点的位置
        prev=child;//指向将要删除节点的前一个节点
        child=child->brother;
    }
    if(child==nullptr) 
    {
        cout<<"不存在该文件或者目录"<<endl;
        return false;
    }
    if(prev==nullptr){//即将要删除的节点位置恰好为父节点的第一个子节点
        target->leftchild=child->brother;
    }
    else{
        prev->brother=child->brother;
    }
    cleartree(child->leftchild);//删除对应的子树
    delete child;
    return true;
}

void catalogtree::saveToFile(const string& filename) {
    ofstream file(filename);
    stack<node*> s;
    s.push(root);

    while (!s.empty()) {
        node* node1 = s.top();
        s.pop();
        
        // 跳过根节点，写入其他节点的绝对路径和类型
        if (node1 != root) {
            file << getAbsolutePath(node1) << " " << (node1->filetype ? "dir" : "file") << endl;
        }
        // 将子节点逆序压入栈（保证加载顺序正确）
        stack<node*> temp;
        node* child = node1->leftchild;
        while (child != nullptr) {
            temp.push(child);
            child = child->brother;
        }
        while (!temp.empty()) {
            s.push(temp.top());
            temp.pop();
        }
    }
    file.close();
}


void catalogtree::loadFromFile(const string& filename) {
    ifstream file(filename);
    cleartree(root);//清空现有目录树
    root = new node();//重建根节点
    root->filetype = true;
    cur = root;

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string path, type;
        iss >> path >> type;

        if (path == "/") continue;//跳过根节点
        if(type=="dir"){mkdir(path);}//直接调用mkdir/mkfile重建目录结构
        if(type=="file"){mkfile(path);}
    }
    file.close();
}
//拆分命令行输入为令牌队列
queue<string> splitCommand(const string& line) {
    queue<string> tokens;
    istringstream iss(line);
    string token;
    while (iss >> token)
        tokens.push(token);
    return tokens;
}

int main() {
    catalogtree fs;
    string commandLine;

    while (true) {
        cout <<fs.getcurrentpath()<<"> ";//显示当前路径以及提示符
        getline(cin, commandLine);
        queue<string> tokens = splitCommand(commandLine);
        if (tokens.empty()) continue;

        string cmd = tokens.front();//命令
        tokens.pop();

        if (cmd == "quit") break;
        else if (cmd == "dir") fs.dir();
        else if (cmd == "cd") {
            string arg = tokens.empty() ? "" : tokens.front();
            fs.cd(arg);
        } else if (cmd == "mkdir") {
            if (tokens.empty()) cout << "Missing argument" << endl;
            else fs.mkdir(tokens.front());
        } else if (cmd == "mkfile") {
            if (tokens.empty()) cout << "Missing argument" << endl;
            else fs.mkfile(tokens.front());
        } else if (cmd == "delete") {
            if (tokens.empty()) cout << "Missing argument" << endl;
            else fs.delete1(tokens.front());
        } else if (cmd == "save") {
            if (tokens.empty()) cout << "Missing argument" << endl;
            else fs.saveToFile(tokens.front());
        } else if (cmd == "load") {
            if (tokens.empty()) cout << "Missing argument" << endl;
            else fs.loadFromFile(tokens.front());
        }else {
            cout << "Unknown command" << endl;
        }
    }
    return 0;
}