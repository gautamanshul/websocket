#include <vector>
#include <string>
#include <iostream>

struct GraphicObject
{
	virtual void draw() = 0;
};

struct Circle : GraphicObject
{
	void draw() override
	{
		std::cout << "Circle " << std::endl;
	}
};

struct Group : GraphicObject
{
	std::string  name;
	std::vector<GraphicObject*> objects;

	Group(const std::string& name) : name{ name } {}

	void draw() override
	{
		std::cout << "Group " << name.c_str() << " contains: " << std::endl;
		for (auto&& o : objects)
		{
			o->draw();
		}
	}
};


int main_geometric_comp(int argc, char* argv[])
{
	Circle c1, c2;
	Group  root("root");

	root.objects.push_back(&c1);
	Group subgroup("sub");
	subgroup.objects.push_back(&c2);

	root.objects.push_back(&subgroup);

	root.draw();

	getchar();
	return 0;
}