#ifdef _WIN32
#include <windows.h>
#endif

#include "header.hpp"

using namespace std;

string gradient = "@BWZJf/1+<!:^' ";
string path;
cv::VideoCapture video;
int len_terminal = 200;

cv::Mat photo, frame, gray, resized;

void video_process() {
    while (true) {
        cout << "Введите путь к файлу: "; cin >> path;
        video.open(path);
        if (video.isOpened()) {
            break;
        }
        else {
            cout << "Файл не найден, повторите попытку " << endl;
        }
        video.release();
    }

    double fps = video.get(cv::CAP_PROP_FPS);//cap_prop_fps метод opencv для счета фпс видео
    int delay;
    if (fps > 0) {
        delay = 1000 /fps;
    }
    else {
        delay = 16;
    }

    while (true) {
        video >> frame;
        if (frame.empty()) break;
        double scale = (double)len_terminal / frame.cols;

        //ВАЖНО: по высоте жмем в 2 раза сильнее (0.5), иначе арт будет вытянутым
        cv::resize(frame, resized, cv::Size(), scale, scale * 0.5);
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
}

void photo_process () {
    cout << "введите путь к картинке: "<< endl; cin >> path;
    photo = cv::imread(path);
    double scale = (double)len_terminal / photo.cols;
    cv::Mat resized;
    cv::resize(photo, resized, cv::Size(), scale, scale * 0.5);
    cv::cvtColor(resized, gray, cv::COLOR_BGR2GRAY);

    string output = "";
    for (int y = 0; y < gray.rows; y++) {
        for (int x = 0; x < gray.cols; x++) {
            uint8_t intensity = gray.at<uint8_t>(y, x);
            int index = intensity * (gradient.length() - 1) / 255;
            output += gradient[index];
        }
        output += "\n";
    }
    cout << "\033[H" << output << flush;
}

int main() {
#ifdef _WIN32
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
#endif

    int mode;

    while(true) {
        cout << " 1. Видео \n 2. Фото \n 0. Выход" << endl;
        cin >> mode;
        if (mode == 1){
            video_process();
        }
        else if (mode == 2) {
            photo_process();
        }
        else if (mode == 0){
            exit(0);
        }
    }
    return 0;
}
