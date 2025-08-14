#include <cstdio>
#include <cstring>

#define MAX_NAME_LEN 64
#define MAX_PATH_DEPTH 10

struct Node {
    char name[MAX_NAME_LEN];
    bool is_dir;
    Node* parent;
    Node* first_child;
    Node* next_sibling;

    Node(const char* name, bool is_dir, Node* parent) 
        : is_dir(is_dir), parent(parent), first_child(nullptr), next_sibling(nullptr) {
        strncpy(this->name, name, MAX_NAME_LEN);
    }
};

class FileSystem {
private:
    Node* root;
    Node* current;

    Node* find_node(Node* parent, const char* name) {
        for (Node* p = parent->first_child; p; p = p->next_sibling) {
            if (strcmp(p->name, name) == 0) return p;
        }
        return nullptr;
    }

    void delete_tree(Node* node) {
        if (!node) return;
        delete_tree(node->first_child);
        delete_tree(node->next_sibling);
        delete node;
    }

public:
    FileSystem() {
        root = new Node("", true, nullptr);
        current = root;
    }

    ~FileSystem() {
        delete_tree(root);
    }

    bool mkdir(const char* name) {
        return add_node(name, true);
    }

    bool mkfile(const char* name) {
        return add_node(name, false);
    }

    bool add_node(const char* name, bool is_dir) {
        if (!current->is_dir) return false;
        if (find_node(current, name)) return false;

        Node* new_node = new Node(name, is_dir, current);
        if (!current->first_child) {
            current->first_child = new_node;
        } else {
            Node* p = current->first_child;
            while (p->next_sibling) p = p->next_sibling;
            p->next_sibling = new_node;
        }
        return true;
    }

    bool delete_node(const char* name) {
        Node *prev = nullptr, *curr = current->first_child;
        while (curr && strcmp(curr->name, name)) {
            prev = curr;
            curr = curr->next_sibling;
        }
        if (!curr) return false;

        if (prev) prev->next_sibling = curr->next_sibling;
        else current->first_child = curr->next_sibling;

        delete_tree(curr->first_child);
        delete curr;
        return true;
    }

    bool cd(const char* path) {
        if (strcmp(path, "..") == 0) {
            if (current != root) current = current->parent;
            return true;
        }

        Node* target = find_node(current, path);
        if (target && target->is_dir) {
            current = target;
            return true;
        }
        return false;
    }

    void dir() const {
        for (Node* p = current->first_child; p; p = p->next_sibling) {
            printf("%s%s\n", p->name, p->is_dir ? "/" : "");
        }
    }

    void pwd() const {
        char path[1024] = "";
        Node* p = current;
        while (p != root) {
            char temp[1024];
            sprintf(temp, "/%s%s", p->name, path);
            strcpy(path, temp);
            p = p->parent;
        }
        printf("%s\n", path[0] ? path : "/");
    }
};

int main() {
    FileSystem fs;
    char cmd[16], arg[MAX_NAME_LEN];

    while (true) {
        printf("> ");
        if (scanf("%15s", cmd) == EOF) break;

        if (strcmp(cmd, "exit") == 0) break;
        else if (strcmp(cmd, "dir") == 0) fs.dir();
        else if (strcmp(cmd, "cd") == 0) {
            scanf("%63s", arg);
            if (!fs.cd(arg)) printf("Path error\n");
        }
        else if (strcmp(cmd, "mkdir") == 0) {
            scanf("%63s", arg);
            if (!fs.mkdir(arg)) printf("Create failed\n");
        }
        else if (strcmp(cmd, "mkfile") == 0) {
            scanf("%63s", arg);
            if (!fs.mkfile(arg)) printf("Create failed\n");
        }
        else if (strcmp(cmd, "delete") == 0) {
            scanf("%63s", arg);
            if (!fs.delete_node(arg)) printf("Delete failed\n");
        }
        else if (strcmp(cmd, "pwd") == 0) fs.pwd();
        else printf("Unknown command\n");
    }

    return 0;
}