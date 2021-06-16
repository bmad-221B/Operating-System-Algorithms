//Bhawesh Madhwani(18JE0226)
#include<bits/stdc++.h>
#define fi first
#define se second
#define mkp make_pair
#define pb push_back
#define sz(x) (long long)(x).size()
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;
vector<pair<pll,pair<ll,string> > >v;
vector<pll>v1;
ll n,m;
string str;
void merge(ll s, ll mid , ll e)
{
    ll n1 = mid - s + 1;
    ll n2 = e - mid;
    vector<pll>v2,v3;
    ll i;
    for(i=s ; i<=mid ; i++)
    {
        v2.push_back(v1[i]);
    }
    for(i=mid+1 ; i<=e ; i++)
    {
        v3.push_back(v1[i]);
    }
    ll j,k;
    i = 0;
    j = 0;
    k = s;
    while(i<n1 && j<n2)
    {
        if(v2[i].first<v3[j].first || (v2[i].first==v3[j].first && v2[i].second<v3[j].second))
        {
            v1[k++] = v2[i++];
        }
        else
        {
            v1[k++] = v3[j++];
        }
    }
    while(i<n1)
    {
        v1[k++] = v2[i++];
    }
    while(j<n2)
    {
        v1[k++] = v3[j++];
    }
}
void mergeSort(ll s , ll e)
{
    if(s!=e)
    {
        ll mid = s + (e-s)/2;
        mergeSort(s,mid);
        mergeSort(mid+1,e);
        merge(s,mid,e);
    }
}
void solveIt()
{
    ll a,b,c,d,i,j,x,y,z,t;
    double p,q,r,w;
    string str1,str2;
    char ch;
    cout<<"Enter Number of Tasks\n";
    cin>>n;//Number of tasks
    cout<<"Enter task details\n";
    //here;
    for(i=0 ; i<n ; i++)
    {
        cout<<"Enter Task ID for Task "<<i+1<<"\n";
        cin>>str;
        cout<<"Enter Arrival Time for Task "<<i+1<<"\n";
        cin>>a;
        cout<<"Enter Burst Time for Task "<<i+1<<"\n";
        cin>>b;
        cout<<"Enter Priority for Task "<<i+1<<"\n";
        cin>>c;
        v.push_back(make_pair(make_pair(a,b),make_pair(c,str)));
        v1.push_back(make_pair(a,i));
    }
    //here;
    mergeSort(0,n-1);
    vector<ll>ct(n),tat(n),wt(n),bt(n);
    //ct represents completion time
    //tat represents Turn Around Time
    //wt represents waiting time
    //how much time this process needs to complete
    for(i=0 ; i<n ; i++)
    {
        a = v1[i].second;
        bt[a] = v[a].first.second;
        //cout<<bt[a]<<" ";
    }
    //here;
    i = 0;
    set<pll>s;//pair contains Priority and Index of the Task
    t = 0;//time starts ar t=0
    while(true)
    {
        if(!sz(s))
        {
            if(i>=n)
            {
                break;
            }
            t = max(t,v1[i].first);
        }
        while(i<n)
        {
            if(v1[i].first<=t)
            {
                a = v1[i].second;
                s.insert(make_pair(v[a].second.first,a));
                i++;
                continue;
            }
            break;
        }
        auto p1 = *s.rbegin();
        c = p1.first;
        a = p1.second;
        t++;
        bt[a]--;
        if(!bt[a])
        {
            ct[a] = t;
            s.erase(p1);
        }
    }
    //here;
    p = q = r = 0.0;
    r = t;
    cout<<"Task Execution Detail are shown Below:-\n";
    cout<<"ID of the Task\t  Completion Time\t  Turn Around Time\t  Waiting Time\n";
    for(i=0; i<n ; i++)
    {
        tat[i] = ct[i] - v[i].first.first;
        wt[i] = tat[i] - v[i].first.second;
        cout<<v[i].second.second<<"\t\t\t\t\t\t"<<ct[i]<<"\t\t\t\t\t"<<tat[i]<<"\t\t\t\t\t"<<wt[i]<<"\n";
        p+=tat[i];
        q+=wt[i];
        //r+=ct[i];

    }
    p = p/(double)n;
    q = q/(double)n;
    r = n/(double)r;
    cout<<"Average Turn Around Time = "<<p<<"\n";
    cout<<"Average Waiting Time = "<<q<<"\n";
    cout<<"Throughput = "<<r<<"\n";
}
int main()
{
// #ifndef ONLINE_JUDGE
//         freopen("Rinput.txt", "r", stdin);
//         freopen("Routput.txt", "w", stdout);
// #endif
    ll t = 1;
    //cin>>t;
    while(t--)
    {
        solveIt();
    }
}
