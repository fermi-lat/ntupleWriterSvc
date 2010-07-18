# -*- python -*-
# $Header: /nfs/slac/g/glast/ground/cvs/ntupleWriterSvc/SConscript,v 1.22 2010/06/13 07:02:54 jrb Exp $ 
# Authors: H. Kelly <heather@slac.stanford.edu>
# Version: ntupleWriterSvc-05-04-04
import os
Import('baseEnv')
Import('listFiles')
Import('packages')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

libEnv.Tool('addLinkDeps', package='ntupleWriterSvc', toBuild='component')
ntupleWriterSvc =libEnv.SharedLibrary('ntupleWriterSvc',
                                      listFiles(['src/*.cxx','src/Dll/*.cxx']))

progEnv.Tool('ntupleWriterSvcLib')

test_ntupleWriterSvc =progEnv.GaudiProgram('test_ntupleWriterSvc',
                                           ['src/test/writeJunkAlg.cxx'],
                                           test = 1, package='ntupleWriterSvc')


progEnv.Tool('registerTargets', package = 'ntupleWriterSvc',
             libraryCxts = [[ntupleWriterSvc, libEnv]],
             testAppCxts = [[test_ntupleWriterSvc, progEnv]], 
             includes = listFiles(['ntupleWriterSvc/*.h']),
             jo = ['src/test/jobOptions.txt'])




