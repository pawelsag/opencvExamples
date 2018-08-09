#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "helperfunctions.cpp"
#include <QDebug>
#include <QInputEvent>

#include <QPixmap>
#include <QImage>
#include "opencv2/core/core_c.h"
#define RGBA2BGR 3
using namespace cv;

MainWindow::MainWindow(QWidget *parent, const  char *fileName) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    if(!isNumber( fileName) )
        cap.open( String( fileName ) );
    else
        cap.open( atoi(fileName) );

    fps = cap.get( cv::CAP_PROP_FPS );
    cap.set(CV_CAP_PROP_FRAME_WIDTH,1920);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,1000);

    width = (int)cap.get(CAP_PROP_FRAME_WIDTH);
    height = (int)cap.get(CAP_PROP_FRAME_HEIGHT);
    frameCount = (int)cap.get(CAP_PROP_FRAME_COUNT);

    ui->setupUi(this);
    this->ui->TimeLine->setMaximum(frameCount);

    player = std::make_unique<std::thread>(&MainWindow::videoPlayerStart, this);

}

void MainWindow::keyPressEvent(QKeyEvent *event){

    switch (event->key()){
        case Qt::Key_S:
            status = PlayerStatus::PAUSE;
            currentFrame = cap.get(CV_CAP_PROP_POS_FRAMES);
            currentFrame++;
            this->setFrame();
            break;
        case Qt::Key_D:
            status = PlayerStatus::PAUSE;
            currentFrame = cap.get(CV_CAP_PROP_POS_FRAMES);
            currentFrame--;
            this->setFrame();
            break;
        case Qt::Key_Escape:
            status = PlayerStatus::EXIT;
            break;

    }
}

void MainWindow::videoPlayerStart()
{

    Size size( width , height);

    writer.open( "output", CV_FOURCC('M','J','P','G'), fps, size );
    while(true){
        cap >> frame;
        if( frame.empty() )
            break;
        cvtColor(frame, frame, RGBA2BGR);
        ui->display->setPixmap((QPixmap::fromImage(QImage(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888))));
        if(status == PlayerStatus::PAUSE)
            while( status == PlayerStatus::PAUSE){
               std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        else if( status == PlayerStatus::EXIT )
            break;
        std::this_thread::sleep_for(std::chrono::milliseconds( 20 ));
        currentFrame++;
        this->ui->TimeLine->setValue(currentFrame);

    }
}
void MainWindow::setFrame(){
    cap.set(CV_CAP_PROP_POS_FRAMES,currentFrame);
    cap >> frame;
    cvtColor(frame, frame, RGBA2BGR);
    ui->display->setPixmap((QPixmap::fromImage(QImage(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888))));
}

MainWindow::~MainWindow()
{
    delete ui;
    status = PlayerStatus::EXIT;
    player->join();
}

void MainWindow::on_Play_released()
{
    this->status = PlayerStatus::ACTIVE;
}

void MainWindow::on_pause_released()
{
    this->status = PlayerStatus::PAUSE;
}

void MainWindow::on_TimeLine_sliderReleased()
{

}
