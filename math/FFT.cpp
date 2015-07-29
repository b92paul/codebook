#include <bits/stdc++.h>
using namespace std;
const int S=5,N=1<<20;
typedef long double LD;
const LD pi=acos(-1.0);
struct C{
	LD a,b;
	C(){}
	C(LD _a){a=_a;b=0;}
	C(LD _a,LD _b){a=_a;b=_b;}
	LD& real(){return a;}
	inline C operator*(const C &A)const{
		return C(a*A.a-b*A.b,a*A.b+b*A.a);
	}
	inline C operator-(const C &A)const{
		return C(a-A.a,b-A.b);
	}
	inline void operator+=(const C &A){
		a+=A.a;b+=A.b;
	}
	inline C operator/(const double &N)const{
		return C(a/N,b/N);
	}
};
char s[N+10],c[N+10];
C x[N+10],y[N+10],X[N+10],Y[N+10];
long long ans[N];
void change(char s[],C x[]){
	int n=strlen(s),top=0;
	for(int i=0;i<n;i++){
		for(int j=min(i+S-1,n-1);j>=i;j--)
			x[top].real()=x[top].real()*10+s[n-j-1]-'0';
		top++;
		i+=S-1;
	}
}
void FFT(C x[],int n,int s,C X[],const int &k){
	if(n==1){
		X[0]=x[0];
		return ;
	}
	n>>=1;
	FFT(x,n,s<<1,X,k);
	FFT(x+s,n,s<<1,X+n,k);
	double w=-pi*k/n;
	for(int i=n-1;i>=0;i--){
		C off=X[i+n]*C(cos(w*i),sin(w*i));
		X[i+n]=X[i]-off;
		X[i]+=off;
	}
}
int main(){// calc (Bigint)s[]*c[], LD->D or LL->int to avoid TLE
	int T;scanf("%d",&T);
	while(T--){
		scanf("%s%s",s,c);
		int N=1<<(32-__builtin_clz((strlen(s)+strlen(c))/S+1));
		if(N>(1<<20))
			N=1<<20;
		for(int i=0;i<N;i++)
			x[i]=y[i]=0;
		change(s,x);
		change(c,y);
		FFT(x,N,1,X,1);
		FFT(y,N,1,Y,1);
		for(int i=0;i<N;i++)
			X[i]=(X[i]*Y[i])/(double)N;
		FFT(X,N,1,x,-1);
		for(int i=0;i<N;i++)
			ans[i]=x[i].real()+1e-1;
		for(int i=0;i<N;i++){
			ans[i+1]+=ans[i]/100000;
			ans[i]%=100000;
		}
		int last=N-1;
		while(last>=1&&ans[last]==0)last--;
		printf("%lld",ans[last]);
		for(int i=last-1;i>=0;i--)
			printf("%05lld",ans[i]);
		puts("");
	}
}
