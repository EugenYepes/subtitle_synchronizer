#include "../inc/subtitle.h"

int correctTimeStamp(Subtitle *subtitles, int amountSubtitles, int corrTimeValue)
{
    int i;
    if (subtitles != NULL) {
        if (corrTimeValue != 0) {
            for (i = 0; i < amountSubtitles; i++) {
                subtitles[i].startTimeMS += corrTimeValue;
                subtitles[i].endTimeMS += corrTimeValue;
            }
        } else {
            printf("No correction time to apply\n");
            return 0;
        }
    } else {
        printf("NULL poiter at the input data at %s, Abort\n", __func__);
        return 1;
    }
    return 0;
}