#include "TestsWidget.h"
#include "ColorDefines.h"
#include "TestSuiteDetailsWidget.h"
#include "TestCaseDetailsWidget.h"

TestsWidget::TestsWidget(const TestReport& test_report, QWidget *parent)
	: QWidget(parent), m_test_report(test_report)
{
	ui.setupUi(this);

	InitializeConnections();
	InitializeUi();
}

void TestsWidget::InitializeUi()
{
	CreateTreeWidgetHeader();
	CreateTreeWidgetItems();
}

void TestsWidget::InitializeConnections() const
{
	connect(ui.m_tests_tree_widget, &QTreeWidget::itemDoubleClicked, this, &TestsWidget::ShowTestDetails);
}

void TestsWidget::CreateTreeWidgetHeader()
{
	const QStringList header_names
	{
		"Name",
		"Duration [ms]",
		"Test case count",
		"Pass rate"
	};

	ui.m_tests_tree_widget->setHeaderLabels(header_names);
	ui.m_tests_tree_widget->header()->setDefaultAlignment(Qt::AlignCenter);
}

void TestsWidget::CreateTreeWidgetItems()
{
	const auto& test_suites = m_test_report.TestSuites();
	for (const auto& test_suite : test_suites)
	{
		CreateTestSuiteTreeItem(test_suite);
	}
}

void TestsWidget::CreateTestSuiteTreeItem(const TestSuite& test_suite)
{
	auto* test_suite_item = new QTreeWidgetItem(ui.m_tests_tree_widget);
	test_suite_item->setText(0, test_suite.Name());
	test_suite_item->setText(1, test_suite.TestSuiteRunDurationMsString());
	test_suite_item->setTextAlignment(1, Qt::AlignCenter);
	test_suite_item->setText(2, QString::number(test_suite.TestCaseCount()));
	test_suite_item->setTextAlignment(2, Qt::AlignCenter);
	test_suite_item->setText(3, QString("%0%").arg(static_cast<double>(test_suite.PassedTestCaseCount()) / static_cast<double>(test_suite.TestCaseCount()) * 100.0));
	test_suite_item->setTextAlignment(3, Qt::AlignCenter);

	//Create a child QTreeWidgetItem for each test case in this test suite
	const auto test_cases = test_suite.TestCases();
	for (const auto& test_case : test_cases)
	{
		CreateTestCaseTreeItem(test_case, test_suite_item);
	}

	//Adjust the coloring of the test suite tree widget item according to the passed rate of the test cases
	auto item_color = QColor(PASSED_TEST_CASE_COLOR);
	if (test_suite.FailedTestCaseCount() > 0)
	{
		item_color.setNamedColor(FAILED_TEST_CASE_COLOR);
	}
	SetTreeWidgetItemColor(test_suite_item, item_color);

	m_test_suites_to_tree_widget_items.insert(test_suite_item, test_suite);
}

void TestsWidget::CreateTestCaseTreeItem(const TestCase& test_case, QTreeWidgetItem* parent_item)
{
	const auto is_test_case_passed = test_case.IsPassed();

	//Create the test case tree widget item and set its data and property
	auto* test_case_item = new QTreeWidgetItem();
	test_case_item->setText(0, test_case.Name());
	test_case_item->setText(1, test_case.DurationMsString());
	test_case_item->setTextAlignment(1, Qt::AlignCenter);
	test_case_item->setText(3, is_test_case_passed ? "Passed" : "Failed");
	test_case_item->setTextAlignment(3, Qt::AlignCenter);

	//Adjust the coloring of the test case tree widget item according to the passed state of the test case
	auto item_color = QColor(FAILED_TEST_CASE_COLOR);
	if (is_test_case_passed)
	{
		item_color.setNamedColor(PASSED_TEST_CASE_COLOR);
	}
	SetTreeWidgetItemColor(test_case_item, item_color);

	parent_item->addChild(test_case_item);

	m_test_cases_to_tree_widget_items.insert(test_case_item, test_case);
}

void TestsWidget::SetTreeWidgetItemColor(QTreeWidgetItem* tree_widget_item, const QColor& color) const
{
	const auto column_count = ui.m_tests_tree_widget->columnCount();
	for (int i = 0; i < column_count; ++i)
	{
		tree_widget_item->setBackground(i, color);
		tree_widget_item->setForeground(i, Qt::white);
	}
}

void TestsWidget::ShowTestDetails(QTreeWidgetItem* item, int column)
{
	Q_UNUSED(column)

	if (m_test_suites_to_tree_widget_items.contains(item))
	{
		auto* test_suite_details_widget = new TestSuiteDetailsWidget(m_test_suites_to_tree_widget_items.value(item), this);
		test_suite_details_widget->show();
	}
	else if (m_test_cases_to_tree_widget_items.contains(item))
	{
		auto* test_case_details_widget = new TestCaseDetailsWidget(m_test_cases_to_tree_widget_items.value(item), this);
		test_case_details_widget->show();
	}
}
