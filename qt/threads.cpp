#ifdef __cplusplus
extern "C"
{
#endif


#include "globals.h"
#include "threads.h"
#include "spi.h"
#include "ourCAN.h"


uint8_t g_speederInputPercent;
uint8_t g_speederOutputPercent;
int g_speederInput;
int g_speederOutput;


void *SpeedControl(void *argument)
{
    //do I need to set smth up?
    int ADC = 0; //variable for ADC reading and calc what to give to DAC.
    int ADCprev = 0; //previous ADC measurement.
    //Factor for getting DAC value. Because ADC 4096 levels, DAC 256 levels (12vs8bit)
    //DAC V_ref with gain 4.096V
    const float DAC_factor = 3.3/4.096/16;

    while(1)
    {
        if (user_settings.driving_mode == DRIVE_MODE_RACE)
        {
            //RACE mode. Follow throttle
            ADC = AnalogRead(0);	//Read channel 0
            //Write to channel 0. Calculate the value to give to DAC.
            AnalogWrite(0, ADC*DAC_factor);
            g_speederInput = ((ADC-709)*100)/2650;
            g_speederOutput = ((ADC*DAC_factor - 44)*100)/166;

        }
        else if (user_settings.driving_mode == DRIVE_MODE_NORMAL)
        {	//HALF the throttle input
            ADC = AnalogRead(0);	//Read channel 0
            //Write to channel 0. Calculate the value to give to DAC. Divide by 2 to get half the input.
            AnalogWrite(0, ADC*DAC_factor/2);
            g_speederInput = ((ADC-709)*100)/2650;
            g_speederOutput = (((ADC*DAC_factor/2) - 44)*100)/166;

        }
        else if (user_settings.driving_mode == DRIVE_MODE_ECO)
        {
            ADC = AnalogRead(0);


            AnalogWrite(0, ADC*DAC_factor/4);
            g_speederInput = ((ADC-709)*100)/2650;
            g_speederOutput = (((ADC*DAC_factor/4) - 44)*100)/166;
        }
        if (g_speederInput > 100)
        {
            g_speederInput = 100;
        }
        else if (g_speederInput < 0)
        {
            g_speederInput = 0;
        }

        if (g_speederOutput > 100)
        {
            g_speederOutput = 100;
        }
        else if (g_speederOutput < 0)
        {
            g_speederOutput = 0;
        }

        g_speederInputPercent = g_speederInput;
        g_speederOutputPercent = g_speederOutput;
        ADCprev = ADC;
        sleep(0.009); // We should be able to update 100 times per second.
    }
    pthread_exit(NULL); // Should never make it to here.
}

int GoshThreadInitSpeedControl(void)
{
    //Init ADC and DAC
    InitADC_DAC(1000000, 0);
    // make a pthread_t to use. If we need to know the id later, we need to do smth with it.
    pthread_t myThread;
    //  Make thread
    if (pthread_create(&myThread, NULL, SpeedControl, NULL))
    {
        // 0 on success
        printf("Failed to create speed control thread.\n"); // Should we write to syslog?
        return 1;
    }

    return 0;
}


void *CANThread(void *argument)
{
    //Init mutex
    pthread_mutex_init(&g_mutex_can, NULL); // put into init the CAN thread
    //Create socket
    int socket = createSocket("can0");	//Create socket
    //Testing:
    //int socket = createSocket("vcan0");		//Testing. TODO: Remove after testing.. used vcan for first test
    setNonblocking(socket);				//Set nonblocking
    //Init Queue
    CAN_msq_init();
    //Can Freme Buffer
    struct can_frame myFrame;			//Struct for holding the can frame being worked with
    //Setup timer and handler.
    SetupStatusTimer();


    //TODO: Set up timer and callback function. Queue. Making the frames...

    //read. Non blocking socket?!
    //write using queue? Mutex.
    //Timer and handler to send periodic messages?
    while(1)
    {
        //CANread_for_nonblocking(socket, &myFrame);
        //decodeCAN(myFrame);

        //If something is read, decode it.
        if (CANread_for_nonblocking(socket, &myFrame) == 0)
        {
            decodeCAN(myFrame);
        }

        //Send status message if flag set
        if (g_status_message_send == 1)
        {		// == 1 should not be needed. Flag set by handler.
            myFrame = can_make_frame(Status1);
            if (CANwrite_frame(socket, &myFrame)==-1)
            {
                printf("Error writing CAN_frame - status1\n");
            }
            //Reset / clear flag
            g_status_message_send = 0;
        }
        //Read CAN_frame from Queue:
        //*can_frame = smth from queue;
        if (!CAN_dequeue_frame(&myFrame))
        {	//if successfully got item
            //Send it on queue.
            if (CANwrite_frame(socket, &myFrame))
            {
                printf("Error writing CAN_frame\n");
            }
        }

        /*//Send - do I need to check if smth is to be send first.
        if (!CANwrite_frame(socket, &myFrame)){
            printf("Error writing CAN_frame");
        }*/

    }
    pthread_exit(NULL); // Should never make it to here.
}


int GoshThreadInitCAN(void)
{
    pthread_t myThread;

    //Make thread
    if (pthread_create(&myThread, NULL, &CANThread, NULL))
    {
        // 0 on success
        printf("Failed to create CAN control thread.\n"); //Should we write to syslog?
        return 1;
    }
    return 0;
}

int SetupStatusTimer(void)
{
    timer_t timerid;
    struct sigevent sev;
    struct itimerspec its;
    struct sigaction sa;


    /* Establish handler for timer signal. */
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = &StatusMessageHandler;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGRTMIN, &sa, NULL) == -1)
    {
        printf("Error, sigaction");
        return -1;
    }

    /* Create the timer. */
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGRTMIN;
    sev.sigev_value.sival_ptr = &timerid;
    if (timer_create(CLOCK_MONOTONIC, &sev, &timerid) == -1)
    {
        printf("Error, timer_create");
        return -1;
    }


    its.it_value.tv_sec = 1;
    its.it_value.tv_nsec = 0;
    its.it_interval.tv_sec = its.it_value.tv_sec;
    its.it_interval.tv_nsec = its.it_value.tv_nsec;

    if (timer_settime(timerid, 0, &its, NULL) == -1)
    {
        printf("Error, timer_settime");
        return -1;
    }

    return 0;
}

void StatusMessageHandler(int signo, siginfo_t *info, void *contex)
{
    //What to do in the message handler. Should we set a flag to not have to get mutex and que?!
    g_status_message_send = 1;
    //Debug TODO: Remove
    //printf("Status_message_handler\n"); //Debug
}


#ifdef __cplusplus
}
#endif


