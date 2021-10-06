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

	// ������Բ
	paint->setPen(Qt::NoPen);//���û�����ʽ 
	paint->setBrush(QBrush(Qt::white, Qt::SolidPattern));//���û�ˢ��ʽ 
	paint->drawEllipse(x_c - MainR, y_c - MainR, MainD, MainD);

	if (ObjectList.size() > 0)
	{
		for (int i = 0; i < ObjectList.size(); i++)
		{
			// Ŀ�껡��
			paint->setPen(QPen(QColor(230, 185, 69), 2, Qt::SolidLine));
			int startAngle = 90 * 16;
			int spanAngle = ObjectList[i] * 16;
			QRectF R_C_arc(4.0, 4.0, 40.0, 40.0);
			paint->drawArc(R_C_arc, startAngle, spanAngle);

			// Ŀ��СԲ
			double x, y;
			paint->setPen(Qt::NoPen);//���û�����ʽ 
			paint->setBrush(QColor(230, 185, 69));//���û�ˢ��ʽ 
			x = sin(deg2rad(ObjectList[i])) * 20;
			y = cos(deg2rad(ObjectList[i])) * 20;
			QRectF R_C_Avatar(x_c - x - minR, y_c - y - minR, minD, minD);
			paint->drawEllipse(R_C_Avatar);
		}

	}


	// ����������СԲ
	paint->setPen(Qt::NoPen);//���û�����ʽ 
	paint->setBrush(Qt::white);//���û�ˢ��ʽ 
	QRectF R_C_baseN(x_c - minR, 2, minD, minD);
	paint->drawEllipse(R_C_baseN);

	// ����СԲ
	double x, y;
	paint->setPen(Qt::NoPen);//���û�����ʽ 
	paint->setBrush(QColor(57, 255, 255));//���û�ˢ��ʽ 
	x = sin(a) * 20;
	y = cos(a) * 20;
	QRectF R_C_Avatar(x_c - x - minR, y_c - y - minR, minD, minD);
	paint->drawEllipse(R_C_Avatar);

	//QPainterPath AvatarArrow;

	// Ŀ���ͷ
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