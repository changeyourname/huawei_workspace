/*
 *
 * Copyright (c) 2005-2015 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License
 * Agreement that you accepted before downloading this file.
 *
 * This source forms part of the Software and can be used for educational,
 * training, and demonstration purposes but cannot be used for derivative
 * works except in cases where the derivative works require OVP technology
 * to run.
 *
 * For open source models released under licenses that you can use for
 * derivative works, please visit www.OVPworld.org or www.imperas.com
 * for the location of the open source models.
 *
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


#define DICTSIZE	5
char *dict[DICTSIZE] = { "simplified", ": ", "Multicore ", "Imperas", "design " };
int  intIndex[DICTSIZE] = { 3, 1, 2, 4, 0 };

int   extIndex[DICTSIZE] = { 0 };

int main(int argc, char **argv)
{
   int i, idx;
   char *tmp;

   // allocate memory for the string
   tmp = malloc(128);
   assert(tmp);

   // init the string
   strcpy(tmp, "");

   printf("\n1) Internal memory allocated for string\n\n");

   // copy the indeces from internal memory 
   // to external memory
   memcpy(extIndex, intIndex, DICTSIZE*sizeof(int));

   printf("Array 'extIndex' defined at address %p with size 0x%x\n\n", extIndex, DICTSIZE*sizeof(int));

   printf("2) Copied indices from internal memory to 'extIndex'\n\n");

   printf("3) Use data from 'extIndex' to index internal dictionary\n\n");
   // read from memory containing extIndex and index
   // the internal dictionary to build a sentence
   i = 0;
   while (i<DICTSIZE) {
       printf("extIndex[%d]=%d\n",i,extIndex[i]);
       idx = extIndex[i];
       strcat(tmp, dict[idx]);
       i++;
   }

   // print the string
   printf("\nString from memory: '%s'\n\n", tmp);

   return 1;
}
