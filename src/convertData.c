#include "../inc/convertData.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int stringToSubtitle(unsigned char *fileRawData, int sizeInput, Subtitle **subtitles, int *amountSubtitles)
{
    int i = 0, startPos = 0;
    int step = NUM_SUBTITLE_STEP;
    if (fileRawData != NULL && sizeInput != 0) {
        *subtitles = (Subtitle *) malloc(sizeof(Subtitle));
        if (*subtitles != NULL) {
            for (i = 0; i < sizeInput; i++) {
                switch (step) {
                    case NUM_SUBTITLE_STEP:
                        if (fileRawData[i] == 0x0A) {
                            *subtitles = (Subtitle *) realloc((Subtitle *) *subtitles, sizeof(Subtitle) * ((*amountSubtitles) + 1));
                            if (*subtitles == NULL) {
                                printf("Error re-allocating memory at %s, Abort\n", __func__);
                                return 4;
                            }
                            (*subtitles)[*amountSubtitles].number = uatoi(&(fileRawData[startPos]), i - startPos);
                            step = START_TIME_STEP;
                            i++;
                            startPos = i;
                        }
                        break;
                    case START_TIME_STEP:
                        if (fileRawData[i] == ' ' && fileRawData[i + 1] == '-' && fileRawData[i + 2] == '-' && fileRawData[i + 3] == '>' && fileRawData[i + 4] == ' ') {
                            (*subtitles)[*amountSubtitles].startTimeMS = timeStrToTimeMilliSec(&(fileRawData[startPos]));
                            step = END_TIME_STEP;
                            i += 5;
                            startPos = i;
                        }
                        break;
                    case END_TIME_STEP:
                        if (fileRawData[i] == 0x0A) {
                            (*subtitles)[*amountSubtitles].endTimeMS = timeStrToTimeMilliSec(&(fileRawData[startPos]));
                            step = TEXT_STEP;
                            i++;
                            startPos = i;
                        }
                        break;
                    case TEXT_STEP:
                        if (fileRawData[i] == 0x0A && fileRawData[i + 1] == 0x0A) {
                            (*subtitles)[*amountSubtitles].text = (char *) malloc(sizeof(unsigned char) * (i - startPos + 1));
                            if ((*subtitles)[*amountSubtitles].text == NULL) {
                                printf("Error allocating memory at %s, Abort\n", __func__);
                                return 3;
                            }
                            memcpy((*subtitles)[*amountSubtitles].text, &(fileRawData[startPos]), i - startPos);
                            (*subtitles)[*amountSubtitles].text[i - startPos] = '\0';
                            step = NUM_SUBTITLE_STEP;
                            i += 2;
                            startPos = i;
                            (*amountSubtitles)++;
                        }
                        break;
                    default:
                        break;
                }
            }
        } else {
            printf("Error allocating memory at %s, Abort\n", __func__);
            return 2;
        }
    } else {
        printf("NULL pointer or cero size at %s, Abort\n", __func__);
        return 1;
    }
    return 0;
}

int subtitleToString(Subtitle *subtitles, int amountSubtitles, unsigned char *fileRawData, int fileSize)
{
    int i, j = 0;
    int lenNum = 0;
    if (subtitles != NULL) {
        memset(fileRawData, 0x00, fileSize);
        for (i = 0; i < amountSubtitles; i++) {
            // number
            lenNum = 0;
            itoua(&(fileRawData[j]), subtitles[i].number, &lenNum);
            fileRawData[j] = 0x0A;
            // start time
            // end time
            // text
        }
    } else {
        printf("NULL poiter at the input data at %s, Abort\n", __func__);
        return 1;
    }
    return 0;
}

