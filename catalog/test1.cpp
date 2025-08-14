#include<iostream>
#include<string>
#include<sstream>
#include<queue>
#include<stack>
#include<fstream>
using namespace std;
struct node
{
    node* parent;
    node* leftchild;
    node* brother;
    int filetype;//1是目录，0是文件
    string filename;
    
    node(node* p=NULL,node* left=NULL,node* bro=NULL,int type=1,string name=""):
        parent(p),leftchild(left),brother(bro),filetype(type),filename(name){}
};

class catalogtree{
private:
    node* root;
    node* cur;
    string getAbsolutePath(node* node) {
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
        root=new node();
        root->filename="";
        root->filetype=1;
        cur=root;
    }
    void cleartree(node* node1){
        if(!node1)
            return;
        cleartree(node1->leftchild);
        cleartree(node1->brother);
        delete node1;
    }
    ~catalogtree(){
        cleartree(root);
    }
    queue<string> splitpath(const string& path){
        queue<string> parts;
        bool isabsolute=false;
        if(!path.empty()&&path[0]=='/'){
            isabsolute=true;
        }
        int i=0;
        if(path[0]=='/'){
            i=1;
        }
        string current;
        for(i;i<path.size();i++){
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
        if(!current.empty()){
            parts.push(current);
        }
        if(isabsolute==1){
            queue<string> absparts;
            absparts.push("");
            while(!parts.empty()){
                absparts.push(parts.front());
                parts.pop();
            }
            return absparts;
        }
        return parts;
    }
    node* findpath(queue<string>& parts);
    void dir();
    void cd(const string& path);
    bool mkdir(const string& name);
    bool mkfile(const string& name);
    bool delete1(const string& name);
    void saveToFile(const string& filename);
    void loadFromFile(const string& filename);
    string getcurrentpath(){
        return getAbsolutePath(cur);
    }
};

node* catalogtree::findpath(queue<string>& parts){
    node* cur1;
    if(parts.front()==""){
        cur1=root;
        parts.pop();
    }
    else{
        cur1=cur;
    }
    while(!parts.empty()&&cur1!=nullptr){
        string part=parts.front();
        parts.pop();
        if(cur1->filetype==0){
            return nullptr;
        }
        node* child=cur1->leftchild;
        while(child!=nullptr&&child->filename!=part)
            child=child->brother;
        if(child==nullptr) return nullptr;
        cur1=child;
    }
    return cur1;
}

void catalogtree::dir(){
    if(cur->filetype==0){
        cout<<"不是一个文件夹"<<endl;
        return;
    }
    node* child=cur->leftchild;
    while(child!=nullptr){
        cout << child->filename 
             << (child->filetype ? " (dir)" : " (file)") << endl; // 显示所有子节点
        child=child->brother;
    }
}

void catalogtree::cd(const string& path){
    if(path.empty()){
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
    else if(path==".."){
        if(cur!=root){
            cur=cur->parent;
        }
        return;
    }
    else{
        queue<string> parts=splitpath(path);
        node* target=findpath(parts);
        if(target!=nullptr&&target->filetype==1){
            cur=target;
        }
        else{
            cout<<"没有该文件"<<endl;
        }
    }
}

bool catalogtree::mkdir(const string& name) {
    queue<string> path_parts = splitpath(name);
    if (path_parts.empty()) return false;

    node* parent = nullptr;
    string new_dir_name;

    // 最后一部分是要创建的目录名
    while (path_parts.size() > 1) {
        string part = path_parts.front();
        path_parts.pop();
        if (parent == nullptr) {
            if (part == "") parent = root;
            else parent = cur;
        }

        node* child = parent->leftchild;
        while (child && child->filename != part)
            child = child->brother;

        if (!child || child->filetype == 0) {
            cout << "路径不存在或不是一个目录" << endl;
            return false;
        }
        parent = child;
    }

    // 最后一部分是要新建的目录名
    new_dir_name = path_parts.front();

    if (!parent) parent = cur;

    // 检查是否重名
    node* child = parent->leftchild;
    while (child) {
        if (child->filename == new_dir_name) {
            cout << "存在重名" << endl;
            return false;
        }
        child = child->brother;
    }

    node* newnode = new node(parent, nullptr, parent->leftchild, 1, new_dir_name);
    parent->leftchild = newnode;
    return true;
}

bool catalogtree::mkfile(const string& name) {
    queue<string> path_parts = splitpath(name);
    if (path_parts.empty()) return false;

    node* parent = nullptr;
    string new_file_name;

    // 最后一部分是要创建的文件名
    while (path_parts.size() > 1) {
        string part = path_parts.front();
        path_parts.pop();

        if (parent == nullptr) {
            if (part == "") parent = root;
            else parent = cur;
        }

        node* child = parent->leftchild;
        while (child && child->filename != part)
            child = child->brother;

        if (!child || child->filetype == 0) {
            cout << "路径不存在或不是一个目录" << endl;
            return false;
        }
        parent = child;
    }

    new_file_name = path_parts.front();
    if (!parent) parent = cur;

    // 检查是否重名
    node* child = parent->leftchild;
    while (child) {
        if (child->filename == new_file_name) {
            cout << "存在重名" << endl;
            return false;
        }
        child = child->brother;
    }

    node* newnode = new node(parent, nullptr, parent->leftchild, 0, new_file_name);
    parent->leftchild = newnode;
    return true;
}

bool catalogtree::delete1(const string& name) {
    // queue<string> parts = splitpath(name);
    // if (parts.empty()) return false;
    // string targetname = parts.back();  // 要删除的文件/目录名
    // parts.pop();  // 剩下的是路径部分（父目录）
    // node* parent = findpath(parts);
    // if (!parent || parent->filetype == 0) {
    //     cout << "路径不存在或不是一个目录" << endl;
    //     return false;
    // }

    // node* prev = nullptr;
    // node* child = parent->leftchild;

    // while (child != nullptr && child->filename != targetname) {
    //     prev = child;
    //     child = child->brother;
    // }

    // if (!child) {
    //     cout << "不存在该文件或者目录" << endl;
    //     return false;
    // }

    // // 删除目标
    // if (prev == nullptr) {
    //     parent->leftchild = child->brother;
    // } else {
    //     prev->brother = child->brother;
    // }
    // cleartree(child->leftchild);
    // delete child;
    // return true;
    
    queue<string> parts1=splitpath(name);
    queue<string> parts;
    while(parts1.size()>1){
        parts.push(parts1.front());
        parts1.pop();
    }
    string name1=
    node* target=findpath(parts)
}

void catalogtree::saveToFile(const string& filename) {
    ofstream file(filename);
    stack<node*> s;
    s.push(root);

    while (!s.empty()) {
        node* node1 = s.top();
        s.pop();

        if (node1 != root) {
            file << getAbsolutePath(node1) << " " << (node1->filetype ? "dir" : "file") << endl;
        }
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
    cleartree(root);
    root = new node();
    root->filetype = true;
    cur = root;

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string path, type;
        iss >> path >> type;

        if (path == "/") continue;

        queue<string> parts = splitpath(path);
        parts.pop();

        node* parent = root;
        while (!parts.empty()) {
            string part = parts.front();
            parts.pop();

            node* child = parent->leftchild;
            while (child != nullptr && child->filename != part)
                child = child->brother;

            if (child == nullptr) {
                node* newNode = new node();
                newNode->filename = part;
                newNode->filetype = (parts.empty() ? (type == "dir") : true);
                newNode->parent = parent;
                newNode->brother = parent->leftchild;
                parent->leftchild = newNode;
                parent = newNode;
            } else {
                parent = child;
            }
        }
    }
    file.close();
}

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
        cout <<fs.getcurrentpath()<<"> ";
        getline(cin, commandLine);
        queue<string> tokens = splitCommand(commandLine);
        if (tokens.empty()) continue;

        string cmd = tokens.front();
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