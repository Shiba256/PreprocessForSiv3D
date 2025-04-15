#include"MacroProcessor.h"

#include"Utils.h"

namespace pps {
	void MacroProcessor::replaceMacros(String& line) const {
		for (const auto& def : definedMacros) {
			if (!def.second.isEmpty()) {
				utils::ReplaceVariable(line, def.first, def.second);
			}
		}
	}

	void MacroProcessor::replaceMacroFunctions(String& line) const {
		for (const auto& def : definedMacroFunctions) {
			size_t index = line.indexOf(def.first.substrView(0, def.first.indexOf(U"(")));
			if (index == String::npos) continue;

			int32_t parenthesisCount = 0;
			size_t functionEndPos = 0;
			for (const auto& c : line.substr(index + def.first.size())) {
				functionEndPos++;
				if (c == U')') parenthesisCount--;
				else if (c == U'(') parenthesisCount++;
				if (parenthesisCount == 0) break;
			}

			auto functionDefinition = line.substr(index, def.first.size() + functionEndPos);
			auto vars = functionDefinition.substr(
				functionDefinition.indexOf(U"(") + 1,
				functionDefinition.lastIndexOf(U")") - functionDefinition.indexOf(U"(") - 1
			).split(U',');

			String funcBody = def.second;
			for (const auto& [i, var] : Indexed(vars)) {
				utils::ReplaceVariable(funcBody, U"{" + Format(i) + U"}", var);
			}

			line = line.substr(0, index) + funcBody + line.substr(index + functionDefinition.size());
		}
	}
}
