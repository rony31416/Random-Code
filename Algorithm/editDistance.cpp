#include <bits/stdc++.h>
using namespace std;

#define DELETE -1
#define SS 1
#define NO_OP 2
#define INSERT 3


int c[100][100],b[100][100];

int editDistance(string x,string y,int m, int n)
{
    for(int i = 0; i <= m; i++)
        c[i][0] = i;

    for(int i = 0; i <= n; i++)
        c[0][i] = i;

    for(int i = 1; i <=m; i++)
    {
        for(int j = 1; j <=n; j++)
        {
            if(x[i- 1] == y[j -1])
            {
                c[i][j] = c[i-1][j-1];
                b[i][j] = NO_OP;
            }
            else
            {
                int ans;
                int sub = c[i-1][j-1] + 1;
                b[i][j] = SS;
                ans = sub;

                int del = c[i-1][j] + 1;

                if(del < sub)
                {
                    b[i][j] = DELETE;
                    ans = del;
                }
                int ins = c[i][j-1] + 1;

                if(ins <ans)
                {
                    b[i][j] = INSERT;
                    ans = ins;
                }
                c[i][j] = ans;

            }
        }
    }
    return c[m][n];
}

int main()
{
    string first,second;
    cout<<"Enter the first string : ";
    cin>>first;
    cout<<"Enter the second string : ";
    cin>>second;

    int firstLength = first.size();
    int secondLength = second.size();
    cout<<"Edit Distance : "<<editDistance(first,second,firstLength,secondLength)<<endl;

    return 0;
}
