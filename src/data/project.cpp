#include <data/project.h>
#include <data/config.h>

namespace  vertelien2 {
    Project::Project() {
        version = PROJECT_VERSION;
        GetUUID(uuid);
        tasks = std::vector<std::shared_ptr<Task>>();
        buffer_task_uuid = std::vector<char[36]>();
        memset(binder, 0, sizeof(binder));
        memset(title, 0, sizeof(title));
        memset(description, 0, sizeof(description));
    }

    Project::~Project() {
        for (auto i : tasks) i = nullptr;
    }

    void Project::ToBinary(char *data) const {
        serialization::ProjectSerialization::ToBinary(*this, data);
    }

    namespace serialization {
        static ProjectSerialization::SerializationCaller s_caller = nullptr;
        static ProjectSerialization::DeserializationCaller ds_caller = nullptr;

        void ProjectSerialization::RegisterCallerHandle(SerializationCaller caller) {
            s_caller = caller;
        }
        void ProjectSerialization::RegisterCallerHandle(DeserializationCaller caller) {
            ds_caller = caller;
        }

        uint32_t ProjectSerialization::ToBinary(const Project &project, char *&ptr) {
            uint32_t size = GetSize(project);

            uint32_t gap = 0;
            ptr = (char*)malloc(size);
            memcpy(&ptr[gap], &project.version, sizeof(Version));
            gap += sizeof(project.version);
            memcpy(&ptr[gap], &project.uuid, sizeof(project.uuid));
            gap += sizeof(project.uuid);
            memcpy(&ptr[gap], &project.title, sizeof(project.title));
            gap += sizeof(project.title);
            memcpy(&ptr[gap], &project.description, sizeof(project.description));
            gap += sizeof(project.description);
            uint32_t jobsSize = project.tasks.size();
            memcpy(&ptr[gap], &jobsSize, sizeof(uint32_t));
            gap += sizeof(uint32_t);
            for (int i = 0; i < jobsSize; i++) {
                memcpy(&ptr[gap], &project.tasks.at(i).get()->uuid, sizeof(project.uuid));
                gap += sizeof(project.uuid);
            }
            if (s_caller != nullptr) s_caller(ptr);
            return size;
        }
        Project * ProjectSerialization::ToData(uint32_t size, const char *ptr) {
            Project* project = new Project();
            uint32_t gap = 0;
            memcpy(&project->version, &ptr[gap], sizeof(Version));
            gap += sizeof(Version);
            memcpy(&project->uuid, &ptr[gap], sizeof(project->uuid));
            gap += sizeof(project->uuid);
            memcpy(&project->title, &ptr[gap], sizeof(project->title));
            gap += sizeof(project->title);
            memcpy(&project->description, &ptr[gap], sizeof(project->description));
            gap += sizeof(project->description);
            uint32_t tasksSize = 0;
            memcpy(&tasksSize, &ptr[gap], sizeof(tasksSize));
            gap += sizeof(tasksSize);
            project->buffer_task_uuid = std::vector<char[36]>(tasksSize);
            for (int i = 0; i < tasksSize; i++) {
                memcpy(&project->buffer_task_uuid[i], &ptr[gap], sizeof(project->uuid));
                gap += sizeof(project->uuid);
            }
            if (ds_caller != nullptr) ds_caller(*project);
            return project;
        }
        uint32_t ProjectSerialization::GetSize(const Project &project) {
            uint32_t size = 0;
            size += sizeof(Version);
            size += sizeof(project.uuid);
            size += sizeof(project.title);
            size += sizeof(project.description);
            size += sizeof(uint32_t);
            for (int i = 0; i < project.tasks.size(); i++) {
                size += sizeof(project.uuid);
            }
            return size;
        }

        uint32_t ProjectSerialization::ToBinary_Whole(const Project &project, char *&ptr) {
            uint32_t size = GetSize_Whole(project);

            uint32_t gap = 0;
            ptr = (char*)malloc(size);
            memcpy(&ptr[gap], &project.version, sizeof(Version));
            gap += sizeof(project.version);
            memcpy(&ptr[gap], &project.uuid, sizeof(project.uuid));
            gap += sizeof(project.uuid);
            memcpy(&ptr[gap], &project.title, sizeof(project.title));
            gap += sizeof(project.title);
            memcpy(&ptr[gap], &project.description, sizeof(project.description));
            gap += sizeof(project.description);
            uint32_t jobsSize = project.tasks.size();
            memcpy(&ptr[gap], &jobsSize, sizeof(uint32_t));
            gap += sizeof(uint32_t);
            for (int i = 0; i < jobsSize; i++) {
                memcpy(&ptr[gap], &project.tasks.at(i).get()->uuid, sizeof(project.uuid));
                gap += sizeof(project.uuid);
            }
            if (s_caller != nullptr) s_caller(ptr);
            return size;
            return 0;
        }
        Project * ProjectSerialization::ToData_Whole(uint32_t size, const char *ptr) {
            return nullptr;
        }
        uint32_t ProjectSerialization::GetSize_Whole(const Project &project) {
            uint32_t size = 0;
            size += sizeof(Version);
            size += sizeof(project.uuid);
            size += sizeof(project.title);
            size += sizeof(project.description);
            size += sizeof(uint32_t);
            for (int i = 0; i < project.tasks.size(); i++) {
                size += TaskSerialization::GetSize_Whole(*project.tasks.at(i).get());
            }
            return size;
        }
    }
}
