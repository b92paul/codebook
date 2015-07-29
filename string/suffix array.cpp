#include <bits/stdc++.h>
const int MAX=200001;
char s[MAX];
int SA[MAX],A[MAX],B[MAX],*r1=A,*r2=B,h,len;
void swap(){int *tmp=r1;r1=r2;r2=tmp;}
bool cmp(int i,int j){return
(r1[i]<r1[j])||(r1[i]==r1[j]&&r1[i+h]<r1[j+h]);}
int main(){
	gets(s);
	len=strlen(s)+1;
	for(int i=0;i<len;i++)SA[i]=i,r1[i]=s[i];
	for(;h<=len;){
		std::sort(SA,SA+len,cmp);
		for(int i=0,j=0;i<len;i++){
			if(i&&cmp(SA[i-1],SA[i]))j++;
			r2[SA[i]]=j;
		}
		swap();
		h+=h?h:1;
	}
	for(int i=1;i<len;i++,puts(""))
		for(int j=SA[i];j<len;j++)
			printf("%c",s[j]);
}
