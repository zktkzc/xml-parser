#include"Xml.h"
#include "Parser.h"
#include <stdexcept>
#include<sstream>
#include<fstream>
using namespace std;
using namespace yazi::xml;

Value::Value()
{
}

Value::Value(bool value)
{
	*this = value;
}

Value::Value(int value)
{
	*this = value;
}

Value::Value(double value)
{
	*this = value;
}

Value::Value(const char* value) : m_value(value)
{
}

Value::Value(const string& value) : m_value(value)
{
}

Value::~Value()
{
}

Value& Value::operator = (bool value)
{
	m_value = value ? "true" : "false";
	return *this;
}

Value& Value::operator = (int value)
{
	stringstream ss;
	ss << value;
	m_value = ss.str();
	return *this;
}

Value& Value::operator = (double value)
{
	stringstream ss;
	ss << value;
	m_value = ss.str();
	return *this;
}

Value& Value::operator = (const char* value)
{
	m_value = value;
	return *this;
}

Value& Value::operator = (const string& value)
{
	m_value = value;
	return *this;
}

Value& Value::operator = (const Value& value)
{
	m_value = value.m_value;
	return *this;
}

bool Value::operator == (const Value& other)
{
	return m_value == other.m_value;
}

bool Value::operator != (const Value& other)
{
	return !(m_value == other.m_value);
}

Value::operator bool()
{
	if (m_value == "true")
		return true;
	else if (m_value == "false")
		return false;
	return false;
}

Value::operator int()
{
	return std::atoi(m_value.c_str());
}

Value::operator double()
{
	return std::atof(m_value.c_str());
}

Value::operator string()
{
	return m_value;
}

Xml::Xml() : m_name(nullptr), m_text(nullptr), m_attrs(nullptr), m_child(nullptr)
{
}

Xml::Xml(const char* name) : m_name(nullptr), m_text(nullptr), m_attrs(nullptr), m_child(nullptr)
{
	m_name = new string(name);
}

Xml::Xml(const string& name) : m_name(nullptr), m_text(nullptr), m_attrs(nullptr), m_child(nullptr)
{
	m_name = new string(name);
}

// 拷贝构造函数
Xml::Xml(const Xml& other)
{
	m_name = other.m_name;
	m_text = other.m_text;
	m_attrs = other.m_attrs;
	m_child = other.m_child;
}

// 获取节点名称
string Xml::name() const
{
	if (m_name == nullptr) // 如果指针为空
	{
		return "";
	}
	return *m_name;
}

// 设置节点名称
void Xml::name(const string& name)
{
	if (m_name != nullptr)
	{
		delete m_name;
		m_name = nullptr;
	}

	m_name = new string(name);
}

// 获取节点内容
string Xml::text() const
{
	if (m_text == nullptr) // 如果指针为空
	{
		return "";
	}
	return *m_text;
}

// 设置节点内容
void Xml::text(const string& text)
{
	if (m_text != nullptr)
	{
		delete m_text;
		m_text = nullptr;
	}

	m_text = new string(text);
}

// 获取节点属性
Value Xml::attr(const string& key)
{
	if (m_attrs == nullptr)
	{
		m_attrs = new map<string, Value>();
	}
	return (*m_attrs)[key];
}

// 设置节点属性
void Xml::attr(const string& key, const Value& val)
{
	if (m_attrs == nullptr)
	{
		m_attrs = new map<string, Value>();
	}
	(*m_attrs)[key] = val;
}

// 序列化
string Xml::str() const
{
	if (m_name == nullptr)
	{
		throw logic_error("element name is enpty");
	}
	stringstream ss;
	ss << "<";
	ss << *m_name;
	if (m_attrs != nullptr)
	{
		for (auto it = m_attrs->begin(); it != m_attrs->end(); it++)
		{
			ss << " " << it->first << "=\"" << string(it->second) << "\"";
		}
	}
	ss << ">";
	if (m_child != nullptr)
	{
		for (auto it = m_child->begin(); it != m_child->end(); it++)
		{
			ss << it->str();
		}
	}
	if (m_text != nullptr)
	{
		ss << *m_text;
	}
	ss << "</" << *m_name << ">";
	return ss.str();
}

// 释放内存
void Xml::clear()
{
	if (m_name != nullptr)
	{
		delete m_name;
		m_name = nullptr;
	}
	if (m_text != nullptr)
	{
		delete m_text;
		m_text = nullptr;
	}
	if (m_attrs != nullptr)
	{
		delete m_attrs;
		m_attrs = nullptr;
	}
	if (m_child != nullptr)
	{
		for (auto it = m_child->begin(); it != m_child->end(); it++)
		{
			it->clear();
		}
		delete m_child;
		m_child = nullptr;
	}
}

// 添加子节点
void Xml::append(const Xml& child)
{
	if (m_child == nullptr)
	{
		m_child = new list<Xml>();
	}
	// 将节点添加到链表最后
	m_child->push_back(child);
}

// 通过数组方式获取子节点
Xml& Xml::operator[](int index)
{
	if (index < 0)
	{
		throw logic_error("index less than zero");
	}
	if (m_child == nullptr)
	{
		m_child = new list<Xml>();
	}
	int size = m_child->size();
	if (index >= 0 && index < size)
	{
		auto it = m_child->begin();
		for (int i = 0; i < index; i++)
		{
			it++;
		}
		return *it;
	}
	if (index >= size)
	{
		// 扩容list
		for (int i = size; i <= index; i++)
		{
			// 将节点添加到链表最后
			m_child->push_back(Xml());
		}
	}
	// 返回最后一个节点
	return m_child->back();
}

// 通过节点名称获取子节点
Xml& Xml::operator[](const char* name)
{
	return (*this)[string(name)];
}

Xml& Xml::operator[](const string& name)
{
	if (m_child == nullptr)
	{
		m_child = new list<Xml>();
	}
	for (auto it = m_child->begin(); it != m_child->end(); it++)
	{
		if (it->name() == name)
		{
			return *it;
		}
	}
	m_child->push_back(Xml(name));
	return m_child->back();
}

// 删除子节点
void Xml::remove(int index)
{
	if (m_child == nullptr)
	{
		return;
	}
	int size = m_child->size();
	if (index < 0 || index >= size)
	{
		return;
	}
	auto it = m_child->begin();
	for (int i = 0; i < index; i++)
	{
		it++;
	}
	it->clear();
	m_child->erase(it); // 删除迭代器
}

void Xml::remove(const char* name)
{
	remove(string(name));
}

void Xml::remove(const string& name)
{
	if (m_child == nullptr)
	{
		return;
	}
	for (auto it = m_child->begin(); it != m_child->end();)
	{
		if (it->name() == name)
		{
			it->clear();
			it = m_child->erase(it);
		}
		else
		{
			it++;
		}
	}
}

// 赋值构造函数
Xml& Xml::operator=(const Xml& other)
{
	clear();
	m_name = other.m_name;
	m_text = other.m_text;
	m_attrs = other.m_attrs;
	m_child = other.m_child;
	return *this;
}

bool Xml::load(const string& filename)
{
	Parser p;
	if (!p.load_file(filename))
	{
		return false;
	}
	*this = p.parse();
	return true;
}

bool Xml::save(const string& filename)
{
	ofstream fout(filename);
	if (fout.fail())
	{
		return false;
	}
	fout << str();
	fout.close();
	return true;
}

bool Xml::parse(const string& str)
{
	Parser p;
	if (!p.load_string(str))
	{
		return false;
	}
	*this = p.parse();
	return true;
}