// SuffixAutomation
// each node is effectively an end-set, there are at most 2L-1 nodes.
// the end-set corresponding to a nodes parent is always its supet-set
// primary edges form tree, (reversed) par link form a (different) tree.

const int N = 1e6+10;
class State {
public:
    int len;
    State *par,*go[26];
    State(int _len=0):len(_len) {
        memset(go,0,sizeof(go));
    }
}Pool[2*N];

class SuffixAutomation {
public:
    State root,*last,* phead;
    SuffixAutomation() {init();}
    void init() {
				phead = Pool;
        root.par=NULL; root.len=0;last=&root;
    }
    void extend(int w) {
        State *cp=last;
        State *np=new (phead++) State(cp->len+1);
        while(cp && cp->go[w]==NULL) {
            cp->go[w]=np;
            cp=cp->par;
        }
        if(!cp) np->par=&root;
        else {
            State *cq=cp->go[w];
            if(cq->len==cp->len+1) {
                np->par=cq;
            } else {
                State *nq=new (phead++) State(cp->len+1);
                memcpy(nq->go,cq->go,sizeof(cq->go));
                nq->par=cq->par; cq->par=nq; np->par=nq;
                while(cp && cp->go[w]==cq) {
                        cp->go[w]=nq;
                        cp=cp->par;
                }
            }
        }
        last=np;
    }
    void extend(char *str) {
        for(int i=0;str[i];i++)
            extend(str[i]-'a');
    }
};
