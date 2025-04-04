# Classroom-DoorLock-System
# 🚪 ESP32 Blynk-Based Door Lock System  

## 📌 Overview  
This project implements a **smart door lock system** using an **ESP32 microcontroller**, **Blynk** for remote control, and **ThingSpeak** for cloud data logging.  

### 🔹 Features  
✅ **Blynk Integration** – Unlock/lock via a mobile app  
✅ **PIR Sensor** – Detects motion and unlocks the door  
✅ **ThingSpeak** – Logs lock status & motion data  

---

## 🛠 Components Used  
- **ESP32** (Microcontroller)  
- **Servo Motor** (Door lock mechanism)  
- **PIR Sensor** (Motion detection)  
- **Blynk App** (Remote control)  
- **ThingSpeak** (Cloud data logging)  

---

## 🚀 Installation & Setup in VS Code (Using Wokwi)  

### **1️⃣ Install VS Code & Extensions**  
1. Download and install **[VS Code](https://code.visualstudio.com/)**  
2. Install the **PlatformIO Extension** (for ESP32 programming)  
3. Install the **Wokwi Extension** (for online simulation)  

---

### **2️⃣ Setting Up Wokwi Simulation**  
1. Open **VS Code**  
2. Click on **Wokwi Extension** (🛠️ icon in the sidebar)  
3. Select **"New Project" → Choose ESP32**  
4. Copy & Paste the provided **Arduino Code** into `main.cpp`  
5. Add the required libraries:  
   - `WiFi.h`  
   - `BlynkSimpleEsp32.h`  
   - `ESP32Servo.h`  
   - `HTTPClient.h`  

---

### **3️⃣ Running the Simulation**  
1. **Start Wokwi Simulation**  
   - Click **"Run"** ▶️ in the Wokwi Extension  
   - The ESP32 will connect to WiFi (Wokwi-GUEST)  
2. **Control the Door Lock**  
   - Open the **Blynk App**  
   - Tap **"Unlock"** or **"Lock"** buttons  
   - Observe **servo movement & serial monitor**  
3. **Check ThingSpeak Data**  
   - Open **ThingSpeak Channel**  
   - See lock & motion updates in real time  

---

## ⚙️ How It Works  
| Action | ESP32 Response | Output |
|--------|--------------|---------|
| WiFi Connects | ✅ "WiFi Connected!" | Serial Monitor |
| **Blynk Unlock Pressed** | 🔓 Door Unlocks | "Door Unlocked via Blynk" |
| **Blynk Lock Pressed** | 🔒 Door Locks | "Door Locked via Blynk" |
| **Motion Detected (PIR HIGH)** | 🚶 Auto-Unlock | "Motion Detected! Unlocking door..." |
| **No Motion (PIR LOW)** | 🏠 No Change | "No Motion Detected." |
| **ThingSpeak Update** | ✅ Sent to Cloud | Data Logged |

---

## 🔧 Customization  
- Change **Blynk Auth Token** (Get from Blynk App)  
- Modify **WiFi SSID & Password** (For real use)  
- Adjust **Servo Angles** (`0°` Unlock, `90°` Lock)  

---

## 🛠 Troubleshooting  
❌ **WiFi Not Connecting?** → Check network credentials  
❌ **Blynk Not Working?** → Ensure App & Server are online  
❌ **ThingSpeak Not Updating?** → Verify API key  

---

🎯 **Now you can control your door remotely!** 🚀  
