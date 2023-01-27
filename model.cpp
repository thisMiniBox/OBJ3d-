#include "model.h"
void CreateQuads(TriFLink* link, coordinate a, coordinate b, coordinate c, COLORREF color)
{
	if (!link->NEXT)
	{
		PadTLink(link, TriF(a, b, c, color));
		PadTLink(link, TriF(a, a + b - c, b, color));
	}
	else
	{
		InsertTNode(link, 1, TriF(a, b, c, color));
		InsertTNode(link, 1, TriF(a, a + b - c, b, color));
	}

}
void CreateCube(TriFLink* link, coordinate a, coordinate b, coordinate c, coordinate d, COLORREF color)
{
	CreateQuads(link, b, a, c, color);
	CreateQuads(link, a, d, c, color);
	CreateQuads(link, d, b, c, color);
	CreateQuads(link, a + d - c, b + d - c, d, color);
	CreateQuads(link, a, a + d - c + b - c, a + d - c, color);
	CreateQuads(link, a + d - c + b - c, b, b + d - c, color);
}
void EfficientCube(TriFLink* link, coordinate midpoint, double SideLength, COLORREF color)
{
	CreateCube(link, SetZB(-SideLength / 2, -SideLength / 2, SideLength / 2) + midpoint, SetZB(SideLength / 2, -SideLength / 2, -SideLength / 2) + midpoint, SetZB(SideLength / 2, -SideLength / 2, SideLength / 2) + midpoint, SetZB(SideLength / 2, SideLength / 2, SideLength / 2) + midpoint, color);
}

#define isNum(c) (isdigit(c)?c-48:(c=='e'?10:(c=='.'?11:(c=='-'?12:(c=='+'?13:-1)))))

