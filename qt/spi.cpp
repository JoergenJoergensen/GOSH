#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/ioctl.h>
#include <asm/ioctl.h>
#include <linux/spi/spidev.h>

#include <unistd.h>

#include "spi.h"

//  The SPI bus parameters
//	Variables as they need to be passed as pointers later on

//static const char       *spiDev0  = "/dev/spidev0.0" ;
//static const char       *spiDev1  = "/dev/spidev0.1" ;
static const uint8_t spiBPW = 8;
static const uint16_t spiDelay = 0;

static uint32_t spiSpeeds[2];
static int spiFds[2];

/*
 *  WiringPiSPIGetFd:
 *	Return the file-descriptor for the given channel
 *********************************************************************************
 */
int WiringPiSPIGetFd(int channel)
{
    return spiFds[channel & 1];
}

/*
 *  WiringPiSPIDataRW:
 *	Write and Read a block of data over the SPI bus.
 *	Note the data ia being read into the transmit buffer, so will
 *	overwrite it!
 *	This is also a full-duplex operation.
 *********************************************************************************
 */
int WiringPiSPIDataRW(int channel, unsigned char *data, int len)
{
    struct spi_ioc_transfer spi;
    channel &= 1;

    memset(&spi, 0, sizeof(spi));

    spi.tx_buf = (unsigned long) data;
    spi.rx_buf = (unsigned long) data;
    spi.len = len;
    spi.delay_usecs = spiDelay;
    spi.speed_hz = spiSpeeds[channel];
    spi.bits_per_word = spiBPW;

    return ioctl(spiFds[channel], SPI_IOC_MESSAGE(1), &spi);
}

/*
 *  WiringPiSPISetupMode:
 *	Open the SPI device, and set it up, with the mode, etc.
 *********************************************************************************
 */
int WiringPiSPISetupMode(int channel, int speed, int mode) {
    int fd;
    char spiDev[32];

    mode &= 3;	// Mode is 0, 1, 2 or 3

    // Channel can be anything - lets hope for the best
    //  channel &= 1 ;	// Channel is 0 or 1
    //TODO: Plan om at køre SPI spidev1.x og CAN på spidev0
    snprintf(spiDev, 31, "/dev/spidev1.%d", channel);

    if ((fd = open(spiDev, O_RDWR)) < 0)
    {
        printf("Unable to open SPI device: %s\n", spiDev);
        exit(EXIT_FAILURE);
    }

    spiSpeeds[channel] = speed;
    spiFds[channel] = fd;

    // Set SPI parameters.
    if (ioctl(fd, SPI_IOC_WR_MODE, &mode) < 0)
    {
        printf("SPI Mode Change failure: %s\n", spiDev);
        exit(EXIT_FAILURE);
    }
    if (ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &spiBPW) < 0)
    {
        printf("SPI BPW Change failure: %s\n", spiDev);
        exit(EXIT_FAILURE);
    }
    if (ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed) < 0)
    {
        printf("SPI Speed Change failure: %s\n", spiDev);
        exit(EXIT_FAILURE);
    }

    return fd;
}

/*
 *  WiringPiSPISetup:
 *	Open the SPI device, and set it up, etc. in the default MODE 0
 *********************************************************************************
 */
int WiringPiSPISetup(int channel, int speed)
{
    return WiringPiSPISetupMode(channel, speed, 0);
}


int AnalogWrite(int OUTchannel, uint8_t value)
{
    // MCP4802		DAC
    // outchannel er den kanal på DAC'en som vi vil skrive til.
    int dac_channel_out = OUTchannel;
    uint8_t gain = 0;	//0: gain = 2. Vref 2,048V.  0: G = 1; 1: G=2;
    unsigned char spiData[2];
    unsigned char chanBits, dataBits;

    // set dac settings. output, gain(active low), operation/shutdown
    chanBits = dac_channel_out << 7 | gain << 5 | 1 << 4;

    // put in digital data values.
    chanBits |= ((value >> 4) & 0x0F);
    dataBits = ((value << 4) & 0xF0);

    spiData[0] = chanBits;
    spiData[1] = dataBits;
    //writing on spidevX.1:				//Asehat ser ud til at køre på channel 1
    if (WiringPiSPIDataRW(1, spiData, 2) < 0)
    {
        printf("Error on writing to DAC");
        return -1;
    }
    return 0;
}


int AnalogRead(int ADCchannel)
{
    //MCP3202		ADC
    //ADC_channel er hvilken indgang vi vil have læst fra.
    unsigned char spiData[3];

    spiData[0] = 1; //Start bit

    if (ADCchannel == 0)	// single ended - channel - MSB
        spiData[1] = 0b10100000;
    else
        spiData[1] = 0b11100000;

    spiData[2] = 0;

    //Use channel 1: SpidevX.0			//Asehat ser ud til at køre ADC ch 0
    //Der kan ændres på channel her.
    if (WiringPiSPIDataRW(0, spiData, 3) < 0)
    {
        printf("Error on analog read");
        return -1;
    }

    return ((spiData[1] << 8) | spiData[2]) & 0xFFF;
}

void InitADC_DAC(int speed, int mode)
{
    //Init with channel 0
    WiringPiSPISetupMode(0, speed, mode);
    //Init with channel 1
    WiringPiSPISetupMode(1, speed, mode);
    //Setup LDAC on pin?
    InitPin("5", "out");
}

int InitPin(char* pin, char *direction){
    //Open file descriptor
    int fd = 0;

    if ((fd = open("/sys/class/gpio/export", O_WRONLY)) == -1)
    {
        printf("Error exporting gpio");
    }
    if (write(fd, pin, strlen(pin)) < strlen(pin))
    {
        printf("Error on writing pin number");
    }
    if (close(fd) != 0)
    {
        printf("Error closing export");
    }

    //Direction
    char buffer[50];
    memset(buffer, 0, sizeof buffer);
    snprintf(buffer, sizeof buffer, "/sys/class/gpio/gpio%c/direction", *pin);

    if ((fd = open(buffer, O_WRONLY)) == -1)
    {
        printf("Error opening direction");
    }
    if (write(fd, direction, strlen(direction)) < strlen(direction))
    {
        printf("Error on writing direction");
    }
    if (close(fd) != 0)
    {
        printf("Error closing direction");
    }

    return 0;
}

#ifdef __cplusplus
}
#endif
