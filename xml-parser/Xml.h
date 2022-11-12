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

			// �������캯��
			Xml(const Xml& other);

			// ��ȡ�ڵ�����
			string name() const;

			// ���ýڵ�����
			void name(const string& name);

			// ��ȡ�ڵ�����
			string text() const;

			// ���ýڵ�����
			void text(const string& text);

			// ��ȡ�ڵ�����
			Value attr(const string& key);

			// ���ýڵ�����
			void attr(const string& key, const Value& val);

			// ���л�
			string str() const;

			// �ͷ��ڴ�
			void clear();

			// ����ӽڵ�
			void append(const Xml& child);

			// ͨ�����鷽ʽ��ȡ�ӽڵ�
			Xml& operator [] (int index);

			// ͨ���ڵ����ƻ�ȡ�ӽڵ�
			Xml& operator [] (const char* name);
			Xml& operator [] (const string& name);

			// ɾ���ӽڵ�
			void remove(int index);
			void remove(const char* name);
			void remove(const string& name);

			// ��ֵ���캯��
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

			// ��ȡ�ڵ���ӽڵ����
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
			// �ڵ�����
			string* m_name;
			// �ڵ�����
			string* m_text;
			// ����
			map<string, Value>* m_attrs;

			// �ӽڵ�
			list<Xml>* m_child;
		};
	}
}