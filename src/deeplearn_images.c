/*
 libdeep - a library for deep learning
 Copyright (C) 2013  Bob Mottram <bob@robotics.uk.to>

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:
 1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
 2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
 3. Neither the name of the University nor the names of its contributors
    may be used to endorse or promote products derived from this software
    without specific prior written permission.
 .
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE HOLDERS OR
 CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "deeplearn_images.h"


/**
* @brief Reads a PNG file into a buffer
* @param filename Filename of the image
* @param width Returned width of the image in pixels
* @param height Returned height of the image in pixels
* @param buffer Image buffer (3 bytes per pixel)
*/
void deeplearn_read_png(char * filename,
                        int * width, int * height,
                        unsigned char ** buffer)
{
    png_structp png_ptr;
    png_infop info_ptr;
    int y,n,bpp,i;
    png_bytep * row_pointers;

    /** 8 is the maximum size that can be checked */
    char header[8];

    /** open file and test for it being a png */
    FILE *fp = fopen(filename, "rb");
    if (!fp)
        printf("[read_png_file] File %s could not be opened for reading", filename);

    if (fread(header, 1, 8, fp) == 0) {
        *width = 0;
        *height = 0;
        fclose(fp);
        return;
    }

    if (png_sig_cmp((png_bytep)header, 0, 8))
        printf("[read_png_file] File %s is not recognized as a PNG file", filename);


    /** initialize stuff */
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png_ptr)
        printf("[read_png_file] png_create_read_struct failed");

    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
        printf("[read_png_file] png_create_info_struct failed");

    if (setjmp(png_jmpbuf(png_ptr)))
        printf("[read_png_file] Error during init_io");

    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, 8);

    png_read_info(png_ptr, info_ptr);

    *width = png_get_image_width(png_ptr, info_ptr);
    *height = png_get_image_height(png_ptr, info_ptr);

    png_read_update_info(png_ptr, info_ptr);

    /** read the image from file */
    if (setjmp(png_jmpbuf(png_ptr)))
        printf("[read_png_file] Error during read_image");

    row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * (*height));
    for (y = 0; y < *height; y++) {
        row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));
    }
    png_read_image(png_ptr, row_pointers);

    /** convert into a standard form */
    *buffer = (unsigned char*)malloc((*width)*(*height)*3*
                                     sizeof(unsigned char));
    n = 0;
    bpp = png_get_rowbytes(png_ptr,info_ptr)/(*width);
    for (y = 0; y < *height; y++) {
        for (i = 0; i < png_get_rowbytes(png_ptr,info_ptr);
             i += bpp, n += 3) {
            switch(bpp) {
            case 3: {
                (*buffer)[n] = (unsigned char)row_pointers[y][i];
                (*buffer)[n+1] = (unsigned char)row_pointers[y][i+1];
                (*buffer)[n+2] = (unsigned char)row_pointers[y][i+2];
                break;
            }
            case 1: {
                (*buffer)[n] = (unsigned char)row_pointers[y][i];
                (*buffer)[n+1] = (*buffer)[n];
                (*buffer)[n+2] = (*buffer)[n];
                break;
            }
            case 6: {
                (*buffer)[n] = (unsigned char)(row_pointers[y][i+1]>>8);
                (*buffer)[n+1] = (unsigned char)(row_pointers[y][i+2]>>8);
                (*buffer)[n+2] = (unsigned char)(row_pointers[y][i+4]>>8);
                break;
            }
            }
        }
    }

    /** free the row pointers */
    for (y=0; y < *height; y++) free(row_pointers[y]);
    free(row_pointers);

    fclose(fp);
}


