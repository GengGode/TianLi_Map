#include "HUD_Map_CircularWindow.h"

#include <QPainter>

using namespace cv;

HUD_Map_CircularWindow::HUD_Map_CircularWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Popup | Qt::Tool);
	this->setAttribute(Qt::WA_TranslucentBackground, true);
	this->setAttribute(Qt::WA_TransparentForMouseEvents, true);

	MapSource = imread("GIMAP.png");
	setAvatarPos(0, 0);
}

HUD_Map_CircularWindow::~HUD_Map_CircularWindow()
{
}

void HUD_Map_CircularWindow::paintEvent(QPaintEvent *)
{
	//设置画面为地图
	QPainter painter(this);
	painter.drawImage(0, 0, RenderImage);
}

void HUD_Map_CircularWindow::updateImage()
{
	//std::vector<Mat> mv0;
	//std::vector<Mat> mv1;
	//通道分离
	//split(MainMat, mv0);
	//split(RES.MAINMASK, mv1);
	//mv0.push_back(mv1[0]);
	//merge(mv0, MainMat);
	RenderImage = QImage((uchar*)(MainMat.data), MainMat.cols, MainMat.rows, MainMat.cols * (MainMat.channels()), QImage::Format_ARGB32);
}

void HUD_Map_CircularWindow::setMapSource(const cv::Mat mapSource)
{
	this->MapSource = mapSource;

	mapSize = this->MapSource.size();
}

void HUD_Map_CircularWindow::setAvatarPos(double x, double y)
{
	//MainMat = GetMatRange(x, y);

	static Mat minMap;

	//需要能越过边界，否则大范围显示时无法保证角色箭头处于正确位置

	Point minMapPoint = Point(0, 0);

	Size reMapSize = Size(this->width(), this->height()); // autoMapSize;
	Point2d reAutoMapCenter = Size(this->width(), this->height())/2;//autoMapCenter;
	reMapSize.width = (reMapSize.width * scale);
	reMapSize.height = (reMapSize.height * scale);
	reAutoMapCenter = Point2d(this->width(), this->height()) * scale;//autoMapCenter * MET.scale;

	Point2d LT = zerosMinMap - reAutoMapCenter;
	Point2d RB = zerosMinMap + Point2d(reMapSize) - reAutoMapCenter;

	minMapPoint = LT;

	if (LT.x < 0)
	{
		minMapPoint.x = 0;
	}
	if (LT.y < 0)
	{
		minMapPoint.y = 0;
	}
	if (RB.x > mapSize.width)
	{
		minMapPoint.x = mapSize.width - reMapSize.width;
	}
	if (RB.y > mapSize.height)
	{
		minMapPoint.y = mapSize.height - reMapSize.height;
	}
	minMapRect = Rect(minMapPoint, reMapSize);

	cv::resize(MapSource(minMapRect), minMap, Size(this->width(), this->height()));
	minMap.copyTo(MainMat);
	//return minMap;
}

#ifdef OpencvVis

#include <opencv2/opencv.hpp>
using namespace cv;

double dis2(double a, double b)
{
	return a * a + b * b;
}

Mat SharRectMat(Mat in, double r, int mode)
{
	//Mat out(row, col, CV_8UC1, Scalar(255, 255, 255));
	Rect roi;
	Mat ReRoi;
	int len;

	roi = Rect(0, 0, cvRound(r), cvRound(r));
	ReRoi = in(roi);
	len = min(roi.width, roi.height);
	for (int i = 0; i < ReRoi.cols; i++)
	{
		for (int j = 0; j < ReRoi.rows; j++)
		{
			double dis = sqrt(dis2(ReRoi.cols - i, ReRoi.rows - j));

			if (dis > len)
			{
				ReRoi.at<uchar>(j, i) = 0;
			}
			else if (dis > len - r)
			{
				ReRoi.at<uchar>(j, i) = 255.0 / (r)*(len - dis);
			}
			else
			{
				ReRoi.at<uchar>(j, i) = 255;
			}
		}
	}
	return in;
}
Mat calMask3(int col, int row, int r, double r0, int flag)
{
	Mat out(row, col, CV_8UC1, Scalar(255, 255, 255));

	int len = min(cvRound(col*0.5), cvRound(row*0.5));
	for (int i = 0; i < col; i++)
	{
		for (int j = 0; j < row; j++)
		{
			double dis = sqrt(dis2(cvRound(col*0.5) - i, cvRound(row*0.5) - j));
			if (dis > len)
			{
				out.at<uchar>(j, i) = 0;
			}
			else if (dis > len - r)
			{
				out.at<uchar>(j, i) = 255.0 / (r)*(len - dis);
			}
			else
			{
				out.at<uchar>(j, i) = 255;
			}
		}
	}
	return out;
}

