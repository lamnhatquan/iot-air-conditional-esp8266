## Xử lí tín hiệu hồng ngoại 

### Đọc tín hiệu từ remote 

Sử dụng ví dụ `IRecvDumpV2`  trong thư viện  https://github.com/markszabo/IRemoteESP8266  để thu tín hiệu của remote máy lạnh TOSHIBA. Dữ liệu thu được là dữ liệu raw data (các xung ON/OFF) trong 1 mảng 199 phần tử cho mỗi nút nhấn điêu khiển, - Lấy dữ liệu rawData của nút ON/OFF, 20 độ và 30 độ. 
Source code tại folder ir-receive

### Gửi tín hiệu để điều khiển máy lạnh 

Sử dụng dữ liệu raw data  của 3 nút nhấn  từ chương trình đọc tín hiệu, phát lại để điều khiển máy lạnh. Dùng ví dụ `IRsendDemo` cũng của thư viện IRemoteESP8266. 

Source code tại folder ir-send