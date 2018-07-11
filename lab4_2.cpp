//
// Created by LooperXX on 2018/7/7.
//
#include <bits/stdc++.h>
using namespace std;

template<class T>
class TreeNode {
public:
    // 左子右兄弟
    TreeNode *parent;
    TreeNode *firstChild;
    TreeNode *nextSibling;
    T value;

    explicit TreeNode(T value) :
            firstChild(nullptr), nextSibling(nullptr), parent(nullptr), value(value) {}

    string getPath() {
        string path;
        stack<TreeNode *> stack;
        TreeNode *cur = this;
        stack.push(cur);
        while (cur->parent != nullptr) {
            stack.push(cur->parent);
            cur = cur->parent;
        }
        while (!stack.empty()) {
            TreeNode *top = stack.top();
            path += top->value.to_string() + "\\";
            stack.pop();
        }
        return path;
    }

    void insert(TreeNode *child) {
        TreeNode *cur = this->firstChild;
        if (cur == nullptr)
            this->firstChild = child;
        else {
            while (cur->nextSibling != nullptr) {
                cur = cur->nextSibling;
            }
            cur->nextSibling = child;
        }
        child->parent = this;
    }

    void Delete() {
        if (this->firstChild != nullptr) // 删除其子节点以及子节点下的的所有节点
            this->firstChild->Delete();
        TreeNode *cur = this->parent;
        if (cur != nullptr)
            cur = cur->firstChild;
        TreeNode *pre = cur;
        if (pre == this)// this为其父节点的首个子节点 则把兄弟节点(nullptr也不影响)重置为其父节点的第一个子节点
            this->parent->firstChild = this->nextSibling;
        else {
            cur = cur->nextSibling;
            while (cur->nextSibling != nullptr) {
                if (cur == this) {
                    pre->nextSibling = cur->nextSibling;
                    break;
                }
                pre = pre->nextSibling;
                cur = cur->nextSibling;
            }
        }
        delete this;
    }
};

class File{
public:
    string name;
    bool dir;

    string to_string() {
        return name;
    }

    File(string name, bool dir) : name(name), dir(dir) {}

    ~File() = default;
};

void showMenuHead(){
    cout << "+-------------------------------------+" << endl;
    cout << "|              文件系统                |" << endl;
    cout << "+-------------------------------------+" << endl;
}

void showMenu(){
    cout << "| 1.新建文件或目录                     |" << endl;
    cout << "| 2.删除文件或目录                     |" << endl;
    cout << "| 3.打开目录                           |" << endl;
    cout << "| 4.返回上一级                         |" << endl;
    cout << "| 0.退出系统                           |" << endl;
    cout << "+-------------------------------------+" << endl;
}

void printPath(TreeNode<File> *curDir) {
    if (curDir->value.dir)
        cout << "| 当前路径: " << curDir->getPath() << "\t\t|" << endl;
    cout << "+-------------------------------------+" << endl;
}

void listFiles(TreeNode<File> *curDir) {
    cout << "| 文件列表: " << endl;
    bool empty = true;
    TreeNode<File> *cur = curDir->firstChild;
    while (cur != nullptr) {
        empty = false;
        cout << "| 文件名: " << cur->value.name << "\t文件类型: " << ((cur->value.dir) ? "目录" : "文件") << " |" << endl;
        cur = cur->nextSibling;
    }
    if (empty)
        cout << "| 暂无文件" << endl;
    cout << "+-------------------------------------+" << endl;
}


int main(){
    TreeNode<File> root(File("root", true));
    TreeNode<File> *curDir = &root;
    TreeNode<File> *initFile_1 = new TreeNode<File>(File("initFile_1", false));
    curDir->insert(initFile_1);
    TreeNode<File> *initFile_2 = new TreeNode<File>(File("initFile_2", false));
    curDir->insert(initFile_2);
    TreeNode<File> *initFolder_1 = new TreeNode<File>(File("initFolder_1", true));
    curDir->insert(initFolder_1);
    TreeNode<File> *initFolder_2 = new TreeNode<File>(File("initFolder_2", true));
    curDir->insert(initFolder_2);
    while(true){
        showMenuHead();
        printPath(curDir);
        listFiles(curDir);
        showMenu();
        int op = 0;
        bool flag = false;
        cin >> op;
        switch (op){
            case 0:
                flag = true;
                break;
            case 1:
                {
                    string nameCre;
                    int dir = 0;
                    cout << "[Input]请输入新建文件(夹)名称及类型,0表示文件,1表示文件夹：" << endl;
                    cout << "       样例如下：" << endl;
                    cout << "       新文件夹 1" << endl;
                    cin >> nameCre >> dir;
                    bool dir_ = (dir == 1);
                    TreeNode<File> *curCre = curDir->firstChild;
                    bool vertify = true;
                    while (curCre != nullptr) {
                        if (curCre->value.name == nameCre) {
                            cout << "[Wrong]您输入的文件(夹)名在当前目录已存在:<" << endl;
                            vertify = false;
                            break;
                        }
                        curCre = curCre->nextSibling;
                    }
                    if (vertify) {
                        TreeNode<File> *newFile = new TreeNode<File>(File(nameCre, dir_));
                        curDir->insert(newFile);
                        cout << "[Success]您已成功新建文件: " << nameCre << ":>" << endl;
                    }
                    break;
                }
            case 2:
                {
                    string nameDel;
                    bool sucDel = false;
                    cout << "[Input]请输入删除的文件(夹)名: " << endl;
                    cin >> nameDel;
                    TreeNode<File> *curDel = curDir->firstChild;
                    while (curDel != nullptr) {
                        if (curDel->value.name == nameDel) {
                            curDel->Delete();
                            sucDel = true;
                            cout << "[Success]您已成功删除文件: " << nameDel << ":>" << endl;
                            break;
                        }
                        curDel = curDel->nextSibling;
                    }
                    if (!sucDel)
                        cout << "[Wrong]您想要删除的文件(夹)不在当前目录下,操作失败:<" << endl;
                    break;
                }
            case 3:
                {
                    string nameOpen;
                    bool sucOpen = false;
                    cout << "[Input]请输入打开目录名: " << endl;
                    cin >> nameOpen;
                    TreeNode<File> *curOpen = curDir->firstChild;
                    while (curOpen != nullptr) {
                        if (curOpen->value.name == nameOpen && curOpen->value.dir) {
                            curDir = curOpen;
                            cout << "[Success]您已成功打开文件: " << nameOpen << ":>" << endl;
                            sucOpen = true;
                            break;
                        }
                        curOpen = curOpen->nextSibling;
                    }
                    if (!sucOpen)
                        cout << "[Wrong]您想要打开的文件夹不在当前目录下,操作失败:<" << endl;
                    break;
                }
            case 4:
                if (curDir->parent != nullptr){
                    curDir = curDir->parent;
                    cout << "[Success]您已成功进入上级目录:>" << endl;
                }
                else
                    cout << "[Wrong]您当前所在为根目录菜单,操作失败:<" << endl;
                break;
            default:
                cout << "[Wrong]您的输入有误,请重新输入:<" << endl;
                break;
        }
        if(flag){
            break;
        }
    }
}
