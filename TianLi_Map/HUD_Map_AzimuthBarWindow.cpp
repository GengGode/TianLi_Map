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
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Popup | Qt::Tool);
	this->setAttribute(Qt::WA_TranslucentBackground, true);
	this->setAttribute(Qt::WA_TransparentForMouseEvents, true);

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

	//指南针窗口控件
	Arrow_AvatarObject = new QTLC_AvatarArrowObject(nullptr);
	Arrow_AvatarObject->show();
	//Arrow_AvatarObject->move(this->x() + 316, this->y() + 90);

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

		// 指南针窗口随动
		Arrow_AvatarObject->move(this->x() + 316, this->y() + 90);

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
		// 窗口随动 + 窗口刷新置顶状态
		Arrow_AvatarObject->move(this->x() + 316, this->y() + 96);
		SetWindowPos((HWND)this->winId(), HW_TopMods, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
		SetWindowPos((HWND)Arrow_AvatarObject->winId(), HW_TopMods, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	}
}

// 方向标签移动
void HUD_Map_AzimuthBarWindow::setFlagS_Range(double value)
{
	int x = static_cast<int>(this->width() / 2 - ui.label_Flag_E->width() / 2 + ((630 / 2 - ui.label_Flag_S->width() / 2) * value));

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

// 方向标签移动
void HUD_Map_AzimuthBarWindow::setFlagN_Range(double value)
{
	int x = static_cast<int>(this->width() / 2 - ui.label_Flag_E->width() / 2 + ((630 / 2 - ui.label_Flag_W->width() / 2) * value));

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
// 方向标签移动
void HUD_Map_AzimuthBarWindow::setFlagW_Range(double value)
{
	int x = static_cast<int>(this->width() / 2 - ui.label_Flag_E->width() / 2 + ((630 / 2 - ui.label_Flag_W->width() / 2) * value));

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

// 方向标签移动
void HUD_Map_AzimuthBarWindow::setFlagE_Range(double value)
{
	int x = arg2range(value) - ui.label_Flag_E->width() / 2;

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

// 角度标点移动
void HUD_Map_AzimuthBarWindow::setFlagStar_Range(double value)
{
	QLabel* thisLabel = ui.label_Flag_Star_A;
	int x = arg2range(value) - thisLabel->width() / 2;
	value=range2range(value);

	moveFlag(ui.label_Flag_Star_A, value + 2.0 / 3.0);
	moveFlag(ui.label_Flag_Star_B, value + 4.0/3.0);
	moveFlag(ui.label_Flag_Star_C, value + 6.0/3.0);
}

// 联动显示
void HUD_Map_AzimuthBarWindow::ShowMe()
{
	this->show();
	Arrow_AvatarObject->show();
}

//联动隐藏
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

//角度数据分发
void HUD_Map_AzimuthBarWindow::setAvatarRotation(double AvatarRotation)
{
	avatarRotation = -AvatarRotation;

	setFlagS(180.0-avatarRotation);
	setFlagN(-avatarRotation);
	setFlagW(-90.0-avatarRotation);
	setFlagE(90.0 - avatarRotation);

	setFlagStar(-avatarRotation);

	//角度传递至指南针
	Arrow_AvatarObject->setAvatarRotation(avatarRotation);
	//update();
}

//从json数据中读取神瞳坐标等信息
void HUD_Map_AzimuthBarWindow::setMessage(QString message)
{
	QJsonDocument jsD = QJsonDocument::fromJson(message.toLocal8Bit().data());
	QJsonObject js = jsD.object();
	int num=0;
	double dis = 0;
	double arg = 0;
	const double rad2degScale = 180 / 3.1415926535;

	//神瞳数量
	num=js["n"].toInt();

	if (num > 0)
	{
		QJsonArray listArray = js["list"].toArray();

		for (int i = 0; i < num; i++)
		{
			//神瞳坐标
			double x = listArray[i].toArray()[0].toDouble();
			double y = listArray[i].toArray()[1].toDouble();
			dis = sqrt(x * x + y * y);

			arg = atan2(-y, x)*rad2degScale;

			arg = arg - 90; //从屏幕空间左侧水平线为0度转到竖直向上为0度
			if (arg < -180.0)arg = arg + 360;

			setFlagObject(i, arg, dis);
			ui.Flag_Image->hide();
			ui.Flag_Message->setText(" ");
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

			int x = static_cast<int>(this->width() / 2 - ui.label_Flag_E->width() / 2 + ((630 / 2 - Flags_ObjectList[id]->width() / 2) * value));

			if (value >= -1 && value <= 1)
			{
				Flags_ObjectList[id]->show();
				Flags_ObjectList[id]->move(x, 5);
				Flags_ObjectList[id]->setShowText(true);
				Flags_ObjectList[id]->setDistance(ObjectDistance);
				Flags_ObjectList[id]->setTransparent(value - 0.2);
			}
			else
			{
				Flags_ObjectList[id]->hide();
				//Flags_ObjectList[id]->setShowText(false);
				//Flags_ObjectList[id]->setTransparent(0);
			}

		}

	}
	else
	{

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
	double value = arg2arg(RelativeAngle) / (avatarRotationRange / 2.0);
	setFlagW_Range(value);
}
void HUD_Map_AzimuthBarWindow::setFlagE(double RelativeAngle)
{
	double value = arg2arg(RelativeAngle) / (avatarRotationRange / 2.0);
	setFlagE_Range(value);
}

void HUD_Map_AzimuthBarWindow::setFlagStar(double RelativeAngle)
{
	double value = arg2arg(RelativeAngle) / (avatarRotationRange / 2.0);
	setFlagStar_Range(value);
}
