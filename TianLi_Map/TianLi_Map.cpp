#include "TianLi_Map.h"

TianLi_Map::TianLi_Map(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setAttribute(Qt::WA_TranslucentBackground, true);

	QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
	shadow->setOffset(0, 0);
	shadow->setColor(QColor(0, 0, 0, 255));
	shadow->setBlurRadius(15);
	ui.label->setGraphicsEffect(shadow);


	connect(ui.pushButton_Exit, &QPushButton::clicked, this, &TianLi_Map::Exit);
}

void TianLi_Map::Exit()
{
	close();
}
