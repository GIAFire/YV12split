# YV12split
对YV12编码的图像进行通道分离、合并、转换色域RGB
工程内包含 Makefile 文件。

如果你们的opencv环境搭建是标准的，解压附件的.zip 包，并进入 yuv_crop_resize_tests 目录并执行 make 应该是可以正常编译的。


运行方法为

make run


包内文件如下

yuv_crop_resize_tests
├── image_helper.cpp // crop 和 resize 主要在这里实现
├── image_helper.h   // 头文件
├── main.cc          // 程序主入口，这里面包含从输入文件（必须是YV12格式且大小为1280x720），封装进 cv::Mat，调用 crop和resize的接口和显示的过程
├── Makefile         // 编译文件
├── test_image_720.jpg // 输入文件（可视）
└── test_image.yv12  // 输入文件
