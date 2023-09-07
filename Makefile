
TARGET := test_yuv_crop

all : $(TARGET)

OPENCV_INCLUDES := $(wildcard /usr/local/include/opencv4) $(wildcard /usr/include/opencv4)

ifeq (,$(strip $(OPENCV_INCLUDES)))
$(error "Failed to find opencv includes, abort")
endif

$(TARGET): main.cc image_helper.cpp Makefile
	$(CXX) -MMD $< image_helper.cpp -o $@ -g $(addprefix -I,$(OPENCV_INCLUDES)) -I. -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs

ifndef TEST_FILE
  TEST_FILE=test_image.yv12
endif

run : $(TARGET)
	./$(TARGET) $(TEST_FILE)

clean:
	rm -f *.o *.d $(TARGET)

-include *.d
