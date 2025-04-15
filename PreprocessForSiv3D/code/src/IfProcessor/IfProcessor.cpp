#include"IfProcessor.h"

#include"../MacroProcessor/MacroProcessor.h"

namespace pps {
	IfProcessor::IfProcessor() :
		reg_if{ UR"(#\s*if\s+(.+))" },
		reg_ifdef{ UR"(#\s*ifdef\s+([a-zA-Z_][a-zA-Z_1-9]*))" },
		reg_ifndef{ UR"(#\s*ifndef\s+([a-zA-Z_][a-zA-Z_1-9]*))" },
		reg_else{ UR"(#\s*else)" },
		reg_elif{ UR"(#\s*elif\s+(.+))" },
		reg_endif{ UR"(#\s*endif)" }
	{
	}

	void IfProcessor::process(const String& line, const String& line_before, const MacroProcessor& macroProcessor) {
		// #if
		if (const auto _if = reg_if.match(line)) {
			if_directive = true;
			if (_if.size() != 2)return;
			skip = not static_cast<bool>(Eval(_if[1].value()));
			if (not skip) {
				is_parent_true = true;
			}
		}
		// #ifdef
		else if (const auto ifdef = reg_ifdef.match(line_before)) {
			if (ifdef.size() != 2)return;
			if_directive = true;
			if (not macroProcessor.isDefined(ifdef[1].value())) {
				skip = true;
			}
			else {
				is_parent_true = true;
			}
		}
		// #ifndef
		else if (const auto ifndef = reg_ifndef.match(line_before)) {
			if (ifndef.size() != 2)return;
			if_directive = true;
			if (macroProcessor.isDefined(ifndef[1].value())) {
				skip = true;
			}
			else {
				is_parent_true = true;
			}
		}
		// #else
		else if (const auto _else = reg_else.match(line)) {
			if (if_directive && not is_parent_true) {
				skip = !(skip);
			}
		}
		// #endif
		else if (const auto endif = reg_endif.match(line)) {
			if_directive = false;
			skip = false;
			is_parent_true = false;
		}
		// #elif
		else if (const auto elif = reg_elif.match(line)) {
			if (not is_parent_true) {
				if (if_directive) {
					if (elif.size() != 2)return;
					skip = not static_cast<bool>(Eval(elif[1].value()));
				}
			}
			else {
				skip = true;
			}
		}
	}
}
