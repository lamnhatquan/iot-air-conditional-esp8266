## Ứng dụng điều khiển máy lạnh dùng ESP8266 

### Mô tả ứng dụng 

Điều khiển  máy điều hòa nhiệt độ thông qua internet bằng cách sử dụng ESP8266. Nhiệt độ và độ ẩm nhận từ cảm biến DHT11 và hiển thị lên màn hình OLED. 

### Các nội dung cần thực hiện 

Check list các nội dung cần thực hiện. 

* [X] Đọc dữ liệu của remote dùng LED thu hồng ngoại. 
* [X] Phát lại tín hiệu hồng ngoại để điều khiển máy lạnh
* [X] Đọc nhiệt độ , độ ẩm môi trường dùng DHT11 và hiển thị lên màn hình OLED 
* [  ] ESP8266 kết nối đến mạng WiFi và xây dựng giao diện điều khiển
* [  ] Sử dụng Websocket để tạo kết nối real-time
* [  ] Viết server ở máy tính local
* [  ] Deploy server lên heroku
* [  ] Tổng hợp những nội dung đã làm, viết tài liệu hướng dẫn.

### Chi tiết các nội dung trong check list 

#### 1. Đọc dữ liệu của remote dùng LED thu hồng ngoại. 

- Sử dụng ví dụ [IRecvDumpV2](/sourceCode/IRecvDumpV2/IRecvDumpV2.ino) trong thư viện https://github.com/markszabo/IRemoteESP8266 để thu tín hiệu của remote TOSHIBA.
- Lấy dữ liệu rawData của nút ON/OFF, 20 độ và 30 độ. 

#### 2. Phát lại tín hiệu hồng ngoại để điều khiển máy lạnh

Sử dụng ví dụ [IRsendDemo](//sourceCode/IRsendDemo/IRsendDemo.ino) trong thư viện https://github.com/markszabo/IRemoteESP8266 để điều khiển máy lạnh thông qua dữ liệu  nhấn  rawData của nút ON/OFF, 20 độ và 30 độ. 

#### 3. Đọc nhiệt độ , độ ẩm môi trường dùng DHT11 và hiển thị lên màn hình OLED 

Dùng thư viện DHT sensor  của Adafruit  https://github.com/adafruit/DHT-sensor-library và thư viện https://github.com/ThingPulse/esp8266-oled-ssd1306 để đọc và hiển thị nhiệt độ, độ ẩm lên OLED.


#### 4. ESP8266 kết nối đến mạng WiFi và xây dựng giao diện điều khiển

Sử dụng Wifi Manager để kết nối đến mạng Wifi