/**
* @brief Saves an image buffer to a PNG formatted image
* @param filename Filename of the image
* @param width Width of the image in pixels
* @param height Height of the image in pixels
* @param buffer Image buffer (3 bytes per pixel)
* @return 1 on success
*/
int deeplearn_write_png(char* filename,
                        int width, int height,
                        unsigned char *buffer)
{
    png_structp png_ptr;
    png_infop info_ptr;
    int y,n,i;
    png_bytep * row_pointers;

    /** create file */
    FILE *fp = fopen(filename, "wb");

    if (!fp)
        printf("[write_png_file] File %s could not be opened for writing", filename);


    /** initialize stuff */
    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png_ptr)
        printf("[write_png_file] png_create_write_struct failed");

    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
        printf("[write_png_file] png_create_info_struct failed");

    if (setjmp(png_jmpbuf(png_ptr)))
        printf("[write_png_file] Error during init_io");

    png_init_io(png_ptr, fp);

    /** write header */
    if (setjmp(png_jmpbuf(png_ptr)))
        printf("[write_png_file] Error during writing header");

    /** create info */
    png_set_IHDR(png_ptr, info_ptr, width, height,
                 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    /** save the info */
    png_write_info(png_ptr, info_ptr);

    /** write bytes */
    if (setjmp(png_jmpbuf(png_ptr)))
        printf("[write_png_file] Error during writing bytes");

    /** create row pointers */
    row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * (height));
    for (y = 0; y < height; y++) {
        row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));
    }

    /** save image data into row pointers */
    n = 0;
    for (y = 0; y < height; y++) {
        for (i = 0; i < width*3; i++, n++) {
            row_pointers[y][i] = buffer[n];
        }
    }

    /** write the row pointers */
    png_write_image(png_ptr, row_pointers);

    /** end write */
    if (setjmp(png_jmpbuf(png_ptr)))
        printf("[write_png_file] Error during end of write");

    png_write_end(png_ptr, NULL);

    /** free row pointers */
    for (y = 0; y < height; y++) {
        free(row_pointers[y]);
    }
    free(row_pointers);

    fclose(fp);
    return 1;
}

/**
* @brief Returns the number of images within the given directory having
*        a given extension
* @param images_directory The directory to search within
* @param extension Filename extension (eg. "png")
* @return Number of images found
*/
static int number_of_images(char * images_directory,
                            char * extension)
{
    int ctr,no_of_images = 0;
    struct dirent **namelist;
    int n,len;

    /** get image filenames */
    n = scandir(images_directory, &namelist, 0, alphasort);
    if (n >= 0) {
        /** count the number of image files */
        ctr = n;
        while (ctr--) {
            /** is the filename long enough? */
            len = strlen(namelist[ctr]->d_name);
            if (len > 4) {
                /** is this a png image? */
                if ((namelist[ctr]->d_name[len-4]=='.') &&
                    (namelist[ctr]->d_name[len-3]==extension[0]) &&
                    (namelist[ctr]->d_name[len-2]==extension[1]) &&
                    (namelist[ctr]->d_name[len-1]==extension[2])) {
                    no_of_images++;
                }
            }
            free(namelist[ctr]);
        }
        free(namelist);
    }
    return no_of_images;
}

/**
* @brief Downsample a colour image to a mono fixed size image
* @param img Original image buffer (3 bytes per pixel)
* @param width Width of the original image in pixels
* @param height Height of the original image in pixels
* @param downsampled Downsampled image buffer (1 byte per pixel)
* @param downsampled_width Downsampled image width in pixels
* @param downsampled_height Downsampled image height in pixels
*/
static void deeplearn_downsample(unsigned char * img,
                                 int width, int height,
                                 unsigned char * downsampled,
                                 int downsampled_width,
                                 int downsampled_height)
{
    int x,y,n2,xx,yy,n=0;

    for (y = 0; y < downsampled_height; y++) {
        /** y coordinate in the original image */
        yy = y * height / downsampled_height;
        for (x = 0; x < downsampled_width; x++, n++) {
            /** x coordinate in the original image */
            xx = x * width / downsampled_width;
            /** index within the original image */
            n2 = ((yy*width) + xx)*3;
            /** update downsampled image */
            downsampled[n] = (img[n2]+img[n2+1]+img[n2+2])/3;
        }
    }
}

