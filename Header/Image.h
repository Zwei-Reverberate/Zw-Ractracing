#ifndef IMAGE_H
#define IMAGE_H
#include <vector>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../Header/Utility.h"

class Image
{
private:
	int width, height;
	std::vector<std::vector<double>> rChannel;
	std::vector<std::vector<double>> gChannel;
	std::vector<std::vector<double>> bChannel;

public:
	Image();
	Image(const int& p_width, const int& p_height);
	~Image();
	void setPixel(const int x, const int y, const double red, const double green, const double blue);
	void setPixel(const int x, const int y, const double red, const double green, const double blue, int samples_per_pixel);
	void drawImage();
	int getWidth();
	int getHeight();
};

#endif
