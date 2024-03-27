# MTDS_LW_1-2
A respositrory with code for Laboratory work 1/2 for MTDS class. More description will be added soon

## UKR

### LW_1
Лабораторна робота представляє із себе консольний застосунок, написаний на С++ для конвертування розмітки тексту із вхідного фомату **Markdown** до формату **HTML** для виводу у консоль чи вихідний файл(в межах лабораторної роботи кількість патернів розміток обмежена).

#### Компіляція та запуск
В репозиторії присутній файл .exe, але якщо ви захочете змінити код та скомпілювати програму, то бажано використовувати для цього середовище програмування **Visual Studio** або, встановивши утиліту **MSBuild** скомпілювати програму через **cmd** чи **PowerShell**.

```
msbuild Ім'яФайлуРішення.sln /p:Configuration=Release /p:Platform="Any CPU"
```

#### Використання програми
Програма запускається та налаштовується через cmd чи PowerShell. Програма має два режими роботи: вивід у консоль(достатнього просто вказати шлях до вхідного файлу) та створення вихідного файлу(другим аргументом потрібно ввести ім'я вихідного файлу у форматі:[--out <output file>]).

#### Вказаня на revert коміт
Унікальний ID revert коміту: 0ba7229eb85ef9a3a843ab9796d20cb967f1e8d7

### LW_2
У рамках виконання лабораторної №2 була додана можливість обирати формат конвертації за допомогою параметра **--format=value**, замість value відповідно підставляється режим конвертації до **HTML** чи **ASCI** escape codes. Також була налаштована система **Continuous Integration** на основі **MSBuild** у **GitHub Actions**. Були також створені відповідно **UNIT тести**, які автоматично перевіряються за допомогою вищезазначеної **Continuous Integration**.

#### Вказаня на pull-request, де впали UNIT тести
Перенлянувши вкладку **pull-requests** можна побачити останній незакритий коміт "Failing test #3", де можна наочно подивитися де і через що впали тести і коміт недопущений.

#### Доцільність створення UNIT-тестів
Для мене особисто це був дуже корисний досвід, що видно за моєю хаотичною історією комітів. Саме написання тестів непроблема, але завдяки потребі в імплементації їх до системи **Continuous Integration** я дослідив методику їх правильного створення для С++, а також вивчив підходи використання **CMake** та **MSBuild**. Також я вважаю, що **UNIT тести** будуть корисними для відловлювання механічних помилок, а також наслідків помилок недосвічених членів команди без потреби рев'ю від адміна.

## ENG

### LW_1
The laboratory work consists of a console application written in C++ for converting text markup from the **Markdown** input format to the **HTML** format for output to the console or an output file (within the scope of the laboratory work, the number of markup patterns is limited).

#### Compilation and Execution
The repository contains an .exe file, but if you want to modify the code and compile the program, it is recommended to use the **Visual Studio** programming environment or, by installing the **MSBuild utility**, compile the program through **cmd** or **PowerShell**.

```
msbuild SolutionFileName.sln /p:Configuration=Release /p:Platform="Any CPU"
```

#### Using the Program
The program is launched and configured via **cmd** or **PowerShell**. The program has two modes of operation: output to the console (it's enough to just specify the path to the input file) and creating an output file (the name of the output file in the format: [--out <output file>] needs to be entered as the second argument).

#### Usage of revert-commit
Unique revert-commit ID: 0ba7229eb85ef9a3a843ab9796d20cb967f1e8d7

### LW_2
As part of laboratory work #2, the ability to select the conversion format using the **--format=value** parameter was added, instead of the value, the conversion mode is based on **HTML** or **ASCI** escape codes. A **Continuous Integration** system was also configured based on **MSBuild** in **GitHub Actions**. As requested UNIT tests that are automatically executed by the aforementioned **Continuous Integration** were also implemented.

#### Indication of the pull request where the UNIT tests failed
By going to the **pull-requests** tab, you can see the last open commit "Failing test #3", where you can immediately see where and why the tests failed and the commit is not allowed.

#### The feasibility of creating UNIT tests
For me, it was a beneficial experience, as seen from my chaotic history of committs. Writing the tests itself is not a problem. Still, due to the need to implement them into a **Continuous Integration** system, I researched the methodology of building them correctly for S++, and also learned approaches to use **CMake** and **MSBuild**. I also believe that UNIT tests will be useful for reproducing mechanical errors as well as traces of errors by inexperienced team members without the need for admin review.
