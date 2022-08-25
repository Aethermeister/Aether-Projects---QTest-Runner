#include "QtXMLTestResultParser.h"

#include <QtCore/QFile>
#include <QtCore/QDateTime>
#include <QtCore/QDebug>

QtXMLTestResultParser::QtXMLTestResultParser(const QStringList& files)
{
	ParseQtXMLTestResults(files);
}

const TestReport& QtXMLTestResultParser::ParsedTestReport() const
{
	return m_test_report;
}

void QtXMLTestResultParser::ParseQtXMLTestResults(const QStringList& files)
{
	for (const auto& file : files)
	{
		ParseQtXMLTestResult(file);
	}
}

void QtXMLTestResultParser::ParseQtXMLTestResult(const QString& file)
{
	//Open the given test result document and check for errors
	QFile test_result_file(file);
	if (!test_result_file.open(QIODevice::ReadOnly))
	{
		XMLError xml_file_error(file);
		xml_file_error.SetErrorMessage(QString("Test result file could not be opened: %0").arg(test_result_file.errorString()));
		m_test_report.AddError(xml_file_error);

		return;
	}

	//Read the test result file content and try to convert it to xml format
	//Set the XMLError object if an error occurs
	QDomDocument qt_xml_test_result_document("QtTestResultDocument");
	XMLError xml_parser_error(file);
	const auto test_result_xml_content = test_result_file.readAll();

	if (TryToCreateDomXMLDocument(test_result_xml_content, qt_xml_test_result_document, xml_parser_error))
	{
		//Get the root element of the xml document and check wheter it is an appropriate Qt generated test result
		const auto qt_xml_document_element = qt_xml_test_result_document.documentElement();
		if (qt_xml_document_element.tagName() != "TestCase")
		{
			XMLError xml_test_case_error(file);
			xml_test_case_error.SetErrorMessage("Test result file does not contain appropriate xml tags");
			m_test_report.AddError(xml_test_case_error);

			return;
		}

		//Set the title of the Test Report
		//The general title contains the timestamp of the parsing
		m_test_report.SetTitle("Test_Report_" + QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss"));

		//Get the Test Suite related information from the xml document
		const auto qt_test_suite_name = qt_xml_document_element.attribute("name");

		//Create a Test Suite object for this xml document and extract the environment/configuration and test case data from the xml document
		TestSuite test_suite(qt_test_suite_name);
		test_suite.SetRawXMLContent(test_result_xml_content);

		ExtractEnvironmentData(qt_xml_test_result_document, test_suite);
		ExtractTestFunctionData(qt_xml_test_result_document, test_suite);

		m_test_report.AddTestSuite(test_suite);
	}
	else
	{
		m_test_report.AddError(xml_parser_error);
	}
}

bool QtXMLTestResultParser::TryToCreateDomXMLDocument(const QString& file_content, QDomDocument& xml_document, XMLError& xml_error) const
{
	QString error_message;
	int error_line;
	int error_column;

	//Set the content of the given QDomDocument and check for errors
	auto xml_ok = xml_document.setContent(file_content, &error_message, &error_line, &error_column);

	if (!xml_ok && error_message == "unexpected end of file") //unexpected end of file
	{
		const auto corrected_file_content = file_content +
			"<Incident type=\"fail\" file=\"?\" line=\"?\">\n" +
			"<Description><![CDATA[Fatal error occured. Please check the log and stack trace]]></Description>\n" +
			"</Incident>\n" +
			"<Duration msecs=\"0\"/>\n" +
			"</TestFunction>\n" +
			"<Duration msecs=\"0\"/>\n" +
			"</TestCase>";

		xml_ok = xml_document.setContent(corrected_file_content, &error_message, &error_line, &error_column);
	}

	if (!xml_ok)
	{
		xml_error.SetErrorMessage(error_message);
		xml_error.SetErrorLine(error_line);
		xml_error.SetErrorColumn(error_column);
	}

	return xml_ok;
}

void QtXMLTestResultParser::ExtractEnvironmentData(const QDomDocument& xml_document, TestSuite& test_suit) const
{
	try
	{
		//Get the environment data of the test result and store it in the test suite object
		const auto environment_child_nodes = xml_document.elementsByTagName("Environment").at(0).childNodes();

		for (int i = 0; i < environment_child_nodes.count(); ++i)
		{
			const auto environment_child_node = environment_child_nodes.at(i).toElement();
			test_suit.AddConfiguration(environment_child_node.tagName(), environment_child_node.text());
		}
	}
	catch (const std::exception& ex)
	{
		//TODO: log and set error
		qDebug() << ex.what();
	}
}

void QtXMLTestResultParser::ExtractTestFunctionData(const QDomDocument& xml_document, TestSuite& test_suit) const
{
	try
	{
		double test_suite_duration = 0.0;
		//Get every TestFunction node and process their data to create the appropriate test case objects
		const auto test_function_nodes = xml_document.elementsByTagName("TestFunction");
		for (int i = 0; i < test_function_nodes.count(); ++i)
		{
			//Create a test case object for each Qt TestFunction
			const auto test_case_name = test_function_nodes.at(i).toElement().attribute("name");
			TestCase test_case(test_case_name, test_suit.Name());

			//Get the child nodes of the TestFunction node and process their content
			const auto test_function_child_nodes = test_function_nodes.at(i).childNodes();
			for (int k = 0; k < test_function_child_nodes.count(); ++k)
			{
				const auto test_function_child_node = test_function_child_nodes.at(k).toElement();
				ExtractTestFunctionContentData(test_function_child_node, test_case);
			}

			test_suite_duration += test_case.DurationMs();
			test_suit.AddTestCase(test_case);
		}
		test_suit.SetDurationMs(QString::number(test_suite_duration));
	}
	catch (const std::exception& ex)
	{
		//log and set error
		qDebug() << ex.what();
	}
}

void QtXMLTestResultParser::ExtractTestFunctionContentData(const QDomElement& xml_element, TestCase& test_case) const
{
	//Check the type of the given xml element and store them in the given test case object

	if (xml_element.tagName() == "Message")
	{
		//If the actual xml element is a Message node get the message and the corresponding information
		const auto message_type = xml_element.attribute("type");
		const auto message_file = xml_element.attribute("file");
		const auto message_line = xml_element.attribute("line");

		const auto message_description = xml_element.elementsByTagName("Description").at(0).toElement();
		const auto message_description_text = message_description.text();

		test_case.AddMessage(TestCaseMessage(message_type, message_description_text, message_file, message_line));
	}
	else if (xml_element.tagName() == "Incident")
	{
		//If the actual xml element is an Incident node than check whether it is a passed or failed test
		//If the test failed get additional information
		const auto incident_type = xml_element.attribute("type");
		if (incident_type != "pass")
		{
			const auto incident_file = xml_element.attribute("file");
			const auto incident_line = xml_element.attribute("line");

			const auto incident_description = xml_element.elementsByTagName("Description").at(0).toElement();
			const auto incident_description_text = incident_description.text();

			test_case.SetIncident(TestCaseMessage(incident_type, incident_description_text, incident_file, incident_line));
		}
	}
	else if (xml_element.tagName() == "Duration")
	{
		//If the actual xml element is a Duration node store the duration of the test
		const auto duration_msecs = xml_element.attribute("msecs");
		test_case.SetDurationMs(duration_msecs);
	}
}
