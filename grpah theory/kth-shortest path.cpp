#include <cstdio>
#include <queue>
const int N=1010,M=100010,MAX=1<<30;
struct edge{
	int p,c;
	edge *next;
}h[N],rh[N],v[M*2];
int vtop;
int dis[N];
void add(int x,int y,int c,edge h[]){
	edge *tmp=&v[vtop++];
	tmp->p=y;tmp->c=c;
	tmp->next=h[x].next;
	h[x].next=tmp;
}
struct dunit{
	int x,d;
	bool operator<(const dunit &A)const
	{return d>A.d;}
};
std::priority_queue<dunit>Q;
void Dij(int s,int n,edge h[]){
	for(int i=1;i<=n;i++)
		dis[i]=MAX;
	Q.push((dunit){s,0});
	dis[s]=0;
	bool flag[N]={};
	while(!Q.empty()){
		dunit a=Q.top();Q.pop();
		if(flag[a.x])continue;
		flag[a.x]=true;
		for(edge *tmp=h[a.x].next;tmp;tmp=tmp->next)
			if(dis[tmp->p] > a.d+tmp->c){
				dis[tmp->p]=a.d+tmp->c;
				Q.push((dunit){tmp->p,dis[tmp->p]});
			}
	}
}
struct unit{
	int x,d;
	bool operator<(const unit &A)const{
		return d+dis[x]>A.d+dis[A.x];
	}
};
std::priority_queue<unit>pQ;
int Astar(int s,int t,int n,int k){
	int vis[N]={};
	pQ.push((unit){s,0});
	while(!pQ.empty()){
		unit a=pQ.top();pQ.pop();
		if(vis[a.x]>k)continue;
		vis[a.x]++;
		if(vis[t]==k)return a.d;
		for(edge *tmp=h[a.x].next;tmp;tmp=tmp->next)
			pQ.push((unit){tmp->p,a.d+tmp->c});
	}
	return -1;
}
int main(){
	int n,m,x,y,c;
	while(~scanf("%d%d",&n,&m)){
		vtop=0;
		for(int i=1;i<=n;i++)
			h[i].next=rh[i].next=NULL;
		while(m--){
			scanf("%d%d%d",&x,&y,&c);
			add(x,y,c,h);
			add(y,x,c,rh);
		}
		int s,t,k;
		scanf("%d%d%d",&s,&t,&k);
		if(s==t)k++;
		Dij(t,n,rh);
		if(dis[s]==MAX)puts("-1");
		else printf("%d\n",Astar(s,t,n,k));
	}
}
