/*********************************************************************/
/* Updated by: Zijie Huang                                           */
/* Date:   02/26/2023                                                */
/*********************************************************************/

#include <stdio.h>
#include <string.h>

#include "Image.h"
#include "Test.h"
#include "DIPs.h"
#include "Advanced.h"
#include "FileIO.h"
#include "Constants.h"

/*** function declarations ***/

/* print a menu */
void PrintMenu();

int main(void)
{
#ifdef DEBUG
	int rc_test; 
	rc_test = AutoTest();
	if (rc_test != SUCCESS) {
		printf("AutoTest failed, error code %d.\n", rc_test);
	}
	else {
		printf("AutoTest finished successfully.\n");
	}
#else
	int freecheck = 0;		/* check if the allocated memory is freed */
  	int rc;
	int option;			/* user input option */
	char fname[SLEN];		/* input file name */
	char colorOption[SLEN];
	Image *image = NULL;		/* pointer initialization */
	
	PrintMenu();
	printf("Please make your choice: ");
	scanf("%d", &option);
	/* rc = -1; */

	/* ColorFilter() parameters */
	int target_r, target_g, target_b, threshold;
	double factor_r, factor_g, factor_b;

	/* AddBorder() parameter */
	int border_width;
	unsigned char rbits, gbits, bbits;

	/* Normalize() parameter */
	int newMinR, newMaxR, newMinG, newMaxG, newMinB, newMaxB;
	
	/* Rotate() parameter */
	double Angle, ScaleFactor;  
  	int CenterX, CenterY;

	/* MotionBlur() parameter */
	int motion_amount; 

	/* Crop() parameter */
	int x, y, W, H;

	/* Resize() parameter */
	int newW, newH;

	/* Brightness & Contrast() parameter */
	int B, C;

	/* Watermark parameter */
	Image *image_watermark = NULL;  
    	const char watermarkImgName[SLEN] = "watermark_template";

	while (option != EXIT) {
		if (option == 1) {
			if (freecheck == 1) {
				DeleteImage(image);
				freecheck = 0;
			}
			printf("Please input the file name to load: ");
			scanf("%s", fname);
			image = LoadImage(fname);
			if (image != NULL) {
				freecheck = 1;
			}
		}

		/* menu item 2 - 18 requires image is loaded first */
		else if (option >= 2 && option <= 18) {
			if (image == NULL)	 {
				printf("No image to process!\n");
			}
			/* now image is loaded */
			else {	
				switch (option) {
					case 2:
						printf("Please input the file name to save: ");
						scanf("%s", fname);
						SaveImage(fname, image);
						break;
					case 3:
						image = BlackNWhite(image);
						printf("\"Black & White\" operation is done!\n");
						break;
					case 4:
						image = Negative(image);
						printf("\"Negative\" operation is done!\n");
						break;
					case 5:
						printf("Enter Red   component for the target color: ");
						scanf("%d", &target_r);
						printf("Enter Green component for the target color: ");
						scanf("%d", &target_g);
						printf("Enter Blue  component for the target color: ");
						scanf("%d", &target_b);
						printf("Enter threshold for the color difference: ");
						scanf("%d", &threshold);
						printf("Enter value for Red component in the target color: ");
						scanf("%lf", &factor_r);
						printf("Enter value for Green component in the target color: ");
						scanf("%lf", &factor_g);
						printf("Enter value for Blue  component in the target color: ");
						scanf("%lf", &factor_b);

						image = ColorFilter(image, target_r, target_g, target_b, threshold, factor_r, factor_g, factor_b);
						printf("\"Color Filter\" operation is done!\n");
						break;
					case 6:
						image = Edge(image);
						printf("\"Edge\" operation is done!\n");
						break;
					case 7:
						image = Shuffle(image);
						printf("\"Shuffle\" operation is done!\n");
						break;
					case 8:
						image = HFlip(image);
						printf("\"HFlip\" operation is done!\n");
						break;
					case 9:
						image = HMirror(image);
						printf("\"HMirror\" operation is done!\n");
						break;
					case 10:
						printf("Enter border width:");
						scanf("%d", &border_width);
						printf("Available border colors : black, white, red, green, blue, yellow, cyan, pink, orange\n");
						printf("Select border color from the options: ");
						scanf("%s",colorOption);
						image = AddBorder(image, colorOption, border_width);
						printf("\"Border\" operation is done!\n");
						break;
					case 11: /* check */
						printf("Enter a new minimum value for the range of R channel:");
						scanf("%d", &newMinR);
						printf("Enter a new maximum value for the range of R channel:");
						scanf("%d", &newMaxR);
            					printf("Enter a new minimum value for the range of G channel:");
						scanf("%d", &newMinG);
						printf("Enter a new maximum value for the range of G channel:");
						scanf("%d", &newMaxG);
            					printf("Enter a new minimum value for the range of B channel:");
						scanf("%d", &newMinB);
						printf("Enter a new maximum value for the range of B channel:");
						scanf("%d", &newMaxB);
						image = Normalize(image, newMinR, newMaxR, newMinG, newMaxG, newMinB, newMaxB);
						printf("\"Normalize\" operation is done!\n");
						break;
					case 12:
						printf("Enter the number of posterization bits for R channel (1 to 8):");
						scanf("%hhu", &rbits);
						printf("Enter the number of posterization bits for G channel (1 to 8):");
						scanf("%hhu", &gbits);
						printf("Enter the number of posterization bits for B channel (1 to 8):");
						scanf("%hhu", &bbits);
						image = Posterize(image, rbits, gbits, bbits);
						printf("\"Posterize\" operation is done!\n"); 
						break;
					case 13: 
						printf("Enter the angle of rotation:");
						scanf("%lf", &Angle);
						printf("Enter the scale of zooming:");
						scanf("%lf", &ScaleFactor);
						printf("Enter the X-axis coordinate of the center of rotation:");
						scanf("%d", &CenterX);
						printf("Enter the Y-axis coordinate of the center of rotation:");
						scanf("%d", &CenterY);
						image = Rotate(image, Angle, ScaleFactor, CenterX, CenterY);
						printf("\"Rotate\" operation is done!\n");
						break;
					case 14: 
						printf("Please input motion blur amount: ");
						scanf("%d", &motion_amount);
						image = MotionBlur(image, motion_amount);
						printf("\"Motion Blur\" operation is done!\n"); 
						break;
					case 15: /* Crop */
						printf("Please enter the X offset value: ");
						scanf("%d", &x);
						printf("Please enter the Y offset value: ");
						scanf("%d", &y);
						printf("Please input the crop width: ");
						scanf("%d", &W);
						printf("Please input the crop height: ");
						scanf("%d", &H);
						image = Crop(image, x, y, W, H);
						printf("\"Crop\" operation is done!\n");
						break; 
					case 16: /* Resize */
						printf("Please input the new image width: ");
						scanf("%d", &newW);
						printf("Please input the new image height: ");
						scanf("%d", &newH);
						image = Resize(image, newW, newH);
						printf("\"Resizing the image\" operation is done!\n"); 
						break;
					case 17: /* B & C */
						printf("Please input the brightness level (integer between -255 - 255): ");
						scanf("%d", &B);
						printf("Please input the contrast level (integer between -255 - 255): ");
						scanf("%d", &C);
						image = BrightnessAndContrast(image, B, C);
						printf("\"Brightness and Contrast Adjustment\" operation is done!\n"); 
						break;
					case 18: /* Watermark */
						image_watermark = LoadImage(watermarkImgName);
						image = Watermark(image, image_watermark); 
						DeleteImage(image_watermark);
						printf("\"Watermark\" operation is done!\n"); 
						break;
					default:
						break;
				}
			}
		}

		else if (option == 19) {
			rc = AutoTest();
			if (rc != SUCCESS) {
				printf("AutoTest failed, error code %d.\n", rc);
			}
			else {
				printf("AutoTest finished successfully.\n");
			}	
		}
		else {
			printf("Invalid selection!\n");
		}

		/* Process finished, waiting for another input */
		PrintMenu();
		printf("Please make your choice: ");
		scanf("%d", &option);
	}

	/* prevent the memory leak when user does not save the file */
	if (freecheck == 1) {
		DeleteImage(image);
	}
	printf("You exit the program.\n");
#endif

	return 0;
}


/*******************************************/
/* Function implementations should go here */
/*******************************************/

/* Menu */
void PrintMenu() {
	printf("\n----------------------------\n");
	printf(" 1: Load a PPM image\n");
	printf(" 2: Save an image in PPM and JPEG format\n");
	printf(" 3: Change a color image to Black & White\n");
	printf(" 4: Make a negative of an image\n");
	printf(" 5: Color filter an image\n");
	printf(" 6: Sketch the edge of an image\n");
	printf(" 7: Shuffle an image\n");
	printf(" 8: Flip an image horizontally\n");
	printf(" 9: Mirror an image horizontally\n");
	printf("10: Add border to an image\n");
	printf("11: Normalize an image\n");
	printf("12: Posterize an image\n");
	printf("13: Rotate and zoom an image\n");
	printf("14: Motion Blur\n");
	printf("15: Crop an image\n");
	printf("16: Resize an image\n");	
	printf("17: Adjust the Brightness and Contrast of an image\n");	
	printf("18: Add Watermark to an image\n");	
	printf("19: Test all functions\n");	
	printf("20: Exit\n");
}

