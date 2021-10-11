#include <iostream>
#include <string>

struct Rendererv1
{
	virtual void render_circle(const float x, const float y, const float radius) = 0;
};

struct RasterizeRendererv1 : Rendererv1
{
	void render_circle(const float x, const float y, const float radius) override
	{
		std::cout << "Rendering a circle of radius " << radius << std::endl;
	}
};

struct VectorRendererv1 : Rendererv1
{
	void render_circle(const float x, const float y, const float radius) override
	{
		std::cout << "Vectorized a circle of radius " << radius << std::endl;
	}
};

struct Shapev1
{
	Rendererv1& renderer;
	Shapev1( Rendererv1 & renderer ) : renderer(renderer) {}
protected:
	virtual void draw() = 0;
	virtual void resize(const float factor) = 0;
};

struct Circlev1 : Shapev1
{
	float x, y, radius;

	explicit Circlev1( Rendererv1 & renderer, const float x, const float y, const float radius ) :
		Shapev1{renderer}, x(x), y(y), radius(radius) {}

	void draw() override
	{
		renderer.render_circle(x, y, radius);
	}

	void resize(const float factor)
	{
		radius *= factor;
	}
};

int main_render_v1(int argc, char* argv[])
{
	RasterizeRendererv1 renderer;
	Circlev1 c1{ renderer, 2, 3, 4 };

	c1.draw();
	c1.resize(3);
	c1.draw();

	getchar();
	return 0;
}