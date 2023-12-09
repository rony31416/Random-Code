#include <bits/stdc++.h>
using namespace std;

#define DELETE -1
#define SS 1
#define NO_OP 2
#define INSERT 3

int c[100][100], b[100][100];

int editDistance(string x, string y, int m, int n)
{
    if (m == 0) {
        return n;
    }
    if (n == 0) {
        return m;
    }
    if (x[m - 1] == y[n - 1]) {
        return editDistance(x, y, m - 1, n - 1);
    }
    int sub = editDistance(x, y, m - 1, n - 1) + 1;
    int del = editDistance(x, y, m - 1, n) + 1;
    int ins = editDistance(x, y, m, n - 1) + 1;

    int ans = min(sub, min(del, ins));

    if (ans == sub) {
        b[m][n] = SS;
    }
    else if (ans == del) {
        b[m][n] = DELETE;
    }
    else {
        b[m][n] = INSERT;
    }

    c[m][n] = ans;
    return ans;
}

int main()
{
    string first, second;
    cout << "Enter the first string : ";
    cin >> first;
    cout << "Enter the second string : ";
    cin >> second;

    int firstLength = first.size();
    int secondLength = second.size();

    cout << "Edit Distance : " << editDistance(first, second, firstLength, secondLength) << endl;

    return 0;
}

