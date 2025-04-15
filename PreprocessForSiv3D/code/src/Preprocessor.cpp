#include"Preprocessor.h"

#include"MacroProcessor/MacroProcessor.h"
#include"IncludeProcessor/IncludeProcessor.h"
#include"IfProcessor/IfProcessor.h"

#include"Utils.h"

namespace pps {
	struct Preprocessor::Preprocessor_impl {
		Preprocessor_impl() :
			reg_pragma{ UR"(#\s*pragma\s*(.+))" },
			reg_define_defines{ UR"(^(?!.*(\(|\)))#\s*define\s+([^ ]+)$)" },
			reg_define_values{ UR"(#\s*define\s+([^\( | ^\)|^ ]+)\s+(.+))" },
			reg_define_eval{ UR"(#define\s+([a-zA-Z_][a-zA-Z0-9_]*\s*\(.*?\))\s+(.+))" },
			reg_undef{ UR"(^(?!.*(\(|\)))#\s*undef\s+([^ ]+)$)" }
		{
		}

		template<class OutputStream>
		void preprocess(FilePathView path, OutputStream& code) {
			TextReader reader{ path };

			while (auto line_opt = reader.readLine()) {
				const String line_before = line_opt.value().trim();
				String& line = line_opt.value().trim();

				// マクロの展開処理
				macroProcessor.replaceMacros(line);

				// マクロ関数の展開処理
				macroProcessor.replaceMacroFunctions(line);

				if (line.starts_with(U"#")) {
					// #include""<>
					if (const auto include_path = includeProcessor.getIncludePath(line,FileSystem::ParentPath(path))) {
						preprocess(include_path, code);
						includeProcessor.addInclude(include_path);
					}
					else if (const auto undef = reg_undef.match(line)) {
						macroProcessor.undefMacro(undef[2].value_or(U""));
					}
					// #define NAME
					else if (const auto define_defines = reg_define_defines.match(line)) {
						macroProcessor.defineMacro(define_defines[2].value_or(U""), U"");
					}
					// #define NAME VALUE
					else if (const auto define_values = reg_define_values.match(line)) {
						macroProcessor.defineMacro(define_values[1].value_or(U""), define_values[2].value_or(U""));
					}
					// #define NAME (1+1)
					else if (auto define_eval = reg_define_eval.match(line)) {
						String def = Unicode::Widen(define_eval[1].value().toUTF8());
						String func = Unicode::Widen(define_eval[2].value().toUTF8());
						const auto vars = def.substr(def.indexOf(U"(") + 1ull, def.lastIndexOf(U")") - def.indexOf(U"(") - 1ull).split(U',');
						for (const auto& [i, var] : Indexed(vars)) {
							utils::ReplaceVariable(func, var, U"{" + Format(i) + U"}");
						}
						macroProcessor.defineMacroFunction(def.substr(0, def.indexOf(U"(")), func);
					}
					// #pragma
					else if (const auto pragma = reg_pragma.match(line)) {
						if (includeProcessor.contains(FileSystem::RelativePath(path))) {
							return;
						}
					}
					// if文の処理
					else {
						ifProcessor.process(line, line_before, macroProcessor);
					}
				}
				else {
					if (not ifProcessor.needSkip()) {
						write(line, code);
					}
				}
			}
		}

		void write(String& line,TextWriter& writer) {
			writer << line;
		}

		void write(String& line,String& code) {
			code += line + U"\n";
		}

		RegExp reg_pragma;
		RegExp reg_define_defines;
		RegExp reg_define_values;
		RegExp reg_define_eval;
		RegExp reg_undef;

		MacroProcessor macroProcessor;
		IncludeProcessor includeProcessor;
		IfProcessor ifProcessor;
	};

	Preprocessor::Preprocessor() :
		p_impl(std::make_shared<Preprocessor_impl>())
	{
	}

	void Preprocessor::preprocess(FilePathView path, TextWriter& writer) {
		this->p_impl->macroProcessor.clear();
		this->p_impl->preprocess(path, writer);
	}

	void Preprocessor::preprocess(FilePathView path, String& code) {
		this->p_impl->macroProcessor.clear();
		this->p_impl->preprocess(path, code);
	}

	String Preprocessor::preprocess(FilePathView path) {
		this->p_impl->macroProcessor.clear();
		String code = U"";
		this->p_impl->preprocess(path, code);
		return code;
	}


	void Preprocessor::addIncludePath(FilePathView includePath) {
		this->p_impl->includeProcessor.addIncludePath(includePath);
	}

	void Preprocessor::removeIncludePath(FilePathView includePath) {
		this->p_impl->includeProcessor.removeIncludePath(includePath);
	}

}
