#pragma once

#include <QtWidgets/QWidget>
#include "ui_TestRunConfigurationWidget.h"

struct TestRunConfigurationData
{
	QString test_executable_path;
	QString test_results_path;
	QString working_directory;

	bool analyze_code_coverage;
	QString code_coverage_configuration_file_path;
};

struct TestRunProcessData
{
	int exit_code;
	QString standard_output;
	QString standard_error;
	qint64 execution_time;
};

class TestRunConfigurationWidget : public QWidget
{
	Q_OBJECT

public:
	explicit TestRunConfigurationWidget(QWidget* parent = nullptr);
	virtual ~TestRunConfigurationWidget() = default;

private:
	Ui::TestRunConfigurationWidgetClass ui;

	void InitializeConnections() const;
	void InitializeUi();
	bool CheckCodeCoverageToolAvailability();

	QString BrowseFile(const QString& caption, const QString& dir, const QString& filter);

private slots:
	void BrowseTestExecutable();
	void BrowseTestResults();
	void BrowseCodeCoverageConfiguration();

	void StartTest();

signals:
	void TestConfigurationDataPrepared(const TestRunConfigurationData& test_configuration_data);
};
