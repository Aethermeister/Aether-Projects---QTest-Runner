#include "TestRunConfigurationWidget.h"

#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>

TestRunConfigurationWidget::TestRunConfigurationWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	InitializeUi();
	InitializeConnections();
}

void TestRunConfigurationWidget::InitializeConnections() const
{
	connect(ui.m_browse_test_executable_btn, &QPushButton::clicked, this, &TestRunConfigurationWidget::BrowseTestExecutable);
	connect(ui.m_browse_test_results_btn, &QPushButton::clicked, this, &TestRunConfigurationWidget::BrowseTestResults);

	connect(ui.m_analyze_code_coverage_check_box, &QCheckBox::toggled, ui.m_code_coverage_configuration_widget, &QWidget::setVisible);

	connect(ui.m_run_test_btn, &QPushButton::clicked, this, &TestRunConfigurationWidget::StartTest);
}

void TestRunConfigurationWidget::InitializeUi()
{
	setAttribute(Qt::WA_DeleteOnClose);
	setWindowFlags(Qt::Tool);
	setWindowModality(Qt::WindowModality::WindowModal);

	ui.m_code_coverage_configuration_widget->setVisible(false);
}

QString TestRunConfigurationWidget::BrowseFile(const QString& caption, const QString& dir, const QString& filter)
{
	if (const auto selected_file = QFileDialog::getOpenFileName(this, caption, dir, filter); !selected_file.isEmpty())
	{
		return selected_file;
	}

	return dir;
}

void TestRunConfigurationWidget::BrowseTestExecutable()
{
	const auto current_path_to_executable = ui.m_path_to_test_executable_line_edit->text();
	const auto selected_file = BrowseFile("Select test executable file", current_path_to_executable, "Qt test executable (*exe)");
	ui.m_path_to_test_executable_line_edit->setText(selected_file);
}

void TestRunConfigurationWidget::BrowseTestResults()
{
	const auto current_path_to_test_results = ui.m_path_to_test_results_line_edit->text();
	const auto selected_folder = QFileDialog::getExistingDirectory(this, "Select test results directory", current_path_to_test_results);
	if (!selected_folder.isEmpty())
	{
		ui.m_path_to_test_results_line_edit->setText(selected_folder);
	}
}

void TestRunConfigurationWidget::StartTest()
{
	const auto test_executable_path = ui.m_path_to_test_executable_line_edit->text();
	const auto test_executable_info = QFileInfo(test_executable_path);

	if (!test_executable_info.exists())
	{
		QMessageBox::critical(this, "Test configuration error", "Selected test executable does not exist");
		return;
	}

	const auto test_results_path = ui.m_path_to_test_results_line_edit->text();

	if (const auto test_results_dir = QDir(test_results_path); !test_results_dir.exists())
	{
		const auto test_results_dir_creation = test_results_dir.mkpath(test_results_path);
		if (!test_results_dir_creation)
		{
			QMessageBox::critical(this, "Test configuration error", "Selected test results folder does not exist and it could not be created");
			return;
		}
	}

	TestRunConfigurationData test_run_configuration_data;
	test_run_configuration_data.test_executable_path = test_executable_path;
	test_run_configuration_data.test_results_path = test_results_path;
	test_run_configuration_data.working_directory = test_executable_info.absolutePath();

	setVisible(false);
	emit TestConfigurationDataPrepared(test_run_configuration_data);
}
