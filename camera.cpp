#include <stdio.h>
#include <fcntl.h>

#include <gphoto2/gphoto2-camera.h>

Camera *camera;
GPContext *context;

void error_func (GPContext *context, const char *format, va_list args, void *data) {
	fprintf (stderr, "*** Contexterror ***\n");
	vfprintf (stderr, format, args);
	fprintf (stderr, "\n");
}

void message_func (GPContext *context, const char *format, va_list args, void *data) {
	vprintf (format, args);
	printf ("\n");
}

int main (int argc, char *argv[]) {
	gp_camera_new (&camera);
	context = gp_context_new();

	// set callbacks for camera messages
	gp_context_set_error_func (context, error_func, NULL);
	gp_context_set_message_func (context, message_func, NULL);

}
