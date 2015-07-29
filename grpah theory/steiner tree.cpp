#include <cstdio>
#include <algorithm>
const int N=31,INF=1<<28;
int conn[N][N];
int DP[1<<8][N];
template<class T>inline void miz(T &a,T b){if(a>b)a=b;}
int steiner_tree(int T[],int top,int n){
	for(int k=0;k<n;k++)
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				miz(conn[i][j],conn[i][k]+conn[k][j]);
	for(int i=0;i<(1<<top);i++)
		for(int j=0;j<n;j++)
			DP[i][j]=INF;
	for(int i=0;i<top;i++)
		for(int j=0;j<n;j++)
			DP[1<<i][j]=conn[T[i]][j];
	for(int i=2;i<(1<<top);i++)
		if(i&(i-1)){//__count(i)>1
			for(int j=0;j<n;j++)
				for(int sub=(i-1)&i;sub>0;sub=(sub-1)&i)
					miz(DP[i][j],DP[sub][j]+DP[i^sub][j]);
			for(int j=0;j<n;j++)
				for(int k=0;k<n;k++)
					miz(DP[i][j],DP[i][k]+conn[k][j]);
		}
	int ans=INF;
	for(int i=0;i<n;i++)
		miz(ans,DP[(1<<top)-1][i]);
	return ans;
}
int main(){
	int n,m;
	while(~scanf("%d%d",&n,&m)&&(n||m)){
		for(int i=0;i<n;i++)
			for(int j=i+1;j<n;j++)
				conn[i][j]=conn[j][i]=INF;
		while(m--){
			int cost,x,y;
			scanf("%d%d%d",&x,&y,&cost);
			miz(conn[x][y],cost);
			miz(conn[y][x],cost);
		}
		int k,T[N];
		scanf("%d",&k);
		for(int i=0;i<k;i++)
			scanf("%d",&T[i]);
		printf("%d\n",steiner_tree(T,k,n));
	}
}
