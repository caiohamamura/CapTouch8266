#pragma once
#include <Arduino.h>

class CapTouch8266
{
public:
    CapTouch8266(uint8_t pin, uint8_t bufferSize = 20);

    void begin();
    void calibrate(uint16_t samples = 50);
    void update();
    bool isTouched();

    unsigned long getRaw();
    unsigned long getBaseline();

    void setThresholdOffset(unsigned long offset);
    void setVotePercentage(float pct);
    void setTimeout(unsigned long timeout);
    uint8_t getVoteCount();
    unsigned long getBufferValue(uint8_t index);
    void printDebug(Stream &s);

private:
    unsigned long measure();

    uint8_t _pin;
    uint8_t _bufferSize;
    uint8_t _index;

    unsigned long *_buffer;

    unsigned long _baseline;
    unsigned long _thresholdOffset;
    float _votePct;
    unsigned long _timeout;
};