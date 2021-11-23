#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &handle);
}

VAO::~VAO()
{
	glDeleteVertexArrays(1, &handle);
}

void VAO::bind()
{
	glBindVertexArray(handle);
}

void VAO::unbind()
{
	glBindVertexArray(0);
}

// Regular buffer initialization
void VAO::genBufferData(VBO* vbo, size_t dataSize, size_t dataStride, void* data)
{
	bind();
	vbo->bind();
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
}

// Automatically sets data to NULL & GL_DYNAMIC_DRAW - used for glMappedBuffers
void VAO::genBufferData(VBO* vbo, size_t dataSize, size_t dataStride)
{
	bind();
	vbo->bind();
	glBufferData(GL_ARRAY_BUFFER, dataSize, NULL, GL_DYNAMIC_DRAW);
}

void VAO::setAttrib(GLuint attributeIndex, size_t attributeSize, GLenum attributeType, size_t dataStride, size_t attributeOffset)
{
	glEnableVertexAttribArray(attributeIndex);
	glVertexAttribPointer(attributeIndex, attributeSize, attributeType, GL_FALSE, dataStride, (const GLvoid*)attributeOffset);
}
