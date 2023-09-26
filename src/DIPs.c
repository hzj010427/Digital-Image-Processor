/*********************************************************************/
/* Updated by: Zijie Huang                                           */
/* Date:   02/26/2023                                                */
/*********************************************************************/

#include "DIPs.h"
#include "Image.h"
#include "Constants.h"

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>

/* reverse image color */
Image *Negative(Image *image) {
	/* Make sure the input pointer is valid */
	assert(image);

	int x, y;
	int HEIGHT = ImageHeight(image);
	int WIDTH = ImageWidth(image);
	for (y = 0; y < HEIGHT; y++) {
		for (x = 0; x < WIDTH; x++) {
			SetPixelR(image, x, y, MAX_PIXEL - GetPixelR(image, x, y));
			SetPixelG(image, x, y, MAX_PIXEL - GetPixelG(image, x, y));
			SetPixelB(image, x, y, MAX_PIXEL - GetPixelB(image, x, y));
		}
	}
	return image;
}

/* color filter */
Image *ColorFilter(Image *image, int target_r, int target_g, int target_b, int threshold, int replace_r, int replace_g, int replace_b) {
	/* Make sure the input pointer is valid */
	assert(image);

	int x, y;
	int HEIGHT = ImageHeight(image);
	int WIDTH = ImageWidth(image);

	replace_r = (replace_r > MAX_PIXEL) ? MAX_PIXEL : (replace_r < 0) ? 0 : replace_r;
	replace_g = (replace_g > MAX_PIXEL) ? MAX_PIXEL : (replace_g < 0) ? 0 : replace_g;
	replace_b = (replace_b > MAX_PIXEL) ? MAX_PIXEL : (replace_b < 0) ? 0 : replace_b;

	for (y = 0; y < HEIGHT; y++){
		for (x = 0; x < WIDTH; x++){
			if (abs(GetPixelR(image, x, y) - target_r) <= threshold
					&& abs(GetPixelG(image, x, y) - target_g) <= threshold
					&& abs(GetPixelB(image, x, y) - target_b) <= threshold) {
				SetPixelR(image, x, y, replace_r); 
				SetPixelG(image, x, y, replace_g); 
				SetPixelB(image, x, y, replace_b); 
			}
		}
	}
	return image;
}

/* edge detection */
Image *Edge(Image *image) {
	/* Make sure the input pointer is valid */
	assert(image);

	int             x, y, m, n, a, b;
	int HEIGHT = ImageHeight(image);
	int WIDTH = ImageWidth(image);
	unsigned char   tmpR[WIDTH][HEIGHT];
	unsigned char   tmpG[WIDTH][HEIGHT];
	unsigned char   tmpB[WIDTH][HEIGHT];
	for (y = 0; y < HEIGHT; y++){
		for (x = 0; x < WIDTH; x++) {
			tmpR[x][y] = GetPixelR(image, x, y);
			tmpG[x][y] = GetPixelG(image, x, y);
			tmpB[x][y] = GetPixelB(image, x, y);
		}
	}
	int sumR = 0;   /* sum of the intensity differences with neighbors */
	int sumG = 0;
	int sumB = 0;
	for (y = 1; y < HEIGHT - 1; y++){
		for (x = 1; x < WIDTH - 1; x++){
			for (n = -1; n <= 1; n++){
				for (m = -1; m <= 1; m++) {
					a = (x + m >= WIDTH) ? WIDTH - 1 : (x + m < 0) ? 0 : x + m;
					b = (y + n >= HEIGHT) ? HEIGHT - 1 : (y + n < 0) ? 0 : y + n;
					sumR += (tmpR[x][y] - tmpR[a][b]);
					sumG += (tmpG[x][y] - tmpG[a][b]);
					sumB += (tmpB[x][y] - tmpB[a][b]);
				}
			}
			SetPixelR(image, x, y, (sumR > MAX_PIXEL) ? MAX_PIXEL: (sumR < 0) ? 0: sumR); 
			SetPixelG(image, x, y, (sumG > MAX_PIXEL) ? MAX_PIXEL: (sumG < 0) ? 0: sumG); 
			SetPixelB(image, x, y, (sumB > MAX_PIXEL) ? MAX_PIXEL: (sumB < 0) ? 0: sumB); 
			sumR = sumG = sumB = 0;
		}
	}
	/* set all four borders to 0 */
	for (y = 0; y < HEIGHT; y++) {
		SetPixelR(image, 0, y, 0); 
		SetPixelG(image, 0, y, 0); 
		SetPixelB(image, 0, y, 0); 
		SetPixelR(image, WIDTH - 1, y, 0); 
		SetPixelG(image, WIDTH - 1, y, 0); 
		SetPixelB(image, WIDTH - 1, y, 0); 
	}
	for (x = 0; x < WIDTH; x++) {
		SetPixelR(image, x, 0, 0); 
		SetPixelG(image, x, 0, 0); 
		SetPixelB(image, x, 0, 0); 
		SetPixelR(image, x, HEIGHT - 1, 0); 
		SetPixelG(image, x, HEIGHT - 1, 0); 
		SetPixelB(image, x, HEIGHT - 1, 0); 
	}
	return image;
}

