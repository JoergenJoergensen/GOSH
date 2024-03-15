/**********************************
 ** CAN.c						 **
 **								 **
 **  Created on: Dec 9, 2021     **
 **      Author: Team 3 		 ** 
 **		Studie: Elektronik Herning      **
 ********************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include "CAN.h"

int createSocket(char* name)
{
	int s; //for the socket

	struct sockaddr_can addr;
	struct ifreq ifr;
	/**
	 * Name is either can0, can1, can2... if wishing to connect to raw CAN,
	 * or vcan0, vcan1... for virtual can kommunikation
	 */
	const char *ifname = name;
	/**
	 * Checking if we can open at CAN socket.
	 * Will make a RAW SOCKET with protocol CAN RAS in the domain of CAN
	 *
	 * PF_CAN = CAN domain
	 * SOCK_RAS = Type RAW SOCKET
	 * CAN_RAW = Protocol CAN_RAW
	 **/
	if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) == -1) {
		perror("Error while opening socket");
		return 0;
	}
	/**
	 * ifr.ifr_name is the interface name, meaning the interface we want to use CAN with.
	 */
	strcpy(ifr.ifr_name, ifname);

	/**
	 * ioctl finds the index for our socket, and puts it into ifr.
	 */
	ioctl(s, SIOCGIFINDEX, &ifr);

	addr.can_family  = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;
	/*
	 * Prints where our interface name is located in the index of interface menu
	 */
	printf("%s at index %d\n", ifname, ifr.ifr_ifindex);

	/**
	 * Attemps to bind the socket to the interfacename, give at the ifr.ifr_ifindex
	 */
	if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
		perror("Error in socket bind");
		return 0;
	}
	return s;	//return the socket
}

//Send message
int CANwrite(int s, __u8 len, __u32 id , __u8 data[8])
{
	/*
	 * Creates a frame for communication over CAN.
	 * The frame contains the id of subsystem, message, length of message.
	 */
	struct can_frame frame;

	//set id of frame
	frame.can_id = id;
	//set length of can data.
	frame.can_dlc = len;		//længde på forsendelse? 0-8 byte.
	//set the can frame data
	int i=0;
	for (i=0; i<8;i++)
		{
			if(i <len)
				frame.data[i] = data[i];
			else
				frame.data[i] = 0;
		}

	//write/send the frame on can-bus. Check that everything was sent or error.
	if (write(s, &frame, sizeof(struct can_frame)) != sizeof(struct can_frame))
	{
	   perror("Write");
	   return -1;
	}
	return 0;
}

//Receive message
struct can_frame CANread(int s) //pass socket
{
	int nbytes = 0;
	int i;
	struct can_frame frame;
	/*
	 * Creates a block with number of bytes, specified by sizeof to 0.
	 * The block is used to store the CAN frame we read in.
	 */
	memset(&frame, 0, sizeof(struct can_frame));

	/*
	 * Read frame from our CAN SOCKET.
	 * If amount of bytes read is less than the sizeof our can_fram struct
	 * then it gives an error, since we have received less than we wanted to.
	 */
	nbytes = read(s, &frame, sizeof(struct can_frame));
	if (nbytes < 0) {
	   perror("Read");
	}
	/*
	 * Prints out can_id in fram and length of data, plus the data it self
	 */
	printf("0x%03X [%d] ",frame.can_id, frame.can_dlc);
	for (i = 0; i < frame.can_dlc; i++)
	   printf("%02X ",frame.data[i]);
	printf("\r\n");
	/*
	 * return the frame so we can use it later.
	 */
	return frame;
} //CANread

//Not finished, just prototype
/*
void decodeCAN(struct can_frame frame)
{
	//Decode our messages received according to known codes.
	switch (frame.can_id)
	{
	case 0x555: //Do smth - decode data and save to relevant variable.
		break;
	default:
		//Do nothing since we do not "know" this id.-code
		break;
	}
} // decodeCAN
*/