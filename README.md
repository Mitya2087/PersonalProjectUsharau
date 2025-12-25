# Extended Calculator

**Консольное приложение "Расширенный калькулятор"**

**Автор:** Ушаров Дмитрий Павлович, Группа 1  
**Курс:** Основы и методы программирования

---

## Возможности

### Калькулятор поддерживает:
- **Standard Mode:** Базовая арифметика (+, -, *, /), квадратный корень
- **Scientific Mode:** Тригонометрические функции, логарифмы, экспонента, степени
- **Programmer Mode:** Битовые операции, конвертация систем счисления (BIN, DEC, HEX), поддержка выражений типа `3 << 2`
- **History:** Сохранение истории вычислений с undo/redo
- **Date Calculations:** Вычисление разницы между датами и добавление дней
- **Array Sorting:** Сортировка массивов (Bubble, Quick, Merge Sort)

---

## Системные Требования

### Зависимости:
```bash
# Ubuntu/Debian
sudo apt update
sudo apt install cmake g++

# Минимальные версии:
# - CMake 3.14+
# - C++17
```

---

## Сборка Проекта

### 1. Клонирование репозитория
```bash
git clone <repository_url>
cd PersonalProjectUsharau
```

### 2. Сборка
```bash
mkdir -p build && cd build
cmake ..
make -j4
```

### Результаты сборки:
- `calculator` - Консольная версия калькулятора
- `calculator_tests` - Набор тестов (Google Test)

---

## Запуск

### Консольная версия
```bash
./build/calculator
```

### Аргументы командной строки

#### Прямые вычисления
```bash
./build/calculator --calc "2 + 2 * 3"
# Output: 2 + 2 * 3 = 8
```

#### Помощь
```bash
./build/calculator --help
```

#### Загрузка истории при старте
```bash
./build/calculator --load-history myhistory.txt
```

#### Установка уровня логирования
```bash
./build/calculator --log-level DEBUG --log-file debug.log
```

#### Запуск в определённом режиме
```bash
./build/calculator --mode scientific
```

### Доступные опции:
- `--help, -h` - Показать справку
- `--calc EXPRESSION` - Вычислить выражение напрямую
- `--load-history FILE` - Загрузить историю из файла
- `--log-level LEVEL` - Уровень логирования (DEBUG|INFO|WARNING|ERROR)
- `--log-file FILE` - Записывать логи в файл
- `--mode MODE` - Режим запуска (standard|scientific|programmer)

---

## Тестирование

### Запуск тестов
```bash
./build/calculator_tests
```

### Результаты:
- **25 тестов** (MathUtils, ExpressionEvaluator, History, Sorter, Integration)
- **100% pass rate**

---

## Работа с Файлами

### Текстовый формат
Человеко-читаемый формат, один entry на строку:
```
2 + 2|4
sin(90)|1
sqrt(16)|4
```

### Бинарный формат
Компактный бинарный формат для быстрого I/O и меньшего размера файлов.

#### Использование:
```cpp
History history;
// Сохранение в текстовом формате
history.save("history.txt");

// Сохранение в бинарном формате
history.saveBinary("history.bin");

// Загрузка бинарного формата
history.loadBinary("history.bin");
```

---

## Архитектура Проекта

```
PersonalProjectUsharau/
├── src/
│   ├── backend/          # Ядро: MathUtils, ExpressionEvaluator, History, Sorter, CalculatorEngine
│   ├── cli/              # Интерфейс: CalculatorApp, Modes (Standard, Scientific, Programmer), DateMode
│   ├── utils/            # Утилиты: ArgumentParser, LinkedList<T>
│   └── tests/            # Тесты: Google Test реализации
├── build/                # Директория сборки
├── CMakeLists.txt        # Конфигурация сборки (CMake)
├── README.md             # Общее описание (этот файл)
└── BUILD.md              # Подробная инструкция по сборке на русском
```

---

## Ключевые Компоненты

### ООП и Полиморфизм
- **Базовый класс Mode** с виртуальными методами
- **StandardMode, ScientificMode, ProgrammerMode** - наследование и полиморфизм
- **CalculatorEngine** - инкапсуляция логики вычислений

### Структуры Данных
- **Собственный LinkedList<T>** - шаблонный двусвязный список с итераторами
- **STL**: vector, string, algorithms (swap, find)

### Файловый I/O
- Текстовые файлы (fstream)
- Бинарные файлы с версионированием
- Сериализация объектов History

### Тестирование
- **Google Test** framework
- Покрытие всех ключевых функций и граничных случаев

---

## Примеры Использования

### Консольный режим
```
=== Main Menu ===
1. Standard Mode
2. Scientific Mode
3. Programmer Mode
...
> 2

=== Scientific Mode ===
sci> sin(90)
= 1

sci> 2 ^ 8
= 256
```

### Programmer Mode (с битовыми операциями)
```
prog> 3 << 2
DEC: 12
HEX: 0xC
BIN: 0000...1100
```

---

## Реализованные Требования Курса

| Критерий | Баллы | Статус |
|----------|-------|--------|
| 1. ООП и логика | 30 | ✅ |
| 2. UI и CLI аргументы | 20 | ✅ |
| 3. Файлы (текст+бинарные) | 15 | ✅ |
| 4. STL + своя structure | 15 | ✅ |
| 5. Тесты + документация | 20 | ✅ |
| **Итого** | **100** | **✅** |

### Детали:
- ✅ Наследование и полиморфизм (Mode hierarchy)
- ✅ Меню-ориентированный интерфейс
- ✅ Аргументы командной строки (--calc, --help, --load-history, etc.)
- ✅ Текстовые и бинарные файлы (Serialization)
- ✅ STL контейнеры и алгоритмы
- ✅ Собственная структура данных (LinkedList<T>)
- ✅ Google Test (25 тестов)
- ✅ README и BUILD инструкции

---

## Автор

**Ушаров Дмитрий Павлович**  
Группа 1, Курс ОиМП  
2025 год
