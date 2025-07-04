#include <assert.h>
#include <iostream>
#include <data/job.h>
#include <utility/uuid.h>

int main() {
    vertelien2::Job job = vertelien2::Job();
    job.version = {5, 0, 7};
    job.script = "hello world";

    std::cout << "Create Job" << std::endl;
    std::cout << "\t version: " << job.version.to_string() << std::endl;
    std::cout << "\t uuid: " << job.uuid << std::endl;
    std::cout << "\t cate: " << (int32_t)job.category << std::endl;
    std::cout << "\t sub-cate: " << job.subCategory.index << std::endl;
    std::cout << "\t script: " << job.script << std::endl;

    char* result;
    std::cout << "Convert binary" << std::endl;
    uint32_t size = vertelien2::serialization::JobSerialization::ToBinary(job, result);
    std::cout << "Convert binary finish: " << size << std::endl;

    std::string raw = std::string(result, size);
    std::cout << "raw data: " << raw.c_str() << std::endl;

    std::cout << "Convert data" << std::endl;
    vertelien2::Job& convertJob = *vertelien2::serialization::JobSerialization::ToData(size, result);
    std::cout << "Convert data finish" << std::endl;

    std::cout << "\t version: " << convertJob.version.to_string() << std::endl;
    std::cout << "\t uuid: " << convertJob.uuid << std::endl;
    std::cout << "\t cate: " << (int32_t)convertJob.category << std::endl;
    std::cout << "\t sub-cate: " << convertJob.subCategory.index << std::endl;
    std::cout << "\t script: " << convertJob.script << std::endl;
    assert(convertJob.version == job.version);
    assert(strcmp(convertJob.uuid, job.uuid) == 0);
    assert(convertJob.category == job.category);
    assert(convertJob.subCategory.index == job.subCategory.index);
    assert(convertJob.script == job.script);
    assert(convertJob.args.size() == job.args.size());

    free(result);
    return 0;
}