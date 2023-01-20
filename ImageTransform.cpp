#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <algorithm>

#include "uiuc/PNG.h"
#include "uiuc/HSLAPixel.h"
#include "ImageTransform.h"

/* ******************
(Begin multi-line comment...)

Write your name and email address in the comment space here:

Name:
Email:

(...end multi-line comment.)
******************** */

using uiuc::PNG;
using uiuc::HSLAPixel;

/**
 * Returns an image that has been transformed to grayscale.
 *
 * The saturation of every pixel is set to 0, removing any color.
 *
 * @return The grayscale image.
 */
PNG grayscale(PNG image) {
  /// This function is already written for you so you can see how to
  /// interact with our PNG class.
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel & pixel = image.getPixel(x, y);

      // `pixel` is a reference to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly. No need to `set`
      // the pixel since you're directly changing the memory of the image.
      pixel.s = 0;
    }
  }

  return image;
}



/**
 * Returns an image with a spotlight centered at (`centerX`, `centerY`).
 *
 * A spotlight adjusts the luminance of a pixel based on the distance the pixel
 * is away from the center by decreasing the luminance by 0.5% per 1 pixel euclidean
 * distance away from the center.
 *
 * For example, a pixel 3 pixels above and 4 pixels to the right of the center
 * is a total of `sqrt((3 * 3) + (4 * 4)) = sqrt(25) = 5` pixels away and
 * its luminance is decreased by 2.5% (0.975x its original value).  At a
 * distance over 160 pixels away, the luminance will always decreased by 80%.
 * 
 * The modified PNG is then returned.
 *
 * @param image A PNG object which holds the image data to be modified.
 * @param centerX The center x coordinate of the crosshair which is to be drawn.
 * @param centerY The center y coordinate of the crosshair which is to be drawn.
 *
 * @return The image with a spotlight.
 */
PNG createSpotlight(PNG image, int centerX, int centerY) {

  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel & pixel = image.getPixel(x, y);

      int deltaX = abs(centerX - (int)x);
      int deltaY = abs(centerY - (int)y);
      double distance = sqrt((deltaX * deltaX) + (deltaY * deltaY));

      /* 
      cout << "centerX: " << centerX << endl << "centerY: " << centerY << endl;
      cout << "x: " << x << endl << "y: " << y << endl;
      cout << "deltaX: " << deltaX << endl << "deltaY: " << deltaY << endl;
      cout << "distance: " << distance << endl;
      */

      double reductionPercentAsDecimal = distance * 0.005;
      if (reductionPercentAsDecimal > 0.8) {
        reductionPercentAsDecimal = 0.8;
      }

      double reductionFactor = 1 - reductionPercentAsDecimal;
      pixel.l = pixel.l * reductionFactor;

      /*
      // Custom breakpoint
      if (true) {
        int hold;
        std::cin >> hold;
      }
      */
    }
  }
  return image;
  
}
 

/**
 * Returns a image transformed to Illini colors.
 *
 * The hue of every pixel is set to the a hue value of either orange or
 * blue, based on if the pixel's hue value is closer to orange than blue.
 *
 * @param image A PNG object which holds the image data to be modified.
 *
 * @return The illinify'd image.
**/
PNG illinify(PNG image) {

  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel & pixel = image.getPixel(x, y);

      // Each color can be reached by going two different directions on the circle.
      // Calculate distance both directions for both colors, and select min
      // Indices are toBlue1, toBlue2, toOrange1, toOrange2
      std::vector<double> colorDistance = {0, 0, 0, 0};
      colorDistance[0] = abs(216-pixel.h);
      colorDistance[1] = (360-pixel.h) + 216;
      colorDistance[2] = abs(11-pixel.h);
      colorDistance[3] = (360-pixel.h) + 11;
      //std::cout << "colorDistance: " << colorDistance[0] << " " << colorDistance[1] << " " << colorDistance[2] << " " << colorDistance[3] << std::endl;
      if (min(colorDistance[0], colorDistance[1]) < min(colorDistance[2], colorDistance[3])) {
        pixel.h = 216;
        //std::cout << "Selected Blue" << std::endl << std::endl;
      } else {
        pixel.h = 11;
        //std::cout << "Selected Orange" << std::endl << std::endl;
      }

      // Custom breakpoint
      //int hold;
      //std::cin >> hold;
    }
  }

  return image;
  /*
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel & pixel = image.getPixel(x, y);

      // `pixel` is a reference to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly. No need to `set`
      // the pixel since you're directly changing the memory of the image.
      pixel.s = 0;
    }
  }
  */
}
 

/**
* Returns an immge that has been watermarked by another image.
*
* The luminance of every pixel of the second image is checked, if that
* pixel's luminance is 1 (100%), then the pixel at the same location on
* the first image has its luminance increased by 0.2.
*
* @param firstImage  The first of the two PNGs, which is the base image.
* @param secondImage The second of the two PNGs, which acts as the stencil.
*
* @return The watermarked image.
*/
PNG watermark(PNG firstImage, PNG secondImage) {

  return firstImage;
}
