//
// Created by LooperXX on 2018/7/7.
//
#include <bits/stdc++.h>
using namespace std;

template<class T>
class TreeNode {
public:
    // �������ֵ�
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
        if (this->firstChild != nullptr) // ɾ�����ӽڵ��Լ��ӽڵ��µĵ����нڵ�
            this->firstChild->Delete();
        TreeNode *cur = this->parent;
        if (cur != nullptr)
            cur = cur->firstChild;
        TreeNode *pre = cur;
        if (pre == this)// thisΪ�丸�ڵ���׸��ӽڵ� ����ֵܽڵ�(nullptrҲ��Ӱ��)����Ϊ�丸�ڵ�ĵ�һ���ӽڵ�
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
    cout << "|              �ļ�ϵͳ                |" << endl;
    cout << "+-------------------------------------+" << endl;
}

void showMenu(){
    cout << "| 1.�½��ļ���Ŀ¼                     |" << endl;
    cout << "| 2.ɾ���ļ���Ŀ¼                     |" << endl;
    cout << "| 3.��Ŀ¼                           |" << endl;
    cout << "| 4.������һ��                         |" << endl;
    cout << "| 0.�˳�ϵͳ                           |" << endl;
    cout << "+-------------------------------------+" << endl;
}

void printPath(TreeNode<File> *curDir) {
    if (curDir->value.dir)
        cout << "| ��ǰ·��: " << curDir->getPath() << "\t\t|" << endl;
    cout << "+-------------------------------------+" << endl;
}

void listFiles(TreeNode<File> *curDir) {
    cout << "| �ļ��б�: " << endl;
    bool empty = true;
    TreeNode<File> *cur = curDir->firstChild;
    while (cur != nullptr) {
        empty = false;
        cout << "| �ļ���: " << cur->value.name << "\t�ļ�����: " << ((cur->value.dir) ? "Ŀ¼" : "�ļ�") << " |" << endl;
        cur = cur->nextSibling;
    }
    if (empty)
        cout << "| �����ļ�" << endl;
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
                    cout << "[Input]�������½��ļ�(��)���Ƽ�����,0��ʾ�ļ�,1��ʾ�ļ��У�" << endl;
                    cout << "       �������£�" << endl;
                    cout << "       ���ļ��� 1" << endl;
                    cin >> nameCre >> dir;
                    bool dir_ = (dir == 1);
                    TreeNode<File> *curCre = curDir->firstChild;
                    bool vertify = true;
                    while (curCre != nullptr) {
                        if (curCre->value.name == nameCre) {
                            cout << "[Wrong]��������ļ�(��)���ڵ�ǰĿ¼�Ѵ���:<" << endl;
                            vertify = false;
                            break;
                        }
                        curCre = curCre->nextSibling;
                    }
                    if (vertify) {
                        TreeNode<File> *newFile = new TreeNode<File>(File(nameCre, dir_));
                        curDir->insert(newFile);
                        cout << "[Success]���ѳɹ��½��ļ�: " << nameCre << ":>" << endl;
                    }
                    break;
                }
            case 2:
                {
                    string nameDel;
                    bool sucDel = false;
                    cout << "[Input]������ɾ�����ļ�(��)��: " << endl;
                    cin >> nameDel;
                    TreeNode<File> *curDel = curDir->firstChild;
                    while (curDel != nullptr) {
                        if (curDel->value.name == nameDel) {
                            curDel->Delete();
                            sucDel = true;
                            cout << "[Success]���ѳɹ�ɾ���ļ�: " << nameDel << ":>" << endl;
                            break;
                        }
                        curDel = curDel->nextSibling;
                    }
                    if (!sucDel)
                        cout << "[Wrong]����Ҫɾ�����ļ�(��)���ڵ�ǰĿ¼��,����ʧ��:<" << endl;
                    break;
                }
            case 3:
                {
                    string nameOpen;
                    bool sucOpen = false;
                    cout << "[Input]�������Ŀ¼��: " << endl;
                    cin >> nameOpen;
                    TreeNode<File> *curOpen = curDir->firstChild;
                    while (curOpen != nullptr) {
                        if (curOpen->value.name == nameOpen && curOpen->value.dir) {
                            curDir = curOpen;
                            cout << "[Success]���ѳɹ����ļ�: " << nameOpen << ":>" << endl;
                            sucOpen = true;
                            break;
                        }
                        curOpen = curOpen->nextSibling;
                    }
                    if (!sucOpen)
                        cout << "[Wrong]����Ҫ�򿪵��ļ��в��ڵ�ǰĿ¼��,����ʧ��:<" << endl;
                    break;
                }
            case 4:
                if (curDir->parent != nullptr){
                    curDir = curDir->parent;
                    cout << "[Success]���ѳɹ������ϼ�Ŀ¼:>" << endl;
                }
                else
                    cout << "[Wrong]����ǰ����Ϊ��Ŀ¼�˵�,����ʧ��:<" << endl;
                break;
            default:
                cout << "[Wrong]������������,����������:<" << endl;
                break;
        }
        if(flag){
            break;
        }
    }
}
