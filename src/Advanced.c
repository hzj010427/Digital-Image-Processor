/*********************************************************************/
/* Updated by: Zijie Huang                                           */
/* Date:   02/26/2023                                                */
/*********************************************************************/

#include "Advanced.h"
#include "Image.h"
#include "Constants.h"

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

/* linear Normalize an image*/
Image *Normalize(Image *image, int newMinR, int newMaxR, int newMinG, int newMaxG, int newMinB, int newMaxB)
{
	/* Make sure the input pointer is valid */
	assert(image);

	int HEIGHT = ImageHeight(image);
	int WIDTH = ImageWidth(image);
	int MaxR = MIN_PIXEL, MaxG = MIN_PIXEL, MaxB = MIN_PIXEL;
	int MinR = MAX_PIXEL, MinG = MAX_PIXEL, MinB = MAX_PIXEL;

	for (int i = 0; i < WIDTH; i++ ) {
		for(int j = 0; j < HEIGHT; j++){
			if(GetPixelR(image, i, j) > MaxR)
        MaxR = GetPixelR(image, i, j);
			if(GetPixelG(image, i, j) > MaxG)
        MaxG = GetPixelG(image, i, j);
      if(GetPixelB(image, i, j) > MaxB)
        MaxB = GetPixelB(image, i, j);
			if(GetPixelR(image, i, j) < MinR)
        MinR = GetPixelR(image, i, j);
      if(GetPixelG(image, i, j) < MinG)
        MinG = GetPixelG(image, i, j);
			if(GetPixelB(image, i, j) < MinB)
        MinB = GetPixelB(image, i, j);
		}
	}
	
	
	for (int i = 0; i < WIDTH; i++ ) {
		for(int j = 0; j < HEIGHT; j++){
			SetPixelR(image, i, j, (GetPixelR(image, i, j) - MinR) * (newMaxR - newMinR) / (MaxR - MinR) + newMinR);
			SetPixelG(image, i, j, (GetPixelG(image, i, j) - MinG) * (newMaxG - newMinG) / (MaxG - MinG) + newMinG);
			SetPixelB(image, i, j, (GetPixelB(image, i, j) - MinB) * (newMaxB - newMinB) / (MaxB - MinB) + newMinB);
		}
	}
	return image;
}

/* make the image posterized */
Image *Posterize(Image *image, int rbits, int gbits, int bbits)
{
	/* Make sure the input pointer is valid */
	assert(image);

	int HEIGHT = ImageHeight(image);
	int WIDTH = ImageWidth(image);
	int x, y;
	for(x=0; x<WIDTH; x++) {
		for(y=0; y<HEIGHT; y++) {
			unsigned char one = 1;
			int i;
			for(i=0; i<rbits-1; i++) {
				SetPixelR(image, x, y, (GetPixelR(image, x, y)) | one);
				one <<= 1;
			}
			one = ~one;
			SetPixelR(image, x, y, (GetPixelR(image, x, y)) & one);

			one = 1;
			for(i=0; i<gbits-1; i++) {
				SetPixelG(image, x, y, (GetPixelG(image, x, y)) | one);
				one <<= 1;
			}
			one = ~one;
			SetPixelG(image, x, y, (GetPixelG(image, x, y)) & one);

			one = 1;
			for(i=0; i<bbits-1; i++) {
				SetPixelB(image, x, y, (GetPixelB(image, x, y)) | one);
				one <<= 1;
			}
			one = ~one;
			SetPixelB(image, x, y, (GetPixelB(image, x, y)) & one);
		}
	}
	return image;
}

