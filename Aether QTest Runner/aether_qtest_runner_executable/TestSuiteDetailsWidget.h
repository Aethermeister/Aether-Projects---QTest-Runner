#pragma once
#include "../aether_qtest_parser/TestSuite.h"

#include <QtWidgets/QWidget>
#include "ui_TestSuiteDetailsWidget.h"

class TestSuiteDetailsWidget : public QWidget
{
	Q_OBJECT

public:
	explicit TestSuiteDetailsWidget(const TestSuite& test_suite, QWidget* parent = nullptr);
	virtual ~TestSuiteDetailsWidget() = default;

private:
	Ui::TestSuiteDetailsWidgetClass ui;

	TestSuite m_test_suite;

	void InitializeUi();
};
