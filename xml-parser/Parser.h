#pragma once
#include "Xml.h"
#include <string>
using namespace std;

namespace yazi {
	namespace xml {
		class Parser {
		public:
			Parser();
			// ͨ���ļ�������xml�ļ�
			bool load_file(const string& file);
			// ͨ���ַ�������xml�ļ�
			bool load_string(const string& str);
			Xml parse();

		private:
			// ���Կո�
			void skip_white_space();
			// ����xml����
			bool parse_declaration();
			// ����ע��
			bool parse_comment();
			// ����Ԫ��
			Xml parse_element();
			// ����Ԫ������
			string parse_element_name();
			// ����Ԫ������
			string parse_element_text();
			// ����Ԫ�����ԡ�����
			string parse_element_attr_key();
			// ����Ԫ�����ԡ���ֵ
			string parse_element_attr_val();

		private:
			string m_str;
			int m_idx;
		};
	}
}