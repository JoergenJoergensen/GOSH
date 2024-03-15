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

#include <stdint.h>     //for uint32_t
#include <sys/msg.h>	//for message queue
#include <stddef.h>		//for message queue
#include <errno.h>		//msgrcv from queue - errno
#include <pthread.h>
#include <math.h>       //link med -lm
#include <time.h>

#include "ourCAN.h"
#include "globals.h"
#include "threads.h"



// Nogle globale variabler til at prøve at aflæse VESC beskeder
uint32_t g_rpm;
uint32_t g_total_current;
//Duty cycle *1000
uint32_t g_duty_cycle;
//Amp Hours consumed * 10k. Lave float / 10k?
uint32_t g_amp_hours_consumed;
//Amp hour charged * 10k
uint32_t g_amp_hours_charged;
//Amp Hours consumed * 10k. Lave float / 10k?
uint32_t g_watt_hours_consumed;
//Amp hour charged * 10k
uint32_t g_watt_hours_charged;
// Mosfet temp *10	Celcius?
uint32_t g_mosfet_temp;
// Motor temp * 10	Celcius?
uint32_t g_motor_temp;
uint32_t g_input_current;
uint32_t g_pid_position;
uint32_t g_tachometer;
uint32_t g_input_voltage;
//----------------------------^^^ Globale til VESC aflæsning.

uint16_t g_battery_capacity;
uint16_t g_battery_temp;
uint16_t g_gokart_speed;
float g_longitude;
float g_latitude;
int g_speed_gps;
int g_clock_hours;
int g_clock_minutes;
time_t g_timestamp;
struct tm g_ourtimestruct;


#define DEBUG_STATUS 1

int createSocket(char* name)
{
    int s; //for the socket

    struct sockaddr_can addr;
    struct ifreq ifr;
    /*
     * Name is either can0, can1, can2... if wishing to connect to raw CAN,
     * or vcan0, vcan1... for virtual can kommunikation
     */
    const char *ifname = name;
    /*
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
    /*
     * ifr.ifr_name is the interface name, meaning the interface we want to use CAN with.
     */
    strcpy(ifr.ifr_name, ifname);

    /*
     * ioctl finds the index for our socket, and puts it into ifr.
     */
    ioctl(s, SIOCGIFINDEX, &ifr);

    addr.can_family  = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    /*
     * Prints where our interface name is located in the index of interface menu
     */
    printf("%s at index %d\n", ifname, ifr.ifr_ifindex);

    /*
     * Attemps to bind the socket to the interfacename, give at the ifr.ifr_ifindex
     */
    if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("Error in socket bind");
        return 0;
    }
    return s;	//return the socket
} //createSocket

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
} //CANwrite

int CANwrite_frame(int socket, struct can_frame *frame){
    //write/send the frame on can-bus. Check that everything was sent or error.
    // Is the frame and pointer to frames being used correct?!
    if (write(socket, frame, sizeof(struct can_frame)) != sizeof(struct can_frame))
    {
        perror("Write from CANwrite_frame");
        return -1;
    }
    return 0;
} //CANwrite_frame

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

//Receive message
int CANread_for_nonblocking(int s,struct can_frame *frame) //pass socket
{
    int nbytes = 0;
    //int i;
    //struct can_frame frame;
    /*
     * Creates a block with number of bytes, specified by sizeof to 0.
     * The block is used to store the CAN frame we read in.
     */
    memset(frame, 0, sizeof(struct can_frame));
    /*
     * Read frame from our CAN SOCKET.
     * If amount of bytes read is less than the sizeof our can_fram struct
     * then it gives an error, since we have received less than we wanted to.
     */
    nbytes = read(s, frame, sizeof(struct can_frame));
    if (nbytes < 0) {
        if (!(errno == EAGAIN || errno == EWOULDBLOCK)){
            perror("Canread nonblocking");
        }
        return -1;
    }


    return 0;
} //CANread_for_nonblocking


void decodeCAN(struct can_frame frame)
{
    //Decode our messages received according to known codes.
    switch (frame.can_id)
    {
    case 0x555: //Do smth - decode data and save to relevant variable.
        break;
    case 0x124: //Test message for GUI - 1
        g_battery_capacity = (uint16_t)frame.data[0] << 8 | (uint16_t)frame.data[1];
        g_battery_temp = (uint16_t)frame.data[2] << 8 | (uint16_t)frame.data[3];
        g_gokart_speed = (uint16_t)frame.data[4] << 8 | (uint16_t)frame.data[5];
        break;
    case 0x1C2: //Latitude longitude scale 100k bigendian        Team 1 - IoT
        //Latitude - north
        g_latitude = ((uint32_t)frame.data[0] << 24 | (uint32_t)frame.data[1] << 16 | (uint32_t)frame.data[2] << 8  | (uint32_t)frame.data[3]) / 100000.0;
        //Longitude - East
        g_longitude = ((uint32_t)frame.data[4] << 24 | (uint32_t)frame.data[5] << 16 | (uint32_t)frame.data[6] << 8  | (uint32_t)frame.data[7]) / 100000.0;
        break;
        // Til hastighed fra GPS - modul. Kommer fra Team 1:
    case 0x1C3: //                                Team 1 - IoT
        //Speed scale 1000. Dvs det kommer i meter/time.
        g_speed_gps = round(((uint16_t)frame.data[0] << 8 | (uint16_t)frame.data[1]) / 1000.0);
        break;
        //Anden måde
    case 0x1C4: //Tid  Team 1 - IoT
        g_timestamp = (uint32_t)frame.data[0] << 24 | (uint32_t)frame.data[1] << 16 | (uint32_t)frame.data[2] << 8 | (uint32_t)frame.data[3];
        localtime_r(&g_timestamp, &g_ourtimestruct);
        g_clock_hours = g_ourtimestruct.tm_hour;
        g_clock_minutes = g_ourtimestruct.tm_min;
        break;
    default:
        //Do nothing since we do not "know" this id.-code
        break;
    }


} // decodeCAN

