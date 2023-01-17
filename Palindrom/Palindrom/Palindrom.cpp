

#include <iostream>
#include <string.h>
using namespace std;
// подробный алгоритм построения палиндрома минимумом обменов будет описан в отдельном текстовом файле
int FirstofRight(string* S, int Start, int End, string Right) { //поиск во внутреннем подмассиве самого близкого к левой границе элемента правой границы
    for (int i = Start; i <= End; i++) {
        if (S[i] == Right) {
            return i;   // искомый элемент найден, делаем возврат индекса
            break;
        }
    }
    return -1;  // искомый элемент не найден
}
int LastofLeft(string* S, int Start, int End, string Left) {  //поиск во внутреннем подмассиве самого близкого к правой границе элемента левой границы
    for (int i = End; i >= Start; i--) {
        if (S[i] == Left) {
            return i;   // искомый элемент найден, делаем возврат индекса
            break;
        }
    }
    return -1;  // искомый элемент не найден
}
void swap(string* a, string* b) {
    string temp = *a;
    *a = *b;
    *b = temp;
}
int main()
{
    int N;
    std::cin >> N;
    if (N <= 0) {
        std::cout << "Error!" << std::endl;
    }
    else {
        string* S = new string[N];
        for (int i = 0; i < N; i++) {
            std::cin >> S[i];           // ввод слова побуквенно
        }
        if (N == 1) {
            std::cout << "We have only 1 palindrome: " << S[0] << std::endl;
            std::cout << "0 swaps" << std::endl;
            return 0;
        }   // тривиальный случай, когда слово состоит из одной буквы, программа завершается
        else {
            int swaps = 0;          // подсчет обменов
            for (int i = 0; i < N / 2; i++) {       // проход от краев к центру
                if (S[i] == S[N - 1 - i]) {
                    continue;                   // если границы совпали, то делаем следующий сдвиг
                }
                else {
                    int L = LastofLeft(S, i + 1, N - 2 - i, S[i]);
                    int R = FirstofRight(S, i + 1, N - 2 - i, S[N - 1 - i]);    // если границы не совпали, ищем самые близкие к границам элементы во внутреннем подмассиве
                    if ((L == -1) && (R == -1)) {   // если не найдены элементы ни правой, ни левой границы, то слово не сможет стать палиндромом, программа завершается
                        std::cout << "It can't become a palyndrome!" << std::endl;
                        return 0;
                        break;
                    }
                    if ((L == -1) && (R != -1)) {   // если найден только элемент правой границы, делаем его сдвиг на левую границу
                        while (R != i) {
                            swap(S[R], S[R - 1]);
                            swaps++;
                            R--;
                        }
                    }
                    if ((L != -1) && (R == -1)) {   // если найден только элемент левой границы, делаем его сдвиг на правую границу
                        while (L != N - 1 - i) {
                            swap(S[L], S[L + 1]);
                            swaps++;
                            L++;
                        }
                    }
                    if ((L != -1) && (R != -1)) {
                        if (N - 1 - i - L <= R - i) {
                            while (L != N - 1 - i) {
                                swap(S[L], S[L + 1]);
                                swaps++;
                                L++;
                            }
                        }
                        else {
                            while (R != i) {
                                swap(S[R], S[R - 1]);
                                swaps++;
                                R--;
                            }
                        }
                    }       // если найдены оба возможных элемента для сдвига, сдвинем тот, на который уйдет меньше обменов
                }
            }
            std::cout << "Result string is: ";
            for (int i = 0; i < N;i++) {
                std::cout << S[i];
            }
            std::cout << "\n";
            std::cout << "Minimal number of swaps is: " << swaps << std::endl;
        }   // выводим результаты
        delete[] S;
    }
    return 0;
}
