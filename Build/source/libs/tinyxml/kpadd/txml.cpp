/* ----------------
 * txml.cpp
 *      papildymai prie tinyXML
 *
 *  Changelog:
 *      2013-06-12  mp  initial creation
 *
 */

#include "envir.h"

#include <stdio.h>
#include <iostream>
#ifdef __WIN32__
#include <windows.h>
#endif

using namespace std;

#include "kperrno.h"
#include "kpstdlib.h"
#include "kptt.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpmsg.h"
#include "kperr.h"

#include "tinyxml.h"

#include "txml.h"


// -----------------------------
TiXmlNode *FindNodeByName(const uchar *p_lpszTagName, TiXmlNode *p_pCurNode)
{
TiXmlNode *retv = NULL;

    KP_ASSERT(p_pCurNode != NULL, E_INVALIDARG, null);
    
    TiXmlNode* cur_child = NULL;
    for (cur_child = p_pCurNode->FirstChild() /* firstChild */; 
        (cur_child != NULL) && (retv == NULL); 
        cur_child = cur_child->NextSibling() /* next */)
    {
        if(cur_child->Type() == TiXmlNode::TINYXML_ELEMENT)
        {
            if (strcmp((const uchar *)cur_child->Value(), p_lpszTagName) == 0)
                retv = cur_child;
            else
                retv = FindNodeByName(p_lpszTagName, cur_child);
        }
    }

return (retv);
}


// -----------------------------
TiXmlNode *FindNodeById(const uchar *p_lpszId, TiXmlNode *p_pCurNode)
{
TiXmlNode *retv = NULL;

    KP_ASSERT(p_pCurNode != NULL, E_INVALIDARG, null);
    
    TiXmlNode* cur_child = NULL;
    for (cur_child = p_pCurNode->FirstChild() /* firstChild */; 
        (cur_child != NULL) && (retv == NULL); 
        cur_child = cur_child->NextSibling() /* next */)
    {
        if(cur_child->Type() == TiXmlNode::TINYXML_ELEMENT)
        {
        const uchar *id_str = (const uchar *)(dynamic_cast<TiXmlElement *>(cur_child)->Attribute("id"));
            if (id_str != null)
                if (strcmp(id_str, p_lpszId) == 0)
                    retv = cur_child;
            
            if (retv == NULL) retv = FindNodeById(p_lpszId, cur_child);
        }
    }

return (retv);
}


// ---------------------------------
const uchar *GetNodeVal(TiXmlNode *p_pNode)
{
const uchar *retv = null;

    TiXmlNode* cur_child = NULL;
    for (cur_child = p_pNode->FirstChild(); 
        (cur_child != NULL) && (retv == NULL); 
        cur_child = cur_child->NextSibling())
            if(cur_child->Type() == TiXmlNode::TINYXML_TEXT)
                retv = (const uchar *)cur_child->Value();

return (retv);
}


// ---------------------------------
const unsigned int NUM_INDENTS_PER_SPACE=2;

const char * getIndent( unsigned int numIndents )
{
	static const char * pINDENT="                                      + ";
	static const unsigned int LENGTH=strlen( pINDENT );
	unsigned int n=numIndents*NUM_INDENTS_PER_SPACE;
	if ( n > LENGTH ) n = LENGTH;

	return &pINDENT[ LENGTH-n ];
}

// same as getIndent but no "+" at the end
const char * getIndentAlt( unsigned int numIndents )
{
	static const char * pINDENT="                                        ";
	static const unsigned int LENGTH=strlen( pINDENT );
	unsigned int n=numIndents*NUM_INDENTS_PER_SPACE;
	if ( n > LENGTH ) n = LENGTH;

	return &pINDENT[ LENGTH-n ];
}

int dump_attribs_to_stdout(TiXmlElement* pElement, unsigned int indent)
{
	if ( !pElement ) return 0;

	TiXmlAttribute* pAttrib=pElement->FirstAttribute();
	int i=0;
	int ival;
	double dval;
	const char* pIndent=getIndent(indent);
	printf("\n");
	while (pAttrib)
	{
		printf( "%s%s: value=[%s]", pIndent, pAttrib->Name(), pAttrib->Value());

		if (pAttrib->QueryIntValue(&ival)==TIXML_SUCCESS)    printf( " int=%d", ival);
		if (pAttrib->QueryDoubleValue(&dval)==TIXML_SUCCESS) printf( " d=%1.1f", dval);
		printf( "\n" );
		i++;
		pAttrib=pAttrib->Next();
	}
	return i;	
}

void dump_to_stdout( TiXmlNode* pParent, unsigned int indent)
{
	if ( !pParent ) return;

	TiXmlNode* pChild;
	TiXmlText* pText;
	int t = pParent->Type();
	printf( "%s", getIndent(indent));
	int num;

	switch ( t )
	{
	case TiXmlNode::TINYXML_DOCUMENT:
		printf( "Document" );
		break;

	case TiXmlNode::TINYXML_ELEMENT:
		printf( "Element [%s]", pParent->Value() );
		num=dump_attribs_to_stdout(pParent->ToElement(), indent+1);
		switch(num)
		{
			case 0:  printf( " (No attributes)"); break;
			case 1:  printf( "%s1 attribute", getIndentAlt(indent)); break;
			default: printf( "%s%d attributes", getIndentAlt(indent), num); break;
		}
		break;

	case TiXmlNode::TINYXML_COMMENT:
		printf( "Comment: [%s]", pParent->Value());
		break;

	case TiXmlNode::TINYXML_UNKNOWN:
		printf( "Unknown" );
		break;

	case TiXmlNode::TINYXML_TEXT:
		pText = pParent->ToText();
		printf( "Text: [%s]", pText->Value() );
		break;

	case TiXmlNode::TINYXML_DECLARATION:
		printf( "Declaration" );
		break;
	default:
		break;
	}
	printf( "\n" );
	for ( pChild = pParent->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) 
	{
		dump_to_stdout( pChild, indent+1 );
	}
}