Mat calMask2(int col, int row, int r, double r0, int flag)
{
	Mat out(row, col, CV_8UC1, Scalar(255, 255, 255));
	Rect roi;
	Mat ReRoi;
	int len;

	roi = Rect(0, 0, cvRound(r + r0), cvRound(r + r0));
	ReRoi = out(roi);
	len = min(roi.width, roi.height);
	for (int i = roi.x; i < roi.x + roi.width; i++)
	{
		for (int j = roi.y; j < roi.y + roi.height; j++)
		{
			double dis = sqrt(dis2(roi.x + roi.width - i, roi.y + roi.height - j));
			if (dis > len)
			{
				out.at<uchar>(i, j) = 0;
			}
			else if (dis > len - r)
			{
				out.at<uchar>(i, j) = 255.0 / (r)*(len - dis);
			}
			else
			{
				out.at<uchar>(i, j) = 255;
			}
		}
	}

	roi = Rect(0, (r + r0), (r + r0), col - (r + r0) * 2);
	len = min(roi.width, roi.height);
	for (int i = roi.x; i < roi.x + roi.width; i++)
	{
		for (int j = roi.y; j < roi.y + roi.height; j++)
		{
			double dis = sqrt(dis2(roi.x + roi.width - i, 0));
			if (dis > len)
			{
				out.at<uchar>(i, j) = 0;
			}
			else if (dis > len - r)
			{
				out.at<uchar>(i, j) = 255.0 / (r)*(len - dis);
			}
			else
			{
				out.at<uchar>(i, j) = 255;
			}
		}
	}

	roi = Rect(0, col - (r + r0), (r + r0), (r + r0));
	len = min(roi.width, roi.height);
	for (int i = roi.x; i < roi.x + roi.width; i++)
	{
		for (int j = roi.y; j < roi.y + roi.height; j++)
		{
			double dis = sqrt(dis2(roi.x + roi.width - i, roi.y + roi.height - (r + r0) - j));
			if (dis > len)
			{
				out.at<uchar>(i, j) = 0;
			}
			else if (dis > len - r)
			{
				out.at<uchar>(i, j) = 255.0 / (r)*(len - dis);
			}
			else
			{
				out.at<uchar>(i, j) = 255;
			}
		}
	}

	roi = Rect((r + r0), 0, row - (r + r0) * 2, (r + r0));
	len = min(roi.width, roi.height);
	for (int i = roi.x; i < roi.x + roi.width; i++)
	{
		for (int j = roi.y; j < roi.y + roi.height; j++)
		{
			double dis = sqrt(dis2(0, roi.y + roi.height - j));
			if (dis > len)
			{
				out.at<uchar>(i, j) = 0;
			}
			else if (dis > len - r)
			{
				out.at<uchar>(i, j) = 255.0 / (r)*(len - dis);
			}
			else
			{
				out.at<uchar>(i, j) = 255;
			}
		}
	}

	roi = Rect((r + r0), col - (r + r0), row - (r + r0) * 2, (r + r0));
	len = min(roi.width, roi.height);
	for (int i = roi.x; i < roi.x + roi.width; i++)
	{
		for (int j = roi.y; j < roi.y + roi.height; j++)
		{
			double dis = sqrt(dis2(0, roi.y + roi.height - (r + r0) - j));
			if (dis > len)
			{
				out.at<uchar>(i, j) = 0;
			}
			else if (dis > len - r)
			{
				out.at<uchar>(i, j) = 255.0 / (r)*(len - dis);
			}
			else
			{
				out.at<uchar>(i, j) = 255;
			}
		}
	}

	roi = Rect(row - (r + r0), 0, cvRound(r + r0), cvRound(r + r0));
	ReRoi = out(roi);
	len = min(roi.width, roi.height);
	for (int i = roi.x; i < roi.x + roi.width; i++)
	{
		for (int j = roi.y; j < roi.y + roi.height; j++)
		{
			double dis = sqrt(dis2(roi.x + roi.width - (r + r0) - i, roi.y + roi.height - j));
			if (dis > len)
			{
				out.at<uchar>(i, j) = 0;
			}
			else if (dis > len - r)
			{
				out.at<uchar>(i, j) = 255.0 / (r)*(len - dis);
			}
			else
			{
				out.at<uchar>(i, j) = 255;
			}
		}
	}

	roi = Rect(row - (r + r0), (r + r0), (r + r0), col - (r + r0) * 2);
	len = min(roi.width, roi.height);
	for (int i = roi.x; i < roi.x + roi.width; i++)
	{
		for (int j = roi.y; j < roi.y + roi.height; j++)
		{
			double dis = sqrt(dis2(roi.x + roi.width - (r + r0) - i, 0));
			if (dis > len)
			{
				out.at<uchar>(i, j) = 0;
			}
			else if (dis > len - r)
			{
				out.at<uchar>(i, j) = 255.0 / (r)*(len - dis);
			}
			else
			{
				out.at<uchar>(i, j) = 255;
			}
		}
	}

	roi = Rect(row - (r + r0), col - (r + r0), (r + r0), (r + r0));
	len = min(roi.width, roi.height);
	for (int i = roi.x; i < roi.x + roi.width; i++)
	{
		for (int j = roi.y; j < roi.y + roi.height; j++)
		{
			double dis = sqrt(dis2(roi.x + roi.width - (r + r0) - i, roi.y + roi.height - (r + r0) - j));
			if (dis > len)
			{
				out.at<uchar>(i, j) = 0;
			}
			else if (dis > len - r)
			{
				out.at<uchar>(i, j) = 255.0 / (r)*(len - dis);
			}
			else
			{
				out.at<uchar>(i, j) = 255;
			}
		}
	}
	return out;
}

