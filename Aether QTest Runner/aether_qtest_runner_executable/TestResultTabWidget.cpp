#include "TestResultTabWidget.h"
#include "OverviewWidget.h"
#include "TestsWidget.h"
#include "StackTraceWidget.h"
#include "XMLContentTabWidget.h"
#include "CodeCoverageResultWidget.h"

TestResultTabWidget::TestResultTabWidget(const TestRunConfigurationData& test_run_configuration_data, const TestRunProcessData& test_run_process_data, const TestReport& test_report, QWidget* parent)
	: QTabWidget(parent), m_test_run_configuration_data(test_run_configuration_data), m_test_run_process_data(test_run_process_data), m_test_report(test_report)
{
	InitializeUi();
}

void TestResultTabWidget::InitializeUi()
{
	auto* overview_widget = new OverviewWidget(m_test_report, m_test_run_process_data, this);
	addTab(overview_widget, "Overview");

	auto* tests_widget = new TestsWidget(m_test_report, this);
	addTab(tests_widget, "Tests");

	auto* stack_trace_widget = new StackTraceWidget(m_test_run_process_data, this);
	addTab(stack_trace_widget, "Stack trace");

	auto* xml_content_tab_widget = new XMLContentTabWidget(m_test_report, this);
	addTab(xml_content_tab_widget, "XML");

	auto* code_coverage_result_widget = new CodeCoverageResultWidget(m_test_run_configuration_data, this);
	addTab(code_coverage_result_widget, "Code coverage");
}
