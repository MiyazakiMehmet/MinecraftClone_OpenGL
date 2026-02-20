#include "Chunk.h"

Chunk::Chunk(glm::vec3 pos)
	: position(pos) {
	indexCount = 0;
    // generate and build chunk immediately so it's ready to render
    GenBlocks();
    BuildChunk();
}

void Chunk::GenChunk() {

}

//Will generate the appropriate block faces and will be added to vector, inapproparites will be culled in BuildChunk
void Chunk::GenBlocks() {
	for (int i = 0; i < 3; i++) {
		Block block(glm::vec3(i, 0, 0));
		FaceData frontFaceData = block.GetFace(FRONT); //Get the FRONT FaceData of the block (it contains vertices, uv, etc. for that face)

        // Append only positions (x,y,z) — no UVs or normals yet
        for (const auto &p : frontFaceData.vertices) {
            chunkVerts.push_back(p.x);
            chunkVerts.push_back(p.y);
            chunkVerts.push_back(p.z);
        }

        AddIndices(1);
	}
}

void Chunk::AddIndices(int amountFace)
{
	for (int i = 0; i < amountFace; i++) {
		chunkIndices.push_back(0 + indexCount);
		chunkIndices.push_back(1 + indexCount);
		chunkIndices.push_back(2 + indexCount);
		chunkIndices.push_back(2 + indexCount);
		chunkIndices.push_back(3 + indexCount);
		chunkIndices.push_back(0 + indexCount);

		indexCount += 4; //Each face has 4 vertices, so we need to increase the index count by 4 for the next face
	}
}

// (ConvertVertsToFloats removed - chunkVerts now stores interleaved floats directly)

void Chunk::BuildChunk() {
    // chunkVerts already contains interleaved floats in the format expected by Mesh
    chunkMesh.CompileMesh(chunkVerts, chunkIndices);
}

void Chunk::Render(Shader shaderProgram) {
    // shaderProgram may be used later (e.g., to set uniforms). For now, just render.
    chunkMesh.RenderMesh(); // Render the chunk mesh
}

Chunk::~Chunk() {
}