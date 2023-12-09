#include <bits/stdc++.h>
using namespace std;

#define nInf -9999999;
int c1=0,c2=0;
int memoCutRodAux(int price[],int n, int r[]);


int cutRod(int price[],int n)

{
   c2++;
    if(n == 0)
        return 0;

    int temp = nInf;

    for(int i = 1; i <=n ; i++)
        temp = max(temp,price[i] + cutRod(price,n-i));

    return temp;
}

int memoCutRod(int price[],int n)
{
    int r[n+1];

    for(int i = 0; i <= n; i++)
        r[i] = nInf;

    return memoCutRodAux(price,n,r);
}

int memoCutRodAux(int price[],int n, int r[])
{
    c1++;
    if(r[n] >= 0)
        {

            return r[n];
        }

    int temp;
    if(n == 0)
    {
        temp = n;
    }
    else
    {
        temp = nInf;

        for(int i = 1; i <= n; i++)
            temp = max(temp,price[i] + memoCutRodAux(price,n-i,r));
    }

    return r[n] = temp;
}

int main()
{

    int p[] = {0,1,5,8,9,10,17,17,20,24,30};

    cout<<memoCutRod(p,4)<<endl;
    cout<<cutRod(p,4)<<endl;
    cout<<c1<<" "<<c2<<endl;

    return 0;
}
