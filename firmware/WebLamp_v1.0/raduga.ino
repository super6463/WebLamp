bool raduga() {
  if (data.power) {
  while (rad_on!=0) {
  memory.tick();
  mqttTick();
  portal.tick();
  checkPortal();
  FastLED.setBrightness(data.bright);
  FastLED.show();
  if (rad_on!=0){
  if (rad_on==1){    
  for (int i = 0; i < LED_AMOUNT; i++) {
    leds[i].setHue(counter + i * 255 / LED_AMOUNT);
  }
  }
  if (rad_on==2){    
  for (int i = 0; i < LED_AMOUNT; i++) {
    leds[i].setHue(counter + 255);
  }
  }
  counter++;
  FastLED.show();
  delay(delayr);
  }
  btn.tick();
  switch (btn.hasClicks()) {
    case 1:
    if (del==0)delayr-=20;
    if (del==1)delayr+=20;
    if (delayr == 123) {
     FastLED.setBrightness(10);
     FastLED.show();
     delay(150);
     FastLED.setBrightness(255);
     FastLED.show();
     delay(150);
     del=0;
     }
     if (delayr == 3) 
     {
     FastLED.setBrightness(10);
     FastLED.show();
     delay(150);
     FastLED.setBrightness(255);
     FastLED.show();
     delay(150);
     del=1;
     }
     sendPacket();
     memory.update();
     break;
    case 2:
     if (rad_on==1)rad_on++;
     else rad_on--;
     sendPacket();
     memory.update();
     break;
    case 3:
     rad_on=0;
     sendPacket();
     break;
    case 4:
     rad_on=0;
     data.power = !data.power;
     sendPacket();
     memory.update();
     break;
    case 5:
     winkFlag = 1;
     sendPacket();
     memory.update();
  }
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
}}
