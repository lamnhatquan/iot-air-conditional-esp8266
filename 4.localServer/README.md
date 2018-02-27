## Server
- File  server.js nằm trong folder Server khởi tạo server ở port 8000 để lắng nghe các kết nối đến từ client.

- Nếu web browser truy cập đến IP_SERVER:PORT, server sẽ trả về 1 trang HTML với giao diện điều khiển và 1 đoạn mã javascript khởi tạo kết nối websoket đến server. Server khi nhận được phản hồi sẽ gĩư luôn kết nối đó. 

- Broadcast gói tin của các client gửi đến server, ví dụ ESP8266 gửi dữ liệu thì web browser, ngược lại khi  web browser nhấn nút thì các LED tương ứng kết nối với ESP8266 sẽ được điều khiển 

## Clients

Gồm ESP8266 web browser :
- Kết nối đến server thông qua phương thức websocket
- Gửi dữ liệu lên server để server Broadcast gói tin đến client khác