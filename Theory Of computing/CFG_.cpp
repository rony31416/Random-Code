#include<bits/stdc++.h>
using namespace std;

bool isOk(string s)
{
    bool ok = true;
    for(int i = 0 ; i < s.size() ; i++)
    {
        if(s[i] != '0' and s[i] != '1' )
        {
            return false;
        }
    }
    return true;
}

bool isAccepted(string s)
{
    for(int i = 1 ; i < s.size() -1 ; i++)
    {
        if(s[i] == '1' and s[0] == '0' and s.back()== '0') return  true;
    }
    return false;
}

int main()
{
    cout<<"Enter a string : ";
    string s;
    cin>>s;


    int len = s.size();

    if(!isOk(s))
    {
        cout<<"This string is not proper context free grammar";
        return 0;
    }

    if(!isAccepted(s))
    {
        cout<<"Not Accepted\n";
        return 0;
    }

    cout<<"This string is accepted\n";

    string A = "A1B";

    vector<string> output;
    output.push_back("S");
    output.push_back("0A1B0");
    int one = 0;
    for(int i = 0 ; i < s.size() ;i++)
    {
      if(s[i] == '1'){
        one = i;
        break;
      }
    }
    string temp = "";
    for(int i = one; i < s.size() ; i++)
    {
       temp+=s[i];
       output.push_back("0A"+temp+"B0");
    }
    output.push_back("0A"+temp);
    string str = "";
    for(int i = 0 ; i < one ; i++)
    {
      str+='0';
      output.push_back(str+"A"+temp);
    }
    output.push_back(s);


    for(auto u : output) {
      cout<<u<<"\n";
    }

    return 0;
}
