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

// from libgphoto2 focus.c
int camera_auto_focus(Camera *camera, GPContext *context) {
	CameraWidget *widget = NULL, *child = NULL;
	CameraWidgetType type;
	int ret, val;

	ret = gp_camera_get_config(camera, &widget, context);
	if (ret < GP_OK) return ret;

	ret = gp_widget_get_child_by_name(widget, "autofocusdrive", &child);
	if (ret < GP_OK) goto caf_out;

	ret = gp_widget_get_type(child, &type);
	if (ret < GP_OK) goto caf_out;

	if (type != GP_WIDGET_TOGGLE) {
		ret = GP_ERROR_BAD_PARAMETERS;
		goto caf_out;
	}

	ret = gp_widget_get_value(child, &val);
	if (ret < GP_OK) goto caf_out;

	val++;
	ret = gp_widget_set_value(child, &val);
	if (ret < GP_OK) goto caf_out;

	ret = gp_camera_set_config(camera, widget, context);

caf_out:
	// clean up
	gp_widget_free(widget);
	return ret;
}

// from libgphoto2 sample.h
static void ctx_error_func(GPContext *context, const char *str, void *data) {
	fprintf(stderr, "\n*** Contexterror ***              \n%s\n",str);
	fflush(stderr);
}

// from libgphoto2 sample.h
static void ctx_status_func(GPContext *context, const char *str, void *data) {
	fprintf(stderr, "%s\n", str);
	fflush(stderr);
}

int main() {
	Camera *camera;
	CameraFile *previewFile;
	GPContext *cam_context;
	int retval;
	const char *data;
	long unsigned int size;

	gp_camera_new(&camera);

	// create context
	cam_context = gp_context_new();
	gp_context_set_error_func(cam_context, ctx_error_func, NULL);
	gp_context_set_status_func(cam_context, ctx_status_func, NULL);

	// init camera
	printf("Camera init\n");
	GP_SAFE( gp_camera_init(camera, cam_context) );

	// get preview image
	GP_SAFE( gp_file_new(&previewFile) );
	camera_auto_focus(camera, cam_context);
	GP_SAFE( gp_camera_capture_preview(camera, previewFile, cam_context) );
	GP_SAFE( gp_file_get_data_and_size(previewFile, &data, &size) );

	// view in opencv
	// 640x424 is the size of the image from preview
	Mat imgbuf(Size(640,424), CV_8UC3, (void*)data);
	Mat img = imdecode(imgbuf, CV_LOAD_IMAGE_COLOR);
	namedWindow("image", WINDOW_AUTOSIZE);
	imshow("image", img);

	waitKey(0);

	// clean up
	gp_file_unref(previewFile);
	gp_camera_exit(camera, cam_context);

	return 0;
}
