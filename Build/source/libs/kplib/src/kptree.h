/* -----------------------------
 * kptree.h
 *      tree-like structure definition
 *
 *  Changelog:
 *      2013-06-11  mp  initial creation
 *
 */


#ifndef KPTREE_INCLUDED
#define KPTREE_INCLUDED

#ifdef __cplusplus

template <class KpTreeRecType> 
class KpTreeEntry
{
private:
    KpTreeRecType *m_lpRecord;

public:
    KpTreeEntry<KpTreeRecType> *m_pFirstChild; // TeXtrcClass::FindFile() naudoja tiesioginį pointerį, po to trina listo elementą
private:
    KpTreeEntry<KpTreeRecType> *m_pNextBrother;
    KpTreeEntry<KpTreeRecType> *m_pPrevBrother;
    KpTreeEntry<KpTreeRecType> *m_pFather;


public:
    //-----------------------------------
    // create new record entry
    // stores allocated object pointer lpRecord to m_lpRecord
    // don't delete it after return
    KpTreeEntry(KpTreeRecType *lpRecord, KpTreeEntry<KpTreeRecType> *pFath = NULL)
    {
     // KP_ASSERT(lpRecord, E_INVALIDARG, null);
        m_lpRecord = lpRecord;

        m_pFather = pFath;
        m_pFirstChild = NULL;
        m_pPrevBrother = NULL;
        m_pNextBrother = NULL;
    }

    //-----------------------------------
    virtual ~KpTreeEntry()
    {
    KpTreeEntry<KpTreeRecType> *next_br = NULL;

        // loop on brothers – recursion could overfill the stack
        while (m_pNextBrother)
        {
            next_br = m_pNextBrother->GetNextBrother();
            m_pNextBrother->SetNextBrother(NULL);
//          m_pNextBrother->SetPrevBrother(NULL);

            KP_DELETE(m_pNextBrother);
            if (next_br) next_br->SetPrevBrother(this);
            SetNextBrother(next_br);
        }

        // recursion on children
        KP_DELETE(m_pFirstChild);

        KP_DELETE(m_lpRecord);
    }


    //-----------------------------------
    // get record object pointer m_lpRecord
    KpTreeRecType *GetValue(void) const { return(m_lpRecord); } 

    
// ------------------------------
// simply linear list methods based on father-child relations
// for not very big lists - deletion recursive

    //-----------------------------------
    // sets value of pointer to the next entry (child) m_pFirstChild
    // sets next chain member in case of linear list
    // pChild cannot be deleted after successfull SetFirstChild()
    // pChild->m_pFather turi sutapti su this
    // pChild->m_pPrevBrother turi buti NULL
    // naudojamas grubiam reikšmės nustatymui
    // pChild gali būti NULL
    void SetFirstChild(KpTreeEntry<KpTreeRecType> *pChild)
    {
    KpTreeEntry<KpTreeRecType> *father = NULL;
    KpTreeEntry<KpTreeRecType> *prev_brother = NULL;

        if (pChild)
        {
            father = pChild->GetFather();
            KP_ASSERT(father == this, KP_E_SYSTEM_ERROR, null);

            prev_brother = pChild->GetPrevBrother();
            KP_ASSERT(prev_brother == NULL, KP_E_SYSTEM_ERROR, null);
        }

        m_pFirstChild = pChild;
    }


    // prijungia vaiką (sekantį sąrašo elementą su visa uodega)
    // pChild cannnot be deleted after successfull ConnectChild()
    // nustato pChild->m_pFather į this
    // pChild->m_pPrevBrother turi buti NULL
    // this->m_pFirstChild turi būti NULL
    // naudojamas šakos/uodegos gražiam prijungimui
    void ConnectChild(KpTreeEntry<KpTreeRecType> *pChild)
    {
        KP_ASSERT(pChild, E_INVALIDARG, null);
        KP_ASSERT(m_pFirstChild == NULL, E_UNEXPECTED, null);
        if (pChild)
        {
//          KP_ASSERT(pChild->GetPrevBrother() == NULL, KP_E_SYSTEM_ERROR, null); // patikrins SetFirstChild()
            pChild->SetFather(this);
        }
        SetFirstChild(pChild);
    }


    //-----------------------------------
    // gets value of m_pFirstChild
    // gets pointer to next entry of the linear list
    // NULL - last entry
    KpTreeEntry<KpTreeRecType> *GetFirstChild(void) const { return(m_pFirstChild); }


