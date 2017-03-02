#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>

    inline void scanint(int *x)
    {
    	register char c = getchar_unlocked();
    	*x = 0;
    	for(; (c<48)||(c>57);c = getchar_unlocked());
    	for(; (c>47)&&(c<58);c = getchar_unlocked())
    		*x = (int)((((*x)<<1) + ((*x)<<3)) + c - 48);
    }
    inline void printint(int n)
    {
    		char buf[11];
    		buf[10] = '\n';
    		int i = 9;
    		while(n)
    		{
    			buf[i--] = n % 10 + '0';
    			n /= 10;
    		}
    		while(buf[i] != '\n')
    			putchar_unlocked(buf[++i]);
    }
struct timeval start_total_time, end_total_time; /*Algo times*/
struct timeval start_read_time, end_read_time; /* io need 2 timers */
struct timeval start_write_time, end_write_time;
struct timeval start_endtoend_time, end_endtoend_time; /* end to end time*/

struct Point
{
        int x;
        int y;
        int z;
};

struct Edge
{
        int first;
        int second;
};


struct hashNode
{
        struct Point *key;
        int index;
        struct hashNode *next;
};

struct hashMap
{
        int size1;
        struct hashNode **root;
} hashMap1;


int equalsPoint(struct Point *a,struct Point *b)
{
        return (a->x==b->x && a->y==b->y && a->z==b->z);
}

void init_hashMap(int n)
{
        hashMap1.size1 = n;
        hashMap1.root = (struct hashNode **)malloc(n*sizeof(struct hashNode *));
        int i;
        for(i=0;i<n;i++)
        {
                hashMap1.root[i] = NULL;
        }
}

void insertInLinkedList(int listIndex,struct Point *point,int index)
{
                struct hashNode *soonToBeRoot = (struct hashNode *)malloc(sizeof(struct hashNode ));
		soonToBeRoot->next =  hashMap1.root[listIndex];
                hashMap1.root[listIndex] = soonToBeRoot;
                soonToBeRoot->key = point;
                soonToBeRoot->index = index;

}

int searchInLinkedList(int listIndex,struct Point *point)
{
        struct hashNode *root = hashMap1.root[listIndex];

        while(root)
        {
                if(equalsPoint(root->key,point))
                        return root->index;
                root = root -> next ;
        }

        return -1;
}

void insert_hashMap(struct Point *point,int index)
{
        int hashCode = hashFunc(point);
        insertInLinkedList(hashCode%(hashMap1.size1),point,index);
}


int hashFunc(struct Point *p)
{
    int val1 = (p->x*997*661 + p->y*661 + p->z);
    return val1&0x7FFFFFFF;
}

int getIndex(struct Point *point)
{
        int hashCode = hashFunc(point);
        return searchInLinkedList(hashCode%(hashMap1.size1),point);
}


int *parent;

int findRoot(int x)
{
        if(parent[x]==x)
                return x;
        return ( parent[x] = findRoot(parent[x]) );
}

void union1(int x,int y)
{
        int xRoot = findRoot(x);
        int yRoot = findRoot(y);

        if(xRoot>yRoot)
        {
               parent[xRoot]  = yRoot;
        }
        else if(xRoot<yRoot)
        {
                parent[yRoot]  = xRoot; 
        }
}

void beautifyOutputAndPrint(int N,struct Point *points)
{

    int i;
    int *prefixSum1 = (int *)malloc(N*sizeof(int));
    int count1 = 0;
    for(i=0;i<N;i++)
    {
          if(parent[i]==i)
                 prefixSum1[i] = ++count1;
    }
    for(i=0;i<N;i++)
    {
                printint(prefixSum1[findRoot(i)]);
    }

}

