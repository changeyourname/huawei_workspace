 
  Copyright (c) 2005-2015 Imperas Software Ltd. All Rights Reserved.

  The contents of this file are provided under the Software License
  Agreement that you accepted before downloading this file.

  This source forms part of the Software and can be used for educational,
  training, and demonstration purposes but cannot be used for derivative
  works except in cases where the derivative works require OVP technology
  to run.

  For open source models released under licenses that you can use for
  derivative works, please visit www.ovpworld.org or www.imperas.com
  for the location of the open source models.


FILE:Imperas/Examples/Models/Processor/README.txt


INTRODUCTION -------------------------------------------------------
The examples in the directories contained here should be used in 
conjunction with the OVP Processor Modeling User Guide. 

They walk through the development of a processor model for the 
Imperas and OVP simulation environment.
 
The processor used is the freely-available or1k processor 
(see http://www.opencores.org/projects.cgi/web/or1k/architecture). 


FILES --------------------------------------------------------------

or1k*
   These are the files that constitute the stage of processor model
   development.

platform/platform.c
   This is the test platform for the processor model using the ICM API.

application/application.c
application/asmtest.S
   These files are application test files used for verification of the
   current part of the model.

Makefile
   This allows the building of the model verification platform, the 
   test application and the model files into a shared object.

BUILDING ------------------------------------------------------------
   The processor model, platform executable and the assembler and/or 
   application source files are built using the Makefile
   
   > make
   
RUNNING --------------------------------------------------------------
    The example is executed by running the platform executable and
    passing the elf file as the first argument
    
    > ./platform/platform.${IMPERAS_ARCH}.exe --program application/asmtest.OR1K.elf
or 
    > ./platform/platform.${IMPERAS_ARCH}.exe --program application/application.OR1K.elf
    
    NOTE: Each example may have both or either an assembler or C based
    application file. 