/**
* @brief Loads a set of training images and automatically creates
*        classification descriptions from the filenames and
*        classification numbers
* @param images_directory The directpry to search for images
* @param images Array which will be used to store the images (1 byte per pixel)
* @param classifications Description of each image, taken from the filename
* @param classification_number Class number of each image
* @param width Standardised width of the images in pixels
* @param height Standardised height of the images in pixels
* @return The number of images loaded
*/
int deeplearn_load_training_images(char * images_directory,
                                   unsigned char *** images,
                                   char *** classifications,
                                   int ** classification_number,
                                   int width, int height)
{
    int ctr,no_of_images = 0;
    struct dirent **namelist;
    int n,len,im_width,im_height;
    unsigned char * img, * downsampled;
    char * extension = "png";
    char filename[256];
    char * classification;

    /** how many images are there? */
    no_of_images = number_of_images(images_directory, extension);
    if (no_of_images == 0) {
        return 0;
    }

    /** allocate an array for the images */
    *images =
        (unsigned char**)malloc(no_of_images*
                                sizeof(unsigned char*));

    /** allocate memory for the classifications */
    *classifications = (char**)malloc(no_of_images*
                                      sizeof(char*));

    /** allocate memory for the class number assigned to each image */
    *classification_number = (int*)malloc(no_of_images * sizeof(int));

    /** get image filenames */
    no_of_images = 0;
    n = scandir(images_directory, &namelist, 0, alphasort);
    if (n >= 0) {
        /** for every filename */
        ctr = n;
        while (ctr--) {
            /** is the filename long enough? */
            len = strlen(namelist[ctr]->d_name);
            if (len > 4) {
                sprintf(filename,"%s/%s",
                        images_directory,namelist[ctr]->d_name);
                len = strlen(filename);
                /** is this a png image? */
                if ((filename[len-4]=='.') &&
                    (filename[len-3]==extension[0]) &&
                    (filename[len-2]==extension[1]) &&
                    (filename[len-1]==extension[2])) {

                    /** obtain an image from the filename */
                    deeplearn_read_png(filename,
                                       &im_width, &im_height, &img);

                    /** was an image returned? */
                    if (img != NULL) {
                        /** create a fixed size image */
                        downsampled =
                            (unsigned char*)malloc(width*height*
                                                   sizeof(unsigned char));
                        deeplearn_downsample(img, im_width, im_height,
                                             downsampled, width, height);

                        (*images)[no_of_images] = downsampled;

                        /** free the original image */
                        free(img);
                    }
                    else {
                        (*images)[no_of_images] = NULL;
                    }

                    /** allocate memory for the classification */
                    classification =
                        (char*)malloc(256*
                                      sizeof(char));

                    /** get the name of the classification */
                    bp_get_classification_from_filename(filename,
                                                        classification);
                    (*classifications)[no_of_images] = classification;

                    no_of_images++;
                }
            }
            free(namelist[ctr]);
        }
        free(namelist);
    }

    /** assign a class number to each image */
    bp_classifications_to_numbers(no_of_images,
                                  *classifications,
                                  (*classification_number));

    return no_of_images;
}

/**
* @brief Plots a number of mono images within a single image
* @param images Array of images (1 byte per pixel)
* @param no_of_images The number of images in the array
* @param image_width Standardised image width within the array
* @param image_height Standardised image height within the array
* @param filename Filename to save as
*/
/* plots mono images */
void bp_plot_images(unsigned char **images,
                    int no_of_images,
                    int image_width, int image_height,
                    char * filename)
{
    int i,y,x,n1,n2;

    /** allocate memory for the image */
    unsigned char * img =
        (unsigned char*)malloc(image_width*image_height*no_of_images*3);

    for (i = 0; i < no_of_images; i++) {
        for (y = 0; y < image_height; y++) {
            for (x = 0; x < image_width; x++) {
                n1 = ((y+(i*image_height))*image_width + x)*3;
                n2 = (y*image_width) + x;
                img[n1] = images[i][n2];
                img[n1+1] = img[n1];
                img[n1+2] = img[n1];
            }
        }
    }

    /** write the image to file */
    deeplearn_write_png(filename,
                        image_width, image_height*no_of_images, img);

    /** free the image memory */
    free(img);
}
