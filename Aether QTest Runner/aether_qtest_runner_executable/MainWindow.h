#pragma once
#include "TestRunConfigurationWidget.h"
#include "../aether_qtest_parser/QtTestResultParser.h"

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
	void InitializeUi();

	TestReport CreateTestReport(const TestRunConfigurationData& test_run_configuration_data) const;
	void ShowTestResults(const TestRunConfigurationData& test_run_configuration_data, const TestRunProcessData& test_run_process_data, const TestReport& test_report);

	void ClearPreviousContent();

private slots:
	void ShowTestRunConfigurationWidget();
	void TestRunConfigured(const TestRunConfigurationData& test_run_configuration_data);

	void ShowAbout();
	void ShowAboutQt() const;
};
