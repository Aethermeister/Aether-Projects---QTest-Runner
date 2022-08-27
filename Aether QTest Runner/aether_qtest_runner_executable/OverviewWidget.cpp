#include "OverviewWidget.h"
#include "ColorDefines.h"

#include <QtWidgets/QGraphicsLayout>

OverviewWidget::OverviewWidget(const TestReport& test_report, const TestRunProcessData& test_run_process_data, QWidget* parent)
	: QWidget(parent), m_test_report(test_report), m_test_run_process_data(test_run_process_data)
{
	ui.setupUi(this);

	InitializeUi();
}

void OverviewWidget::InitializeUi()
{
	ui.m_title_lbl->setText(m_test_report.Title());

	const QString state_text = "<b><span style=\"color: %0;\">%1</span></b>";
	if (m_test_report.IsPassed())
	{
		ui.m_test_state_lbl->setText(state_text.arg(PASSED_TEST_CASE_COLOR).arg("All tests passed"));
	}
	else
	{
		ui.m_test_state_lbl->setText(state_text.arg(FAILED_TEST_CASE_COLOR).arg("One or more tests failed"));
	}

	ui.m_test_suites_and_cases_lbl->setText(QString("<b>%0</b> test cases were executed in <b>%1</b> test suite(s)").arg(m_test_report.TestCaseCount()).arg(m_test_report.TestSuiteCount()));
	ui.m_duration_lbl->setText(QString("The tests run for a total of <b>%0 ms</b>").arg(m_test_run_process_data.execution_time));
	ui.m_exit_code_lbl->setText(QString("The test executable exited with <b>%0</b>").arg(m_test_run_process_data.exit_code));

	CreateTestSuiteStatisticsChart();
	CreateTestCaseStatisticsChart();
}

void OverviewWidget::CreateTestSuiteStatisticsChart()
{
	auto* test_suite_series = new QtCharts::QPieSeries();
	test_suite_series->setHoleSize(0.25);
	connect(test_suite_series, &QtCharts::QPieSeries::hovered, this, &OverviewWidget::PieSliceHoverStateChanged);

	const auto passed_count = m_test_report.PassedTestSuiteCount();
	const auto passed_percentage = m_test_report.PassedTestSuitePercentage();
	auto* passed_test_suite_pie_slice = test_suite_series->append(QString("%0 (%1%) test suite passed").arg(passed_count).arg(passed_percentage), passed_count);
	passed_test_suite_pie_slice->setColor(QColor(PASSED_TEST_CASE_COLOR));

	const auto failed_count = m_test_report.FailedTestSuiteCount();
	const auto failed_percentage = m_test_report.FailedTestSuitePercentage();
	auto* failed_test_suite_pie_slice = test_suite_series->append(QString("%0 (%1%) test suite failed").arg(failed_count).arg(failed_percentage), failed_count);
	failed_test_suite_pie_slice->setColor(QColor(FAILED_TEST_CASE_COLOR));

	CreateChartView("Test suite statistics", test_suite_series, ui.m_test_suite_chart_container_widget);
}

void OverviewWidget::CreateTestCaseStatisticsChart()
{
	auto* test_case_series = new QtCharts::QPieSeries();
	test_case_series->setHoleSize(0.25);
	connect(test_case_series, &QtCharts::QPieSeries::hovered, this, &OverviewWidget::PieSliceHoverStateChanged);

	const auto passed_count = m_test_report.PassedTestCaseCount();
	const auto passed_percentage = m_test_report.PassedTestCasePercentage();
	auto* passed_test_case_pie_slice = test_case_series->append(QString("%0 (%1%) test case passed").arg(passed_count).arg(passed_percentage), passed_count);
	passed_test_case_pie_slice->setColor(QColor(PASSED_TEST_CASE_COLOR));

	const auto failed_count = m_test_report.FailedTestCaseCount();
	const auto failed_percentage = m_test_report.FailedTestCasePercentage();
	auto* failed_test_case_pie_slice = test_case_series->append(QString("%0 (%1%) test case failed").arg(failed_count).arg(failed_percentage), failed_count);
	failed_test_case_pie_slice->setColor(QColor(FAILED_TEST_CASE_COLOR));

	CreateChartView("Test case statistics", test_case_series, ui.m_test_case_chart_container_widget);
}

void OverviewWidget::CreateChartView(const QString& title, QtCharts::QPieSeries* series, QWidget* parent) const
{
	auto* chart_view = new QtCharts::QChartView(parent);
	chart_view->setRenderHint(QPainter::Antialiasing);
	chart_view->chart()->setAnimationOptions(QtCharts::QChart::AnimationOption::SeriesAnimations);
	chart_view->chart()->layout()->setContentsMargins(0, 0, 0, 0);
	chart_view->chart()->setBackgroundRoundness(0);
	chart_view->chart()->addSeries(series);
	chart_view->chart()->legend()->setVisible(false);

	auto title_font = chart_view->chart()->titleFont();
	title_font.setPointSizeF(10);
	title_font.setBold(true);
	chart_view->chart()->setTitleFont(title_font);
	chart_view->chart()->setTitle(title);

	parent->layout()->addWidget(chart_view);
}

void OverviewWidget::PieSliceHoverStateChanged(QtCharts::QPieSlice* slice, bool state) const
{
	slice->setExploded(state);
	slice->setLabelVisible(state);
}
