#pragma once
#include "../aether_qtest_parser/TestReport.h"

#include <QtWidgets/QWidget>
#include "ui_TestsWidget.h"

class TestsWidget : public QWidget
{
	Q_OBJECT

public:
	explicit TestsWidget(const TestReport& test_report, QWidget *parent = nullptr);
	virtual ~TestsWidget() = default;

private:
	Ui::TestsWidgetClass ui;

	TestReport m_test_report;
	QMap<QTreeWidgetItem*, TestSuite> m_test_suites_to_tree_widget_items;
	QMap<QTreeWidgetItem*, TestCase> m_test_cases_to_tree_widget_items;

	void InitializeUi();
	void InitializeConnections() const;

	void CreateTreeWidgetHeader();
	void CreateTreeWidgetItems();
	void CreateTestSuiteTreeItem(const TestSuite& test_suite);
	void CreateTestCaseTreeItem(const TestCase& test_case, QTreeWidgetItem* parent_item);

	void SetTreeWidgetItemColor(QTreeWidgetItem* tree_widget_item, const QColor& color) const;

private:
	void ShowTestDetails(QTreeWidgetItem* item, int column);
};
