int fail[N];
void KMP(char t[],char p[]) {
	int n=strlen(t),m=strlen(p);
	if(m>n)return;
	for(int i=1,j=fail[0]=-1;i<m;i++){
		while(j>=0 && p[j+1]!=p[i])
			j=fail[j];
		if(p[j+1]==p[i])j++;
		fail[i]=j;
	}
	for(int i=0,j=-1;i<n;i++) {
		while(j>=0 && p[j+1]!=t[i])
			j=fail[j];
		if(p[j+1]==t[i])j++;
		if(j==m-1) {
			printf("p occur at %d\n",i-m+1);
			j=fail[j];
		}
	}
}
