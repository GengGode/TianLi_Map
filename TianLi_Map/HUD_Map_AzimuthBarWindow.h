#pragma once

#include <Windows.h>
#include <QMouseEvent>
#include <QWidget>
#include "ui_HUD_Map_AzimuthBarWindow.h"

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

private:
	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void paintEvent(QPaintEvent *);
};
