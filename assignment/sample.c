//If we get passed a null pointer, we don't want to try access it later
    if (obj == NULL) {
        fprintf(stderr, "Attempt to free unallocated chunk\n");
        exit(1);
    }
 
    //The header of obj
    void *headerobj = ((byte *)obj - sizeof(header));
 
    //Check that what we're freeing is valid:
    header *headerchunk = (header *)(headerobj);
    int invalid = 0;
    if (headerchunk->status != ALLOC || (void *)(headerchunk) < Heap.heapMem || (addr)(headerchunk) > heapMaxAddr() - sizeof(header)) {
        invalid = 1;
    }
 
    //Check that it's actually a header in Heap.heapMem
    int isChunk = 0;
    addr iterationChunk  = (addr)Heap.heapMem;
    while(iterationChunk < heapMaxAddr()){
        header *current = (header *)iterationChunk;
        if(current == headerchunk){
            isChunk = 1;
        }
        iterationChunk += current->size;
    }
 
 
    if (invalid == 1 || isChunk != 1) {
        fprintf(stderr, "Attempt to free unallocated chunk\n");
        exit(1);
    }
    else {
        header *chunk = (header *)(headerobj);
       
        bool before = false;
        bool after = false;
       
        //To figure out if the after is free,
        //check that the address at the end of the allocated chunk
        //is not in the freeList array.
        header *after_chunk = (header *)(((char*) chunk) + chunk->size);
 
        int i = 0;
        int after_index = 0;
        while (i < Heap.freeElems) {
            if (Heap.freeList[i] == after_chunk) {
                after = true;
                after_index = i;
                break;
            }
            i++;
        }
 
        header *curr = Heap.heapMem;
        header *prev = NULL;
       
        while (curr < (header *)(heapMaxAddr())) {
            prev = curr;
            curr = (header *)((char *)(curr) + curr->size);
            //Check that the previous is alloced.
            if (curr == chunk) {
                if (prev->status == FREE) {
                    before = true;
                }
                break;
            }
            //If we've gone past our header, stop
            if (curr > chunk) {
                before = false;
                break;
            }
        }
 
        //case 1: before = false, after = false. We're freeing a single chunk
        if (before == false && after == false) {
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
        } else if (before == false && after == true) {
            chunk->status = FREE;
            chunk->size = chunk->size + after_chunk->size;
            Heap.freeList[after_index] = chunk;
           
        //case 3: before = true, after = false.
        } else if (before == true && after == false) {
            header *before_chunk = prev;
            uint before_size = before_chunk->size;
            before_chunk->status = FREE;
            before_chunk->size = before_size + chunk->size;
           
        //case 4: before = true, after = true.
        } else if (after == true && before == true) {
            header *before_chunk = prev;
            uint before_size = before_chunk->size;
            uint after_size = after_chunk->size;
            before_chunk->status = FREE;
            before_chunk->size = before_size + chunk->size + after_size;
 
            //shift everything left to fill after index in the freeList array.
            int shift_to = after_index;
            Heap.freeList[shift_to] = 0;
            while (Heap.freeList[shift_to + 1]!= 0 && (shift_to + 1) < Heap.freeElems) {
                Heap.freeList[shift_to] = Heap.freeList[shift_to + 1];
                shift_to++;
            }
            Heap.freeList[shift_to] = 0;
        }
    }
    return;
