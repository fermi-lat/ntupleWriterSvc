# $Header: /nfs/slac/g/glast/ground/cvs/GlastRelease-scons/ntupleWriterSvc/ntupleWriterSvcLib.py,v 1.2 2008/10/28 16:59:34 ecephas Exp $
def generate(env, **kw):
    if not kw.get('depsOnly', 0):
        env.Tool('addLibrary', library = ['ntupleWriterSvc'])
        if env['PLATFORM']=='win32' and env.get('CONTAINERNAME','')=='GlastRelease':
	    env.Tool('findPkgPath', package = 'ntupleWriterSvc') 
    env.Tool('facilitiesLib')
    env.Tool('addLibrary', library = env['gaudiLibs'])
    env.Tool('addLibrary', library = env['rootLibs'])
def exists(env):
    return 1;
