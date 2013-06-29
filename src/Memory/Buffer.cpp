#include "Buffer.h"

#include <cstring>

#include "../System/Log.h"

Buffer::Buffer()
    : buffer(NULL),
      length(0),
      bufferEnd(NULL),
      readLoc(NULL),
      writeLoc(NULL),
      external(false)
{
}

Buffer::Buffer(size_t maxSize)
{
    allocateData(maxSize);
}

Buffer::Buffer(char* buf, int bufferLength)
{
    setBuffer(buf, bufferLength);
}

Buffer::~Buffer()
{
    if (!external)
        delete [] buffer;
    buffer = NULL;
}

void Buffer::allocateData(size_t maxSize)
{
    buffer = new char[maxSize];
    length = maxSize;
    bufferEnd = &buffer[length];

    readLoc = writeLoc = buffer;

    external = false;
}

void Buffer::setBuffer(char* buf, int bufferLength)
{
    buffer = buf;
    length = bufferLength;
    bufferEnd = &buffer[length];

    readLoc = buffer;
    writeLoc = bufferEnd;

    external = true;

    logf("%p, %d", buffer, length);
}

bool Buffer::atEnd()
{
    return readLoc == bufferEnd;
}

size_t Buffer::size()
{
    return (size_t)(bufferEnd - buffer);
}

void Buffer::rewind()
{
    readLoc = buffer;
}

void Buffer::clear()
{
    writeLoc = readLoc = buffer;
}

void Buffer::append(Buffer* b)
{
    memcpy(bufferEnd, b->getBuffer(), b->size());
    writeLoc += b->size();
}

char* Buffer::getBuffer()
{
    return buffer;
}

/*
float Buffer::readFloat()
{
    float f;
    memcpy(&f, readLoc, sizeof(f));
    readLoc += sizeof(f);

    return f;
}

void Buffer::writeFloat(float f)
{
    memcpy(writeLoc, &f, sizeof(f));
    writeLoc += sizeof(f);
}

void Buffer::readVector(Vector2f* v)
{
    float x = readFloat();
    float y = readFloat();

    v->set(x, y);
}

void Buffer::writeVector(float x, float y)
{
    writeFloat(x);
    writeFloat(y);
}

void Buffer::writeVector(const Vector2f& v)
{
    writeVector(v.x, v.y);
}

void Buffer::readColor(Color* c)
{
    float r = readFloat();
    float g = readFloat();
    float b = readFloat();
    float a = readFloat();

    c->set(r, g, b, a);
}

void Buffer::writeColor(float r, float g, float b, float a)
{
    writeFloat(r);
    writeFloat(g);
    writeFloat(b);
    writeFloat(a);
}

void Buffer::writeColor(const Color& c)
{
    writeColor(c.r, c.g, c.b, c.a);
}

void Buffer::dumpBuffer()
{
    rewind();

    while (!atEnd())
    {
        logf("%f", readFloat());
    }
}
*/


