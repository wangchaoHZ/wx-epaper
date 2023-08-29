/*****************************************************************************
* | File      	:   EPD_2in9d_test.c
* | Author      :   Waveshare team
* | Function    :   2.9inch e-paper d test demo
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2019-06-13
* | Info        :
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include "EPD_Test.h"
#include "EPD_2in9d.h"

int EPD_test(void)
{
    printf("EPD_2IN9D_test Demo\r\n");
    DEV_Module_Init();
    EPD_2IN9D_Init();
    printf("e-Paper Init and Clear...\r\n");

    EPD_2IN9D_Clear();
    // DEV_Delay_ms(500);

    // Create a new image cache
    UBYTE *BlackImage;
    /* you have to edit the startup_stm32fxxx.s file and set a big enough heap size */
    UWORD Imagesize = ((EPD_2IN9D_WIDTH % 8 == 0) ? (EPD_2IN9D_WIDTH / 8) : (EPD_2IN9D_WIDTH / 8 + 1)) * EPD_2IN9D_HEIGHT;
    if ((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL)
    {
        printf("Failed to apply for black memory...\r\n");
        return -1;
    }
    printf("Paint_NewImage\r\n");
    Paint_NewImage(BlackImage, EPD_2IN9D_WIDTH, EPD_2IN9D_HEIGHT, 270, WHITE);

#if 0 // show image for array    
    printf("show image for array\r\n");
    Paint_SelectImage(BlackImage);
    Paint_Clear(WHITE);
    Paint_DrawBitMap(gImage_2in9);

    EPD_2IN9D_Display(BlackImage);
    DEV_Delay_ms(2000);
#endif

#if 1 // Drawing on the image
    // 1.Select Image
    // printf("SelectImage:BlackImage\r\n");
    Paint_SelectImage(BlackImage);
    printf("Start........................\r\n");
    Paint_Clear(WHITE);
    printf("end........................\r\n");
    EPD_2IN9D_Display(BlackImage);

    // for (int x = 0; x < 100; x++)
    // {
    //     Paint_ClearWindows(60, 50, 150 + Font24.Width * 7, 80 + Font24.Height, WHITE);
    //     Paint_DrawNum(60, 50, x + 100, &Font24, BLACK, WHITE);
    //     EPD_2IN9D_DisplayPart(BlackImage);
    //     DEV_Delay_ms(500);
    // }

    Paint_DrawString_CN(130, 20, "บร", &Font24CN, BLACK, WHITE);
    // EPD_2IN9D_DisplayPart(BlackImage);
    // DEV_Delay_ms(2000);
    // EPD_2IN9D_DisplayPart(BlackImage);
    // DEV_Delay_ms(2000);
    // EPD_2IN9D_DisplayPart(BlackImage);
    // EPD_2IN9D_DisplayPart(BlackImage);
    // printf("EPD_Display\r\n");
    EPD_2IN9D_Display(BlackImage);
    DEV_Delay_ms(2000);
#endif

#if 0 // Partial refresh, example shows time
    printf("Partial refresh\r\n");
    PAINT_TIME sPaint_time;
    sPaint_time.Hour = 12;
    sPaint_time.Min = 34;
    sPaint_time.Sec = 56;
    UBYTE num = 20;
    for (;;)
    {
        sPaint_time.Sec = sPaint_time.Sec + 1;
        if (sPaint_time.Sec == 60)
        {
            sPaint_time.Min = sPaint_time.Min + 1;
            sPaint_time.Sec = 0;
            if (sPaint_time.Min == 60)
            {
                sPaint_time.Hour = sPaint_time.Hour + 1;
                sPaint_time.Min = 0;
                if (sPaint_time.Hour == 24)
                {
                    sPaint_time.Hour = 0;
                    sPaint_time.Min = 0;
                    sPaint_time.Sec = 0;
                }
            }
        }
        Paint_ClearWindows(150, 80, 150 + Font20.Width * 7, 80 + Font20.Height, WHITE);
        Paint_DrawTime(150, 80, &sPaint_time, &Font20, WHITE, BLACK);

        num = num - 1;
        if (num == 0)
        {
            break;
        }
        EPD_2IN9D_DisplayPart(BlackImage);
        DEV_Delay_ms(500); // Analog clock 1s
    }

#endif
    DEV_Delay_ms(2000 * 10);
    printf("Clear...\r\n");
    EPD_2IN9D_Init();
    EPD_2IN9D_Clear();
    DEV_Delay_ms(2000); // important, at least 2s
    printf("Goto Sleep...\r\n");
    EPD_2IN9D_Sleep();
    free(BlackImage);
    BlackImage = NULL;
    DEV_Delay_ms(2000); // important, at least 2s
    // close 5V
    printf("close 5V, Module enters 0 power consumption ...\r\n");
    DEV_Module_Exit();

    return 0;
}
