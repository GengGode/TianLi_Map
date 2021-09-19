#pragma once
#include <iostream>

#include <QWidget>
#include "ui_HUD_Map_AzimuthBarWindow.h"
#include "QTL_FlagObject.h"

#include <QGraphicsOpacityEffect>

class HUD_Map_AzimuthBarWindow : public QWidget
{
	Q_OBJECT

public:
	HUD_Map_AzimuthBarWindow(QWidget *parent = Q_NULLPTR);
	~HUD_Map_AzimuthBarWindow();

private:
	Ui::HUD_Map_AzimuthBarWindow ui;

private:
	QPoint m_Press;
	QPoint m_Move;
	bool leftBtnClk = false;

	bool isShow = true;
	bool isTopMost = true;
	
	double avatarRotationRange = 90;
	double avatarRotation = 0;

	QGraphicsOpacityEffect *opacityEffect = nullptr;

	std::vector<QTL_FlagObject*> Flags_ObjectList;
	std::vector<std::vector<double>> p;
private:
	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void paintEvent(QPaintEvent *);

private:
	void setFlagS_Range(double value);
	void setFlagN_Range(double value);
	void setFlagW_Range(double value);
	void setFlagE_Range(double value);
public slots:
	void setShow(bool IsShow);
	void setTopMost(bool IsTopMost);
	void setAvatarRotation(double AvatarRotation);
	void setMessage(QString message);

	void setFlagObject(int id, double ObjectRotation,double ObjectDistance);

	void setFlagS(double RelativeAngle);
	void setFlagN(double RelativeAngle);
	void setFlagW(double RelativeAngle);
	void setFlagE(double RelativeAngle);

private:
	double arg2arg(double arg) 
	{
		int argInteger = static_cast<int>(arg);
		double argDecimal = arg - argInteger;
		argInteger = argInteger % 360;

		double res = argInteger + argDecimal;
		if (res > 180)res = res - 360;
		if (res < -180)res = res + 360;
		return res;
	}
};