double str2num(std::string s)
{	//�ַ���ת���֣�����������С���Ϳ�ѧ������ 
	int i, j, k, negative = 0;
	double n = 0;
	std::string s1, s2;

	if (s.empty()) return 0;
	if (s[0] == '-') negative = 1; //���ø������ 
	if (s[0] == '+' || s[0] == '-') s = s.substr(1, s.size());
	//--------------- 
	for (i = 0; i < s.size(); i++) //�ų�����Ҫ���ַ� 
		if (isNum(s[i]) == -1) return pow(-1.1, 1.1);
	if (s[0] == 'e' || s[0] == '.' || s[s.size() - 1] == 'e' || s[s.size() - 1] == '.')
		return pow(-1.1, 1.1); //�ų� e��. ��������β 
	i = -1; j = 0;
	while ((i = s.find('.', ++i)) != s.npos) j++;
	if (j > 1) return pow(-1.1, 1.1); //�ų����С���� 
	i = -1; j = 0;
	while ((i = s.find('e', ++i)) != s.npos) j++;
	if (j > 1) return pow(-1.1, 1.1); //�ų������ĸe 
	if (s.find('e') == s.npos) //û��eʱ�ų��Ӽ�
		if (s.find('+') != s.npos || s.find('-') != s.npos) return pow(-1.1, 1.1);
	//---------------
	if ((i = s.find('e')) != s.npos) {
		s1 = s.substr(0, i); //β������ 
		s2 = s.substr(i + 1, s.size()); //���� 
		if (s2[0] == '+') s2 = s2.substr(1, s2.size()); //����Ϊ������ȥ��+ 
		if (s2.find('.') != s2.npos) return pow(-1.1, 1.1); //���벻׼����С��
		n = str2num(s1) * pow(10.0, str2num(s2)); //β���ͽ���ֱ�ݹ���� 
		return negative ? -n : n;
	}
	i = 0; k = 1;
	if ((i = s.find('.')) != s.npos) {
		for (j = i + 1; j < s.length(); j++, k++)
			n += isNum(s[j]) / pow(10.0, (double)k);
		n += str2num(s.substr(0, i));  //�������ֵݹ���� 
	}
	else
		for (j = 0; j < s.size(); j++)
			n = n * 10 + isNum(s[j]);

	return negative ? -n : n; //��������-n 
}
Mesh::Mesh()
{}
Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
}
glm::vec3 str_vec3(const std::string str)
{
	int hm = 0;
	std::string fragment;
	double num[3] = { 0 };
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == ' ' || str[i] == '\n')
		{
			if (fragment != "\0")
			{
				num[hm] = str2num(fragment);
				hm++;
			}
			fragment = "\0";
			continue;
		}
		else
		{
			fragment += str[i];
		}
	}
	return glm::vec3(num[0], num[1], num[2]);
}
glm::vec2 str_vec2(const std::string str)
{
	int hm = 0;
	std::string fragment;
	double num[3] = { 0 };
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == ' ' || str[i] == '\n')
		{
			if (fragment != "\0")
			{
				num[hm] = str2num(fragment);
				hm++;
			}
			fragment = "\0";
			continue;
		}
		else
		{
			fragment += str[i];
		}
	}
	return glm::vec2(num[0], num[1]);
}
Vertex str_ver(
	const std::string num,
	const std::vector<glm::vec3>* Position,
	const std::vector<glm::vec3>* Normal,
	const std::vector<glm::vec2>* TexCoords)
{
	Vertex note = {};
	int front = num.find_first_of('/');
	int post = num.find_last_of('/');
	if (num[0] == '-')
	{
		note.Position = *(Position->end() + std::stoll(num.substr(0, front)));
		if (post - front > 1)
		{
			note.TexCoords = TexCoords->operator[](TexCoords->size() + std::stoll(num.substr(front + 1, post)));
			note.Normal = Normal->operator[](Normal->size() + std::stoll(num.substr(post + 1)));
			//note.TexCoords = *(TexCoords->end() + std::stoll(num.substr(front + 1, post)));
			//note.Normal = *(Normal->end() + std::stoll(num.substr(post + 1)));
			return note;
		}
		else if (post == front)
		{
			note.TexCoords = *(TexCoords->end() + std::stoll(num.substr(front + 1, post)));
			note.Normal = glm::vec3(0.0);
			return note;
		}
		else if (post - front == 1)
		{
			note.Normal = *(Normal->end() + std::stoll(num.substr(post + 1)));
			note.TexCoords = glm::vec2(0.0);
			return note;
		}
		else if (post == -1)
		{
			note.Normal = glm::vec3(0.0);
			note.TexCoords = glm::vec2(0.0);
			return note;
		}
	}
	note.Position = Position->operator[](std::stoll(num.substr(0, front)) - 1);
	if (post - front > 1)
	{
		note.TexCoords = TexCoords->operator[](std::stoll(num.substr(front + 1, post)) - 1);
		note.Normal = Normal->operator[](std::stoll(num.substr(post + 1)) - 1);
		return note;
	}
	else if (post == front)
	{
		note.TexCoords = TexCoords->operator[](std::stoll(num.substr(post + 1)) - 1);
		note.Normal = glm::vec3(0.0);
		return note;
	}
	else if (post - front == 1)
	{
		note.Normal = Normal->operator[](std::stoll(num.substr(post + 1)) - 1);
		note.TexCoords = glm::vec2(0.0);
		return note;
	}
	else if (post == -1)
	{
		note.Normal = glm::vec3(0.0);
		note.TexCoords = glm::vec2(0.0);
		return note;
	}
}
bool Model::loadobj(const std::string path)
{
	char c = 0;
	std::string Num;
	FILE* f = nullptr;
	std::vector<char> buffer;
	fopen_s(&f, path.c_str(), "r");
	if (!f)
	{
		printf_s("�ļ���ʧ��");
		return 0;
	}
	while (1)
	{
		c = fgetc(f);
		buffer.push_back(c);
		if (c == EOF)break;
	}
	fclose(f);
	char* file = buffer.data();
	printf_s("�ļ�����ɹ������ڽ����ļ�\n");
	std::vector<glm::vec3>Position;
	std::vector<glm::vec3>Normal;
	std::vector<glm::vec2>TexCoords;
	std::vector<Vertex>* mesh = nullptr;
	Vertex ver4;
	Vertex ver3;
	Vertex ver1;
	int meshNum = path.find_last_of("/");
	if (meshNum == -1)meshNum = path.find_last_of("\\");
	directory = path.substr(0, meshNum + 1);
	meshNum = 0;
	while (1)
	{
		c = *file;
		file++;
		if (c == EOF)break;
		switch (c)
		{
		case'v':
			c = *file;
			file++;
			if (c == ' ')
			{
				while (1)
				{
					c = *file;
					file++;
					if (c == 'E')c = 'e';
					Num += c;
					if (c == '\n')break;
				}
				Position.push_back(str_vec3(Num));
				Num = "";
				break;
			}
			else if (c == 'n')
			{
				c = *file;
				file++;
				if (c == ' ')
				{
					while (1)
					{
						c = *file;
						file++;
						if (c == 'E')c = 'e';
						Num += c;
						if (c == '\n')break;
					}
					Normal.push_back(str_vec3(Num));
					Num = "";
					break;
				}
				else
				{
					while (1)
					{
						c = *file;
						file++;
						if (c == '\n')break;
					}
				}
			}
			else if (c == 't')
			{
				c = *file;
				file++;
				if (c == ' ')
				{
					while (1)
					{
						c = *file;
						file++;
						if (c == 'E')c = 'e';
						Num += c;
						if (c == '\n')break;
					}
					TexCoords.push_back(str_vec2(Num));
					Num = "";
					break;
				}
				else
				{
					while (1)
					{
						c = *file;
						file++;
						if (c == '\n')break;
					}
				}
			}
			else
			{
				while (1)
				{
					c = *file;
					file++;
					if (c == '\n')break;
				}
			}
			break;
		case'f':
			c = *file;
			file++;
			if (c == ' ')
			{
				if (meshNum == 0)
				{
					MessageBox(NULL, TEXT("���������Ƿ���ȷ"), TEXT("����"), MB_OK);
					printf_s("���������Ƿ���ȷ\n");
					meshes.FreeLinkList();
					return 0;
				}
				int space = 0;
				mesh = &meshes.FindNode(meshNum)->data.vertices;
				while (1)
				{
					c = *file;
					file++;
					if (c == ' ' && Num != "")
					{
						mesh->push_back(str_ver(Num, &Position, &Normal, &TexCoords));
						Num = "";
						space++;
					}
					else if (c == ' ' && Num == "")continue;
					else if (c == '\n')
					{
						if (Num != "")
						{
							mesh->push_back(str_ver(Num, &Position, &Normal, &TexCoords));
							space++;
						}
						Num = "";
						if (space == 4)
						{
							ver4 = mesh->operator[](mesh->size() - 1);
							ver3 = mesh->operator[](mesh->size() - 2);
							ver1 = mesh->operator[](mesh->size() - space);
							glm::vec3 nor = glm::vec3(glm::cross((ver1.Position - ver4.Position), (ver3.Position - ver4.Position)));
							if (glm::angle(nor, ver4.Normal) < 90)
							{
								ver1.Normal = nor;
								ver3.Normal = nor;
							}
							else
							{
								ver1.Normal = -nor;
								ver3.Normal = -nor;
							}
							mesh->push_back(ver1);
							mesh->push_back(ver3);
						}
						else if (space > 4)
						{
							Vertex ver = {};
							ver1 = mesh->operator[](mesh->size() - space);
							for (int i = 0; i < space; i++)
							{
								ver.Position + mesh->operator[](mesh->size() - 1 - i).Position;
								ver.TexCoords + mesh->operator[](mesh->size() - 1 - i).TexCoords;
							}
							ver.Position.x = ver.Position.x / space;
							ver.Position.y = ver.Position.y / space;
							ver.Position.z = ver.Position.z / space;
							ver.TexCoords.x = ver.TexCoords.x / space;
							ver.TexCoords.y = ver.TexCoords.y / space;
							for (int i = space - 2; i >= 0; i--)
							{
								mesh->insert(mesh->end() - i, ver);
								glm::vec3 nor = glm::vec3(glm::cross((mesh->operator[](mesh->size() - 3 - i).Position - ver.Position), (mesh->operator[](mesh->size() - 2 - i).Position - ver.Position)));
								if (glm::angle(nor, mesh->at(mesh->size() - i - 3).Normal) < 90)mesh->at(mesh->size() - i - 3).Normal = nor;
								mesh->at(mesh->size() - i - 3).Normal = -nor;
								mesh->insert(mesh->end() - i, mesh->operator[](mesh->size() - i - 1));
							}
							mesh->push_back(ver1);
							mesh->push_back(ver);
							glm::vec3 nor = glm::vec3(glm::cross((mesh->operator[](mesh->size() - 3).Position - ver.Position), (mesh->operator[](mesh->size() - 2).Position - ver.Position)));
							if (glm::angle(nor, mesh->operator[](mesh->size() - 3).Normal) < 90)mesh->at(mesh->size() - 3).Normal = nor;
							else mesh->at(mesh->size() - 3).Normal = -nor;
						}
						break;
					}
					else Num += c;
				}
			}
			else
			{
				while (1)
				{
					c = *file;
					file++;
					if (c == '\n')break;
				}
			}
			break;
		case'g':
			c = *file;
			file++;
			if (c == ' ')
			{
				Num = "";
				while (1)
				{
					c = *file;
					file++;
					if (c == '\n')break;
					Num += c;
				}
				meshes.AddNode(Mesh());
				meshNum++;
				printf_s("��ʼ������%d����ģ��%s\n", meshNum, Num.c_str());
				meshes.FindNode(meshNum)->data.Name = Num;
				Num = "";
			}
			else if (c == '\n')continue;
			else
			{
				while (1)
				{
					c = *file;
					file++;
					if (c == '\n')break;
				}
			}
			break;
		case'\n':
			continue;
		case'#':
			while (1)
			{
				c = *file;
				file++;
				if (c == '\n')break;
			}
			break;
		case'o':
			c = *file;
			file++;
			if (c == ' ')
			{
				Num = "";
				while (1)
				{
					c = *file;
					file++;
					if (c == '\n')break;
					Num += c;
				}
				if (Name == "")Name = Num;
				meshes.AddNode(Mesh());
				meshNum++;
				printf_s("��ʼ������%d����ģ��%s\n", meshNum, Num.c_str());
				meshes.FindNode(meshNum)->data.Name = Num;
				Num = "";
			}
			else
			{
				while (1)
				{
					c = *file;
					file++;
					if (c == '\n')break;
				}
			}
			break;
		case'm':
			Num = "";
			for (int i = 0; i < 6; i++)
			{
				c = *file;
				file++;
				if (c == '\n')break;
				Num += c;
			}
			if (Num == "tllib ")
			{
				Num = "";
				while (1)
				{
					c = *file;
					file++;
					if (c == '\n')break;
					Num += c;
				}
				printf_s("���ʵ�ַΪ%s\n",(directory + Num).c_str());
				Num = "";
			}
			else
			{
				while (1)
				{
					if (c == '\n')break;
					c = *file;
					file++;
				}
			}
			Num = "";
			break;
		}
	}
	return 1;
}
bool Model::loadModel(std::string path)
{
	std::string suffix;
	directory = path.substr(0, path.find_last_of('/'));
	suffix = path.substr(path.find_last_of('.'));
	if (suffix == ".obj")
	{
		return loadobj(path);
	}
	else
	{
		MessageBox(NULL, TEXT("��֧�ִ˸�ʽ���ļ�"), TEXT("����"), MB_OK);
		return 0;
	}
}