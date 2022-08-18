#pragma once
#include "QtXMLTestResultParser.h"

#include "aether_qtest_parser_global.h"

class AETHER_QTEST_PARSER_EXPORT QtTestResultParser
{
public:
    QtTestResultParser() = delete;
    ~QtTestResultParser() = delete;

    static TestReport ParseQtTestResultFiles(const QStringList& test_result_files);
};
