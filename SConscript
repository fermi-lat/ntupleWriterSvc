# -*- python -*-
# $Header: /nfs/slac/g/glast/ground/cvs/ntupleWriterSvc/SConscript,v 1.1 2008/08/15 21:22:48 ecephas Exp $ 
# Authors: H. Kelly <heather@slac.stanford.edu>
# Version: ntupleWriterSvc-03-23-04
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