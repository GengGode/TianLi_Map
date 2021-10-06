#include "TianLi_Map.h"

TianLi_Map::TianLi_Map(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setAttribute(Qt::WA_TranslucentBackground, true);

	MainShadow = new QGraphicsDropShadowEffect;
	MainShadow->setOffset(0, 0);
	MainShadow->setColor(QColor(0, 0, 0, 255));
	MainShadow->setBlurRadius(15);
	ui.label->setGraphicsEffect(MainShadow);

#pragma region Test
	foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
	{
		QSerialPort serial;
		serial.setPort(info);
		if (serial.open(QIODevice::ReadWrite))
		{
			ui.comboBox->addItem(serial.portName());
			serial.close();
		}
	}
	connect(ui.pushButton_2, &QPushButton::clicked, this, &TianLi_Map::test2);
	connect(ui.pushButton_32, &QPushButton::clicked, this, &TianLi_Map::test4);
	connect(ui.pushButton_3, &QPushButton::clicked, this, &TianLi_Map::test5);
	//mainSerial=;
#pragma endregion

#ifdef TabButtonEffect
	TabShadow = new QGraphicsDropShadowEffect;
	TabShadow->setOffset(0, 0);
	TabShadow->setColor(QColor(0, 0, 0, 255));
	TabShadow->setBlurRadius(15);
	ui.pushButton_UI_1->setGraphicsEffect(TabShadow);
#endif

	connect(ui.pushButton_Exit, &QPushButton::clicked, this, &TianLi_Map::Exit);

	connect_UI_Tab();
	init_UI_Tab_1();

#pragma region Test
	t = new QTimer();
	connect(t, &QTimer::timeout, this, &TianLi_Map::test1);
	t->start(1);
#pragma endregion

	CreateWidgetMapS();
	CreateWidgetMapC();
	CreateWidgetMapAB();
}

void TianLi_Map::CreateWidgetMapS()
{
	if (WidgetMapS == nullptr)
	{
		WidgetMapS = new HUD_Map_SquareWindow();
		WidgetMapS->show();
		//****//
		WidgetMapS->move(static_cast<int>((1920 - WidgetMapS->width()) / 2.0), 0);
		WidgetMapS->update();
	}
	else
	{
		WidgetMapS->show();
	}
}
void TianLi_Map::CreateWidgetMapC()
{
	if (WidgetMapC == nullptr)
	{
		WidgetMapC = new HUD_Map_CircularWindow();
		WidgetMapC->show();
		//****//
		WidgetMapS->move(static_cast<int>((1920 - WidgetMapC->width()) / 2.0), 0);
		WidgetMapS->update();
	}
	else
	{
		WidgetMapC->show();
	}
}

void TianLi_Map::CreateWidgetMapAB()
{
	if (WidgetMapAB == nullptr)
	{
		WidgetMapAB = new HUD_Map_AzimuthBarWindow();
		WidgetMapAB->show();
		//****//
		WidgetMapAB->move(static_cast<int>((1920 - WidgetMapAB->width()) / 2.0), 0);
		WidgetMapAB->update();
	}
	else
	{
		WidgetMapAB->show();
	}
}
void TianLi_Map::connect_UI_Tab()
{
	pushButton_UI_Tab.append(ui.pushButton_UI_1);
	pushButton_UI_Tab.append(ui.pushButton_UI_2);
	pushButton_UI_Tab.append(ui.pushButton_UI_3);
	pushButton_UI_Tab.append(ui.pushButton_UI_4);

	for (int i = 0; i < pushButton_UI_Tab.size(); i++)
	{
		connect(pushButton_UI_Tab[i], &QPushButton::clicked, this, &TianLi_Map::TabButtonSwitch);
	}
}

