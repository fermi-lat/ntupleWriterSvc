# -*- python -*-
# $Header: /nfs/slac/g/glast/ground/cvs/ntupleWriterSvc/SConscript,v 1.29 2012/08/20 19:07:59 jrb Exp $ 
# Authors: H. Kelly <heather@slac.stanford.edu>
# Version: ntupleWriterSvc-06-02-01
import os
Import('baseEnv')
Import('listFiles')
Import('packages')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

libEnv.Tool('addLinkDeps', package='ntupleWriterSvc', toBuild='component')
ntupleWriterSvc =libEnv.ComponentLibrary('ntupleWriterSvc',
                                         listFiles(['src/*.cxx']))

progEnv.Tool('ntupleWriterSvcLib')

test_ntupleWriterSvc =progEnv.GaudiProgram('test_ntupleWriterSvc',
                                           ['src/test/writeJunkAlg.cxx'],
                                           test = 1, package='ntupleWriterSvc')


progEnv.Tool('registerTargets', package = 'ntupleWriterSvc',
             libraryCxts = [[ntupleWriterSvc, libEnv]],
             testAppCxts = [[test_ntupleWriterSvc, progEnv]], 
             includes = listFiles(['ntupleWriterSvc/*.h']),
             jo = ['src/test/jobOptions.txt'])




