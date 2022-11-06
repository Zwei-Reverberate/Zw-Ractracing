#include <iostream>
#include "../Header/ZwApp.h"
#include "../Header/Camera.h"


int main()
{
	ZwApp zw;
	//zw.imgSetting();
	zw.renderWithMultiThreads();
	zw.renderLoop();
	return 0;
}