#pragma once
#include <vector>
#include <string>
#include <map>
#include <stdexcept>

using namespace std;

/**
* @brief Обработка ошибок
* @details Проверяет код на ошибки
* @return Ошибка
*/
class cipher_error : public std::invalid_argument {
public:
    // Конструктор класса cipher_error с аргументом типа std::string
    explicit cipher_error(const std::string& what_arg) : std::invalid_argument(what_arg) {}
    
    // Конструктор класса cipher_error с аргументом типа const char*
    explicit cipher_error(const char* what_arg) : std::invalid_argument(what_arg) {}
};

// Попытка расшифровки зашифрованного текста
decryptedText = cipher.decrypt(cipherText);

// Удаление пробелов из расшифрованного текста
string decryptedTextNoSpaces;
for (char c : decryptedText) {
    if (c != ' ') { // Проверка на пробел
        decryptedTextNoSpaces += c; // Добавление символа в новый текст, если это не пробел
    }
}

cout << "Ключ = " << key << endl; // Вывод ключа шифрования
cout << "Открытый текст: " << Text << endl; // Вывод исходного открытого текста
cout << "Зашифрованный текст: " << cipherText << endl; // Вывод зашифрованного текста
cout << "Расшифрованный текст: " << decryptedTextNoSpaces << endl; // Вывод расшифрованного текста без пробелов


} catch (const cipher_error &e) { // Если возникла ошибка шифрования
    cerr << "Ошибка: " << e.what() << endl; // Вывод сообщения об ошибке
} catch (const std::exception &e) { // Обработка других стандартных исключений
    cerr << "Ошибка: " << e.what() << endl; // Вывод сообщения об ошибке
}

int main() {
    // Проверка различных случаев шифрования и дешифрования с разными ключами и текстами
    check("ЧУМАЗИН", "КЛЮЧ"); // Испытание 1: корректный текст и ключ
    cout << "испытание 1\n" << endl;
    
    check("ЧУМАЗИН", "Ключ"); // Испытание 2: ключ с маленькой буквы
    cout << "испытание 2\n" << endl;
    
    check("ЧУМАЗИН", ""); // Испытание 3: пустой ключ
    cout << "испытание 3\n" << endl;
    
    check("ЧУМАЗИН", "Клю4"); // Испытание 4: некорректный ключ с цифрой
    cout << "испытание 4\n" << endl;
    
    check("ЧУМА ЗИН", "КЛЮЧ"); // Испытание 5: текст с пробелами
    cout << "испытание 5\n" << endl;
    
    check("CHUM", "КЛЮЧ"); // Испытание 6: текст на английском с русским ключом
    cout << "испытание 6\n" << endl;
    
    check("           ", "КЛЮЧ"); // Испытание 7: только пробелы в тексте
    cout << "испытание 7\n" << endl;

    return 0; // Завершение программы
}
