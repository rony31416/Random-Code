#include<bits/stdc++.h>
using namespace std;
int m[100][100];

int main()
{
    cout<<"Enter the number of state : ";
    int state;
    cin>>state;

    cout<<"Enter the starting state : ";
    char start;
    cin>>start;
    int starting = start-'a';


    cout<<"enter the number of finishing state : ";
    int num_of_finishig;
    cin>>num_of_finishig;


    cout<<"Enter the finishing states : ";
    vector<char> vfinish;
    vector<int> finishing;
    for(int i = 0 ; i < num_of_finishig; i++)
    {
        char c;
        cin>>c;
        vfinish.push_back(c);
        finishing.push_back(c-'a');
    }

    cout<<"Input dfa table\n----------------------\n";
    cout<<"state  0  1\n------------------\n";
    map<char,char> m0,m1;
    for(int i = 0 ; i < state ; i++ )
    {
        char c,c0,c1;
        cin>>c>>c0>>c1;
        m0[c] = c0;
        m1[c] = c1;
    }


    //corner gula k baad dilam 2 diye and surute sobgula equal table e
    for(int i = 0 ; i < state ; i++)
    {
        for(int j = 0 ; j < state ; j++)
        {
            if(i>j) m[i][j] = 1;
            else m[i][j] = 2;
        }
    }


    //jegula accepting state segular row and column k 0 means cross dilam
    for(int k = 0 ; k < num_of_finishig ; k++)
    {
        for(int i = 0 ; i< state ; i++)
        {
            for(int j = 0 ; j < state ; j++)
            {
                int num = finishing[k];
                if(m[i][j] == 0) m[i][j] = 1;//jodi 2 tain accepting row column crossover kore
                else if(i == num or j == num) m[i][j]= 0;
            }
        }
    }



    cout<<"before table filling algorithm \n---------------------------\n";
    for(int i = 0 ; i< state ; i++)
    {
        cout<<char('a'+i)<<" ";
        for(int j = 0 ; j < state ; j++)
        {
            if(i>j )
            {
                cout<<m[i][j]<<" ";
            }
        }
        cout<<endl;
    }


    //algorithm
    bool ok = true;
    while(ok)
    {
        int cnt = 0;
        for(int i = 0 ; i< state ; i++)
        {
            for(int  j = 0 ; j < state ; j++)
            {
                if(m[i][j] == 1)
                {
                    char st1 = 'a'+ i;
                    char st2 = 'a'+ j;
                    //for zero
                    char viaZero1 = m0[st1];
                    char viaZero2 = m0[st2];

                    if(m[viaZero1-'a'][viaZero2-'a'] == 0 or m[viaZero2-'a'][viaZero1-'a'] == 0)
                    {
                        m[i][j] = 0;
                        cnt++;
                    }
                    //for one;

                    char viaOne1 = m1[st1];
                    char viaOne2 = m1[st2];
                    if(m[viaOne1-'a'][viaOne2-'a'] == 0 or m[viaOne2-'a'][viaOne1-'a'] == 0)
                    {
                        m[i][j] = 0;
                        cnt++;
                    }
                }
            }
        }

        if(cnt==0)
            ok = false;
    }


    //ans store
    vector<pair<char,char>>ans;
    for(int i = 0 ; i< state ; i++)
    {
        for(int j = 0 ; j < state ; j++)
        {
            if(i>j and m[i][j] == 1)
            {
                ans.push_back({'a'+i,'a'+j});
            }
        }
    }


    cout<<"after table filling algorithm \n---------------------------\n";
    for(int i = 0 ; i< state ; i++)
    {
        cout<<char('a'+i)<<" ";
        for(int j = 0 ; j < state ; j++)
        {
            if(i>j )
            {
                cout<<m[i][j]<<" ";
            }
        }
        cout<<endl;
    }
    cout<<" ";
    for(int i = 0 ; i< state ; i++) cout<<" "<<(char)('a'+i);
    cout<<"\n\n-------------------------\n";



    //final output
    for(auto u : ans)
    {
        cout<<"state "<<u.first<<"  and state "<<u.second<<"  are euivalent--->>{"<<u.first<<","<<u.second<<"}"<<"\n";

    }

    return 0;
}
/*
Enter the number of state : 5
Enter the starting state : a
enter the number of finishing state : 1
Enter the finishing states : d
Input dfa table
----------------------
state  0  1
------------------
a      b  e
b      b  c
c      b  d
d      b  e
e      b  e
before table filling algorithm
---------------------------
a
b 1
c 1 1
d 0 0 0
e 1 1 1 0
  a b c d e
after table filling algorithm
---------------------------
a
b 0
c 0 0
d 0 0 0
e 1 0 0 0
  a b c d e

-------------------------
state e  and state a  are euivalent--->>{e,a}


*/
