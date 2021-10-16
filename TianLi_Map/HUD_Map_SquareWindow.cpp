#include "HUD_Map_SquareWindow.h"

HUD_Map_SquareWindow::HUD_Map_SquareWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Popup | Qt::Tool);
	this->setAttribute(Qt::WA_TranslucentBackground, true);
	this->setAttribute(Qt::WA_TransparentForMouseEvents, true);
}

HUD_Map_SquareWindow::~HUD_Map_SquareWindow()
{
}
