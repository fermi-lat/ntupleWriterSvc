/** 
 * @file ntupleWriterSvc_load.cxx
 *
 * @brief Implementation of <Package>_load routine.
 * This routine is needed for forcing the linker to load all the 
 * components of the library. 
 * 
 * $Header: /nfs/slac/g/glast/ground/cvs/ntupleWriterSvc/src/Dll/ntupleWriterSvc_load.cxx,v 1.3 2002/02/13 19:07:39 heather Exp $
 */

#include "GaudiKernel/DeclareFactoryEntries.h"

DECLARE_FACTORY_ENTRIES(ntupleWriterSvc) {
    DECLARE_SERVICE(ntupleWriterSvc);
    DECLARE_ALGORITHM(WriteTupleAlg);
} 

