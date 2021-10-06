#include "HUD_Map_AzimuthBarWindow.h"

#include <Windows.h>
#include <QString>
#include <QPainter>
#include <QJsonArray>
#include <QJsonObject>
#include <QMouseEvent>
#include <QJsonDocument>
#include <QPropertyAnimation>

HUD_Map_AzimuthBarWindow::HUD_Map_AzimuthBarWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setAttribute(Qt::WA_TranslucentBackground, true);
	this->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	this->setWindowFlags(Qt::FramelessWindowHint);
	
	opacityEffect = new QGraphicsOpacityEffect;

	opacityEffect->setOpacity(50);
	ui.widget->setGraphicsEffect(opacityEffect);

	//ui.label_test->hide();:/test/Resource/test/ObjectList1.png

	QTL_FlagObject* newQTL_FlagObject1 = new QTL_FlagObject(this);
	newQTL_FlagObject1->setIcon(":/test/Resource/test/ObjectList2.png");
	QTL_FlagObject* newQTL_FlagObject2 = new QTL_FlagObject(this);
	newQTL_FlagObject2->setIcon(":/test/Resource/test/ObjectList2.png");
	QTL_FlagObject* newQTL_FlagObject3 = new QTL_FlagObject(this);
	newQTL_FlagObject3->setIcon(":/test/Resource/test/ObjectList2.png");

	Flags_ObjectList.push_back(newQTL_FlagObject1);
	Flags_ObjectList.push_back(newQTL_FlagObject2);
	Flags_ObjectList.push_back(newQTL_FlagObject3);

	Arrow_AvatarObject = new QTLC_AvatarArrowObject(this);
	Arrow_AvatarObject->move(this->x() + 316, this->y() + 90);

	//Arrow_AvatarObject->show();
#ifdef _DEBUG
	//test = new QGraphicsDropShadowEffect;
	//test->setOffset(0, 0);
	//test->setColor(QColor(0, 0, 0, 255));
	//test->setBlurRadius(15);
	//ui.label_Flag_N->setGraphicsEffect(test);
#endif

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

		//Arrow_AvatarObject->move(this->x() + 316, this->y() + 90);

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
		//Arrow_AvatarObject->move(this->x() + 316, this->y() + 96);
		SetWindowPos((HWND)this->winId(), HW_TopMods, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
		SetWindowPos((HWND)Arrow_AvatarObject->winId(), HW_TopMods, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	}
}

void HUD_Map_AzimuthBarWindow::setFlagS_Range(double value)
{
	int x = static_cast<int>(this->width() / 2 - ui.label_Flag_E->width() / 2 + ((this->width() / 2 - ui.label_Flag_S->width() / 2) * value));

	if (value >= -1 && value <= 1)
	{
		ui.label_Flag_S->move(x, ui.label_Flag_S->y());
		ui.label_Flag_S->show();
	}
	else
	{
		ui.label_Flag_S->hide();
	}
}

void HUD_Map_AzimuthBarWindow::setFlagN_Range(double value)
{
	int x = static_cast<int>(this->width() / 2 - ui.label_Flag_E->width() / 2 + ((this->width() / 2 - ui.label_Flag_W->width() / 2) * value));

	if (value >= -1 && value <= 1)
	{
		ui.label_Flag_N->move(x, ui.label_Flag_N->y());


		ui.label_Flag_N->show();
	}
	else
	{
		ui.label_Flag_N->hide();
	}
}
void HUD_Map_AzimuthBarWindow::setFlagW_Range(double value)
{
	int x = static_cast<int>(this->width() / 2 - ui.label_Flag_E->width() / 2 + ((this->width() / 2 - ui.label_Flag_W->width() / 2) * value));

	if (value >= -1 && value <= 1)
	{
		ui.label_Flag_W->move(x, ui.label_Flag_W->y());
		ui.label_Flag_W->show();
	}
	else
	{
		ui.label_Flag_W->hide();
	}
}
void HUD_Map_AzimuthBarWindow::setFlagE_Range(double value)
{
	int x = static_cast<int>(this->width()/2 - ui.label_Flag_E->width() / 2 + ((this->width() / 2 - ui.label_Flag_E->width() / 2) * value));

	if (value >= -1 && value <= 1)
	{
		ui.label_Flag_E->move(x, ui.label_Flag_E->y());
		ui.label_Flag_E->show();
	}
	else
	{
		ui.label_Flag_E->hide();
	}
}
void HUD_Map_AzimuthBarWindow::ShowMe()
{
	this->show();
	Arrow_AvatarObject->show();
}