int main(int argc,char* argv[])
{
        gettimeofday(&start_endtoend_time,NULL);
        if(argc < 2)
        {
                printf("Input Format: <NumberOfLines>\n");
                exit(1);
        }

        int n,i;
        n = atoi(argv[1]);
        struct Point *points = (struct Point *)malloc(n*sizeof(struct Point));
        struct Edge *edges = (struct Edge *)malloc(6*n*sizeof(struct Edge));
        parent = (int *)malloc(n*sizeof(int));
        init_hashMap(n);
    	int m = -1;

    	gettimeofday(&start_read_time,NULL);
        for(i=0;i<n;i++)
        {
	        scanint(&points[i].x);
		scanint(&points[i].y);
		scanint(&points[i].z);
                /*scanf("%d,%d,%d\n",&points[i].x,&points[i].y,&points[i].z);*/
        }
        gettimeofday(&end_read_time,NULL);

        omp_set_num_threads(omp_get_max_threads());

        gettimeofday(&start_total_time,NULL);

        for(i=0;i<n;i++)
        {
                insert_hashMap(&points[i],i);
		parent[i] = i;
        }

        #pragma omp parallel
        {
                const int ithread = omp_get_thread_num();
                const int nthreads = omp_get_num_threads();
                int start1 = ithread*n/nthreads;
		int end1 = (ithread+1)*n/nthreads;
		int myStart = start1*6;
		int i;
                int index1;

		for(i = start1;i<end1;i++)
		{
			struct Point temp = points[i];
			
			/* changing x co-ordinate*/
			temp.x++;
                	index1 = getIndex(&temp);
                	if(index1 > i )
                	{
                             edges[myStart].first = i;
			     edges[myStart].second = index1;
			     myStart++;
                	}

                	temp.x--;

			temp.x--;
               		index1 = getIndex(&temp);
			if(index1 > i )
                	{
                             edges[myStart].first = i;
			     edges[myStart].second = index1;
			     myStart++;
                	}

			temp.x++;

                        
                        /* changing y co-ordinate*/
			temp.y++;
                	index1 = getIndex(&temp);
                	if(index1 > i )
                	{
                             edges[myStart].first = i;
			     edges[myStart].second = index1;
			     myStart++;
                	}

                	temp.y--;

			temp.y--;
               		index1 = getIndex(&temp);
			if(index1 > i )
                	{
                             edges[myStart].first = i;
			     edges[myStart].second = index1;
			     myStart++;
                	}

			temp.y++;

                       
                        /* changing z co-ordinate*/
			temp.z++;
                	index1 = getIndex(&temp);
                	if(index1 > i )
                	{
                             edges[myStart].first = i;
			     edges[myStart].second = index1;
			     myStart++;
                	}

                	temp.z--;

			temp.z--;
               		index1 = getIndex(&temp);
			if(index1 > i )
                	{
                             edges[myStart].first = i;
			     edges[myStart].second = index1;
			     myStart++;
                	}

		}

		int start2 = start1*6;

		for(i=start2;i<myStart;i++)
		{
			#pragma critical
				union1(edges[i].first,edges[i].second);
		}
        }

        gettimeofday(&end_total_time,NULL);

        gettimeofday(&start_write_time,NULL);
        beautifyOutputAndPrint(n,points);
        gettimeofday(&end_write_time,NULL);

        gettimeofday(&end_endtoend_time,NULL);

        double endtoendTime = ( end_endtoend_time.tv_usec - start_endtoend_time.tv_usec );
        endtoendTime += (end_endtoend_time.tv_sec - start_endtoend_time.tv_sec)*1000000;
        endtoendTime /= 1000000;
        double ioTime = (end_read_time.tv_usec - start_read_time.tv_usec) + (end_read_time.tv_sec - start_read_time.tv_sec)*1000000;
        ioTime += (end_write_time.tv_usec - start_write_time.tv_usec) + (end_write_time.tv_sec - start_write_time.tv_sec)*1000000;;
        double algoTime = (end_total_time.tv_usec - start_total_time.tv_usec) + (end_total_time.tv_sec - start_total_time.tv_sec)*1000000;

        fprintf(stderr, "--- other user output (if any) ---\n");
        fprintf(stderr, "Algorithm time = %f microsecs\n",algoTime);
        fprintf(stderr, "IO time = %f microsecs\n",ioTime);
        fprintf(stderr, "End to end time = %f secs\n",endtoendTime);
        return 0;
}
