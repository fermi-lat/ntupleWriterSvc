# -*- python -*-
# $Header: /nfs/slac/g/glast/ground/cvs/GlastRelease-scons/ntupleWriterSvc/SConscript,v 1.8 2008/10/29 14:30:15 glastrm Exp $ 
# Authors: H. Kelly <heather@slac.stanford.edu>
# Version: ntupleWriterSvc-04-02-00
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



