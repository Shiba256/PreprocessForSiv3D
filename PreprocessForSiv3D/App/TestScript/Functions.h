#define CIRCLE_R 6.0

/// @brief 単位円に点が含まれているか判定します
bool inCircle(double x, double y) {
	return (x * x + y * y <= CIRCLE_R * CIRCLE_R);
}

/// @brief 円周率を計算します
double getPi(double allNum, double inCircleNum) {
	return    4.0 * inCircleNum / allNum;
}

