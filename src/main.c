#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../inc/convertData.h"
#include "../inc/subtitle.h"

/**
 * @brief Program to read a srt file and adding or subtract time to the timestamp
 * this is useful to fix unsync subtitles with the video
 * 
 * input a .srt file. (can be a UTF-16LE or UTF-8 format)
 * parse the file to the Subtitle struct
 * convert the time to miliseconds
 * add or substruct the diference between the reproduction time and the time of the subtitle, apply this to all the subtitles
 * save in a new file
 * 
 */

/**
 * @brief print in lines of 16 bytes the data
 * 
 * @param data pointer to data to print
 * @param size size of data
 */
void hexDump(unsigned char *data, int size);

int main(void)
{
    char fileName[50];
    FILE *fp;
    long fileSize;
    unsigned char *fileRawData = NULL;
    Subtitle *subtitles;
    int amountSubtitles = 0;
    int corrTimeValue;

    // open file
    printf("Enter file name or complete path: \n");
    scanf("%s", fileName);
    fp = fopen(fileName, "r+");

    // read file
    fseek(fp, 0L, SEEK_END);
    fileSize = ftell(fp);
    rewind(fp);
    fileRawData = (unsigned char *) malloc(sizeof(unsigned char) * fileSize);
    if (fileRawData == NULL) {
        printf("Error allocating memory, null pointer, Abort\n");
        fclose(fp);
        return 1;
    }
    fread(fileRawData, sizeof(unsigned char), fileSize, fp);
    stringToSubtitle(fileRawData, fileSize, &subtitles, &amountSubtitles);
    printf("%lld\n",strlen(subtitles[0].text));
    // hexDump(fileRawData, fileSize);

    printf("Enter the time correction in milliseconds.\n");
    printf("Positive number if the subtitle is behind\n");
    printf("Negative number if the subtitle is ahead\n");
    scanf("%d", &corrTimeValue);

    // change time
    correctTimeStamp(subtitles, amountSubtitles, corrTimeValue);

    // save the subtitles structs in a string
    subtitleToString(subtitles, amountSubtitles, fileRawData, fileSize);



    // Test conversion from utf16le to utf8
    // int outBufferSize = 0;
    // unsigned char *outBuffer;
    // utf16le_To_Utf8(fileRawData, fileSize, &outBuffer, &outBufferSize);
    // printf("outBuffer: \n");
    // hexDump(outBuffer, outBufferSize);
    // FILE *fp2 = fopen("out_utf8_test.srt", "w");
    // fwrite(outBuffer, sizeof(unsigned char), outBufferSize, fp2);
    // fclose(fp2);
    // free(outBuffer);

    fclose(fp);
    free(fileRawData);

    return 0;
}

void hexDump(unsigned char *data, int size)
{
    int i = 0;
    if (data != NULL) {
        for (i = 0; i < size; i++) {
            printf("%02X ", data[i]);
            if (((i + 1) % 16) == 0) {
                printf(" | %d \n", i);
            }
        }
    } else {
        printf("NULL pointer at %s, Abort\n", __func__);
    }
    printf("\n");
}

