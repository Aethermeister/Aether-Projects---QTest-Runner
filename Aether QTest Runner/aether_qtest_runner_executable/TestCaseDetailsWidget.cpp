#include "TestCaseDetailsWidget.h"
#include "ColorDefines.h"

#include <QtCore/QFileInfo>

TestCaseDetailsWidget::TestCaseDetailsWidget(const TestCase& test_case, QWidget* parent)
	: QWidget(parent), m_test_case(test_case)
{
	ui.setupUi(this);

	InitializeUi();
}

void TestCaseDetailsWidget::InitializeUi()
{
	setAttribute(Qt::WA_DeleteOnClose);
	setWindowFlags(Qt::Tool);

	ui.m_test_case_name_lbl->setText(m_test_case.Name());
	ui.m_test_suite_name_lbl->setText(m_test_case.TestSuiteName());
	ui.m_duration_lbl->setText(m_test_case.DurationMsString() + " ms");

	QString state_text = "<b><span style=\"color: %0;\">%1</span></b>";
	QString incident_message = "-";

	if (m_test_case.IsPassed())
	{
		ui.m_state_lbl->setText(state_text.arg(PASSED_TEST_CASE_COLOR).arg("Passed"));
	}
	else
	{
		ui.m_state_lbl->setText(state_text.arg(FAILED_TEST_CASE_COLOR).arg("Failed"));

		const QFileInfo source_file_info(m_test_case.Incident().SourceFile());
		incident_message = m_test_case.Incident().Message() + '\n' +
			"File: " + source_file_info.fileName() + '\n' +
			"Line: " + m_test_case.Incident().SourceLine();
	}

	ui.m_incident_message_lbl->setText(incident_message);

	for (const auto& message : m_test_case.Messages())
	{
		ui.m_test_message_list_widget->addItem(message.Message());
	}
}
