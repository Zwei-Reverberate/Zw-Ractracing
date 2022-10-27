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
	img = Image(WINDOW_WIDTH, WINDOW_HEIGHT);
	auto aspect_ratio = 16.0 / 9.0;
	camera = Camera(point3(0, 0, 0), point3(0, 0, -1), vec3(0, 1, 0), 90, aspect_ratio);

	auto material_ground = std::make_shared<Lambertian>(color(0.8, 0.8, 0.0));
	auto material_center = std::make_shared<Lambertian>(color(0.1, 0.2, 0.5));
	auto material_left = std::make_shared<Dielectric>(1.5);
	auto material_right = std::make_shared<Metal>(color(0.8, 0.6, 0.2), 1.0);


	// 向屏幕空间中的物体列表中添加球体
	world.add(std::make_shared<Sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
	world.add(std::make_shared<Sphere>(point3(0.0, 0.0, -1.0), 0.5, material_center));
	world.add(std::make_shared<Sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
	// 如果使用负半径，几何形状不受影响，但表面法线指向内部。这可以用作制造空心玻璃球的气泡
	world.add(std::make_shared<Sphere>(point3(-1.0, 0.0, -1.0), -0.4, material_left));
	world.add(std::make_shared<Sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));

	for (int x = img.getHeight() - 1; x >= 0; --x)
	{
		for (int y = 0; y < img.getWidth(); ++y)
		{

			color pixel_color(0, 0, 0);
			for (int s = 0; s < samples_per_pixel; ++s)
			{
				auto u = (y + random_double()) / (img.getWidth() - 1);
				auto v = (x + random_double()) / (img.getHeight() - 1);
				Ray r(camera.origin, camera.lower_left_corner + u * camera.horizontal + v * camera.vertical);
				pixel_color += ray_color(r, max_depth);
			}
			img.setPixel(y, x, pixel_color.e[0], pixel_color.e[1], pixel_color.e[2], samples_per_pixel);
			renderedPixel++;
		}
		if (renderedPixel != totalPixel)
		{
			printf("\r渲染中[%.2lf%%]", ((float)renderedPixel / (float)totalPixel) * 100.0);
		}
		else
		{
			printf("\r渲染完成[%.2lf%%]", 100.0);
		}
	}	
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


