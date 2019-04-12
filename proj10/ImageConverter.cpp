/*
 * ImageConverter.cpp declares a class for
 *  various image conversion operations.
 *
 *  Author:  Joel Adams, CS112 @ Calvin College.
 *  Created: March 2015
 *  Revised: November 2016
 */

#include "ImageConverter.h"
#include <unistd.h>            // sleep()

//-----------------  Method definitions ------------------------------

/* explicit constructor
 *
 * @param imageFileName, a string.
 * @param width, an int.
 * @param height, an int.
 *
 * Precondition: imageFileName contains the name of a valid image file
 *               && width > 0 && height > 0
 * Postcondition: myImageFileName == imageFileName
 *                && myWidth == width && myHeight = height
 *                && width x height Canvas containing the image
 *                    from imageFileName has been displayed on screen.
 */
ImageConverter::ImageConverter(const std::string& imageFileName, int width, int height)
 : myCanvas1(0, 0, width, height, imageFileName),
   myImageFileName(imageFileName),
   myWidth(width),
   myHeight(height)
{
    myCanvas1.start();
    myCanvas1.drawImage(myImageFileName, 0, 0, width, height);
    sleep(1);
}

/* destructor
 *
 * Precondition: this ImageConverter object is going out of scope.
 * Postcondition: myCanvas1 has disappeared from the screen.
 */
ImageConverter::~ImageConverter() {
    myCanvas1.wait();
    cout << "\nImageConverter terminated normally." << endl;
}

/* invertImage() inverts the image from myImageFileName.
 *
 * Precondition: myCanvas1 contains a TSGL Image that is to be inverted
 *               && myWidth contains the number of columns in which to display the image
 *               && myHeight contains the number of rows in which to display the image.
 *
 * Postcondition: a myWidth x myHeight Canvas has been displayed
 *                 containing the inverse of the image from myCanvas1
 *                 (which contains the image from myImageFileName).
 */

void ImageConverter::invertImage() {

	// record starting time
	double startTime = omp_get_wtime();

	Canvas canvas2(myWidth+50, 0, myWidth, myHeight, myImageFileName + " Inverted");
	canvas2.start();

	// loop through the image rows
	#pragma omp parallel for
	for (int row = 0; row < myHeight; row++) {
		// slow the processing to simulate a very large image
		canvas2.sleep();
		// loop through the image columns
		for (int col = 0; col < myWidth; col++) {
			// read the pixel at canvas1[row][col]
			ColorInt pixelColor = myCanvas1.getPixel(row, col);
			// compute its inverse
			int invertedR = 255 - pixelColor.R;
			int invertedG = 255 - pixelColor.G;
			int invertedB = 255 - pixelColor.B;
			// draw the inverse at the same spot in canvas2
			canvas2.drawPixel(row, col, ColorInt(invertedR,invertedG,invertedB) );
		} // inner for
	} // outer for

	// compute and display the time difference
	double totalTime = omp_get_wtime() - startTime;
	cout << "\n\nImage inversion took " << totalTime << " seconds.\n" << endl;

	// save converted image
	canvas2.takeScreenShot();

	canvas2.wait();
} // invertImage


/* invertImage() inverts the image from myImageFileName. Uses the chunk-size 1 approach
 *
 * Precondition: myCanvas1 contains a TSGL Image that is to be inverted
 *               && myWidth contains the number of columns in which to display the image
 *               && myHeight contains the number of rows in which to display the image.
 *
 * Postcondition: a myWidth x myHeight Canvas has been displayed
 *                 containing the inverse of the image from myCanvas1
 *                 (which contains the image from myImageFileName).
 */
void ImageConverter::invertImage2() {

   Canvas canvas3(myWidth+50, 0, myWidth, myHeight, myImageFileName + " Inverted, Chunk-Size 1");
   canvas3.start();

   // launch additional threads
   #pragma omp parallel
   {
      // how many workers do we have?
      unsigned numThreads = omp_get_num_threads();
      // which one am I?
      unsigned id = omp_get_thread_num();

      // loop through the image rows
      for (int row = id; row < myHeight; row += numThreads) {
         // slow the processing to simulate a very large image
         canvas3.sleep();
         // loop through the image columns
         for (int col = 0; col < myWidth; col++) {
            // read the pixel at canvas1[row][col]
            ColorInt pixelColor = myCanvas1.getPixel(row, col);
            // compute its inverse
            int invertedR = 255 - pixelColor.R;
            int invertedG = 255 - pixelColor.G;
            int invertedB = 255 - pixelColor.B;
            // draw the inverse at the same spot in canvas2
            canvas3.drawPixel(row, col, ColorInt(invertedR,invertedG,invertedB) );
         } // inner for
      } // outer for
   } // #pragma omp parallel

   canvas3.wait();
} // invertImage2