/* mirror image horizontally */
Image *HMirror(Image *image)
{
	/* Make sure the input pointer is valid */
	assert(image);

	int             x, y;
	int HEIGHT = ImageHeight(image);
	int WIDTH = ImageWidth(image);

	for (y = 0; y < HEIGHT; y++) {
		for (x = 0; x < WIDTH / 2; x++) {
			SetPixelR(image, WIDTH - 1 - x, y, GetPixelR(image, x, y));
			SetPixelG(image, WIDTH - 1 - x, y, GetPixelG(image, x, y));
			SetPixelB(image, WIDTH - 1 - x, y, GetPixelB(image, x, y));
		}
	}
	return image;
}

/* add border to the image */
Image *AddBorder(Image *image, char *color, int border_width) {
	/* Make sure the input pointer is valid */
	assert(image);

	int x, y;
	int HEIGHT = ImageHeight(image);
	int WIDTH = ImageWidth(image);
	
	int border_r = 255;
	int border_g = 255;
	int border_b = 255;
	if (!strcmp(color, "black")) {
		border_r = 0;
		border_g = 0;
		border_b = 0;
	} else if (!strcmp(color, "white")) {
		border_r = 255;
		border_g = 255;
		border_b = 255;
	} else if (!strcmp(color, "red")) {
		border_r = 255;
		border_g = 0;
		border_b = 0;
	} else if (!strcmp(color, "green")) {
		border_r = 0;
		border_g = 255;
		border_b = 0;
	} else if (!strcmp(color, "blue")) {
		border_r = 0;
		border_g = 0;
		border_b = 255;
	} else if (!strcmp(color, "yellow")) {
		border_r = 255;
		border_g = 255;
		border_b = 0;
	} else if (!strcmp(color, "cyan")) {
		border_r = 0;
		border_g = 255;
		border_b = 255;
	} else if (!strcmp(color, "pink")) {
		border_r = 255;
		border_g = 192;
		border_b = 203;
	} else if (!strcmp(color, "orange")) {
		border_r = 255;
		border_g = 165;
		border_b = 0;
	} else {
		printf("Unsurported color.\n");
		return image;
	}
	for (y = 0; y < HEIGHT; y++) {
		for (x = 0; x < WIDTH; x++) {
			if ((y < border_width) || (y > HEIGHT - 1 - border_width) ||
					(x < border_width) || (x > WIDTH - 1 - border_width)) {
				SetPixelR(image, x, y, border_r);
				SetPixelG(image, x, y, border_g);
				SetPixelB(image, x, y, border_b);
			}
		}
	}
	return image;
}

/* change color image to black & white */
Image *BlackNWhite(Image *image)
{
	/* Make sure the input pointer is valid */
	assert(image);

	int             x, y, tmp;
	int HEIGHT = ImageHeight(image);
	int WIDTH = ImageWidth(image);

	for (y = 0; y < HEIGHT; y++)
	{
		for (x = 0; x < WIDTH; x++)
		{
			tmp = (GetPixelR(image, x, y) + GetPixelG(image, x, y) + GetPixelB(image, x, y)) / 3;
			SetPixelR(image, x, y, tmp);
			SetPixelG(image, x, y, tmp);
			SetPixelB(image, x, y, tmp);
		}
	}
	return image;
}

