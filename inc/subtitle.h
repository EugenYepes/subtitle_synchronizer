#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef SUBTITLE_H
#define SUBTITLE_H

typedef struct subtitle
{
    int number;
    int startTimeMS;
    int endTimeMS;
    char *text;
} Subtitle;

enum ParseSteps{
    NUM_SUBTITLE_STEP,
    START_TIME_STEP,
    END_TIME_STEP,
    TEXT_STEP
};

/**
 * @brief Construct a new correct Time Stamp object
 * 
 * @param subtitles 
 * @param amountSubtitles 
 * @param corrTimeValue 
 */
int correctTimeStamp(Subtitle *subtitles, int amountSubtitles, int corrTimeValue);

#endif //SUBTITLE_H