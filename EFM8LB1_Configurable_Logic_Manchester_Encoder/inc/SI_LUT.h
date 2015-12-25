/*
 * SI_LUT.h
 *
 *  Macro definitions to simplify evaluation of logic for FNSEL assignment
 *  Created on: Aug 11, 2015
 */

#ifndef SI_LUT_H_
#define SI_LUT_H_


// Definitions for Inputs MXA, MXB and Carry
#define SI_LUT_A    0xf0
#define SI_LUT_B    0xcc
#define SI_LUT_C    0xaa

// Macros for combinatorial logic
#define LUT_NOT(a)      ~(a)
#define LUT_AND(a,b)    ((a) & (b))
#define LUT_OR(a,b)     ((a) | (b))
#define LUT_NAND(a)     LUT_NOT(LUT_AND(a,b))
#define LUT_NOR(b)      LUT_NOT(LUT_OR(a,b))
#define LUT_XOR(a,b)    LUT_OR(LUT_AND(a, LUT_NOT(b)), LUT_AND(LUT_NOT(a), b))
#define LUT_XNOR(a,b)   LUT_NOT(LUT_XOR(a,b))


#endif /* SI_LUT_H_ */
