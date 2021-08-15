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
	t->start(300);
#pragma endregion

	if (WidgetMapAB == nullptr)
	{
		WidgetMapAB = new HUD_Map_AzimuthBarWindow();
		WidgetMapAB->show();
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

void TianLi_Map::Exit()
{
	this->showMinimized();
	//close();
}

#pragma region Test
void TianLi_Map::test()
{
	static int b = 0;
	WidgetMapAB->setAvatarRotation(b);
	b = b + 10;
	if (b > 50)
	{
		b = -50;
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
