#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct
{
    int key;
    long off;
} index_S;

typedef struct
{
    index_S *arr;
    int cursize;
    int cntr;
} Mycol;

void initMycol(Mycol *m,int size)
{
    m=malloc(sizeof(Mycol));
    m->arr=(index_S *)malloc(size*sizeof(index_S));
    m->cursize=size;
    m->cntr=0;
};

void insert(Mycol *m, index_S *val)
{
    int x,y;
    x=m->cursize;
    y=m->cntr;
    //printf("\n size - %d    cuse - %d\n",x,y);
    if(x==y)
    {
    //printf("\nexpanding");
        m->cursize=m->cursize*2+1;
        m->arr=(index_S *)realloc(m->arr,m->cursize*sizeof(index_S));
    //printf("\nexpanded\n");
    }
    int c=m->cntr;

    while(c>0 && m->arr[c-1].key>val->key)
    {
        //printf("%d",m->arr[c-1].key);
        m->arr[c]=m->arr[c-1];
        c-=1;
    }
    m->arr[c].key=val->key;
    m->arr[c].off=val->off;
    m->cntr+=1;
};

long delkey(Mycol *m, int val)
{
    int c=m->cntr;
    long tuff=-1;
    while(c>=0 && m->arr[c].key!=val)
    {
        c-=1;
    }
    if(c!=-1)
    {
        tuff=m->arr[c].off;
        while(c<m->cntr)
        {
            m->arr[c]=m->arr[c+1];
            c+=1;
        }
        m->cntr-=1;
    }
    return tuff;
};

int bincheck(Mycol *m,int SID)
{
    int fi=0;
    int la=m->cntr;
    if(la==0)
    {
        return -1;
    }
    int flg=-1;
    int mid=0;
    while(la-fi>1)
    {
        mid=(fi+la)/2;
        if(m->arr[mid].key==SID)
        {
            flg=mid;
            break;
        }
        else if(m->arr[mid].key>SID)
        {
            la=mid;
        }
        else
        {
            fi=mid;
        }
    }

    if(m->arr[fi].key==SID)
    {
        flg=fi;
    }
    else if(m->arr[la].key==SID)
    {
        flg=la;
    }
    return flg;
};

void painter(Mycol *m)
{
    printf("Index:\n");
    int k=m->cntr;
    int i=0;
    while(i<k)
    {
        printf("key=%d: ",m->arr[i].key);
        printf(" offset=%ld\n",m->arr[i].off);
        i+=1;
    }
}

//# availability list
typedef struct
{
    int siz;
    long off;
} avail_S;


typedef struct
{
    avail_S *arr;
    int cursize;
    int cntr;
} Myavl;

long ckavl(Myavl *m,int siz)
{
    long toff=-1;
    int c=m->cntr;
    int p=0;
    while(p<c)
    {
        if(m->arr[p].siz>=siz)
        {
            toff=m->arr[p].off;
            return toff;
        }
        p+=1;
    }
    return toff;
};

void initMyavl(Myavl *m,int size)
{
    //m=malloc(sizeof(Myavl));
    m->arr=(avail_S *)malloc(size*sizeof(avail_S));
    m->cursize=size;
    m->cntr=0;
};

void insrtAvl(Myavl *m, avail_S *val)
{
    int x,y;
    x=m->cursize;
    y=m->cntr;
    if(x==y)
    {
        m->cursize=m->cursize*2+1;
        m->arr=(avail_S *)realloc(m->arr,m->cursize*sizeof(avail_S));
    }
    int c=m->cntr;
    m->arr[c].siz=val->siz;
    m->arr[c].off=val->off;
    m->cntr+=1;
};

int delavl(Myavl *m, int hole)
{
    int tz=-1;
    int c=m->cntr;
    int p=0;
    while(p<c && m->arr[p].siz<hole)
    {
        p+=1;
    }
    if(p!=c)
    {
        tz=m->arr[p].siz-hole;
    }
    if(p==c-1)
    {
        m->cntr-=1;
    }
    else if(p<c)
    {
        while(p<m->cntr)
        {
            m->arr[p]=m->arr[p+1];
            p+=1;
        }
        m->cntr-=1;
    }
    return tz;
};

int pavl(Myavl *m)
{
    printf("Availability:\n");
    int k=m->cntr;
    int i=0;
    int hsum=0;
    while(i<k)
    {
        printf("size=%d: ",m->arr[i].siz);
        hsum+=m->arr[i].siz;
        printf("offset=%ld\n",m->arr[i].off);
        i+=1;
    }
    return hsum;
}

