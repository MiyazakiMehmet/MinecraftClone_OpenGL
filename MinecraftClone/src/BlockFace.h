#pragma once

#include <vector>
#include <map>
#include <glm.hpp>


enum Faces {
	FRONT,
	BACK,
	LEFT,
	RIGHT,
	TOP,	
	BOTTOM
};

struct FaceData {
	std::vector<glm::vec3> vertices;
};

struct FaceDataRaw {
	std::map<Faces, std::vector<glm::vec3>> rawVertexData{
		{
			FRONT,
			{
				glm::vec3(-0.5f, -0.5f, 0.5f),
				glm::vec3(0.5f, -0.5f, 0.5f),
				glm::vec3(-0.5f, 0.5f, 0.5f),
				glm::vec3(0.5f, 0.5f, 0.5f)
			}
		},
		{
			BACK,
			{
				glm::vec3(0.5f, -0.5f, -0.5f), 
				glm::vec3(-0.5f, -0.5f, -0.5f),
				glm::vec3(-0.5f,  0.5f, -0.5f),
				glm::vec3(0.5f,  0.5f, -0.5f)  
			}
		},
		{
			RIGHT,
			{
				glm::vec3(0.5f, -0.5f,  0.5f), 
				glm::vec3(0.5f, -0.5f, -0.5f), 
				glm::vec3(0.5f,  0.5f, -0.5f), 
				glm::vec3(0.5f,  0.5f,  0.5f)  
			}
		},
		{
			LEFT,
			{
				glm::vec3(-0.5f, -0.5f, -0.5f),
				glm::vec3(-0.5f, -0.5f,  0.5f),
				glm::vec3(-0.5f,  0.5f,  0.5f),
				glm::vec3(-0.5f,  0.5f, -0.5f) 
			}
		},
		{
			TOP,
			{
				glm::vec3(-0.5f,  0.5f,  0.5f),
				glm::vec3(0.5f,  0.5f,  0.5f), 
				glm::vec3(0.5f,  0.5f, -0.5f), 
				glm::vec3(-0.5f,  0.5f, -0.5f) 
			}
		},
		{
			BOTTOM,
			{
				glm::vec3(-0.5f, -0.5f, -0.5f),
				glm::vec3(0.5f, -0.5f, -0.5f), 
				glm::vec3(0.5f, -0.5f,  0.5f), 
				glm::vec3(-0.5f, -0.5f,  0.5f) 
			}
		}
	};
};
