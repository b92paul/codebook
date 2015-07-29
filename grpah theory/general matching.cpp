const int N=510;
VI G[N];
int fa[N],mh[N];
char color[N];
deque<int>path[N];
queue<int>Q;
int greedy_match(int n)  {
	int ans=0;
	FOR1(i,n)if(mh[i]==0)
		FOR(j,G[i].size())
			if(mh[G[i][j]]==0) {
				mh[G[i][j]]=i;
				mh[i]=G[i][j];
				ans++;
				break;
			}
	return ans;
}
void recordPath(int x,int y,int ba){
	for(int i=ba+1;i<path[x].size();i++){
		int p=path[x][i];
		if(color[p]==1){
			path[p]=path[y];
			path[p].insert(path[p].end(),path[x].rbegin(),path[x].rend()-i);
			color[p]=0;
			Q.push(p);
		}
	}
}
bool findPath(int st,int n){
	while(!Q.empty())Q.pop();
	FOR1(i,n){
		color[i]=-1;
		path[i].clear();
	}
	Q.push(st);
	color[st]=0;
	path[st].pb(st);
	while(!Q.empty()){
		int x=Q.front();Q.pop();
		FOR(i,G[x].size()){
			int y=G[x][i];
			if(mh[y]==y||y==st)continue;
			if(mh[y]==0){
				for(int i=1;i<path[x].size();i+=2){
					mh[path[x][i]]=path[x][i-1];
					mh[path[x][i-1]]=path[x][i];
				}
				mh[x]=y;mh[y]=x;
				return true;
			}
			if(color[y]==-1){
				color[y]=1;
				int &my=mh[y];
				color[my]=0;
				path[my]=path[x];
				path[my].pb(y);
				path[my].pb(my);
				Q.push(my);
			}
			else if(color[y]==0){
				int base=0;
				while(base<path[x].size()&&base<path[y].size()&&path[x][base]==path[y][base])
					base++;
				base--;
				recordPath(x,y,base);
				recordPath(y,x,base);
			}
		}
	}
	return false;
}
int general_match(int n){
	FOR1(i,n)mh[i]=0;
	int ans=greedy_match(n);
	FOR1(i,n)if(mh[i]==0){
		if(findPath(i,n))ans++;
		else mh[i]=i;
	}
	return ans;
}
int main(){
	int n,m;
	RI(n,m);
	FOR1(i,n)G[i].clear();
	while(m--){
		RID(x);RID(y);
		G[x].pb(y);
		G[y].pb(x);
	}
	printf("%d\n",general_match(n));
}

