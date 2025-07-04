#include <utility/uuid.h>

int main(){
    char uuid[36];
    vertelien2::GetUUID(uuid);
    std::cout << uuid << std::endl;
    return 0;
}