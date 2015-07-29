//link cut tree with treap
//by david942j
#include <bits/stdc++.h>
const int N=100100;
struct node{
	int pos,sum,val,hval;
	node *L,*R,*par;
	node(){pos=val=sum=0;}
	node(int _pos,node *p,int v,int h,node *l,node *r){pos=_pos;hval=h;par=p;val=v;L=l;R=r;sum=v;}
	inline void update(){
		sum=L->sum+R->sum+val;
	}
	void print(){
		printf("node pos=%d, sum=%d\n",pos,sum);
	}
}*nil,*map[N];
int n;
int heap[N],par[N],val[N];
int real[N];
void init(){
	nil=new node();
	nil->par=nil->L=nil->R=nil;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		heap[i] = i;
	std::random_shuffle(heap+1,heap+n+1);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&par[i],&val[i]);
		map[i]=new node(i,nil,val[i],heap[i],nil,nil);
		real[i]=0;
	}
}
void changeval(int x,int v){
	node *now = map[x];
	for(now->val=v;now!=nil;now=now->par)
		now->update();
}
node *findroot(node *now){
	while(now->par!=nil)now=now->par;
	return now;
}
node* merge(node *a,node *b){
	if(a==nil)return b;
	if(b==nil)return a;
	if(a->hval > b->hval){
		a->R=merge(a->R,b);
		a->R->par=a;
		a->update();
		return a;
	}
	else{
		b->L=merge(a,b->L);
		b->L->par=b;
		b->update();
		return b;
	}
}
int LR[N];
void split(node* now,node *&a,node *&b){
	if(LR[now->pos]==-1){
		a=now->L;
		now->L=nil;
		now->update();
		b=now;
		return;
	}
	if(LR[now->pos]){
		split(now->R,now->R,b);
		now->update();
		now->R->par=now;
		a=now;
	}
	else{
		split(now->L,a,now->L);
		now->update();
		now->L->par=now;
		b=now;
	}
}
void cut(node *now,node *&a,node *&b){
	node *x=now->par;
	LR[now->pos]=-1;
	while(x!=nil){
		LR[x->pos] = (x->R==now);
		now=x;
		x=now->par;
	}
	split(now,a,b);
	a->par=b->par=nil;
}
void changepar(int x,int y){
	node *a=nil,*b=nil;
	if(real[par[x]]!=x)
		;//b=findroot(map[x]);
	else{
		cut(map[x],a,b);
		real[par[x]]=0;
	}
	par[x]=y;
}
node *head(node *now){
	while(now->L!=nil)now=now->L;
	return now;
}
void expose(node *x){
	x=findroot(x);
	node *h=head(x);
	while(par[h->pos]!=0){
		int &r=real[par[h->pos]];
		if(r==0){
			r=h->pos;
			x=merge(findroot(map[par[h->pos]]),x);
			h=head(x);
		}
		else{
			node *a=nil,*b=nil;
			cut(map[r],a,b);
			r=h->pos;
			x=merge(a,x);
			h=head(x);
		}
	}
}
void querylength(int u,int v){
	//printf("query %d %d\n",u,v);
	node *x=map[u],*y=map[v],*a=nil,*b=nil,*c=nil;
	expose(x);
	expose(y);
	if(findroot(x)==findroot(y)){
		cut(y,a,b);
		int sum1=b->sum;
		merge(a,b);
		cut(x,a,b);
		int sum2=b->sum;
		merge(a,b);
		if(sum1>sum2)
			printf("%d\n",sum1-sum2+x->val);
		else printf("%d\n",sum2-sum1+y->val);
	}
	else{
		node *lca=map[par[head(findroot(x))->pos]];
		//lca->print();
		cut(lca,a,b);
		cut(y,b,c);
		int sum1=b->sum+y->val;
		b=merge(a,b);
		merge(b,c);
		cut(x,a,b);
		printf("%d\n",a->sum+x->val+sum1);
		merge(a,b);
	}
}
void solve(){
	int m,t,x,y;
	scanf("%d",&m);
	while(m--){
		scanf("%d%d%d",&t,&x,&y);
		if(t==1)
			querylength(x,y);
		else if(t==2)
			changeval(x,y);
		else
			changepar(x,y);
	}
}
int main(){
	init();
	solve();
}
