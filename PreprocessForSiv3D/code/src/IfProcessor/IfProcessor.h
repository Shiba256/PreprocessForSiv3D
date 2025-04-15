#pragma once

#include"stdafx.h"


namespace pps {
	class MacroProcessor;

	class IfProcessor {
	public:
		IfProcessor();

		void process(const String& line, const String& line_before, const MacroProcessor& macroProcessor);

		inline constexpr bool needSkip() const {
			return skip;
		}

	private:
		RegExp reg_if;
		RegExp reg_ifdef;
		RegExp reg_ifndef;
		RegExp reg_else;
		RegExp reg_elif;
		RegExp reg_endif;

		bool skip = false;
		bool is_parent_true = false;
		bool if_directive = false;
	};
}
