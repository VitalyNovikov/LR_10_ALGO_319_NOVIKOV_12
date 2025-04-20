#include <iostream>
#include <cmath> // Для функції abs() у задачі Begin17
using namespace std;

// ===== Завдання 1 (Param85) =====

// Структура для представлення часу (з Param71)
struct TTime {
    int Hour;   // Години (0-23 або 1-12 в залежності від формату)
    int Min;    // Хвилини (0-59)
    int Sec;    // Секунди (0-59)
};

// Функція для перевірки коректності часу в 24-годинному форматі (з Param71)
int CheckTime(TTime T) {
    int errors = 0; // Лічильник помилок (0 - немає помилок)
    
    if (T.Hour < 0 || T.Hour > 23) errors += 100;
    if (T.Min < 0 || T.Min > 59) errors += 10;
    if (T.Sec < 0 || T.Sec > 59) errors += 1;
    
    return errors;
}

// Функція для перевірки, чи час вже у 24-годинному форматі
bool Is24HourFormat(TTime T) {
    return CheckTime(T) == 0; // Час коректний у 24-годинному форматі
}

// Функція для перевірки коректності часу в 12-годинному форматі
bool Is12HourFormatValid(TTime T, bool PM) {
    // Для 12-годинного формату години мають бути 1-12, хвилини/секунди 0-59
    return (T.Hour >= 1 && T.Hour <= 12) && 
           (T.Min >= 0 && T.Min <= 59) && 
           (T.Sec >= 0 && T.Sec <= 59);
}

// Функція для перетворення 12-годинного формату в 24-годинний
TTime To24h(TTime T, bool PM) {
    // Якщо час вже у 24-годинному форматі
    if (Is24HourFormat(T) && !PM) {
        return T;
    }
    
    // Якщо час некоректний для 12-годинного формату
    if (!Is12HourFormatValid(T, PM)) {
        return {0, 0, 0}; // Повертаємо 00:00:00 при помилці
    }
    
    // Виконуємо перетворення
    int hour24 = T.Hour;
    if (PM) {
        hour24 = (T.Hour == 12) ? 12 : T.Hour + 12;
    } else {
        hour24 = (T.Hour == 12) ? 0 : T.Hour;
    }
    
    return {hour24, T.Min, T.Sec};
}

void PrintTime(TTime T) {
    printf("%02d:%02d:%02d", T.Hour, T.Min, T.Sec);
}

void DemoTimeFunctions() {
    cout << "=== Завдання 1 (Param85) ===" << endl;
    
    struct TestCase {
        TTime time;
        bool PM;
        string desc;
    };
    
    TestCase tests[] = {
        {{3,45,30}, false, "3:45:30 AM → 03:45:30"},
        {{12,0,0}, true, "12:00:00 PM → 12:00:00"},
        {{8,15,0}, false, "8:15:00 AM → 08:15:00"},
        {{6,30,45}, true, "6:30:45 PM → 18:30:45"},
        {{11,59,59}, true, "11:59:59 PM → 23:59:59"},
        {{33,0,0}, false, "33:00:00 AM → 00:00:00 (некоректний)"},
        {{5,60,0}, false, "5:60:00 AM → 00:00:00 (некоректний)"},
        {{7,0,60}, false, "7:00:60 AM → 00:00:00 (некоректний)"},
        {{16,30,0}, false, "16:30:00 → 16:30:00 (вже 24-годинний)"},
        {{0,0,0}, false, "00:00:00 → 00:00:00 (вже 24-годинний)"}
    };
    
    for (int i = 0; i < 10; i++) {
        auto test = tests[i];
        cout << "Тест " << i+1 << ": " << test.desc << endl;
        cout << "Вхідний час: ";
        PrintTime(test.time);
        cout << " (" << (test.PM ? "PM" : "AM") << ")" << endl;
        
        TTime result = To24h(test.time, test.PM);
        cout << "Результат: ";
        PrintTime(result);
        cout << endl << endl;
    }
}



// ===== Завдання 2 (Begin17) =====
// Структура для представлення точки на числовій осі
struct Point {
    double x; // Координата точки
};

// Структура для вхідних та вихідних даних задачі
struct LineSegments {
    Point A, B, C; // Вхідні дані - три точки
    double AC, BC, Sum; // Вихідні дані - довжини відрізків та їх сума
};

// Функція для обчислення довжин відрізків
void CalculateSegments(LineSegments &data) {
    // Обчислюємо довжину відрізка AC (модуль різниці координат)
    data.AC = abs(data.C.x - data.A.x);
    
    // Обчислюємо довжину відрізка BC (модуль різниці координат)
    data.BC = abs(data.C.x - data.B.x);
    
    // Обчислюємо суму довжин
    data.Sum = data.AC + data.BC;
}

// Функція для введення даних та перевірки їх коректності
void InputAndValidate(LineSegments &data) {
    cout << "Введіть координату точки A: ";
    cin >> data.A.x;
    
    cout << "Введіть координату точки B: ";
    cin >> data.B.x;
    
    cout << "Введіть координату точки C: ";
    cin >> data.C.x;
    
    // У цій задачі всі вхідні дані коректні, оскільки вони просто числа
}

// Демонстрація роботи для задачі з точками
void DemoLineSegments() {
    cout << "\n=== Завдання 2 (Begin17) ===" << endl;
    
    LineSegments data;
    
    // Введення даних
    InputAndValidate(data);
    
    // Обчислення
    CalculateSegments(data);
    
    // Виведення результатів
    cout << "Довжина відрізка AC: " << data.AC << endl;
    cout << "Довжина відрізка BC: " << data.BC << endl;
    cout << "Сума довжин AC і BC: " << data.Sum << endl;
}



// ===== Завдання 3 (Boolean13) =====
// Структура для вхідних та вихідних даних задачі
struct NumbersCheck {
    int A, B, C; // Вхідні дані - три цілих числа
    bool result;  // Вихідні дані - результат перевірки
};

// Функція для перевірки умови
void CheckCondition(NumbersCheck &data) {
    // Умова: хоча б одне з чисел A, B, C позитивне
    data.result = (data.A > 0) || (data.B > 0) || (data.C > 0);
}

// Функція для введення даних
void InputNumbers(NumbersCheck &data) {
    cout << "Введіть число A: ";
    cin >> data.A;
    
    cout << "Введіть число B: ";
    cin >> data.B;
    
    cout << "Введіть число C: ";
    cin >> data.C;
}

// Демонстрація роботи для задачі з числами
void DemoNumbersCheck() {
    cout << "\n=== Завдання 3 (Boolean13) ===" << endl;
    
    NumbersCheck data;
    
    // Введення даних
    InputNumbers(data);
    
    // Перевірка умови
    CheckCondition(data);
    
    // Виведення результату
    cout << "Хоча б одне з чисел A, B, C позитивне: " 
         << (data.result ? "так" : "ні") << endl;
}

// ===== Головна функція =====
int main() {
    // Демонстрація роботи всіх трьох завдань
    DemoTimeFunctions();
    DemoLineSegments();
    DemoNumbersCheck();
    
    return 0;
}