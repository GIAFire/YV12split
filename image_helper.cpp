#include "image_helper.h"
using namespace cv;
using namespace std;

namespace api {
namespace hexintek {
namespace utils {

void dumpFile(const uint8_t* rawData, size_t size /*how many bytes to write*/, const char* filename) {
  FILE* file = fopen(filename, "w");
  fwrite(rawData, sizeof(uint8_t), size, file);
  fclose(file);
}

void dumpFile(cv::Mat& img, size_t size, const char* filename) {
  dumpFile(img.data, size, filename);
}

cv::Mat cropMat(cv::Mat& src, ::PixelFormat srcFormat, cv::Rect rect, ::PixelFormat targetFormat) {
  Mat result,bgr;
  int width = 1280;
  int height = 720;

  // 计算每个分量的尺寸
  int ySize = width * height;
  int uvSize = ySize / 4;

  // 分离Y通道
  Mat yChannel(height, width, CV_8UC1, src.data);
  
  // 分离V通道
  Mat vChannel(height / 2, width / 2, CV_8UC1, src.data + ySize);
  
  // 分离U通道
  Mat uChannel(height / 2, width / 2, CV_8UC1, src.data + ySize + uvSize);

  // 按比例缩放三个通道大小
  Rect vuRect(50,50,200,200);
  Mat yRect = yChannel(rect).clone();
  Mat vRect = vChannel(vuRect).clone();
  Mat uRect = uChannel(vuRect).clone();

  ySize = yRect.size().height * yRect.size().width;
  uvSize = vRect.size().height * vRect.size().width;

  // 合并Y、U和V分量
  unsigned char* mergedData = new unsigned char[ySize + uvSize + uvSize];
  memset(mergedData, 0, (ySize + uvSize + uvSize) * sizeof(unsigned char));
  memcpy(mergedData, yRect.data, ySize);
  memcpy(mergedData + ySize, vRect.data, uvSize);
  memcpy(mergedData + ySize + uvSize, uRect.data, uvSize);

  // 创建合并后的图像
  Mat yuv(rect.height * 3 / 2, rect.width, CV_8UC1, mergedData); 
  cvtColor(yuv, result, COLOR_YUV2BGR_YV12);
  delete[] mergedData;
  return result;
}

cv::Mat resizeMat(cv::Mat& src, ::PixelFormat srcFormat, cv::Size targetSize, ::PixelFormat targetFormat) {
  Mat result,bgr;
  int width = 1280;
  int height = 720;

  // 计算每个分量的尺寸
  int ySize = width * height;
  int uvSize = ySize / 4;

  // 分离Y通道
  Mat yChannel(height, width, CV_8UC1, src.data);
  
  // 分离V通道
  Mat vChannel(height / 2, width / 2, CV_8UC1, src.data + ySize);
  
  // 分离U通道
  Mat uChannel(height / 2, width / 2, CV_8UC1, src.data + ySize + uvSize);

  // 按比例缩放三个通道大小
  Mat yResize,vResize,uResize;
  resize(yChannel, yResize, targetSize);
  resize(vChannel, vResize, Size(80, 45));
  resize(uChannel, uResize, Size(80, 45));

  ySize = yResize.size().height * yResize.size().width;
  uvSize = vResize.size().height * vResize.size().width;

  // 合并Y、U和V分量
  unsigned char* mergedData = new unsigned char[ySize + uvSize + uvSize];
  memset(mergedData, 0, (ySize + uvSize + uvSize) * sizeof(unsigned char));
  memcpy(mergedData, yResize.data, ySize);
  memcpy(mergedData + ySize, vResize.data, uvSize);
  memcpy(mergedData + ySize + uvSize, uResize.data, uvSize);

  // 创建合并后的图像
  Mat yuv(targetSize.height * 3 / 2, targetSize.width, CV_8UC1, mergedData); 
  cvtColor(yuv, result, COLOR_YUV2BGR_YV12);
  delete[] mergedData;
  return result;
}

} // namespace utils
} // namespace utils
} // namespace api
