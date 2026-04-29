#include "header.hpp"

using namespace std;

string gradient = "$B8W#ohbpwZ0LJYznf/|1[+-<!I:^' ";

int main() {
    string path;
    cout << "Path: "; cin >> path;
    cv::VideoCapture video(path);

    if (!video.isOpened()) return -1;
    double fps = video.get(cv::CAP_PROP_FPS);//cap_prop_fps метод opencv для счета фпс видео
    int delay;
    if (fps > 0) {
        delay = 1000 /fps;
    }
    else {
        delay = 16;
    }
    cv::Mat frame, gray;
    int len_terminal = 200;

    while (true) {
        video >> frame;
        if (frame.empty()) break;
        double scale = (double)len_terminal / frame.cols;

        // 2. ВАЖНО: по высоте жмем в 2 раза сильнее (0.5), иначе арт будет вытянутым
        cv::Mat resized;
        cv::resize(frame, resized, cv::Size(), scale, scale * 0.5);

        // 3. Переводим в ч/б сразу средствами OpenCV для четкости
        cv::cvtColor(resized, gray, cv::COLOR_BGR2GRAY);

        string output = "";
        for (int y = 0; y < gray.rows; y++) {
            for (int x = 0; x < gray.cols; x++) {
                // Получаем яркость (0-255)
                uint8_t intensity = gray.at<uint8_t>(y, x);
                // Выбираем символ
                int index = intensity * (gradient.length() - 1) / 255;
                output += gradient[index];
            }
            output += "\n";
        }

        // Очистка и вывод
        cout << "\033[H" << output << flush;
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
    return 0;
}
