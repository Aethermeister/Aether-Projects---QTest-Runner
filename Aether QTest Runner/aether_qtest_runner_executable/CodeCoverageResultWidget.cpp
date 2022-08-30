#include "CodeCoverageResultWidget.h"

#include <QtCore/QFileInfo>
#include <QtCore/QUrl>
#include <QtGui/QDesktopServices>
#include <QtWidgets/QGridLayout>

CodeCoverageResultWidget::CodeCoverageResultWidget(const TestRunConfigurationData& test_run_configuration_data, QWidget* parent)
	: QWidget(parent), m_test_run_configuration_data(test_run_configuration_data)
{
	InitializeUi();
}

void CodeCoverageResultWidget::InitializeUi()
{
	auto* grid_layout = new QGridLayout(this);
	setLayout(grid_layout);

	auto* code_coverage_information_lbl = new QLabel(this);
	code_coverage_information_lbl->setAlignment(Qt::AlignCenter);
	grid_layout->addWidget(code_coverage_information_lbl);

	const QString code_coverage_index_file_path(m_test_run_configuration_data.test_results_path + "/CodeCoverageResults/index.html");
	if (!QFileInfo::exists(code_coverage_index_file_path))
	{
		code_coverage_information_lbl->setText("<b>Code coverage file is not available</b>");
		return;
	}

	code_coverage_information_lbl->setTextInteractionFlags(Qt::TextBrowserInteraction);
	code_coverage_information_lbl->setOpenExternalLinks(true);
	code_coverage_information_lbl->setText(QString("<b><a href=\"file:///%0\">Code coverage is available. Click here to open it in the default browser</a></b>").arg(code_coverage_index_file_path));
}
