#pragma once
#include "../aether_qtest_parser/TestReport.h"
#include "TestRunConfigurationWidget.h"

#include <QtWidgets/QWidget>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>

#include "ui_OverviewWidget.h"

class OverviewWidget : public QWidget
{
	Q_OBJECT

public:
	explicit OverviewWidget(const TestReport& test_report, const TestRunProcessData& test_run_process_data, QWidget* parent = nullptr);
	virtual ~OverviewWidget() = default;

private:
	Ui::OverviewWidgetClass ui;

	TestReport m_test_report;
	TestRunProcessData m_test_run_process_data;

	void InitializeUi();
	void CreateTestSuiteStatisticsChart();
	void CreateTestCaseStatisticsChart();

	void CreateChartView(const QString& title, QtCharts::QPieSeries* series, QWidget* parent) const;

private slots:
	void PieSliceHoverStateChanged(QtCharts::QPieSlice* slice, bool state) const;
};
