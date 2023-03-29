# Stand-up reminder

Stand up reminder is a device to prevent sedentary behavior. This project is written in C++ and runs on an Arduino microcontroller.

## How it works

The device uses an ultrasonic sensor to detect if a person is sitting on a chair and, if they are, starts a timer to measure how long they remain seated(30 min). If the person sits for too long, the device emits a sound to remind them to stand up and move around. Additionally, the device provides visual feedback through a multifunction shield.

## Requirements

### Hardware

To build this device, the following items are required:

- Arduino microcontroller (Arduino UNO R3 was used)
- Arduino Multifunction Shield (for Arduino Uno R3)
- Ultrasonic sensor (HC-SR04 model was used)
- Real Time Clock Module  (DS3231 model was used)

### Software

This project requires the following libraries to run:

- [Multi Function Shield Library by Hpsaturn](https://registry.platformio.org/libraries/hpsaturn/MultiFuncShield)
- [NewPing by Tim Eckel](https://registry.platformio.org/libraries/teckel12/NewPing)
- [RTClib by Adafruit Industries](https://registry.platformio.org/libraries/adafruit/RTClib)

### Developer Notes

- Developed using [Visual Studio Code with development containers](https://code.visualstudio.com/docs/devcontainers/containers)(optional). With custom [devcontainer](https://gist.github.com/jhordyess/07f126d2017bb99bcfca9cffc62162bc) configuration file.
- Developed using the [PlatformIO extension](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide).
- If you are running in Linux, you could also need the correct permission ```sudo chmod o+rw /dev/ttyACM0```.

## To-Do

- Add reset button feature.
- Add wiring diagram.
- Add installation steps.
- Add more to-do's.

## Inspiration link 🤔

Don't worry, it's not spam, just know that it is necessary to pay attention to the sedentary work of the programmer.

- <https://www.popsci.com/health/exercise-sitting-work>

## License

© 2022> [Jhordyess](https://github.com/jhordyess). Under the [MIT](https://choosealicense.com/licenses/mit/) license.

---

Made with 💪 by [Jhordyess](https://www.jhordyess.com/)
