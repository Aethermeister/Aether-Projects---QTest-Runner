#include "TestExecutionProgressDialog.h"

TestExecutionProgressDialog::TestExecutionProgressDialog(const QString& information_text, QProcess* test_execution_process, QWidget *parent)
	: QDialog(parent), m_test_execution_process(test_execution_process)
{
	ui.setupUi(this);

	setAttribute(Qt::WA_DeleteOnClose);
	ui.m_progress_information_lbl->setText(information_text);
	connect(ui.m_cancel_btn, &QPushButton::clicked, this, &TestExecutionProgressDialog::CancelTestExecution);
}

void TestExecutionProgressDialog::CancelTestExecution()
{
	ui.m_progress_information_lbl->setText("Cancelling test run...");

	m_test_execution_process->kill();
	m_is_cancelled = true;
}

bool TestExecutionProgressDialog::IsCancelled() const
{
	return m_is_cancelled;
}
