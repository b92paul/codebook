//by david942j  
//Bron_Kerbosch algorithm  
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#define lg(x) 31-__builtin_clz(x)
using namespace std;
const int N=31;
int conn[N];
int n,ans;
void Search(int Pv,int Xv){
    if( Pv==0 ){
        if(Xv==0)
            ans++;
        return;
    }
    int B=Pv&~conn[lg(Pv&-Pv)];
    while(B){
        int i=lg(B&-B);
        Search(Pv&conn[i],Xv&conn[i]);
        Pv^=1<<i;
        Xv|=1<<i;
        B^=1<<i;
    }
}
void Bron_Kerbosch(){
    int Pv=(1<<n)-1,Xv=0;
    for(int i=0;i<n;i++){
        Search(Pv&conn[i],Xv&conn[i]);
        Pv^=1<<i;
        Xv|=1<<i;
    }
}
int main(){
    int m,T;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        /*for(int i=0;i<n;i++)
            conn[i]=((1<<n)-1)^(1<<i);*/
        for(int i=0;i<n;i++)conn[i]=0;
		while(m--){
            int x,y;
            scanf("%d%d",&x,&y);
            x--;y--;
            //if(conn[x]&(1<<y)){
                conn[x]|=1<<y;
                conn[y]|=1<<x;
            //}
        }
        ans=0;
        Bron_Kerbosch();
        printf("%d\n",ans);
    }
}
/*
define ^^ intersection
function Search(R,P,X)
	if P.empty() && X.empty()
		record R
		return
	choose a vertex u belongs to P U X
	for v in P\N(u) do
		Search(R U {v}, P^^N(v),X^^N(v))
		P=P\{v}
		X=X U {v}
	end
end

function Bron_Kerbosch(){
	R=0;P=V(G);X=0
    for v in degeneracy order of G {
        Search(R U {v},P^^N(v),X^^N(v));
        P=P\{v};
        X=X U {v};
    }
}
*/
