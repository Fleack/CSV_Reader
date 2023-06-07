\documentclass[]{article}
\usepackage{lmodern}
\usepackage{amssymb,amsmath}
\usepackage{ifxetex,ifluatex}
\usepackage{fixltx2e} % provides \textsubscript
\ifnum 0\ifxetex 1\fi\ifluatex 1\fi=0 % if pdftex
  \usepackage[T1]{fontenc}
  \usepackage[utf8]{inputenc}
\else % if luatex or xelatex
  \ifxetex
    \usepackage{mathspec}
  \else
    \usepackage{fontspec}
  \fi
  \defaultfontfeatures{Ligatures=TeX,Scale=MatchLowercase}
\fi
% use upquote if available, for straight quotes in verbatim environments
\IfFileExists{upquote.sty}{\usepackage{upquote}}{}
% use microtype if available
\IfFileExists{microtype.sty}{%
\usepackage{microtype}
\UseMicrotypeSet[protrusion]{basicmath} % disable protrusion for tt fonts
}{}
\usepackage[unicode=true]{hyperref}
\hypersetup{
            pdfborder={0 0 0},
            breaklinks=true}
\urlstyle{same}  % don't use monospace font for urls
\usepackage{longtable,booktabs}
\IfFileExists{parskip.sty}{%
\usepackage{parskip}
}{% else
\setlength{\parindent}{0pt}
\setlength{\parskip}{6pt plus 2pt minus 1pt}
}
\setlength{\emergencystretch}{3em}  % prevent overfull lines
\providecommand{\tightlist}{%
  \setlength{\itemsep}{0pt}\setlength{\parskip}{0pt}}
\setcounter{secnumdepth}{0}
% Redefines (sub)paragraphs to behave more like sections
\ifx\paragraph\undefined\else
\let\oldparagraph\paragraph
\renewcommand{\paragraph}[1]{\oldparagraph{#1}\mbox{}}
\fi
\ifx\subparagraph\undefined\else
\let\oldsubparagraph\subparagraph
\renewcommand{\subparagraph}[1]{\oldsubparagraph{#1}\mbox{}}
\fi

\date{}

\begin{document}

\textsuperscript{Test}

\begin{longtable}[]{@{}l@{}}
\toprule
Задан CSV-файл (\emph{comma-separated values}) с заголовком, в котором
перечислены названия столбцов. Строки нумеруются целыми положительными
числами, необязательно в порядке возрастания. В ячейках CSV-файла могут
хранится или целые числа или выражения вида

\subsection{\texorpdfstring{= \textbf{ARG1} \textbf{OP}
\textbf{ARG2}}{= ARG1 OP ARG2}}\label{arg1-op-arg2}

где \textbf{ARG1} и \textbf{ARG2} -- целые числа или адреса ячеек в
формате Имя\_колонки Номер\_строки, а \textbf{OP} -- арифметическая
операция из списка: +, -, *, /.

Например, таблица

\begin{longtable}[]{@{}llll@{}}
\toprule
& \textbf{A} & \textbf{B} & \textbf{Cell}\tabularnewline
\midrule
\endhead
\textbf{1} & 1 & 0 & 1\tabularnewline
\textbf{2} & 2 & =A1+Cell30 & 0\tabularnewline
\textbf{30} & 0 & =B1+A1 & 5\tabularnewline
\bottomrule
\end{longtable}

Будет представлена в нашем CSV-формате следующим образом:

\begin{quote}
\textbf{,A,B,Cell}

\textbf{1,1,0,1}

\textbf{2,2,=A1+Cell30,0}

\textbf{30,0,=B1+A1,5}
\end{quote}

(обратите внимание на \emph{\textbf{пропуск первого значения}} в первой
строке CSV-представления, он обозначает пустую левую верхнюю ячейку
таблицы).

Требуется написать программу, которая читает произвольную CSV-форму из
файла (количество строк и столбцов может быть любым), \textbf{вычисляет}
значения ячеек, если это необходимо, и выводит получившуюся табличку в
виде CSV-представления в консоль. Решением задания будет: файл или
несколько файлов с исходным кодом программы на языке C++, инструкции по
сборке и тестовые примеры (количество тестов -- на усмотрение
разработчика).

Программа должна компилироваться компилятором gcc или clang в Linux,
mingw/cygwin в Windows. Рекомендуется использование стандартной
библиотеки (STL). Использование любых сторонних библиотек, кроме STL,
запрещено. Имя CSV-файла необходимо передавать первым аргументом
командной строки. В решении, кроме файлов с исходным кодом, требуется
предоставить инструкции по компиляции программы для проверки. Можно, но
необязательно, использовать следующие системы автоматизации сборки:
make, automake, cmake, gradle; проприетарные средства сборки не
допускаются: например, файлы проектов MS Visual Studio не подойдут.

Пример запуска программы:

\begin{quote}
\$ csvreader.exe file.csv
\end{quote}

где \textbf{csvreader.exe} -- имя исполняемого файла (может быть любым),
\textbf{file.csv} -- имя файла с таблицей (произвольно задаётся
пользователем), \textbf{\$} - приглашение командного интерпретатора.

Для приведённого примера результат, напечатанный в консоль, может быть
таким:

\begin{quote}
\textbf{,A,B,Cell}

\textbf{1,1,0,1}

\textbf{2,2,6,0,}

\textbf{30,0,1,5}
\end{quote}

Рекомендуем решение задачи проверять

\begin{itemize}
\item
  На приведённом примере
\item
  На дополнительных тестах (csv-файлах), выбор которых отводится на ваше
  усмотрение; постарайтесь в своих тестах учесть различные правильные и
  ошибочные ситуации (например, к ошибочным можно отнести деление на 0,
  некорректные адреса ячеек, неверные номера строк, неправильный формат
  таблицы и т.п.)
\item
  Можно (но необязательно) написать дополнительно проверочные юнит-тесты
  с использованием доступной библиотеки (Google Test, CppUTest, и т.п.)
\end{itemize}

Рекомендуется в решении задания использовать современные возможности
С++, структуры и типы данных из стандартной библиотеки (STL). Будьте
готовы защитить своё решение тестового задания на этапе очного интервью
(ответить на вопросы технических специалистов по домашнему заданию или
по смежным темам).

Проверка домашнего задания осуществляется в два этапа:

\begin{enumerate}
\def\labelenumi{\arabic{enumi}.}
\item
  Обработка наших эталонных тестовых CSV-файлов, содержащих как
  корректные, так и некорректные таблицы.
\item
  Оценивание исходных кодов программы проверяющими.
\end{enumerate}\tabularnewline
\midrule
\endhead
\bottomrule
\end{longtable}

\end{document}
