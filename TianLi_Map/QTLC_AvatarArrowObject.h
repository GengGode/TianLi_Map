#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class QTLC_AvatarArrowObject : public QOpenGLWidget,protected QOpenGLFunctions
{
	Q_OBJECT

public:
	QTLC_AvatarArrowObject(QWidget *parent);
	~QTLC_AvatarArrowObject();

private:
	//QPainter *paint;
private:
	void initializeGL();
	void paintEvent(QPaintEvent *);

private:
	double avatarRotation = 0;
	QVector<double> ObjectList;
public slots:
	void setAvatarRotation(double AvatarRotation);
	void setFlagObjectRotation(double ObjectRotation);

private:
	double deg2rad(double deg)
	{
		return deg / 180.0 * 3.1415926535;
	}
	double rad2deg(double rad)
	{
		return rad / 3.1415926535 * 180.0;
	}
};
