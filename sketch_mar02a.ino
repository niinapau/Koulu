void setup() {
  // Kerrotaan mikrokontrollerille, että gpio4/D2 on output
  pinMode (4, OUTPUT);

}

void loop() {
  // Sammutetaan LED ja odotetaan 4s
  digitalWrite (4, LOW);
  delay(4000);

  // Laitetaan LED päälle ja odotetaan 1s
  digitalWrite (4, HIGH);
  delay(1000);

}
