#ifndef CONDITION_PARSER_H
#define CONDITION_PARSER_H

#include <memory>
#include <iostream>
#include "../include/node.h"

std::shared_ptr<Node> ParseCondition(std::istream& is);

void TestParseCondition();

#endif // CONDITION_PARSER_H
