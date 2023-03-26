/*
* I use English to write the note to avoid error code.
* 因为怕有乱码，所以有的用英文注释
* 简单的插入和删除操作没有在main中有展示，因为其他的函数中都有使用了。
*/

#include <iostream>
using namespace std;
template<typename T> class List;
template<typename T> class Node {
    T data;
    Node<T>* link;
public:
    Node(Node<T>* nx=NULL) {
        link = nx;
    }
    Node(const T &x, Node<T>* nx = NULL) {
        data = x; link = nx;
    }
    void insert_after(Node<T>* p) {
        p->link = link;
        link = p;
    }
    Node<T>* remove_after() {
        Node<T>* p = link;
        if (p == NULL) p = NULL;
        else link = p->link;
        return p;
    }

    friend class List<T>;

};




template<class T> class List {
    Node<T>* tail,* head;
public:
    List();
    ~List();
    void make_empty();// delete the whole list 删除整个链表
    void insert_front(Node <T> * p);// insert to head 从head插入
    void insert_rear(Node <T>* p);//insert to tail 从tail插入
    void show();// print the whole list 输出链表的所有的元素
    Node<T>* find_node(T data); //find node whose data is equal to data 找到节点
    Node<T>* create_node(T data) { //create new node with data 新建节点
        Node<T>* p = new Node<T>(data);
        return p;
    }
    Node<T>* delete_node(Node<T>* p) { //delete the node p 删除节点p
        Node<T>* nw = head;
        while (nw != NULL && nw->link != p) nw = nw->link;
        if (nw->link == tail) tail = nw;
        return nw->remove_after();
    }
    int len() { //return the list's length 链表的长度
        int res = 0;Node<T>* nw = head;
        while (nw != NULL) {
            res++; nw = nw->link;
        }
        return res;
    }
    void sort_list();  //low->high 从低到高排序
    void reverse_list(Node<T>* lnode,Node<T>* rnode);// reverse list [l,r] l，r闭区间反转
    void merge_list(const List<T> &ad,List<T> &res);// merge 2 ordered list, res means result 合并两个有序链表，res为结果
    void delete_repeat() { //delete the node with same data in ordered list 删除有序链表中的重复节点
        sort_list();
        T x = head->data;
        Node<T>* p = head->link;
        while (p != NULL) {
            if (x == p->data) {
                Node<T>* pre = p;
                p = p->link;
                delete_node(pre);
            }
            else {
                x = p->data; p = p->link;
            }
        }
    }
    void delete_last(int n); // delete the last n node 删除最后n个节点
};



template<typename T> List<T>::List() {
    head = tail = NULL;
}
template<typename T> List<T>::~List() {
    make_empty();
}
template<typename T> void List<T>::make_empty() {
    Node<T>* nw;
    while (head != NULL) {
        nw = head;
        head = nw->link;
        delete nw;
    }
    tail = head = NULL;
}
template<typename T> void List<T>::insert_front(Node<T>* p) {
    if (head == NULL) {
        head = p; tail = head;
    }
    else {
        p->link = head;
        head = p;
    }
}
template<typename T> void List<T>::insert_rear(Node<T>* p) {
    if (tail == NULL) {
        tail = p; head = tail;
    }
    tail->link = p;
    tail = p;
    if (head == NULL) head = p;
}
template<typename T> void List<T>::show() {
    Node<T>* p = head;
    while (p != NULL) {
        cout << p->data << " ";
        p = p->link;
    }
    cout << endl;
}
template<typename T> Node<T>* List<T>::find_node(T data) {
    Node<T>* p = head;
    while (p != NULL && p->data != data)  p = p->link;
    return p;
}
template<typename T> void List<T>::merge_list(const List<T> &ad,List<T> & res) {
    Node<T>* p1 = head;
    Node<T>* p2 = ad.head;
    while (p1 != NULL && p2 != NULL) {
        if (p1->data <= p2->data) {
            res.insert_rear(res.create_node(p1->data));
            p1 = p1->link;
        }
        else {
            res.insert_rear(res.create_node(p2->data));
            p2 = p2->link;
        }
    }
    
    while (p1 != NULL) {
        res.insert_rear(res.create_node(p1->data));
        p1 = p1->link;
    }
    while (p2 != NULL) {
        res.insert_rear(res.create_node(p2->data));
        p2 = p2->link;
    }
}


