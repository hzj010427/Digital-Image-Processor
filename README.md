When the user selects option 1 in the menu, the code prompts the user to input a file name and then calls the LoadImage function. This function returns a pointer to an Image data structure, which is stored in the "image" pointer. This allows the program to access the image data for processing.

For the menu options 2 to 18, the program performs various operations on the image data stored in the "image" pointer. Each of these operations is implemented as a separate function, which takes the "image" pointer as a parameter and returns the processed image. These functions modify the image data stored in memory by changing the values stored at the memory addresses pointed to by the "image" pointer.

The program also uses other pointers such as "image_watermark" in the "Watermark" operation, which is used to store the watermark image data. This pointer is declared and initialized to NULL and is later used to store the watermark image data after it has been loaded from a file.

Overall, the code extensively uses pointers to manipulate and access image data stored in memory, allowing it to perform various image editing operations efficiently.

Crop: This function crops an image by taking a rectangular region specified by the x, y, W, and H parameters. The function first checks if the crop region exceeds the width or height of the original image and adjusts the crop region accordingly. It then copies the rectangular region to a temporary array and creates a new Image with the same data. Finally, it deletes the original image and returns the new cropped image.

Resize: This function resizes an image by taking the new width and height as arguments. The function first calculates the scaling factors for width and height. It then creates a new Image with the specified new dimensions and resizes the original image by copying the pixel values from the original to the new image using the scaling factors. Finally, it deletes the original image and returns the new resized image.

Watermark: This function adds a watermark to an image by taking a watermark image as an argument. The function iterates over each pixel of the original image and multiplies the red, green, and blue values by a factor if the corresponding pixel intensity in the watermark image is 0. It then returns the original image with the watermark.

BrightnessAndContrast: This function adjusts the brightness and contrast of an image by taking the brightness and contrast values as arguments. The function first checks if the brightness and contrast values are within the valid range. It then calculates a scaling factor based on the contrast value and adjusts the red, green, and blue values of each pixel by adding the brightness value and multiplying by the scaling factor. Finally, it returns the original image with the adjusted brightness and contrast.
