#include <assert.h>
#include <iostream>
#include <data/task.h>

int main() {
    vertelien2::Task task = vertelien2::Task();
    strcpy(task.title, "Hello");
    strcpy(task.description, "World");
    task.jobs.push_back(std::make_shared<vertelien2::Job>(vertelien2::Job()));

    std::cout << "Create Task" << std::endl;
    std::cout << "\t version: " << task.version.to_string() << std::endl;

    std::cout << "\t uuid: ";
    for (auto i: task.uuid) std::cout << i;
    std::cout << std::endl;

    std::cout << "\t title: " << task.title << std::endl;
    std::cout << "\t description: " << task.description << std::endl;
    std::cout << "\t type: " << static_cast<uint32_t>(task.type) << std::endl;
    std::cout << "\t multi: " << task.multiKey << std::endl;
    std::cout << "\t cron: " << task.cronjobKey << std::endl;
    std::cout << "\t job: " << task.jobs.at(0).get()->uuid << std::endl;

    char* result;
    std::cout << "Convert binary" << std::endl;
    uint32_t size = vertelien2::serialization::TaskSerialization::ToBinary(task, result);
    std::cout << "Convert binary finish: " << size << std::endl;

    std::string raw = std::string(result, size);
    std::cout << "raw data: " << raw.c_str() << std::endl;

    std::cout << "Convert data" << std::endl;
    vertelien2::Task& convertTask = *vertelien2::serialization::TaskSerialization::ToData(size, result);
    std::cout << "Convert data finish" << std::endl;

    std::cout << "\t version: " << convertTask.version.to_string() << std::endl;

    std::cout << "\t uuid: ";
    for (auto i: convertTask.uuid) std::cout << i;
    std::cout << std::endl;

    std::cout << "\t title: " << convertTask.title << std::endl;
    std::cout << "\t description: " << convertTask.description << std::endl;
    std::cout << "\t type: " << static_cast<uint32_t>(convertTask.type) << std::endl;
    std::cout << "\t multi: " << convertTask.multiKey << std::endl;
    std::cout << "\t cron: " << convertTask.cronjobKey << std::endl;
    std::cout << "\t job: " << convertTask.buffer_job_uuid.at(0) << std::endl;

    assert(strcmp(task.uuid, convertTask.uuid) == 0);
    assert(strcmp(task.title, convertTask.title) == 0);
    assert(strcmp(task.description, convertTask.description) == 0);
    assert(strcmp(task.multiKey, convertTask.multiKey) == 0);
    assert(strcmp(task.cronjobKey, convertTask.cronjobKey) == 0);
    assert(task.type == convertTask.type);
    assert(task.jobs.size() == convertTask.buffer_job_uuid.size());
    assert(strcmp(task.jobs.at(0).get()->uuid, convertTask.buffer_job_uuid.at(0)) == 0);

    return 0;
}