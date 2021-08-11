* Документация
https://tools.ietf.org/html/draft-pantos-hls-rfc8216bis-04

https://developer.apple.com/documentation/http_live_streaming/hls_authoring_specification_for_apple_devices

* Тестовый плейлист
https://devstreaming-cdn.apple.com/videos/streaming/examples/img_bipbop_adv_example_ts/master.m3u8

* Требования
C++17
Qt5

* Особенности
Расчет битрейта видео потока(Variant Stream) производится путем получения длины файла из заголовка `Content-Length`.
Если данного параметра нет, то размер берется из загруженного видео-чанка потока.

