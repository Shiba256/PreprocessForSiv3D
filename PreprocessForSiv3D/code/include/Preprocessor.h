#pragma once

#include"stdafx.h"

namespace pps {
	class Preprocessor {
	public:
		SIV3D_NODISCARD_CXX20
		Preprocessor();

		SIV3D_NODISCARD_CXX20
		Preprocessor(const Preprocessor&) = default;

		SIV3D_NODISCARD_CXX20
		Preprocessor(Preprocessor&&) = default;

		SIV3D_NODISCARD_CXX20
		~Preprocessor() = default;

		/// @brief 指定されたパスのプリプロセッサを実行します
		/// @param path ファイルパス
		/// @param writer 書き込み先
		void preprocess(FilePathView path, TextWriter& writer);

		/// @brief 指定されたパスのプリプロセッサを実行します
		/// @param path ファイルパス
		/// @param code 処理後のコード
		void preprocess(FilePathView path, String& code);

		/// @brief 指定されたパスのプリプロセッサを実行します
		/// @param path ファイルパス
		/// @return 処理後のコード
		SIV3D_NODISCARD_CXX20
		String preprocess(FilePathView path);

		/// @brief includeパスを追加します
		/// @param includePath 追加したいディレクトリのパス
		void addIncludePath(FilePathView includePath);

		/// @brief includeパスを削除します
		/// @param includePath 削除したいディレクトリのパス
		void removeIncludePath(FilePathView includePath);

	private:
		struct Preprocessor_impl;

		std::shared_ptr<Preprocessor_impl> p_impl;
	};
}
