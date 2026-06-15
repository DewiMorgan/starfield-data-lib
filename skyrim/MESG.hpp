#ifndef MESG_H
#define MESG_H

struct MESG {
    zstring editorId;
    lstring messageText;
    lstring title;
    uint32 unknown;
    formid quest;
    uint32 flags;
    uint32 time;
    std::vector<CTDA> conditionData;
    std::vector<lstring> responseTexts;
};


#endif