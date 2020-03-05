// COMP1521 19t2 ... Assignment 2: heap management system

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myHeap.h"

/** minimum total space for heap */
#define MIN_HEAP 4096
/** minimum amount of space for a free Chunk (excludes Header) */
#define MIN_CHUNK 32


#define ALLOC 0x55555555
#define FREE  0xAAAAAAAA

#define EmptyHeader 0
#define TRUE 1
#define FALSE 0
/// Types:

typedef unsigned int  uint;
typedef unsigned char byte;

typedef uintptr_t     addr; // an address as a numeric type

/** The header for a chunk. */
typedef struct header {
	uint status;    /**< the chunk's status -- ALLOC or FREE */
	uint size;      /**< number of bytes, including header */
	byte data[];    /**< the chunk's data -- not interesting to us */
} header;

/** The heap's state */
struct heap {
	void  *heapMem;     /**< space allocated for Heap */
	uint   heapSize;    /**< number of bytes in heapMem */
	void **freeList;    /**< array of pointers to free chunks */
	uint   freeElems;   /**< number of elements in freeList[] */
	uint   nFree;       /**< number of free chunks */
};


/// Variables:

/** The heap proper. */
static struct heap Heap;


/// Functions:

static addr heapMaxAddr (void);
int adjustSize(int size);
void sortFreeList(void);
void swap(void *a, void *b);

/*
void mergeWithRight(int index, void *chunk);
void mergeWithLeft(int index, void *chunk);
void mergeFree(int index);
void merge(void *merge_here, void *move_this);
*/
/** Initialise the Heap. */
int initHeap (int size)
{
	Heap.nFree = 0;
	Heap.freeElems = 0;
	
	if (size < MIN_HEAP) {
	    size = MIN_HEAP;
	} else {
	    size = adjustSize(size);
	}

	Heap.heapSize = size;
	Heap.heapMem = malloc(Heap.heapSize * sizeof(byte));
	if (Heap.heapMem == NULL) {
	    printf("Error in heap memory\n");
	    return -1;
	}
	
	header *newh = (header *)(Heap.heapMem);
	newh->status = FREE;
	newh->size = size;
	
	Heap.freeList = malloc((Heap.heapSize / MIN_CHUNK) * sizeof(header *));
	if (Heap.freeList == NULL) return -1;
	
	Heap.freeList[0] = newh;
	Heap.nFree = 1;
	Heap.freeElems = Heap.heapSize / MIN_CHUNK;
	return 0;
}

/** Release resources associated with the heap. */
void freeHeap (void)
{
	free (Heap.heapMem);
	free (Heap.freeList);
}

/** Allocate a chunk of memory large enough to store `size' bytes. */
void *myMalloc (int size)
{
	if (size < 1) return NULL;
	
    size = adjustSize(size);
    
    uint smallest_size = size;
    int index = 0;
    header *curr_header = (header *)(Heap.freeList[0]);
    for (int i = 1; i < Heap.nFree; i++) {
        // find the smallest free chunk larger than N + HeaderSize
        if (curr_header->size >= size) {
            if (smallest_size > size && curr_header->size <= smallest_size) {
                smallest_size = curr_header->size;
                index = i;
            }
        }
        curr_header = (header *)(Heap.freeList[i]);
    }
    
    header *alloc_here = Heap.freeList[index];
    
    if (alloc_here->size < size) {
        return NULL;
    }
    
    uint chunkSize = size + sizeof(header);
    // smaller than N + HeaderSize + MIN_CHUNK, allocate the whole chunk
    if (alloc_here->size <= (chunkSize + MIN_CHUNK)) {
        alloc_here->status = ALLOC;
        Heap.freeList[index] = EmptyHeader;
        Heap.nFree--;
        sortFreeList();
    } else {
        uint freeSize;
        freeSize = alloc_here->size - chunkSize;
        
        // lower -- allocate for the request
        alloc_here->status = ALLOC;
        alloc_here->size = chunkSize;
        Heap.freeList[index] = EmptyHeader;
        sortFreeList();
        
        // upper -- new free chunk
        header *upper = (header *)((void *)alloc_here + alloc_here->size);
        upper->status = FREE;
        upper->size = freeSize;
        Heap.freeList[index] = upper;
        sortFreeList();
    }
    
    return ((void *)alloc_here + sizeof(header));
}

