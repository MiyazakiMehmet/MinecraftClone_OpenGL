#pragma once

#include "Shader.h"
#include "Block.h"
#include "Mesh.h"
#include "Texture.h"

#include <iostream>
#include <vector>
#include <glm.hpp>
#include <map>

class Chunk {
private:
	Mesh chunkMesh;
	Texture dirtTexture;

    // interleaved vertex data: position(3), uv(2), normal(3) per vertex
    std::vector<float> chunkVerts;
	std::vector<unsigned int> chunkIndices;

	glm::vec3 position;
	int indexCount;

	const int SIZE = 16;
	const int HEIGHT = 32;
public:
	Chunk(glm::vec3 position);
	
	void GenChunk(); //Generates the data
	void GenBlocks(); //Generate the appropriate block faces given data
	void AddIndices(int amountFace); //Add the indices for rendering
	void BuildChunk(); //Take data and process it for rendering
    // (no conversion needed; chunkVerts stores floats already)
    void Render(Shader shaderProgram); //Drawing the Chunk
	
	~Chunk();
};