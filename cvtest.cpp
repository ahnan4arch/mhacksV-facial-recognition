#include <stdio.h>
#include <stdlib.h>
#include <gphoto2/gphoto2.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

#define GP_SAFE( retval ) ( gp_safe( (retval) ) )

using namespace cv;
using namespace std;

inline void gp_safe(int gp_code) {
	if (gp_code != GP_OK) {
		fprintf(stderr, "*** ERROR %i ***\n", gp_code);
		// maybe be more graceful?
		exit(1);
	}
}

int main() {
	CameraFile *previewFile;
	const char *data;
	long unsigned int dsize;

	// get preview image
	GP_SAFE( gp_file_new(&previewFile) );
	GP_SAFE( gp_file_open(previewFile, "a.jpg") );
	GP_SAFE( gp_file_get_data_and_size(previewFile, &data, &dsize) );

	printf("Size: %lu\n", dsize);

	Mat imgbuf(Size(640,424), CV_8UC3, (void*)data);
	namedWindow("image",WINDOW_AUTOSIZE);
	Mat img = imdecode(imgbuf, CV_LOAD_IMAGE_COLOR);
	imshow("image", img);

	waitKey(0);

	// clean up
	gp_file_unref(previewFile);

	return 0;
}
