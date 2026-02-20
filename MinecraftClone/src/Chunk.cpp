#include "Chunk.h"

Chunk::Chunk(glm::vec3 pos)
	: position(pos) {
	indexCount = 0;
    // generate and build chunk immediately so it's ready to render
    GenBlocks();
    BuildChunk();

    dirtTexture = Texture("src/Textures/DirtText.jpg");
    if (!dirtTexture.LoadTexture()) {
        std::cout << "Warning: failed to load texture 'src/Textures/DirtText.jpg'\n";
    }
    dirtTexture.CompileTexture();
}

void Chunk::GenChunk() {

}

//Will generate the appropriate block faces and will be added to vector, inapproparites will be culled in BuildChunk
void Chunk::GenBlocks() {
    for (int i = 0; i < 3; i++) {
        Block block(glm::vec3(i, 0, 0));
        
        // 6 yüzeyi bir diziye alýyoruz ki kod kalabalýðý bitsin
        FaceData faces[6] = {
            block.GetFace(FRONT), block.GetFace(BACK),
            block.GetFace(RIGHT), block.GetFace(LEFT),
            block.GetFace(TOP),   block.GetFace(BOTTOM)
        };

        // 6 Yüzey için döngü
        for (int f = 0; f < 6; f++) {
            // Her yüzeyin 4 köþesi (vertex) için döngü
            for (int v = 0; v < 4; v++) {
                
                // 1. POZÝSYON (X, Y, Z)
                chunkVerts.push_back(faces[f].vertices[v].x);
                chunkVerts.push_back(faces[f].vertices[v].y);
                chunkVerts.push_back(faces[f].vertices[v].z);

                // 2. UV (U, V) - Pozisyonun HEMEN ardýna ekliyoruz!
                chunkVerts.push_back(faces[f].uv[v].x);
                chunkVerts.push_back(faces[f].uv[v].y);

            }
        }

        // 6 yüzey ekledik, indeksleri güncelle
        AddIndices(6);
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
	dirtTexture.UseTexture();
    int shaderID = shaderProgram.GetShaderID();
    int texLoc = glGetUniformLocation(shaderID, "texture1");
    if (texLoc >= 0) glUniform1i(texLoc, 0); // set sampler to texture unit 0
	
	chunkMesh.RenderMesh(); // Render the chunk mesh
}

Chunk::~Chunk() {
}