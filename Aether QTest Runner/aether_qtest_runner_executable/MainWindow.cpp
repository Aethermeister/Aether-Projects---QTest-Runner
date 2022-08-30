#include "MainWindow.h"
#include "TestExecutionProgressDialog.h"
#include "TestResultTabWidget.h"

#include <QtCore/QElapsedTimer>
#include <QtCore/QProcess>
#include <QtCore/QDir>

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

TestReport MainWindow::CreateTestReport(const TestRunConfigurationData& test_run_configuration_data) const
{
	QStringList test_result_files;
	const auto test_result_file_infos = QDir(test_run_configuration_data.test_results_path).entryInfoList({ "*.xml" }, QDir::Filter::Files);
	for (const auto& file_info : test_result_file_infos)
	{
		test_result_files.append(file_info.absoluteFilePath());
	}

	return QtTestResultParser::ParseQtTestResultFiles(test_result_files);
}

void MainWindow::ShowTestResults(const TestRunConfigurationData& test_run_configuration_data, const TestRunProcessData& test_run_process_data, const TestReport& test_report)
{
	ClearPreviousContent();

	auto* test_result_tab_widget = new TestResultTabWidget(test_run_configuration_data, test_run_process_data, test_report, ui.m_central_widget);
	ui.m_central_widget_layout->addWidget(test_result_tab_widget);
}

void MainWindow::ClearPreviousContent()
{
	auto* previous_content_widget = ui.m_central_widget->findChild<QWidget*>();

	if (previous_content_widget)
	{
		ui.m_central_widget_layout->removeWidget(previous_content_widget);
		previous_content_widget->deleteLater();
	}
}

void MainWindow::ShowTestRunConfigurationWidget()
{
	auto* test_configuration_widget = new TestRunConfigurationWidget(this);
	connect(test_configuration_widget, &TestRunConfigurationWidget::TestConfigurationDataPrepared, this, &MainWindow::TestRunConfigured);

	test_configuration_widget->show();
}

void MainWindow::TestRunConfigured(const TestRunConfigurationData& test_run_configuration_data)
{
	auto* sender_widget = qobject_cast<QWidget*>(sender());

	auto* test_run_process_timer = new QElapsedTimer();
	auto* test_run_process = new QProcess(this);
	test_run_process->setWorkingDirectory(test_run_configuration_data.working_directory);

	if (test_run_configuration_data.analyze_code_coverage)
	{
		const auto code_coverage_export_arg = QString("--export_type=html:%0\\%1").arg(test_run_configuration_data.test_results_path).arg("CodeCoverageResults");

		QStringList test_process_args = { "-v", code_coverage_export_arg, "--", test_run_configuration_data.test_executable_path };

		QString code_coverage_configuration_arg;
		if (!test_run_configuration_data.code_coverage_configuration_file_path.isEmpty())
		{
			test_process_args.insert(1, QString("--config_file=%0").arg(test_run_configuration_data.code_coverage_configuration_file_path));
		}

		test_run_process->setProgram("OpenCppCoverage");
		test_run_process->setArguments(test_process_args);
	}
	else
	{
		test_run_process->setProgram(test_run_configuration_data.test_executable_path);
	}

	auto* prog_diag = new TestExecutionProgressDialog("Tests are running\nThis could take several minutes, please wait...", test_run_process, this);

	connect(test_run_process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), [=](int exit_code, QProcess::ExitStatus exit_status) {
		Q_UNUSED(exit_status)

			if (prog_diag->IsCancelled())
			{
				ui.statusBar->showMessage("Test run cancelled");
				sender_widget->setVisible(true);
			}
			else
			{
				sender_widget->close();

				TestRunProcessData test_run_process_data;
				test_run_process_data.exit_code = exit_code;
				test_run_process_data.standard_output = test_run_process->readAllStandardOutput();
				test_run_process_data.standard_error = test_run_process->readAllStandardError();
				test_run_process_data.execution_time = test_run_process_timer->elapsed();

				const auto test_report = CreateTestReport(test_run_configuration_data);
				ShowTestResults(test_run_configuration_data, test_run_process_data, test_report);
			}

		delete test_run_process_timer;

		prog_diag->close();
		test_run_process->deleteLater();
		raise();
		});

	test_run_process->start();
	test_run_process_timer->start();
	prog_diag->exec();
}