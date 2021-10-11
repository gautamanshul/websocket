#include <iostream>
#include <string>
#include <algorithm>
#include "model.hpp"
#include <sstream>
#include "visitor.hpp"

struct HtmlVisitor : Visitor
{
	virtual void visit(const Paragraph& p) override
	{
		oss << "<p>" << p.text << "</p>\n";
 	}

	virtual void visit(const ListItem& l) override
	{
		oss << "<li>" << l.text << "</li>";
	}

	virtual void visit(const List& l) override
	{
		oss << "<ul>" << "\n";
		for (auto ls : l)
		{
			ls.accept(*this);
		}
		std::cout << "</ul>" << "\n";
	}

	
	std::string str() const override
	{
		return oss.str();
	}
private:
	std::ostringstream oss;
};

int main15()
{
	Paragraph p{ "Here are some colors" };
	ListItem red{ "Red" };
	ListItem green{ "Green" };
	ListItem blue{ "Blue" };

	List colors{ red, green, blue };
	std::vector<Element*> document{ &p, &colors };
	HtmlVisitor v;
	
	for (auto x : document)
	{
		x->accept(v);
	}
	

	std::cout << v.str() << "\n";
	getchar();
		return 0;
}