/* invertImage() inverts the image from myImageFileName. Uses the equal-sized chunks approach
 *
 * Precondition: myCanvas1 contains a TSGL Image that is to be inverted
 *               && myWidth contains the number of columns in which to display the image
 *               && myHeight contains the number of rows in which to display the image.
 *
 * Postcondition: a myWidth x myHeight Canvas has been displayed
 *                 containing the inverse of the image from myCanvas1
 *                 (which contains the image from myImageFileName).
 */
void ImageConverter::invertImage3() {

   Canvas canvas4(myWidth+50, 0, myWidth, myHeight, myImageFileName + " Inverted, Equal-Sized Chunks ");
   canvas4.start();

   // launch additional threads
   #pragma omp parallel
   {
      // how many workers do we have?
      unsigned numThreads = omp_get_num_threads();
      // which one am I?
      unsigned id = omp_get_thread_num();

      // compute size of chunks (iterations % numThreads may != 0)
      double iterations = myHeight;
      unsigned chunkSize = (unsigned)ceil(iterations / numThreads);

      // compute starting and stopping index values
      int start = id * chunkSize;
      int stop = 0;
      if (id < numThreads-1) {
          stop = start + chunkSize;
      } else {
          stop = myHeight;
      }

      // loop through image rows in equal-sized chunks
      for (int row = start; row < stop; row++) {
         // slow the processing to simulate a very large image
         canvas4.sleep();
         // loop through the image columns
         for (int col = 0; col < myWidth; col++) {
            // read the pixel at canvas1[row][col]
            ColorInt pixelColor = myCanvas1.getPixel(row, col);
            // compute its inverse
            int invertedR = 255 - pixelColor.R;
            int invertedG = 255 - pixelColor.G;
            int invertedB = 255 - pixelColor.B;
            // draw the inverse at the same spot in canvas2
            canvas4.drawPixel(row, col, ColorInt(invertedR,invertedG,invertedB) );
         } // inner for
      } // outer for
   } // #pragma omp parallel

   canvas4.wait();
} // invertImage3

/* grayScale() converts the image from color to gray-scale. Uses the equal-sized chunks approach
 *
 * Precondition: myCanvas1 contains a TSGL Image that is to be inverted
 *               && myWidth contains the number of columns in which to display the image
 *               && myHeight contains the number of rows in which to display the image.
 *
 * Postcondition: a myWidth x myHeight Canvas has been displayed
 *                 containing the gray-scale version image of myCanvas1
 */
void ImageConverter::grayscale() {

	// record starting time
	double startTime = omp_get_wtime();

	Canvas canvas(myWidth+50, 0, myWidth, myHeight, myImageFileName + " Grayscale, Equal-Sized Chunks ");
	canvas.start();

	// launch additional threads
	#pragma omp parallel
	{
		// how many workers do we have?
		unsigned numThreads = omp_get_num_threads();
		// which one am I?
		unsigned id = omp_get_thread_num();
		// compute size of chunks (iterations % numThreads may != 0)
		double iterations = myHeight;
		unsigned chunkSize = (unsigned)ceil(iterations / numThreads);
		// compute starting and stopping index values
		int start = id * chunkSize;
		int stop = 0;
		if (id < numThreads-1) {
			stop = start + chunkSize;
		} else {
			stop = myHeight;
		}
		// loop through image rows in equal-sized chunks
		for (int row = start; row < stop; row++) {
			// slow the processing to simulate a very large image
			canvas.sleep();
			// loop through the image columns
			for (int col = 0; col < myWidth; col++) {
				// read the pixel at canvas1[row][col]
				ColorInt pixelColor = myCanvas1.getPixel(row, col);
				// compute the average (gray) intensity
				int intensity = (pixelColor.R + pixelColor.G + pixelColor.B) / 3;
				// draw the grayscale color at the same spot in canvas2
				canvas.drawPixel(row, col, ColorInt(intensity,intensity,intensity) );
			} // inner for
		} // outer for
	}

	// compute and display the time difference
	double totalTime = omp_get_wtime() - startTime;
	cout << "\n\nGrayscale took " << totalTime << " seconds.\n" << endl;

	// save converted image
	canvas.takeScreenShot();

	canvas.wait();
}

