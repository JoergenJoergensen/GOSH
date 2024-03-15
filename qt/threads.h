#ifndef THREADS_H
#define THREADS_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <signal.h>           /* Definition of SIGEV_* constants */
#include <time.h>			// -lrt
#include <pthread.h>		//-lpthread
//  Speed control
void *SpeedControl(void *argument);
int GoshThreadInitSpeedControl(void);

//  CAN control
void *CANThread(void *argument);
int GoshThreadInitCAN(void);
int SetupStatusTimer(void);
void StatusMessageHandler(int signo, siginfo_t *info, void *context);

extern __uint8_t g_speederInputPercent;
extern __uint8_t g_speederOutputPercent;

extern int g_speederInput;
extern int g_speederOutput;

#ifdef __cplusplus
}
#endif

#endif // THREADS_H
