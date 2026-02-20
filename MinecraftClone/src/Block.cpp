#include "Block.h"

Block::Block(glm::vec3 pos)
	: position(pos) {

	//Transformed vertices
	FaceData faceData;
	faceData.vertices = AddTransformedVertices(FaceDataRaw().rawVertexData[FRONT]);
	faces[FRONT] = faceData;
	faceData.vertices = AddTransformedVertices(FaceDataRaw().rawVertexData[BACK]);
	faces[BACK] = faceData;
	faceData.vertices = AddTransformedVertices(FaceDataRaw().rawVertexData[RIGHT]);
	faces[RIGHT] = faceData;
	faceData.vertices = AddTransformedVertices(FaceDataRaw().rawVertexData[LEFT]);
	faces[LEFT] = faceData;
	faceData.vertices = AddTransformedVertices(FaceDataRaw().rawVertexData[TOP]);
	faces[TOP] = faceData;
	faceData.vertices = AddTransformedVertices(FaceDataRaw().rawVertexData[BOTTOM]);
	faces[BOTTOM] = faceData;
}

std::vector<glm::vec3> Block::AddTransformedVertices(const std::vector<glm::vec3>& vertices) {
	std::vector<glm::vec3> transformedVertices;

	for (const auto& vert : vertices) {
		transformedVertices.push_back(vert + position);
	}

	return transformedVertices;
}

Block::~Block() {

}