/* ===============================================
 *
 * kpstdlib.cpp
 *
 *    common tools for all Kp C++ projects
 *
 * 2013-02-22  mp  initial creation
 *
 */

// -----------------------------
#include "envir.h"

#include <string.h>
#include <string>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <math.h>
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
#include "kpcapp.h"

using namespace std;


// ========================================= KpLib 
KpErrorClass KpError((const uchar *)"kplib", True);
KpCommonApp *KpApp = NULL;
KpCommonApp *KpAppAlloc = NULL; // pointer to locally here allocated KpApp 

void KpInit(const uchar *ProdName, const void *pStackTop)
{
    try
    {
        if (KpApp == NULL) // allocate just in case when not allocated in the main application
        {
            KP_NEW(KpAppAlloc, KpCommonApp(ProdName, 0));
            KpApp = KpAppAlloc;
        }
        KpApp->Init(
#ifdef __WIN32__
            GetModuleHandle(NULL), (const uchar *)GetCommandLine(),
#else
// TODO Linux: get cmd line
            0, ProdName,
#endif             
            pStackTop);
    }
    catch(const KpException *e)
    {
        KP_CATCH(*e);
    }
    catch(const exception &e)
    {
        KP_CATCH(e);
    }
    catch(...)
    {
        KP_ERROR(KP_E_UNHANDLED_EXCEPTION, null);
    }
}


void KpClose(void)
{
    try
    {
        KP_ASSERT(KpApp, E_POINTER, null);
        KpApp->Close();
        if (KpAppAlloc)
        {
            KP_DELETE(KpAppAlloc /* KpApp */); // delete just in case when allocated not in the main application
            KpApp = KpAppAlloc;
        }
    }
    catch(const KpException *e)
    {
        KP_CATCH(*e);
    }
    catch(const exception &e)
    {
        KP_CATCH(e);
    }
    catch(...)
    {
        KP_ERROR(KP_E_UNHANDLED_EXCEPTION, null);
    }
}


// ========================================= malloc

// -----------------------------
#ifdef _MSC_VER
void *xmalloc(size_t size)
{
    void *ptr = malloc(size);
    if (!ptr)
        abort();
    return ptr;
}
#endif

// -----------------------------
// memory allocation control
#ifdef KP_ALLOC_SAFE
KpHeapClass KpHeap;

int KpHeapClass::SearchHeapEntry(const void *pPtr) // -1 – did not find
{
int ret_val = -1;

   for (int ii = 0; ii < m_iCurKpHeapIx; ii++)
      if (m_KpHeapArray[ii].m_pAddress == pPtr)
      {
         ret_val = ii;
         break;
      }

return(ret_val);
}


void KpHeapClass::InsertHeapPtr(const void *pNewPtr, bool bArrayFl)
{
HRESULT retc = S_OK;

uchar msg_out[MAX_LONG_HEX_DIGITS + 5];
   sprintf((char *)msg_out, "%lx", (unsigned long)pNewPtr);

int ix = SearchHeapEntry(pNewPtr);
   KP_ASSERTW(ix < 0, KP_E_DOUBLE_CALL, null);

   KP_ASSERTW(m_iCurKpHeapIx < KP_HEAP_SIZE - 1, KP_E_BUFFER_OVERFLOW, msg_out);
   if (SUCCEEDED(retc))
   {
      m_KpHeapArray[m_iCurKpHeapIx].m_pAddress = pNewPtr;
      m_KpHeapArray[m_iCurKpHeapIx].m_bArrayFl = bArrayFl;
      m_iCurKpHeapIx++;
   }
}


HRESULT KpHeapClass::RemoveHeapPtr(const void *pDelPtr, bool bArrayFl)
{
HRESULT retc = S_OK;

uchar msg_out[MAX_LONG_HEX_DIGITS + 5];
   sprintf((char *)msg_out, "%lx", (DWORD)pDelPtr);

int ix = SearchHeapEntry(pDelPtr);
   KP_ASSERTW(ix >= 0, KP_E_SYSTEM_ERROR, msg_out);
   KP_ASSERTW(m_KpHeapArray[ix].m_bArrayFl == bArrayFl, KP_E_SYSTEM_ERROR, msg_out);
// if (FAILED(retc)) KpError.StackDump();

   if ((ix >= 0) /* SUCCEEDED(retc) */)
   {
      memmove(&(m_KpHeapArray[ix]), &(m_KpHeapArray[ix + 1]), (m_iCurKpHeapIx - ix - 1) * sizeof(KpHeapEntry));
      m_iCurKpHeapIx--;
   }

return(retc);
}
#endif // #ifdef KP_ALLOC_SAFE


// ----------------------------------
void I2BinStr(uchar *p_lpszBinStrBuf, int p_iVal)
{
    KP_ASSERT(p_lpszBinStrBuf, E_INVALIDARG, null);
uchar *pntd = p_lpszBinStrBuf + 16;
    *pntd = Nul;
int val = p_iVal;     
    for (int ii = 0; ii < 16; ii++)
    {
        *(--pntd) = (val & 1)?'1':'0';
        val >>= 1;         
    }         
}


// ----------------------------------
double NormAngle(double p_dAngle)
{
double whole = 0.0;
double fract = modf(p_dAngle / (2.0 * M_PI), &whole);

double angle = fract * (2.0 * M_PI);
    if (angle >= M_PI) angle -= (2.0 * M_PI);
    else if (angle < -M_PI) angle += (2.0 * M_PI);

return(angle);
}

