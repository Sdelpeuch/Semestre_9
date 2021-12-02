#ifndef TD_RING_BUFFER_H
#define TD_RING_BUFFER_H
#define RING_BUFFER_SIZE 64


struct RingBuffer{
    unsigned char buffer[RING_BUFFER_SIZE];
    unsigned char* read;
    unsigned char* write;
};

void ringBufferInit(struct RingBuffer* rb);
unsigned char ringBufferRead(struct RingBuffer* rb);
void ringBufferWrite(struct RingBuffer* rb, unsigned char c);
int ringBufferAvailable(struct RingBuffer* rb);


#endif //TD_RING_BUFFER_H
