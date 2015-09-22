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
#include <stdlib.h>

int main() {

    unsigned int i,j;
    int id = impProcessorId();

    printf ("CPU %d: Starting ...\n", id);

    for(i=0;i<200;i++){

        printf ("CPU %d: Hello World %d\n", id, i);

        for(j=0;j<20000;j++){
            // wait
        }
    }
}

