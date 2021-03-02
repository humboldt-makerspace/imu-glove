#include "io/Parser.hpp"
#include "system/Interface.hpp"

int Parser::parseValue (String cmd)
{
	int begin = -1;
	int end = -1;
	for (unsigned int i = 0; i < cmd.length(); i++) {
		if (!isDigit(cmd.charAt(i))) {
			if (begin == -1) continue;
			else {
				end = i;
				break;
			}
		}
		else {
			if (begin == -1) begin = i;
			if (i == cmd.length() - 1) end = i + 1;
		}
	}
	if (begin == -1) return -1;
	return (cmd.substring(begin, end)).toInt();
}
