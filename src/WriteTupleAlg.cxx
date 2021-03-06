/** @file WriteTupleAlg.cxx

*/
#include "GaudiKernel/Algorithm.h"

#include "GaudiKernel/MsgStream.h"
#include "GaudiKernel/AlgFactory.h"
#include "GaudiKernel/IDataProviderSvc.h"
#include "GaudiKernel/DataObject.h"
#include "GaudiKernel/SmartDataPtr.h"
#include "GaudiKernel/DataSvc.h"
#include "ntupleWriterSvc/INTupleWriterSvc.h"


/** @class WriteTupleAlg
 * @brief Test routine for the ntupleWriterSvc
 * 
 * $Header: /nfs/slac/g/glast/ground/cvs/GlastRelease-scons/ntupleWriterSvc/src/WriteTupleAlg.cxx,v 1.3.658.1 2010/10/08 16:43:48 heather Exp $
*/
class WriteTupleAlg : public Algorithm
{   
public:
    WriteTupleAlg(const std::string& name, ISvcLocator* pSvcLocator); 
    StatusCode initialize();
    StatusCode execute();
    StatusCode finalize();
private:
    INTupleWriterSvc* m_ntupleWriterSvc;
    int m_count;
    
    
};

//  factory stuff
//static const AlgFactory<WriteTupleAlg>  Factory;
//const IAlgFactory& WriteTupleAlgFactory = Factory;
DECLARE_ALGORITHM_FACTORY(WriteTupleAlg);


WriteTupleAlg::WriteTupleAlg(const std::string& name, ISvcLocator* pSvcLocator) 
:Algorithm(name, pSvcLocator) 
{
    m_count =0;
}


StatusCode WriteTupleAlg::initialize() { 
    MsgStream log(msgSvc(), name());
    log << MSG::INFO << "initialize" << endreq;
    StatusCode sc =StatusCode::SUCCESS;
    
    // Use the Job options service to set the Algorithm's parameters
    setProperties();
    

    sc = service("RootTupleSvc", m_ntupleWriterSvc);
    
    if(sc.isFailure())    {
        log << MSG::ERROR << "Could not locate the ntupleSvc" <<endreq;
    }


    return sc;
    
}


StatusCode WriteTupleAlg::execute() {

    // this is all this does, make sure that the tuple is saved
    m_ntupleWriterSvc->storeRowFlag(true);
    
    MsgStream   log( msgSvc(), name() );
    StatusCode  sc = StatusCode::SUCCESS;

    return sc;
}


StatusCode WriteTupleAlg::finalize() {
    
    MsgStream log(msgSvc(), name());
    return StatusCode::SUCCESS;
}

