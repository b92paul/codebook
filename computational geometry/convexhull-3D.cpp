#include <bits/stdc++.h>
using namespace std;
typedef double LD;
const int N=110;
const LD EPS=1e-7;
int flag[N][N],n;
struct point{double x,y,z;
	point operator-(point &b)const
	{return (point){x-b.x,y-b.y,z-b.z};}
	LD len()const{return sqrt(x*x+y*y+z*z);}
};
struct face{int a,b,c;};
point t[N];
double dot(point a, point b)
{return a.x*b.x+a.y*b.y+a.z*b.z;}
point cross(point a, point b)
{return (point){a.y*b.z-b.y*a.z,a.z*b.x-b.z*a.x,a.x*b.y-b.x*a.y};}
point ver(face f)
{return cross(t[f.b]-t[f.a],t[f.c]-t[f.a]);}
double calc(point a,point b,point c,point d){
	point tmp=cross(d-b,c-b);
	return abs(tmp.x*(a.x-b.x)+tmp.y*(a.y-b.y)+tmp.z*(a.z-b.z));
}
double AREA(point a,point b,point c){
	point tmp=cross(b-a,c-a);
	return tmp.len()*0.5;
}
bool zero(point a){//a.len()<EPS?
	return abs(a.x)<EPS&&abs(a.y)<EPS&&abs(a.z)<EPS;
}
int main(){
	int i,j,w=1;
	while(~scanf("%d",&n)&&n){
		for(i=0;i<n;i++)
			scanf("%lf%lf%lf",&t[i].x,&t[i].y,&t[i].z);
		for(i=1;i<n;i++)
			if(!zero(t[i]-t[0])){swap(t[i],t[1]);break;}
		for(i++;i<n;i++)
			if(!zero(cross(t[1]-t[0],t[i]-t[0]))){swap(t[i],t[2]);break;}
		point tmp=cross(t[0]-t[1],t[2]-t[1]);
		for(i++;i<n;i++)
        	if(abs(dot(tmp,t[0]-t[i]))>EPS){swap(t[i],t[3]);break;}
		std::vector<face>now;
		now.push_back((face){0,1,2});
		now.push_back((face){2,1,0});
		for(i=3;i<n;i++){
			memset(flag,0,sizeof(flag));
			std::vector<face> next;
			for(j=0;j<now.size();j++){
				face& f=now[j];
				double d=dot(t[i]-t[f.a],ver(f));
				if (d<=0.0) next.push_back(f);
	            int ff=0;
				if(d>0.0)ff=1;
				else if(d<0.0)ff=-1;
	            flag[f.a][f.b]=flag[f.b][f.c]=flag[f.c][f.a]=ff;
	        }
			for(j=0;j<now.size();j++){
				face& f=now[j];
				if(flag[f.a][f.b]>0&&flag[f.a][f.b]!=flag[f.b][f.a])
					next.push_back((face){f.a,f.b,i});
				if(flag[f.b][f.c]>0&&flag[f.b][f.c]!=flag[f.c][f.b])
					next.push_back((face){f.b,f.c,i});
				if(flag[f.c][f.a]>0&&flag[f.c][f.a]!=flag[f.a][f.c])
					next.push_back((face){f.c,f.a,i});
	        }
	        now=next;
	    }
	    double volume=0.0;
	    for(i=0;i<now.size();i++){
			if(!now[i].a||!now[i].b||!now[i].c)continue;
			volume+=calc(t[0],t[now[i].a],t[now[i].b],t[now[i].c]);
		}
		//printf("%d\n",now.size());
		printf("%.2lf\n",volume/6.0);
		double area=0.0;
		for(i=0;i<now.size();i++)
			area+=AREA(t[now[i].a],t[now[i].b],t[now[i].c]);
		//printf("%.2lf\n",area);
	}
}
