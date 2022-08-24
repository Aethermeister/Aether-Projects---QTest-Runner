#include "TestSuiteDetailsWidget.h"
#include "ColorDefines.h"

TestSuiteDetailsWidget::TestSuiteDetailsWidget(const TestSuite& test_suite, QWidget* parent)
	: QWidget(parent), m_test_suite(test_suite)
{
	ui.setupUi(this);

	InitializeUi();
}

void TestSuiteDetailsWidget::InitializeUi()
{
	setAttribute(Qt::WA_DeleteOnClose);
	setWindowFlags(Qt::Tool);

	ui.m_test_suite_name_lbl->setText(m_test_suite.Name());

	QString test_case_count_text = "%0 (<span style=\"color: %1;\">%2 passed</span> and <span style=\"color: %3;\">%4 failed</span>)";
	ui.m_test_case_count_lbl->setText(test_case_count_text
		.arg(m_test_suite.TestCaseCount())
		.arg(PASSED_TEST_CASE_COLOR).arg(m_test_suite.PassedTestCaseCount())
		.arg(FAILED_TEST_CASE_COLOR).arg(m_test_suite.FailedTestCaseCount()));

	ui.m_duration_lbl->setText(m_test_suite.TestSuiteRunDurationMsString() + " ms");
	ui.m_pass_rate_lbl->setText(QString("%0%").arg(static_cast<double>(m_test_suite.PassedTestCaseCount()) / static_cast<double>(m_test_suite.TestCaseCount()) * 100.0));

	QString configuration_text;
	for (auto it = m_test_suite.Configurations().begin(); it != m_test_suite.Configurations().end(); ++it)
	{
		configuration_text += QString("%0: %1\n").arg(it.key()).arg(it.value());
	}
	ui.m_configuration_lbl->setText(configuration_text);
}
