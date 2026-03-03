#include "CapTouch8266.h"

CapTouch8266::CapTouch8266(uint8_t pin, uint8_t bufferSize)
    : _pin(pin),
      _bufferSize(bufferSize),
      _index(0),
      _baseline(0),
      _thresholdOffset(8),
      _votePct(0.2),
      _timeout(2000)
{
    _buffer = new unsigned long[_bufferSize];
}

void CapTouch8266::begin() {
    pinMode(_pin, INPUT);
    for (uint8_t i = 0; i < _bufferSize; i++)
        _buffer[i] = 0;
}

void CapTouch8266::setThresholdOffset(unsigned long offset) {
    _thresholdOffset = offset;
}

void CapTouch8266::setVotePercentage(float pct) {
    _votePct = pct;
}

void CapTouch8266::setTimeout(unsigned long timeout) {
    _timeout = timeout;
}

unsigned long CapTouch8266::measure() {
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
    delayMicroseconds(5);

    pinMode(_pin, INPUT);

    unsigned long val = pulseIn(_pin, HIGH, _timeout);

    if (val == 0 || val >= _timeout)
        return 0;

    return val;
}

void CapTouch8266::update() {
    unsigned long val = measure();
    _buffer[_index] = val;
    _index = (_index + 1) % _bufferSize;
}

bool CapTouch8266::isTouched() {
    uint8_t count = 0;
    unsigned long threshold = _baseline + _thresholdOffset;

    for (uint8_t i = 0; i < _bufferSize; i++) {
        if (_buffer[i] > threshold)
            count++;
    }

    return count >= (_bufferSize * _votePct);
}

void CapTouch8266::calibrate(uint16_t samples) {
    unsigned long sum = 0;

    for (uint16_t i = 0; i < samples; i++) {
        sum += measure();
        delay(5);
    }

    _baseline = sum / samples;
}

unsigned long CapTouch8266::getRaw() {
    return _buffer[(_index == 0 ? _bufferSize : _index) - 1];
}

unsigned long CapTouch8266::getBaseline() {
    return _baseline;
}
