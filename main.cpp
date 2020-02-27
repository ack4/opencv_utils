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
    if (!cap.isOpened()) {
        return -1;
    }

    cv::Mat frame;
    while (cap.read(frame)) {
        cout << fps.getFps() << endl;

        auto cropFrame = CvUtils::cropFrame(frame, 70, 70, 140, 140);
        auto bgrFrames = CvUtils::splitBGR(frame);
//        auto bgrFrames = CvUtils::cscBGR2YUV(frame);
//        auto bgrFrames = CvUtils::cscBGR2HSV(frame);
//        cv::imshow("window", frame);
        cv::imshow("crop_window", cropFrame);
        cv::imshow("palain", CvUtils::createPlain(70,70,cv::Scalar(12,2,127)));
        cv::imshow("b", bgrFrames[0]);
        cv::imshow("g", bgrFrames[1]);
        cv::imshow("r", bgrFrames[2]);
        cv::imshow("window", frame);
        cv::imshow("window2", CvUtils::resize(CvUtils::cscBGR2YUV2BGR(frame),0.5));
        const int key = cv::waitKey(1);
        if (key == 'q') {
            break;
        } else if (key == 's') {
            cv::imwrite("img.png", frame);
        }
    }

    cv::destroyAllWindows();
    cap.release();
    return 0;
}




