#include "renderer.h"

Renderer::Renderer()
{
	shader = new Shader("res/shaders/basic.vert", "res/shaders/basic.frag");
	init();
}

Renderer::~Renderer()
{
	if (shader != NULL)
		delete shader;
	shader = NULL;
}

void Renderer::addParticlesToRenderQueue(ParticleHandler* pHandler)
{
	map_buffer();
	for (glm::vec2 i : pHandler->getRenderQueue())
	{
		vertexBuffer->x = i.x;
		vertexBuffer->y = i.y;
		Particle p = *pHandler->get_p(i.x, i.y);
		vertexBuffer->r = p.color.r;
		vertexBuffer->g = p.color.g;
		vertexBuffer->b = p.color.b;
		vertexBuffer++;
	}
	unmap_buffer();
}

void Renderer::render(ParticleHandler* pHandler)
{
	vao.bind();
	glDrawArrays(GL_POINTS, 0, pHandler->getActiveParticles());
	vao.unbind();
}

void Renderer::init()
{
	shader->enable();
	glPointSize(particleSize);
	glEnable(GL_PROGRAM_POINT_SIZE);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // set background to black

	vao.genBufferData(&vbo, (size_t)buffer_size, (size_t)vertex_size);
	vao.setAttrib(0, 2, GL_FLOAT, vertex_size, (size_t)0);
	vao.setAttrib(1, 3, GL_FLOAT, vertex_size, (size_t)(2*sizeof(float)));
	vbo.unbind();
	vao.unbind();
	//shader->disable();
}

void Renderer::map_buffer()
{
	vbo.bind();
	vertexBuffer = (VertexData*)glMapBuffer(vbo.type, GL_WRITE_ONLY);
}

void Renderer::unmap_buffer()
{
	glUnmapBuffer(GL_ARRAY_BUFFER);
	vbo.unbind();
}
