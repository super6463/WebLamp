void buttonTick() {
  btn.tick();

  // клики
  switch (btn.hasClicks()) {
    case 1:   // сменить цвет
      data.color += 16;
      sendPacket();
      memory.update();
      break;
    case 2:   // подмигнуть
      winkFlag = 1;
      sendPacket();
      break;
    case 3:
     rad_on=2;
     sendPacket();
      memory.update();
      break;
    break;
    case 4:
    data.power = !data.power;
      sendPacket();
      memory.update();
      break;
  }
  // импульсное удержание
  static int8_t dir = 10;
  if (btn.step()) {
    data.bright = constrain(data.bright + dir, 5, 255);
    if (data.bright == 255) {
      FastLED.setBrightness(10);
      FastLED.show();
      delay(150);
      FastLED.setBrightness(255);
      FastLED.show();
      delay(150);
    }
  }
  if (btn.releaseStep()) {
    dir = -dir;
    memory.update();
  }
}
