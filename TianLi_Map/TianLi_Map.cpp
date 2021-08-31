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
	connect(t, &QTimer::timeout, this, &TianLi_Map::test);
	t->start(1);
#pragma endregion

	if (WidgetMapAB == nullptr)
	{
		WidgetMapAB = new HUD_Map_AzimuthBarWindow();
		WidgetMapAB->show();
		WidgetMapAB->move(static_cast<int>((1920 - WidgetMapAB->width()) / 2.0),0);
		WidgetMapAB->setTopMost(true);
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
void TianLi_Map::test()
{
	static bool isc = false;
	if (isc == false)
	{
		isc = true;
		static double a = 0;
		bool res = GetRotation(a);
		if (res)
		{
			WidgetMapAB->setAvatarRotation(a);
		}
		isc = false;
	}
}
#pragma endregion


void TianLi_Map::TabButtonSwitch()
{
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
