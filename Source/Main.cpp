#include <iostream>
#include "../Header/ZwApp.h"
#include "../Header/Camera.h"


int main()
{
	ZwApp zw;
	zw.imgSetting();
	zw.renderLoop();
	return 0;
}