/** Deallocate a chunk of memory. */
void myFree (void *obj)
{   
	// insert the chunk and sort the free list
	/*
	
	chunk->status = FREE;
	Heap.freeList[Heap.nFree] = chunk;
    Heap.nFree++;
    sortFreeList();
    */
    
    void *heapTail = (void *)Heap.heapMem + Heap.heapSize;
	if (obj == NULL || obj < Heap.heapMem || obj >= heapTail) {
	    fprintf(stderr, "Attempt to free unallocated chunk\n");
	    exit(1);
	}
	
    header *chunk = (header *)((void *)obj - sizeof(header));
	if (chunk->status == FREE) {
	    fprintf(stderr, "Attempt to free unallocated chunk\n");
	    exit(1);
	}
	
    //The header of obj
    void *headerobj = ((void *)obj - sizeof(header));
 
    //Check that what we're freeing is valid:
    //header *headerchunk = (header *)(headerobj);

    //header *chunk = (header *)(headerobj);
      
    int before = FALSE;
    int after = FALSE;
       
    // next 
    header *next = (header *)((void *)chunk + chunk->size);
    int index = 0;
    for (int i = 0; i < Heap.freeElems; i++) {
        //header *curr = (header *)(Heap.freeList[i]);
        if (Heap.freeList[i] == next) {
            after = TRUE;
            index = i;
            break;
        }
    }
 
    // prev
    header *curr = Heap.heapMem;
    header *prev = NULL;
    while (curr < (header *)(heapMaxAddr())) {
        prev = curr;
        curr = (header *)((void *)(curr) + curr->size);
        if (curr == chunk) {
            if (prev->status == FREE) {
                before = TRUE;
            }
        break;
        }
    }
 
        //case 1: before = false, after = false. We're freeing a single chunk
        if (before == FALSE && after == FALSE) {
            chunk->status = FREE;
           
            //find where to put the pointer in the free list array
            int insertion_index = 0;
            while (insertion_index < Heap.nFree) {
                if ((header *)(Heap.freeList[insertion_index]) > chunk) {
                    break;
                }
                insertion_index++;
            }
            //shift everything right of inserting index right one
            int j = Heap.nFree;
            while (j > insertion_index) {
                Heap.freeList[j] = Heap.freeList[j-1];
                j--;
            }
            Heap.freeList[insertion_index] = headerobj;
            Heap.nFree++;
           
        //case 2: before = false, after = true.
        } else if (before == FALSE && after == TRUE) {
            chunk->status = FREE;
            chunk->size = chunk->size + next->size;
            Heap.freeList[index] = chunk;
           
        //case 3: before = true, after = false.
        } else if (before == TRUE && after == FALSE) {
            header *before_chunk = prev;
            uint before_size = before_chunk->size;
            before_chunk->status = FREE;
            before_chunk->size = before_size + chunk->size;
           
        //case 4: before = true, after = true.
        } else if (after == TRUE && before == TRUE) {
            header *before_chunk = prev;
            uint before_size = before_chunk->size;
            uint after_size = next->size;
            before_chunk->status = FREE;
            before_chunk->size = before_size + chunk->size + after_size;
 
            //shift everything left to fill after index in the freeList array.
            int shift_to = index;
            Heap.freeList[shift_to] = 0;
            while (Heap.freeList[shift_to + 1]!= 0 && (shift_to + 1) < Heap.freeElems) {
                Heap.freeList[shift_to] = Heap.freeList[shift_to + 1];
                shift_to++;
            }
            Heap.freeList[shift_to] = 0;
        }
}
/** Return the first address beyond the range of the heap. */
static addr heapMaxAddr (void)
{
	return (addr) Heap.heapMem + Heap.heapSize;
}

/** Convert a pointer to an offset in the heap. */
int heapOffset (void *obj)
{
	addr objAddr = (addr) obj;
	addr heapMin = (addr) Heap.heapMem;
	addr heapMax =        heapMaxAddr ();
	if (obj == NULL || !(heapMin <= objAddr && objAddr < heapMax))
		return -1;
	else
		return (int) (objAddr - heapMin);
}

/** Dump the contents of the heap (for testing/debugging). */
void dumpHeap (void)
{
	int onRow = 0;
    //printf("Running dumpHeap()\n");
	// We iterate over the heap, chunk by chunk; we assume that the
	// first chunk is at the first location in the heap, and move along
	// by the size the chunk claims to be.
	addr curr = (addr) Heap.heapMem;
	//int i = 0;
	while (curr < heapMaxAddr ()) {
	    
		header *chunk = (header *) curr;

		char stat;
		switch (chunk->status) {
		case FREE:  stat = 'F'; break;
		case ALLOC: stat = 'A'; break;
		default:
			fprintf (
				stderr,
				"myHeap: corrupted heap: chunk status %08x\n",
				chunk->status
			);
			exit (1);
		}
		printf (
			"+%05d (%c,%5d)%c",
			heapOffset ((void *) curr),
			stat, chunk->size,
			(++onRow % 5 == 0) ? '\n' : ' '
		);
        //printf("\nwhile %d\n", i);
	    //i++;
		curr += chunk->size;
	}

	if (onRow % 5 > 0)
		printf ("\n");
}

// adjust the size to a multiple of 4
int adjustSize(int size) 
{
    if (size % 4 != 0) {
	    return 4 * ((size / 4) + 1);
	}
	return size;
}

// sort the freeList in ascending address order
void sortFreeList(void)
{
    int i, j;
    for (i = 0; i < Heap.nFree - 1; i++) {
        for (j = 0; j < Heap.nFree - i - 1; j++) {
            if (Heap.freeList[j] > Heap.freeList[j + 1]) {
                swap(Heap.freeList[j], Heap.freeList[j + 1]);
            }
        }
    }
}

void swap(void *a, void *b)
{
    void *temp = a;
    a = b;
    b = temp;
}
/*
// if curr chunk is adjacent to the right chunk, merge them
void mergeWithRight(int index, void *chunk)
{

}

// if curr chunk is adjacent to the left chunk, merge them
void mergeWithLeft(int index, void *chunk){


}

// merge small free chunks into one big free chunk
void mergeFree(int index)
{

}

void merge(void *merge_here, void *move_this)
{
    header *add_one = (header *)merge_here;
    header *add_two = (header *)move_this;
    add_one->size = add_one->size + add_two->size;
    Heap.nFree--;
}*/
