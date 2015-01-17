#include <stdio.h>
#include <stdlib.h>
#include <gphoto2/gphoto2.h>
#include <jpeglib.h>
#include <setjmp.h>
#include <jerror.h>

#define GP_SAFE( retval ) ( gp_safe( (retval) ) )

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

{

	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	JSAMPROW row_pointer[1];
	int i,location;
	unsigned char *raw_image = NULL;

	cinfo.err = jpeg_std_error(&jerr);

	jpeg_create_decompress(&cinfo);
	jpeg_mem_src(&cinfo, (unsigned char *)data, dsize);
	jpeg_read_header(&cinfo, TRUE);

	printf( "JPEG File Information: \n" );
	printf( "Image width and height: %d pixels and %d pixels.\n", cinfo.image_width, cinfo.image_height );
	printf( "Color components per pixel: %d.\n", cinfo.num_components );
	printf( "Color space: %d.\n", cinfo.jpeg_color_space );

	jpeg_start_decompress( &cinfo );
	
	raw_image = (unsigned char*)malloc( cinfo.output_width*cinfo.output_height*cinfo.num_components );
	row_pointer[0] = (unsigned char *)malloc( cinfo.output_width*cinfo.num_components );
printf("BEFORE\n");
	while( cinfo.output_scanline < cinfo.image_height )        
	{                                                          
		jpeg_read_scanlines( &cinfo, row_pointer, 1 );         
		for( i=0; i<cinfo.image_width*cinfo.num_components;i++)
			raw_image[location++] = row_pointer[0][i];         
	}                                                          
printf("AFTER\n");

	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	free(row_pointer[0]);
}

	// clean up
	gp_file_unref(previewFile);

	return 0;
}
