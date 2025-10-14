#include <iostream>
#include <thread>
#include <chrono>

void simple_work(int id) {
    for (int i = 0; i < 3; ++i) {
        std::cout << "Thread " << id << " working... " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    std::cout << "Main thread started" << std::endl;
    
    // Создаем два потока
    std::thread t1(simple_work, 1);
    std::thread t2(simple_work, 2);
    
    std::cout << "Main thread continues working..." << std::endl;
    
    // Ждем завершения потоков
    t1.join();  // "Присоединяем" поток t1
    t2.join();  // "Присоединяем" поток t2
    
    std::cout << "All threads completed" << std::endl;
} 