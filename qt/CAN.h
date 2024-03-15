/********************************
 ** CAN.h							 **
 **														 **
 **  Created on: Dec 9, 2021       **
 **      Author: Mikkel 			 ** 
 **		Studie nr: 20145474      **
 ********************************/

#ifndef CAN_H_
#define CAN_H_

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

/**
 * @brief Creates a socket for CAN communication. Name specifies
 * which socket to talk from.
 * @param char pointer to CAN interface.
 * @return int s SOCKET address
 */

int createSocket(char* name);

/**
 * @brief Writes over CAN-bus to a subsystem. Takes SOCKET address, length of message
 * id of subsystem and the message itself.
 *
 * @param int s SOCKET
 * @param unsigned int 8 bite defining length of messages
 * @param unsigned int 32 bite deinfinig id of subsystem
 * @param unsigned int 8 bite defining data to be sent
 * @return 0 on succes, -1 on fail.
 */
int CANwrite(int s, __u8 len, __u32 id , __u8 data[8]);

/**
 * @brief reads data from the CAN-bus.
 * @param int s SOCKET
 * @return structur of type can_fram with id, length of data and the data received.
 */
struct can_frame CANread(int s);

/**
 * @brief decodes the frame id, to see which subsystem sent it
 * @param frame.can_id from structur returned from CANread
 */
//void decodeCAN(struct can_frame frame); <-- Not finished!!


#endif