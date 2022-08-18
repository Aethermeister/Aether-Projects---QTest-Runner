#include "QtTestResultParser.h"

TestReport QtTestResultParser::ParseQtTestResultFiles(const QStringList& test_result_files)
{
	QtXMLTestResultParser parser(test_result_files);
	return parser.ParsedTestReport();
}
