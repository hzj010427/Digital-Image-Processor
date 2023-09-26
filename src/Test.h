/*********************************************************************/
/* Updated by: Zijie Huang                                           */
/* Date:   02/26/2023                                                */
/*********************************************************************/

#ifndef TEST_H
#define TEST_H

/* Test all DIPs */
int AutoTest(void);

/* test parameters used in AutoTest() */
/* parameters for color filter */
#define CF_TARGET_R 250
#define CF_TARGET_G 250
#define CF_TARGET_B 250
#define CF_THRESHOLD 60
#define CF_REPLACED_R 0
#define CF_REPLACED_G 0
#define CF_REPLACED_B 255

#define NOISE_PERCENTAGE 9


/* border */
#define BORDER_WIDTH 32

/* posterize */
#define R_BITS 7
#define G_BITS 7
#define B_BITS 7

/* motion blur */
#define BLUR_AMOUNT 40

/* crop */
#define CROP_X 150
#define CROP_Y 40
#define CROP_WIDTH 250
#define CROP_HEIGHT 100

/* resize */
#define BIG_RESIZE_WIDTH 800
#define BIG_RESIZE_HEIGHT 400
#define SMALL_RESIZE_WIDTH 300
#define SMALL_RESIZE_HEIGHT 200

/* brightness and contrast */
#define BRIGHTNESS 20
#define CONTRAST 200

#endif /* TEST_H */
