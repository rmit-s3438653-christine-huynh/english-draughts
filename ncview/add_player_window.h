/* add_player_window.h (Paul Miller 2017)
 * Modified by S3438653 Christine Huynh 2017
 */
#include "window.h"
#pragma once
namespace draughts
{
    namespace ncview
    {
        class add_player_window : public window
        {
            public:
            virtual void activate(void) override;
            virtual ~add_player_window(void){}
        };
    }
}
