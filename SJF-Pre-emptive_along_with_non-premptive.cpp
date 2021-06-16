#include <bits/stdc++.h>
using namespace std;
//structure for every process
struct ProcessPre {
   int pid; 
   int art;
   int bt; 
   int ct;
   int tat;
   int wt;
};

struct ProcessNonPre
{
	int at;
	int bt;
	int ct;
	int wt;
	int tat;
	int id;
};



bool comp(ProcessNonPre a,ProcessNonPre b)
{
	if(a.at<b.at || (a.at==b.at && a.id<b.id))
	{
		return true;
	}
	return false;
}



struct compare
{
	bool operator()(ProcessNonPre a,ProcessNonPre b)
	{
		return ((a.bt>b.bt)||(a.bt == b.bt && a.at>b.at) ||(a.bt == b.bt && a.at==b.at && a.id>b.id));
	}
};

void findTurnAroundTime(ProcessPre proc[], int n, int wt[], int tat[]) {
   for (int i = 0; i < n; i++)
   tat[i] = proc[i].bt + wt[i];
}
//waiting time of all process
void findWaitingTime(ProcessPre proc[], int n, int wt[]) {
   int rt[n];
   for (int i = 0; i < n; i++)
   rt[i] = proc[i].bt;
   int complete = 0, t = 0, minm = INT_MAX;
   int shortest = 0, finish_time;
   bool check = false;
   while (complete != n) {
      for (int j = 0; j < n; j++) {
         if ((proc[j].art <= t) && (rt[j] < minm) && rt[j] > 0) {
            minm = rt[j];
            shortest = j;
            check = true;
         }
      }
      if (check == false) {
         t++;
         continue;
      }
      // decrementing the remaining time
      rt[shortest]--;
      minm = rt[shortest];
      if (minm == 0)
         minm = INT_MAX;
         // If a process gets completely
         // executed
         if (rt[shortest] == 0) {
            complete++;
            check = false;
            finish_time = t + 1;
            proc[shortest].ct=finish_time;
            // Calculate waiting time
            wt[shortest] = finish_time -
            proc[shortest].bt -
            proc[shortest].art;
            if (wt[shortest] < 0)
               wt[shortest] = 0;
         }
         // Increment time
         t++;
   }
}
// Function to calculate average time
void findavgTime(ProcessPre proc[], int n) {
   int wt[n], tat[n], total_wt = 0,i,
   total_tat = 0;
   // Function to find waiting time of all
   // processes
   findWaitingTime(proc, n, wt);
   // Function to find turn around time for
   // all processes
   findTurnAroundTime(proc, n, wt, tat);
   for(i=0;i<n;i++)
   {
   	proc[i].wt=wt[i];
   	proc[i].tat=tat[i];
   }
   cout << "Processes " << " Burst time "<<" Completion Time "<< " Turn around time " << " Waiting time\n";
   for (int i = 0; i < n; i++) {
      total_wt = total_wt + wt[i];
      total_tat = total_tat + tat[i];
      cout << " " << proc[i].pid << "\t\t" << proc[i].bt << "\t\t " << proc[i].ct<<"\t\t "<<proc[i].tat<< "\t\t " << proc[i].wt << endl;
   }
   cout << "\nAverage waiting time = " << (float)total_wt / (float)n; cout << "\nAverage turn around time = " << (float)total_tat / (float)n;
}
// main function
int main() {
	int n,i;
	cout<<"Enter the number of processes: ";
	cin>>n;
	ProcessPre proc[n];
	ProcessNonPre p[n];
	for(i=0;i<n;i++)
	{
		cout<<"Enter process id: ";
		cin>>proc[i].pid;
		p[i].id=proc[i].pid;
		cout<<"Enter arrival time: ";
		cin>>proc[i].art;
		p[i].at=proc[i].art;
		cout<<"Enter burst time: ";
		cin>>proc[i].bt;
		p[i].bt=proc[i].bt;
	}
	cout<<"\n\n\nFor premptive scheduling:\n\n";
   findavgTime(proc, n);
   cout<<"\n\n\nFor non-premptive scheduling:\n\n";
   sort(p,p+n,comp);
	priority_queue<ProcessNonPre,vector<ProcessNonPre> ,compare> q;
	int t = 0;
	ProcessNonPre res[n];
	int l = 0;
	double tataverage = 0,waitaverage = 0;
	for(int i =0;i<n;i++)
	{
		// cout<<i<<' '<<t<<endl;
		if(p[i].at <= t)
		{
			
			q.push(p[i]);
			
		}
		else
		{
			
			ProcessNonPre c = q.top();
			q.pop();
			c.ct = t+c.bt;
			c.tat = c.ct-c.at;
			c.wt = c.tat-c.bt;
			t = c.ct;
			res[l++] = c; 
			i--;
			tataverage+=c.tat;
			waitaverage+=c.wt;
			
		}
		
	}

	
	while(!q.empty())
	{
		ProcessNonPre cu = q.top(); q.pop(); cu.ct = t+cu.bt; cu.tat = cu.ct-cu.at;
		cu.wt = cu.tat-cu.bt; t = cu.ct;
		res[l++] = cu;	tataverage+=cu.tat;	waitaverage+=cu.wt;
	}
	
	cout<<"ID\tA.T.\tB.T.\tC.T.\tT.A.T.\tW.T.\n";
	
	for(int i = 0;i<n;i++)
	{
		printf("%d\t%d\t%d\t%d\t%d\t%d\n",res[i].id,res[i].at,res[i].bt,res[i].ct,res[i].tat,res[i].wt);
	}
	cout<<"Wait Time Average = "<<waitaverage/n<<'\n';
	cout<<"Turn Around Time Average = "<<tataverage/n<<'\n';
   return 0;
}
