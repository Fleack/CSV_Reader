# CSV_Reader
# Инструкция по сборке
1) Склонируйте репозиторий
2) У вас должен быть установлен CMake
3) С помощью консоли заходите в корневую папку репозитория
4) Создаёте в ней папку 'build'
5) Переходите в созданную папку 'build'
6) Прописываете команду 'cmake ..' для генерации ide-файлов(можете указать конкретные параметры для генерации IDE файлов)
7) Заходите в файл CMakeLists.txt
8) В 6 строке закомментированное поле с указанием компилятора
9) Убираете символ '#' в начале, а в поле в кавычках указываете путь до компилятора(Не ниже C++17)
10) Возвращаетесь в папку 'build'
11) Прописываете команду 'cmake --build . --config Release --target CSV_Reader'
12) В папке 'build' появится папка 'Release', в ней будет лежать скомпилированный файл
13) При запуске файла нужно передать название файла. Например: 'CSV_Reader.exe file.csv'

*Проверил на компиляцию на следующих компиляторах: LLVM, GCC, MinGW, MSVC

# Тесты
Все тесты, с их описанием находятся в папке 'tests'