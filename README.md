# spbu2-hw-qt-calculator

Qt Calculator с формой логина и видеоплеером.

## Требования

- Qt 5.15+ с MinGW
- CMake 3.16+

## Быстрый запуск (Windows)

1. Откройте `build.bat` и укажите путь к вашей установке Qt:
   ```batch
   set QT_PATH=C:\Qt\5.15.2\mingw81_64
   set MINGW_PATH=C:\Qt\Tools\mingw810_64
   ```

2. Запустите `build.bat` двойным кликом или из командной строки:
   ```batch
   build.bat
   ```

## Сборка вручную

### С использованием CMake (рекомендуется)

```bash
mkdir build
cd build
cmake -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH="C:/Qt/5.15.2/mingw81_64" ..
mingw32-make
windeployqt Calculator.exe
Calculator.exe
```

### С использованием qmake

```bash
qmake Calculator.pro
mingw32-make
windeployqt Calculator.exe
Calculator.exe
```

## Использование

1. **Форма логина**:
   - Логин: `Илья Владимирович`
   - Пароль: `ЛУЧШИЙ`

2. **Калькулятор**: после успешного входа открывается калькулятор с видеоплеером справа

## Структура проекта

```
├── CMakeLists.txt        # CMake конфигурация
├── Calculator.pro        # qmake конфигурация
├── build.bat             # Скрипт сборки для Windows
├── main.cpp              # Точка входа
├── logindialog.h/cpp     # Форма логина
└── calculatorwindow.h/cpp # Калькулятор с видеоплеером
```