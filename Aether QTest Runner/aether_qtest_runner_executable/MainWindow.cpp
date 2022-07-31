#include "MainWindow.h"
#include "TestRunConfigurationWidget.h"

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

void MainWindow::ShowTestRunConfigurationWidget()
{
	auto* test_configuration_widget = new TestRunConfigurationWidget(this);
	test_configuration_widget->show();
}
