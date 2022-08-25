#include "StackTraceWidget.h"

#include <QtWidgets/QTextEdit>

StackTraceWidget::StackTraceWidget(const TestRunProcessData& test_run_process_data, QWidget* parent)
	: QWidget(parent), m_test_run_process_data(test_run_process_data)
{
	ui.setupUi(this);

	InitializeUi();
}

void StackTraceWidget::InitializeUi()
{
	if (m_test_run_process_data.standard_output.isEmpty() && m_test_run_process_data.standard_error.isEmpty())
	{
		auto* information_label = new QLabel("No available stack trace or output information", this);
		ui.m_widget_layout->addWidget(information_label);
	}
	else
	{
		auto* output_text_edit = new QTextEdit(this);
		output_text_edit->setReadOnly(true);
		output_text_edit->setFrameShape(QFrame::Shape::NoFrame);
		output_text_edit->setFrameShadow(QFrame::Shadow::Plain);
		output_text_edit->setLineWidth(0);

		ui.m_widget_layout->addWidget(output_text_edit);

		const auto output_information =
			"Standard output: \n\n" + m_test_run_process_data.standard_output + "\n\n\n" +
			"Standard error: \n\n" + m_test_run_process_data.standard_error;
		output_text_edit->setText(output_information);
	}
}
