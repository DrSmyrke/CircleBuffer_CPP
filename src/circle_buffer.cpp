//------------------- INCLUDES ----------------------------
#include "circle_buffer.h"
#include <stdlib.h>
//------------------- DEFINES -----------------------------
//------------------- STRUCTURES --------------------------
//------------------- VARIABLES ---------------------------
//------------------- FUNCTIONS ---------------------------
CircleBuffer::CircleBuffer(const unsigned int size) : m_size( size )
{
	m_pBuffer								= nullptr;
	m_bufferMask							= m_size - 1;
	m_rIndx									= 0;
	m_wIndx									= 0;

	m_pBuffer								= malloc( size );
}

//---------------------------------------------------------
CircleBuffer::~CircleBuffer(void)
{
	disable();
}

//---------------------------------------------------------
void CircleBuffer::disable(void)
{
	free( m_pBuffer );
	m_pBuffer								=  nullptr;
	m_size									= 0;
	m_bufferMask							= 0;
	clear();
}

//---------------------------------------------------------
void CircleBuffer::appendData(char data)
{
	char* ptr								= (char*)m_pBuffer;
	ptr[ m_wIndx++ & m_bufferMask ]			= data;
}

//---------------------------------------------------------
void CircleBuffer::appendData(unsigned char data)
{
	unsigned char* ptr						= (unsigned char*)m_pBuffer;
	ptr[ m_wIndx++ & m_bufferMask ]			= data;
}

//---------------------------------------------------------
void CircleBuffer::appendData(short data)
{
	short* ptr								= (short*)m_pBuffer;
	ptr[ m_wIndx++ & m_bufferMask ]			= data;
}

//---------------------------------------------------------
void CircleBuffer::appendData(unsigned short data)
{
	unsigned short* ptr						= (unsigned short*)m_pBuffer;
	ptr[ m_wIndx++ & m_bufferMask ]			= data;
}

//---------------------------------------------------------
void CircleBuffer::appendData(int data)
{
	int* ptr								= (int*)m_pBuffer;
	ptr[ m_wIndx++ & m_bufferMask ]			= data;
}

//---------------------------------------------------------
void CircleBuffer::appendData(unsigned int data)
{
	unsigned int* ptr						= (unsigned int*)m_pBuffer;
	ptr[ m_wIndx++ & m_bufferMask ]			= data;
}

//---------------------------------------------------------
unsigned int CircleBuffer::available(void)
{
	return ( m_wIndx - m_rIndx ) & m_bufferMask;
}

//---------------------------------------------------------
unsigned char CircleBuffer::isFull(void)
{
	return ( ( m_wIndx - m_rIndx ) & ~( m_bufferMask ) ) != 0;
}

//---------------------------------------------------------
unsigned char CircleBuffer::isEmpty(void)
{
	return m_wIndx == m_rIndx;
}

//---------------------------------------------------------
void CircleBuffer::clear(void)
{
	m_rIndx									= 0;
	m_wIndx									= 0;
}

//---------------------------------------------------------
char CircleBuffer::readData_8(const unsigned offset, const unsigned char increment)
{
	return (char)readByte( offset, increment );
}

//---------------------------------------------------------
unsigned char CircleBuffer::readData_u8(const unsigned offset, const unsigned char increment)
{
	return readByte( offset, increment );
}

//---------------------------------------------------------
short CircleBuffer::readData_16(const unsigned offset, const unsigned char increment)
{
	short value = ( (short)readByte( offset, increment ) << 8 ) |  (short)readByte( offset + 1, increment );
	return value;
}

//---------------------------------------------------------
unsigned short CircleBuffer::readData_u16(const unsigned offset, const unsigned char increment)
{
	unsigned short value = ( (unsigned short)readByte( offset, increment ) << 8 ) |  (unsigned short)readByte( offset + 1, increment );
	return value;
}

//---------------------------------------------------------
int CircleBuffer::readData_32(const unsigned offset, const unsigned char increment)
{
	int value = ( (int)readByte( offset, increment ) << 24 ) | ( (int)readByte( offset + 1, increment ) << 16 ) | ( (int)readByte( offset + 2, increment ) << 8 ) | (int)readByte( offset + 3, increment );
	return value;
}

//---------------------------------------------------------
unsigned int CircleBuffer::readData_u32(const unsigned offset, const unsigned char increment)
{
	unsigned int value = ( (unsigned int)readByte( offset, increment ) << 24 ) | ( (unsigned int)readByte( offset + 1, increment ) << 16 ) | ( (unsigned int)readByte( offset + 2, increment ) << 8 ) | (unsigned int)readByte( offset + 3, increment );
	return value;
}

//---------------------------------------------------------
//---------------------------------------------------------
unsigned char CircleBuffer::readByte(const unsigned offset, const unsigned char increment)
{
	unsigned char* ptr						= (unsigned char*)m_pBuffer;
	unsigned char byte = ptr[ ( m_rIndx + offset ) & m_bufferMask ];
	if( increment ) m_rIndx++ & m_bufferMask;
	return byte;
}

//---------------------------------------------------------