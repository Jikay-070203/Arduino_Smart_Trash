# 🚀 Automatic Trash Bin using Ultrasonic Sensor & Servo Motor

This project is an **automatic trash bin** that opens its lid when an object (e.g., a hand or waste) is detected within **10 cm** of the sensor and closes it after **2 seconds**.

## 📌 How It Works?
1. The **ultrasonic sensor** (HC-SR04) measures the distance of an object in front of the bin.
2. If an object is detected within **10 cm**, the servo motor rotates to open the lid.
3. The lid remains open for **2 seconds** and then automatically closes.
4. The system continuously monitors the distance to detect new objects.

## 🛠 Hardware Components
- **Arduino Uno** (or compatible board)
- **HC-SR04 Ultrasonic Sensor** (for distance measurement)
- **Servo Motor (SG90 / MG995)** (to open/close the lid)
- **Wires & Power Supply**

## 🔌 Wiring Diagram
| Component         | Arduino Pin |
|------------------|------------|
| **HC-SR04 Trig** | D8         |
| **HC-SR04 Echo** | D7         |
| **Servo Signal** | D11        |

## 📝 Code Explanation
- **Distance Measurement**: The ultrasonic sensor sends a signal and calculates the time for it to bounce back.
- **Servo Control**: The servo rotates **110°** to open the lid and returns to **0°** after 2 seconds.
- **Auto-Trigger System**: Prevents repeated activation until the cycle is complete.

## 🚀 How to Use?
1. Upload the provided code to your **Arduino** using the **Arduino IDE**.
2. Connect the components as per the wiring diagram.
3. Power on the system and place your hand near the sensor.
4. The bin lid will open automatically and close after **2 seconds**.

## 📜 Arduino Code
```cpp
#include <Servo.h>

// Sensor pins
const int trig = 8;
const int echo = 7;

// Servo pin
const int servoPin = 11;

// Servo angles
#define GOC_DONG 0
#define GOC_MO 110

// Control variables
Servo myservo;
unsigned long autoMillis = 0;
bool autoTrigger = false;

void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  myservo.attach(servoPin);
  myservo.write(GOC_DONG); // Initial closed position
}

void loop() {
  long duration;
  int distance;

  // Send ultrasonic pulse
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  // Read echo time
  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2; // Convert time to distance (cm)

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Open lid if an object is detected within 10 cm
  if (distance > 0 && distance < 10 && !autoTrigger) {
    myservo.write(GOC_MO);
    autoTrigger = true;
    autoMillis = millis();
  }

  // Close lid after 2 seconds
  if (autoTrigger && millis() - autoMillis >= 2000) {
    myservo.write(GOC_DONG);
    autoTrigger = false;
  }

  delay(100); // Reduce frequency to avoid noise
}
