#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<random>
#include <climits>
using namespace std;
random_device rd;
mt19937_64 gen(time(0));

struct player {
    int id;
    int element;
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
    virtual ~losertree() {}
    virtual void initialize(T* theplayer, int number) = 0;
    virtual int getthewinner() const = 0;
    virtual void replay(int theplayer, T newvalue) = 0;
};

template<class T>
class minlosertree : public losertree<T> {
private:
    int* tree;
    int* leave;
    T* players;
    int k;
    int low1;
    int offset;

    void play(int p, int leftchild, int rightchild) {
        tree[p] = loser(leftchild, rightchild);
        leave[p] = winner(leftchild, rightchild);
        while (p % 2 == 1 && p > 1) {
            tree[p / 2] = loser(leave[p - 1], leave[p]);
            leave[p / 2] = winner(leave[p - 1], leave[p]);
            p /= 2;
        }
    }

    int loser(int x, int y) { return players[x] <= players[y] ? y : x; }
    int winner(int x, int y) { return players[x] <= players[y] ? x : y; }

public:
    minlosertree(T* theplayer = NULL, int thenumber = 0) { initialize(theplayer, thenumber); }
    ~minlosertree() { delete[] tree; delete[] leave; }

    void initialize(T* theplayer, int number) {
        k = number;
        delete[] tree; delete[] leave;
        tree = new int[k + 1]; leave = new int[k + 1];
        players = theplayer;

        int s;
        for (s = 1; 2 * s <= k - 1; s += s);
        low1 = 2 * (k - s);
        offset = 2 * s - 1;

        for (int i = 2; i <= low1; i += 2)
            play((offset + i) / 2, i - 1, i);

        if (k % 2) {
            play(k / 2, leave[k - 1], low1 + 1);
            for (int i = low1 + 3; i <= k; i += 2)
                play((i - low1 + k - 1) / 2, i - 1, i);
        } else {
            for (int i = low1 + 2; i <= k; i += 2)
                play((i - low1 + k - 1) / 2, i - 1, i);
        }
        tree[0] = leave[1];
    }

    int getthewinner() const { return tree[0]; }

    void replay(int theplayer, T newvalue) {
        players[theplayer] = newvalue;
        int p, left, right;
        if (theplayer <= low1) {
            p = (offset + theplayer) / 2;
            left = 2 * p - offset;
            right = left + 1;
        } else {
            p = (theplayer - low1 + k - 1) / 2;
            if (2 * p == k - 1) {
                left = leave[2 * p];
                right = theplayer;
            } else {
                left = 2 * p - k + 1 + low1;
                right = left + 1;
            }
        }

        int old = tree[p];
        tree[p] = loser(left, right);
        leave[p] = winner(left, right);
        if (p == (k / 2) && k % 2) {
            p /= 2;
            tree[p] = loser(leave[k - 1], low1 + 1);
            leave[p] = winner(leave[k - 1], low1 + 1);
        }
        for (p /= 2; p >= 1; p /= 2) {
            tree[p] = loser(leave[2 * p], leave[2 * p + 1]);
            leave[p] = winner(leave[2 * p], leave[2 * p + 1]);
        }
        tree[0] = leave[1];
    }
};

int merge_k_runs(const vector<string>& input_files, const string& output_file) {
    int k = input_files.size();
    if (k == 0) return 0;

    vector<ifstream> fins(k);
    vector<int> current_values(k, INT_MAX);
    vector<bool> is_eof(k, false);
    int access_count = 0;

    for (int i = 0; i < k; ++i) {
        fins[i].open(input_files[i]);
        if (fins[i] >> current_values[i]) {
            access_count++;
        } else {
            is_eof[i] = true;
            current_values[i] = INT_MAX;
        }
    }

    int* players = new int[k + 1];
    for (int i = 1; i <= k; ++i)
        players[i] = current_values[i - 1];

    minlosertree<int> tree(players, k);
    ofstream fout(output_file);
    int remaining = k;

    while (remaining > 0) {
        int winner_idx = tree.getthewinner();
        int value = players[winner_idx];
        if (value == INT_MAX) break;

        fout << value << ' ';
        access_count++;

        int stream_idx = winner_idx - 1;
        if (!is_eof[stream_idx]) {
            if (fins[stream_idx] >> current_values[stream_idx]) {
                access_count++;
                players[winner_idx] = current_values[stream_idx];
            } else {
                players[winner_idx] = INT_MAX;
                is_eof[stream_idx] = true;
                remaining--;
            }
        } else {
            players[winner_idx] = INT_MAX;
        }
        tree.replay(winner_idx, players[winner_idx]);
    }

    fout.close();
    delete[] players;
    for (auto& fin : fins) fin.close();
    return access_count;
}

