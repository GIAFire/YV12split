#include <cstdio>
#include <iostream>
#include <opencv2/opencv.hpp>

#include "image_helper.h"

#define IMAGE_WIDTH 1280
#define IMAGE_HEGHT 720

int main(const int argc, const char** argv) {
  std::cout << "Hello world!" << std::endl;

  if (argc <= 1) {
    std::cout << "Must accept 1 parameter" << std::endl;
    return 1;
  }

  // Read file from input parameter.
  FILE* inputFile = fopen(argv[1], "r");
  if (inputFile == nullptr) {
    fprintf(stderr, "Failed read input file: %s\n", argv[1]);
    return 1;
  }

  // Create heap space to retain the image rawdata.
  uint8_t* yv12Raw = (uint8_t*) malloc(IMAGE_HEGHT * IMAGE_WIDTH /* width x height */ * 3 / 2 /* 12bpp */ * sizeof(uint8_t));
  // Normally should not happend.
  if (yv12Raw == nullptr) {
    fprintf(stderr, "Failed to alloc 720p memory of image, out of memory\n");
    return 1;
  }

  // Try reading image raw data.
  size_t readLength = 0;
  uint8_t* fileReadPtr = yv12Raw;
  do {
    readLength = fread(fileReadPtr, sizeof(uint8_t), 4096, inputFile);
    fileReadPtr += readLength;
  } while (readLength > 0);

  fclose(inputFile);

  // Creat the cv::Mat container to store the yv12 data.
  cv::Mat yv12(IMAGE_HEGHT * 3 / 2 /*rows*/ , IMAGE_WIDTH /*cols*/, CV_8UC1, yv12Raw);
#if 0
  std::cout << "YV12 size: width = " << yv12.size().width
            << ", height = " << yv12.size().height
            << ", rows = " << yv12.rows
            << ", cols = " << yv12.cols
            << ", chns = " << yv12.channels()
            << std::endl;
#endif
  // Show loaded image with BGR color format.
  cv::Mat imgBgr;
  cv::cvtColor(yv12, imgBgr, cv::COLOR_YUV2BGR_YV12);
#if 0
  std::cout << "JPG size: width = " << imgBgr.size().width
            << ", height = " << imgBgr.size().height
            << ", rows = " << imgBgr.rows
            << ", cols = " << imgBgr.cols
            << ", chns = " << imgBgr.channels()
            << std::endl;
#endif
  cv::imshow("Origin", imgBgr);
  cv::waitKey(0);

  // Now, deside the crop size.
  int x = 100;
  int y = 100;
  int width = 400;
  int height = 400;

  // Now, we crop the yv12 image and request output format with BGR(BGR_888)
  cv::Mat croppedBgr = api::hexintek::utils::cropMat(yv12, PixelFormat::YV12,
                                                     cv::Rect(x, y, width, height),
                                                     PixelFormat::BGR_888);
  // And crop a reference image to exam your result is correct.
  cv::Mat sampleBgrCropped = imgBgr(cv::Rect(x, y, width, height));

  // Show both your result and reference image.
  cv::imshow("Sample_crop", sampleBgrCropped);
  if (croppedBgr.empty()) {
    std::cerr << "WARNING: unsupported format or cropMat not implemented" << std::endl;
  } else {
    cv::imshow("Result_crop", croppedBgr);
  }
  cv::waitKey(0);

  // Now we try to resize input image to 160*90
  int resizedWidth = 160;
  int resizedHeight = 90;

  cv::Mat resizedBgr = api::hexintek::utils::resizeMat(yv12, PixelFormat::YV12,
                                                       cv::Size(resizedWidth, resizedHeight),
                                                       PixelFormat::BGR_888);
  cv::Mat sampleBgrResized;
  cv::resize(imgBgr, sampleBgrResized, cv::Size(resizedWidth, resizedHeight));
  cv::imshow("Sample_resized", sampleBgrResized);
  if (resizedBgr.empty()) {
    std::cerr << "WARNING: unsupported format or resizedMat not implemented" << std::endl;
  } else {
    cv::imshow("Result_resized", resizedBgr);
  }
  cv::waitKey(0);

  free(yv12Raw);
  yv12Raw = nullptr;

  return 0;
}
