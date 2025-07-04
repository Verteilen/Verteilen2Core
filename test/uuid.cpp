#include <cassert>
#include <utility/uuid.h>

int main(){
    char uuid[36];
    vertelien2::GetUUID(uuid);
    for (int i = 0; i < 36; i++) {
        if (i == 8 || i == 13 || i == 18 || i == 23) {
            assert(uuid[i] == 45);
        }else {
            bool nr = uuid[i] >= 48 && uuid[i] <= 57;
            bool cr = uuid[i] >= 97 && uuid[i] <= 112;
            assert(nr || cr);
        }
    }
    std::cout << "uuid: " << uuid << std::endl;

    return 0;
}