#ifndef OURCAN_H
#define OURCAN_H


extern uint16_t g_battery_capacity;
extern uint16_t g_battery_temp;
extern uint16_t g_gokart_speed;
extern float g_longitude;
extern float g_latitude;
extern int g_speed_gps;
extern int g_clock_hours;
extern int g_clock_minutes;


#ifdef __cplusplus
extern "C"
{
#endif


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

#include <stdint.h>	//uint32_t
#include <asm-generic/int-ll64.h>


int createSocket(char* name);


int CANwrite(int s, __u8 len, __u32 id , __u8 data[8]);
int CANwrite_frame(int socket, struct can_frame *frame);

struct can_frame CANread(int s);

/*
 * Give socket and struct to save the frame
 */
int CANread_for_nonblocking(int s,struct can_frame *frame);

void decodeCAN(struct can_frame frame);

/*
 * Set socket to non-blocking.
 * Not tested.
 */
int setNonblocking(int fd);


void set_VESC_current_max(uint32_t max, uint32_t min, int socket);
void decodeCANeid(struct can_frame frame);

//Message queue for CAN.
void CAN_msq_init(void);
int CAN_enqueue_frame(struct can_frame *can_frame_to_send);
int CAN_dequeue_frame(struct can_frame *can_frame_to_receive);
struct can_frame can_make_frame(int code);

#ifdef __cplusplus
}
#endif

#endif // OURCAN_H
