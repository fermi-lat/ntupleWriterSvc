
#include "GaudiKernel/SvcFactory.h"
#include "GaudiKernel/MsgStream.h"

#include "GaudiKernel/Incident.h"
#include "GaudiKernel/IIncidentSvc.h"
#include "GaudiKernel/Property.h"

#include "GaudiKernel/INTuple.h"
#include "GaudiKernel/NTuple.h"
#include "GaudiKernel/SmartDataPtr.h"
#include "GaudiKernel/StatusCode.h"

#include "ntupleWriterSvc/ntupleWriterSvc.h"

#include <vector>
#include <stdlib.h>

#ifdef WIN32
#include <float.h> // used to check for NaN
#else
#include <math.h>
#endif

// Storage location for ntuples within the TDS
static std::string tupleRoot("/NTUPLES/");

// A value to insert into the ntuple when NaN or inf is
// passed in to be written
static float badValue = -99999.0;

unsigned int ntupleWriterSvc::m_tupleCounter;

// declare the service factories for the ntupleWriterSvc
static SvcFactory<ntupleWriterSvc> a_factory;
const ISvcFactory& ntupleWriterSvcFactory = a_factory;


// ------------------------------------------------
// Implementation of the ntupleWriterSvc class
// ------------------------------------------------
/// Standard Constructor
ntupleWriterSvc::ntupleWriterSvc(const std::string& name,ISvcLocator* svc)
: Service(name,svc)
{
    
    // declare the properties and set defaults
    declareProperty("tuple_name",  m_tuple_name);

    m_tupleCounter = 0;  // initialize the count to 0;
}


// initialize
StatusCode ntupleWriterSvc::initialize () 
{
    StatusCode  status =  Service::initialize ();
     
    // bind all of the properties for this service
    setProperties ();
    
    // open the message log
    MsgStream log( msgSvc(), name() );
 
    // use the incident service to register "end" events
    IIncidentSvc* incsvc = 0;
    status = serviceLocator()->getService ("IncidentSvc",
        IID_IIncidentSvc, reinterpret_cast<IInterface*&>( incsvc ));
    
    if( status.isFailure() ) return status;

    incsvc->addListener(this, "EndEvent", 0);

    // get a pointer to the Gaudi NTupleSvc
    status = serviceLocator()->getService("NTupleSvc", 
        IID_INTupleSvc, reinterpret_cast<IInterface*&>( ntupleSvc));

    if( status.isFailure() ) {
        log << MSG::ERROR << "ntupleWriterSvc failed to get the NTupleSvc" << endreq;
        return status;
    }

    // Setup the ntuples asked for in the job options file
    int index = 0;
    for (index = 0; index < m_tuple_name.size(); index++) {
        ++m_tupleCounter;
        // store the id for this ntuple
        m_TDS_tuple_name.push_back("/");
        // convert the id number into a string and append to the path name
        char tdsName[5];
        _itoa(m_tupleCounter, tdsName, 10);
        m_TDS_tuple_name[index] += tdsName;

        // Try to book the ntuple
        if( !m_tuple_name[index].empty() ) {
            // add this path into the map
            m_tuples[m_tuple_name[index]] = (tupleRoot+m_tuple_name[index]+m_TDS_tuple_name[index]);
            // create the ntuple
            status = bookNTuple(index);
        } else {
            log << MSG::INFO << "No tuple name supplied, no ntuple created "<< endreq;
        }
    }

    return status;
}


StatusCode ntupleWriterSvc::bookNTuple(int index) {

    StatusCode sc = StatusCode::SUCCESS;
    MsgStream log(msgSvc(), name());

    if (!m_tuple_name[index].empty()) {
        m_fileName.push_back(tupleRoot+m_tuple_name[index]);

        NTupleDirPtr dir(ntupleSvc, m_fileName[index]);
        if( dir ) {
            NTuplePtr *m_nt = new NTuplePtr( dir, m_TDS_tuple_name[index].c_str()); 
            if(!(*m_nt)){
                (*m_nt) = ntupleSvc->book(m_fileName[index],(index+1),CLID_RowWiseTuple, "The new Ntuple");
            } else {
                log << MSG::ERROR  << "could not book Ntuple" << endreq;
            }
        } else {
            log << MSG::ERROR << "NTUPLE directory could not be created " << endreq;
        }   
    }

    log << MSG::INFO << "Booked the ntuple " << m_fileName[index] << m_TDS_tuple_name[index] << endreq;
    return sc;
}




