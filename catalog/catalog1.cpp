#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <queue>
#include <fstream>

using namespace std;

struct TreeNode {
    string name;
    bool isDir;
    TreeNode* parent;
    TreeNode* firstChild;
    TreeNode* nextSibling;

    TreeNode() : name(""), isDir(true), parent(nullptr), firstChild(nullptr), nextSibling(nullptr) {}
};

class CatalogTree {
private:
    TreeNode* root;
    TreeNode* currentDir;

    queue<string> splitPath(const string& path) {
        queue<string> parts;
        bool isAbsolute = !path.empty() && path[0] == '/';
        size_t start = isAbsolute ? 1 : 0;

        string current;
        for (size_t i = start; i < path.size(); ++i) {
            if (path[i] == '/') {
                if (!current.empty()) {
                    parts.push(current);
                    current.clear();
                }
            } else {
                current += path[i];
            }
        }
        if (!current.empty()) {
            parts.push(current);
        }
        if (isAbsolute) {
            queue<string> absParts;
            absParts.push("");
            while (!parts.empty()) {
                absParts.push(parts.front());
                parts.pop();
            }
            return absParts;
        }
        return parts;
    }

    TreeNode* findNodeByPath(queue<string>& parts) {
        TreeNode* current = parts.front() == "" ? root : currentDir;
        if (parts.front() == "") parts.pop();

        while (!parts.empty() && current != nullptr) {
            string part = parts.front();
            parts.pop();
            if (!current->isDir) return nullptr;

            TreeNode* child = current->firstChild;
            while (child != nullptr && child->name != part)
                child = child->nextSibling;

            if (child == nullptr) return nullptr;
            current = child;
        }
        return current;
    }

    void clearTree(TreeNode* node) {
        if (!node) return;
        clearTree(node->firstChild);
        clearTree(node->nextSibling);
        delete node;
    }

    string getAbsolutePath(TreeNode* node) {
        if (node == root) return "/";
        stack<string> pathStack;
        while (node != root) {
            pathStack.push(node->name);
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
    CatalogTree() {
        root = new TreeNode();
        root->name = "";
        root->isDir = true;
        currentDir = root;
    }

    ~CatalogTree() {
        clearTree(root);
    }

    void processDir() {
        if (!currentDir->isDir) {
            cout << "Not a directory" << endl;
            return;
        }

        TreeNode* child = currentDir->firstChild;
        while (child != nullptr) {
            cout << child->name << (child->isDir ? " (dir)" : " (file)") << endl;
            child = child->nextSibling;
        }
    }

    void processCd(const string& path) {
        if (path.empty()) {
            cout << getAbsolutePath(currentDir) << endl;
            return;
        }

        if (path == "..") {
            if (currentDir != root)
                currentDir = currentDir->parent;
            return;
        }

        queue<string> parts = splitPath(path);
        TreeNode* target = findNodeByPath(parts);
        if (target != nullptr && target->isDir)
            currentDir = target;
        else
            cout << "Directory not found" << endl;
    }

    bool mkdir(const string& name) {
        if (!currentDir->isDir) return false;

        TreeNode* child = currentDir->firstChild;
        while (child != nullptr) {
            if (child->name == name) return false;
            child = child->nextSibling;
        }

        TreeNode* newNode = new TreeNode();
        newNode->name = name;
        newNode->isDir = true;
        newNode->parent = currentDir;
        newNode->nextSibling = currentDir->firstChild;
        currentDir->firstChild = newNode;
        return true;
    }

    bool mkfile(const string& name) {
        if (!currentDir->isDir) return false;

        TreeNode* child = currentDir->firstChild;
        while (child != nullptr) {
            if (child->name == name) return false;
            child = child->nextSibling;
        }

        TreeNode* newNode = new TreeNode();
        newNode->name = name;
        newNode->isDir = false;
        newNode->parent = currentDir;
        newNode->nextSibling = currentDir->firstChild;
        currentDir->firstChild = newNode;
        return true;
    }

    bool deleteNode(const string& name) {
        TreeNode* prev = nullptr;
        TreeNode* curr = currentDir->firstChild;

        while (curr != nullptr && curr->name != name) {
            prev = curr;
            curr = curr->nextSibling;
        }

        if (curr == nullptr) return false;

        if (prev == nullptr)
            currentDir->firstChild = curr->nextSibling;
        else
            prev->nextSibling = curr->nextSibling;

        clearTree(curr->firstChild);
        delete curr;
        return true;
    }

    void saveToFile(const string& filename) {
        ofstream file(filename);
        stack<TreeNode*> s;
        s.push(root);

        while (!s.empty()) {
            TreeNode* node = s.top();
            s.pop();

            if (node != root) {
                file << getAbsolutePath(node) << " " << (node->isDir ? "dir" : "file") << endl;
            }

            stack<TreeNode*> temp;
            TreeNode* child = node->firstChild;
            while (child != nullptr) {
                temp.push(child);
                child = child->nextSibling;
            }
            while (!temp.empty()) {
                s.push(temp.top());
                temp.pop();
            }
        }
        file.close();
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        clearTree(root);
        root = new TreeNode();
        root->isDir = true;
        currentDir = root;

        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string path, type;
            iss >> path >> type;

            if (path == "/") continue;

            queue<string> parts = splitPath(path);
            parts.pop(); // Remove root marker

            TreeNode* parent = root;
            while (!parts.empty()) {
                string part = parts.front();
                parts.pop();

                TreeNode* child = parent->firstChild;
                while (child != nullptr && child->name != part)
                    child = child->nextSibling;

                if (child == nullptr) {
                    TreeNode* newNode = new TreeNode();
                    newNode->name = part;
                    newNode->isDir = (parts.empty() ? (type == "dir") : true);
                    newNode->parent = parent;
                    newNode->nextSibling = parent->firstChild;
                    parent->firstChild = newNode;
                    parent = newNode;
                } else {
                    parent = child;
                }
            }
        }
        file.close();
    }
};

queue<string> splitCommand(const string& line) {
    queue<string> tokens;
    istringstream iss(line);
    string token;
    while (iss >> token)
        tokens.push(token);
    return tokens;
}

int main() {
    CatalogTree fs;
    string commandLine;

    while (true) {
        cout << "> ";
        getline(cin, commandLine);
        queue<string> tokens = splitCommand(commandLine);
        if (tokens.empty()) continue;

        string cmd = tokens.front();
        tokens.pop();

        if (cmd == "quit") break;
        else if (cmd == "dir") fs.processDir();
        else if (cmd == "cd") {
            string arg = tokens.empty() ? "" : tokens.front();
            fs.processCd(arg);
        } else if (cmd == "mkdir") {
            if (tokens.empty()) cout << "Missing argument" << endl;
            else fs.mkdir(tokens.front());
        } else if (cmd == "mkfile") {
            if (tokens.empty()) cout << "Missing argument" << endl;
            else fs.mkfile(tokens.front());
        } else if (cmd == "delete") {
            if (tokens.empty()) cout << "Missing argument" << endl;
            else fs.deleteNode(tokens.front());
        } else if (cmd == "save") {
            if (tokens.empty()) cout << "Missing argument" << endl;
            else fs.saveToFile(tokens.front());
        } else if (cmd == "load") {
            if (tokens.empty()) cout << "Missing argument" << endl;
            else fs.loadFromFile(tokens.front());
        } else {
            cout << "Unknown command" << endl;
        }
    }

    return 0;
}