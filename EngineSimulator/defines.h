#pragma once

#define INERTIA 10
#define OVERHEAT_TEMP 110
#define HM_COEF 0.01
#define HV_COEF 0.00001
#define C_COEF 0.1

int m_from_v(int v) {
	switch (v) {
	case 0:
		return 20;
	case 75:
		return 75;
	case 150:
		return 100;
	case 200:
		return 105;
	case 250:
		return 75;
	case 300:
		return 0;
	default:
		return -1;
	}
}