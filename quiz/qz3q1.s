   li   $t1, 0                  #int t1 = 0;
   li   $t2, 1                  #int t2 = 1;
   li   $t3, 10                 #int t3 = 10;
loop:
   bgt  $t2, $t3, end_loop      #if (t2 > t3) goto end;
   mul  $t1, $t1, $t2           # t1 = t1 * t2
   addi $t2, $t2, 1             # t2++
   j    loop                    
end_loop:
   sw   $t1, result             #t1 = result
   
   # int i = 1;
   # for (i = 1; i <= 10; i++){
   #    t1 *= i;
   # }
   # return t1;
