/** 
 * @file ntupleWriterSvc_load.cxx
 *
 * @brief Implementation of <Package>_load routine.
 * This routine is needed for forcing the linker to load all the 
 * components of the library. 
 * 
 * $Header: /nfs/slac/g/glast/ground/cvs/ntupleWriterSvc/src/Dll/ntupleWriterSvc_load.cxx,v 1.4 2002/04/08 21:13:20 heather Exp $
 */

#include "GaudiKernel/DeclareFactoryEntries.h"

DECLARE_FACTORY_ENTRIES(ntupleWriterSvc) {
    DECLARE_SERVICE(ntupleWriterSvc);
    DECLARE_SERVICE(RootTupleSvc);

    DECLARE_ALGORITHM(WriteTupleAlg);
} 

