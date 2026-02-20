#include "Block.h"

Block::Block(glm::vec3 pos)
	: position(pos) {


    // UVs for a quad in the same order as vertices: bottom-left, bottom-right, top-right, top-left
    dirtUV.push_back(glm::vec2(0.0f, 0.0f)); // bottom-left
    dirtUV.push_back(glm::vec2(1.0f, 0.0f)); // bottom-right
    dirtUV.push_back(glm::vec2(1.0f, 1.0f)); // top-right
    dirtUV.push_back(glm::vec2(0.0f, 1.0f)); // top-left

	//Transformed vertices
	FaceData faceData;
	faceData.vertices = AddTransformedVertices(FaceDataRaw().rawVertexData[FRONT]);
	faceData.uv = dirtUV;
	faces[FRONT] = faceData;
	faceData.vertices = AddTransformedVertices(FaceDataRaw().rawVertexData[BACK]);
	faceData.uv = dirtUV;
	faces[BACK] = faceData;
	faceData.vertices = AddTransformedVertices(FaceDataRaw().rawVertexData[RIGHT]);
	faceData.uv = dirtUV;
	faces[RIGHT] = faceData;
	faceData.vertices = AddTransformedVertices(FaceDataRaw().rawVertexData[LEFT]);
	faceData.uv = dirtUV;
	faces[LEFT] = faceData;
	faceData.vertices = AddTransformedVertices(FaceDataRaw().rawVertexData[TOP]);
	faceData.uv = dirtUV;
	faces[TOP] = faceData;
	faceData.vertices = AddTransformedVertices(FaceDataRaw().rawVertexData[BOTTOM]);
	faceData.uv = dirtUV;
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