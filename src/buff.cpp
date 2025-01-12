#include "buff.hpp"

void Buffer::bind() {
  glBindBuffer(this->type, this->handle);
}

void Buffer::initialize(unsigned int type, unsigned int usage, unsigned int size, void *data) {
  glGenBuffers(1, &this->handle);
  glBindBuffer(type, this->handle);
  glBufferData(type, size, data, usage);

  this->type = type;
  this->usage = usage;
  this->size = size;
}

void Buffer::unbind() {
  glBindBuffer(this->type, 0);
}

void Buffer::update(void *data, int idx) {
  glBindBuffer(this->type, this->handle);
  glBufferSubData(this->type, idx, this->size, data);
}

void Buffer::destroy() {
  glDeleteBuffers(1, &this->handle);
}

Buffer::~Buffer() {
  this->destroy();
}
