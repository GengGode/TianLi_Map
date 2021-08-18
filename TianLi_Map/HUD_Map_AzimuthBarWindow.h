#pragma once
#include <iostream>
#include <Windows.h>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QWidget>
#include "ui_HUD_Map_AzimuthBarWindow.h"
#include "QTL_FlagObject.h"


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

	std::vector<QTL_FlagObject*> Flags_ObjectList;
	std::vector<std::vector<double>> p;
private:
	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void paintEvent(QPaintEvent *);

private:
	void setFlagN_Range(double value);
public slots:
	void setShow(bool IsShow);
	void setTopMost(bool IsTopMost);
	void setAvatarRotation(double AvatarRotation);
	void setFlagN(double RelativeAngle);
};
