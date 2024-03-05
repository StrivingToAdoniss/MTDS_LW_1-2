# MTDS_LW_1-2
A respositrory with code for Laboratory work 1/2 for MTDS class. More description will be added soon

## UKR
Лабораторна робота представляє із себе консольний застосунок, написаний на С++ для конвертування розмітки тексту із вхідного фомату **Markdown** до формату **HTML** для виводу у консоль чи вихідний файл(в межах лабораторної роботи кількість патернів розміток обмежена).

### Компіляція та запуск
В репозиторії присутній файл .exe, але якщо ви захочете змінити код та скомпілювати програму, то бажано використовувати для цього середовище програмування **Visual Studio** або, встановивши утиліту **MSBuild** скомпілювати програму через **cmd** чи **PowerShell**.

```
msbuild Ім'яФайлуРішення.sln /p:Configuration=Release /p:Platform="Any CPU"
```

### Використання програми
Програма запускається та налаштовується через cmd чи PowerShell. Програма має два режими роботи: вивід у консоль(достатнього просто вказати шлях до вхідного файлу) та створення вихідного файлу(другим аргументом потрібно ввести ім'я вихідного файлу у форматі:[--out <output file>]).

### Вказаня на revert коміт
приклад

## ENG
The laboratory work consists of a console application written in C++ for converting text markup from the **Markdown** input format to the **HTML** format for output to the console or an output file (within the scope of the laboratory work, the number of markup patterns is limited).

### Compilation and Execution
The repository contains an .exe file, but if you want to modify the code and compile the program, it is recommended to use the **Visual Studio** programming environment or, by installing the **MSBuild utility**, compile the program through **cmd** or **PowerShell**.

```
msbuild SolutionFileName.sln /p:Configuration=Release /p:Platform="Any CPU"
```

### Using the Program
The program is launched and configured via **cmd** or **PowerShell**. The program has two modes of operation: output to the console (it's enough to just specify the path to the input file) and creating an output file (the name of the output file in the format: [--out <output file>] needs to be entered as the second argument).

### Usage of revert-commit

examlpe
