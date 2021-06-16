//Bhawesh Madhwani(18JE0226)
#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
pair<int,pair<string,int> > v[105];
bool check(string str1 , string str2)
{
    int i,j;
    i = 0;
    j = 0;
    int n1,n2;
    n1 = str1.size();
    n2 = str2.size();
    if(n1<n2)
    {
        return(true);
    }
    if(n1>n2)
    {
        return(false);
    }
    while(i<n1 && j<n2)
    {
        if(str1[i]==str2[j])
        {
            i++;
            j++;
            continue;
        }
        if(str1[i]<str2[j])
        {
            return(true);
        }
        return(false);
    }
    return(false);
}
void join(int l , int mid , int r)
{
    int n1 = mid - l + 1;
    int n2 = r - mid;
    int i,j,k,a,b,c;
    pair<int,pair<string,int> > v1[n1],v2[n2];
    for(i=0 ; i<n1 ; i++)
    {
        v1[i] = (v[l+i]);
    }
    for(i=0 ; i<n2 ; i++)
    {
        v2[i] = (v[mid+1+i]);
    }
    i = 0;
    j = 0;
    k = l;
    while(i<n1 && j<n2)
    {
        pair<int,pair<string,int> >p,q;
        p = v1[i];
        q = v2[j];
        if(p.fi<q.fi || (p.fi==q.fi && check(p.se.fi,q.se.fi)))
        {
            v[k++] = v1[i++];
        }
        else
        {
            v[k++] = v2[j++];
        }
    }
    while(i<n1)
    {
        v[k++] = v1[i++];
    }
    while(j<n2)
    {
        v[k++] = v2[j++];
    }
}
void mergeSort(int l , int r)
{
    if(l<r)
    {
        int mid = l + (r-l)/2;
        mergeSort(l,mid);
        mergeSort(mid+1,r);
        join(l,mid,r);
    }
}
int main()
{
    //First Come First Serve
    int a,b,c,i,j,n;
    string str;
    cin>>n;//number of tasks
    for(i=0 ; i<n ; i++)
    {
        cin>>str>>b>>c;
        //str denotes Id of the process
        //b denotes Arrival TIme of the process
        //c denotes Burst Time of the Process
        v[i] = (make_pair(b,make_pair(str,c)));
    }
    mergeSort(0,n-1);
    int ct[n],tat[n],wt[n];
    int t = v[0].fi;
    i = 0;
    while(i<n)
    {
        str = v[i].se.fi;//ID of the task
        b = v[i].fi;//Arrival Time of task with ID str
        c = v[i].se.se;//Burst time for the task with ID str
        t+=c;
        ct[i] = t;
        tat[i] = ct[i] - b;
        wt[i] = tat[i] - c;
        i++;
    }
    cout<<"Task Execution Detail are shown Below:-\n";
    cout<<"ID of the Task\t  Completion Time\t  Turn Around Time\t  Waiting Time\n";
    double p,q;
    p = q = 0.0;
    for(i=0 ; i<n;  i++)
    {
        cout<<v[i].se.fi<<"\t\t\t\t\t\t"<<ct[i]<<"\t\t\t\t\t"<<tat[i]<<"\t\t\t\t\t"<<wt[i]<<"\n";
        p+=tat[i];
        q+=wt[i];
    }
    p = (double)p/(double)n;
    q = (double)q/(double)n;
    cout<<"Average Turn Around Time = "<<p<<"\n";
    cout<<"Average Waiting Time = "<<q<<"\n";
}