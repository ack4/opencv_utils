#include <iostream>
#include <vector>
#include "cvutils.h"
#include <opencv2/core/core.hpp>


CvUtils::CvUtils() {
    tm = cv::TickMeter();
    tm.start();
    counter = 0;
    fps = 0;
    fps_interval = 10;
}

CvUtils::~CvUtils() {
    std::cout << "delete!" << std::endl;
}

double CvUtils::getFps() {
    if (fps_interval != counter) {
        counter++;
        return fps;
    } else {
        tm.stop();
        fps = fps_interval / tm.getTimeSec();
        tm.reset();
        counter = 0;
        tm.start();
        return fps;
    }

}

void CvUtils::readImg(const std::string &filePath = "/opencv/sources/samples/data/pic6.png") {
    cv::Mat img = cv::imread(filePath);
    cv::imshow("window", img);
    cv::waitKey(0);
    cv::destroyAllWindows();
}

void CvUtils::showFrame(const cv::Mat &frame) {
    cv::imshow("disp", frame);
    cv::waitKey(0);
    cv::destroyAllWindows();
}


cv::Mat CvUtils::resize(cv::Mat inFrame, double scale = 1.0) {
    cv::Mat outFrame;
    cv::resize(inFrame, outFrame, cv::Size(), scale, scale, cv::INTER_LINEAR);
//    cv::resize(inFrame, outFrame, cv::Size(), scale, scale,cv::INTER_LANCZOS4);
    return outFrame;
}

cv::Mat CvUtils::createPlain(const int &width, const int &height, const unsigned char &fillVal) {
    cv::Mat outFrame(height, width, CV_8UC1, fillVal);
    return outFrame;
}

//cv::Scalar(b->g->r)
cv::Mat CvUtils::createPlain(const int &width, const int &height, const cv::Scalar &scalar) {
    cv::Mat outFrame(height, width, CV_8UC3, scalar);
    return outFrame;
}


cv::Mat CvUtils::cropFrame(const cv::Mat &frame, int leftTopX, int leftTopY, int width, int height) {
    cv::Rect rect = cv::Rect(leftTopX, leftTopY, width, height);
    cv::Mat outFrame(frame, rect);
    return outFrame;
}

std::vector<cv::Mat> CvUtils::splitBGR(const cv::Mat &frame) {
    cv::Mat channels[3];
    cv::split(frame, channels);
    std::vector<cv::Mat> outFrames;
    outFrames.emplace_back(channels[0]);//b
    outFrames.emplace_back(channels[1]);//g
    outFrames.emplace_back(channels[2]);//r
    return outFrames;
}

std::vector<cv::Mat> CvUtils::cscBGR2YUV(const cv::Mat &frame) {
    cv::Mat yuv;
    cv::cvtColor(frame, yuv, cv::COLOR_BGR2YUV);
    cv::Mat channels[3];
    cv::split(yuv, channels);
    std::vector<cv::Mat> outFrames;
    outFrames.emplace_back(channels[0]);//y
    outFrames.emplace_back(channels[1]);//u
    outFrames.emplace_back(channels[2]);//v
    return outFrames;
}

std::vector<cv::Mat> CvUtils::cscBGR2HSV(const cv::Mat &frame) {
    cv::Mat hsv;
    cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);
    cv::Mat channels[3];
    cv::split(hsv, channels);
    std::vector<cv::Mat> outFrames;
    outFrames.emplace_back(channels[0]);//h
    outFrames.emplace_back(channels[1]);//s
    outFrames.emplace_back(channels[2]);//v
    return outFrames;
}


cv::Mat CvUtils::cscBGR2YUV2BGR(const cv::Mat &frame) {
    cv::Mat yuv;
    cv::cvtColor(frame, yuv, cv::COLOR_BGR2YUV);
//    cv::Mat yuvCh[3];
    std::vector<cv::Mat> yuvCh;
    cv::split(yuv, yuvCh);

//    yuvCh[0] = resize(yuvCh[0], 0.05);
//    yuvCh[0] = resize(yuvCh[0], 20);
//    yuvCh[1] = createPlain(640, 480, 127);
//    yuvCh[2] = createPlain(640, 480, 0);

    //色情報の圧縮
    yuvCh[1] = resize(yuvCh[1], 0.025);
    yuvCh[1] = resize(yuvCh[1], 40);
    yuvCh[2] = resize(yuvCh[2], 0.025);
    yuvCh[2] = resize(yuvCh[2], 40);

    //チャンネル入れ替え
//    cv::Mat y = yuvCh[0];
//    cv::Mat u = yuvCh[1];
//    cv::Mat v = yuvCh[2];
//    yuvCh[0] = v;
//    yuvCh[1] = y;
//    yuvCh[2] = u;

    cv::Mat yuvMerge;
    cv::merge(yuvCh, yuvMerge);

    cv::Mat bgr;
    cv::cvtColor(yuvMerge, bgr, cv::COLOR_YUV2BGR);

    return bgr;
}


