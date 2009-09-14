# -*- python -*-
# $Header: /nfs/slac/g/glast/ground/cvs/ntupleWriterSvc/SConscript,v 1.17 2009/05/22 18:30:22 glastrm Exp $ 
# Authors: H. Kelly <heather@slac.stanford.edu>
# Version: ntupleWriterSvc-05-04-01
import os
Import('baseEnv')
Import('listFiles')
Import('packages')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

libEnv.Tool('ntupleWriterSvcLib', depsOnly = 1)
ntupleWriterSvc = libEnv.SharedLibrary('ntupleWriterSvc', listFiles(['src/*.cxx']) + listFiles(['src/Dll/*.cxx']))

progEnv.Tool('ntupleWriterSvcLib')
test_ntupleWriterSvc = progEnv.GaudiProgram('test_ntupleWriterSvc',['src/test/writeJunkAlg.cxx'], test = 1)


progEnv.Tool('registerObjects', package = 'ntupleWriterSvc', libraries = [ntupleWriterSvc], testApps = [test_ntupleWriterSvc], \
includes = listFiles(['ntupleWriterSvc/*.h']))




