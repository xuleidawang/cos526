/*
Szymon Rusinkiewicz
Princeton University

imageio++_test.cpp
Simple test of the imageio++ functionality
*/

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include "imageio++.h"


/* Helper function: returns distance from (x,y) to center of an image of
   size (w,h), scaled such that corners are 1 */
inline float dist2cent(int x, int y, int w, int h)
{
	float dx = (0.5f * w) - (x + 0.5f);
	float dy = (0.5f * h) - (y + 0.5f);
	float cx = (0.5f * w) - 0.5f;
	float cy = (0.5f * h) - 0.5f;
	return std::sqrt((dx*dx + dy*dy) / (cx*cx + cy*cy));
}


/* Main function */
int main(int argc, char *argv[])
{
	if (argc < 4) {
		fprintf(stderr, "Usage: %s in.png out.png mask.png\n", argv[0]);
		exit(1);
	}
	const char *infilename = argv[1];
	const char *outfilename = argv[2];
	const char *maskfilename = argv[3];
	/* Read an image */
	Im im, mask;
	if (!im.read(infilename))
		exit(1);
	Im out(im.w(), im.h());
	printf("Read an image of size %d x %d\n", im.w(), im.h());

	if (!mask.read(maskfilename))
		exit(1);
	printf("Read a mask image of size %d x %d\n", mask.w(), mask.h());

	/* Transform image - apply a vignetting filter */
	for (int y = 0; y < im.h(); y++) {
		for (int x = 0; x < im.w(); x++) {
			if((int)mask(x,y).r==255 && (int)mask(x,y).g ==255 && (int)mask(x,y).b==255 )
			{
				Color &pixel = im(x, y);
				out.setColor(x,y,pixel);
				
			}
		}
	}

	/* Write image back out */
	if (!out.write(outfilename))
		exit(1);

	exit(0);
}
