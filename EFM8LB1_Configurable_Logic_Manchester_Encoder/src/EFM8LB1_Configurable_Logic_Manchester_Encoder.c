//-----------------------------------------------------------------------------
// EFM8LB1_Configurable_Logic_Manchester_Encoder.c
//-----------------------------------------------------------------------------
// Copyright 2015 Silicon Laboratories, Inc.
// http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt
//
// Program Description:
//
// This program demonstrates how to use the Configurable Logic to
// output Manchester encoded data via the SPI module.  The Manchester
// encoding is based on the IEEE 802.3 standard:
//    '0' : high-to-low transition in the middle of a bit
//    '1' : low-to-high transition in the middle of a bit
//
// Resources:
//   SYSCLK - 24.5 MHz HFOSC0 / 1
//   SPI0   - 765 kbps
//   P0.4   - SPI0 SCK
//   P0.5   - SPI0 MISO
//   P0.7   - SPI0 MOSI
//   P1.0   - Manchester encoded output
//   CLU0 and CLU1
//
// Target:         EFM8LB1
// Tool chain:     Generic
//
// Release 0.1 (KHS)
//    - Initial Revision
//    - 9 OCT 2015
//

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <SI_EFM8LB1_Register_Enums.h>                  // SFR declarations
#include "InitDevice.h"
#include "SI_LUT.h"

// $[Generated Includes]
// [Generated Includes]$
void CLU0_Init(void)
{
	SFRPAGE = 0x20;
	CLU0MX = 0xAB; // MXA as P0.4, MXB as P0.7
//	CLU0FN = SI_LUT_B; // MXB input value 0xCC equal to output
	CLU0FN = LUT_XOR(SI_LUT_A, SI_LUT_B); // MXB input value 0xCC equal to output
	//D flip-flop output, MXA as clock, and GPIO P0.2 pin output enable.
//	CLU0CF |= CLU0CF_OEN__ENABLE | CLU0CF_CLKSEL__MXA_INPUT;
	CLU0CF = CLU0CF_OEN__ENABLE | CLU0CF_OUTSEL__LUT;
	CLEN0 |= CLEN0_C0EN__ENABLE;
	SFRPAGE = 0;
}

void CLU1_Init(void)
{
	SFRPAGE = 0x20;
//	CLU1MX = 0xB1; // MXA as P1.2, MXB as CLU1 output, P1.0
//	CLU1FN = 0xF0; // MXA input value 0xF0 equal to output which means this is a buffer
	CLU1MX = CLU1MX_MXA__CLU1A8 | CLU1MX_MXB__CLU1B0;  // MXA is P0.4 (SCK), MXB is CLU0OUTPUT
	CLU1FN = LUT_XOR(SI_LUT_A, SI_LUT_B);
	CLU1CF = 0x80 | 0x40  ; //LUT output and GPIO pin output enable. for CLU1, it is P1.0
	CLEN0 |= CLEN0_C1EN__ENABLE;
	SFRPAGE = 0;
}

void CLU2_Init(void)
{
	SFRPAGE = 0x20;
	CLU2MX = 0xB2; // MXA as P1.1, MXB as CLU2 output, P2.2
	CLU2FN = 0xF0; // MXA input value 0xF0 equal to output which means this is a buffer
	CLU2CF = 0x80 | 0x40  ; //LUT output and GPIO pin output enable. for CLU2, it is P2.2
	CLEN0 |= CLEN0_C2EN__ENABLE;
	SFRPAGE = 0;
}

void CLU3_Init(void)
{
	SFRPAGE = 0x20;
	CLU3MX = 0xC3; // MXA as P1.2, MXB as CLU3 output, P2.5
	CLU3FN = 0xF0; // MXA input value 0xF0 equal to output which means this is a buffer
	CLU3CF = 0x80 | 0x40  ; //LUT output and GPIO pin output enable. for CLU3, it is P2.5
	CLEN0 |= CLEN0_C3EN__ENABLE;
	SFRPAGE = 0;
}


void CLU_Init(void)
{
	CLU0_Init();
//	CLU1_Init();
//	CLU2_Init();
//	CLU3_Init();
}
//-----------------------------------------------------------------------------
// main() Routine
// ----------------------------------------------------------------------------
int main(void)
{
    int i;
    unsigned char tmp = 0;

    // Call hardware initialization routine
    enter_DefaultMode_from_RESET();

    // Setup FNSEL is CLU0 and CLU1
//    SFRPAGE = 0x20;
//    CLU0FN = SI_LUT_B; // Select the B input
//    CLU1FN = LUT_XOR(SI_LUT_A, SI_LUT_B);
//    SFRPAGE = 0x00;
//    P0_B7 = 1;
    CLU_Init();
    while (1)
    {
// $[Generated Run-time code]
// [Generated Run-time code]$
    	for (i = 0; i< 50; i++);
//        SPI0DAT = 0xcc;
        SPI0DAT = tmp++;
        while (!SPI0CN0_TXNF);
    }
}
