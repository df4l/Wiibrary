#include "epub.h"

void extract_cover(const char *epub_path)
{
    struct zip *epub = zip_open(epub_path, 0, NULL);
    if(!epub)
    {
        return;
    }

    for(zip_int64_t i = 0; i < zip_get_num_entries(epub, 0); i++)
    {
        const char *name = zip_get_name(epub, i, 0);

        if (strstr(name, "cover") && (strstr(name, ".jpg") || strstr(name, ".png")))
        {
            struct zip_file *file = zip_fopen(epub, name, 0);

            
        }
    }
}