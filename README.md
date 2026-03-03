# CapTouch8266

Work was done manually, but turned into library through vibe coding.

Lightweight capacitive touch sensing library for **ESP8266** using simple RC timing and `pulseIn()`.

This library allows you to create capacitive touch pads using only:

- 1 resistor (typically 500kΩ–1MΩ)
- A copper pad (or wire / foil)
- No special ICs required

---

## ✨ Features

- ✅ Works on ESP8266 (Arduino framework)
- ✅ Uses simple RC charge timing
- ✅ Adaptive baseline calibration
- ✅ Rolling buffer + statistical voting
- ✅ Adjustable threshold offset
- ✅ Adjustable timeout
- ✅ Debug inspection (raw values + votes)
- ✅ No external dependencies

---

## 🔧 Hardware Setup

Basic circuit:

```
3.3V
  |
  R (500kΩ–1MΩ)
  |
  +---- GPIO (e.g. D1)
  |
  Touch Pad
  |
  (Finger capacitance to GND)
```

### Recommended values

- 500kΩ works
- 1MΩ is more stable
- Optional: 22pF–47pF from pad to GND for increased stability

---

## 📦 Installation (PlatformIO)

### Option 1 — From GitHub

```ini
lib_deps =
  https://github.com/YOUR_USERNAME/CapTouch8266.git
```

### Option 2 — Local Library

Place in:

```
lib/CapTouch8266/
```

---

## 🚀 Basic Usage

```cpp
#include <Arduino.h>
#include <CapTouch8266.h>

CapTouch8266 touch(D1);

void setup() {
  Serial.begin(115200);

  touch.begin();

  Serial.println("Calibrating... Do NOT touch.");
  touch.calibrate();
  Serial.println("Done.");
}

void loop() {
  touch.update();

  if (touch.isTouched())
    Serial.println("Touch!");
  else
    Serial.println("No touch");

  delay(10);
}
```

---

## ⚙ API Reference

### Constructor

```cpp
CapTouch8266(uint8_t pin, uint8_t bufferSize = 20);
```

- `pin` → GPIO pin
- `bufferSize` → number of samples stored for voting

---

### `begin()`

Initializes internal state.

---

### `calibrate(uint16_t samples = 50)`

Measures baseline without touching.

Call this at startup while the pad is untouched.

---

### `update()`

Performs one measurement.

Call once per loop.

---

### `isTouched()`

Returns `true` if enough samples exceed the threshold.

Uses statistical voting to reduce noise.

---

### `setThresholdOffset(unsigned long offset)`

Adjusts sensitivity.

Default: `8`

Increase for less sensitivity.
Decrease for more sensitivity.

---

### `setVotePercentage(float pct)`

Percentage of buffer that must exceed threshold.

Default: `0.2` (20%)

Example:

```cpp
touch.setVotePercentage(0.3); // 30%
```

---

### `setTimeout(unsigned long timeout)`

Timeout passed to `pulseIn()`.

Default: `2000` (microseconds)

---



## 📊 Debug & Inspection API

These functions allow you to inspect internal values for tuning and teaching.

---

### `getRaw()`

Returns the most recent raw measurement.

---

### `getBaseline()`

Returns the calibrated baseline value.

---

### `getVoteCount()`

Returns how many buffer samples are above threshold.

---

### `getBufferValue(uint8_t index)`

Returns a specific buffer value.

---

### `printDebug(Stream &s)`

Prints full diagnostic information to any Arduino `Stream`.

Example:

```cpp
touch.printDebug(Serial);
```

Example output:

```
Baseline: 0 | Threshold: 8 | Votes: 10/20 | Buffer: 2 12 2 15 17 13 5 35 13 15 22 0 0 0 0 0 0 0 15 28
```

## 🧠 How It Works

1. The GPIO pin is driven LOW to discharge capacitance.
2. It is switched to INPUT mode.
3. The resistor pulls the pad HIGH.
4. The time required to cross the digital threshold is measured.
5. Touch increases capacitance → increases rise time.
6. Statistical voting determines touch state.

---

## 📊 Typical Values (500kΩ Example)

Without touch:
```
0 0 0 0 0 0 ...
```

With touch:
```
5 12 15 22 30 ...
```

Set threshold offset accordingly.

---

## 🎮 Ideal For

- IoT classroom experiments
- Multiplayer WebSocket button games
- Low-cost touch interfaces
- DIY capacitive sensors
- Understanding RC physics

---

## ⚠ Limitations

- ESP8266 only (for now)
- Sensitive to wiring length
- Sensitive to environmental noise
- Not a replacement for dedicated capacitive ICs

---

## 📈 Stability Tips

- Use 1MΩ if possible
- Keep wires short
- Add 33pF capacitor to GND if unstable
- Calibrate at startup
- Avoid touching during calibration

---

## 🛣 Roadmap Ideas

- Auto baseline drift compensation
- Long-press detection
- Multi-pad manager
- ESP32 compatibility layer
- Frequency-mode (555 oscillator support)

---

## 📜 License

MIT License

---

## 👨‍🏫 Educational Note

This library intentionally avoids complex hardware to demonstrate how capacitive sensing works using only:

- RC timing
- Digital threshold detection
- Statistical filtering

It is designed to be hackable, understandable, and classroom-friendly.

---

Happy hacking 🚀
