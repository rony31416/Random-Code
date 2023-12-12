#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef long double ld;
typedef vector<ll> vll;
typedef vector<string> vs;
typedef vector<pair<int, int>> vpi;
typedef set<ll> s;
typedef map<ll, ll> mll;
typedef pair<int, int> pint;
double pi = 3.14159265359;

#define FOR(n, v)             \
   for (ll i = 0; i < n; i++) \
      cin >> v[i];
#define REP(i, n) for (int i = 0; i < n; i++)
#define pb push_back
#define ttimes(T) while (T--)
#define fastIO ios_base::sync_with_stdio(false);
#define nl "\n";
#define all(v) v.begin(), v.end()
#define sort_a(v) sort(all(v));
#define sort_d(v) sort(all(v), greater<ll>());
#define py printf("YES\n");
#define pn printf("NO\n");
#define pmone printf("-1\n");

const ll N = 50005;

void solve()
{
   int n;
  // cin>>n;
   int a,b;
   cin>>a>>b;
   string s;
   cin>>s;
   int i = 0;
   for( i = a-1;i>=0; i++)
   {
      if(s[i] > b-'0')
      break;
   }
   for(int j = 0 ; j < s.size() ; j++)
   {

      cout<<s[j];
      if(j == a-i) cout<<b;
   }
   cout<<nl;



}
int main()
{

   int t;
   bool cs;
   cs = true;
   // cs = false;
   if (cs)
   {
      cin >> t;
      for (int i = 1; i <= t; i++)
      {
        // printf("Case %d: ", i);
         solve();
      }
   }

   else
      solve();

   return 0;
}
