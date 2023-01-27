#pragma once
#include<vector>
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>
#include<string>
#include"LinkList.h"
#include<windows.h>
#include <cstring>
#include"datalink.h"
glm::vec3 str_vec3(std::string str);
struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};
struct Texture {
	unsigned int id;
	std::string type;
};
class Mesh {
public:
	std::string Name;
	/*  ��������  */
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	/*  ����  */
	Mesh();
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
};
class Model
{
public:
	/*  ����   */
	Model() {}
	Model(const char* path)
	{
		loadModel(path);
	}
	bool loadModel(std::string path);
	LinkList<Mesh> meshes;
	std::string directory;
	std::string Name;
	/*  ����   */
	bool loadobj(std::string path);
};

//link����ϣ�������������ab��Ϊ�Խ��ߣ�c��ȷ����С������ɫĬ��Ϊ��ɫ
//��Ҫע�⣬c���ȷ�������ǳ���Ҫ
void CreateQuads(TriFLink* link,coordinate a, coordinate b, coordinate c, COLORREF color = RGB(255, 255, 255));
//ab��Ϊ�ױ߶Խ��ߣ�c��ȷ����С����d��ȷ���߶���ɫĬ��Ϊ��ɫ
void CreateCube(TriFLink* link, coordinate a, coordinate b, coordinate c, coordinate d, COLORREF color = RGB(255, 255, 255));
//��ݴ���������
void EfficientCube(TriFLink* link, coordinate midpoint, double SideLength = 1, COLORREF color = RGB(255, 255, 255));
//������
void CreateBall(TriFLink* link, coordinate locat, double radius, int Fineness);