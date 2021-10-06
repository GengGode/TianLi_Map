#include "QTLC_AvatarArrowObject.h"

#include <QPainter>
#include <QSurfaceFormat>

QTLC_AvatarArrowObject::QTLC_AvatarArrowObject(QWidget *parent)
	: QOpenGLWidget(parent)
{
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setAttribute(Qt::WA_TranslucentBackground, true);
	this->setAttribute(Qt::WA_TransparentForMouseEvents, true);

	QSurfaceFormat format;
	format.setSamples(16);
	this->setFormat(format);

	this->setMinimumSize(48, 48);
	this->setMaximumSize(48, 48);
}

QTLC_AvatarArrowObject::~QTLC_AvatarArrowObject()
{
}
void QTLC_AvatarArrowObject::initializeGL()
{
	initializeOpenGLFunctions();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void QTLC_AvatarArrowObject::paintEvent(QPaintEvent *)
{
	const int MainR = 16;
	const int MainD = 32;
	const int minR = 2;
	const int minD = 4;
	const double x_c = 24;
	const double y_c = 24;
	double a = avatarRotation / 180 * 3.14;

	paint = new QPainter;



	paint->begin(this);
	paint->setRenderHint(QPainter::HighQualityAntialiasing);
	//
	//paint->setCompositionMode(QPainter::CompositionMode_DestinationIn);
	paint->setCompositionMode(QPainter::CompositionMode_DestinationIn);
	//paint->fillRect(this->rect(), Qt::NoBrush);
	paint->fillRect(this->rect(), Qt::transparent);
	paint->setCompositionMode(QPainter::CompositionMode_SourceOver);

	// 基础大圆
	paint->setPen(Qt::NoPen);//设置画笔形式 
	paint->setBrush(QBrush(Qt::white, Qt::SolidPattern));//设置画刷形式 
	paint->drawEllipse(x_c - MainR, y_c - MainR, MainD, MainD);

	if (ObjectList.size() > 0)
	{
		for (int i = 0; i < ObjectList.size(); i++)
		{
			// 目标弧线
			paint->setPen(QPen(QColor(230, 185, 69), 2, Qt::SolidLine));
			int startAngle = 90 * 16;
			int spanAngle = ObjectList[i] * 16;
			QRectF R_C_arc(4.0, 4.0, 40.0, 40.0);
			paint->drawArc(R_C_arc, startAngle, spanAngle);

			// 目标小圆
			double x, y;
			paint->setPen(Qt::NoPen);//设置画笔形式 
			paint->setBrush(QColor(230, 185, 69));//设置画刷形式 
			x = sin(deg2rad(ObjectList[i])) * 20;
			y = cos(deg2rad(ObjectList[i])) * 20;
			QRectF R_C_Avatar(x_c - x - minR, y_c - y - minR, minD, minD);
			paint->drawEllipse(R_C_Avatar);
		}

	}


	// 基础自身朝向小圆
	paint->setPen(Qt::NoPen);//设置画笔形式 
	paint->setBrush(Qt::white);//设置画刷形式 
	QRectF R_C_baseN(x_c - minR, 2, minD, minD);
	paint->drawEllipse(R_C_baseN);

	// 北方小圆
	double x, y;
	paint->setPen(Qt::NoPen);//设置画笔形式 
	paint->setBrush(QColor(57, 255, 255));//设置画刷形式 
	x = sin(a) * 20;
	y = cos(a) * 20;
	QRectF R_C_Avatar(x_c - x - minR, y_c - y - minR, minD, minD);
	paint->drawEllipse(R_C_Avatar);

	//QPainterPath AvatarArrow;

	// 目标箭头
	double x_a, y_a;
	double x_b, y_b;
	x_a = sin(a) * 12;
	y_a = cos(a) * 12;
	x_b = sin((avatarRotation + 90) / 180 * 3.14) * 4;
	y_b = cos((avatarRotation + 90) / 180 * 3.14) * 4;

	QVector<QPointF> AvatarArrowPoints;
	AvatarArrowPoints.append(QPointF(x_c + x_b, y_c + y_b));
	AvatarArrowPoints.append(QPointF(x_c + x_a, y_c + y_a));
	AvatarArrowPoints.append(QPointF(x_c - x_b, y_c - y_b));
	AvatarArrowPoints.append(QPointF(x_c - x_a, y_c - y_a));

	paint->setPen(Qt::NoPen);
	paint->setBrush(Qt::transparent);
	paint->setCompositionMode(QPainter::CompositionMode_DestinationIn);
	paint->drawPolygon(AvatarArrowPoints);
	paint->setCompositionMode(QPainter::CompositionMode_SourceOver);

	paint->end();
}

void QTLC_AvatarArrowObject::setAvatarRotation(double AvatarRotation)
{
	avatarRotation = AvatarRotation;
	update();
}
void QTLC_AvatarArrowObject::setFlagObjectRotation(double ObjectRotation)
{
	ObjectList.clear();
	ObjectList.append(ObjectRotation);
	
	update();
}