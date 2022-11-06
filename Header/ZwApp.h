#ifndef ZWAPP_H
#define ZWAPP_H  
#include <chrono>
#include <thread>
#include "../Header/Image.h"
#include "../Header/Camera.h"
#include "../Header/Sphere.h"
#include "../Header/HittableList.h"
#include "../Header/Material.h"
#include "../Imgui/imgui.h"
#include "../Imgui/imgui_impl_glfw.h"
#include "../Imgui/imgui_impl_opengl2.h"



const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

class ZwApp
{
private:
	Image img;
	GLFWwindow* window;
	Camera camera;

public:
	ZwApp();
	void renderLoop();
	void imgSetting();

	int renderedPixel = 0;
	int totalPixel = 1280 * 720;

	// 屏幕空间中的物体列表
	HittableList world;
	void random_scene();

	// 采样数量
	const int samples_per_pixel = 50;
	// 最大递归深度
	const int max_depth = 50;

	// 计时
	std::chrono::system_clock::time_point startTime;

	// 多线程
	const int threadNum = 16;
	static void renderWithOneThread(int k, ZwApp*ptr);
	void renderWithMultiThreads();

public:
	color ray_color(const Ray& r, int depth);
};




#endif

