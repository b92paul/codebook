//xor of n ArithSeq
#include <cstdio>
const int N=200100;
LL A[N],B[N],C[N];
int bit(int a,int s){
	return (a>>s) &1;
}
int K(LL a,LL b,LL c){
	return (b-a)/c;
}
LL fun(LL x,LL a,LL b,LL n){
	LL res=0,k=(a/b)&1;
	if(n<0)return 0;
	a%=b;
	if(n&1)
		res=((n+1>>1)&1);
	else
		res=((n/2)&1);
	res=(res*k)&1;
	if(a==0){
		res+=((x/b)&1)*((n+1)&1);
        return res&1;
	}
	res+=((x/b)&1)+(n&1)*(((x+n*a)/b)&1)+fun(b-x%b-1,b,a,(x+n*a)/b-x/b-1);
	return res&1;
}
int main(){
	int n;
	while(~scanf("%d",&n)){
		for(int i=0;i<n;i++){
			int a,b,c;
			scanf("%d%d%d",&a,&b,&c);
			A[i]=a;//first
			B[i]=b;//last
			C[i]=c;//diff
		}
		unsigned ans=0;
		for(int i=0;i<n;i++){
			unsigned x=0;
			LL add=0;
			for(int j=0;j<32;j++)
				x^=fun(A[i],C[i],1LL<<j,K(A[i],B[i],C[i]))<<j;
			ans^=x;
		}
		printf("%u\n",ans);
	}
}
