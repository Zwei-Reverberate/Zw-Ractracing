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

	// ��Ļ�ռ��е������б�
	HittableList world;
	void random_scene();

	// ��������
	const int samples_per_pixel = 50;
	// ���ݹ����
	const int max_depth = 50;

	// ��ʱ
	std::chrono::system_clock::time_point startTime;

	// ���߳�
	const int threadNum = 16;
	static void renderWithOneThread(int k, ZwApp*ptr);
	void renderWithMultiThreads();

public:
	color ray_color(const Ray& r, int depth);
};




#endif

