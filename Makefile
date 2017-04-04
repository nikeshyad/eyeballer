OPTS = -Wall -g -std=c++11
LIBS = -lGL -lglut -lm /usr/lib64/libopencv_videostab.so.2.4.11 /usr/lib64/libopencv_video.so.2.4.11 /usr/lib64/libopencv_ts.so.2.4.11 /usr/lib64/libopencv_superres.so.2.4.11 /usr/lib64/libopencv_stitching.so.2.4.11 /usr/lib64/libopencv_photo.so.2.4.11 /usr/lib64/libopencv_ocl.so.2.4.11 /usr/lib64/libopencv_objdetect.so.2.4.11 /usr/lib64/libopencv_ml.so.2.4.11 /usr/lib64/libopencv_legacy.so.2.4.11 /usr/lib64/libopencv_imgproc.so.2.4.11 /usr/lib64/libopencv_highgui.so.2.4.11 /usr/lib64/libopencv_flann.so.2.4.11 /usr/lib64/libopencv_features2d.so.2.4.11 /usr/lib64/libopencv_core.so.2.4.11 /usr/lib64/libopencv_contrib.so.2.4.11 /usr/lib64/libopencv_calib3d.so.2.4.11 /usr/lib64/libopencv_video.so.2.4.11 /usr/lib64/libopencv_objdetect.so.2.4.11 /usr/lib64/libopencv_ml.so.2.4.11 /usr/lib64/libopencv_features2d.so.2.4.11 /usr/lib64/libopencv_highgui.so.2.4.11 /usr/lib64/libopencv_imgproc.so.2.4.11 /usr/lib64/libopencv_flann.so.2.4.11 /usr/lib64/libopencv_core.so.2.4.11 
EYELIBS = OpenCV/helpers.o OpenCV/findEyeCorner.o OpenCV/findEyeCenter.o
ARCH := $(shell uname)
ifeq ($(ARCH), Linux)
else
 MACOSX_DEFINE = -DMACOSX -I/sw/include
 LIBS = -I/usr/common/include -I/usr/include/GL -L/System/Library/Frameworks/OpenGL.framework/Libraries -framework GLUT -framework OpenGL -lGL -lm -lobjc -lstdc++  

endif

EyeGame: EyeGame.o Button.o Texture.o EyeInterface.o Circle.o $(EYELIBS)
	g++ $(OPTS) EyeGame.o Button.o Texture.o EyeInterface.o Circle.o -o EyeGame $(LIBS) $(EYELIBS)

EyeGame.o: EyeGame.cpp Texture.h Button.h
	g++ $(OPTS) $(MACOSX_DEFINE) -c EyeGame.cpp $(LIBS)

Texture.o: Texture.cpp Texture.h
	g++ $(OPTS) $(MACOSX_DEFINE) -c Texture.cpp $(LIBS)

Button.o: Button.cpp Button.h
	g++ $(OPTS) $(MACOSX_DEFINE) -c Button.cpp $(LIBS)

Circle.o: Circle.cpp Circle.h
	g++ $(OPTS) $(MACOSX_DEFINE) -c Circle.cpp $(LIBS)

#Eye detection files
EyeInterface.o: EyeInterface.h EyeInterface.cpp
	g++ $(OPTS) -c EyeInterface.cpp

OpenCV/helpers.o: OpenCV/helpers.h OpenCV/helpers.cpp
	g++ $(OPTS) -o OpenCV/helpers.o -c OpenCV/helpers.cpp

OpenCV/findEyeCorner.o: OpenCV/findEyeCorner.h OpenCV/findEyeCorner.cpp
	g++ $(OPTS) -o OpenCV/findEyeCorner.o -c OpenCV/findEyeCorner.cpp

OpenCV/findEyeCenter.o: OpenCV/findEyeCenter.h OpenCV/findEyeCenter.cpp
	g++ $(OPTS) -o OpenCV/findEyeCenter.o -c OpenCV/findEyeCenter.cpp

TARBALL_FILES = README Makefile Makefile.Nikesh.Fedora *.cpp *.h OpenCV/ Images/ Documentation/
tarball: $(TARBALL_FILES)
	tar cfz proj.tar.gz $(TARBALL_FILES)	
