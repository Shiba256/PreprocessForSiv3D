#pragma once

#include"stdafx.h"

namespace pps {
	class IncludeProcessor {
	public:
		IncludeProcessor();

		String getIncludePath(const String& line,const String& ParentDirectory)const;

		inline void addInclude(FilePathView path) {
			includes.emplace(path);
		}

		inline bool contains(FilePathView path) const {
			return includes.contains(path);
		}

		inline void addIncludePath(FilePathView path) {
			current_include_paths.emplace(path);
		}

		inline void removeIncludePath(FilePathView path) {
			current_include_paths.erase(path);
		}

	private:
		HashSet<FilePathView> ignore_includes_name = { UR"(Siv3D.hpp)" };
		HashSet<String> current_include_paths = { FileSystem::CurrentDirectory() ,FileSystem::CurrentDirectory() + U"../" };
		RegExp reg_include;

		HashSet<FilePath> includes;
	};
}
