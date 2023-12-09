#include <bits/stdc++.h>
using namespace std;

int LCSlen(string x, string y, int m, int n)
{
    if (m == 0 || n == 0)
    {
        return 0;
    }

    if (x[m-1] == y[n-1])
    {
        return 1 + LCSlen(x, y, m-1, n-1);
    }
    else
    {
        return max(LCSlen(x, y, m-1, n), LCSlen(x, y, m, n-1));
    }
}

void printLCS(string x, string y, int m, int n)
{
    if (m == 0 || n == 0)
    {
        return;
    }

    if (x[m-1] == y[n-1])
    {
        printLCS(x, y, m-1, n-1);
        cout << x[m-1];
    }
    else if (LCSlen(x, y, m-1, n) >= LCSlen(x, y, m, n-1))
    {
        printLCS(x, y, m-1, n);
    }
    else
    {
        printLCS(x, y, m, n-1);
    }
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

    cout << "Longest common subsequence length = " << LCSlen(first, second, firstLength, secondLength) << endl;

    cout << "Longest common subsequence = ";
    printLCS(first, second, firstLength, secondLength);

    return 0;
}
