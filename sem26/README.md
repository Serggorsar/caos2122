# Семинар 26

## Дополнительные материалы

* [Материалы 2020-21 года по `std::thread`](https://github.com/blackav/hse-caos-2020/tree/master/23-stdthread)

## Задачи на семинар

### A

Реализовать с помощью future-promise, async.
Программа на стандартном входном потоке принимает 3 числа:

`start end n`

Следует запустить отдельную нить, которая должна найти первые `n` простых чисел
в интервале `[start; end)`. Найденные числа должна распечатать функция `main()`.
Если в указанном интервале простых чисел меньше, чем `n`, то следует
вывести на стандартный поток `end` и завершить выполнение программы.