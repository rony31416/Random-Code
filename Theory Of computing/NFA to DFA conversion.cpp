#include<bits/stdc++.h>
#include<stdio.h>
#include<string.h>
using namespace std;
char states[10],acceptState,startState;
char zero[100][3]= {"",""};
int numberOfState =4;
vector<pair<char,pair<string,string>>> NFA;
vector<pair<string,pair<string,string>>> DFA;

void  print_DFA()
{
    cout<<"states\t0\t1\n";
    cout<<"-----------------\n";
    for(auto u : DFA)
    {
        cout<<u.first<<"\t";
        cout<<u.second.first<<"\t";
        cout<<u.second.second<<"\n";
    }
}


int main()
{
    char states[10],acceptState,startState;
    char zero[100][3]= {"",""};
    int numberOfState;

    printf("Enter the number of states : ");
    scanf("%d",&numberOfState);


    printf("Enter all states : ");
    for(int i = 0 ; i < numberOfState ; i++)
    {
        cin>>states[i];
    }

    printf("Enter starting state : ");
    scanf(" %c",&startState);

    printf("Enter accepting state: ");
    scanf(" %c",&acceptState);

    printf("Enter a string for checking : ");
    string s;
    cin>>s;
    int i,j;
    for(i = 0,j = 0; i < s.length(); i++)
    {
        bool f = false;
        if(s[i] == '0')
        {
            cout<<"current state (a,0)---> {"<<states[j]<<"}\n";
            continue;
        }

        if(j == 3)
        {
            cout<<"current state (d,0/1)-->{"<<states[j]<<"}\n";
            continue;
        }

        if(s[i] == '1')
        {
            cout<<"current state (a,1)---> {"<<states[j++];
            if(j == 3) continue;
            cout<<","<<states[j]<<"}\n";
        }

        if(s[i+1] == '1' )
        {
            i++;
            cout<<"current state (b,1)--> {"<<states[j++];
            if(j == 3) continue;
            cout<<","<<states[j]<<"}\n";
        }
        else
        {
            j = 0;
            continue;;
        }

        if(s[i+1] == '1' )
        {
            // i+=2;
            cout<<"current state (c,1)--> {"<<states[j++];

            cout<<","<<states[j]<<"}\n";
            if(j == 3) continue;
        }
        else
        {
            j = 0;
            continue;

        }
        if(f) i++;
    }
    cout<<"\n---------------------\n";
    if(j==3)
    {
        cout<<"ACCEPTED\n";;
    }
    else
    {
        cout<<"NOT ACCEPTED\n";
    }

    // NFA_transition_table();
    cout<<"if there are no transition via 0/1 then write '\-1\' for trap"<<"\n";
    for(int i = 0 ; i < numberOfState ; i++)
    {
        cout<<"Transition for state "<<states[i]<<" via 0 : ";
        string a,b;
        cin>>a;
        cout<<"Transition for state "<<states[i]<<" via 1 : ";
        cin>>b;
        NFA.push_back({states[i],{a,b}});

    }


    for(auto u : NFA)
    {
        char k = u.first;
        string x = "";
        x+=k;
        string y = u.second.first;
        string z = u.second.second;
        DFA.push_back({x,{y,z}});
    }
    DFA.push_back({"AB",{DFA[0].second.first,NFA[0].second.second+NFA[1].second.second}});
    string aa = DFA[0].first+DFA[2].second.second;
    DFA.push_back({"ABC",{DFA[0].first,aa+"BC"}});

    DFA.push_back({"ABCD",{aa,"BC"+aa}});
    DFA.push_back({aa,{aa,"BC"+aa}});

    print_DFA();
   // dbg_out(DFA);

    return 0;


}
/*
//sample input

Enter the number of states : 4
Enter all states : A B C D
Enter starting state : A
Enter accepting state: D
Enter a string for checking : 10101110
current state (a,1)---> {A,B}
current state (a,0)---> {A}
current state (a,1)---> {A,B}
current state (a,0)---> {A}
current state (a,1)---> {A,B}
current state (b,1)--> {B,C}
current state (c,1)--> {C,D}
current state (d,0/1)-->{D}
current state (a,0)---> {D}

---------------------
ACCEPTED

if there are no transition via 0/1 then write '-1' for trap
Transition for state A via 0 : A
Transition for state A via 1 : AB
Transition for state B via 0 : -1
Transition for state B via 1 : C
Transition for state C via 0 : -1
Transition for state C via 1 : D
Transition for state D via 0 : D
Transition for state D via 1 : D

states	0	1
-----------------
A	  A	    AB
B	  -1	C
C	  -1	D
D	  D	    D
AB	  A	    ABC
ABC	  A	    ADBC
ABCD  AD	BCAD
AD	  AD	BCAD

*/
