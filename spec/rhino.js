load(java.lang.System.getenv("GEM_HOME") + "/gems/jspec-4.3.3/lib/jspec.js")
load('lib/mojo.js')
load('spec/spec.helpers.js')

JSpec
.exec('spec/mojo.spec.js')
.run({ reporter: JSpec.reporters.Terminal })
.report()