#pragma once
#include "../aether_qtest_parser/TestCase.h"

#include <QtWidgets/QWidget>
#include "ui_TestCaseDetailsWidget.h"

class TestCaseDetailsWidget : public QWidget
{
	Q_OBJECT

public:
	explicit TestCaseDetailsWidget(const TestCase& test_case, QWidget* parent = nullptr);
	virtual ~TestCaseDetailsWidget() = default;

private:
	Ui::TestCaseDetailsWidgetClass ui;

	TestCase m_test_case;

	void InitializeUi();
};
