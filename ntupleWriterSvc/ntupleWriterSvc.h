
#ifndef _H_ntupleWriterSvc_
#define _H_ntupleWriterSvc_

#include "GaudiKernel/Service.h"

#include "GaudiKernel/IIncidentListener.h"
#include "ntupleWriterSvc/INTupleWriterSvc.h"
#include "GaudiKernel/INTupleSvc.h"
#include "GaudiKernel/NTuple.h"

#include <map>

template <class TYPE> class SvcFactory;

/** 
 * @class ntupleWriterSvc
 * @brief A service that handles the ins and outs of writing to a ntuple the 
 * Gaudi framework.
 *
 * This service uses the Gaudi provided NTupleSvc and IncidentSvc.
 * The IncidentSvc is used to inform ntupleWriterSvc when we have reached the
 * beginning and the end of each event.  At the beginning of each event, the
 * ntupleWriterSvc clears the ntuple.  At the end of each event, the service
 * write to the ntuple in memory.
 * 
 * $Header: /nfs/slac/g/glast/ground/cvs/ntupleWriterSvc/ntupleWriterSvc/ntupleWriterSvc.h,v 1.13 2003/10/21 09:15:08 burnett Exp $
 */
class ntupleWriterSvc :  public Service, virtual public IIncidentListener,
                        virtual public INTupleWriterSvc
{  

public:
    
    /// perform initializations for this service - required by Gaudi
    virtual StatusCode initialize ();
    
    /// clean up after processing all events - required by Gaudi
    virtual StatusCode finalize ();

    /// Handles incidents, implementing IIncidentListener interface
    virtual void handle(const Incident& inc);    
 
   /// Query interface - required of all Gaudi services
   virtual StatusCode queryInterface( const IID& riid, void** ppvUnknown );

   /// Provide the named ntuple Ptr from the data store
   virtual SmartDataPtr<NTuple::Tuple> getNTuple(const char *tupleName);

   /// add a new item to an ntuple
   virtual StatusCode addItem(const char *tupleName, const char *item, double val);

   /**
        @param tupleName name of the tuple 
        @param itemName 
        @param val  pointer to the value, which must be defined 
   */
    virtual StatusCode addItem(const std::string & tupleName, const std::string& itemName, const double* val);

   /// force writing of the ntuple to disk
   virtual StatusCode saveNTuples();

   /// Set a flag to denote whether or not to store a row
   virtual void storeRowFlag(bool flag) { m_storeFlag = flag; };
   /// retrieve the flag that denotes whether or not to store a row
   virtual bool storeRowFlag() { return m_storeFlag; };

   /// check for NaN and infinity
   int isFinite(float val);

       /** store row flag by tuple Name option, retrive currrent
    @param tupleName Name of the tuple (TTree for RootTupleSvc implemetation)
    @param flag new value
    @return previous value
    This service  does not implement, it is ignored (return false)
    */
   virtual bool storeRowFlag(const std::string& /*tupleName*/, bool /*flag*/)
       { return false; }

protected: 

    ntupleWriterSvc ( const std::string& name, ISvcLocator* al );    

private:

    INTupleSvc *ntupleSvc;

    /// Allow SvcFactory to instantiate the service.
    friend class SvcFactory<ntupleWriterSvc>;
    /// routine to be called at the beginning of an event
    void beginEvent();
    /// routine that is called when we reach the end of an event
    void endEvent();
    /// create the ntuple
    StatusCode bookNTuple(int index, const char *title);
    /// write an event's data into the ntuple
    StatusCode writeNTuple(int index);
    /// add an entry into an ntuple, where the item has already been declared 
    StatusCode addValue(const char *tupleName, const char *item, double val);


    ///Maintain a list of each item so that this algorithm could handle multiple ntuples

    /// set non-blank to enable tuples
    std::vector<std::string> m_tuple_name;
    /// of the form "/1"
    std::vector<std::string> m_TDS_tuple_name;  
    /// path into the data store where the ntuple is located
    std::vector<std::string> m_fileName;

    /// Store ntuple Id and ntuple path in data store
    std::map<std::string, std::string> m_tuples;

    bool m_storeFlag;

    /// need the less for vc8
    typedef std::map< NTuple::Item<float> , const double*, std::less<const void*> > 
        NTupleItemMap;
    /// special map to set values from pointers at end of event
    NTupleItemMap  m_itemList;

    static unsigned int m_tupleCounter;
};


#endif // _H_ntupleWriterSvc
