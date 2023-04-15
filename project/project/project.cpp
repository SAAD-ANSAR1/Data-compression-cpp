#include <iostream>
#include <fstream>
#include <string>
#include<algorithm>
using namespace std;

class node {
public:
    char data;
    int freq;
    node* left;
    node* right;
};

node* tempptr=NULL;
double freqcalculate = 0;

void printCodes(node* root, int arr[], int top);

class tree {
public:
    node* root;

    tree() {
        root = NULL;
    }

    void insert(node* a, node* b)
    {
        if (root == NULL) {
            node* temp = new node;
            temp->data = ' ';
            temp->freq = a->freq + b->freq;
            temp->left = a;
            temp->right = b;
            root = temp;
        }
        else {
            node* temp = new node;
            if (root->freq==a->freq) {
                temp->right = root;
                temp->left = b;
                temp->freq = a->freq+b->freq;
                temp->data = ' ';
                root = temp;
            }
            else if (root->freq == b->freq) {
                temp->left = root;
                temp->right = a;
                temp->freq = a->freq + b->freq;
                temp->data = ' ';
                root = temp;
            }
            else {
                if (a->data != ' ' || b->data != ' ') {
                    temp->data = ' ';
                    temp->freq = a->freq + b->freq;
                    temp->left = a;
                    temp->right = b;
                    tempptr = temp;
                   // cout << "PROBLEM OCCURED" << endl;
                }









            }
        }

    }
    void inorder(node* n) {
        if (n != NULL) {
            inorder(n->left);
            cout << n->data << " ";
            inorder(n->right);
        }
    }



};



struct Nodes {
    char data;
    int freq = 1;
    Nodes* next{};
};

class list {
public:
    Nodes* head;

    list() {
        head = NULL;
    }

    void insert_term(char ch)
    {
        Nodes* temp = new Nodes;
        temp->data = ch;
        temp->next = NULL;

        if (head == NULL)
            head = temp;
        else {
            Nodes* temp2 = head;
            while (temp2!=NULL) {
                if (temp2->data == ch) {
                    temp2->freq++;
                    return;
                }
                temp2 = temp2->next;
            }
            temp2 = head;
            while (temp2->next != NULL) {
                temp2 = temp2->next;
            }
            temp2->next = temp;
        }
        sort();
    }

    void display() {
        Nodes* q = head;
        while (q != NULL) {
            cout << q->data << ":" << q->freq << endl;
            q = q->next;
        }

    }
    void sort() {
        Nodes* ptr = head;
        Nodes* nxt = NULL;
        Nodes* temp = new Nodes;
        if (head != NULL) {
            while (ptr != NULL) {
                nxt = ptr->next;
                while (nxt != NULL) {
                    if (ptr->freq > nxt->freq) {
                        temp->data = ptr->data;
                        temp->freq = ptr->freq;
                        ptr->data = nxt->data;
                        ptr->freq = nxt->freq;
                        nxt->data = temp->data;
                        nxt->freq = temp->freq;
                    }
                    nxt = nxt->next;
                }
                ptr = ptr->next;
            }
        }
    }

    void huffman() {
        Nodes* ptr=head;
        tree T;

        while (ptr->next!=NULL) {
            node* temp = new node;
            node* temp2 = new node;
            temp->data = ptr->data;
            temp->freq = ptr->freq;
            temp->left = NULL;
            temp->right = NULL;
            ptr = ptr->next;
            temp2->data = ptr->data;
            temp2->freq = ptr->freq;
            temp2->left = NULL;
            temp2->right = NULL;
            ptr->data = ' ';
            ptr->freq = head->freq + ptr->freq;
            head = ptr;
            T.inorder(T.root);
            cout << endl;
            T.insert(temp,temp2);
            if (tempptr != NULL) {
                node* temp3 = new node;
                temp3->data = ' ';
                temp3->freq = T.root->freq + tempptr->freq;
                temp3->left = T.root;
                temp3->right = tempptr;
                T.root = temp3;
                tempptr = NULL;
            }
            T.inorder(T.root);
            cout << endl;
            cout << endl;
            sort();
            display();
        }
        T.inorder(T.root);
        cout << endl;
        int arr[10];
        int top = 0;
        printCodes(T.root, arr, top);
    }








};

int isLeaf(node* root)
{
    return !(root->left) && !(root->right) && root->data!=' ';
}

void printArr(int arr[], int n,node* root)
{
    int i;
    freqcalculate = freqcalculate+(n*root->freq);
    for (i = 0; i < n; ++i)
        cout << arr[i];
    cout << endl;
}



void printCodes(node* root, int arr[], int top) {

    // Assign 0 to left edge and recur
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    // Assign 1 to right edge and recur
    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

   
    // and its code from arr[]
    if (isLeaf(root)) {
        cout << root->data <<" : ";
        printArr(arr, top,root);
    }
}








int main() {

    list obj;
    int size = 0;
    ifstream fin;
    fin.open("text.txt");
    string str = " ";
    getline(fin, str);
    for (int i = 0; str[i] != '\0'; i++) {
        obj.insert_term(str[i]);
        size++;
    }
    obj.display();
    cout << endl;
    obj.huffman();
 


    cout << "Compression of file is : "<< 8 / (freqcalculate / size)<<endl;


}





