#include <future>
#include <vector>
#include <chrono>
#include <thread>
#include <iostream>
// Долгая операция (имитация)
int expensive_calculation(int x) {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return x * x;
}
int main() {
    std::cout << "Starting async operations..." << std::endl;
    
    // Запускаем асинхронную задачу
    // std::launch::async - гарантирует выполнение в отдельном потоке
    std::future<int> future1 = std::async(std::launch::async, expensive_calculation, 5);//std::future - это "расписка" или "обещание" о результате, который будет готов в будущем.
    std::future<int> future2 = std::async(std::launch::async, expensive_calculation, 10);
    
    std::cout << "Async tasks started, main thread is free..." << std::endl;
    
    // Делаем другую работу в основном потоке
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Main thread doing other work..." << std::endl;
    // std::async - делаете заказ по телефону
    // std::future - получаете чек (расписку, что пицца будет)
    // future.get() - забираете готовую пиццу, когда она готова
 
    int result1 = future1.get();  // Может блокировать
    int result2 = future2.get();  // Может блокировать
    
    std::cout << "Results: " << result1 << ", " << result2 << std::endl;
}