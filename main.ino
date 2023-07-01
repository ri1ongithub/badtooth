#include <WiFi.h>
#include <WebServer.h>
#include <BleKeyboard.h>

WebServer server(80);
BleKeyboard bleKeyboard;

void handleRoot()
{
  String page = F("<meta charset='UTF-8'>");
  page += F("    <meta http-equiv='X-UA-Compatible' content='IE=edge'>");
  page += F("    <meta name='viewport' content='width=device-width, initial-scale=1.0'>");
  page += F("    <title>BadTooth</title>");
  page += F("    <style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
  page += F("       .button { background-color: #196ecf; border: none; color: white; padding: 16px 40px;");
  page += F("        text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer; border-radius: 10px; width: 90%;}");
  page += F("        .button:disabled {background-color: #555555; cursor: not-allowed;}");
  page += F("        textarea {width: 90%;height: 100px;padding: 12px 20px;box-sizing: border-box;border: 2px solid #ccc;border-radius: 4px;background-color: #f8f8f8;resize: none;}</style>");
  page += F("</head>");
  page += F("<body>");
  page += F("    <h1>BadTooth</h1><h2 id='status'>Connected : ");  page += bleKeyboard.isConnected() ? "true" : "false";
  page += F("</h2><br><textarea placeholder='Type something...' id='txtarea'></textarea><br><br><a href='javascript:;' onclick = 'this.href=`/text?text=` + document.getElementById(`txtarea`).value'><button class='button'>Send</button></a>");
  page += F("    <br><br><br><a href='/enter'><button class='button'>Send ENTER</button></a><br><br><a href='/backspace'><button class='button'>Send Backspace</button></a><br><br><a href='/winr'><button class='button'>Send WIN + R</button></a>");
  page += F("<br><br><a href='/ctrlaltsupr'><button class='button'>Send CTRL + ALT + SUPR</button></a>");  
  page += F("</body></html><script>");
  page += F("    if(document.getElementById('status').textContent.includes('false')) {document.querySelectorAll('.button').forEach(disable)} function disable(item) {item.disabled = true;}");
  page += F("</script>");
  server.send(200, "text/html", page);
}

void handleText()
{
    String value = server.arg("text");
    server.sendHeader("Location","/");
    server.send(303);
    if(bleKeyboard.isConnected()) {
        bleKeyboard.print(value);
    }
}

void handleEnter()
{
    server.sendHeader("Location","/");
    server.send(303);
    if(bleKeyboard.isConnected()) {
        bleKeyboard.write(KEY_RETURN);    
    }
}

void handleBackspace()
{
    server.sendHeader("Location","/");
    server.send(303);
    if(bleKeyboard.isConnected()) {
        bleKeyboard.write(KEY_BACKSPACE);    
    }
}

void handleWinR()
{
    server.sendHeader("Location","/");
    server.send(303);

    if(bleKeyboard.isConnected()) {
        bleKeyboard.press(KEY_LEFT_GUI);
        bleKeyboard.press('r');
        delay(100);
        bleKeyboard.releaseAll();      
    }
}

void handleCTRLALTSUPR()
{
    server.sendHeader("Location","/");
    server.send(303);

    if(bleKeyboard.isConnected()) {
      bleKeyboard.press(KEY_LEFT_CTRL);
      bleKeyboard.press(KEY_LEFT_ALT);
      bleKeyboard.press(KEY_DELETE);
      delay(100);
      bleKeyboard.releaseAll();    
    }
}

void handleNotFound()
{
    server.send(404, "text/plain", "404: Not found");
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n");

  Serial.print(F("Setting the Bluetooth...\n"));
  bleKeyboard.setName("Bluetooth Keyboard");
  bleKeyboard.begin();

  // Connect to Wi-Fi network with SSID and password
  Serial.print(F("Setting the AP...\n"));
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP("BadTooth", "YouShallNotPass");

  IPAddress IP = WiFi.softAPIP();
  Serial.print(F("AP IP address: "));
  Serial.println(IP);
  
  server.on("/", handleRoot);
  server.on("/text", handleText);
  server.on("/enter", handleEnter);
  server.on("/backspace", handleBackspace);
  server.on("/winr", handleWinR);
  server.on("/ctrlaltsupr", handleCTRLALTSUPR);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.print(F("Web server online."));
}

void loop()
{
    server.handleClient();
}