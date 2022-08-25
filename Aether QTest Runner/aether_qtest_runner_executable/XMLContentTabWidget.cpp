#include "XMLContentTabWidget.h"

XMLContentTabWidget::XMLContentTabWidget(const TestReport& test_report, QWidget* parent)
	: QTabWidget(parent), m_test_report(test_report)
{
	InitializeUi();
}

void XMLContentTabWidget::InitializeUi()
{
	setDocumentMode(true);

	QString combined_xml_content;

	for (const auto& test_suite : m_test_report.TestSuites())
	{
		const auto& xml_content = test_suite.RawXMLContent();

		addTab(CreateXMLTextEdit(xml_content), test_suite.Name());
		combined_xml_content += xml_content + "\n\n";
	}

	insertTab(0, CreateXMLTextEdit(combined_xml_content), "All");
	setCurrentIndex(0);
}

QTextEdit* XMLContentTabWidget::CreateXMLTextEdit(const QString& content) const
{
	auto* xml_content_text_edit = new QTextEdit();
	xml_content_text_edit->setText(content);
	xml_content_text_edit->setReadOnly(true);
	xml_content_text_edit->setFrameShape(QFrame::Shape::NoFrame);
	xml_content_text_edit->setFrameShadow(QFrame::Shadow::Plain);
	xml_content_text_edit->setLineWidth(0);

	return xml_content_text_edit;
}
