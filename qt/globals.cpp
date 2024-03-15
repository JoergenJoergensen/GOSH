#include <sys/types.h>
#include <pthread.h>

#include "globals.h"

pthread_mutex_t g_mutex_can; // put in globals
int g_msqid;                 //message queue ID for the CAN - sending queue.

struct User_settings user_settings;

//Flags
volatile unsigned char g_status_message_send;

//Data:
