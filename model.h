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
	/*  网格数据  */
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	/*  函数  */
	Mesh();
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
};
class Model
{
public:
	/*  函数   */
	Model() {}
	Model(const char* path)
	{
		loadModel(path);
	}
	bool loadModel(std::string path);
	LinkList<Mesh> meshes;
	std::string directory;
	std::string Name;
	/*  函数   */
	bool loadobj(std::string path);
};

//link是你希望储存进的链表ab点为对角线，c点确定大小方向，颜色默认为白色
//需要注意，c点对确定正反非常重要
void CreateQuads(TriFLink* link,coordinate a, coordinate b, coordinate c, COLORREF color = RGB(255, 255, 255));
//ab点为底边对角线，c点确定大小方向，d点确定高度颜色默认为白色
void CreateCube(TriFLink* link, coordinate a, coordinate b, coordinate c, coordinate d, COLORREF color = RGB(255, 255, 255));
//快捷创建正方体
void EfficientCube(TriFLink* link, coordinate midpoint, double SideLength = 1, COLORREF color = RGB(255, 255, 255));
//创建球
void CreateBall(TriFLink* link, coordinate locat, double radius, int Fineness);