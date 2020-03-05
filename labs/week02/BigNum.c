// BigNum.c ... LARGE positive integer values

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BigNum.h"

// Initialise a BigNum to N bytes, all zero
void initBigNum (BigNum *bn, int Nbytes)
{
	bn->bytes = malloc(Nbytes * sizeof(Byte));
	assert(bn->bytes != NULL);
	bn->nbytes = Nbytes;
	memset(bn->bytes, '0', Nbytes);
	return;
}

// Add two BigNums and store result in a third BigNum
void addBigNums (BigNum bnA, BigNum bnB, BigNum *res)
//void addBigNums (BigNum n, BigNum m, BigNum *res)
{
    // Find the longer size
	int longer;
	if (bnA.nbytes >= bnB.nbytes){
	    longer = bnA.nbytes + 1;
	}else{
	    longer = bnB.nbytes + 1;
	}
	
	// Create a new array
	Byte *new = malloc((longer + 1) * sizeof(Byte));
   	assert(new != NULL);
   	memset(new, '0', longer + 1);
	
	// Add two numbers and store it into 'new'
	int length = 0;
	int total;
	int tenth = 0;
	for (int i = 0; i < longer; i++){
	    if (i == longer - 1 && tenth == 0){
	        length = longer;
	        break;
	    }else if (i == longer - 1 && tenth == 1){
	        new[i] = 1 + '0';
	        length = longer;
	        break;
	    }else{
	        if (i < bnA.nbytes && i < bnB.nbytes){
	            total = (bnA.bytes[i] - '0') + (bnB.bytes[i] - '0') + tenth;
	            if (total > 9){
	               int one = total%10;
	               new[i] = one + '0';
	               tenth = 1;
	            }else{
	                new[i] = total + '0';
	                tenth = 0;
	            }
	        }else{
	            if (bnA.nbytes > bnB.nbytes){
	                new[i] = bnA.bytes[i];
	            }else{
	                new[i] = bnB.bytes[i];
	            }
	        }
	    }
	}
	
	free(res->bytes);
	res->nbytes = length;
	res->bytes = new;
	
	return;
}

// Set the value of a BigNum from a string of digits
// Returns 1 if it *was* a string of digits, 0 otherwise
int scanBigNum (char *s, BigNum *bn)
{    
    
    // Count the number of digit in s
    int nd = 0;             
	int i = 0;
	while(s[i] != '\0'){
	    if (isdigit(s[i])){
	        nd++;
	    }
	    i++;
	}
	
	if (nd == 0) return 0;
	
	// Create a new array
	Byte *new = malloc(nd * sizeof(Byte));
   	assert(new != NULL);
   	memset(new, '0', nd);
    
	// Store the number in BigNum
	int j = 0;
	int m = 0;
	while (s[j] != '\0'){
	    if (isdigit(s[j])){
	        new[nd - m - 1] = s[j];
	        m++;
	    }
	    j++;
	}
	
	free(bn->bytes);
	bn->nbytes = nd;
	bn->bytes = new;
	
	return 1;
}

// Display a BigNum in decimal format
void showBigNum (BigNum bn)
{
    int position = 0;
	for (int i = bn.nbytes - 1; i >= 0; i--){
	    if (bn.bytes[i] != '0'){
	        position = i;
	        break;
	    }
	}
	
	if (position == 0 && bn.bytes[position] == '0'){
	    printf("0");
	}else{    
	    for (int i = position; i >= 0; i--){
	        printf ("%d", bn.bytes[i] - '0');
	    }
	}
	return;
}
