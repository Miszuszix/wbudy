#include "spi_setup.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_ssp.h"

void init_ssp(void) {
    SSP_CFG_Type SSP_ConfigStruct;
    PINSEL_CFG_Type PinCfg;

    PinCfg.Funcnum = 2;
    PinCfg.OpenDrain = 0;
    PinCfg.Pinmode = 0;
    PinCfg.Portnum = 0;

    PinCfg.Pinnum = 7; PINSEL_ConfigPin(&PinCfg);
    PinCfg.Pinnum = 8; PINSEL_ConfigPin(&PinCfg);
    PinCfg.Pinnum = 9; PINSEL_ConfigPin(&PinCfg);

    PinCfg.Funcnum = 0;
    PinCfg.Portnum = 2;
    PinCfg.Pinnum = 2; PINSEL_ConfigPin(&PinCfg);

    SSP_ConfigStructInit(&SSP_ConfigStruct);
    SSP_Init(LPC_SSP1, &SSP_ConfigStruct);
    SSP_Cmd(LPC_SSP1, ENABLE);
}
