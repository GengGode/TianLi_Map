#pragma once

#include <QList>
#include <QPushButton>
#include <QGraphicsDropShadowEffect>
#include <QtWidgets/QWidget>
#include "ui_TianLi_Map.h"
#include "HUD_Map_SquareWindow.h"
#include "HUD_Map_CircularWindow.h"
#include "HUD_Map_AzimuthBarWindow.h"

class TianLi_Map : public QWidget
{
    Q_OBJECT

public:
    TianLi_Map(QWidget *parent = Q_NULLPTR);

private:
	HUD_Map_SquareWindow *WidgetMapS = nullptr;
	HUD_Map_CircularWindow *WidgetMapC = nullptr;
	HUD_Map_AzimuthBarWindow *WidgetMapAB = nullptr;

private:
    Ui::TianLi_MapClass ui;

	QGraphicsDropShadowEffect *TabShadow;

	QList<QPushButton*> pushButton_UI_Tab;
private:
	void connect_UI_Tab();
	void init_UI_Tab_1();

private slots:
	void Exit();

private:
	void TabButtonSwitch();
};
