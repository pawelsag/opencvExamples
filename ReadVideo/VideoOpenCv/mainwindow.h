#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/cvstd.hpp"
#include <opencv2/videoio/videoio_c.h>
#include <chrono>
#include <thread>

namespace Ui {
class MainWindow;
}
enum class PlayerStatus{
    ACTIVE,
    PAUSE,
    EXIT
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0, const char *fileName = "");
    void keyPressEvent(QKeyEvent *event);
    void videoPlayerStart();
    ~MainWindow();

private slots:
    void on_Play_released();

    void on_pause_released();

    void on_TimeLine_sliderReleased();

private:
    Ui::MainWindow *ui;
    cv::VideoCapture cap;
    cv::Mat frame;
    cv::VideoWriter writer;

    int width, height, frameCount, currentFrame{0};
    double fps;
    std::unique_ptr<std::thread> player;
    PlayerStatus status;

    // private functions
    void setFrame();
};

#endif // MAINWINDOW_H
