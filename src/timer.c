#include "stm32f30x_conf.h" // STM32 config
#include "stm32f30x.h"
#include "30010_io.h" // Input/output library for this course
#include "ansi.h"
#include "time.h"

// timer code with interrupt function

void resetTimer(timestop_t *timer, int timeCount)
{
    timer->hr = 0;
    timer->hundSec = 0;
    timer->minute = 0;
    timer ->sec = 0;
    timeCount = 0;
}

void updateTimer(timestop_t *timer)
{

    timer->hundSec ++;

    if (timer->hundSec >= 100)
    {
        timer->sec ++;
        timer->hundSec = 0;
    }
    if (timer->sec >= 60)
    {
        timer->minute ++;
        timer->sec = 0;
    }
    if (timer->minute >= 60)
    {
        timer->hr ++;
        timer->minute = 0;
    }
}

void drawTimer(timestop_t *timer, int x, int y)
{
    int temp_hsec = timer->hundSec;
    int temp_sec = timer->sec;
    int temp_m = timer->minute;
    int temp_hr = timer->hr;

    gotoxy(x, y);
    printf("%d:%d:%d:%d", temp_hr, temp_m, temp_sec, temp_hsec);
}

