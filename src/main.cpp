#include <M5Unified.h>
#include <WiFiMulti.h>
#include <WiFiClientSecure.h>

WiFiMulti wifiMulti;

const struct wifi_info_t {
  const char *ssid;
  const char *password;
} wifi_infos[] = {
  {"REPLACE_WITH_YOUR_SSID", "REPLACE_WITH_YOUR_PASSWORD"},
};

const String first_letter_options = "あいうえおかきくけこさしすせそたちつてとなにぬねのはひふへほまみむめもやゆよらりるれろわがぎぐげござじずぜぞだでどばびぶべぼ";
const uint8_t hiragana_bytes = 3U;

const char* chatgpt_host = "api.openai.com";
const char* chatgpt_path  = "/v1/chat/completions";
const char* chatgpt_secret_apikey = "REPLACE_WITH_YOUR_CHATGPT_SECRET_API_KEY";

const String content_key = "\"content\": \"";

const uint8_t tone_volume = 48U;
const float tone_frequency = 3322.44F;
const uint32_t tone_duration = 50U;

M5Canvas ContentSprite;
M5Canvas WindowSprite;

void connect_wifi(){
  Serial.println("Connecting to Wi-Fi...");
  M5.Display.print("Wi-Fiに接続しています");

  for (uint8_t i = 0; i < sizeof(wifi_infos) / sizeof(struct wifi_info_t); i++) {
    wifiMulti.addAP(wifi_infos[i].ssid, wifi_infos[i].password);
  }

  wifiMulti.run(200);

  while (WiFi.status() != WL_CONNECTED) { 
    delay(500); 
    M5.Display.print(".");
  }
  
  Serial.println("Connected.");
  M5.Display.println("");
  M5.Display.println("WiFiに接続しました");
  M5.Display.print("IPアドレス: ");
  M5.Display.println(WiFi.localIP());
  delay(1500);
}

String build_req_payload(const String first_letter) {
  String prompt = \
    "以下のルールを厳守して、伝説の古文書風の文章を生成しなさい。\\n" \
    "・文章は必ず文語調で古めかしい文体とする。\\n" \
    "・文章のテーマはロールプレイングゲームとする。\\n" \
    "・文頭の1文字目は必ず平仮名「" \
    + first_letter + \
    "」とする。\\n" \
    "・文頭の2文字目は必ず句読点でないこと。\\n" \
    "・文章の長さは40文字程度とする。\\n" \
    "・文章は必ず漢字を含むこと。\\n";

  String req_payload  = \
    "{" \
      "\"model\": \"gpt-3.5-turbo\", " \
      "\"max_tokens\": 90, " \
      "\"messages\": " \
      "[" \
        "{" \
          "\"role\": \"user\", " \
          "\"content\": \""  + prompt + "\"" \
        "}" \
      "]" \
    "}";

  return req_payload;
}

String request_to_chatgpt(const String req_payload) {
  String content = "";

  WiFiClientSecure client;
  client.setInsecure();

  Serial.println("Connecting to ChatGPT...");
  if (!client.connect(chatgpt_host, 443)) {
    Serial.println("Connection failed.");
    return content;
  }
  Serial.println("Connected.");

  Serial.println("Requesting text-generation to ChatGPT...");
  client.println("POST " + String(chatgpt_path) + " HTTP/1.1");
  client.println("Host: " + String(chatgpt_host));
  client.println("Content-Type: application/json");
  client.println("Content-Length: " + String(req_payload.length()));
  client.println("Authorization: Bearer " + String(chatgpt_secret_apikey));
  client.println("Connection: close");
  client.println();
  client.println(req_payload);
  Serial.println("Requested.");

  M5.Display.print(".");
  delay(1000);
  M5.Display.print(".");
  delay(1000);
  M5.Display.println(".");

  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      break;
    }
  }
  String res_payload = "";
  while (client.available()) {
    char c = client.read();
    res_payload += c;
  }
  client.stop();

  int from = res_payload.indexOf(content_key) + content_key.length();
  int to = from + res_payload.substring(from).indexOf("\"");
  content = res_payload.substring(from, to);
  content.replace(" ", "　");
  content.replace("\\n", "　");

  return content;
}

void show_ancient_text() {
  M5.Speaker.tone(tone_frequency, tone_duration);

  uint16_t rnd = random(first_letter_options.length() / hiragana_bytes);

  String first_letter = first_letter_options.substring(rnd * hiragana_bytes, rnd * hiragana_bytes + hiragana_bytes);

  M5.Display.fillScreen(TFT_BLACK);
  M5.Display.setCursor(0, 0);
  M5.Display.setTextColor(TFT_WHITE, TFT_BLACK);
  M5.Display.setFont(&fonts::lgfxJapanGothic_16);
  M5.Display.print("「" + first_letter + "」で始まる古文書を生成しています");

  String req_payload = build_req_payload(first_letter);
  String content = request_to_chatgpt(req_payload);
  if (content != "") {
    WindowSprite.fillScreen(TFT_BLACK);
    WindowSprite.fillRoundRect(0, 0, 320, 145, 8, TFT_WHITE);
    WindowSprite.fillRoundRect(2, 2, 316, 141, 8, TFT_BLACK);
    ContentSprite.fillScreen(TFT_BLACK);
    ContentSprite.setCursor(0, 0);
    ContentSprite.setFont(&fonts::lgfxJapanGothic_20);
    ContentSprite.println(content);
    ContentSprite.pushSprite(&WindowSprite, 30, 20); 
    WindowSprite.pushSprite(&M5.Display, 0, 50); 

    M5.Speaker.tone(tone_frequency, tone_duration);
  }
}

void setup() {
  M5.begin();

  M5.Speaker.begin();
  M5.Speaker.setVolume(tone_volume);

  Serial.begin(115200);
  delay(500);

  M5.Display.init();

  M5.Display.setRotation(1);
  M5.Display.setBrightness(128);

  M5.Display.fillScreen(TFT_BLACK);
  M5.Display.setTextColor(TFT_WHITE, TFT_BLACK);
  M5.Display.setFont(&fonts::lgfxJapanGothic_16);
  M5.Display.println("～古文書生成くん～");
  M5.Display.println();

  connect_wifi();

  ContentSprite.setPsram(true);
  WindowSprite.setPsram(true);
  ContentSprite.createSprite(260, 100);
  WindowSprite.createSprite(320, 150);

  show_ancient_text();
} 

void loop() { 
  M5.update();

  if (M5.Touch.getDetail().wasClicked())
  {
    show_ancient_text();
  }
}