// handle "incidents"
void ntupleWriterSvc::handle(const Incident &inc)
{
    if(inc.type()=="EndEvent") endEvent();
}



void ntupleWriterSvc::endEvent()  // must be called at the end of an event to update, allow pause
{            
    
    StatusCode  sc = StatusCode::SUCCESS;
    MsgStream   log( msgSvc(), name() );
    
    // fill and write out the Gaudi tuple   
    int index = 0;
    for (index = 0; index < m_tuple_name.size(); index++) {
        sc = writeNTuple(index);
        if (sc.isFailure()) log << MSG::ERROR << "Could not write out ntuple " << (index+1) << endreq;
    }
   
}

StatusCode ntupleWriterSvc::writeNTuple(int index) {
    StatusCode  sc = StatusCode::SUCCESS;
    
    MsgStream log(msgSvc(), name());
    
    sc = ntupleSvc->writeRecord(m_fileName[index]+m_TDS_tuple_name[index]);

    log << MSG::INFO << "Wrote this event to the ntuple " << m_fileName[index] << m_TDS_tuple_name[index] << endreq;
    return sc;
}

// finalize
StatusCode ntupleWriterSvc::finalize ()
{
    StatusCode  status = StatusCode::SUCCESS;
       
    return status;
}
/// Query interface
StatusCode ntupleWriterSvc::queryInterface(const IID& riid, void** ppvInterface)  {
  if ( IID_INTupleWriterSvc.versionMatch(riid) )  {
    *ppvInterface = (INTupleWriterSvc*)this;
  }
  else  {
    return Service::queryInterface(riid, ppvInterface);
  }
  addRef();
  return SUCCESS;
}

SmartDataPtr<NTuple::Tuple> ntupleWriterSvc::getNTuple(const char *tupleName) {
    SmartDataPtr<NTuple::Tuple> m_nt(ntupleSvc, m_tuples[tupleName]);
    return m_nt;
}

StatusCode ntupleWriterSvc::addValue(const char *tupleName, const char *item, double val) {
    StatusCode sc = StatusCode::SUCCESS;
    MsgStream log(msgSvc(), name());

    SmartDataPtr<NTuple::Tuple> m_nt(ntupleSvc, m_tuples[tupleName]);

    NTuple::Item<float> ntItem;
    /// retrieve the item from the ntuple 
    sc = m_nt->item(item, ntItem);
    if (sc != StatusCode::SUCCESS) {
        log << MSG::ERROR << "failed to retrieve our ntuple item " << endreq;
        return sc;
    }
    if (!isFinite(val)) {
        log << MSG::INFO << "Attempt to add a non-finite value, inserting -99 instead" << endreq;
        ntItem = badValue;
    } else {
        ntItem = val;
    }

    return sc;
}


StatusCode ntupleWriterSvc::addItem(const char *tupleName, const char *item, double val) {

    StatusCode sc = StatusCode::SUCCESS;
    MsgStream log(msgSvc(), name());

    SmartDataPtr<NTuple::Tuple> m_nt(ntupleSvc, m_tuples[tupleName]);

    if (m_nt) {
        NTuple::Item<float> ntItem;
        // Check to see if this item has already been added into the ntuple
        sc = m_nt->item(item, ntItem);
        if (sc.isFailure()) {
            log << MSG::INFO << "Adding a new item to the ntuple " << item << endreq;
            m_nt->addItem(item, ntItem);
            if (!isFinite(val)) {
                log << MSG::INFO << "Attempt to add a non-finite value, inserting -99 instead" << endreq;
                ntItem = badValue;
            } else {
                ntItem = val;
            }
            sc = StatusCode::SUCCESS;
        } else {
            // Otherwise, this item is already in the ntuple and we are adding a new row
            return addValue(tupleName, item, val);
        }
    } else {
        return StatusCode::FAILURE;
    }

    return sc;
}

int ntupleWriterSvc::isFinite(float val) {

#ifdef WIN32 
    return (_finite(val));  // Win32 call available in float.h
#else
    return (isfinite(val)); // gcc call available in math.h
#endif

}