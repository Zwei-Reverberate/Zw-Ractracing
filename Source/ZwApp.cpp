#include "..\Header\ZwApp.h"

ZwApp::ZwApp()
{
	if (!glfwInit()) { EXIT_FAILURE; }
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Ray Tracing", nullptr, nullptr);
	if (window == nullptr) { EXIT_FAILURE; }
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
}

void ZwApp::renderLoop()
{
	while (!glfwWindowShouldClose(window))
	{
		int w = img.getWidth();
		int h = img.getHeight();
		glfwPollEvents();
		glfwGetFramebufferSize(window, &w, &h);
		glViewport(0, 0, w, h);
		glClearColor(0.0f, 0.0f, 0.0f, 1.00f);
		glClear(GL_COLOR_BUFFER_BIT);

		img.drawImage();

		glfwMakeContextCurrent(window);
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
}

void ZwApp::imgSetting()
{
	// 计时
	auto startTime = std::chrono::system_clock::now();

	img = Image(WINDOW_WIDTH, WINDOW_HEIGHT);
	auto aspect_ratio = 16.0 / 9.0;
	//camera = Camera(point3(0, 0, 0), point3(0, 0, -1), vec3(0, 1, 0), 90, aspect_ratio);
	//camera = Camera(point3(-2, 2, 1), point3(0, 0, -1), vec3(0, 1, 0), 90, aspect_ratio);
	// camera = Camera(point3(-2, 2, 1), point3(0, 0, -1), vec3(0, 1, 0), 20, aspect_ratio);
	point3 lookfrom(13, 2, 3);
	point3 lookat(0, 0, 0);
	vec3 vup(0, 1, 0);
	auto dist_to_focus = 10.0;
	auto aperture = 0.1;

	camera = Camera(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

	random_scene();
	// Test Scene
	/*
	auto material_ground = std::make_shared<Lambertian>(color(0.8, 0.8, 0.0));
	auto material_center = std::make_shared<Lambertian>(color(0.1, 0.2, 0.5));
	auto material_left = std::make_shared<Dielectric>(1.5);
	auto material_right = std::make_shared<Metal>(color(0.8, 0.6, 0.2), 0.0);


	// 向屏幕空间中的物体列表中添加球体
	world.add(std::make_shared<Sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
	world.add(std::make_shared<Sphere>(point3(0.0, 0.0, -1.0), 0.5, material_center));
	world.add(std::make_shared<Sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
	// 如果使用负半径，几何形状不受影响，但表面法线指向内部。这可以用作制造空心玻璃球的气泡
	world.add(std::make_shared<Sphere>(point3(-1.0, 0.0, -1.0), -0.45, material_left));
	world.add(std::make_shared<Sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));
	*/

	for (int x = img.getHeight() - 1; x >= 0; --x)
	{
		for (int y = 0; y < img.getWidth(); ++y)
		{

			color pixel_color(0, 0, 0);
			for (int s = 0; s < samples_per_pixel; ++s)
			{
				auto u = (y + random_double()) / (img.getWidth() - 1);
				auto v = (x + random_double()) / (img.getHeight() - 1);
				Ray r = camera.get_ray(u, v);
				pixel_color += ray_color(r, max_depth);
			}
			img.setPixel(y, x, pixel_color.e[0], pixel_color.e[1], pixel_color.e[2], samples_per_pixel);
			renderedPixel++;
		}
		if (renderedPixel != totalPixel)
		{
			auto nowTime = std::chrono::system_clock::now();
			auto durationTime = std::chrono::duration_cast<std::chrono::microseconds>(nowTime - startTime);
			double outputTime = double(durationTime.count()) * std::chrono::microseconds::period::num / std::chrono::microseconds::period::den;
			printf("\r渲染中[%.2lf%%], 耗时 %.2lf s", ((float)renderedPixel / (float)totalPixel) * 100.0, outputTime);
		}
		else
		{
			auto nowTime = std::chrono::system_clock::now();
			auto durationTime = std::chrono::duration_cast<std::chrono::microseconds>(nowTime - startTime);
			double outputTime = double(durationTime.count()) * std::chrono::microseconds::period::num / std::chrono::microseconds::period::den;
			printf("\r渲染完成[%.2lf%%], 耗时 %.2lf s", 100.0, outputTime);
		}
	}	
}

void ZwApp::random_scene()
{
	auto ground_material = std::make_shared<Lambertian>(color(0.5, 0.5, 0.5));
	world.add(std::make_shared<Sphere>(point3(0, -1000, 0), 1000, ground_material));

	for (int a = -11; a < 11; a++) 
	{
		for (int b = -11; b < 11; b++) 
		{
			auto choose_mat = random_double();
			point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

			if ((center - point3(4, 0.2, 0)).length() > 0.9) 
			{
				std::shared_ptr<Material> sphere_material;

				if (choose_mat < 0.8) 
				{
					// diffuse
					auto albedo = random() * random();
					sphere_material = std::make_shared<Lambertian>(albedo);
					world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
				}
				else if (choose_mat < 0.95) 
				{
					// metal
					auto albedo = random(0.5, 1);
					auto fuzz = random_double(0, 0.5);
					sphere_material = std::make_shared<Metal>(albedo, fuzz);
					world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
				}
				else 
				{
					// glass
					sphere_material = std::make_shared<Dielectric>(1.5);
					world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
				}
			}
		}
	}
	auto material1 = std::make_shared<Dielectric>(1.5);
	world.add(std::make_shared<Sphere>(point3(0, 1, 0), 1.0, material1));

	auto material2 = std::make_shared<Lambertian>(color(0.4, 0.2, 0.1));
	world.add(std::make_shared<Sphere>(point3(-4, 1, 0), 1.0, material2));

	auto material3 = std::make_shared<Metal>(color(0.7, 0.6, 0.5), 0.0);
	world.add(std::make_shared<Sphere>(point3(4, 1, 0), 1.0, material3));
}

void ZwApp::renderWithOneThread(int k, ZwApp* ptr)
{
	for (int x = ptr->img.getHeight() - 1 - k; x >= 0; x-= ptr->threadNum)
	{
		for (int y = 0; y < ptr->img.getWidth(); ++y)
		{

			color pixel_color(0, 0, 0);
			for (int s = 0; s < ptr->samples_per_pixel; ++s)
			{
				auto u = (y + random_double()) / (ptr->img.getWidth() - 1);
				auto v = (x + random_double()) / (ptr->img.getHeight() - 1);
				Ray r = ptr->camera.get_ray(u, v);
				pixel_color += ptr->ray_color(r, ptr->max_depth);
			}
			ptr->img.setPixel(y, x, pixel_color.e[0], pixel_color.e[1], pixel_color.e[2], ptr->samples_per_pixel);
			ptr->renderedPixel++;
		}
		if (ptr->renderedPixel != ptr->totalPixel)
		{
			auto nowTime = std::chrono::system_clock::now();
			auto durationTime = std::chrono::duration_cast<std::chrono::microseconds>(nowTime - ptr->startTime);
			double outputTime = double(durationTime.count()) * std::chrono::microseconds::period::num / std::chrono::microseconds::period::den;
			printf("\r渲染中[%.2lf%%], 耗时 %.2lf s", ((float)ptr->renderedPixel / (float)ptr->totalPixel) * 100.0, outputTime);
		}
	}
}

void ZwApp::renderWithMultiThreads()
{
	// 计时
	startTime = std::chrono::system_clock::now();
	// 共享数据
	img = Image(WINDOW_WIDTH, WINDOW_HEIGHT);
	auto aspect_ratio = 16.0 / 9.0;
	point3 lookfrom(13, 2, 3);
	point3 lookat(0, 0, 0);
	vec3 vup(0, 1, 0);
	auto dist_to_focus = 10.0;
	auto aperture = 0.1;
	camera = Camera(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);
	random_scene();


	// 生成线程
	std::vector<std::thread> threads;
	for (int i = 0; i < threadNum; ++i)
	{
		threads.push_back(std::thread(renderWithOneThread, i, this));
	}
	for (auto& thread : threads)
	{
		thread.join();
	}

	auto nowTime = std::chrono::system_clock::now();
	auto durationTime = std::chrono::duration_cast<std::chrono::microseconds>(nowTime - startTime);
	double outputTime = double(durationTime.count()) * std::chrono::microseconds::period::num / std::chrono::microseconds::period::den;
	printf("\r渲染完成[%.2lf%%], 耗时 %.2lf s", 100.0, outputTime);
}

color ZwApp::ray_color(const Ray& r, int depth)
{
	hit_record rec;

	// If we've exceeded the ray bounce limit, no more light is gathered.
	if (depth <= 0) return color(0, 0, 0);

	if (world.hit(r, 0.001, infinity, rec))
	{
		Ray scattered;
		color attenuation;

		// 递归采样
		if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
		{
			return attenuation * ray_color(scattered, depth - 1);
		}
		return color(0, 0, 0);
	}
	vec3 unit_direction = unit_vector(r.direction());
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}


