#include "pch.h"
#include "IndexBuffer.h"

namespace tiger {

	IndexBuffer::IndexBuffer() {
		glGenBuffers(1, &m_BufferID);
	}

	IndexBuffer::IndexBuffer(unsigned int* data, int amount){
		glGenBuffers(1, &m_BufferID);
		load(data, amount);
	}

	IndexBuffer::~IndexBuffer() {
		glDeleteBuffers(1, &m_BufferID);
	}
	void IndexBuffer::bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
	}
	void IndexBuffer::unbind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void IndexBuffer::load(unsigned int* data, int amount) {
		m_Count = amount;

		bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, amount * sizeof(unsigned int), data, GL_STATIC_DRAW);
	}

}