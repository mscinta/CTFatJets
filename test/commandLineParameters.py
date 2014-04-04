import FWCore.ParameterSet.VarParsing as VarParsing

# ################################################
# ----------------- options parsing --------------
# ################################################
# setup 'analysis'  options
options = VarParsing.VarParsing ('standard')

# register options
options.register ('inputFilesConfig',
                  "", # default value
                  VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                  VarParsing.VarParsing.varType.string,          # string, int, or float
                  "config file for inputs, automatically appended with _cff.py")

options.register ('outputFile',
                  "T1tttt", # default value
                  VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                  VarParsing.VarParsing.varType.string,          # string, int, or float
                  "root file for outputs, automatically appended with _sumJetMass_AnalysisTree.root")

options.register ('numEvents',
                  -1, # default value
                  VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                  VarParsing.VarParsing.varType.int,          # string, int, or float
                  "maximum number of events to analyze")

options.register ('skipEvents',
                  0, # default value
                  VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                  VarParsing.VarParsing.varType.int,          # string, int, or float
                  "number of events to skip before analyzing")

options.register ('reportEvery',
                  1000, # default value
                  VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                  VarParsing.VarParsing.varType.int,          # string, int, or float
                  "number of events to wait before printing report")

options.register ('applySUSYfilter',
                  False, # default value
                  VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                  VarParsing.VarParsing.varType.bool,          # string, int, or float
                  "if true filter is used to select a specific signal from gen-level info")

options.register ('useGenJets',
                  False, # default value
                  VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                  VarParsing.VarParsing.varType.bool,          # string, int, or float
                  "if true models will expect jet collections to be of the type vector< reco::GenJet >")

options.register ('mLSP',
                  475., # default value
                  VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                  VarParsing.VarParsing.varType.float,          # string, int, or float
                  "LSP mass, used for SUSY filter")

options.register ('mGo',
                  1150., # default value
                  VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                  VarParsing.VarParsing.varType.float,          # string, int, or float
                  "Gluino mass, used for SUSY filter")

options.register ('SUSYtopo',
                  "T1tttt", # default value
                  VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                  VarParsing.VarParsing.varType.string,          # string, int, or float
                  "topology used for SUSY filter")

options.register ('leptonicTopFilter',
                  True, # default value
                  VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                  VarParsing.VarParsing.varType.bool,          # string, int, or float
                  "use gen-level information to skip events in which a top decays leptonically")


options.register ('maxMHT',
                  9999999., # default value
                  VarParsing.VarParsing.multiplicity.singleton, #singleton or list
                  VarParsing.VarParsing.varType.float,          #string, int, or float
                  "maximum missing Ht")

options.register ('minMHT',
                  200., # default value
                  VarParsing.VarParsing.multiplicity.singleton, #singleton or list
                  VarParsing.VarParsing.varType.float,          #string, int, or float
                  "minimum missing Ht")

options.register ('minHT',
                  500., # default value
                  VarParsing.VarParsing.multiplicity.singleton, #singleton or list
                  VarParsing.VarParsing.varType.float,          #string, int, or float
                  "minimum Ht")

options.register ('maxHT',
                  9999999., # default value
                  VarParsing.VarParsing.multiplicity.singleton, #singleton or list
                  VarParsing.VarParsing.varType.float,          #string, int, or float
                  "maximum Ht")

options.register ('minNjets',
                  3, # default value
                  VarParsing.VarParsing.multiplicity.singleton, #singleton or list
                  VarParsing.VarParsing.varType.int,          #string, int, or float
                  "minimum number of jets")

options.register ('maxNjets',
                  9999999, # default value
                  VarParsing.VarParsing.multiplicity.singleton, #singleton or list
                  VarParsing.VarParsing.varType.int,          #string, int, or float
                  "maximum number of jets")



# get and parse the command line arguments
options.parseArguments()

# ------------------------------------------------
