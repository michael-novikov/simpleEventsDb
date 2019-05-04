#ifndef CONDITION_PARSER_H
#define CONDITION_PARSER_H

#include "node.h"

#include <memory>
#include <iostream>

std::shared_ptr<Node> ParseCondition(std::istream& is);

void TestParseCondition();

#endif // CONDITION_PARSER_H
