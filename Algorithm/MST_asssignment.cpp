#include<bits/stdc++.h>
using namespace std;

const int number_of_city = 26;
int city_name[number_of_city][number_of_city],total_cost;



int find_minimum_cost_in_row(int row)
{
    int minimum = INT_MAX,index;
    for(int i = 0 ; i < number_of_city ; i++)
    {
        if(city_name[row][i] <= minimum)
        {
            minimum = city_name[row][i];
            index = i;
        }
    }
    total_cost = total_cost + minimum;
    city_name[row][index] = INT_MAX;
    city_name[index][row] = INT_MAX;

    if(minimum == INT_MAX) return -1;
    return index;
}


int main()
{
    char first_city,second_city;
    char start_city,Final_destination_city;
    vector<char> path_of_cities;


    cout<<"Enter starting city"<<endl;
    cin>>start_city;
    path_of_cities.push_back(start_city);


    cout<<"Enter final destination city"<<endl;
    cin>>Final_destination_city;

    int cost;


    for(int i = 0 ;  i < number_of_city ; i++)
    {
        for(int j = 0 ; j < number_of_city ; j++)
        {
            city_name[i][j] = INT_MAX;
        }
    }

    cout<<"ENTER source city = 0 for exiting input"<<"\n";
    cout<<"Enter source city and Destination city and cost"<<"\n";

    while(1)
    {
        cin>>first_city;
        if(first_city == '0' ) break;
        cin>>second_city;

        cin>>cost;
        city_name[first_city-'A'][second_city-'A'] = cost;
        city_name[second_city-'A'][first_city-'A'] = cost;
    }


    int a,b;
    a = start_city - 'A';
    b = Final_destination_city - 'A';

    while(a!=b)
    {

        int minimum = find_minimum_cost_in_row(a);

        a = minimum;
        if(minimum == -1)
        {
            cout<<"NO WAY TO REACH DESTINATION\n";
            return 0;
        }
        path_of_cities.push_back((char)(minimum+'A'));
    }

    cout<<"the seleted greedy path :"<<endl;
    for(auto u : path_of_cities)
    {
        cout<<"-->"<<u;
    }
    cout<<endl;
    cout<<"Total cost = " <<total_cost<<endl;


    return 0;

}
/*input

A
D
A B 15
B C 11
C D 27
D E 7
E F 19
F G 13
G A 25
A H 10
H D 20
E H 2
0
*/
