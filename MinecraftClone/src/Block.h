#pragma once

#include "BlockFace.h"

#include <iostream>
#include <glm.hpp>
#include <vector>
#include <map>

class Block {
private:
	glm::vec3 position;
	std::map<Faces, FaceData> faces;
public:
	Block(glm::vec3 pos);

	std::vector<glm::vec3> AddTransformedVertices(const std::vector<glm::vec3>& vertices);

	inline FaceData GetFace(Faces face) { return faces[face]; }

	~Block();
};