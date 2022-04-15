#include<stdio.h>

typedef long Align; //for aligment to long boundary

union header //block header:
{
    struct
    {
        union header *ptr; //next block if on free list
        unsigned size; //size of this block
    }s;
    Align x; //force alignment of blocks
};

typedef union header Header;


static Header base;
static Header *freep = NULL;
void *mymalloc(unsigned nbytes);
void myfree(void *ap);
static Header *morecore(unsigned nu);


//malloc : grneral-purpose storage allocator
void *mymalloc(unsigned nbytes)
{
    printf("malloc:\n");
    Header *p, *prevp;
    Header *morecore(unsigned);
    unsigned nunits;

    nunits = (nbytes + sizeof(Header)-1)/sizeof(Header) + 1;
    if( (prevp = freep) == NULL )//no free list yet
    {
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }
    for(p=prevp->s.ptr; ; prevp = p, p = p->s.ptr)
    {
        if(p->s.size >= nunits)//big enough
        {
            if(p->s.size == nunits) //exactly
                prevp->s.ptr = p->s.ptr;
            else
            {
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void*)(p+1);
        }
        if(p==freep)
            if((p = morecore(nunits)) == NULL)
                return NULL;
    }
}

#define NALLOC 1024 //minimum #units to request

//morecore: ask system for more memory
static Header *morecore(unsigned nu)
{
    printf("morecore:\n");
    char *cp, *sbrk(int);
    Header *up;

    if(nu < NALLOC)
        nu = NALLOC;
    cp = sbrk(nu *sizeof(Header));
    if(cp == (char*) - 1) //no space at all
        return NULL;
    up = (Header *)cp;
    up->s.size = nu;
    myfree((void *)(up+1));
    return freep;
}

//free: put block ap in free list
void myfree(void *ap)
{
    printf("free:\n");
    Header *bp, *p;

    bp = (Header *)ap - 1;
    for(p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if(p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break; // freed block at start or end of arena
    /*
    printf("&base:\t%p\n", &base);
    printf("freep:\t%p\n", freep);
    printf("p:\t%p\n", p);
    printf("bp:\t%p\n", bp);
    printf("p->s.ptr:\t%p\n", p->s.ptr);
    printf("p->s.size:\t%d\n", p->s.size);
    printf("bp->s.ptr:\t%p\n", bp->s.ptr);
    printf("bp->s.size:\t%d\n", bp->s.size);
    */
    if(bp + bp->s.size == p->s.ptr)
    {
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    }
    else
        bp->s.ptr = p->s.ptr;
    if(p+p->s.size == bp)
    {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    }
    else
        p->s.ptr = bp;
    freep = p;

}


int main()
{
    int i;
    char *p;
    for(i=0; i<10; i++)
    {
        p = (char*)mymalloc(sizeof(char));
        //if(p==NULL)
            //printf("error!\n");
        *p = '0'+i;
        printf("%c\n", *p);
        printf("%p\n", p);
    }
}
