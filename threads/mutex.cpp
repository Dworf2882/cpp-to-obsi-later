#include <mutex>
#include <iostream>
#include <thread>
std::mutex cout_mutex;  // Защита для std::cout
int shared_counter = 0; // Разделяемые данные
std::mutex counter_mutex;

void unsafe_increment(int id) {
    for (int i = 0; i < 100; ++i) {
        // ❌ ОПАСНО: гонка данных (race condition)
        shared_counter++;
    }
}

void safe_increment(int id) {
    for (int i = 0; i < 100; ++i) {
        { // Блок для ограничения времени владения мьютексом
            std::lock_guard<std::mutex> lock(counter_mutex);
            shared_counter++;
        }
        
        // Безопасный вывод
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << shared_counter<<std::endl;
    }//Здеесь 2 мьюттекса чттобы пока один выводит консоль другой  добавлял count
}

int main() {
    std::thread t1(unsafe_increment, 1);
    std::thread t2(unsafe_increment, 2);
    
    t1.join();
    t2.join();
    
    // Результат может быть непредсказуемым!
    std::cout << "Unsafe counter: " << shared_counter << std::endl;
    
    shared_counter = 0; // Сброс
    
    std::thread t3(safe_increment, 3);
    std::thread t4(safe_increment, 4);
    
    t3.join();
    t4.join();
    
    // Результат всегда 2000
    std::cout << "Safe counter: " << shared_counter << std::endl;
}