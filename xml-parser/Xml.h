#pragma once
#include<string>
#include<map>
#include<list>
using namespace std;

namespace yazi {
	namespace xml {

		class Value {
		public:
			Value();
			Value(bool value);
			Value(int value);
			Value(double value);
			Value(const char* value);
			Value(const string& value);
			~Value();

			Value& operator = (bool value);
			Value& operator = (int value);
			Value& operator = (double value);
			Value& operator = (const char* value);
			Value& operator = (const string& value);
			Value& operator = (const Value& value);

			bool operator == (const Value& other);
			bool operator != (const Value& other);

			operator bool();
			operator int();
			operator double();
			operator string();

		private:
			string m_value;
		};

		class Xml
		{
		public:
			Xml();
			Xml(const char* name);
			Xml(const string& name);

			// 拷贝构造函数
			Xml(const Xml& other);

			// 获取节点名称
			string name() const;

			// 设置节点名称
			void name(const string& name);

			// 获取节点内容
			string text() const;

			// 设置节点内容
			void text(const string& text);

			// 获取节点属性
			Value attr(const string& key);

			// 设置节点属性
			void attr(const string& key, const Value& val);

			// 序列化
			string str() const;

			// 释放内存
			void clear();

			// 添加子节点
			void append(const Xml& child);

			// 通过数组方式获取子节点
			Xml& operator [] (int index);

			// 通过节点名称获取子节点
			Xml& operator [] (const char* name);
			Xml& operator [] (const string& name);

			// 删除子节点
			void remove(int index);
			void remove(const char* name);
			void remove(const string& name);

			// 赋值构造函数
			Xml& operator = (const Xml& other);

			typedef list<Xml>::iterator iterator;
			iterator begin()
			{
				return m_child->begin();
			}
			iterator end()
			{
				return m_child->end();
			}
			iterator erase(iterator it)
			{
				it->clear();
				return m_child->erase(it);
			}

			// 获取节点的子节点个数
			int size() const
			{
				return m_child->size();
			}

			bool load(const string& filename);
			bool save(const string& filename);
			bool parse(const string& str);

			friend ostream& operator << (ostream& os, const Xml& xml)
			{
				os << xml.str();
				return os;
			}

		private:
			// 节点名称
			string* m_name;
			// 节点内容
			string* m_text;
			// 属性
			map<string, Value>* m_attrs;

			// 子节点
			list<Xml>* m_child;
		};
	}
}