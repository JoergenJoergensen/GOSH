#ifndef GPIO_H
#define GPIO_H

#include "home.h"
#include "ui_home.h"
#include <stdio.h>

#define MAX_TAB_INDEX   (4)

// gpio paths
#define GPIO12_PATH     ("/sys/class/gpio/gpio2/value")        // Haptic Motor
#define GPIO26_PATH     ("/sys/class/gpio/gpio3/value")        // Watcher dødmandsknap
#define GPIO13_PATH     ("/sys/class/gpio/gpio4/value")        // dmuWatcher
#define GPIO19_PATH     ("/sys/class/gpio/gpio14/value")        // dmdWatcher
#define GPIO5_PATH      ("/sys/class/gpio/gpio22/value")         // tiuWatcher
#define GPIO6_PATH      ("/sys/class/gpio/gpio23/value")         // tidWatcher



#endif // GPIO_H