template<typename T> void List<T>::sort_list() {
    int len_cu = len();
    for (int i = 1; i <= len_cu; i++) {
        Node<T>* p=head;
        Node<T>* p_r = p->link;
        Node<T>* p_l;
        if (p->data > p_r->data) {
            head = p_r;
            p->link = p_r->link;
            p_r->link = p;
            p = p_r;
        }
        p_l = p;
        p = p->link;
        p_r = p->link;
        while (p->link != NULL) {
            if (p->data > p_r->data) {
                p_l->link = p_r;
                p->link = p_r->link;
                p_r->link = p;
                p = p_r;
            }
            p_l = p;
            p = p->link;
            p_r = p->link;
        }
    }
    Node<T>* p = head;
    while (p->link != NULL) p = p->link;
    tail = p;
}

template<typename T> void List<T>::reverse_list(Node<T>* lnode, Node<T>* rnode) {
    if (lnode == rnode) return;
    Node<T>* pre = head;
    if (lnode == head && rnode == tail) {    
        Node<T>* nw = lnode->link;
        Node<T>* nxt = nw->link;
        while (nw != NULL) {
            nw->link = pre;
            pre = nw;
            nw = nxt;
            if (nxt != NULL) nxt = nxt->link;
        }
        head = rnode; tail = lnode;
        lnode->link = NULL;
        return;
    }
    if (lnode == head) {
        Node<T>* nd = rnode->link;
        head = rnode;
        Node<T>* nw = lnode->link;
        Node<T>* nxt = nw->link;
        pre->link = rnode->link;
        while (nw != nd && nxt!=NULL) {
            nxt = nw->link;
            nw->link = pre;
            pre = nw; nw = nxt; nxt = nxt->link;
        }
        return;
    }
    
    while (pre->link != lnode) pre = pre->link;
    
    if (rnode == tail) {
        tail = lnode;
    }

    Node<T>* nd = rnode->link;
    pre->link = rnode;
    Node<T>* nw = lnode->link; 
    Node<T>* nxt = nw->link;
    lnode->link = rnode->link;
    pre = lnode;
    while (nw != nd ) {
        nxt = nw->link;
        nw->link = pre;
        pre = nw; nw = nxt; 
        if(nxt!=NULL) nxt = nxt->link;
    }
}

template<typename T> void List<T>::delete_last(int n) {
    int lens = len();
    if (n > lens) exit(0);
    lens -= n;
    Node<T>* p = head;
    while (lens--)
        p = p->link;
    while (p != NULL) {
        Node<T>* pre = p;
        p = p->link;
        delete_node(pre);
    }
}

int main()
{
    List<int> ls;
    cout << "输入6个int元素" << endl;
    for (int i = 1, x; i <= 6; i++) {
        cin >> x;
        ls.insert_front(ls.create_node(x));
    }
    cout << "头插入结果" << endl;
    ls.show();
    ls.sort_list();
    cout << "排序结果" << endl;
    ls.show();
    int x, y; 
    cout << "翻转的闭区间节点的data，x与y，x与y之间的节点将会翻转，如1 3 5 7 9 10序列输入3 5 会变为1 5 3 7 9 10" << endl;
    cin >> x >> y;
    ls.reverse_list(ls.find_node(x),ls.find_node(y));
    ls.show();
    ls.sort_list();

    List<int> ls2,ls3;
    cout << "再次输入六个元素" << endl;
    for (int i = 1, x; i <= 6; i++) {
        cin >> x;
        ls2.insert_front(ls2.create_node(x));
    }
    cout << "排序后结果" << endl;
    ls2.sort_list();
    ls2.show();
    cout << "合并第一个与第二个链表结果" << endl;
    ls.merge_list(ls2,ls3);
    ls3.show();
    cout << "删除重复节点的结果" << endl;
    ls3.delete_repeat();
    ls3.show();
    cout << "输入一个整数，删除最后整数个节点" << endl;
    cin >> x;
    ls3.delete_last(x); ls3.show();
    return 0;
}

