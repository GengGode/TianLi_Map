#pragma once

#include <QWidget>
#include "ui_HUD_Map_SquareWindow.h"

class HUD_Map_SquareWindow : public QWidget
{
	Q_OBJECT

public:
	HUD_Map_SquareWindow(QWidget *parent = Q_NULLPTR);
	~HUD_Map_SquareWindow();

private:
	Ui::HUD_Map_SquareWindow ui;

private:
	QImage RenderImage;

private:
	void paintEvent(QPaintEvent*);

public slots:
	void setAvatarPos(double x, double y);
};
