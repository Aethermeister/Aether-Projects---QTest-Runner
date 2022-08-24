#pragma once
#include "TestRunConfigurationWidget.h"
#include "../aether_qtest_parser/TestReport.h"

#include <QtWidgets/QTabWidget>

class TestResultTabWidget : public QTabWidget
{
	Q_OBJECT

public:
	explicit TestResultTabWidget(const TestRunConfigurationData& test_run_configuration_data, const TestRunProcessData& test_run_process_data, const TestReport& test_report, QWidget *parent = nullptr);
	virtual ~TestResultTabWidget() = default;

private:
	TestRunConfigurationData m_test_run_configuration_data;
	TestRunProcessData m_test_run_process_data;
	TestReport m_test_report;

	void InitializeUi();
};
