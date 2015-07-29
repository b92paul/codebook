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
	}//t.order_of_key(int) // 0-base, lower_bound;
}
int main(){
	_ordered_map();
    return 0;
}
//{{TwT
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,
tree_order_statistics_node_update> set_t; typedef __gnu_pbds::priority_queue<int> heap_t; int main() {
    set_t s;
    for ( int i=0; i<5; i++ ) s.insert(10*i); assert(*s.find_by_order(0) == 0); assert(*s.find_by_order(3) == 30); assert(s.find_by_order(5) == s.end()); assert(s.order_of_key(0) == 0); assert(s.order_of_key(30) == 3); assert(s.order_of_key(35) == 4); assert(s.order_of_key(100) == 5);
    heap_t h1,h2;
    for ( int i=1; i<=10; i+=2 ) h1.push(i); for ( int i=2; i<=10; i+=2 ) h2.push(i); assert(h1.size() == 5);
    assert(h1.top() == 9);
    assert(h2.size() == 5);
    assert(h2.top() == 10);
    h1.join(h2);
    assert(h1.size() == 10);
    assert(h1.top() == 10);
    return 0;
}
