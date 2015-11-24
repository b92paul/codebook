#include<bits/stdc++.h>
using namespace std;
const int T=50;
int pow(long long a,long long b,long long mod){
		long long ans=1,tmp=a;
		while(b){
				if(b&1) ans=(ans*tmp)%mod;
				tmp=(tmp*tmp)%mod;
				b>>=1;
		}
		return ans;
}
bool isPrime(long long n){
		if(n==3||n==2) return true;
		else if(n==1) return false;
		int r=0;
		long long d=n-1;
		while(d%2==0) r++,d/=2;
		for(int t=0;t<T;t++){
				long long a = rand()%(n-3)+2;
				long long x = pow(a,d,n);
				if(x==1||x==n-1) continue;
				bool isReturn=true;
				for(int j=0;j<r-1;j++){
						x=(x*x)%n;
						if(x==1) {return false;}
						if(x==n-1) {
								isReturn = false;
								break;
						}
				}
				if(!isReturn) continue;
				return false;
		}
		return true;
}
int x[100];
int main(){
		int n;
		srand(time(NULL));
		while(scanf("%d",&n)==1) {
				if(!isPrime((long long)n)) puts("NO");
				else puts("YES");
		}
}

