#pragma once 
#include <vector> 
#include <string> 
#include <map>    
#include <stdexcept> 

using namespace std; 

/**
* @brief Класс modAlphaCipher для реализации шифрования и расшифровки текста с помощью модифицированного алфавитного шифра
* @param Text: строка, представляющая открытый текст. Key: строка, представляющая ключ шифрования.
*/
class modAlphaCipher {
    private:
        // Строка, содержащая русский алфавит (включая букву "Ё")
        wstring numAlpha = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"; 
        
        // Словарь для отображения символов алфавита в их числовые значения
        map <wchar_t,int> alphaNum; 
        
        // Вектор, содержащий числовые значения ключа шифрования
        vector <int> key; 
        
        // Вспомогательный метод для преобразования строки в числовой вектор
        vector<int> convert(const string& s);
        
        // Вспомогательный метод для преобразования числового вектора обратно в строку
        string convert(const vector<int>& v);
        
        // Метод для проверки и валидации ключа
        string getValidKey(const string & s);
        
        // Метод для проверки и валидации открытого текста
        string getValidOpenText(const string & s);
        
        // Метод для проверки и валидации зашифрованного текста (пока без проверки)
        string getValidCipherText(const string & s);
    
    public:
        // Запрещенный конструктор по умолчанию
        modAlphaCipher()=delete; 
        
        // Конструктор класса, принимающий строку ключа
        modAlphaCipher(const string& skey);
        
        // Метод для шифрования открытого текста
        string encrypt(const string& open_text);
        
        // Метод для расшифровки зашифрованного текста
        string decrypt(const string& cipher_text);
};

// Класс исключения для обработки ошибок, связанных с шифрованием
class cipher_error : public std::invalid_argument {
public:
    // Конструктор исключения, принимающий строку с сообщением об ошибке
    explicit cipher_error(const std::string& what_arg) : std::invalid_argument(what_arg) {}
    
    // Конструктор исключения, принимающий указатель на сообщение об ошибке
    explicit cipher_error(const char* what_arg) : std::invalid_argument(what_arg) {}
};
