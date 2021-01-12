## ft_containers

ft_containers - учебный проект от школы 21. Это первый серьезный на C++ в программе обучения, в котором просят реализовать контейнеры оригинальной библиотеки STL.
В реализации я решил отказаться от операторов new  и delete в пользу аллокатора с целью изучить эту тему. Так же написано порядка 700 тест кейсов с использованием [Cath2](https://github.com/catchorg/Catch2) unit-test фреймворка

### Реализованые контейнеры:
* __vector__<br>
Простая структура данных, которая реализована как динамический массив с некоторым запасом "сзади" дабы избежать реаллоцирования памяти при каждом добавлении
* __list__<br>
Лист реализован как двухсвязанный циклический список
* __map__<br>
Самая интересная структура данных, реализованна через левостороннее красно-черное дерево. Посчитал что это отличная возможность изучить эту структуру данных.
В качестве ноды хранится пара ключ-значение. Ключи уникальны. Основные операции (вставка, поиска, удаление) отрабатывают за O(logn)
* __queue__<br>
Адаптор над deque, представляющий LIFO структуру данных
* __stack__<br>
Адаптор над deque, представляющий FIFO структуру данных

### Из бонусной части были реализованы:
* __deque__<br>
Также реализован через динамический массив. Прелесть в том, что, в отличии от вектора, данные хранятся посередине. Запас памяти здесь имеется как "сзади", так и "спереди",
опять же для опитимазции операций добавления
* __set__<br>
В данном проекте это почти полная копия map, главное отличие - в ноде хранится только ключ
