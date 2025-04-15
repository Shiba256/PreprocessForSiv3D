#include"IncludeProcessor.h"

namespace pps {
	IncludeProcessor::IncludeProcessor() :
		reg_include{ UR"(#\s*include\s*["|<]\s*(.+)\s*["|>])" }
	{
	}

	String IncludeProcessor::getIncludePath(const String& line,const String& ParentDirectory)const {
		String include_path;

		if (auto result = reg_include.match(line)) {
			if (result.size() != 2ull) return U"";

			if (ignore_includes_name.contains(result[1].value()))return U"";

			if (not ParentDirectory.isEmpty()) {
				const auto path = FileSystem::RelativePath(FileSystem::PathAppend(ParentDirectory, result[1].value()));
				if (FileSystem::IsFile(path)) {
					include_path = path;
					return include_path;
				}
			}

			for (const auto& parent_path : current_include_paths) {	
				const auto path = FileSystem::RelativePath(FileSystem::PathAppend(parent_path, result[1].value()));
				if (FileSystem::IsFile(path)) {
					include_path = path;
					return include_path;
				}
			}

		}

		return U"";
	}
}
