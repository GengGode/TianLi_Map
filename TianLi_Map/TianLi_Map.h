#pragma once

#include <QGraphicsDropShadowEffect>
#include <QtWidgets/QWidget>
#include "ui_TianLi_Map.h"

class TianLi_Map : public QWidget
{
    Q_OBJECT

public:
    TianLi_Map(QWidget *parent = Q_NULLPTR);

private:
    Ui::TianLi_MapClass ui;

private slots:
	void Exit();
};
