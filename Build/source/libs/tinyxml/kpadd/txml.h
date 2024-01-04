/* ----------------
 * txml.h
 *      papildymai prie tinyXML
 *
 *  Changelog:
 *      2013-06-12  mp  initial creation
 *
 */

#ifndef txml_included
#define txml_included

// The first child of this node with the matching tag name. Will be null if none found.
// Searches through all grandchildren, starting from p_pCurNode
extern TiXmlNode* FindNodeByName(const uchar *p_lpszTagName, TiXmlNode *p_pCurNode);
// search for tag with corresponding value of attribute "id"
extern TiXmlNode *FindNodeById(const uchar *p_lpszId, TiXmlNode *p_pCurNode);

// Searches for text child, returns its value
extern const uchar *GetNodeVal(TiXmlNode *p_pNode);

extern void dump_to_stdout( TiXmlNode* pParent, unsigned int indent = 0 );

#endif // #ifndef txml_included
