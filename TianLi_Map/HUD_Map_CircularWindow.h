#pragma once
//#include <opencv2/opencv.hpp>
#include <QWidget>
#include "ui_HUD_Map_CircularWindow.h"

class HUD_Map_CircularWindow : public QWidget
{
	Q_OBJECT

public:
	HUD_Map_CircularWindow(QWidget *parent = Q_NULLPTR);
	~HUD_Map_CircularWindow();

private:
	Ui::HUD_Map_CircularWindow ui;

private:
	QImage RenderImage;
	cv::Mat MapSource;
	cv::Mat MainMat;

	double scale = 2;
	cv::Point2d zerosMinMap = cv::Point2d(1428, 2937);//Point(5352, 9432)
		//完整地图大小
	cv::Size mapSize;
	cv::Rect minMapRect;
private:
	void paintEvent(QPaintEvent *);

public slots:
	void updateImage();

	void setMapSource(const cv::Mat mapSource);
	void setAvatarPos(double x, double y);
};