/* rotate and zoom the image */
Image *Rotate(Image *image, double Angle, double ScaleFactor,  int CenterX, int CenterY)
{
	/* Make sure the input pointer is valid */
	assert(image);

	int HEIGHT = ImageHeight(image);
	int WIDTH = ImageWidth(image);
    unsigned char RotatedR[WIDTH][HEIGHT];
    unsigned char RotatedG[WIDTH][HEIGHT];
    unsigned char RotatedB[WIDTH][HEIGHT];
    int x, y;
    int x2, y2;
    const double pi = 3.14159265358979323846;
    double Radian;
    double ScaleX, ScaleY;
    double M[2][2];

    Radian = -Angle/360.0 * 2*pi;
    ScaleX = ScaleFactor;
    ScaleY = ScaleFactor;
    M[0][0] = cos(Radian)/ScaleX;
    M[0][1] = -sin(Radian)/ScaleX;
    M[1][0] = sin(Radian)/ScaleY;
    M[1][1] = cos(Radian)/ScaleY;
    for(y=0; y<HEIGHT; y++)
    {   for(x=0; x<WIDTH; x++)
        {
            x2 = (x-CenterX)*M[0][0] + (y-CenterY)*M[0][1] + CenterX;
            y2 = (x-CenterX)*M[1][0] + (y-CenterY)*M[1][1] + CenterY;
            if (  (x2<0) || (x2>WIDTH-1)
                ||(y2<0) || (y2>HEIGHT-1))
            {
		RotatedR[x][y] = 0;
		RotatedG[x][y] = 0;
		RotatedB[x][y] = 0;
            }
            else
            {
                RotatedR[x][y] = GetPixelR(image, x2, y2);
                RotatedG[x][y] = GetPixelG(image, x2, y2);
                RotatedB[x][y] = GetPixelB(image, x2, y2);
            }
        }
    }
    for(y=0; y<HEIGHT; y++)
    {   for(x=0; x<WIDTH; x++)
        {
		SetPixelR(image, x, y, RotatedR[x][y]);
		SetPixelG(image, x, y, RotatedG[x][y]);
		SetPixelB(image, x, y, RotatedB[x][y]);
        }
    }
    return image;
} /* end of Rotate */

/* add motion blur to the image */
Image *MotionBlur(Image *image, unsigned char BlurAmount)
{
	/* Make sure the input pointer is valid */
	assert(image);

	/* local varible declaration */
	
	int HEIGHT = ImageHeight(image);
	int WIDTH = ImageWidth(image);
	double sumR;
	double sumG;
	double sumB;
	int counter;

	/* calculate the new value of R G B for each pixel */

	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			sumR = 0;
			sumG = 0;
			sumB = 0;
			for (counter = 0; counter < BlurAmount; counter++) {
				if (i + counter >= WIDTH - 1) {
					break;
				}
				sumR += GetPixelR(image, i + counter + 1, j);
				sumG += GetPixelG(image, i + counter + 1, j);
				sumB += GetPixelB(image, i + counter + 1, j);
			}
			SetPixelR(image, i, j, ((GetPixelR(image, i, j)) / 2) + (sumR / counter / 2));
			SetPixelG(image, i, j, ((GetPixelG(image, i, j)) / 2) + (sumG / counter / 2));
			SetPixelB(image, i, j, ((GetPixelB(image, i, j)) / 2) + (sumB / counter / 2));
		}
	}	
	return image;
}
 
/* Crop */ 
Image *Crop(Image *image, int x, int y, int W, int H) {
	
	/* Make sure the input pointer is valid */
	assert(image);

	/* local varible declaration */

	Image *image_C;	
	int HEIGHT = ImageHeight(image);
	int WIDTH = ImageWidth(image);
	int H_C;
	int W_C;
    	unsigned char tmpR[WIDTH][HEIGHT];
    	unsigned char tmpG[WIDTH][HEIGHT];
    	unsigned char tmpB[WIDTH][HEIGHT];

	/* check if the crop amount exceeds the image W & H */
	if((x + W) > WIDTH - 1){
		W_C = WIDTH - x - 1;
	}
	else {
		W_C = W;
	}	
	if((y + H) > HEIGHT - 1){
		H_C = HEIGHT - y - 1;
	}
	else {
		H_C = H;
	}

	for (int i = 0; i < W_C; i++) {
		for (int j = 0; j < H_C; j++) {
			tmpR[i][j] = GetPixelR(image, i + x, j + y);
			tmpG[i][j] = GetPixelG(image, i + x, j + y);
			tmpB[i][j] = GetPixelB(image, i + x, j + y);
		}
	}
	
	/* create a new image */	
	image_C = CreateImage(W_C, H_C);
 
	for (int i = 0; i < W_C; i++) {
		for (int j = 0; j < H_C; j++) {
			SetPixelR(image_C, i, j, tmpR[i][j]);
			SetPixelG(image_C, i, j, tmpG[i][j]);
			SetPixelB(image_C, i, j, tmpB[i][j]);
		}
	}

	/* delete the original image */
	DeleteImage(image);

	return image_C;
}

