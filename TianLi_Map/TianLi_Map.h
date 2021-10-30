#pragma once

#define NON_PORT

#include <QList>
#pragma region Test
#include <QThread>
#include <QTimer>
#include <cvAutoTrack.h>
#pragma endregion
#include <QCheckBox>
#include <QPushButton>
#include <QSerialPort>
#include <QSerialPortInfo>
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


#pragma region Test
	QTimer *ComSendTimer;
	QSerialPort *mainSerial=nullptr;
#pragma endregion

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
	void init_UI_Tab_3();
	void init_UI_Tab_4();

private slots:
	void Exit();

#pragma region Test
	void test1();
	void test2();
	void test3();
	void test4();
	void test5();
	void test6(QString str);
	void test7();
#pragma endregion

private:
	void TabButtonSwitch();
};
