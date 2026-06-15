#ifndef TES4_H
#define TES4_H

struct TES4 {
    HEDR header;
    ZString author;
    ZString description;
    std::vector<Master> masters;
    std::vector<FormID> overridden_forms;
    uint32 tagify_strings_count;
    uint32 master_counter;
};

#endif
