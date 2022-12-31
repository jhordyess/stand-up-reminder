# Stand-up reminder

Stand up reminder with Arduino Multifunction Shield, Real Time Clock Module, and Ultrasonic Distance Sensor.

## Dev Info

- Arduino Uno R3
- Arduino Multifunction Shield (for Arduino Uno R3)
- Ultrasonic Distance Sensor
- Real Time Clock Module
- [Multi Function Shield Library by Hpsaturn](https://registry.platformio.org/libraries/hpsaturn/MultiFuncShield)
- [NewPing by Tim Eckel](https://registry.platformio.org/libraries/teckel12/NewPing)
- [RTClib by Adafruit Industries](https://registry.platformio.org/libraries/adafruit/RTClib)
- [PlatformIO Core (CLI)](https://docs.platformio.org/en/latest/core/index.html#platformio-core-cli)
- VSCode with [remote containers](https://code.visualstudio.com/docs/remote/containers)

## My useful PlatformIO commands

```bash
# Initialize project for Arduino Uno R3
pio project init --board uno --ide vscode
# Build
pio run
# Upload
pio run -t upload
# Connect to the serial port monitor
pio device monitor
# Enable serial port permissions for linux
sudo chmod o+rw /dev/ttyACM0
```

## License

© 2022 [Jhordyess](https://github.com/jhordyess). Under the [MIT](https://choosealicense.com/licenses/mit/) license.

---

Made with 💪 by [Jhordyess](https://www.jhordyess.com/)
