# Семинар 20

## Дополнительные материалы

* [Материалы 2020-21 года по работе с signalfd & eventfd](https://github.com/blackav/hse-caos-2020/tree/master/20-poll)
* [signalfd(2) — Linux manual page](https://man7.org/linux/man-pages/man2/signalfd.2.html)
* [eventfd(2) — Linux manual page](https://man7.org/linux/man-pages/man2/eventfd.2.html)
* [пример использования signalfd](https://cpp.hotexamples.com/ru/examples/-/-/signalfd/cpp-signalfd-function-examples.html)

## Задачи на семинар


### A

Процесс порождает трех сыновей. Они пересылают некоторое число друг другу по кругу в следующем порядке:
1 -> 2 -> 3 -> 1 -> ...

Каждый раз при получении числа процесс печатает свой номер, значение числа,
инкрементирует его и отправляет дальше по цепочке.
Для синхронизации использовать `eventfd`.
