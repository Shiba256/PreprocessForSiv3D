#pragma once

#include"stdafx.h"

namespace pps {
	class MacroProcessor {
	public:
		void replaceMacros(String& line) const;

		void replaceMacroFunctions(String& line) const;

		inline void defineMacro(const String& name, const String& value) {
			definedMacros.emplace(name, value);
		}

		inline void defineMacro(StringView name, StringView value) {
			definedMacros.emplace(name, value);
		}

		inline void undefMacro(StringView name) {
			if (definedMacroFunctions.contains(name)) {
				definedMacroFunctions.erase(name);
			}
			if (definedMacros.contains(name)) {
				definedMacros.erase(name);
			}
		}

		inline void defineMacroFunction(const String& name, const String& body) {
			definedMacroFunctions.emplace(name, body);
		}

		inline bool isDefined(const String& name) const {
			return definedMacros.contains(name) || definedMacroFunctions.contains(name);
		}

		inline bool isDefined(StringView name) const {
			return definedMacros.contains(name) || definedMacroFunctions.contains(name);
		}

		inline void clear() {
			definedMacros.clear();
			definedMacroFunctions.clear();
		}

	private:
		HashTable<String, String> definedMacros;
		HashTable<String, String> definedMacroFunctions;
	};
}
