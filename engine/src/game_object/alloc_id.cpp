#include <game_object/alloc_id.h>
#include <cstdlib>

using namespace std;

#if defined(USE_ATOMIC)
#include <atomic>
uint64_t alloc_game_object_id()
{
    static std::atomic_uint_least64_t __game_object_id_index_safe;
    return __game_object_id_index_safe++;
}
#else
uint64_t alloc_game_object_id()
{
    static uint64_t __game_object_id_index;
    return __game_object_id_index++;
}

#endif
