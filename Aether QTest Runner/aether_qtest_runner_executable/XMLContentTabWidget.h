#pragma once
#include "../aether_qtest_parser/TestReport.h"

#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>

class XMLContentTabWidget : public QTabWidget
{
	Q_OBJECT

public:
	explicit XMLContentTabWidget(const TestReport& test_report, QWidget* parent = nullptr);
	virtual ~XMLContentTabWidget() = default;

private:
	TestReport m_test_report;

	void InitializeUi();
	QTextEdit* CreateXMLTextEdit(const QString& content) const;
};
