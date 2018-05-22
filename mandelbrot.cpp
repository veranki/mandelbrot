#include "mandelbrot.h"

double mapToReal(int x, int imgWidth, double minR, double maxR) {
  double xrange = maxR - minR;
  // scaled x value is minR + ((maxR-minR)*Range/width)
  return (x * (xrange / imgWidth) + minR);
}

double mapToImag(int y, int imgHeight, double minI, double maxI) {
  double yrange = maxI - minI;
  return (y * (yrange / imgHeight) + minI);
}

int findmandelbrot(double cr, double ci, int max_iteration) {
  //
  int i = 0;
  double zr = 0.0, zi = 0.0;
  double zrsqr = 0.0, zisqr = 0.0;
  while (i < max_iteration && (zrsqr + zisqr) < 4.0) {
    double temp = zrsqr - zisqr + cr;
    // cout << temp << " is temp value" << endl;
    zi = (2.0 * zr * zi) + ci;
    zr = temp;
    zrsqr = zr * zr;
    zisqr = zi * zi;
    i++;
  };
  // while (i < max_iteration && (zr * zr + zi * zi) < 4.0) {
  //   double temp = (zr * zr) - (zi * zi) + cr;
  //   // cout << temp << " is temp value" << endl;
  //   zi = (2.0 * zr * zi) + ci;
  //   zr = temp;
  //   i++;
  // };
  return i;
}

int main() {
  // Open the output file, write the PPM header
  ofstream fout("mandelbrot-image.ppm");
  fout << "P3" << endl;                          // ppm format
  fout << imgWidth << " " << imgHeight << endl;  // image dimensions
  fout << "256" << endl;                         // maximum pixel value
  // For every pixel..
  for (int y = 0; y < imgHeight; y++) {   // Rows
    for (int x = 0; x < imgWidth; x++) {  // Pixels in row
      // Find real and imaginary for C, corresponding to  x,y pixel in image
      double cr = mapToReal(x, imgWidth, minR, maxR);
      // cout << cr << " is cr value" << endl;
      double ci = mapToImag(y, imgHeight, minI, maxI);
      // cout << ci << " is ci value" << endl;
      // Find  number of iterations in  Mandelbrot formula using C
      int n = findmandelbrot(cr, ci, max_iteration);
      // cout << n << " is n value" << endl;
      // Map resulting iterations to RGB values
      int r, g, b = 0;
      // int r = n % 256;
      // int g = n % 256;
      // int b = n * n % 256;
      if (n < 16) {
        r = 16 * (16 - n);
        g = 0;
        b = 16 * n - 1;
      } else if (n < 32) {
        r = 0;
        g = 16 * (n - 16);
        b = 16 * (32 - n) - 1;
      } else if (n < 64) {
        r = 8 * (n - 32);
        g = 8 * (64 - n) - 1;
        b = 0;
      } else {  // range is 64 - 127
        r = 255 - (n - 64) * 4;
        g = 0;
        b = 0;
      }
      // Output it to the image
      fout << r << " " << g << " " << b << " ";
    }
    fout << endl;
  }
  fout.close();
  cout << max_iteration << " Iterations Finished!" << endl;
  return 0;
}
