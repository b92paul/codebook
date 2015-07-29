#include <bits/stdc++.h>
using namespace std;
const int N=160;
struct node{
	node *next[27],*fail;
	int idx,cnt;
	int vidx;
	node(int vtop=-1,int _idx=-1){
		for(int i=0;i<27;i++)next[i]=NULL;
		fail=NULL;
		idx=_idx;cnt=0;
		vidx=vtop;
	}
}*root,v[N*70];
char s[N][80],tar[1000010];
int stov[N];
int vtop;
node* newnode(){
	v[vtop]=node(vtop);vtop++;
	return &v[vtop-1];
}
void insert(char s[],int idx){
	node *now=root;
	int n=strlen(s);
	for(int i=0;i<n;i++){
		if(now->next[s[i]-'a']==NULL)
			now->next[s[i]-'a']=newnode();
		now=now->next[s[i]-'a'];
	}
	stov[idx]=now->vidx;
	if(now->idx==-1)
		now->idx=idx;
	else
		stov[idx]=now->vidx;
}
queue<node*>Q;
void make_fail(){
	while(!Q.empty())Q.pop();
	root ->fail=root;
	Q.push(root);
	while(!Q.empty()){
		node *now=Q.front();Q.pop();
		for(int i=0;i<26;i++)
			if(now->next[i]!=NULL){
				node *tmp=now;
				bool ok=false;
				while(tmp!=root){
					tmp=tmp->fail;
					if(tmp->next[i]!=NULL){
						now->next[i]->fail=tmp->next[i];
						ok=true;
						break;
					}
				}
				if(!ok)now->next[i]->fail=root;
				Q.push(now->next[i]);
			}
	}
}
void update(node *now){
	if(now==root)return;
	now->cnt++;
	update(now->fail);
}
void string_match(char s[]){
	int n=strlen(s);
	s[n++]='z'+1;
	node *now=root;
	for(int i=0;i<n;i++){
		while(now!=root&&now->next[s[i] -'a']==NULL)
			now=now->fail;
		if(now->next[s[i]-'a']!=NULL)
			now=now->next[s[i]-'a'];
		update(now);
	}
}
int main(){
	int n;
	while(~scanf("%d",&n)&&n){
		vtop=0;
		root=newnode();
		for(int i=0;i<n;i++){
			scanf("%s",s[i]);
			insert(s[i],i);
		}
		make_fail();
		scanf("%s",tar);
		string_match(tar);
		int Max=0;
		for(int i=0;i<n;i++)
			if(Max<v[stov[i]].cnt)
				Max=v[stov[i]].cnt;
		printf("%d\n",Max);
		for(int i=0;i<n;i++)
			if(Max==v[stov[i]].cnt)
				printf("%s\n",s[i]);
	}
}
