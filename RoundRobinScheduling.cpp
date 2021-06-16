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
vector<pair<pll,string> >v;
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
void check(ll qt)
{
    ll a,b,c,d,i,j,t;
    double p,q,r,w;
    queue<ll>rq;
    vector<ll>ct(n),tat(n),wt(n),bt(n);
    for(i=0  ;i<n ; i++)
    {
        bt[i] = v[i].first.second;
    }
    t = 0;
    i = 0;
    p = -1;
    while(true)
    {
        if(!sz(rq) && p==-1)
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
                rq.push(v1[i].second);
                i++;
                continue;
            }
            break;
        }
        if(p!=-1)
        {
            rq.push(p);
        }
        j = rq.front();
        rq.pop();
        if(bt[j]<=qt)
        {
            t+=bt[j];
            ct[j] = t;
            bt[j] = 0;
            p = -1;
        }
        else
        {
            bt[j]-=qt;
            t+=qt;
            p = j;
        }
    }
    cout<<"For Quantum Time = "<<qt<<"\n";
    p = q = r = 0.0;
    r = t;
    cout<<"Task Execution Detail are shown Below:-\n";
    cout<<"ID of the Task\t  Completion Time\t  Turn Around Time\t  Waiting Time\n";
    for(i=0; i<n ; i++)
    {
        tat[i] = ct[i] - v[i].first.first;
        wt[i] = tat[i] - v[i].first.second;
        cout<<v[i].second<<"\t\t\t\t\t\t"<<ct[i]<<"\t\t\t\t\t"<<tat[i]<<"\t\t\t\t\t"<<wt[i]<<"\n";
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
void solveIt()
{
    ll a,b,c,d,i,j,x,y,z,t;
    double p,q,r,w;
    string str1,str2;
    char ch;
    cout<<"Enter the Number of Tasks\n";
    cin>>n;
    for(i=0 ; i<n ; i++)
    {
        cout<<"Enter the ID of Tasks\n";
        cin>>str;
        cout<<"Enter Arrival Time for Task\n";
        cin>>a;
        cout<<"Enter Burst Time for Task\n";
        cin>>b;
        v.push_back(make_pair(make_pair(a,b),str));
        v1.push_back(make_pair(a,i));
    }
    mergeSort(0,n-1);
    check(1);
    check(2);
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
