#include "TestRunConfigurationWidget.h"

#include <QtWidgets\QFileDialog>

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
	const auto selected_file = QFileDialog::getOpenFileName(this, caption, dir, filter);
	if (!selected_file.isEmpty())
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