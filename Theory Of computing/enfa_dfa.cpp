#include <bits/stdc++.h>
using namespace std;
vector<char> state, alphabet, start, finish;
vector<set<char> > vZero,vOne,vEpsilon,vClosed,DFA;

set<char> First;
int index(char c);
vector<char> findEclose(char ch);


int main()
{


    int numState;
    cout<<"Number of states in E-NFA?: "<<endl;
    cin >>numState;


    //input states
    for(int i = 0 ; i < numState; i++)
    {
        char STATE;
        cin >> STATE;
        state.push_back(STATE);
    }


    //input number os start states
    int numberOfStartState;
    cout<<"How many start states?"<<endl;
    cin >> numberOfStartState;
   // cout<<"Enter start states\n";
    for(int i = 0; i < numberOfStartState; i++)
    {
        char startState;
        cin >> startState;
        start.push_back(startState);
    }

    //input number of finishing states
    int numberOfFinishState;
    cout<<"How many finishing states?"<<endl;
    cin >> numberOfFinishState;
   // cout<<"Enter finishing states\n";
    for(int i = 0; i < numberOfFinishState; i++)
    {
        char finishState;
        cin >> finishState;
        finish.push_back(finishState);
    }


    //Input taking follows for transition table set.
    cout<<"state  0  1   e\n";
    cout<<"-----------------\n";
    for(int i = 0; i < state.size(); i++)
    {
        //transition with zero
        char kk;
        cin>>kk;
        string viaZero;
        cin>>viaZero;
        set<char> setZero;
        for(auto  u : viaZero)
        {
            if(u != '-')setZero.insert(u);
        }
        vZero.push_back(setZero);
        setZero.clear();

        //transition with one.
        string viaOne;
        cin>>viaOne;
        set<char> setOne;
        for(auto  u : viaOne)
        {
            if(u != '-')setOne.insert(u);
        }
        vOne.push_back(setOne);
        setOne.clear();

        //transition with epsilon.
        set<char> setEpsilon;
        setEpsilon.insert(state[i]);
        string viaEpsilon;
        cin>>viaEpsilon;
        for(auto  u : viaEpsilon)
        {
            if(u != '-')setEpsilon.insert(u);
        }
        vEpsilon.push_back(setEpsilon);
        setEpsilon.clear();
    }
    //eclose of all states.

    for(int i = 0; i < state.size(); i++)
    {
        vector <char> temp = findEclose(state[i]);

        set<char> setIn;

        for(auto ch: temp)
            setIn.insert(ch);

        vClosed.push_back(setIn);
        setIn.clear();
    }


    cout<<"Enclosure of all states\n------------------------\n";
    for(int i = 0; i < state.size() ; i++)
    {
        cout<< state[i] <<" -----> ";
        for(auto ch: vClosed[i])cout<<ch;
        cout<<"\n";
    }

    cout<<"\n\nTable of DFA\n";
    cout<<"States\tzero\tone\n";
    cout<<"---------------------\n";
    int Size = 0;
    for(auto k: vClosed[0])
        First.insert(k);

    DFA.push_back(First);

    while(Size <= DFA.size())
    {
        if(Size == DFA.size() and Size > 0)
            break;

        for(auto cc: DFA[Size])
        {
            cout<<cc;
        }
        cout<<"\t";


        set<char> temp1,temp2, tempOne, tempTwo;

        for(auto ch:DFA[Size])
        {
            int idx = index(ch);

            for(auto c: vZero[idx])temp1.insert(c);

            for(auto chars: temp1)
            {
                int pt = index(chars);

                for(auto chr: vClosed[pt])
                    tempOne.insert(chr);
            }

            for(auto chars: vOne[idx])
            {
                temp2.insert(chars);
            }

            for(auto chars: temp2)
            {
                int pt = index(chars);

                for(auto chr: vClosed[pt])
                    tempTwo.insert(chr);
            }

        }

        for(auto cc: tempOne)
        {
            cout<<cc;
        }
        cout<<"\t";
        for(auto cc: tempTwo)
        {
            cout<<cc;
        }
        cout<<"\n";


        bool flag = true;
        for(int i = 0; i < DFA.size(); i++)
        {
            if(DFA[i] == tempOne)
                flag = false;
        }

        if(flag)
            DFA.push_back(tempOne);

        flag = true;

        for(int i = 0; i < DFA.size(); i++)
        {
            if(DFA[i] == tempTwo)
                flag = false;
        }

        if(flag)
            DFA.push_back(tempTwo);

        Size++;

    }
    return 0;

}

int index(char c)
{
    for(int i = 0; i < state.size(); i++)
    {
        if(state[i] == c)
            return i;
    }
    return -1;
}
vector<char> findEclose(char ch)
{
    set<char> temp;
    vector< char > r;

    int idx = index(ch);
    temp = vEpsilon[idx];

    int Size = 0;

    for(auto c: temp)
        r.push_back(c);

    while( Size <= r.size())
    {
        if(Size == r.size() and Size > 0)
            break;

        temp.clear();

        int pt = index(r[Size]);

        temp = vEpsilon[pt];
        for(auto chr: temp)
        {
            if(find(r.begin(),r.end(),chr) == r.end())
                r.push_back(chr);
        }
        Size++;
    }
    return r;
}
/*
Number of states in E-NFA?:
4
A B C D
How many start states?
1 A
How many finishing states?
1 D
state  0  1   e
-----------------
A     AB  A    C
B     -   C    -
C	  D   -    B
D	  D   D    D
Enclosure of all states
------------------------
A -----> ABC
B -----> B
C -----> BC
D -----> D


Table of DFA
States	zero	one
---------------------
ABC	    ABCD	ABC
ABCD	ABCD	ABCD
*/




