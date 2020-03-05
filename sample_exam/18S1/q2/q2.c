// COMP1521 18s1 Q2 ... shred() function

// put any needed #include's here

void shred(int infd, int outfd)
{
	/*
	for the whole infd file {
        read a 64-byte block into a buffer
        // may have < 64 bytes in buffer at end of file
        overwrite the buffer with random characters from 'A'..'Z'
        write the buffer to outfd, then write a newline ('\n') to outfd
    }
	*/
	char buf[64];
	char n1 = '\n';
	while (read(infd, &buf, 64) > 0) {
	    for (int i = 0; i < 64; i++) {
	        char random = (rand() % 26) + 'A';
	        buf[i] = random;
	    }
	    write(outfd, &buf, 64);
	    write(outfd, &n1, 1);
	}
}