int utf16le_To_Utf8(unsigned char *input_utf16le, int sizeInput, unsigned char **out_utf8, int *sizeOut)
{
    int i = 0, j = 0;
    *sizeOut = 0;
    if (input_utf16le != NULL) {
        // check the if the input has the utf-16le format
        if (input_utf16le[0] == 0xFF && input_utf16le[1] == 0xFE) {
            *sizeOut = (sizeInput / 2) - 2; // 2 bytes to indicate the format and half of bytes because utf-16le use the double amount of bytes than utf-8
            *out_utf8 = (unsigned char *) malloc(sizeof(unsigned char) * (*sizeOut));
            if (*out_utf8 != NULL) {
                // discard the 2 init bytes
                for (i = 2, j = 0; i < sizeInput; i += 2, j++) {
                    (*out_utf8)[j] = input_utf16le[i];
                      if ((*out_utf8)[j] == 0x0A && (*out_utf8)[j - 1] == 0x0D) {
                        (*out_utf8)[j - 1] = (*out_utf8)[j];
                        j--; // Discard de 0x0D byte
                    }
                }
                *out_utf8 = (unsigned char *) realloc((unsigned char *) *out_utf8, j * sizeof(unsigned char)); // resize output, because delete enters
                *sizeOut = j;
                if (*out_utf8 == NULL){
                    printf("Error re-allocating memory at %s, Abort\n", __func__);
                    return 4;
                }
            } else {
                printf("Error allocating memory at %s, Abort\n", __func__);
                return 3;
            }
        } else {
            printf("The data in the input string isn't in the utf-16le format, Abort\n");
            return 2;
        }
    } else {
        printf("NULL poiter at the input data at %s, Abort\n", __func__);
        return 1;
    }
    return 0;
}

int timeMilliSecTotimeStr(unsigned char *timeStr, int time)
{
    unsigned char auxTimeStr[12];
    // itoua(timeStr, (int) time/1000, 3);
    timeStr = auxTimeStr;
    return 0;
}

int timeStrToTimeMilliSec(unsigned char *timeStr)
{
    int timeMs = 0;
    if (timeStr != NULL) {
        // check format
        if (timeStr[2] == ':' && timeStr[5] == ':' && timeStr[8] == ',') {
            timeMs = uatoi(&(timeStr[9]), 3);                   // milli seconds
            timeMs += uatoi(&(timeStr[6]), 2) * 1000 ;          // seconds
            timeMs += uatoi(&(timeStr[3]), 2) * 60 * 1000;      // minutes
            timeMs += uatoi(&(timeStr[0]), 2) * 60 * 60 * 1000; // hours
            if (timeMs < 0) {
                printf("Error Unknown at %s, Abort\n", __func__);
                return -3;
            }
        } else {
            printf("Error in input string time format at %s, Abort\n", __func__);
            return -2;
        }
    } else {
        printf("NULL poiter at the input data at %s, Abort\n", __func__);
        return -1;
    }
    return timeMs;
}

int uatoi(unsigned char *str, int len)
{
    int i, num = 0;
    if (str != NULL) {
        for (i = 0; i < len; i++) {
            num = num * 10 + (str[i] - '0');
        }
    } else {
        printf("NULL poiter at the input data at %s, Abort\n", __func__);
        return -1;
    }
    return num;
}

int itoua(unsigned char *str, int num, int *len)
{
    int numBases = 10, i;
    int lenNum = 0, auxNum = num;

    // calculate the length of the number
    while (auxNum != 0) {
        auxNum = (int) auxNum / 10;
        lenNum++;
    }
    *len = lenNum;
    auxNum = num;
    if (num < 0) {
        lenNum++;
        auxNum = -num;
    }
    if (lenNum > 0) {
        str[lenNum] = '\0';
        for (i = (lenNum - 1); i >= 0; i--) {
            str[i] = (auxNum % 10) + '0';
            auxNum = (int) auxNum / 10;
        }
        if (num < 0) {
            str[0] = '-';
        }
    } else {
        printf("Error negative length of the number at %s, abort\n", __func__);
        return 1;
    }
    return 0;
}