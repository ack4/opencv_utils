#include <iostream>
#include "cvutils.h"

using namespace std;

int image();


int main() {
    image();
    return 0;
}

int image() {
    auto fps = CvUtils();
    cv::VideoCapture cap(0);
//    cv::VideoCapture cap("/x/sample.mp4");
    if (!cap.isOpened()) {
        return -1;
    }

    cv::Mat frame;
    while (cap.read(frame)) {
        auto s = std::to_string(fps.getFps()) + ":" + std::to_string(fps.getElapsedTimeMs());
        cout << s << endl;

//        auto cropFrame = CvUtils::cropFrame(frame, 70, 70, 140, 140);
//        auto frames = CvUtils::splitBGR(frame);
//        auto frames = CvUtils::cscBGR2YUV(frame);
//        auto frames = CvUtils::cscBGR2HSV(frame);
//        cv::imshow("window", frame);
//        cv::imshow("crop_window", cropFrame);
//        cv::imshow("palain", CvUtils::createPlain(70,70,cv::Scalar(12,2,127)));
//        cv::imshow("0", frames[0]);
//        cv::imshow("1", frames[1]);
//        cv::imshow("2", frames[2]);
//        cv::imshow("window", CvUtils::resize(frame,0.5));
//        cv::imshow("window2", CvUtils::resize(CvUtils::cscBGR2YUV2BGR(frame),0.5));
//        cv::imshow("window", CvUtils::stylizePencil(frame));
        cv::imshow("window", frame);
        const int key = cv::waitKey(8);
        if (key == 'q') {
            break;
        }
    }

    cv::destroyAllWindows();
    cap.release();
    return 0;
}


