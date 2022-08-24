#include "TestResultTabWidget.h"
#include "TestsWidget.h"

TestResultTabWidget::TestResultTabWidget(const TestRunConfigurationData& test_run_configuration_data, const TestRunProcessData& test_run_process_data, const TestReport& test_report, QWidget *parent)
	: QTabWidget(parent), m_test_run_configuration_data(test_run_configuration_data), m_test_run_process_data(test_run_process_data), m_test_report(test_report)
{
	InitializeUi();
}

void TestResultTabWidget::InitializeUi()
{
	auto* tests_widget = new TestsWidget(m_test_report, this);
	addTab(tests_widget, "Tests");
}
