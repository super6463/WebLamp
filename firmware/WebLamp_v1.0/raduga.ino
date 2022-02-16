bool raduga() {
  uint8_t curBr = data.power ? (255 ? 255 : 255) : 0;
  while (rad_on!=0) {
  if (data.power) {
  if (rad_on!=0){  
  memory.tick();
  mqttTick();
  portal.tick();
  checkPortal();
  FastLED.setBrightness(data.bright);
  FastLED.show();
  if (rad_on==1){    
  for (int i = 0; i < LED_AMOUNT; i++) {
    leds[i].setHue(counter + i * 255 / LED_AMOUNT);
    }
  }
   //if (rad_on==2){    
  //for (int i = 0; i < LED_AMOUNT; i++) {
    //fill_color(counter + 255);
  //}
  if (rad_on==2){
    CRGB ncol = CHSV(counter++, 255, curBr);
    CRGB ccol = leds[0];
    if (ccol != ncol) ccol = blend(ccol, ncol, 17);
    fill_solid(leds, LED_AMOUNT, ccol);
  }
 
  counter++;
  FastLED.show();
  memory.update();  
  delay(delayr);
  }
  }
  else rad_on=0;
  btn.tick();
  switch (btn.hasClicks()) {
    case 1:
    if (delayr >= 63) {
     FastLED.setBrightness(10);
     FastLED.show();
     delay(150);
     FastLED.setBrightness(255);
     FastLED.show();
     delay(150);
     del=0;
     }
     if (delayr <= 3) 
     {
     FastLED.setBrightness(10);
     FastLED.show();
     delay(150);
     FastLED.setBrightness(255);
     FastLED.show();
     delay(150);
     del=1;
     }
    if (del==0)delayr-=10;
    if (del==1)delayr+=10;
     sendPacket();
     memory.update();
     break;
    case 2:
     rad_on--;
     sendPacket();
     break;
    case 3:
     winkFlag = 1;
      FastLED.setBrightness(data.bright);
      FastLED.show();
      delay(200);
      FastLED.setBrightness(data.bright-50);
      FastLED.show();
      delay(200);
     sendPacket();
     memory.update();
     break;
    case 4:
     rad_on=0;
     data.power = !data.power;
     sendPacket();
     memory.update();
     break;

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
}
