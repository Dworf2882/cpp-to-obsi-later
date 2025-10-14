// Основное отличие:
//     std::async + future = "Заказал и забыл" (автоматика)
//     std::promise + future = "Ручное управление" (полный контроль)
// Аналогия: 🏭
// std::async - как заказ такси через приложение:
//     Нажал кнопку - такси едет
//     Не знаешь, какой именно автомобиль, какой маршрут
//     Просто ждешь результат
// std::promise + future - как собственный водитель:
//     Сам контролируешь, когда он поедет
//     Можешь дать особые инструкции
//     Полный контроль над процессом

#include <future>
#include <vector>
#include <chrono>
#include <thread>
#include <iostream>
// Функция, которая выполняется в отдельном потоке (рабочий поток)
void worker_function(std::promise<int> promise) {
    std::cout << "Worker started..." << std::endl;
    
    // Имитируем долгую работу (например, загрузку файла, вычисления и т.д.)
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    // 🎯 УСТАНАВЛИВАЕМ РЕЗУЛЬТАТ - говорим "задача выполнена, вот ответ!"
    // Это как сказать: "Пицца готова, забирайте!"
    promise.set_value(42);
    
    std::cout << "Worker completed" << std::endl;
}

int main() {
    // 🎪 СОЗДАЕМ "ДОГОВОР" МЕЖДУ ПОТОКАМИ
    
    // Promise (Обещание) - это КОНЕЦ ДЛЯ ЗАПИСИ
    // Рабочий поток будет "положить" сюда результат
    std::promise<int> promise;
    
    // Future (Будущее) - это КОНЕЦ ДЛЯ ЧТЕНИЯ  
    // Основной поток будет "забирать" отсюда результат
    std::future<int> future = promise.get_future();
    
    // 🚀 ЗАПУСКАЕМ РАБОЧИЙ ПОТОК
    // Передаем promise в поток (нужно использовать move, т.к. promise нельзя копировать)
    std::thread worker(worker_function, std::move(promise));
    
    std::cout << "Main thread waiting for result..." << std::endl;
    
    // ⏳ ОСНОВНОЙ ПОТОК ЖДЕТ РЕЗУЛЬТАТ
    // future.get() - это как сказать: "Жду, пока пицца будет готова"
    // Этот вызов БЛОКИРУЕТ основной поток, пока worker не выполнит promise.set_value()
    int result = future.get();  
    
    // 🎉 ПОЛУЧАЕМ РЕЗУЛЬТАТ!
    std::cout << "Got result: " << result << std::endl;
    
    // Ждем завершения рабочего потока (как join() в обычных потоках)
    worker.join();
}