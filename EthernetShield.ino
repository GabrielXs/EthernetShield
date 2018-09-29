//Program: Arduino Ethernet Shield
//Author: Gabriel Xavier

#include<Ethernet.h>

//Define IP, MAC, Mascara de rede e gateway
byte mac[] ={0xDE, 0xAD, 0xBE, 0xEF, 0xED};

IPAddress ip(192,168,1,2); //Endereço de IP
IPAddress gateway(192,168,1,1); //Gateway Padrão
IPAddress subnet(255,255,255,0); //Mascara de Sub-Rede

//Inicializa na porta 80
EthernetServer server(80);


void setup() {
  Ethernet.begin(mac,ip,gateway,subnet);
  server.begin(); 
}

void loop() {
  //Aguardando conexao do browser
  EthernetClient client = server.available();
  if(client){
    Serial.println("New Client");
    // uma solicitação http termina com uma linha em branco
    boolean currentLineIsBlank = true;
    while(client.connected()){
       if(client.available()){
        char c = client.read();
        Serial.write(c);
//se você chegou ao final da linha (recebeu um caractere de nova linha)
//e a linha está em branco, a solicitação http termina
//entao você pode enviar uma resposta ao servidor
        
        if(c == 'n' && currentLineIsBlank){
          //Enviando Resposta ao Servidor
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("connction: close");
          //client.println("Refresh: 2"); -> Recarrega a pagina a cada 2 seg
          client.println("<!DOCTYPE HTML>");
          client.println("<HTML>");
          client.println("<font color =#FF0000><b><u>");
          client.println("Envio de informações pela rede utilizando Arduino");
          client.println("</u></b></font>");
          client.println("<p> Ola mundo !! </p>");
          client.println("</HTML>");
        }
          if (c == 'n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != 'r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
       }
    }
     delay(1);
    // Fechando conexão:
    client.stop();
  }
} 
