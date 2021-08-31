#include "HUD_Map_AzimuthBarWindow.h"

HUD_Map_AzimuthBarWindow::HUD_Map_AzimuthBarWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setAttribute(Qt::WA_TranslucentBackground, true);
	this->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	//ui.label_test->hide();

	QTL_FlagObject* newQTL_FlagObject1 = new QTL_FlagObject(this);
	newQTL_FlagObject1->setIcon(":/test/Resource/test/Component 9.png");
	QTL_FlagObject* newQTL_FlagObject2 = new QTL_FlagObject(this);
	newQTL_FlagObject2->setIcon(":/test/Resource/test/Component 9.png");
	QTL_FlagObject* newQTL_FlagObject3 = new QTL_FlagObject(this);
	newQTL_FlagObject3->setIcon(":/test/Resource/test/Component 9.png");

	Flags_ObjectList.push_back(newQTL_FlagObject1);
	Flags_ObjectList.push_back(newQTL_FlagObject2);
	Flags_ObjectList.push_back(newQTL_FlagObject3);

	//
}

HUD_Map_AzimuthBarWindow::~HUD_Map_AzimuthBarWindow()
{
}

void HUD_Map_AzimuthBarWindow::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_Press = event->globalPos();
		leftBtnClk = true;
	}
	event->ignore();
}

void HUD_Map_AzimuthBarWindow::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) 
	{
		leftBtnClk = false;
	}
	event->ignore();
}
void HUD_Map_AzimuthBarWindow::mouseMoveEvent(QMouseEvent *event)
{
	if (leftBtnClk) 
	{
		m_Move = event->globalPos();
		this->move(this->pos() + m_Move - m_Press);
		m_Press = m_Move;
	}
	event->ignore();
	update();
}

void HUD_Map_AzimuthBarWindow::paintEvent(QPaintEvent *)
{
	//ShowWindow((HWND)this->winId(), SW_RESTORE);
	//if()
	static HWND HW_TopMods = HWND_TOP;
	//HWND HW_Now = HWND_TOPMOST;
	bool isChanged = false;
	if (isShow)
	{

	}
	else
	{

	}

	if (isTopMost)
	{
		if (HW_TopMods != HWND_TOPMOST)
		{
			HW_TopMods = HWND_TOPMOST;
			isChanged = true;
		}
	}
	else
	{
		if (HW_TopMods != HWND_NOTOPMOST)
		{
			HW_TopMods = HWND_NOTOPMOST;
			isChanged = true;
		}
	}

	//SetWindowPos((HWND)this->winId(), HW_TopMods, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);

	if (isChanged)
	{
		SetWindowPos((HWND)this->winId(), HW_TopMods, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	}
}

void HUD_Map_AzimuthBarWindow::setFlagN_Range(double value)
{
	int x = static_cast<int>(80 + 378 - ui.label_Flag_N->width() / 2 + ((378 - ui.label_Flag_N->width() / 2) * value));

	int xw = static_cast<int>(80 + 378 - ui.label_Flag_W->width() / 2 + ((378 - ui.label_Flag_W->width() / 2) * (value - 90.0)));
	int xn = static_cast<int>(80 + 378 - ui.label_Flag_N->width() / 2 + ((378 - ui.label_Flag_N->width() / 2) * (value + 90)));
	int xs = static_cast<int>(80 + 378 - ui.label_Flag_S->width() / 2 + ((378 - ui.label_Flag_S->width() / 2) * (value - 180.0)));
	int xe = static_cast<int>(80 + 378 - ui.label_Flag_E->width() / 2 + ((378 - ui.label_Flag_E->width() / 2) * (value + 90.0)));

	if (value >= -1 && value <= 1)
	{
		ui.label_Flag_N->move(x, 10);

		Flags_ObjectList[0]->move(x+30, 10);
		Flags_ObjectList[0]->setShowText(false);
		Flags_ObjectList[0]->setDistance(value*100);
		Flags_ObjectList[0]->setTransparent(value);

		//Flags_ObjectList[1]->move(x-30, 40);
		//Flags_ObjectList[1]->setDistance(value * 80);
		//Flags_ObjectList[1]->setTransparent(value);

		//Flags_ObjectList[2]->move(x+20, 40);
		//Flags_ObjectList[2]->setDistance(value * 80);
		//Flags_ObjectList[2]->setTransparent(value);
		//QPropertyAnimation *animation = new QPropertyAnimation(ui.label_Flag_N, "geometry");
		//animation->setDuration(100);
		//animation->setStartValue(QRect(ui.label_Flag_N->x(), ui.label_Flag_N->y(), ui.label_Flag_N->width(), ui.label_Flag_N->height()));
		//animation->setEndValue(QRect(x,10, ui.label_Flag_N->width(), ui.label_Flag_N->height()));
		//animation->setEasingCurve(QEasingCurve::Linear);
		//animation->start(QAbstractAnimation::DeleteWhenStopped);

		ui.label_Flag_N->show();
	}
	else
	{
		ui.label_Flag_N->hide();
	}
}

void HUD_Map_AzimuthBarWindow::setShow(bool IsShow)
{
	isShow = IsShow;
}

void HUD_Map_AzimuthBarWindow::setTopMost(bool IsTopMost)
{
	isTopMost = IsTopMost;
}

void HUD_Map_AzimuthBarWindow::setAvatarRotation(double AvatarRotation)
{
	avatarRotation = -AvatarRotation;
	setFlagS(180.0-avatarRotation);
	setFlagN(-avatarRotation);
	setFlagW(-90.0-avatarRotation);
	setFlagE(90.0-avatarRotation);
}

void HUD_Map_AzimuthBarWindow::setFlagS(double RelativeAngle)
{
	double value = RelativeAngle / (avatarRotationRange / 2.0);
	setFlagS_Range(value);
}
void HUD_Map_AzimuthBarWindow::setFlagN(double RelativeAngle)
{
	double value = RelativeAngle / (avatarRotationRange / 2.0);
	setFlagN_Range(value);
}
void HUD_Map_AzimuthBarWindow::setFlagW(double RelativeAngle)
{
	double value = RelativeAngle / (avatarRotationRange / 2.0);
	setFlagW_Range(value);
}
void HUD_Map_AzimuthBarWindow::setFlagE(double RelativeAngle)
{
	double value = RelativeAngle / (avatarRotationRange / 2.0);
	setFlagE_Range(value);
}