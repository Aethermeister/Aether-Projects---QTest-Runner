#pragma once
#include "TestRunConfigurationWidget.h"

#include <QtWidgets/QWidget>
#include "ui_StackTraceWidget.h"

class StackTraceWidget : public QWidget
{
	Q_OBJECT

public:
	explicit StackTraceWidget(const TestRunProcessData& test_run_process_data, QWidget* parent = nullptr);
	virtual ~StackTraceWidget() = default;

private:
	Ui::StackTraceWidgetClass ui;

	TestRunProcessData m_test_run_process_data;

	void InitializeUi();
};
