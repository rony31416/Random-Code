#include <bits/stdc++.h>
using namespace std;
#define previousDiagonal 2
#define upperCell -1
#define LeftCell 1

int c[100][100],b[100][100];

int LCSlen(string x,string y,int m,int n)
{
    for(int i = 0; i <= m; i++)
        c[i][0] = 0;
    for(int i = 0; i <= n; i++)
        c[0][i] = 0;


    for(int i = 1; i <= m; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            if(x[i-1] == y[j-1])
            {
                c[i][j] = c[i-1][j-1] + 1;
                b[i][j] = 2;
            }
            else if(c[i-1][j] >= c[i][j-1])
            {
                c[i][j] = c[i-1][j];
                b[i][j] = -1;
            }
            else
            {
                c[i][j] = c[i][j-1];
                b[i][j] = 1;
            }

        }
    }
    return c[m][n];
}

void printLCS(string x,int i,int j)
{

    if(i == 0 or j == 0)
    {
        return;
    }
    if(b[i][j] == previousDiagonal)
    {
        printLCS(x,i-1,j-1);
        cout<<x[i-1];
    }
    else if(b[i][j] == upperCell)
        printLCS(x,i-1,j);
    else
        printLCS(x,i,j-1);

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

    cout<<"Longest common subsequence length = "<<LCSlen(first,second,firstLength,secondLength)<<endl;

    printLCS(first,firstLength,secondLength);

    return 0;


}
