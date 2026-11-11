# Prepare your board

Use one ESP32 and a USB data cable. No sensors are required. Install Arduino
IDE and ESP32 board support. All libraries used by the sketch come with the
board package; WiFiManager is not needed.

## Download and personalize the sketch

1. Open the class repository on GitHub, choose **Code → Download ZIP**, and
   extract it on your computer. Open
   [ESPNow_Block_Network.ino](../firmware/ESPNow_Block_Network/ESPNow_Block_Network.ino).
2. Change this line in your local copy:

   ```cpp
   const char OWNER_NAME[] = "lastname_firstname";
   ```

   Enter your own name, such as `cruz_juan`. Use no spaces and at most
   31 characters. The shared sketch stops at startup if the placeholder is left in place.
3. Keep `RADIO_CHANNEL = 1`, `MAGIC = 0xB10C2026`, and the message layout
   unchanged. Everyone testing together needs this same 40-byte owner-name version.
   The older 8-byte and 28-byte sketches are incompatible.

Only the owner name differs between students. Keep your local name edit out
of your results pull request.

## Verify and upload

1. Connect your board and select its current port.
2. Select the board profile that matches your hardware:

   | Board | Common Arduino IDE selection |
   | :--- | :--- |
   | Standard ESP32-WROOM-32 development board | ESP32 Dev Module |
   | Generic ESP32-S3 development board | ESP32S3 Dev Module |

   Use the manufacturer's exact profile when one is supplied. On an S3
   using native USB, Serial Monitor may require **USB CDC On Boot** to be enabled.
3. Click **Verify**, then **Upload**. Open Serial Monitor at **115200 baud**.
4. Press and release **EN/RESET**. Check for your name, your actual board
   MAC, channel `1`, and `ESP-NOW ready`.
5. Test with another board running the same version. Zero boards heard
   while testing alone is normal.

The sketch does not connect the ESP32 to a router or hotspot. It creates no
custom tasks or queues; a short lock protects the shared list while messages
arrive. If the list-full warning appears, the stored results are incomplete.

The code compiled for ESP32 Dev Module and ESP32S3 Dev Module with native USB
CDC enabled using ESP32 Arduino core 3.3.12. A successful compile does not
prove that two physical boards can communicate. Check that before your window.

If something fails, use [the troubleshooting guide](troubleshooting.md).
Next: [collect your results during the block session](block-session.md).
Return to [the class starting page](../README.md).
