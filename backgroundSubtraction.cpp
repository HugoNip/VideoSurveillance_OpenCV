// BACKGROUND SUBTRACTION

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/video/background_segm.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <sstream>
#include <memory>

int main (int argc, char* argv[])
{
    // Current frame
    cv::Mat frame;

    // Foreground mask generated by MOG2 method
    cv::Mat fgMaskMOG2;

    // MOG2 background substractor
    cv::Ptr<cv::BackgroundSubtractor> pMOG2;

    char ch;

    // Create the capture object
    cv::VideoCapture cap(0);

    if (!cap.isOpened())
        return -1;

    // Create GUI windows
    cv::namedWindow("Frame");
    cv::namedWindow("FG Mask MOG 2");

    // Create MOG2 Background Subtractor object
    pMOG2 = cv::createBackgroundSubtractorMOG2();

    // Scaling factor to resize the input frames from the webcam
    float scalingFactor = 0.75;

    // Iterate until the user presses the ESC key
    while (true)
    {
        // Capture the current frame
        cap >> frame;

        // Resize the frame
        cv::resize(frame, frame, cv::Size(), scalingFactor, scalingFactor, cv::INTER_AREA);

        // Update the MOG2 background model based on the current frame
        pMOG2->apply(frame, fgMaskMOG2);

        // Show the current frame
        cv::imshow("Frame", frame);

        // Show the MOG foreground mask
        cv::imshow("FG Mask MOG 2", fgMaskMOG2);

        // Get the keyboard input
        ch = cv::waitKey(30);
        if (ch == 27)
            break;
    }

    cap.release();

    cv::destroyAllWindows();

    return 0;
}
