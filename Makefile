CC=g++
# from pkg-config --cflags libgphoto2
CFLAGS=-I/usr/include/gphoto2 -I/usr/include/libexif -I/usr/include/opencv
# from pkg-config --libs libgphoto2
LFLAGS=-lgphoto2 -lgphoto2_port -lm -lexif /usr/lib/libopencv_calib3d.so /usr/lib/libopencv_contrib.so /usr/lib/libopencv_core.so /usr/lib/libopencv_features2d.so /usr/lib/libopencv_flann.so /usr/lib/libopencv_gpu.so /usr/lib/libopencv_highgui.so /usr/lib/libopencv_imgproc.so /usr/lib/libopencv_legacy.so /usr/lib/libopencv_ml.so /usr/lib/libopencv_objdetect.so /usr/lib/libopencv_photo.so /usr/lib/libopencv_softcascade.so /usr/lib/libopencv_stitching.so /usr/lib/libopencv_superres.so /usr/lib/libopencv_ts.a /usr/lib/libopencv_video.so /usr/lib/libopencv_videostab.so /usr/lib/libopencv_facedetect.so /usr/lib/libopencv_imuvstab.so /usr/lib/libopencv_tegra.so /usr/lib/libopencv_vstab.so /usr/local/cuda-6.0/lib/libcufft.so /usr/local/cuda-6.0/lib/libnpps.so /usr/local/cuda-6.0/lib/libnppi.so /usr/local/cuda-6.0/lib/libnppc.so /usr/local/cuda-6.0/lib/libcudart.so -lrt -lpthread -lm -ldl
SRC=camera.cpp

all:
	$(CC) -Wall -o camera $(SRC) $(CFLAGS) $(LFLAGS)

cvtest:
	g++ -Wall -o cvtest cvtest.cpp -I/usr/include/gphoto2 -I/usr/include/libexif -I/usr/include/opencv  /usr/lib/libopencv_calib3d.so /usr/lib/libopencv_contrib.so /usr/lib/libopencv_core.so /usr/lib/libopencv_features2d.so /usr/lib/libopencv_flann.so /usr/lib/libopencv_gpu.so /usr/lib/libopencv_highgui.so /usr/lib/libopencv_imgproc.so /usr/lib/libopencv_legacy.so /usr/lib/libopencv_ml.so /usr/lib/libopencv_objdetect.so /usr/lib/libopencv_photo.so /usr/lib/libopencv_softcascade.so /usr/lib/libopencv_stitching.so /usr/lib/libopencv_superres.so /usr/lib/libopencv_ts.a /usr/lib/libopencv_video.so /usr/lib/libopencv_videostab.so /usr/lib/libopencv_facedetect.so /usr/lib/libopencv_imuvstab.so /usr/lib/libopencv_tegra.so /usr/lib/libopencv_vstab.so /usr/local/cuda-6.0/lib/libcufft.so /usr/local/cuda-6.0/lib/libnpps.so /usr/local/cuda-6.0/lib/libnppi.so /usr/local/cuda-6.0/lib/libnppc.so /usr/local/cuda-6.0/lib/libcudart.so -lrt -lpthread -lm -ldl -lgphoto2 -lgphoto2_port -lm -lexif

jpegtest:
	$(CC) -Wall -o jpgtest jpgtest.cpp $(CFLAGS) -ljpeg $(LFLAGS)

.PHONY: clean

clean:
	rm -f camera jpgtest