Mat calMask(int col, int row, double r, int flag)
{
	Mat out(row, col, CV_8UC1, Scalar(255, 255, 255));
	Rect roi;
	Mat ReRoi;
	int len;

	roi = Rect(0, 0, cvRound(r), cvRound(r));
	ReRoi = out(roi);
	len = min(roi.width, roi.height);
	for (int i = roi.x; i < roi.x + roi.width; i++)
	{
		for (int j = roi.y; j < roi.y + roi.height; j++)
		{
			double dis = sqrt(dis2(roi.x + roi.width - i, roi.y + roi.height - j));
			if (dis > len)
			{
				out.at<uchar>(i, j) = 0;
			}
			else if (dis > len - r)
			{
				out.at<uchar>(i, j) = 255.0 / (r)*(len - dis);
			}
			else
			{
				out.at<uchar>(i, j) = 255;
			}
		}
	}

	roi = Rect(0, r, r, col - r * 2);
	len = min(roi.width, roi.height);
	for (int i = roi.x; i < roi.x + roi.width; i++)
	{
		for (int j = roi.y; j < roi.y + roi.height; j++)
		{
			double dis = sqrt(dis2(roi.x + roi.width - i, 0));
			if (dis > len)
			{
				out.at<uchar>(i, j) = 0;
			}
			else if (dis > len - r)
			{
				out.at<uchar>(i, j) = 255.0 / (r)*(len - dis);
			}
			else
			{
				out.at<uchar>(i, j) = 255;
			}
		}
	}

	roi = Rect(0, col - r, r, r);
	len = min(roi.width, roi.height);
	for (int i = roi.x; i < roi.x + roi.width; i++)
	{
		for (int j = roi.y; j < roi.y + roi.height; j++)
		{
			double dis = sqrt(dis2(roi.x + roi.width - i, roi.y + roi.height - r - j));
			if (dis > len)
			{
				out.at<uchar>(i, j) = 0;
			}
			else if (dis > len - r)
			{
				out.at<uchar>(i, j) = 255.0 / (r)*(len - dis);
			}
			else
			{
				out.at<uchar>(i, j) = 255;
			}
		}
	}

	roi = Rect(r, 0, row - r * 2, r);
	len = min(roi.width, roi.height);
	for (int i = roi.x; i < roi.x + roi.width; i++)
	{
		for (int j = roi.y; j < roi.y + roi.height; j++)
		{
			double dis = sqrt(dis2(0, roi.y + roi.height - j));
			if (dis > len)
			{
				out.at<uchar>(i, j) = 0;
			}
			else if (dis > len - r)
			{
				out.at<uchar>(i, j) = 255.0 / (r)*(len - dis);
			}
			else
			{
				out.at<uchar>(i, j) = 255;
			}
		}
	}

	roi = Rect(r, col - r, row - r * 2, r);
	len = min(roi.width, roi.height);
	for (int i = roi.x; i < roi.x + roi.width; i++)
	{
		for (int j = roi.y; j < roi.y + roi.height; j++)
		{
			double dis = sqrt(dis2(0, roi.y + roi.height - r - j));
			if (dis > len)
			{
				out.at<uchar>(i, j) = 0;
			}
			else if (dis > len - r)
			{
				out.at<uchar>(i, j) = 255.0 / (r)*(len - dis);
			}
			else
			{
				out.at<uchar>(i, j) = 255;
			}
		}
	}

	roi = Rect(row - r, 0, cvRound(r), cvRound(r));
	ReRoi = out(roi);
	len = min(roi.width, roi.height);
	for (int i = roi.x; i < roi.x + roi.width; i++)
	{
		for (int j = roi.y; j < roi.y + roi.height; j++)
		{
			double dis = sqrt(dis2(roi.x + roi.width - r - i, roi.y + roi.height - j));
			if (dis > len)
			{
				out.at<uchar>(i, j) = 0;
			}
			else if (dis > len - r)
			{
				out.at<uchar>(i, j) = 255.0 / (r)*(len - dis);
			}
			else
			{
				out.at<uchar>(i, j) = 255;
			}
		}
	}

	roi = Rect(row - r, r, r, col - r * 2);
	len = min(roi.width, roi.height);
	for (int i = roi.x; i < roi.x + roi.width; i++)
	{
		for (int j = roi.y; j < roi.y + roi.height; j++)
		{
			double dis = sqrt(dis2(roi.x + roi.width - r - i, 0));
			if (dis > len)
			{
				out.at<uchar>(i, j) = 0;
			}
			else if (dis > len - r)
			{
				out.at<uchar>(i, j) = 255.0 / (r)*(len - dis);
			}
			else
			{
				out.at<uchar>(i, j) = 255;
			}
		}
	}

	roi = Rect(row - r, col - r, r, r);
	len = min(roi.width, roi.height);
	for (int i = roi.x; i < roi.x + roi.width; i++)
	{
		for (int j = roi.y; j < roi.y + roi.height; j++)
		{
			double dis = sqrt(dis2(roi.x + roi.width - r - i, roi.y + roi.height - r - j));
			if (dis > len)
			{
				out.at<uchar>(i, j) = 0;
			}
			else if (dis > len - r)
			{
				out.at<uchar>(i, j) = 255.0 / (r)*(len - dis);
			}
			else
			{
				out.at<uchar>(i, j) = 255;
			}
		}
	}
	return out;
}
#endif