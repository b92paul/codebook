struct SAIS{
	static const int N=100100;
	//S[n-1] must be the smallest character
	//MAX alphabet must < N
	int S[N*2],SA[N*2],hei[N];// hei[i]=maxlen of SA[i],SA[i-1]
	bool _iss[N*2];
	int _p[N*2],_pb[N*2],cnt[N],qe[N];
	void build(int/*char*/ s[],int n){
		for(int i=0;i<n;i++)S[i]=s[i];
		suffixArray(n);
		//mkhei(n);
	}
	inline int operator[](int i){return SA[i];}
	void isort(int n,int *s,int *sa,bool iss[],int p[],int pc){
		int a=0,i;
		for(int i=0;i<n;i++)a=max(a,s[i]);a++;
		memset(cnt,0,sizeof(int)*a);
		for(int i=0;i<n;i++)cnt[s[i]]++;
		qe[0]=cnt[0];for(int i=1;i<a;i++)qe[i]=qe[i-1]+cnt[i];
		memset(sa,-1,sizeof(int)*n);
		for(int i=pc-1;i>=0;i--)sa[--qe[s[p[i]]]]=p[i];
		qe[0]=0;for(int i=1;i<a;i++)qe[i]=qe[i-1]+cnt[i-1];
		for(int i=0;i<n;i++)if(sa[i]>0 && !iss[sa[i]-1])sa[qe[s[sa[i]-1]]++]=sa[i]-1;
		qe[0]=cnt[0];for(int i=1;i<a;i++)qe[i]=qe[i-1]+cnt[i];
		for(int i=n-1;i>=0;i--)if(sa[i]>0&&iss[sa[i]-1])sa[--qe[s[sa[i]-1]]]=sa[i]-1;
	}
	bool eq(int *s,bool iss[],int pp[],int pb[],int pc,int x,int p){
		if(pb[p]==pc-1 || pb[x]==pc-1 || pp[pb[p]+1]-p!=pp[pb[x]+1]-x)return 0;
		for(int j=0;j<=pp[pb[p]+1]-p;j++)if(s[j+p]!=s[j+x]||iss[j+p]!=iss[j+x])return 0;
		return 1;
	}
	void suffixArray(int n,int a1=0){
		int *s=S+a1,*sa=SA+a1,*pp=_p+a1,*pb=_pb+a1,pc=0;
		bool *iss=_iss+a1;
		iss[n-1]=1;
		for(int i=n-2;i>=0;i--)iss[i]=s[i]<s[i+1]||(s[i]==s[i+1]&&iss[i+1]);
		for(int i=1;i<n;i++)if(iss[i]&&!iss[i-1])pp[pb[i]=pc++]=i;
		isort(n,s,sa,iss,pp,pc);
		int p=-1,c=-1;
		for(int i=0;i<n;i++){
			int x=sa[i];
			if(x&&iss[x]&&!iss[x-1]){
				if(p==-1||!eq(s,iss,pp,pb,pc,x,p))c++;
				s[n+pb[p=x]]=c;
			}
		}
		if(c==pc-1)for(int i=0;i<pc;i++)sa[n+s[n+i]]=i;
		else suffixArray(pc,a1+n);
		for(int i=0;i<pc;i++)pb[i]=pp[sa[n+i]];
		isort(n,s,sa,iss,pb,pc);
	}
	void mkhei(int n){
        static int r[N];
        for(int i=0;i<n;i++) r[SA[i]] = i;
        hei[0] = 0;
        for(int i=0;i<n;i++)if(r[i]) {
            hei[r[i]] = i>0 ? max(hei[r[i-1]] - 1, 0) : 0;
            while(S[i+hei[r[i]]] == S[SA[r[i]-1]+hei[r[i]]]) hei[r[i]]++;
        }
    }
}sa;
int main(){
	while(gets(s)){
		int n=strlen(s);
		sa.build(s,n+1);
		FOR1(i,n)
			printf("%d\n",sa[i]);
	}
}
