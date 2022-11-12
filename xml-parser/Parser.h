#pragma once
#include "Xml.h"
#include <string>
using namespace std;

namespace yazi {
	namespace xml {
		class Parser {
		public:
			Parser();
			// 通过文件名加载xml文件
			bool load_file(const string& file);
			// 通过字符串加载xml文件
			bool load_string(const string& str);
			Xml parse();

		private:
			// 忽略空格
			void skip_white_space();
			// 解析xml声明
			bool parse_declaration();
			// 解析注释
			bool parse_comment();
			// 解析元素
			Xml parse_element();
			// 解析元素名称
			string parse_element_name();
			// 解析元素内容
			string parse_element_text();
			// 解析元素属性——键
			string parse_element_attr_key();
			// 解析元素属性——值
			string parse_element_attr_val();

		private:
			string m_str;
			int m_idx;
		};
	}
}