/* Resize */
Image *Resize(Image *image, int newWidth, int newHeight) {
	
	/* Make sure the input pointer is valid */
	assert(image);

	/* local varible declaration */

	Image *image_resize;	
	int HEIGHT = ImageHeight(image);
	int WIDTH = ImageWidth(image);
	double ScaleX = (double)newWidth / WIDTH;
	double ScaleY = (double)newHeight / HEIGHT;

	/* create a new image */	
	image_resize = CreateImage(newWidth, newHeight);
	
	/* resize the image */
	
	for (int i = 0; i < newWidth; i++) {
		for (int j = 0; j < newHeight; j++) {
			SetPixelR(image_resize, i, j, GetPixelR(image, i / ScaleX, j / ScaleY));
			SetPixelG(image_resize, i, j, GetPixelG(image, i / ScaleX, j / ScaleY));
			SetPixelB(image_resize, i, j, GetPixelB(image, i / ScaleX, j / ScaleY));
		}
	}	

	/* delete the original image */
	DeleteImage(image);

	return image_resize;
}


/*  Watermark */
Image *Watermark(Image *image, const Image *watermark_image) {
		
	/* local varible declaration */
	
	int HEIGHT = ImageHeight(image);
	int WIDTH = ImageWidth(image);
	double tmpr;
	double tmpg;
	double tmpb;
	double factor = 1.45;
	
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			if (GetPixelR(watermark_image, i, j) == 0) {
				tmpr = (double)GetPixelR(image, i, j) * factor;
				if (tmpr > 255) {
					tmpr = 255;
				}
				SetPixelR(image, i, j, tmpr);
			}
			if (GetPixelG(watermark_image, i, j) == 0) {
				tmpg = (double)GetPixelG(image, i, j) * factor;
				if (tmpg > 255) {
					tmpg = 255;
				}
				SetPixelG(image, i, j, tmpg);
			}
			if (GetPixelB(watermark_image, i, j) == 0) {
				tmpb = (double)GetPixelB(image, i, j) * factor;
				if (tmpb > 255) {
					tmpb = 255;
				}
				SetPixelB(image, i, j, tmpb);
			}
		}
	}
	return image;	
} 

/* Brightness & Contrast */
Image *BrightnessAndContrast(Image *image, int brightness, int contrast) {
		
	/* local varible declaration */
	
	int HEIGHT = ImageHeight(image);
	int WIDTH = ImageWidth(image);
	double new_pixel_value_r;
	double new_pixel_value_g;
	double new_pixel_value_b;
	double factor;

	/* check if the brightness and contrast value is valid */
	
	if (brightness < -255 || brightness > 255 || contrast < -255 || contrast > 255) {
		printf("Error: the brightness and contrast value must be between -255 and 255\n");
		return 0;
	}

	/* factor calculation */

	factor = (double)(259 * (contrast + 255)) / (double)(255 * (259 - contrast));

	/* new_pixel_value calculation */

	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			new_pixel_value_r = GetPixelR(image, i, j);
			new_pixel_value_r = (double)(factor * (new_pixel_value_r - 128) + 128) + brightness;
			if (new_pixel_value_r < 0) {
				SetPixelR(image, i, j, 0);
			}	
			else if (new_pixel_value_r > 255) {
				SetPixelR(image, i, j, 255);
			}
			else {
				SetPixelR(image, i, j, new_pixel_value_r);
			}

			new_pixel_value_g = GetPixelG(image, i, j);
			new_pixel_value_g = (double)(factor * (new_pixel_value_g - 128) + 128) + brightness;
			if (new_pixel_value_g < 0) {
				SetPixelG(image, i, j, 0);
			}	
			else if (new_pixel_value_g > 255) {
				SetPixelG(image, i, j, 255);
			}
			else {
				SetPixelG(image, i, j, new_pixel_value_g);
			}

			new_pixel_value_b = GetPixelB(image, i, j);
			new_pixel_value_b = (double)(factor * (new_pixel_value_b - 128) + 128) + brightness;
			if (new_pixel_value_b < 0) {
				SetPixelB(image, i, j, 0);
			}	
			else if (new_pixel_value_b > 255) {
				SetPixelB(image, i, j, 255);
			}
			else {
				SetPixelB(image, i, j, new_pixel_value_b);
			}
		}
	}
	return image;	
}
/*	EOF Advanced.c		*/
