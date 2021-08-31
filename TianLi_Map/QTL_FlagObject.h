#pragma once

#include <QString>
#include <QWidget>
#include <QGraphicsOpacityEffect>
#include "ui_QTL_FlagObject.h"

class QTL_FlagObject : public QWidget
{
	Q_OBJECT

public:
	QTL_FlagObject(QWidget *parent = Q_NULLPTR);
	~QTL_FlagObject();

private:
	Ui::QTL_FlagObject ui;

	QGraphicsOpacityEffect *opacityEffect = nullptr;
private:
	double direction = 0;
	double distance = 0;
	double transparent = 0;
public:
	void setIcon(QString urlIcon);
	void setDirection(double dirValue);
	void setDistance(double disValue);
	void setTransparent(double value);
	void setShowText(bool isShow);

private slots:
	void updateText();
	void updateTransparent();
signals:
	void directionChanged();
	void distanceChanged();
	void transparentChanged();
};