void HUD_Map_AzimuthBarWindow::HideMe()
{
	this->hide();
	Arrow_AvatarObject->hide();
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
	Arrow_AvatarObject->setAvatarRotation(avatarRotation);
	//update();
}

void HUD_Map_AzimuthBarWindow::setMessage(QString message)
{
	QJsonDocument jsD = QJsonDocument::fromJson(message.toLocal8Bit().data());
	QJsonObject js = jsD.object();
	int num=0;
	double dis = 0;
	double arg = 0;
	const double rad2degScale = 180 / 3.1415926535;
	//获取神瞳数量
	if (js.contains("n"))
	{
		QJsonValue numValue= js.take("n");
		if (numValue.isDouble())
		{
			//神瞳数量
			num = numValue.toVariant().toInt();
			if (num > 0)
			{
				//获取神瞳坐标数组
				if (js.contains("list"))
				{
					QJsonValue listValue = js.take("list");
					if (listValue.isArray())
					{
						//神瞳坐标数组
						QJsonArray listArray = listValue.toArray();
						for (int i = 0; i < num; i++)
						{
							//获取神瞳坐标
							QJsonValue StarOneValue = listArray[i];
							if (StarOneValue.isArray())
							{
								//神瞳坐标 [double,double]
								QJsonArray StarValue = StarOneValue.toArray();
								QJsonValue xValue = StarValue[0];
								QJsonValue yValue = StarValue[1];


								//listArrayValue[]
								if (xValue.isDouble() && yValue.isDouble())
								{
									//神瞳坐标
									double x = xValue.toDouble();
									double y = yValue.toDouble();
									dis = sqrt(x * x + y * y);

									arg = atan2(-y, x)*rad2degScale;

									arg = arg - 90; //从屏幕空间左侧水平线为0度转到竖直向上为0度
									if (arg < -180.0)arg = arg + 360;

									setFlagObject(i, arg, dis);
									//ui.Flag_Image->show();
									ui.Flag_Image->hide();
									//ui.Flag_Message->setText(QString::number(dis) + " " + QString::number(arg));
									ui.Flag_Message->setText(" ");

								}
							}
						}
					}
				}
			}
			else
			{

				ui.Flag_Image->hide();
				ui.Flag_Message->setText("");
			}
		}
	}
	else
	{
		ui.Flag_Image->hide();
		ui.Flag_Message->setText("");
	}
}

void HUD_Map_AzimuthBarWindow::setFlagObject(int id, double ObjectRotation,  double ObjectDistance)
{
	//如果id位于列表中
	if (id < Flags_ObjectList.size())
	{
		//如果朝向位于角色视角之内
		//if (abs(ObjectRotation - avatarRotation) < (avatarRotationRange/2.0))
		{
			double arg = arg2arg(-avatarRotation-ObjectRotation);
			
			double value = arg / (avatarRotationRange / 2.0);

			Arrow_AvatarObject->setFlagObjectRotation(-arg);

			int x = static_cast<int>(this->width() / 2 - ui.label_Flag_E->width() / 2 + ((this->width() / 2 - Flags_ObjectList[id]->width() / 2) * value));

			if (value >= -1 && value <= 1)
			{
				Flags_ObjectList[id]->move(x, 5);
				Flags_ObjectList[id]->setShowText(true);
				Flags_ObjectList[id]->setDistance(ObjectDistance);
				Flags_ObjectList[id]->setTransparent(value - 0.2);
			}
			else
			{
				Flags_ObjectList[id]->setShowText(true);
				Flags_ObjectList[id]->setTransparent(1.0);
			}

		}

	}
}

void HUD_Map_AzimuthBarWindow::setFlagS(double RelativeAngle)
{
	double value = arg2arg(RelativeAngle) / (avatarRotationRange / 2.0);
	setFlagS_Range(value);
}
void HUD_Map_AzimuthBarWindow::setFlagN(double RelativeAngle)
{
	double value = arg2arg(RelativeAngle) / (avatarRotationRange / 2.0);
	setFlagN_Range(value);
}
void HUD_Map_AzimuthBarWindow::setFlagW(double RelativeAngle)
{
	if (RelativeAngle < -180)
	{
		RelativeAngle = RelativeAngle + 360;
	}
	double value = arg2arg(RelativeAngle) / (avatarRotationRange / 2.0);
	setFlagW_Range(value);
}
void HUD_Map_AzimuthBarWindow::setFlagE(double RelativeAngle)
{
	double value = arg2arg(RelativeAngle) / (avatarRotationRange / 2.0);
	setFlagE_Range(value);
}