    //-----------------------------------
    // uses the object *lpNode itself, don't delete it after return 
    void PutToEnd(KpTreeEntry<KpTreeRecType> *lpNode)
    {
    KpTreeEntry<KpTreeRecType> *cur_entry = this;
    KpTreeEntry<KpTreeRecType> *next_entry = NULL;

        KP_ASSERT(lpNode, E_INVALIDARG, null);

        do
        {
            next_entry = cur_entry->GetFirstChild();
            if (next_entry) cur_entry = next_entry;
        } while (next_entry);

        lpNode->SetFather(cur_entry);
        cur_entry->SetFirstChild(lpNode);
    }
    

// ------------------------------
// tree management methods


    //-----------------------------------
    KpTreeEntry<KpTreeRecType> *GetFather(void) const { return(m_pFather); };

    // nustato tėvą ir visiems tolimesniems broliams
    // pFath cannnot be deleted after successfull SetFather()
    void SetFather0(KpTreeEntry<KpTreeRecType> *pFath) // recursive entry
    {
        m_pFather = pFath;

        // recursion
        if (m_pNextBrother) m_pNextBrother->SetFather0(pFath);
    }

    // papildomai prie SetFather0(): pPrevBrother turi būti NULL
    void SetFather(KpTreeEntry<KpTreeRecType> *pFath)  // main entry
    {
        KP_ASSERT(m_pPrevBrother == NULL, KP_E_SYSTEM_ERROR, null);
        SetFather0(pFath);
    }


    //-----------------------------------
    KpTreeEntry<KpTreeRecType> *GetPrevBrother(void) const { return(m_pPrevBrother); }


    //-----------------------------------
    // pPrevBr cannnot be deleted after successfull SetPrevBrother()
    // pPrevBr->pFather turi sutapti su this->pFather
    void SetPrevBrother(KpTreeEntry<KpTreeRecType> *pPrevBr)
    {
    KpTreeEntry<KpTreeRecType> *father = NULL;

        if (pPrevBr)
        {
            father = pPrevBr->GetFather();
            KP_ASSERT(father == m_pFather, KP_E_SYSTEM_ERROR, null);
        }

        m_pPrevBrother = pPrevBr;
    }


    //-----------------------------------
    KpTreeEntry<KpTreeRecType> *GetNextBrother(void) const { return(m_pNextBrother); }
    

    //-----------------------------------
    // nustato sekantį brolį šiam mazgui (this)
    // pNextBr cannnot be deleted after successfull SetNextBrother()
    // pNextBr->pFather turi sutapti su this->pFather
    void SetNextBrother(KpTreeEntry<KpTreeRecType> *pNextBr)
    {
    KpTreeEntry<KpTreeRecType> *father = NULL;

        if (pNextBr)
        {
            father = pNextBr->GetFather();
            KP_ASSERT(father == m_pFather, KP_E_SYSTEM_ERROR, null);
        }

        m_pNextBrother = pNextBr;
    }


    //-----------------------------------
    // nustato sekantį brolį šiam mazgui (this)
    // pNextBr cannnot be deleted after successfull ConnectBrother()
    // nustato pNextBr->m_pFather=this->m_pFather
    // į galimai buvusį brolį pNextBr->m_pPrevBrother nekreipia dėmesio –
    //      užkloja ant viršaus
    void ConnectBrother(KpTreeEntry<KpTreeRecType> *pNextBr)
    {
        KP_ASSERT(pNextBr, E_INVALIDARG, null);
        KP_ASSERT(m_pNextBrother == NULL, E_UNEXPECTED, null);

        if(pNextBr)
        {
            pNextBr->SetPrevBrother(NULL);
            pNextBr->SetFather(m_pFather);
            pNextBr->SetPrevBrother(this);
        }

        SetNextBrother(pNextBr);
    }


    //-----------------------------------
    // appends new child AFTER the last child of this
    //    pChild cannot be deleted after successfull AppendChild()
    // nežiūrėdamas nustato pChild->pFather į this
    void AppendChild(KpTreeEntry<KpTreeRecType> *pChild)
    {
    KpTreeEntry<KpTreeRecType> *cur_brother = NULL;
    KpTreeEntry<KpTreeRecType> *next_brother = NULL;

        KP_ASSERT(pChild, E_INVALIDARG, null);

        // patikrins pChild->SetFather(this);
        // KP_ASSERT(pChild->GetPrevBrother() == NULL, E_INVALIDARG, null);

        pChild->SetFather(this);

        if(m_pFirstChild == NULL) ConnectChild(pChild);
        else
        {
            next_brother = m_pFirstChild;
            do
            {
                cur_brother = next_brother;
                next_brother = cur_brother->GetNextBrother();
            } while(next_brother);

            cur_brother->ConnectBrother(pChild);
        }
    }


    //-----------------------------------
    //  suskaičiuoja protėvius
    int GetDepth(void)
    {
    int ret_val = 0;

        if (m_pFather)
            ret_val = 1 + m_pFather->GetDepth();

    return(ret_val);
    }


