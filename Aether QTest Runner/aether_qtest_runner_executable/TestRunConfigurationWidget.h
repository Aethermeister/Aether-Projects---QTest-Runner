#pragma once

#include <QWidget>
#include "ui_TestRunConfigurationWidget.h"

class TestRunConfigurationWidget : public QWidget
{
	Q_OBJECT

public:
	explicit TestRunConfigurationWidget(QWidget *parent = nullptr);
	virtual ~TestRunConfigurationWidget() = default;

private:
	Ui::TestRunConfigurationWidgetClass ui;

	void InitializeConnections() const;
	void InitializeUi();

	QString BrowseFile(const QString& caption, const QString& dir, const QString& filter);

private slots:
	void BrowseTestExecutable();
	void BrowseTestResults();
};
