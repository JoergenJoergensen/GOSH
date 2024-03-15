#ifndef GLOBALS_H
#define GLOBALS_H

#include "threads.h"

extern pthread_mutex_t g_mutex_can;
extern int g_msqid;
extern struct User_settings user_settings;
extern volatile unsigned char g_status_message_send;

typedef enum
{
    DRIVE_MODE_RACE,
    DRIVE_MODE_NORMAL,
    DRIVE_MODE_ECO,
} Driving_mode;

typedef enum
{
    Test,
    Status1,
} CAN_frame_code;


/*struct User_settings{
    int driving_mode;
};*/
struct User_settings
{
    volatile unsigned char driving_mode;
};


#endif // GLOBALS_H
