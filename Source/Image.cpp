#include "..\Header\Image.h"

Image::Image()
{
	width = 0;
	height = 0;
}

Image::Image(const int& p_width, const int& p_height)
{
	width = p_width;
	height = p_height;
	rChannel.resize(width, std::vector<double>(height, 0));
	gChannel.resize(width, std::vector<double>(height, 0));
	bChannel.resize(width, std::vector<double>(height, 0));
}

Image::~Image()
{
}

void Image::setPixel(const int x, const int y, const double red, const double green, const double blue)
{
	rChannel.at(x).at(y) = red;
	gChannel.at(x).at(y) = green;
	bChannel.at(x).at(y) = blue;
}

void Image::setPixel(const int x, const int y, const double red, const double green, const double blue, int samples_per_pixel)
{
    auto r = red;
    auto g = green;
    auto b = blue;

    // Divide the color by the number of samples and gamma-correct for gamma=2.0.
    auto scale = 1.0 / samples_per_pixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    rChannel.at(x).at(y) = (256 * clamp(r, 0.0, 0.999));
    gChannel.at(x).at(y) = (256 * clamp(g, 0.0, 0.999));
    bChannel.at(x).at(y) = (256 * clamp(b, 0.0, 0.999));
}

void Image::drawImage()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, 0.0,height, 0.0, 1.0);
    glBegin(GL_POINTS);

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            glColor3d(rChannel[i][j] / 255, gChannel[i][j] / 255, bChannel[i][j] / 255);
            glVertex3f(i , j, 0);
        }
    }
    glEnd();
}

int Image::getWidth()
{
    return width;
}

int Image::getHeight()
{
    return height;
}
