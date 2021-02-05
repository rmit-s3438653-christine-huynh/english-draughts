/* direction.h (Paul Miller 2017)
 * Modified by S3438653 Christine Huynh 2017
 */
#include <climits>
#pragma once
namespace draughts
{
    enum class direction
    {
        UP=-1, DOWN=1, BOTH=2, INVALID=INT_MAX
    };
}
