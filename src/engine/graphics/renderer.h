#ifndef RENDERER_H
#define RENDERER_H

#include "../glHeader.h"
#include "shader/shader.h"
#include "texture/texture.h"
#include "../particle/pencil.h"
#include "buffers/VAO.h"
#include "buffers/VBO.h"

class Renderer
{
private:
	VertexData* vertexBuffer;
	VAO vao;
	VBO vbo;
public:
	Shader* shader;

public:
	Renderer();
	Renderer(const char* vertex_path, const char* fragment_path);
	~Renderer();

	void addParticlesToRenderQueue(ParticleHandler* pHandler);
	void render(ParticleHandler* pHandler);
	Shader* getShader() { return shader; };
	GLuint getVAO() { return vao.handle; };
	GLuint getVBO() { return vbo.handle; };
private:
	void init();
	void map_buffer();
	void unmap_buffer();
};

#endif // !RENDERER_H
