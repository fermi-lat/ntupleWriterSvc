/** 
 * @file ntupleWriterSvc_dll.cxx
 *
 * @brief Implementation of the DllMain routine.  
 * The DLL initialization must be done seperately for each DLL. 
 * 
 * $Header: /nfs/slac/g/glast/ground/cvs/ntupleWriterSvc/src/Dll/ntupleWriterSvc_dll.cxx,v 1.2 2002/02/13 19:07:39 heather Exp $
 */

#include "GaudiKernel/LoadFactoryEntries.h"
LOAD_FACTORY_ENTRIES(ntupleWriterSvc)


//void FATAL(const char * msg) {
//    std::cerr << "FATAL error from ntupleWriterSvc DLL: " << msg << std::endl;/
//}

//void WARNING(const char * t){ std::cerr << "WARNING from ntupleWriterSvc DLL: " << t << std::endl; }
