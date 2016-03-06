/*
 * Open Closed Principle, Entities should be open for extension and closed for modification
 */

#include <string>
#include <vector>
#include <iostream>

enum class Color {Red, Green, Blue};

enum class Size {Small, Medium, Large};

struct Product
{
	std::string m_name;
	Color m_color;
	Size m_size;
};

template<typename T> 
struct ISpecification
{
	virtual bool is_satisfied(T* item) = 0;
};

template<typename T>
struct IFilter
{
	virtual std::vector<T*> filter(std::vector<T*> items, ISpecification<T>& spec) = 0;
};

struct BetterFilter : IFilter<Product>
{
	typedef std::vector<Product*> Items;
	Items filter(Items items, ISpecification<Product>& spec) override
	{
		Items result;
		for (auto& i : items)
		{
			if (spec.is_satisfied(i) == true)
			{
				result.push_back(i);
			}
		}

		return result;
	}
};

struct ColorSpecification : ISpecification<Product>
{
	Color m_color;

	explicit ColorSpecification(const Color color)
		: m_color(color)
	{

	}

	bool is_satisfied(Product* item) override
	{
		return (item->m_color == m_color);
	}
};

struct SizeSpecification : ISpecification<Product>
{
	Size m_size;

	explicit SizeSpecification(const Size size)
		: m_size(size)
	{

	}

	bool is_satisfied(Product* item) override
	{
		return (item->m_size == m_size);
	}
};

template <typename T> 
struct AndSpecification : ISpecification<T>
{
	ISpecification<T>& m_first;
	ISpecification<T>& m_second;

	AndSpecification(ISpecification<T>& first, ISpecification<T>& second) 
		: m_first(first), m_second(second)
	{

	}

	bool is_satisfied(T* item) override
	{
		return m_first.is_satisfied(item) && m_second.is_satisfied(item);
	}
};

int _tmain(int argc, char** argv)
{
	Product apple{ "Apple", Color::Green, Size::Small };
	Product tree{ "tree", Color::Green, Size::Large };
	Product house{ "house", Color::Blue, Size::Large };

	std::vector<Product*> all{ &apple, &tree, &house };

	BetterFilter bf;
	ColorSpecification green(Color::Green);
	auto greenProducts = bf.filter(all, green);

	std::cout << "Green products" << std::endl;
	for (auto& p : greenProducts)
	{
		std::cout << p->m_name << std::endl;
	}

	SizeSpecification large(Size::Large);
	AndSpecification<Product> greenAndLarge(green, large);
	auto greenAndLargeProducts = bf.filter(all, greenAndLarge);

	std::cout << "Green and large products" << std::endl;
	for (auto& p : greenAndLargeProducts)
	{
		std::cout << p->m_name << std::endl;
	}

	return 0;
}