/* flip image horizontally */
Image *HFlip(Image *image)
{
	/* Make sure the input pointer is valid */
	assert(image);

	int HEIGHT = ImageHeight(image);
	int WIDTH = ImageWidth(image);
	int             x, y;
	unsigned char   r, g, b;

	for (y = 0; y < HEIGHT; y++) {
		for (x = 0; x < WIDTH / 2; x++) {
			r = GetPixelR(image, WIDTH - 1 - x, y);
			g = GetPixelG(image, WIDTH - 1 - x, y);
			b = GetPixelB(image, WIDTH - 1 - x, y);

			SetPixelR(image, WIDTH - 1 - x, y, GetPixelR(image, x, y));
			SetPixelG(image, WIDTH - 1 - x, y, GetPixelG(image, x, y));
			SetPixelB(image, WIDTH - 1 - x, y, GetPixelB(image, x, y));

			SetPixelR(image, x, y, r);
			SetPixelG(image, x, y, g);
			SetPixelB(image, x, y, b);
		}
	}
	return image;
}

/* Shuffle the image */
Image *Shuffle(Image *image) 
{
	/* Make sure the input pointer is valid */
	assert(image);

	int HEIGHT = ImageHeight(image);
	int WIDTH = ImageWidth(image);
	int block_cnt = SHUFF_HEIGHT_DIV * SHUFF_WIDTH_DIV;
	int block_width = WIDTH/SHUFF_WIDTH_DIV;
	int block_height = HEIGHT/SHUFF_HEIGHT_DIV;
	int block[SHUFF_WIDTH_DIV][SHUFF_HEIGHT_DIV];
	int i, j;

	srand(time(NULL));
	/* Initialize block markers to not done (-1) */
	for (i = 0; i < SHUFF_WIDTH_DIV; i++) {
		for (j = 0; j< SHUFF_HEIGHT_DIV; j++) {
			block[i][j] = -1;
		}
	}

	while (block_cnt > 0) {
		/* Generate a random pair of blocks */
		int dest_height = rand() % SHUFF_HEIGHT_DIV;
		int dest_width = rand() % SHUFF_WIDTH_DIV;
		int src_height = rand() % SHUFF_HEIGHT_DIV;
		int src_width = rand() % SHUFF_WIDTH_DIV;

		/* Check if these blocks are already swaped, if not swap blocks */
		if ((block[dest_width][dest_height] == -1) && (block[src_width][src_height] == -1) && (dest_height!=src_height || dest_width!=src_width)) {
			/* Swap blocks */
			for (i = 0; i < block_height; i++) {
				/* Init src and dest height offset */
				int h_dest = ((dest_height * block_height) + i) % HEIGHT;
				int h_src  = ((src_height * block_height) + i) % HEIGHT;
				for (j = 0; j < block_width; j++) {
					int temp;
					/* Init src and dest width offset */
					int w_src  = ((src_width * block_width) + j) % WIDTH;
					int w_dest = ((dest_width * block_width) + j) % WIDTH;

					temp = GetPixelR(image, w_dest, h_dest);
					SetPixelR(image, w_dest, h_dest, GetPixelR(image, w_src, h_src));
					SetPixelR(image, w_src, h_src, temp);

					temp = GetPixelG(image, w_dest, h_dest);
					SetPixelG(image, w_dest, h_dest, GetPixelG(image, w_src, h_src));
					SetPixelG(image, w_src, h_src, temp);

					temp = GetPixelB(image, w_dest, h_dest);
					SetPixelB(image, w_dest, h_dest, GetPixelB(image, w_src, h_src));
					SetPixelB(image, w_src, h_src, temp);
				}
			}
			/* Set marker as done */
			block[dest_width][dest_height] = 1;
			block[src_width][src_height] = 1;
			/* Decrease block count */
			block_cnt -= 2; /* Two blocks are swapped */
		}
	}
	return image;
}
