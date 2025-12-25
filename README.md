# Extended Calculator

**Консольное и GUI приложение "Расширенный калькулятор"**

**Автор:** Ушаров Дмитрий Павлович, Группа 1  
**Курс:** Основы и методы программирования

---

## Возможности

### Калькулятор поддерживает:
- **Standard Mode:** Базовая арифметика (+, -, *, /), квадратный корень
- **Scientific Mode:** Тригонометрические функции, логарифмы, экспонента, степени
- **Programmer Mode:** Битовые операции, конвертация систем счисления (BIN, DEC, HEX)
- **History:** Сохранение истории вычислений с undo/redo
- **Array Sorting:** Сортировка массивов (Bubble, Quick, Merge Sort)

### Две версии:
1. **Qt GUI** (`calculator`) - Графический интерфейс с вкладками
2. **Console CLI** (`calculator_cli`) - Консольное меню-driven приложение

---

## Системные Требования

### Зависимости:
```bash
# Ubuntu/Debian
sudo apt install cmake g++ qtbase5-dev

# Минимальные версии:
# - CMake 3.14+
# - C++17
# - Qt5 (опционально, только для GUI)
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
- `calculator` - GUI версия (Qt5)
- `calculator_cli` - Консольная версия
- `calculator_tests` - Набор тестов (Google Test)

---

## Запуск

### Графический интерфейс (Qt GUI)
```bash
./build/calculator
```

### Консольная версия
```bash
./build/calculator_cli
```

### Аргументы командной строки

#### Прямые вычисления
```bash
./build/calculator_cli --calc "2 + 2 * 3"
# Output: 2 + 2 * 3 = 8
```

#### Помощь
```bash
./build/calculator_cli --help
```

#### Загрузка истории при старте
```bash
./build/calculator_cli --load-history myhistory.txt
```

#### Установка уровня логирования
```bash
./build/calculator_cli --log-level DEBUG --log-file debug.log
```

#### Запуск в определённом режиме
```bash
./build/calculator_cli --mode scientific
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

В меню калькулятора можно выбрать формат при сохранении/загрузке.

---

## Архитектура Проекта

```
PersonalProjectUsharau/
├── src/
│   ├── backend/          # Общая логика (MathUtils, ExpressionEvaluator, etc.)
│   ├── gui/              # Qt GUI компоненты
│   ├── cli/              # Кнсольное приложение
│   ├── utils/            # Утилиты (ArgumentParser, LinkedList)
│   └── tests/            # Модульные тесты
├── build/                # Артефакты сборки
├── CMakeLists.txt        # Конфигурация сборки
├── README.md             # Этот файл
├── BUILD.md              # Детальная инструкция по сборке
└── GUI_README.md         # Руководство по GUI
```

---

## Ключевые Компоненты

### ООП и Полиморфизм
- **Базовый класс Mode** с виртуальными методами
- **StandardMode, ScientificMode, ProgrammerMode** - наследование и полиморфизм
- **CalculatorEngine** - инкапсуляция логики вычислений

### Структуры Данных
- **Собственный LinkedList<T>** - шаблонный двусвязный список с итераторами
- **STL**: vector, map, string, algorithms (sort, find)

### Файловый I/O
- Текстовые файлы (fstream)
- Бинарные файлы с магическими числами и версионированием
- Сериализация объектов History

### Тестирование
- **Google Test** framework
- Покрытие всех ключевых функций
- Проверка граничных случаев и ошибок

---

## Примеры Использования

### Консольный режим
```
=== Main Menu ===
1. Standard Mode
2. Scientific Mode
3. Programmer Mode
4. Evaluate Expression (RPN)
5. History Management
6. Array Sorting
0. Exit
> 2

--- Scientific Mode ---
> sin(90)
= 1

> 2 ^ 8
= 256
```

### Прямое вычисление
```bash
$ ./calculator_cli --calc "sqrt(16) + log(2.718)"
sqrt(16) + log(2.718) = 5
```

---

## Дополнительная Документация

- [BUILD.md](BUILD.md) - Подробные инструкции по сборке и зависимостям
- [GUI_README.md](GUI_README.md) - Руководство по графическому интерфейсу

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
- ✅ Двухуровневое меню (главное + подменю режимов)
- ✅ Аргументы командной строки (--calc, --help, --load-history, etc.)
- ✅ Текстовые и бинарные файлы
- ✅ Сериализация объектов (History)
- ✅ STL контейнеры (vector, map) и алгоритмы
- ✅ Собственная структура данных (LinkedList<T>)
- ✅ Google Test (25 тестов)
- ✅ Doxygen-style комментарии
- ✅ README с инструкциями

---

## Автор

**Ушаров Дмитрий Павлович**  
Группа 1, Курс ОиМП  
2024 год