    //-----------------------------------
    //  suskaičiuoja vyresnius brolius
    int GetDist(void)
    {
    int ret_val = 0;

        if (m_pPrevBrother)
            ret_val = 1 + m_pPrevBrother->GetDist();

    return(ret_val);
    }


    //-----------------------------------
    // Trina mazgą horizontaliai, vietoj jo atkeldamas tolesnius brolius
    // ištrina *pEntryPtr su visais vaikais
    // žr. DeleteKpTreeBros()
    // former DeleteKpTreeEntry()
    static void DeleteKpTreeChildren(KpTreeEntry<KpTreeRecType> **ppEntryPtr)
    {
        KP_ASSERT(ppEntryPtr, E_POINTER, null);
        KP_ASSERT(*ppEntryPtr, E_POINTER, null);

    KpTreeEntry<KpTreeRecType> *next_brother = (*ppEntryPtr)->GetNextBrother();
    KpTreeEntry<KpTreeRecType> *prev_brother = (*ppEntryPtr)->GetPrevBrother();
    KpTreeEntry<KpTreeRecType> *father = (*ppEntryPtr)->GetFather();

        if (next_brother) next_brother->SetPrevBrother(prev_brother);
        if (prev_brother) prev_brother->SetNextBrother(next_brother);

        // pirmas vaikas – nustatom naują tėvo pirmą vaiką
        if ((prev_brother == NULL) && father)
            father->SetFirstChild(next_brother);

        (*ppEntryPtr)->SetNextBrother(NULL);
        (*ppEntryPtr)->SetPrevBrother(NULL);
        KP_DELETE((*ppEntryPtr));

        *ppEntryPtr = next_brother;
    }


    //-----------------------------------
    // Trina mazgą vertikaliai, vietoj jo atkeldamas vaikus
    // žr. DeleteKpTreeChildren()
    // elementą *ppEntryPtr trina su visais broliais
    // tinka paprasto listo tėvai-vaikai tvarkymui;
    // papildytas ankstesnis DeleteChild()
    // former DeleteKpTreeNode()
    static void DeleteKpTreeBros(KpTreeEntry<KpTreeRecType> **ppEntryPtr)
    {
        KP_ASSERT(ppEntryPtr, E_POINTER, null);
        KP_ASSERT(*ppEntryPtr, E_POINTER, null);

    KpTreeEntry<KpTreeRecType> *first_child = (*ppEntryPtr)->GetFirstChild();
    KpTreeEntry<KpTreeRecType> *prev_brother = (*ppEntryPtr)->GetPrevBrother();
    KpTreeEntry<KpTreeRecType> *father = (*ppEntryPtr)->GetFather();

        if (first_child) 
        {
            first_child->SetPrevBrother(prev_brother);
            first_child->SetFather0(father);
        }
        if (prev_brother) prev_brother->SetNextBrother(first_child);

        (*ppEntryPtr)->SetFirstChild(NULL);
     // (*ppEntryPtr)->SetPrevBrother(NULL);
        KP_DELETE(*ppEntryPtr);

        // pirmas vaikas – nustatom naują tėvo pirmą vaiką
        if ((prev_brother == NULL) && father) father->SetFirstChild(first_child);
        // šiaip čia tas pats – ppEntryPtr ir rodo į tėvą
        *ppEntryPtr = first_child;
    }


// ----------------------------
// elementų sąrašo trynimas, kai sąrašas ilgas – rekursinis naikinimas gali užkišti steką
// sąrašas žemyn per vaikus m_pFirstChild
    static void KpTreeListDelete(KpTreeEntry<KpTreeRecType> *m_pListNodePtr)
    {
    KpTreeEntry<KpTreeRecType> *cur_entry = m_pListNodePtr;
    KpTreeEntry<KpTreeRecType> *first_child = NULL;
    
        while (cur_entry)
        {
            first_child = cur_entry->GetFirstChild();
            cur_entry->SetFirstChild(NULL);
            KP_DELETE(cur_entry);
            cur_entry = first_child;  
        }
    }

// ---------------------------------
// listo elementų skaičius (linijinio listo per vaikus m_pFirstChild)
    static int KpTreeListSize(KpTreeEntry<KpTreeRecType> *m_pListPtr)
    {
    KpTreeEntry<KpTreeRecType> *cur_entry = m_pListPtr;
    int node_cnt = 0;
    
        while (cur_entry)
        {
            node_cnt++;
            cur_entry = cur_entry->GetFirstChild();
        }
    
    return(node_cnt);
    }

};

#endif // #ifdef __cplusplus

#endif // #ifndef KPTREE_INCLUDED
