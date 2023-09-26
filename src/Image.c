/*********************************************************************/
/* Updated by: Zijie Huang                                           */
/* Date:   02/26/2023                                                */
/*********************************************************************/

#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "Image.h"
#include "Constants.h"

/* Get the R intensity of pixel (x, y) in image */
unsigned char GetPixelR(const Image *image, unsigned int x,  unsigned int y) {
	/* Make sure the input pointer is valid */
	assert(image);
	/* Ensure that the coordinates are within the valid ranges for the image */
	assert(x < (image->W));
	assert(y < (image->H));

	return image->R[x + y * (image->W)];
}

/* Get the G intensity of pixel (x, y) in image */
unsigned char GetPixelG(const Image *image, unsigned int x,  unsigned int y) {
	/* Make sure the input pointer is valid */
	assert(image);
	/* Ensure that the coordinates are within the valid ranges for the image */
	assert(x < (image->W));
	assert(y < (image->H));

	return image->G[x + y * (image->W)];
}

/* Get the B intensity of pixel (x, y) in image */
unsigned char GetPixelB(const Image *image, unsigned int x,  unsigned int y) {
	/* Make sure the input pointer is valid */
	assert(image);
	/* Ensure that the coordinates are within the valid ranges for the image */
	assert(x < (image->W));
	assert(y < (image->H));

	return image->B[x + y * (image->W)];
}

/* Set the R intensity of pixel (x, y) in image to r */
void SetPixelR(Image *image, unsigned int x,  unsigned int y, unsigned char r) {
	/* Make sure the input pointer is valid */
	assert(image);
	/* Ensure that the coordinates are within the valid ranges for the image */
	assert(x < (image->W));
	assert(y < (image->H));

	image->R[x + y * (image->W)] = r;
}

/* Set the G intensity of pixel (x, y) in image to g */
void SetPixelG(Image *image, unsigned int x,  unsigned int y, unsigned char g) {
	/* Make sure the input pointer is valid */
	assert(image);
	/* Ensure that the coordinates are within the valid ranges for the image */
	assert(x < (image->W));
	assert(y < (image->H));

	image->G[x + y * (image->W)] = g;
}

/* Set the B intensity of pixel (x, y) in image to b */
void SetPixelB(Image *image, unsigned int x,  unsigned int y, unsigned char b) {
	/* Make sure the input pointer is valid */
	assert(image);
	/* Ensure that the coordinates are within the valid ranges for the image */
	assert(x < (image->W));
	assert(y < (image->H));

	image->B[x + y * (image->W)] = b;
}

/* Allocate dynamic memory for the image structure and its R/G/B values */
/* Return the pointer to the image, or NULL in case of error */
Image *CreateImage(unsigned int Width, unsigned int Height) {
	Image *image;
	image = malloc(sizeof(Image));
	image->W = Width;
	image->H = Height;
	image->R = malloc(sizeof(unsigned char) * Width * Height);
	image->G = malloc(sizeof(unsigned char) * Width * Height);
	image->B = malloc(sizeof(unsigned char) * Width * Height);
	/* Check the return value of malloc */
	if ((! image) || (! (image->R)) || (! (image->G)) || (! (image->B))) {
		perror("Out of memory!");
		/* Deallocate all the memory spaces for the image */
		free(image->R);
		free(image->G);
		free(image->B);
		free(image);
		return NULL;
	}
	return image;
}

/* Free the memory for the R/G/B values and Image structure */
void DeleteImage(Image *image) {
	/* Make sure the input pointer is valid */
	assert(image);

	free(image->R);
	free(image->G);
	free(image->B);
	free(image);
}

/* Return the image's width in pixels */
unsigned int ImageWidth(const Image *image) {
	/* Make sure the input pointer is valid */
	assert(image);

	return image->W;
}

/* Return the image's height in pixels */
unsigned int ImageHeight(const Image *image) {
	/* Make sure the input pointer is valid */
	assert(image);

	return image->H;
}

