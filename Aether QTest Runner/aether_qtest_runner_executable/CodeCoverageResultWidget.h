#pragma once
#include "TestRunConfigurationWidget.h"

#include <QtWidgets/QWidget>

class CodeCoverageResultWidget : public QWidget
{
	Q_OBJECT

public:
	explicit CodeCoverageResultWidget(const TestRunConfigurationData& test_run_configuration_data, QWidget* parent);
	virtual ~CodeCoverageResultWidget() = default;

private:
	TestRunConfigurationData m_test_run_configuration_data;

	void InitializeUi();
};
