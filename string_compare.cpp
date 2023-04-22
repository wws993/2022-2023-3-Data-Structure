// string_compare.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<time.h>
#include<algorithm>
#include<string>

using namespace std;

int kmp(char* s1, char* s2,int len1,int len2) {
    int* nxt = new int[len2 + 10];
    nxt[0] = -1; nxt[1] = 0;
    for (int i = 2, j = 0; i < len2; i++) {
        if (s2[i - 1] == s2[j]) nxt[i] = ++j;
        else if (j > 0) j = nxt[j];
            else nxt[i] = 0;
    }
    int i = 0, j = 0;
    while (i < len1 && j < len2) {
        if (s1[i] == s2[j]) i++, j++;
        else if (j != 0) j = nxt[j];
            else i++;
    }
    delete[] nxt;
    return j == len2 ? i - len2 : -1;
}


int bf(char* s1, char* s2, int len1, int len2) {
    for (int i = 0; i < len1; i++) {
        bool b = 1;
        for (int j = 0; j < len2; j++)
            if (s1[j + i] != s2[j]) {
                b = 0;
                break;
            }
        if (b == 1) return i;
    }
    return -1;
}


int bm(char* s1, char* s2, int len1, int len2) {
    // prebmbc
    int bmbc[300];
    for (int i = 0; i < 256; i++) bmbc[i] = len2;
    for (int i = 0; i < len2 - 1; i++) bmbc[s2[i]] = len2 - 1 - i;


    // prebmgs
    int* suff = new int[len2 + 10];
    int* bmgs = new int[len2 + 10];
    suff[len2 - 1] = len2;
    
    for (int i = len2 - 2; i >= 0; i--) {
        int j = i;
        while (j >= 0 && s2[j] == s2[len2 - 1 - i + j]) j--;
        suff[i] = i - j;
    }
    
    for (int i = 0; i < len2; i++) bmgs[i] = len2;
    for (int i = len2 - 1; i >= 0; i--)
        if (suff[i] == i + 1)
            for (int j=0 ; j < len2 - 1 ; j++)
                if (bmgs[j] == len2) bmgs[j] = len2 - 1 - i;
    for (int i = 0; i <= len2 - 2; i++) 
        bmgs[len2 - 1 - suff[i]] = len2 - 1 - i;
    
    //compare
    int j = 0;
    while (j <= len1 - len2) {
        int i = 0;
        for (i = len2 - 1; i >= 0 && s2[i] == s1[i + j]; i--);
        if (i < 0) {
            delete[]bmgs;
            delete[]suff;
            return j;
        }
        else
            j += max(bmbc[s1[i + j]] - len2 + 1 + i, bmgs[i]);
    }
    delete[]bmgs;
    delete[]suff;
    return -1;
}

string make_string(int len) {//构造数据函数
    string s;
    for (int i = 0; i < len; i++)
        s.push_back(char('a' + rand() % 26));
    return s;
}

/*
14 5
abbabcababacab
babac
*/
int main()
{
    int m, n;
    cin >> n >> m;
    char* s1 = new char[n + 10];
    char* s2 = new char[m + 10];
    /* 
    //自动构造大数据进行时间测试
    string s = make_string(n);
    //cout << s << endl;
    for (int i = 0; i < n; i++)
        s1[i] = s[i];
    for (int i = n-m-5,j=0; i < n-5; j++,i++)
        s2[j] = s[i];
    */
    //小数据判断正确性
    for (int i = 0; i < n; i++)
        cin >> s1[i];
    for (int i = 0; i < m; i++)
        cin >> s2[i];


    clock_t start = clock();
    cout<<"bf result:" << bf(s1, s2, n, m) << endl;
    clock_t end = clock();
    cout <<"bf time:" << (double)(end - start) / CLOCKS_PER_SEC * 1000 << "ms" << endl;


    start = clock();
    cout << "kmp result:" << kmp(s1, s2, n, m) << endl;
    end = clock();
    cout << "kmp time:" << (double)(end - start) / CLOCKS_PER_SEC * 1000 << "ms" << endl;

    start = clock();
    cout << "bm result:" << bm(s1, s2, n, m) << endl;
    end = clock();
    cout << "bm time:" << (double)(end - start) / CLOCKS_PER_SEC * 1000 << "ms" << endl;

    delete[] s1;
    delete[] s2;
    return 0;
}