int cmpfunbf(const void * a, const void *b)
{
    avail_S *x,*y;
    x=(avail_S*)a;
    y=(avail_S*)b;
//printf("%d \t",x->siz);
    if(x->siz==y->siz)
    {
        return (*(&(x->off))-*(&(y->off)));
    }
    else
    {
        return (*(&(x->siz))-*(&(y->siz)));
    }
}

int mycmpfun(const void * a, const void *b)
{
    avail_S *x,*y;
    x=(avail_S*)a;
    y=(avail_S*)b;
    return (*(&(x->off))-*(&(y->off)));
}

int cmpfunwf(const void * a, const void *b)
{
    avail_S *x,*y;
    x=(avail_S*)a;
    y=(avail_S*)b;
//printf("%d \t",x->siz);
    if(x->siz==y->siz)
    {
        return (*(&(x->off))-*(&(y->off)));
    }
    else
    {
        return (*(&(y->siz))-*(&(x->siz)));
    }
}

int merger(Myavl *m)
{

    int size=m->cntr;
    int c=0;
    int flg=-1;
    for(c=0; c<size-1; c++)
    {
        if(m->arr[c].off+m->arr[c].siz==m->arr[c+1].off)
        {
            m->arr[c].siz+=m->arr[c+1].siz;
            m->cntr-=1;
            flg=0;
            break;
        }
    }
    c+=1;
    while(c<size)
    {
        m->arr[c]=m->arr[c+1];
        c+=1;
    }
    //printf("curz    %d\n",m->cntr);
    return flg;
}

void handler(Myavl *av,int method)
{
    int flg=0;
    int sz=0;
    switch(method)
    {
    case 1://Best-fit
        sz=av->cntr;
        qsort(av->arr,sz,(sizeof(avail_S)),cmpfunbf);

        break;
    case 2://Worst-fit
        sz=av->cntr;
        qsort(av->arr,sz,(sizeof(avail_S)),cmpfunwf);

        break;
    case 3://My-fit with merge
        sz=av->cntr;
        qsort(av->arr,sz,(sizeof(avail_S)),mycmpfun);
        while(merger(av)!=-1)
        {
            ;
        }

        break;
    default:
        printf("Invalid option selected");
        break;
    }
};
//##################The following function was taken from Stackoverflow#####################
int number(char *str)
{
    int result;
    int puiss;

    result = 0;
    puiss = 1;
    while(('-'==(*str))||((*str)=='+'))
    {
        if (*str=='-')
            puiss=puiss * -1;
        str++;
    }
    while((*str>='0')&&(*str<='9'))
    {
        result=(result*10)+((*str)-'0');
        str++;
    }
    return (result*puiss);
}

