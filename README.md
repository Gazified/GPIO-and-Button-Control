# GPIO and Button Control

An ESP32 sketch, developed in the Arduino IDE, that reads a push button on a GPIO input and drives two LEDs on GPIO outputs. The two LEDs always show opposite states, and the state changes according to the button.

## Objective

- Assemble a button and status LED circuit and run the base behavior.
- Add a second LED that displays the opposite state of the first.
- Demonstrate stable input behavior: the input must not change randomly when the button is released.

## Hardware

| Qty | Component | Purpose |
|---|---|---|
| 1 | ESP32 DevKit | Microcontroller |
| 1 | Push button | Digital input |
| 2 | LED | LED1 (status) and LED2 (opposite state) |
| 2 | 220 Ω resistor | Current limiting, one per LED |
| 1 | Breadboard and jumper wires | Assembly |

## GPIO Connections

| Signal | Pin | Direction | Connection |
|---|---|---|---|
| Push button | GPIO23 | Input (`INPUT_PULLUP`) | One terminal to GPIO23, other terminal to GND |
| LED1 | GPIO18 | Output | GPIO18 → 220 Ω → LED1 anode; LED1 cathode → GND |
| LED2 | GPIO19 | Output | GPIO19 → 220 Ω → LED2 anode; LED2 cathode → GND |

## Circuit Diagram


<img width="808" height="280" alt="Circuit Diagram using Wokwi" src="https://github.com/user-attachments/assets/8c9f2b30-aa11-4a57-8307-4315e7784a46" />


The GPIO connections were drawn and labeled before applying power.

## Behavior

| Button | GPIO23 level | LED1 (GPIO18) | LED2 (GPIO19) |
|---|---|---|---|
| Released | HIGH | ON | OFF |
| Pressed | LOW | OFF | ON |

### Meaning of HIGH and LOW for the button

The button connects GPIO23 to GND, and the internal pull-up resistor is enabled with `INPUT_PULLUP`.

- **HIGH (logic 1, about 3.3 V):** the button is released. The pull-up resistor holds the pin at the supply level because no other path exists.
- **LOW (logic 0, about 0 V):** the button is pressed. The closed contact connects the pin directly to GND and overrides the weak pull-up.

The input is therefore **active-low**: LOW means "pressed". Without the pull-up, the pin would float when the button is released and could read random values. The pull-up guarantees a defined HIGH level in that state, which is why the input does not change randomly when released.

For the outputs, `HIGH` on a GPIO pin drives current through the resistor and LED (LED ON), and `LOW` turns the LED OFF.

## Firmware

The complete source is in [`gpio-button-led-control.ino`](gpio-button-led-control.ino).

- `setup()` enables the internal pull-up on the button pin and configures both LED pins as outputs.
- `setup()` then sets the initial outputs to the "released" state (LED1 ON, LED2 OFF), so the LEDs are in a known state immediately after reset.
- `loop()` reads the button with `digitalRead()` and uses a single if/else to set both LEDs. Because both outputs are written together in each branch, the LEDs can never show the same state.

### Initial state after reset

After pressing the board's reset (EN) button with the push button released, the expected outputs are **LED1 ON** and **LED2 OFF**.

## Build and Upload (Arduino IDE)

1. Install the Arduino IDE.
2. Open **Boards Manager** and install **esp32 by Espressif Systems**.
3. Open `gpio-button-led-control.ino`. The sketch folder name must match the `.ino` file name, which is the case in this repository.
4. Select **Tools → Board → ESP32 Arduino → ESP32 Dev Module**.
5. Select the board's port under **Tools → Port**.
6. Click **Upload**. If the upload stalls at "Connecting...", hold the board's BOOT button until it starts.

The circuit can also be simulated in Wokwi: create an ESP32 project, paste the sketch into the code editor, and replace the project's `diagram.json` with the one in this repository.

## Verification

Record what is actually observed after running the circuit.

| Test | Condition | Expected GPIO23 | Expected LED1 | Expected LED2 | Observed |
|---|---|---|---|---|---|
| T1 | Power-on / reset, button released | HIGH | ON | OFF | |
| T2 | Button pressed and held | LOW | OFF | ON | |
| T3 | Button released after T2 | HIGH | ON | OFF | |
| T4 | Button untouched for 30 s | HIGH, no random changes | ON | OFF | |
| T5 | Reset while button is held | LOW | OFF | ON | |

**Success criteria:** the two LEDs always show opposite states, and the input does not change randomly while the button is released.

## Demonstration and Expected Output:

https://drive.google.com/file/d/1wVsgHOQrneVF-fxCeRIbFvl9CvJqatQZ/view?usp=sharing








