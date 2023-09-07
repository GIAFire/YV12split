#include <opencv2/opencv.hpp>

enum class PixelFormat {
    UNKNOWN = 0x0,
    RGBA_8888 = 0x1,
    RGBX_8888 = 0x2,
    RGB_888 = 0x3,
    RGB_565 = 0x4,
    NV16 = 0x10,
    NV21 = 0x11,
    YUY2 = 0x14,
    RGBA_FP16 = 0x16,
    RAW_SENSOR = 0x20,
    PRIVATE = 0x22,
    YUV_420_888 = 0x23,
    RAW_PRIVATE = 0x24,
    RAW10 = 0x25,
    RAW12 = 0x26,
    RGBA_1010102 = 0x2b,
    JPEG = 0x100,
    DEPTH_POINT_CLOUD = 0x101,
    RAW_DEPTH = 0x1002, // @hide
    YV12 = 0x32315659,
    Y8 = 0x20203859, // @hide
    Y16 = 0x20363159, // @hide
    DEPTH16 = 0x44363159,
    BGR_888 = 0x50000001 // Customized
};

namespace api {
namespace hexintek {
namespace utils {

cv::Mat cropMat(cv::Mat& src, ::PixelFormat srcFormat, cv::Rect rect, ::PixelFormat targetFormat);

cv::Mat resizeMat(cv::Mat& src, ::PixelFormat srcFormat, cv::Size targetSize, ::PixelFormat targetFormat);

}  // namespace utils
}  // namespace hexintek
}  // namespace api
