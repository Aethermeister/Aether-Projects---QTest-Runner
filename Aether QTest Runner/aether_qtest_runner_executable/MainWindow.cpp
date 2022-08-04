#include "MainWindow.h"
#include "TestExecutionProgressDialog.h"

#include <QtCore/QDebug>
#include <QtCore/QProcess>

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	InitializeConnections();
}

void MainWindow::InitializeConnections() const
{
	connect(ui.m_exit_action, &QAction::triggered, this, &MainWindow::close);
	connect(ui.m_run_test_action, &QAction::triggered, this, &MainWindow::ShowTestRunConfigurationWidget);
}

void MainWindow::ProcessTestResults(const TestRunConfigurationData& test_run_configuration_data, const TestRunProcessData& test_run_process_data)
{
}

void MainWindow::ShowTestRunConfigurationWidget()
{
	auto* test_configuration_widget = new TestRunConfigurationWidget(this);
	connect(test_configuration_widget, &TestRunConfigurationWidget::TestConfigurationDataPrepared, this, &MainWindow::TestRunConfigured);

	test_configuration_widget->show();
}

void MainWindow::TestRunConfigured(const TestRunConfigurationData& test_run_configuration_data)
{
	auto* test_run_process = new QProcess();
	test_run_process->setWorkingDirectory(test_run_configuration_data.working_directory);
	test_run_process->setProgram(test_run_configuration_data.test_executable_path);

	auto* prog_diag = new TestExecutionProgressDialog("Tests are running\nThis could take several minutes, please wait", test_run_process, this);

	connect(test_run_process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), [=](int exit_code, QProcess::ExitStatus exit_status) {
		Q_UNUSED(exit_status)

		if (prog_diag->IsCancelled())
		{
			ui.statusBar->showMessage("Test run cancelled");
		}
		else
		{
			TestRunProcessData test_run_process_data;
			test_run_process_data.exit_code = exit_code;
			test_run_process_data.standard_output = test_run_process->readAllStandardOutput();
			test_run_process_data.standard_error = test_run_process->readAllStandardError();

			ProcessTestResults(test_run_configuration_data, test_run_process_data);
		}

		prog_diag->close();
		test_run_process->deleteLater();
		});

	connect(test_run_process, &QProcess::destroyed, [] {
		qDebug() << "Ended";
		});

	qDebug() << "Starting test";
	test_run_process->start();
	prog_diag->exec();
}