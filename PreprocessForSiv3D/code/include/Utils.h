#pragma once

#include"stdafx.h"

namespace pps {
	namespace utils {
		// + - * / % ^ ~ | & < > ( ) , ; = かどうか判別します 
		static constexpr bool IsOperator(char32 ch) noexcept {
			constexpr const char32 operators[] = { U"+-*/%^~|&<>(),;=" };
			for (size_t i = 0; i < 16ull; ++i) {
				if (operators[i] == ch) {
					return true;
				}
			}
			return false;
		}

		/// @brief line 中の変数を指定された文字列に置き換えます。line: HelloWorld, var: Hello の場合は置換されず line: Hello World, var: Hello のように区切り文字が入る場合に置換されます
		/// @param line 置換したい文字列 
		/// @param var 置換したい変数
		/// @param replace 置換したい値
		static void ReplaceVariable(String& line, const String& targetVar, const String& replacement) {
			size_t start_pos = 0ull;
			while (start_pos != String::npos || start_pos >= line.size()) {
				size_t index = line.indexOf(targetVar.trimmed(), start_pos);
				if (line.indexOf(U'\"', start_pos)  < index && index < line.indexOf(U'\"', line.indexOf(U'\"', start_pos) + 1ull)) {
					index = line.indexOf(U'\"', line.indexOf(U'\"', start_pos) + 1ull);
				}
				if (index == String::npos)break;
				if (index + targetVar.trimmed().size() >= line.size())break;
				const char32_t ch = line[index + targetVar.trimmed().size()];
				if (IsBlank(ch) || IsOperator(ch)) {
					line =
						line.substr(0, index) +
						line.substr(index, targetVar.trimmed().size()).replace(targetVar.trimmed(), replacement.trimmed()) +
						line.substr(index + targetVar.trimmed().size());
				}
				start_pos = index + replacement.size() - 1ull;
			}
		}
	}
}
