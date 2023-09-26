/*********************************************************************/
/* Updated by: Zijie Huang                                           */
/* Date:   02/26/2023                                                */
/*********************************************************************/

#ifndef ADVANCED_H_INCLUDED_
#define ADVANCED_H_INCLUDED_

#include "Constants.h"
#include "Image.h"

/* linear Normalize an image*/
Image *Normalize(Image *image, int newMinR, int newMaxR, int newMinG, int newMaxG, int newMinB, int newMaxB);

/* rotate and zoom the image */
Image *Rotate(Image *image, double Angle, double ScaleFactor,  int CenterX, int CenterY);

/* Posterize an image */
Image *Posterize(Image *image, int rbits, int gbits, int bbits);

/* Add motion blur to an image */
Image *MotionBlur(Image *image, unsigned char BlurAmount);

/* Crop */
Image *Crop(Image *image, int x, int y, int W, int H);

/* Resize */
Image *Resize(Image *image, int newWidth, int newHeight);

/* Watermark */
Image *Watermark(Image *image, const Image *watermark_image);

/* Brightness & Contrast */
Image *BrightnessAndContrast(Image *image, int brightness, int contrast);
#endif /* ADVANCED_H_INCLUDED_ */
