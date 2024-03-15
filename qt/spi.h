#ifndef SPI_H
#define SPI_H

//#include <iostream>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

int WiringPiSPIGetFd(int channel);
int WiringPiSPIDataRW(int channel, unsigned char *data, int len);
int WiringPiSPISetupMode(int channel, int speed, int mode);
int WiringPiSPISetup(int channel, int speed);

//extern int mcp3002Setup (int pinBase, int spiChannel) ;
//extern int mcp4802Setup (int pinBase, int spiChannel) ;

//Write to MCP 4802 on SPIdev channel 0
int AnalogWrite(int OUTchannel, uint8_t value); //MCP4802
//Read from MCP3202 on spidev channel 1
int AnalogRead(int ADCchannel);	//MCP3202
//Init the ADC and DAC
void InitADC_DAC(int speed, int mode);
//Init LDAC
int InitPin(char *pin, char* direction);

#ifdef __cplusplus
}
#endif


#endif // SPI_H
