# -*- python -*-
# $Header: /nfs/slac/g/glast/ground/cvs/ntupleWriterSvc/SConscript,v 1.10 2009/01/23 00:07:11 ecephas Exp $ 
# Authors: H. Kelly <heather@slac.stanford.edu>
# Version: ntupleWriterSvc-05-00-00
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




