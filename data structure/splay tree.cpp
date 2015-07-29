#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
const int N=500010;
inline int max(int a,int b){return a>b?a:b;}
struct node{
	int val,sum,maxL,maxR,maxS,size;
	bool rev,same;
	node *ch[2],*pre;
}tree[N],*root,*Nil;
node* newnode(int val){
	node *tmp=new node;
	tmp->val=tmp->sum=tmp->maxL=tmp->maxR=tmp->maxS=val;
	tmp->rev=tmp->same=false;
	tmp->pre=tmp->ch[0]=tmp->ch[1]=Nil;
	return tmp;
}
void make_same(node *now,int c){
	if(now==Nil)return;
	now->same=true;now->val=c;
	now->sum=c*now->size;
    now->maxL=now->maxR=now->maxS=max(now->sum,c);
}
void rev(node *now){
	if(now==Nil)return;
	swap(now->ch[0],now->ch[1]);
	swap(now->maxL,now->maxR);
	now->rev^=1;
}
void sign_down(node *now){
	if(now==Nil)return;
	if(now->same)
	{now->same=false;make_same(now->ch[0],now->val);make_same(now->ch[1],now->val);}
	if(now->rev)
	{now->rev=false;rev(now->ch[0]);rev(now->ch[1]);}
}
void update(node *now){
	node *L=now->ch[0],*R=now->ch[1];
	now->size=L->size+R->size+1;
	now->sum=L->sum+R->sum+now->val;
	now->maxL=max(L->maxL,L->sum+max(0,R->maxL)+now->val);
	now->maxR=max(R->maxR,R->sum+max(0,L->maxR)+now->val);
	now->maxS=max(max(L->maxS,R->maxS),max(0,L->maxR)+now->val+max(0,R->maxL));
}
void ror(node *now,int p) {// p=0 left ror
	node *par=now->pre;
	sign_down(par);sign_down(now);
	par->ch[!p]=now->ch[p];
	if(now->ch[p]!=Nil)now->ch[p]->pre=par;
	now->ch[p]=par;
	now->pre=par->pre;
	if(now->pre!=Nil)now->pre->ch[now->pre->ch[1]==par]=now;
	par->pre=now;
	if(par==root)root=now;
	update(par);
}
void splay(node *now,node *fa){
	for(sign_down(now);now->pre!=fa;)
		if(now->pre->pre)
			ror(now,now->pre->ch[0]==now);
		else{
			node *par=now->pre,*gpar=par->pre;
			if(gpar->ch[0]==par)
				if(par->ch[0]==now)
					{ror(par,1);ror(now,1);}
				else
					{ror(now,0);ror(now,1);}
			else
				if(par->ch[0]==now)
					{ror(par,0);ror(now,0);}
				else
					{ror(now,1);ror(now,1);}
		}
	update(now);
}
void find(int k,node *fa){
	node *tmp=root;
	while(1){
		sign_down(tmp);
		int s=tmp->ch[0]->size;
		if(s+1==k)break;
		if(k<=s)tmp=tmp->ch[0];
		else {
			tmp=tmp->ch[1];
			k-=s+1;
		}
	}
	splay(tmp,fa);
}
int t[N];
node* make_tree(int L,int R,node *par){
	if(L>R)return Nil;
	int mid=L+R>>1;
	node *tmp=newnode(t[mid]);
	tmp->ch[0]=make_tree(L,mid-1,tmp);
	tmp->ch[1]=make_tree(mid+1,R,tmp);
	tmp->pre=par;update(tmp);
	return tmp;
}
void Insert(int pos,int n){
	for(int i=1;i<=n;i++)scanf("%d",&t[i]);
	find(pos,Nil);find(pos+1,root);
	root->ch[1]->ch[0]=make_tree(1,n,root->ch[1]);
	splay(root->ch[1]->ch[0], Nil);
}
void del(node *now){
	if(now==Nil)return;
	del(now->ch[0]);
	del(now->ch[1]);
	delete now;
}
int main(){
	int n,m,pos,tot,c;
	char s[30];
	Nil = newnode(-(1<<20));Nil->size=Nil->sum=0;
	root = newnode(-(1<<20));
	root->ch[1]=newnode(-(1<<20));
	root->ch[1]->pre=root;
	update(root);
	scanf("%d%d",&n,&m);
	Insert(1,n);
	while(m--){
		scanf("%s",s);
		if(s[2]!='X')scanf("%d%d",&pos,&tot);
		if(s[2]=='K'){//[pos,pos+tot-1] = c
			scanf("%d",&c);
			find(pos,Nil);find(pos+tot+1,root);
			make_same(root->ch[1]->ch[0],c);splay(root->ch[1],Nil);
		}
		if(s[0]=='I')Insert(pos+1,tot);
		else if(s[0]=='D'){//delete
			find(pos,Nil);find(pos+tot+1,root);
			del(root->ch[1]->ch[0]);
			root->ch[1]->ch[0]=Nil;
			splay(root->ch[1],Nil);
		}
		else if(s[0]=='R'){//reverse
			find(pos,Nil);find(pos+tot+1,root);
			rev(root->ch[1]->ch[0]);splay(root->ch[1],Nil);
		}
		else if(s[0]=='G')//get-sum
		{
			find(pos,Nil);find(pos+tot+1,root);
			printf("%d\n",root->ch[1]->ch[0]->sum);
		}
		else if(s[2]=='X')//get-all-max_subsum
			printf("%d\n",root->maxS);
	}
}

