# PreprocessForSiv3D

�w�肵���t�@�C���ɑ΂��āAC++�X�^�C���̃v���v���Z�b�T���������s���܂��B�v���v���Z�b�T�f�B���N�e�B�u�͈ȉ��̂��̂ɑΉ����Ă��܂��B
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

## �g�p��
`Functions.h`�y��`Main.as`��p�ӂ��܂��B
- Functions.h
```C++
#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#define CIRCLE_R 6.0

/// @brief �P�ʉ~�ɓ_���܂܂�Ă��邩���肵�܂�
bool inCircle(double x, double y) {
	return (x * x + y * y <= CIRCLE_R * CIRCLE_R);
}

/// @brief �~�������v�Z���܂�
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
    Print << "�~�̔��a��" << CIRCLE_R << "�ł�";
#endif

#undef CIRCLE_R

#ifndef CIRCLE_R
    Print << "CIRCLE_R �� #undef ����܂���";
#endif

}
```

�Ō��Siv3D���̃R�[�h��`pps::Preprocessor`���`���A`pps::Preprocessor::preprocess(FilePathView)`�����s���܂��B

```C++
#include<Siv3D.hpp>

#include"Preprocessor.h"

void Main() {
	pps::Preprocessor preprocessor;

	// ������̃R�[�h�𕶎���Ƃ��Ď擾
	Script script{ Arg::code = preprocessor.preprocess(U"TestScript/Main.as") };
	
	auto updateFunction = script.getFunction<void(void)>(U"update");

	while (System::Update()) {
		updateFunction();
	}
}
```

������̃R�[�h
```C++
/// @brief �P�ʉ~�ɓ_���܂܂�Ă��邩���肵�܂�
bool inCircle(double x, double y) {
return (x * x + y * y <= 6.0 * 6.0);
}

/// @brief �~�������v�Z���܂�
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
Print << "�~�̔��a��" << 6.0 << "�ł�";


Print << "CIRCLE_R �� #undef ����܂���";

}
```

---
