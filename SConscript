# -*- python -*-
# $Header: /nfs/slac/g/glast/ground/cvs/GlastRelease-scons/ntupleWriterSvc/SConscript,v 1.19 2009/11/09 23:53:43 jrb Exp $ 
# Authors: H. Kelly <heather@slac.stanford.edu>
# Version: ntupleWriterSvc-05-04-02
import os
Import('baseEnv')
Import('listFiles')
Import('packages')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

libEnv.Tool('ntupleWriterSvcLib', depsOnly = 1)
ntupleWriterSvc = libEnv.SharedLibrary('ntupleWriterSvc',
                                       listFiles(['src/*.cxx']) + listFiles(['src/Dll/*.cxx']))

progEnv.Tool('ntupleWriterSvcLib')
test_ntupleWriterSvc = progEnv.GaudiProgram('test_ntupleWriterSvc',
                                            ['src/test/writeJunkAlg.cxx'],
                                            test = 1)


progEnv.Tool('registerTargets', package = 'ntupleWriterSvc',
             libraryCxts = [[ntupleWriterSvc, libEnv]],
             testAppCxts = [[test_ntupleWriterSvc, progEnv]], 
             includes = listFiles(['ntupleWriterSvc/*.h']))




