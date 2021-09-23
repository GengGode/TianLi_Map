#pragma once

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

private:
	void paintEvent(QPaintEvent *);
};

typedef HUD_Map_CircularWindow HUD_Map_CW;
