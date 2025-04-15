# PreprocessForSiv3D

指定したファイルに対して、C++スタイルのプリプロセッサ処理を実行します。プリプロセッサディレクティブは以下のものに対応しています。
- `#include`
- `#define`
- `#undef`
- `#pragma once`
- `#if`
- `#ifdef`
- `#ifndef`
- `#else`
- `#elif`
- `#endif`
---

## 使用例
`Functions.h`及び`Main.as`を用意します。
- Functions.h
```C++
#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#define CIRCLE_R 6.0

/// @brief 単位円に点が含まれているか判定します
bool inCircle(double x, double y) {
	return (x * x + y * y <= CIRCLE_R * CIRCLE_R);
}

/// @brief 円周率を計算します
double getPi(double allNum, double inCircleNum) {
	return    4.0 * inCircleNum / allNum;
}

#endif // !_FUNCTION_H_

```
- Main.as
```C++
#include"Functions.h"
#include"Functions.h"

int counter = 0;
int inCircleCounter = 0;

Font font(50);

void update(){
    counter++;
    if(inCircle(CIRCLE_R*Random(),CIRCLE_R*Random())){
        inCircleCounter++;
    }        
    font(getPi(counter,inCircleCounter)).drawAt(Scene::Center());

#ifdef CIRCLE_R
    ClearPrint();
    Print << "円の半径は" << CIRCLE_R << "です";
#endif

#undef CIRCLE_R

#ifndef CIRCLE_R
    Print << "CIRCLE_R は #undef されました";
#endif

}
```

最後にSiv3D側のコードで`pps::Preprocessor`を定義し、`pps::Preprocessor::preprocess(FilePathView)`を実行します。

```C++
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
```

処理後のコード
```C++
/// @brief 単位円に点が含まれているか判定します
bool inCircle(double x, double y) {
return (x * x + y * y <= 6.0 * 6.0);
}

/// @brief 円周率を計算します
double getPi(double allNum, double inCircleNum) {
return    4.0 * inCircleNum / allNum;
}



int counter = 0;
int inCircleCounter = 0;

Font font(50);

void update(){
counter++;
if(inCircle(6.0*Random(),6.0*Random())){
inCircleCounter++;
}
font(getPi(counter,inCircleCounter)).drawAt(Scene::Center());

ClearPrint();
Print << "円の半径は" << 6.0 << "です";


Print << "CIRCLE_R は #undef されました";

}
```

---
