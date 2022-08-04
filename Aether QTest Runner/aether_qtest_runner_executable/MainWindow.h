#pragma once
#include "TestRunConfigurationWidget.h"

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = nullptr);
	virtual ~MainWindow() = default;

private:
	Ui::MainWindowClass ui;

	void InitializeConnections() const;
	void ProcessTestResults(const TestRunConfigurationData& test_run_configuration_data, const TestRunProcessData& test_run_process_data);

private slots:
	void ShowTestRunConfigurationWidget();
	void TestRunConfigured(const TestRunConfigurationData& test_run_configuration_data);
};
