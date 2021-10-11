#include <string>
#include <iostream>

struct Renderer
{
	virtual void render_circle(const float x, const float y, const float radius) = 0;
};

struct RasterRenderer : Renderer
{
	void render_circle(const float x, const float y, const float radius) override
	{
		std::cout << "Rasterizing a circle of radius " << radius << std::endl;
	}
};

struct VectorRenderer : Renderer
{
	void render_circle(const float x, const float y, const float radius) override
	{
		std::cout << "Vectorizing a circle of radius " << radius << std::endl;
	}
};

struct Shape
{
	Renderer& renderer;
	Shape(Renderer& renderer) : renderer(renderer) {}
protected:
	virtual void draw() = 0;
	virtual void resize(float factor) = 0;
};

struct Circlev1 : Shape
{
	float x, y, radius;

	void draw() override
	{
		renderer.render_circle(x, y, radius);
	}

	void resize(float factor) override
	{
		radius *= factor;
	}

	explicit Circlev1( Renderer & renderer, const float x, const float y, const float radius): Shape(renderer),
		x(x), y(y), radius(radius)	
	{}

};

int main_renderer(int argc, char *argv[])
{
	RasterRenderer renderer;
	Circlev1 c1(renderer, 2,3, 4);

	c1.draw();
	c1.resize(2);
	c1.draw();

	getchar();
	return 0;
}