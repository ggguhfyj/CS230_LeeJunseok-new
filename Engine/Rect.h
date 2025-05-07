#include "Vec2.h"

namespace Math {
    struct rect {
        Math::vec2 bottom_left{ 0.0, 0.0 };
        Math::vec2 top_right{ 0.0, 0.0 };
    };
    struct irect {
        Math::ivec2 bottom_left{ 0, 0 };
        Math::ivec2 top_right{ 0, 0 };
    };
}