void TianLi_Map::init_UI_Tab_1()
{
	ui.comboBox_P1_Top->clear();
	ui.comboBox_P1_Top->addItem(tr("Str_Area_AllArea"));
	ui.comboBox_P1_Top->addItem(tr("Str_Area_MengDe"));
	ui.comboBox_P1_Top->addItem(tr("Str_Area_LiYue"));
	ui.comboBox_P1_Top->addItem(tr("Str_Area_DaoQi"));

	connect(ui.comboBox_P1_Top, QOverload<int>::of(&QComboBox::currentIndexChanged),
		[=](int index) { ui.stackedWidget_P1_ObjectPage->setCurrentIndex(index); });
}

void TianLi_Map::init_UI_Tab_3()
{

}

void TianLi_Map::init_UI_Tab_4()
{
	checkBox_Page_Switch.clear();
	checkBox_Page_Switch.append(ui.checkBox_W_ABW);
	checkBox_Page_Switch.append(ui.checkBox_W_CW);
	checkBox_Page_Switch.append(ui.checkBox_W_SW);

	for (int i = 0; i < checkBox_Page_Switch.size(); i++)
	{
		connect(checkBox_Page_Switch[i], &QCheckBox::clicked, this, &TianLi_Map::TabButtonSwitch);
	}
}

void TianLi_Map::Exit()
{
	this->showMinimized();
	//close();
}

#pragma region Test
void TianLi_Map::test1()
{
	static bool isc = false;
	if (isc == false)
	{
		isc = true;
		static double a = 0;
		bool res = GetRotation(a);
		char buff[1024] = {'\0'};

		if (res)
		{
			WidgetMapAB->setAvatarRotation(a);
			WidgetMapAB->ShowMe();
		}
		else
		{
			int ec = GetLastErr();
			if (!ui.checkBox->isChecked())
			{
				WidgetMapAB->HideMe();
			}
		}

		res=GetStarJson(buff);
		if (res)
		{
			WidgetMapAB->setMessage(QString(buff));
		}
		isc = false;
	}
}

void TianLi_Map::test2()
{
	mainSerial = new QSerialPort;
	//设置串口名  
	mainSerial->setPortName(ui.comboBox->currentText());
	//打开串口  
	mainSerial->open(QIODevice::ReadWrite);
	//设置波特率  
	mainSerial->setBaudRate(115200);
	//设置数据位数  
	mainSerial->setDataBits(QSerialPort::Data8);
	//设置奇偶校验  
	mainSerial->setParity(QSerialPort::NoParity);
	//设置停止位  
	mainSerial->setStopBits(QSerialPort::OneStop);
	//设置流控制  
	mainSerial->setFlowControl(QSerialPort::NoFlowControl);
	//连接信号槽  
	QObject::connect(mainSerial, &QSerialPort::readyRead, this, &TianLi_Map::test3);

}
void TianLi_Map::test3()
{
	QByteArray buf;
	buf = mainSerial->readAll();
	if (!buf.isEmpty())
	{
		QString str = ui.textEdit->toPlainText();
		str += tr(buf);
		ui.textEdit->clear();
		ui.textEdit->append(str);
	}
	buf.clear();

}

void TianLi_Map::test4()
{
	mainSerial->write(ui.textEdit_2->toPlainText().toLatin1());
}
void TianLi_Map::test5()
{
	test6("M 1 0 10 0");
	test6("M 0 0 0 0");
	test6("K 0 0 4 0");
	test6("K 0 0 0 0");
}
void TianLi_Map::test6(QString str)
{
	mainSerial->write(str.toLatin1());
	QThread::msleep(3000);
	QString str2 = ui.textEdit->toPlainText();
	str2 += tr("OK");
	ui.textEdit->clear();
	ui.textEdit->append(str2);
}
#pragma endregion


void TianLi_Map::TabButtonSwitch()
{
	//切换缺少动效
	QPushButton *btn = qobject_cast<QPushButton*>(sender());

#ifdef TabButtonEffect
	btn->setGraphicsEffect(TabShadow);
#endif

	for (int i = 0; i < pushButton_UI_Tab.size(); i++)
	{
		if (btn == pushButton_UI_Tab[i])
		{
			ui.MainWidget_Page->setCurrentIndex(i);
		}
	}
}
