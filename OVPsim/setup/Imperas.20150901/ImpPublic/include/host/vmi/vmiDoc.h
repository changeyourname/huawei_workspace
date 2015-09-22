/*
 *
 * Copyright (c) 2005-2015 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License Agreement
 * that you accepted before downloading this file.
 *
 * This header forms part of the Software but may be included and used unaltered
 * in derivative works.
 *
 * For more information, please visit www.OVPworld.org or www.imperas.com
 */

/******************************************************************************/
/*                                                                            */
/*            V I R T U A L   M A C H I N E   I N T E R F A C E               */
/*                                                                            */
/*                  M O D E L   D O C U M E N T A T I O N                     */
/*                                                                            */
/******************************************************************************/

#ifndef VMI_DOC_H
#define VMI_DOC_H

#include "vmi/vmiTyperefs.h"
#include "hostapi/impTypes.h"

//
// Create a new node. The name is a paragraph or section heading.
//
vmiDocNodeP vmidocAddSection(vmiDocNodeP parent, const char *name);

//
// Create a new text node. The text will appear in the paragraph or section
//
vmiDocNodeP vmidocAddText   (vmiDocNodeP node,   const char *text);

//
// Set the root document node on a processor model.
//
void vmidocProcessor(vmiProcessorP processor, vmiDocNodeP document);


#endif

