#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "iot";
const char* password = "iotiotiot";
HTTPClient http;
String TOKEN = "";
int RESPONSE;
String urlToken = "http://iot-auth-api.herokuapp.com/iot/auth";
String urlEnvio= "http://iot-auth-api.herokuapp.com/iot/data";
int var = 0;
 
void setup () {
 
Serial.begin(115200);
WiFi.begin(ssid, password);
 
while (WiFi.status() != WL_CONNECTED) {
 
delay(1000);
Serial.print("Conectando..");
Serial.print("\n");
 
}
Serial.print("Conectado!");
Serial.print("\n");
obterToken();
}
void loop() {
 
if (WiFi.status() == WL_CONNECTED) {
   
   if(TOKEN){
    enviarDados();
     if(RESPONSE == 401){
      obterToken();
      }
   }else{
    obterToken();
    }
 
 var ++;
 
http.end(); 
 
}
 
delay(1500); 
 
}

void obterToken(){

  Serial.print("Obtendo Token de autenticação!");
  Serial.print("\n");
  http.begin(urlToken);
  int httpCode = http.GET();  
  TOKEN = http.getString(); 
  Serial.println("Token recebido: " + TOKEN);
  Serial.print("\n");
  
}

void enviarDados(){

    Serial.println("Enviando os dados coletados...");
    http.begin(urlEnvio +"/" + var);
    http.addHeader("Authorization",TOKEN);

    RESPONSE = http.POST("");
    Serial.println("Resposta do Servidor: ");
    Serial.println(RESPONSE);
    Serial.print("\n");
  }
