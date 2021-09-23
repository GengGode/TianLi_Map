#pragma once

#include <QList>
#pragma region Test
#include <QTimer>
#include <cvAutoTrack.h>
#pragma endregion
#include <QCheckBox>
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

	QGraphicsDropShadowEffect *MainShadow = nullptr;

#ifdef TabButtonEffect
	QGraphicsDropShadowEffect *TabShadow = nullptr;
#endif

	QList<QPushButton*> pushButton_UI_Tab;
	QList<QCheckBox*> checkBox_Page_Switch;

#pragma region Test
	QTimer *t = nullptr;
#pragma endregion

private:
	void CreateWidgetMapS();
	void CreateWidgetMapC();
	void CreateWidgetMapAB();

private:
	void connect_UI_Tab();
	void init_UI_Tab_1();
	void init_UI_Tab_4();

private slots:
	void Exit();

#pragma region Test
	void test();
#pragma endregion

private:
	void TabButtonSwitch();
};
