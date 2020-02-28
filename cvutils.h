#ifndef OPENCV_TEST_CVUTILS_H
#define OPENCV_TEST_CVUTILS_H

#include "opencv2/opencv.hpp"


class CvUtils {

public:
    CvUtils();

    ~CvUtils();

    static void readImg(const std::string &filePath);

    static void showFrame(const cv::Mat &frame);

    static cv::Mat resize(cv::Mat inFrame, double scale);

    static cv::Mat createPlain(const int &width, const int &height, const unsigned char &fillVal);

    static cv::Mat createPlain(const int &width, const int &height, const cv::Scalar &s);

    static cv::Mat cropFrame(const cv::Mat &frame, int leftTopX, int leftTopY, int width, int height);

    static std::vector<cv::Mat> splitBGR(const cv::Mat &frame);

    static std::vector<cv::Mat> cscBGR2YUV(const cv::Mat &frame);

    static std::vector<cv::Mat> cscBGR2HSV(const cv::Mat &frame);

    static cv::Mat cscBGR2YUV2BGR(const cv::Mat &frame);

    static cv::Mat stylizePencil(cv::Mat frame);

    int getFps();

    int getElapsedTimeMs();


private:
    //for getFps()
    int count;
    int fps;
    double freq;
    int diffTime;
    int64 tmStart;
    int64 tmNow;

    //for getElapsedTimeMs()
    int64 start;
    int64 end;
    int elapsedTime;
};

#endif //OPENCV_TEST_CVUTILS_H
