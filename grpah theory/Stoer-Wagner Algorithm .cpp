//min-cut N^3
const int N=160;
int n,m;
struct node{int p,c;struct node* next;
	node(){}
	node(int P,int C,node *n):p(P),c(C),next(n){}
};
node h[N],v[N*N*N];
int conn[N][N],line[N],top,dis[N];
bool flag[N],use[N];
int vtop;
void add(int x,int y,int c){
	if(conn[x][y]){conn[x][y]+=c;return;}
	h[x].next=&(v[vtop++]=node(y,c,h[x].next));
	conn[x][y]=c;
}
void DFS(int x){
	flag[x]=true;
	for(node* tmp=h[x].next;tmp;tmp=tmp->next)
		if(!flag[tmp->p])
			DFS(tmp->p);
}
void MAS(int nn){
	mst(flag);mst(dis);
	priority_queue<PII>Q;
	for(int i=1;i<=n;i++)
		flag[i]=use[i];
	top=0;
	for(int i=1;i<=n;i++)
		if(!flag[i]){
			dis[i]=1;
			Q.push(mpr(dis[i],i));
			break;
		}
	while(nn){
		int x=Q.top().Y;Q.pop();
		if(flag[x])continue;
		nn--;
		line[top++]=x;
		flag[x]=1;
		for(node *tmp=h[x].next;tmp;tmp=tmp->next)
			if(!flag[tmp->p]){
				dis[tmp->p]+=conn[x][tmp->p];
				Q.push(mpr(dis[tmp->p],tmp->p));
			}
	}
}
int main(){
	int T,x,y,c;
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		vtop=0;
		mst(conn);
		for(int i=1;i<=n;i++)
			h[i].next=NULL;
		while(m--){
			scanf("%d%d%d",&x,&y,&c);
			add(x,y,c);
			add(y,x,c);
		}
		mst(flag);
		DFS(1);
		bool connect=true;
		for(int i=1;i<=n;i++)
			if(!flag[i])connect=false;
		if(!connect){puts("0");continue;}
		int ans=2147483647,nn=n;
		mst(use);
		while(nn>1){
			MAS(nn);
			int x=line[top-1],y=line[top-2];
			miz(ans,dis[x]);
			use[x]=1;
			for(node *tmp=h[x].next;tmp;tmp=tmp->next)
				if(tmp->p!=y){
					add(y,tmp->p,conn[x][tmp->p]);
					add(tmp->p,y,conn[x][tmp->p]);
				}
			nn--;
		}
		printf("%d\n",ans);
	}
}
