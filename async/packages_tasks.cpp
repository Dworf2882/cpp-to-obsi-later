#include <future>
#include <vector>
#include <chrono>
#include <thread>
#include <iostream>

int main() {
    // Создаем packaged_task для функции
    std::packaged_task<int(int, int)> task([](int a, int b) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return a + b;
    });
    
    // Получаем future для результата
    std::future<int> future = task.get_future();
    
    // Запускаем задачу в отдельном потоке
    std::thread t(std::move(task), 10, 20);
    
    std::cout << "Waiting for packaged_task result..." << std::endl;
    int result = future.get();
    std::cout << "Result: " << result << std::endl;
    
    t.join();
}