void external_sort() {
    string path, infile, outfile;
    int buffer, numbers, count = 0;

    cout << "输入文件路径（0为默认）: ";
    cin >> path;
    cout << "输入缓冲区大小: ";
    cin >> buffer;
    if (path == "0") path = "";
    infile = path + "input.txt";
    outfile = path + "output.txt";

    ofstream file(infile);
    cout << "随机生成(0)或手动输入(1): ";
    int a; cin >> a;
    cout << "元素个数: ";
    cin >> numbers;
    if (a == 0) {
        for (int i = 0; i < numbers; ++i) {
            int x = gen() % 1000 + 1;
            file << x << ' ';
        }
    } else {
        cout << "输入元素: ";
        for (int i = 0; i < numbers; ++i) {
            int x; cin >> x;
            file << x << ' ';
        }
    }
    file.close();

    ifstream fin(infile);
    player* players = new player[buffer + 1];
    for (int i = 1; i <= buffer && fin >> players[i].element; ++i) {
        players[i].id = 1;
        count++;
    }

    minlosertree<player> tree(players, buffer);
    int m = 0;
    while (fin >> m) {
        player temp;
        temp.element = players[tree.getthewinner()].element;
        temp.id = players[tree.getthewinner()].id;
        player newp;
        newp.element = m;
        newp.id = (m >= temp.element) ? temp.id : temp.id + 1;
        tree.replay(tree.getthewinner(), newp);
        string runfile = path + "test" + to_string(temp.id) + ".txt";
        ofstream fout(runfile, ios::app);
        fout << temp.element << ' ';
        fout.close();
        count++;
    }
    fin.close();

    int max_run = players[tree.getthewinner()].id;
    for (int i = 1; i <= max_run; ++i) {
        string runfile = path + "test" + to_string(i) + ".txt";
        ifstream fin(runfile);
        int x;
        cout << "Run " << i << ": ";
        while (fin >> x) cout << x << ' ';
        cout << endl;
        fin.close();
    }

    int k;
    cout << "输入归并路数k: ";
    cin >> k;

    m = max_run;
    while (m > 1) {
        int groups = (m + k - 1) / k;
        for (int i = 0; i < groups; ++i) {
            int start = i * k + 1;
            int end = min((i + 1) * k, m);
            vector<string> inputs;
            for (int j = start; j <= end; ++j)
                inputs.push_back(path + "test" + to_string(j) + ".txt");
            string output = path + "new_test" + to_string(i + 1) + ".txt";
            count += merge_k_runs(inputs, output);
        }

        for (int j = 1; j <= m; ++j)
            remove((path + "test" + to_string(j) + ".txt").c_str());
        for (int j = 1; j <= groups; ++j)
            rename((path + "new_test" + to_string(j) + ".txt").c_str(), 
                   (path + "test" + to_string(j) + ".txt").c_str());
        m = groups;
    }

    ifstream final_in(path + "test1.txt");
    ofstream final_out(outfile);
    int x;
    while (final_in >> x) {
        final_out << x << ' ';
        count++;
    }
    final_in.close();
    final_out.close();
    remove((path + "test1.txt").c_str());

    cout << "排序结果: ";
    ifstream result(outfile);
    while (result >> x) cout << x << ' ';
    cout << "\n磁盘访问次数: " << count << endl;
}

int main() {
    external_sort();
    return 0;
}