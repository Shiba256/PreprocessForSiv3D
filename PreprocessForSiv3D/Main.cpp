#include<Siv3D.hpp>

#include"Preprocessor.h"

void Main() {
	pps::Preprocessor preprocessor;

	// 処理後のコードを文字列として取得
	Script script{ Arg::code = preprocessor.preprocess(U"TestScript/Main.as") };
	
	auto updateFunction = script.getFunction<void(void)>(U"update");

	while (System::Update()) {
		updateFunction();
	}
}