int main()
{
    index_S sin;
    int s=0,e=0,z=0;
    long offs=0;
    Mycol *m=malloc(sizeof(Mycol));
    initMycol(m,1);
    int key=0;
    char record[50];
    //printf("AVAIL checking");
    Myavl *ma=malloc(sizeof(Myavl));
    initMyavl(ma,1);
    avail_S as1;
    FILE *fpdb;
    FILE *fp;
    fp=fopen("input-01.txt","r");//INSERT FILENAME HERE
    fpdb=fopen("output.db","rb");

    if(fpdb==NULL)
    {
        fpdb=fopen("output.db","w+b");
    }
    else
    {
        fpdb=fopen("output.db","r+b");
    }

    if(fp == NULL)
    {
        printf("File doesn't exist");
        exit(EXIT_FAILURE);
    }

    FILE *out = fopen("index.bin", "rb");
    if(out!=NULL)
    {
        int culocal=0;
        long ctlocal=0;
        while(fread(&culocal,1,sizeof(int),out)!=0)
        {
            fread(&ctlocal,1,sizeof(long),out);
            sin.key=culocal;
            sin.off=ctlocal;
            insert(m,&sin);
        }
        fclose(out);
    }

    FILE *favl = fopen("avl.bin", "rb");
    if(favl!=NULL)
    {
        //printf("old file found for a-list");
        long ctlocal=0;
        int culocal=0;
        //fread(&culocal,1,sizeof(int),out);
        while(fread(&culocal,1,sizeof(int),favl)!=0)
        {
            fread(&ctlocal,1,sizeof(long),favl);
            as1.off=ctlocal;
            as1.siz=culocal;
            insrtAvl(ma,&as1);
        }
        fclose(favl);
    }

    char mline[200];
    //FILE *out, *favl;
    while((fscanf(fp,"%s",&mline))!=-1)
    {
        char fir=mline[0];

        switch(fir)
        {
        case 'a':
            fscanf(fp,"%s",&record);
            key=number(record);
            fscanf(fp,"%s",&record);
            s=strlen(record);
            offs=ftell(fpdb);
            if(bincheck(m,key)==-1)
            {
                if(ckavl(ma,s+sizeof(int))!=-1)
                {

                    long troff=0;
                    troff=ckavl(ma,s+sizeof(int));
                    int tez=0;
                    tez=delavl(ma,s+sizeof(int));
                    fseek(fpdb,troff*sizeof(char),SEEK_SET);
                    //printf("Writing %d , %s to hole of size %d at offset %ld\n",s,record,tez,troff);
                    fwrite(&s,1,sizeof(int),fpdb);
                    fwrite(&record,s,sizeof(char),fpdb);
                    sin.key=key;
                    sin.off=troff;
                    insert(m,&sin);
                    if(tez!=0)
                    {
                        as1.off=troff+s+sizeof(int);
                        as1.siz=tez;
                        insrtAvl(ma,&as1);
                    }
                    fseek(fpdb,0,SEEK_END);
                }
                else
                {
                    //printf("hole not found, appending to end of list\n");
                    fwrite(&s,1,sizeof(int),fpdb);
                    fwrite(&record,s,sizeof(char),fpdb);
                    sin.key=key;
                    sin.off=offs;
                    //printf("%d   %ld\n",key,offs);
                    insert(m,&sin);
                }
            }
            else
            {
                printf("Record with SID=%d exists\n",key);
            }
            break;

        case 'f':
            fscanf(fp,"%s",&record);
            key=number(record);
            z=bincheck(m,key);
            if(z!=-1)
            {
                char stemp[200];
                int ltemp=0;
                //printf("Record found at position %d,  offset %ld\n",z,m->arr[z].off);
                fseek(fpdb,m->arr[z].off*sizeof(char),SEEK_SET);
                fread(&ltemp,sizeof(int),1,fpdb);
                fread(&stemp,sizeof(char),ltemp,fpdb);
                stemp[ltemp]='\0';
                printf("%s\n",stemp);
                fseek(fpdb,0,SEEK_END);
            }
            else
            {
                printf("No record with SID=%d exists\n",key);
            }
            break;

        case 'd':
            fscanf(fp,"%s",&record);
            key=number(record);
            z=bincheck(m,key);
            if(z!=-1)
            {
                fseek(fpdb,m->arr[z].off*sizeof(char),SEEK_SET);
                fread(&as1.siz,sizeof(int),1,fpdb);
                as1.off=delkey(m,key);
                as1.siz+=sizeof(int);
                fseek(fpdb,0,SEEK_END);
                insrtAvl(ma,&as1);
                handler(ma,1); //Change the second argument to 2 or 3 for bestfit and mergefit
            }
            else
            {
                printf("No record with SID=%d exists\n",key);
            }
            break;

        case 'e':


            out= fopen("index.bin", "w");
            int yt=m->cntr;
            int p=0;
            int gloc;
            long hloc;
            while(p<yt)
            {
                gloc=m->arr[p].key;
                hloc=m->arr[p].off;
                fwrite(&gloc,1,sizeof(int),out);
                fwrite(&hloc,1,sizeof(long),out);
                p+=1;
            }
            fclose(out);
            favl = fopen("avl.bin", "w");
            yt=ma->cntr;
            p=0;
            while(p<yt)
            {
                gloc=ma->arr[p].siz;
                hloc=ma->arr[p].off;
                fwrite(&gloc,1,sizeof(int),favl);
                fwrite(&hloc,1,sizeof(long),favl);
                p+=1;
            }
            fclose(favl);
//printf("\n");
            break;

        default:
//printf("\n");
            break;
        }
    }
    fclose(fpdb);
    fclose(fp);
    int hsum=0;
    painter(m);
    hsum=pavl(ma);
    printf("Number of holes: %d\n",ma->cntr);
    printf("Hole space: %d",hsum);

    free(m->arr);
    free(m);
    return 0;
}
