#include <bits/stdc++.h>
#include <ext/rope>
#include<ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;
typedef std::pair<int,int> PII;
typedef tree<int,int,less<int>,rb_tree_tag,tree_order_statistics_node_update> TR;
const int N=100000;
rope<int>a;
int t[N],n;
void _rope(){
	a=rope<int>(t,t+n);
	//operator same as string
}
void _ordered_map(){
	static TR t;
    t.clear();
    int m;scanf("%d",&m);
    while(m--){
		char s[3],x;
		scanf("%s%d",s,&x);
		// query the xth(0-base) key
		if(s[0]=='?')printf("%d\n",t.find_by_order(x)->first);
		else if(s[0]=='I') {
			int y;scanf("%d",&y);
			t[x]=y;
		}
		else if(s[0]=='D') t.erase(x);
	}
}
int main(){
	_ordered_map();
    return 0;
}
