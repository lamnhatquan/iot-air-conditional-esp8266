## Server
- File  server.js nằm trong folder Server khởi tạo server ở port 8000 để lắng nghe các kết nối đến từ client.

- Nếu web browser truy cập đến IP_SERVER:PORT, server sẽ trả về 1 trang HTML với giao diện điều khiển và 1 đoạn mã javascript khởi tạo kết nối websoket đến server. Server khi nhận được phản hồi sẽ gĩư luôn kết nối đó. 

- Broadcast gói tin của các client gửi đến server, ví dụ ESP8266 gửi dữ liệu thì web browser, ngược lại khi  web browser nhấn nút thì các LED tương ứng kết nối với ESP8266 sẽ được điều khiển 

## Clients

Gồm ESP8266 và web browser với các chức năng:

- Kết nối đến server thông qua phương thức websocket
- Gửi dữ liệu lên server để server Broadcast gói tin đến client khác.

#### ESP8266 

- Đọc nhiệt độ, độ ẩm của DHT11và hiển thị trên OLED 
- Kết nối với mạng wifi sử dụng wifimanager 
- Gửi dữ liệu tới server local mỗi 3s 

#### Web browser

- Lấy dữ liệu từ server khi server broadcast gói tin đến các client, hiển thị lên text nhiệt độ, độ ẩm. 

## Kết quả 

Hình ảnh trang giao diện HTML 

![Server chạy ở máy tính](/images/senData.png)

Trang giao diện hiển thị nhiệt độ, độ ẩm và điều khiển máy điều hòa nhiệt độ

![trang index](/images/interface.png)

Dữ liệu rawData nhận được khi nhấn các button trên trang index.

![data send to A/C](/images/receiveData.png)


