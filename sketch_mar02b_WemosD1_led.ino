// Otetaan käyttöön tarvittava kirjasto WiFin käyttöön
#include <ESP8266WiFi.h>
// Otetaan käyttöön tarvittava kirjasto web-serverille
#include <ESP8266WebServer.h>

//Kerrotaan Wi-Fi verkon nimi ja salasana
char ssid [] = "ICT LABRAx";
char pass [] = "ict2016a";

//Luodaan web-serveri, joka kuuntelee 80-portissa
ESP8266WebServer server (80);

void setup() {
  //Alustetaan sarjaportti
  Serial.begin(115200);

  Serial.println ();
  Serial.print ("Yhdistetään WiFi-verkkoon");
  Serial.println(ssid);

  //Kerrotaan Wi-Fi-kirjastolle että halutaan yhdistää
  //ICT LABRAx-langattomaan verkkoon ja ollaan client
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  //Odotetaan, kunnes ollaan saatu yhteys WiFi-verkkoon
  //ja ip-osoite
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //Tulostetaan konsoliin ip-osoite
   Serial.println("");
   Serial.println("WiFi connected");
   Serial.println("IP address: ");
   Serial.println(WiFi.localIP());

   initWebServer();// Alustetaan web-serverin palvelut

   //Alustetaan gpio4 outputiksi
   pinMode (4, OUTPUT);
}

  void initWebServer()  {
    //Luodaan pääsivu
    server.on("/", []() {
        server.send(200, "text/html", "\
        <html>\
        <a href='/LED_ON'>Aseta ledi ON</a>\
        <br>\
        <a href='/LED_OFF'>Aseta ledi pois OFF</a>\
        </html>\
        ");
    });

    //kutsuttaessa urlia http://IP_OSOITE/LED_ON
    //laitetaan led pois päältä
    server.on("/LED_ON", []() {
        server.send(200, "text/plain", "Led On!!!");
        digitalWrite(4, HIGH);
    });

    //kutsuttaessa urlia http://IP_OSOITE/LED_OFF
    //laitetaan led pois päältä
    server.on("/LED_OFF", []() {
        server.send(200, "text/plain", "Led Off!!!");
        digitalWrite (4, LOW);
    });

    //käynnistetään serveri
    server.begin ();
    Serial.println("HTTP server started");
}
void loop() {
  //Ajetaan web-serveriä aina loop-funktioon tullessa
  //sekä palvellaan web-serverin asiakkaita
  server.handleClient ();
}
