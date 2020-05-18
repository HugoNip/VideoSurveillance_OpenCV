// FRAME DIFFERENCING

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/background_segm.hpp"

#include <iostream>
#include <sstream>

cv::Mat frameDiff(cv::Mat prevFrame, cv::Mat curFrame, cv::Mat nextFrame)
{
    cv::Mat diffFrames1, diffFrames2, output;

    // Compute absolute difference between current frame and the next frame
    cv::absdiff(nextFrame, curFrame, diffFrames1);

    // Compute absolute difference between current frame and the previous frame
    cv::absdiff(curFrame, prevFrame, diffFrames2);

    // Bitwise "AND" operation between the above two diff images
    cv::bitwise_and(diffFrames1, diffFrames2, output);

    return output;
}

cv::Mat getFrame(cv::VideoCapture cap, float scalingFactor)
{
    // float scalingFactor = 0.5;
    cv::Mat frame, output;

    // Capture the current frame
    cap >> frame;

    // Resize the frame
    cv::resize(frame, frame, cv::Size(), scalingFactor, scalingFactor, cv::INTER_AREA);

    // Convert to grayscale
    cv::cvtColor(frame, output, cv::COLOR_BGR2GRAY);

    return output;
}

int main(int argc, char* argv[])
{
    cv::Mat frame, preFrame, curFrame, nextFrame;
    char ch;

    // Create the capture object
    cv::VideoCapture cap(0);

    if (!cap.isOpened())
        return -1;

    // Create GUI windows
    std::string windowName = "Object Movement";
    cv::namedWindow(windowName);

    // Scaling factor to resize the input frames from the webcam
    float scalingFactor = 0.75;

    preFrame = getFrame(cap, scalingFactor);
    curFrame = getFrame(cap, scalingFactor);
    nextFrame = getFrame(cap, scalingFactor);

    // Iterate until the user presses the ESC key
    while (true)
    {
        // Show the object movement
        cv::imshow(windowName, frameDiff(preFrame, curFrame, nextFrame));

        // Update the variables and grab the next frame
        preFrame = curFrame;
        curFrame = nextFrame;
        nextFrame = getFrame(cap, scalingFactor);

        // Get the keyboard input and check if it's 'ESC'
        ch = cv::waitKey(30);
        if (ch == 27)
            break;
    }

    // Release the video capture object
    cap.release();

    // Close all windows
    cv::destroyAllWindows();

    return 0;
}
