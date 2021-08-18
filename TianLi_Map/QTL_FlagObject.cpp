#include "QTL_FlagObject.h"

QTL_FlagObject::QTL_FlagObject(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setGeometry(QRect(this->x(), 38 , 64, 89));
	
	connect(this, &QTL_FlagObject::distanceChanged, this, &QTL_FlagObject::updateText);
	connect(this, &QTL_FlagObject::transparentChanged, this, &QTL_FlagObject::updateTransparent);
	
	opacityEffect = new QGraphicsOpacityEffect;
	this->setGraphicsEffect(opacityEffect);
}

QTL_FlagObject::~QTL_FlagObject()
{
}

void QTL_FlagObject::setIcon(QString urlIcon)
{
	ui.label_Icon->setPixmap(urlIcon);
}

void QTL_FlagObject::setDirection(double dirValue)
{
	direction = dirValue;
	emit directionChanged();
}

void QTL_FlagObject::setDistance(double disValue)
{
	distance = disValue;
	emit distanceChanged();
}

void QTL_FlagObject::updateText()
{
	ui.label_Text->setText(QString::number(static_cast<int>(abs(distance)))+"m");
}

void QTL_FlagObject::updateTransparent()
{
	
	opacityEffect->setOpacity(1 - abs(transparent));

}

void QTL_FlagObject::setTransparent(double value)
{
	if (transparent <= 0)
	{
		transparent = 0;
	}
	if (transparent >= 1)
	{
		transparent = 1;
	}
	transparent = value;
	emit transparentChanged();
}
