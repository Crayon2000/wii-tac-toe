#include "mxml/mxml.h"
#include <ogc/conf.h>
#include "language.h"

// Languages
#include "english_xml.h"
#include "french_xml.h"
#include "german_xml.h"
#include "dutch_xml.h"
#include "spanish_xml.h"
#include "italian_xml.h"

/**
 * Constructor for the Language class.
 */
Language::Language()
{
    SetLanguage(CONF_GetLanguage());

    u8 i;
    mxml_node_t *Message_Node;
    mxml_node_t *Up_Node;

    Up_Node = mxmlFindElement(First_Node, First_Node, "tie_game", NULL, NULL, MXML_DESCEND);
    TieCount = ChildCount(Up_Node, "message");
    TieMessage = new std::string[TieCount];
    for(Message_Node = mxmlFindElement(Up_Node, Up_Node,"message", NULL, NULL, MXML_DESCEND), i = 0;
        Message_Node != NULL;
        Message_Node = mxmlFindElement(Message_Node, Up_Node, "message", NULL, NULL, MXML_DESCEND))
    {
        TieMessage[i++] = mxmlElementGetAttr(Message_Node, "text");
    }

    Up_Node = mxmlFindElement(First_Node, First_Node, "winning_game", NULL, NULL, MXML_DESCEND);
    WinningCount = ChildCount(Up_Node, "message");
    WinningMessage = new std::string[WinningCount];
    for(Message_Node = mxmlFindElement(Up_Node, Up_Node,"message", NULL, NULL, MXML_DESCEND), i = 0;
        Message_Node != NULL;
        Message_Node = mxmlFindElement(Message_Node, Up_Node, "message", NULL, NULL, MXML_DESCEND))
    {
        WinningMessage[i++] = mxmlElementGetAttr(Message_Node, "text");
    }

    Up_Node = mxmlFindElement(First_Node, First_Node, "turn_over", NULL, NULL, MXML_DESCEND);
    TurnOverCount = ChildCount(Up_Node, "message");
    TurnOverMessage = new std::string[TurnOverCount];
    for(Message_Node = mxmlFindElement(Up_Node, Up_Node,"message", NULL, NULL, MXML_DESCEND), i = 0;
        Message_Node != NULL;
        Message_Node = mxmlFindElement(Message_Node, Up_Node, "message", NULL, NULL, MXML_DESCEND))
    {
        TurnOverMessage[i++] = mxmlElementGetAttr(Message_Node, "text");
    }
}

/**
 * Destructor for the Language class.
 */
Language::~Language()
{
    if(First_Node != NULL)
    {
        mxmlDelete(First_Node);
    }

    delete[] WinningMessage;
    delete[] TieMessage;
    delete[] TurnOverMessage;
}

/**
 * Load a text from an XML file in memory.
 */
std::string Language::String(const char *From)
{
    if(From == NULL)
    {
        return "";
    }

    mxml_node_t *Text_Node = mxmlFindElement(First_Node, First_Node, "translation", "from", From, MXML_DESCEND);
    if(Text_Node == NULL)
    {
        return "";
    }

    return mxmlElementGetAttr(Text_Node, "to");
}

/**
 * Set the proper language.
 * @param[in] Conf_Lang Language ID to set.
 */
void Language::SetLanguage(s32 Conf_Lang)
{
    mxml_node_t *Root_Node;
    switch(Conf_Lang)
    {
        case CONF_LANG_FRENCH:
            Root_Node = mxmlLoadString(NULL, (char*)french_xml, MXML_TEXT_CALLBACK);
            break;
        case CONF_LANG_GERMAN:
            Root_Node = mxmlLoadString(NULL, (char*)german_xml, MXML_TEXT_CALLBACK);
            break;
        case CONF_LANG_DUTCH:
            Root_Node = mxmlLoadString(NULL, (char*)dutch_xml, MXML_TEXT_CALLBACK);
            break;
        case CONF_LANG_SPANISH:
            Root_Node = mxmlLoadString(NULL, (char*)spanish_xml, MXML_TEXT_CALLBACK);
            break;
        case CONF_LANG_ITALIAN:
            Root_Node = mxmlLoadString(NULL, (char*)italian_xml, MXML_TEXT_CALLBACK);
            break;
        case CONF_LANG_JAPANESE:
        case CONF_LANG_KOREAN:
        case CONF_LANG_SIMP_CHINESE:
        case CONF_LANG_TRAD_CHINESE:
        default:    // CONF_LANG_ENGLISH
            Root_Node = mxmlLoadString(NULL, (char*)english_xml, MXML_TEXT_CALLBACK);
    }
    First_Node = mxmlFindElement(Root_Node, Root_Node, "language", NULL, NULL, MXML_DESCEND);
}

/**
 * Count the number of child in a node.
 * @return Number of child in a node.
 */
unsigned int Language::ChildCount(mxml_node_s *Up_Node, const char *Name)
{
    int Count = 0;

    if(Up_Node != NULL)
    {
        mxml_node_t *Message_Node = NULL;
        for(Message_Node = mxmlFindElement(Up_Node, Up_Node, Name, NULL, NULL, MXML_DESCEND);
            Message_Node != NULL;
            Message_Node = mxmlFindElement(Message_Node, Up_Node, Name, NULL, NULL, MXML_DESCEND))
        {
            ++Count;
        }
    }
    return Count;
}

/**
 * Get a winning message.
 * @param[in] Index The index of the message the get.
 *            If the value is under 0, a random message will be returned.
 * @return A winning message.
 */
std::string Language::GetWinningMessage(s8 Index)
{
    if(Index < 0)
    {
        Index = rand() % WinningCount;
    }
    else if(Index >= WinningCount)
    {
        return "";
    }
    return WinningMessage[Index];
}
/**
 * Get a tie message.
 * @param[in] Index The index of the message the get.
 *            If the value is under 0, a random message will be returned.
 * @return A tie message.
 */
std::string Language::GetTieMessage(s8 Index)
{
    if(Index < 0)
    {
        Index = rand() % TieCount;
    }
    else if(Index >= TieCount)
    {
        return "";
    }
    return TieMessage[Index];
}
/**
 * Get a turn over message.
 * @param[in] Index The index of the message the get.
 *            If the value is under 0, a random message will be returned.
 * @return A turn over message.
 */
std::string Language::GetTurnOverMessage(s8 Index)
{
    if(Index < 0)
    {
        Index = rand() % TurnOverCount;
    }
    else if(Index >= TurnOverCount)
    {
        return "";
    }
    return TurnOverMessage[Index];
}