void decodeCANeid(struct can_frame frame)
{
    // bit 7-0 is controller id.
    int command = -1;
    // Det er jo nok nødvendigt med en mask.
    command = (frame.can_id & CAN_EFF_MASK) >> 8;
    //command = frame.can_id >> 8; // bit shift to get code only. Perhaps
    // need bit mask in future.
    // (frame.can_id & CAN_EFF_MASK) >> 8
    // Prøv hvis det ikke fungerer med at læse commands korrekt.
    //TODO:

    switch(command)
    {
    case 9: // Status 1
        //rpm
        g_rpm = (uint32_t)frame.data[3] << 24 | (uint32_t)frame.data[2] << 16 |
                                                                           (uint32_t)frame.data[1] << 8 | (uint32_t)frame.data[0];
        //total current * 10 (should we make float and divide with 10?)
        g_total_current = (uint16_t)frame.data[4] << 8 | (uint16_t)frame.data[5];
        //Duty cycle *1000
        g_duty_cycle = (uint16_t)frame.data[6] << 8 | (uint16_t)frame.data[7];
        if (DEBUG_STATUS){
            printf("Case 9, status 1.\nRPM = %d\nCurrent = %d\nDuty Cycle = %d\n"
                   , g_rpm, g_total_current, g_duty_cycle);
        }
        break;
    case 14: // Status 2
        //Amp Hours consumed * 10k. Lave float / 10k?
        g_amp_hours_consumed = 	(uint32_t)frame.data[3] << 24 |
                                                           (uint32_t)frame.data[2] << 16 |
                                                                                      (uint32_t)frame.data[1] << 8 |
                                                                                                                 (uint32_t)frame.data[0];
        //Amp hour charged * 10k
        g_amp_hours_charged = 	(uint32_t)frame.data[4] << 24 |
                                                           (uint32_t)frame.data[5] << 16 |
                                                                                      (uint32_t)frame.data[6] << 8 |
                                                                                                                 (uint32_t)frame.data[7];
        if (DEBUG_STATUS){
            printf("Case 14, status 2.\nAmpH = %d\nAH_charged = %d"
                   , g_amp_hours_consumed, g_amp_hours_charged);
        }
        break;
    case 15: //Status 3
        //Amp Hours consumed * 10k. Lave float / 10k?
        g_watt_hours_consumed = 	(uint32_t)frame.data[3] << 24 |
                                                               (uint32_t)frame.data[2] << 16 |
                                                                                          (uint32_t)frame.data[1] << 8 |
                                                                                                                     (uint32_t)frame.data[0];
        //Amp hour charged * 10k
        g_watt_hours_charged = 	(uint32_t)frame.data[4] << 24 |
                                                           (uint32_t)frame.data[5] << 16 |
                                                                                      (uint32_t)frame.data[6] << 8 |
                                                                                                                 (uint32_t)frame.data[7];
        break;
    case 16: //Status 4
        // Mosfet temp *10	Celcius?
        g_mosfet_temp =		(uint16_t)frame.data[0] << 8 |
                                                       (uint16_t)frame.data[1];
        // Motor temp * 10	Celcius?
        g_motor_temp =		(uint16_t)frame.data[2] << 8 |
                                                       (uint16_t)frame.data[3];
        // Total input current * 10		AMPS?
        g_input_current =	(uint16_t)frame.data[4] << 8 |
                                                       (uint16_t)frame.data[5];
        //Current PID position	?
        g_pid_position =	(uint16_t)frame.data[6] << 8 |
                                                       (uint16_t)frame.data[7];
        break;
    case 27: //Status 5
        //Tachometer value, rpm?
        g_tachometer = 			(uint32_t)frame.data[3] << 24 |
                                                           (uint32_t)frame.data[2] << 16 |
                                                                                      (uint32_t)frame.data[1] << 8 |
                                                                                                                 (uint32_t)frame.data[0];
        //Input voltage *10
        g_input_voltage =		(uint16_t)frame.data[4] << 8 |
                                                           (uint16_t)frame.data[5];
        break;
    default:
        printf("Koden er uden for kendt spektrum");
        break;
    }
} // decodeCANeid

