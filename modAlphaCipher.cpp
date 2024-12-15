#include "modAlphaCipher.h"
#include <locale>
#include <codecvt>

// Установка локали для работы с русским языком
locale loc("ru_RU.UTF-8");

// Конвертер для преобразования между строками UTF-8 и wide-строками
wstring_convert<codecvt_utf8<wchar_t>, wchar_t> codec;
using namespace std;

// Конструктор класса modAlphaCipher, принимает строку ключа
modAlphaCipher::modAlphaCipher(const string& skey) {
    // Инициализация отображения символов алфавита в их числовые значения
    for (unsigned i = 0; i < numAlpha.size(); i++)
        alphaNum[numAlpha[i]] = i;

    // Преобразование и валидация ключа
    key = convert(getValidKey(skey));
}

// Метод шифрования открытого текста
string modAlphaCipher::encrypt(const string& open_text) {
    // Преобразование открытого текста в числовой вектор
    vector<int> work = convert(getValidOpenText(open_text));
    
    // Шифрование: добавление соответствующего значения ключа и применение модуля
    for (unsigned i = 0; i < work.size(); i++)
        work[i] = (work[i] + key[i % key.size()]) % numAlpha.size();
    
    // Преобразование числового вектора обратно в строку и возврат результата
    return convert(work);
}

// Метод расшифровки зашифрованного текста
string modAlphaCipher::decrypt(const string& cipher_text) {
    // Преобразование зашифрованного текста в числовой вектор
    vector<int> work = convert(getValidCipherText(cipher_text));
    
    // Расшифровка: вычитание соответствующего значения ключа и применение модуля
    for (unsigned i = 0; i < work.size(); i++)
        work[i] = (work[i] + numAlpha.size() - key[i % key.size()]) % numAlpha.size();
    
    // Преобразование числового вектора обратно в строку и возврат результата
    return convert(work);
}

// Вспомогательный метод для преобразования строки в числовой вектор
inline vector<int> modAlphaCipher::convert(const string& s) {
    // Преобразование строки из формата UTF-8 в wide-строку
    wstring ws = codec.from_bytes(s);
    vector<int> result;
    
    // Преобразование каждого символа wide-строки в его числовое значение
    for (auto c : ws)
        result.push_back(alphaNum[c]); // Добавление числового значения символа в результат
    
    return result; // Возврат числового вектора
}

// Вспомогательный метод для преобразования числового вектора обратно в строку
inline string modAlphaCipher::convert(const vector<int>& v) {
    wstring ws;
    
    // Преобразование каждого числового значения обратно в символ wide-строки
    for (auto i : v)
        ws.push_back(numAlpha[i]); // Добавление символа в wide-строку
    
    // Преобразование wide-строки обратно в строку UTF-8 и возврат результата
    return codec.to_bytes(ws);
}

// Вспомогательный метод для проверки и валидации ключа
inline string modAlphaCipher::getValidKey(const string & s) {
    // Преобразование строки из формата UTF-8 в wide-строку
    wstring ws = codec.from_bytes(s);
    
    // Проверка на пустой ключ
    if (ws.empty())
        throw cipher_error("Пустой ключ");
    
    int razmer = ws.size();
    
    // Проверка каждого символа на допустимость
    for (int i = 0; i < razmer; i++) {
        if (ws[i] < L'А' || ws[i] > L'Я') // Проверка на русский алфавит
            throw cipher_error(string("Неверный ключ: ") + s);
        
        // Приведение строчных букв к заглавным
        if (ws[i] >= L'а' && ws[i] <= L'я')
            ws[i] -= 32; // Приведение к верхнему регистру
    }
    
    return codec.to_bytes(ws); // Возврат валидированного ключа в формате UTF-8
}

// Вспомогательный метод для проверки и валидации открытого текста
inline string modAlphaCipher::getValidOpenText(const string & s) {
    // Преобразование строки из формата UTF-8 в wide-строку
    wstring ws = codec.from_bytes(s);
    wstring tmp;
    
    // Проверка каждого символа на допустимость
    for (auto c : ws) {
        if (c >= L'А' && c <= L'Я' || c >= L'а' && c <= L'я') {
            if (c >= L'а' && c <= L'я')
            
             tmp.push_back(c -= 32); // Приведение строчных букв к заглавным
            else
                tmp.push_back(c); // Добавление заглавной буквы в результирующую строку
        } else if (c == L' ') {
            // Игнорирование пробелов
        } else {
            throw cipher_error("Недопустимый символ в тексте"); // Генерация ошибки для недопустимых символов
        }
    }
    
    // Проверка на пустой текст после фильтрации
    if (tmp.empty())
        throw cipher_error("Надо текст!"); 
    
    return codec.to_bytes(tmp); // Возврат валидированного открытого текста в формате UTF-8
}

// Вспомогательный метод для получения валидного зашифрованного текста (пока без проверки)
inline string modAlphaCipher::getValidCipherText(const string & s) {
    // Преобразование строки из формата UTF-8 в wide-строку
    wstring ws = codec.from_bytes(s);
    
    return codec.to_bytes(ws); // Возврат зашифрованного текста в формате UTF-8 без дополнительных проверок
}
