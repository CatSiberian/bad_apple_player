#include "header.hpp"

using namespace std;
using namespace cv;

string source_video;

vector<Mat> ConvertA(VideoCapture video) {
    vector<Mat> frames;
    Mat frame;
    Mat temp;
    while (true) {
        video >> frame;
        if (frame.empty())
            break;
        cv::resize(frame, temp, cv::Size(), 0.4, 0.4);
        frames.push_back(temp.clone());
    }
    video.release();
    return frames;
}

vector<string> ASCIIB(vector<Mat> frames) {
    vector<string> res;
    for (int i = 0; i < frames.size(); i++)
    {
        string str = "";
        Mat frame = frames[i];
        for (int y = 0; y < frame.rows; y += 2) {
            for (int x = 0; x < frame.cols; x++) {
                Vec3b& color = frame.at<Vec3b>(y, x);
                if (color[0] == 0 && color[1] == 0 && color[2] == 0)
                    str += " ";
                else if (color[0] == 255 && color[1] == 255 && color[2] == 255)
                    str += "%";
                else
                    str += "*";
            }
            str += "\n";
        }
        res.push_back(str);
    }
    return res;
}

int main(int argc, char** argv)
{
    cout << "введите путь файла" <<endl;
    cin >> source_video;
    VideoCapture video(source_video);

    if (!video.isOpened()) {
        cout << "Video doesn't find" << endl;
        cin.get();
        return -1;
    }
    vector<Mat> frames = ConvertA(video);
    vector<string> res = ASCIIB(frames);

    for (int i = 0; i < res.size(); i++)
    {
        cout << "\033[H" << res[i] << flush;
        this_thread::sleep_for(chrono::milliseconds(33));
    }
    return 0;
}