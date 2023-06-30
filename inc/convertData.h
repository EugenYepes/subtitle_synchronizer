#include "subtitle.h"

#ifndef CONVERTDATA_H
#define CONVERTDATA_H

/**
 * @brief Convert an unsigned string number to int 
 * 
 * @param str 
 * @param len 
 * @return the number on success. Negative value on error.
 */
int uatoi(unsigned char *str, int len);

/**
 * @brief 
 * 
 * @param str 
 * @param num 
 * @param len 
 * @return int 
 */
int itoua(unsigned char *str, int num, int *len);

/**
 * @brief parse the raw data from the buffer and fill the array of subtitles
 * check the type of the encoding text. UTF-16LE or UTF-8
 * 
 * @param fileRawData bytes readed from file 
 * @param subtitles array of subtitle to fill with the data
 * @return 0 on success, 1 otherwise 
 */
int stringToSubtitle(unsigned char *fileRawData, int sizeInput, Subtitle **subtitles, int *amountSubtitles);

/**
 * Instead of convert from utf-16le i can save the data in the struct, or have the option to save in utf-16le
 * @todo add doxy
 * @todo why add a lot of enters between lines? Add the 0x0D after 0x0D after saving the file. when print the file doesnt appear
 * @brief convert the hex data of a text file in UTF-16LE encoded to a UTF-8. Also change from 0x0D 0x0A enter to 0x0A
 * 
 * @param input_utf16le 
 * @param sizeInput 
 * @param out_utf8 
 * @param sizeOut 
 * @return int 
 *
*/
int utf16le_To_Utf8(unsigned char *input_utf16le, int sizeInput, unsigned char **out_utf8, int *sizeOut);

/**
 * @brief convert time string in format hh::mm:ss,sss to ms 
 * 
 * @param timeStr 
 * @return int 
 */
int timeStrToTimeMilliSec(unsigned char *timeStr);

#endif //CONVERTDATA_H