//En funktion til at sende noget besked til VESC
//Sende max og minimums strømforbrug.
//Måske bedre at give max og min allerede som milliamp?
void set_VESC_current_max(uint32_t max, uint32_t min, int socket){
    uint32_t id = CAN_EFF_FLAG | 255 | (21<<8);
    uint8_t data[8];

    /*//Hvis ufaktoreret argumenter.
    //minumum value in position 0-3
    uint32_t min_factored = min * 1000; //either do this or give already faktored.
    data[0] = min_factored >> 24;
    data[1] = min_factored >> 16;
    data[2] = min_factored >> 8;
    data[3] = min_factored;
    //maximum value in position 4-7
    uint32_t max_factored = max * 1000;
    data[4] = max_factored >> 24;
    data[5] = max_factored >> 16;
    data[6] = max_factored >> 8;
    data[7] = max_factored;
    */

    //Hvis vi giver med faktor indregnet:
    //minumum value in position 0-3
    data[0] = min >> 24;
    data[1] = min >> 16;
    data[2] = min >> 8;
    data[3] = min;
    //maximum value in position 4-7
    data[4] = max >> 24;
    data[5] = max >> 16;
    data[6] = max >> 8;
    data[7] = max;

    CANwrite(socket, 8, id, data);
} //set_VESC_current_max

int setNonblocking(int fd)
{
    int flags;

    /* If they have O_NONBLOCK, use the Posix way to do it */
#if defined(O_NONBLOCK)
    /* Fixme: O_NONBLOCK is defined but broken on SunOS 4.1.x and AIX 3.2.5. */
    if (-1 == (flags = fcntl(fd, F_GETFL, 0)))
        flags = 0;
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
#else
    /* Otherwise, use the old way of doing it */
    flags = 1;
    return ioctl(fd, FIONBIO, &flags);
#endif
}     //setNonblocking


void CAN_msq_init(void){
    key_t key_sendqueue;
    //int g_msqid; // put in globals.
    //TODO: Where to place send queue.
    key_sendqueue = ftok("/home/pi/CANsendqueue", 'a');	//For pi
    //Testing:
    //key_sendqueue = ftok("/home/jorgen/CANsendqueue", 'a');		//For testing.
    printf("key_sendqueue = %d\n", key_sendqueue); //DEbug -1 is error
    if (key_sendqueue == -1) printf("Errno: %d\n",errno); //debug : -2 no such file. Skal oprette fil til ftok
    g_msqid = msgget(key_sendqueue, 0666 | IPC_CREAT);
    printf("g_msqid = %d\n", g_msqid); //DEbug
    if (g_msqid==-1){
        printf("Error on getting/creating queue.\n");
    }
}

int CAN_enqueue_frame(struct can_frame *can_frame_to_send){
    struct can_msgbuf{
        long mtype;
        struct can_frame frame;
    }msgbuf;
    msgbuf.mtype = 1;
    msgbuf.frame = *can_frame_to_send;
    //Take mutex
    pthread_mutex_lock(&g_mutex_can);
    /* stick him on the queue */
    if (msgsnd(g_msqid, &msgbuf, sizeof(struct can_frame), IPC_NOWAIT)==-1){
        perror("Error msgsnd");//debug
        printf("Error putting frame in queue\n");
        printf("errno %d\n",errno); //debug	EINVAL er 22 errno-base.h
        pthread_mutex_unlock(&g_mutex_can); //Give mutex back also when we fail.
        return -1;
    }
    //Give mutex back
    pthread_mutex_unlock(&g_mutex_can);
    return 0;
} //CAN_enqueue_frame

int CAN_dequeue_frame(struct can_frame *can_frame_to_receive){
    struct can_msgbuf{
        long mtype;
        struct can_frame frame;
    }msgbuf;

    //Take mutex
    pthread_mutex_lock(&g_mutex_can);
    /* stick him on the queue */
    if (msgrcv(g_msqid, &msgbuf, sizeof(struct can_frame), 0, MSG_NOERROR | IPC_NOWAIT)==-1){
        if(errno != ENOMSG){
            printf("Error getting frame from queue");
        }
        pthread_mutex_unlock(&g_mutex_can); //Give mutex back also when we fail.
        return -1;
    }
    //Give mutex back
    pthread_mutex_unlock(&g_mutex_can);
    //Put frame into the frame to recv.
    *can_frame_to_receive = msgbuf.frame;

    return 0;
} //CAN_dequeue_frame

struct can_frame can_make_frame(int code){
    struct can_frame frame;
    memset(&frame, 0, sizeof frame);
    switch(code){
    case Test:
        frame.can_id = 0x123;
        frame.can_dlc = 3;
        frame.data[0] = 255;
        frame.data[1] = 0;
        frame.data[2] = 255;
        break;
        //Big Endian
    case Status1:
        frame.can_id = 0x600;
        frame.can_dlc = 6;
        frame.data[1] = user_settings.driving_mode;
        frame.data[3] = g_speederInputPercent;    //TODO: Implement speederInputPercent
        frame.data[5] = g_speederOutputPercent;    //TODO: Implement speederOutputPercent
        break;
    default:
        break;
    }
    return frame;
}

#ifdef __cplusplus
}
#endif
