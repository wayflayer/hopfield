курсовая работа по нейронной сети хопфилда
Сеть Хопфилда - это рекуррентная нейронная сеть, которая используется для ассоциативной памяти.
Она хранит информацию в виде весовых связей между нейронами, а затем может восстанавливать исходное состояние, даже если оно было частично повреждено.

1. Структура сети
Нейроны: Сеть Хопфилда состоит из N нейронов, каждый из которых может находиться в одном из двух состояний: +1 (активный) или -1 (неактивный).
Весовые связи: Между нейронами существует симметричная матрица весовых связей W.
W(i, j) представляет собой силу связи между нейроном i и нейроном j.
W(i, j) = W(j, i), т.е. связи симметричны.
W(i, i) = 0, т.е. нейрон не имеет связи с самим собой.
2. Хранение информации
Вектор состояния: Состояние сети представляется вектором S, где S(i) - состояние нейрона i.
Обучение: Сеть обучается путем сохранения векторов состояния (памяти) в матрице весовых связей.
Для каждого обучающего вектора Sk, матрица W обновляется по формуле:
W(i, j) = W(i, j) + S<sub>k</sub>(i) * S<sub>k</sub>(j)
3. Восстановление информации
Ввод: В качестве входных данных предоставляется частично поврежденный вектор состояния.
Асинхронный алгоритм:
Выбирается случайный нейрон i.
Вычисляется суммарный взвешенный вход для нейрона:
net<sub>i</sub> = Σ<sub>j</sub> W(i, j) * S(j)
Нейрон обновляет свое состояние:
S(i) = sign(net<sub>i</sub>)
где sign(x) - функция знака, которая возвращает +1, если x > 0, -1, если x < 0, и 0, если x = 0.
Итерации: Алгоритм повторяется до тех пор, пока состояние нейронов не стабилизируется.
Результатом является восстановленный вектор состояния, который должен быть максимально близок к исходному.
4. Пример
Обучение:

Пусть у нас есть два вектора состояния:
S1 = [+1, +1, -1]
S2 = [-1, +1, +1]
После обучения, матрица весовых связей W будет:
W = | 0  2 -2 |
    | 2  0  2 |
    | -2 2  0 |
Восстановление:

В качестве входного вектора используем:
S = [+1, -1, -1] (частично поврежденный S1)
Выполняем асинхронное обновление нейронов:
Нейрон 1: net<sub>1</sub> = 2 * (-1) - 2 * (-1) = 0, S(1) = sign(0) = 0
Нейрон 2: net<sub>2</sub> = 2 * (+1) + 2 * (-1) = 0, S(2) = sign(0) = 0
Нейрон 3: net<sub>3</sub> = -2 * (+1) + 2 * (-1) = -4, S(3) = sign(-4) = -1
Продолжая обновлять нейроны, в итоге мы получим вектор S = [+1, +1, -1], который является исходным вектором S1.
5. Свойства
Ассоциативная память: Сеть может восстанавливать исходное состояние, даже если оно было частично повреждено.
Область привлечения: Сеть имеет определенную область привлечения, в пределах которой она может восстанавливать исходное состояние.
Локальные минимумы: Не всегда гарантируется, что сеть всегда будет сходиться к желаемому состоянию. Она может попасть в локальный минимум.
Ограниченная емкость: Сеть может хранить только ограниченное количество векторов состояния.
