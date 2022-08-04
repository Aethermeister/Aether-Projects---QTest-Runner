#pragma once


#include <QtCore/QProcess>
#include <QtWidgets/QDialog>
#include "ui_TestExecutionProgressDialog.h"

class TestExecutionProgressDialog : public QDialog
{
	Q_OBJECT

public:
	explicit TestExecutionProgressDialog(const QString& information_text, QProcess* test_execution_process, QWidget *parent = nullptr);
	virtual ~TestExecutionProgressDialog() = default;

	bool IsCancelled() const;

private:
	Ui::TestExecutionProgressDialogClass ui;

	QProcess* m_test_execution_process;
	bool m_is_cancelled = false;

private slots:
	void CancelTestExecution();
};
