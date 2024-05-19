#ifndef __CIRCLE_BUFFER_H__
#define __CIRCLE_BUFFER_H__

//------------------- INCLUDES ----------------------------
//------------------- DEFINES -----------------------------
//------------------- STRUCTURES --------------------------
//------------------- VARIABLES ---------------------------
//------------------- FUNCTIONS ---------------------------
class CircleBuffer{
	public:
		CircleBuffer(const unsigned int size);
		~CircleBuffer(void);
		void disable(void);
		void appendData(char data);
		void appendData(unsigned char data);
		void appendData(short data);
		void appendData(unsigned short data);
		void appendData(int data);
		void appendData(unsigned int data);
		unsigned int available(void);
		unsigned char isFull(void);
		unsigned char isEmpty(void);
		void clear(void);
		inline unsigned int size(void){ return m_size; }
		char readData_8(const unsigned offset = 0, const unsigned char increment = 1);
		unsigned char readData_u8(const unsigned offset = 0, const unsigned char increment = 1);
		short readData_16(const unsigned offset = 0, const unsigned char increment = 1);
		unsigned short readData_u16(const unsigned offset = 0, const unsigned char increment = 1);
		int readData_32(const unsigned offset = 0, const unsigned char increment = 1);
		unsigned int readData_u32(const unsigned offset = 0, const unsigned char increment = 1);
	private:
		unsigned char readByte(const unsigned offset = 0, const unsigned char increment = 1);
		void* m_pBuffer;
		unsigned int m_rIndx;
		unsigned int m_wIndx;
		unsigned int m_size;
		unsigned int m_bufferMask;
};

#endif //__CIRCLE_BUFFER_H__