/* andyWarhol() uses the image from myImageFileName and creates an Andy Warhol style collage,
 * 				a tiling the image into a 9x9 set, each with a different color shift.
 * Uses the equal-sized chunks approach
 *
 * Precondition: myCanvas1 contains a TSGL Image that is to be inverted
 *               && myWidth contains the number of columns in which to display the image
 *               && myHeight contains the number of rows in which to display the image.
 *
 * Postcondition: a myWidth x myHeight Canvas has been displayed
 *                 containing the the Andy Warhol collage of the image used.
 */
void ImageConverter::andyWarhol() {
	// record starting time
	double startTime = omp_get_wtime();

	Canvas canvas(myWidth+50, 0, myWidth, myHeight, myImageFileName + " Andy Warhol, Chunksize 1 ");
	canvas.start();

	// launch additional threads
#pragma omp parallel
	{
		// how many workers do we have?
		unsigned numThreads = omp_get_num_threads();
		// which one am I?
		unsigned id = omp_get_thread_num();

		unsigned evenThirdH = (unsigned)ceil(myHeight / 3);
		unsigned evenThirdW = (unsigned)ceil(myWidth / 3);

		// loop through the image rows
		for (int row = id; row < myHeight; row += numThreads) {
			// slow the processing to simulate a very large image
			canvas.sleep();
			// loop through the image columns
			for (int col = 0; col < myWidth; col++) {
				int colArea, rowArea;
				if (col <= evenThirdH) {  // Top
					colArea = 10;
				} else if (evenThirdH < col && col <= evenThirdH * 2) {  // Middle
					colArea = 20;
				} else {  // Bottom
					colArea = 30;
				}

				if (row <= evenThirdW) {  // Left
					rowArea = 1;
				} else if (evenThirdW < row && row <= evenThirdW * 2) {  // Middle
					rowArea = 2;
				} else {  // Right
					rowArea = 3;
				}

				int areacode = colArea + rowArea;

				ColorInt workingPixel = myCanvas1.getPixel( ((row) * 3) % myHeight, ((col) * 3) % myWidth );
				unsigned grayIntensity = (workingPixel.R + workingPixel.G + workingPixel.B) / 3;

				switch (areacode) {
				case 11:  // Green zone
					workingPixel = ColorInt(workingPixel.R / 2, workingPixel.G, workingPixel.B / 2);
					break;
				case 21:  // Purple zone
					workingPixel = ColorInt(workingPixel.R * 2, workingPixel.G, workingPixel.B * 3);
					break;
				case 31:  // Pink zone
					workingPixel = ColorInt(workingPixel.R * 2, workingPixel.G * 1.5, workingPixel.B * 1.5);
					break;
				case 12:  // Yellow zone
					workingPixel = ColorInt(workingPixel.R * 2, workingPixel.G * 3, workingPixel.B * 2);
					break;
				case 22:  // Grayscale zone
					workingPixel = ColorInt(grayIntensity, grayIntensity, grayIntensity);
					break;
				case 32:  // Red zone
					workingPixel = ColorInt(workingPixel.R * 2, workingPixel.G, workingPixel.B);
					break;
				case 13:  // Blue zone
					workingPixel = ColorInt(workingPixel.R, workingPixel.G, workingPixel.B * 2);
					break;
				case 23:  // Strong yellow zone
					workingPixel = ColorInt(workingPixel.R, workingPixel.G * 2, workingPixel.B);
					break;
				case 33:  // Light purple zone
					workingPixel = ColorInt(workingPixel.R, workingPixel.G / 2, workingPixel.B);
					break;
				}
				canvas.drawPixel(row, col, workingPixel);
			} // inner for
		} // outer for
	} // #pragma omp parallel

	// compute and display the time difference
	double totalTime = omp_get_wtime() - startTime;
	cout << "\n\nAndy Warhol took " << totalTime << " seconds.\n" << endl;

	// save converted image
	canvas.takeScreenShot();

	canvas.wait();

}





