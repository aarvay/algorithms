/* Author : Vignesh Rajagopalan */
/* Earliest Deadline First in a non-preemptive environment (Aperiodic) */

#include<cstdio>
#include<algorithm>
using namespace std;

struct process{
	char pr;
	int A,ex,end,S;
}P[10];

bool operator < (const process& p1, const process& p2)
{return((p1.A == p2.A) ? (p1.S < p2.S) : (p1.A < p2.A));}

void get(int i){
	scanf("%c%d%d%d\n",&P[i].pr,&P[i].A,&P[i].ex,&P[i].S);
	P[i].end = P[i].A + P[i].ex;	
}

void move(int i, int j){
	if (i+1==j) swap(P[i],P[j]);
	else{
		process temp = P[j];
		while(j<i){
			P[j] = P[j-1];
			j--;
		}
		P[i] = temp;
	}
}

void reOrder(int N){
	int current_end = P[0].end;
	for(int i=1;i<N;i++){
		if(P[i].S < current_end) P[i].A = -1; //Process misses the Starting deadline
		else if(P[i].A < current_end){
			if (i != N-1){
				int j=i+1, min = i;
				while(P[j].A<=current_end && j<N){
					if(P[j].S<P[min].S) min = j;
					j++;
				}
				move(i,min);
				P[i].A = current_end;
				P[i].end = P[i].A + P[i].ex;
				current_end = P[i].end;
			}
			else{
				P[i].A = current_end;
				P[i].end = P[i].A + P[i].ex;
				current_end = P[i].end;
			}
		}
		else if(P[i].A > current_end){
				P[i].end = P[i].A + P[i].ex;
				current_end = P[i].end;			
		}
	}
}

void put(int N){
	printf("PROCESS\tSTART-TIME\tEND-TIME\n");
	for(int i=0;i<N;i++){
		if(P[i].A == -1) printf("-----------%c misses------------\n",P[i].pr);
		else printf("%c\t%d\t\t%d\n",P[i].pr,P[i].A,P[i].end);
	}
}

int main(){
	int N;
	scanf("%d\n",&N);
	
	for(int i=0;i<N;i++) get(i);
	sort(P,P+N); //Sorting the process according to arrival time. 
	reOrder(N); //Scheduling the process according to EDF
	put(N);
	
	return 0;
}
