#include <bits/stdc++.h>
const int N=13,hash=999991;
const long long mod=1125899906842624LL;
typedef struct node{long long val;int p;struct node *next;}node;
typedef struct unit{char c[13];int p;struct unit *next;}unit;
unit h[hash];
node H[2][hash];
std::queue<int>Q[2];
int m;
char map[N][N];
bool ok(int n){
	int S[20],stop=0;
	for(;n;n>>=2){
		if(!(n&3))continue;
		if((n&3)==1)S[stop++]=1;
		else if(stop==0)return false;
		else stop--;
	}
	if(stop)return false;
	return true;
}
void DFS(int now,int k){
	if(k==0){
		if(ok(now)){
			unit *tmp=new unit;
			tmp->p=now;tmp->next=h[now%hash].next;
			h[now%hash].next=tmp;
			int S[20],stop=0,j=0;
			for(;now;now>>=2,j++){
				if(!(now&3))continue;
				if((now&3)==1)S[stop++]=j;
				else{
					tmp->c[j]=S[stop-1];
					tmp->c[S[stop-1]]=j;
					stop--;
				}
			}
		}
		return;
	}
	DFS(now<<2,k-1);
	DFS((now<<2)+1,k-1);
	DFS((now<<2)+2,k-1);
}
inline void add(int x,int y,long long c,node H[]){
	node *tmp=new node;
	tmp->p=y;tmp->val=c;
	tmp->next=H[x].next;
	H[x].next=tmp;
}
inline int C(int p,int j){return p<<(2*j);}
inline int z(int x,int j){return (x>>(2*j))&3;}
inline void flagnize(int y,long long val,node H[],bool f){
	for(node *tmp=H[y%hash].next;tmp;tmp=tmp->next)
		if(tmp->p==y){
			tmp->val+=val;
			if(tmp->val>=mod)tmp->val-=mod;
			return;
		}
	add(y%hash,y,val,H);
	Q[f].push(y);
}
long long get(int x,node H[]){
	for(node *tmp=H[x%hash].next;tmp;tmp=tmp->next)
		if(tmp->p==x)return tmp->val;
	return 0;
}
int cor(int x,int j){
	for(unit *tmp=h[x%hash].next;tmp!=NULL;tmp=tmp->next)
		if(tmp->p==x)
			return tmp->c[j];
}
void del(int x,node H[]){
	for(node *tmp=&H[x%hash];tmp->next!=NULL;tmp=tmp->next)
		if(tmp->next->p==x){
			node *tmp2=tmp->next;
			tmp->next=tmp2->next;
			delete tmp2;
			return;
		}
}
int main(){
	DFS(0,13);
	for(int i=0;i<hash;i++)H[0][i].next=H[1][i].next=NULL;
	int n,lastx,lasty;
	while(~scanf("%d%d",&n,&m)){
		for(int i=0;i<n;i++)
			scanf("%s",map[i]);
		lastx=-1;lasty=-1;
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				if(map[i][j]=='.')
					lastx=i,lasty=j;
		bool f=0;
		Q[0].push(0);
		add(0,0,1,H[0]);
		for(int i=0;i<n;i++){
			while(!Q[f].empty()){
				int x=Q[f].front();Q[f].pop();
				if(z(x,m)==0)
					flagnize(x<<2,get(x,H[f]),H[!f],!f);
				del(x,H[f]);
			}
			f^=1;
			for(int j=0;j<m;j++){
				if(map[i][j]=='*'){
					while(!Q[f].empty()){
						int x=Q[f].front();Q[f].pop();
						if(!z(x,j)&&!z(x,j+1))
							flagnize(x,get(x,H[f]),H[!f],!f);
						del(x,H[f]);
					}
				}
				else{
					if(i==lastx&&j==lasty){
						while(!Q[f].empty()){
							int x=Q[f].front();Q[f].pop();
							if(z(x,j)==1&&z(x,j+1)==2)
								flagnize(x^C(z(x,j),j)^C(z(x,j+1),j+1),get(x,H[f]),H[!f],!f);
							del(x,H[f]);
						}
						f^=1;
						break;
					}
					while(!Q[f].empty()){
						int x=Q[f].front();Q[f].pop();
						long long v=get(x,H[f]);
						if(!z(x,j)&&!z(x,j+1))
							flagnize(x^C(1,j)^C(2,j+1),v,H[!f],!f);
						else if(!z(x,j)||!z(x,j+1)){
							flagnize(x,v,H[!f],!f);
							flagnize(x^( C( z(x,j) , j ) ^ C( z(x,j) , j+1 ) )^( C( z(x,j+1) , j ) ^ C( z(x,j+1) , j+1 ) ),v,H[!f],!f);
						}
						else if(z(x,j)&z(x,j+1))
							flagnize(x^C(z(x,j),j)^C(z(x,j+1),j+1)^C(3,cor(x,j+2-z(x,j))),v,H[!f],!f);
						else if(z(x,j)==2)
							flagnize(x^C(z(x,j),j)^C(z(x,j+1),j+1),v,H[!f],!f);
						del(x,H[f]);
					}
				}
				f^=1;
			}
			if(i==lastx)break;
		}
		printf("%lld\n",get(0,H[f]));
		while(!Q[0].empty()){int x=Q[0].front();Q[0].pop();del(x,H[0]);}
		while(!Q[1].empty()){int x=Q[1].front();Q[1].pop();del(x,H[1]);}
	}
}
