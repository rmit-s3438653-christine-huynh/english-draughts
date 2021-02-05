/* main_menu.h (Paul Miller 2017)
 * Modified by S3438653 Christine Huynh 2017
 */
 #include "menu.h"

#pragma once

namespace draughts
{
    namespace ncview
    {
        class main_menu : public menu
        {
            static const std::vector<std::string> strings;
            public:
                main_menu(void);
                virtual ~main_menu(void);
        };
    }
}
