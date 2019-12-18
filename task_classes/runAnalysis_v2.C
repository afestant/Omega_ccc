#include <cmath>
#include "AliDummyHandler.h"
#include "AliAnalysisAlien.h"
#include "AliRecoDecayOmegac.h"
#include "AliRecoDecayOmegacc.h"
#include "AliRecoDecayOmegaccc.h"
#include "AliAnalysisTaskSEOmegacccToOmega3Pi.h"
// using namespace std;

//SETTINGS
//************************************

Bool_t runLocal=kTRUE;                                  // flag to run locally on AliAOD.root + AliAOD.VertexingHF.root
TString pathToLocalAODfiles="../input_files/bkg_Kr"; // ../input_files/bkg_Kr path to find AOD files when running locally
Bool_t runGridTest=kFALSE;                                // flag to run a grid test: kTRUE (+runLocal=kFALSE). To run job on GRID: runGridTest=kFALSE, runLocal=kFALSE
TString runMode="full";                                  // sets the run grid mode: "full", "terminate"

TString aliPhysVersion="vAN-20181128-1";

Bool_t isRunOnMC=kTRUE;                                 // set to kTRUE to run on Mone Carlo and uncomment/comment accordingly the following lines about paths on Alien
//paths on Alien
// Monte Carlo
TString gridDataDir="/alice/cern.ch/user/a/afestant/testHIJINGPYTHIAgen_omegaccc_bkg/output_Kr/";//"/alice/sim/2016/LHC16i2a/";
TString gridDataPattern="";//"/AOD198";
// Data
//TString gridDataDir="/alice/data/2015/LHC15o/";
//TString gridDataPattern="/pass1_pidfix/AOD194";


// Alien output directory
TString gridWorkingDir="testHIJINGPYTHIAgen_omegaccc_bkg/background_analysis_Kr";
TString gridOutputDir="output";

//run numbers
const Int_t nruns = 1;
Int_t runlist[nruns] = {245146};

//Task configuration
TString cutFile="./cutfile/D0DsDplusCuts.root";          // file containing the cuts for the different mesons
  														 // to generate the cut file: 1) move to cutfile directory
  														 //                           2) .L makeCutsTreeCreator.C
  														 //                           3) makeCutsTreeCreator();
  														 // to run with ROOT5/6 generate the cut file using AliPhysics built on ROOT5/6
  														 
  														 
  														 												 

//************************************

void runAnalysis_v2()
{
    
     // since we will compile a class, tell root where to look for headers  
#if !defined (__CINT__) || defined (__CLING__)
    gInterpreter->ProcessLine(".include $ROOTSYS/include");
    gInterpreter->ProcessLine(".include $ALICE_ROOT/include");
#else
    gROOT->ProcessLine(".include $ROOTSYS/include");
    gROOT->ProcessLine(".include $ALICE_ROOT/include");
#endif
    
    // Load libraries
    
 // MC generator libraries
    //gSystem->SetIncludePath("-I. -I$ROOTSYS/include -I$ALICE_ROOT -I$ALICE_ROOT/include -I$ALICE_ROOT/ITS -I$ALICE_ROOT/TPC -I$ALICE_ROOT/CONTAINERS -I$ALICE_ROOT/STEER/STEER -I$ALICE_ROOT/STEER/STEERBase -I$ALICE_ROOT/STEER/ESD -I$ALICE_ROOT/STEER/AOD -I$ALICE_ROOT/TRD -I$ALICE_ROOT/macros -I$ALICE_ROOT/ANALYSIS  -I$ALICE_ROOT/OADB -I$ALICE_ROOT/PWGJE -I$ALICE_ROOT/PWG/FLOW/Base -I$ALICE_ROOT/PWG/FLOW/Tasks -I$ALICE_ROOT/JETAN -I$ALICE_ROOT/CORRFW -I$ALICE_ROOT/PYTHIA6 -g");

    //gSystem->Load("liblhapdf.so");
    //gSystem->Load("libpythia6.4.25.so");
    //gSystem->Load("libEGPythia6");
    //gSystem->Load("libAliPythia6");
    
    
    //gSystem->Load("libpythia6");
    
    // set if you want to run the analysis locally (kTRUE), or on grid (kFALSE)
    Bool_t local = runLocal;
    // if you run on grid, specify test mode (kTRUE) or full grid model (kFALSE)
    Bool_t gridTest = runGridTest;
    
    // since we will compile a class, tell root where to look for headers  
// #if !defined (__CINT__) || defined (__CLING__)
//     gInterpreter->ProcessLine(".include $ROOTSYS/include");
//     gInterpreter->ProcessLine(".include $ALICE_ROOT/include");
// #else
//     gROOT->ProcessLine(".include $ROOTSYS/include");
//     gROOT->ProcessLine(".include $ALICE_ROOT/include");
// #endif
// 
// 	gSystem->Load("libEG");
//     gSystem->Load("libEGPythia6");
//     gSystem->Load("libgeant321.so");
//     gSystem->Load("liblhapdf.so");      // Parton density functions
//     gSystem->Load("libpythia6.so");     // Pythia
//     gSystem->Load("libAliPythia6.so");
     
    // create the analysis manager
    
   //  header location
//         gInterpreter->ProcessLine(".include $ROOTSYS/include");
//         gInterpreter->ProcessLine(".include $ALICE_ROOT/include");
    
    AliAnalysisManager *mgr = new AliAnalysisManager("AnalysisTaskExample");
    
    AliESDEvent *esdE = new AliESDEvent();
    esdE->CreateStdContent();
    AliESDVertex *vtx = new AliESDVertex(0.,0.,100);
    vtx->SetName("VertexTracks");
    vtx->SetTitle("VertexTracks");
    esdE->SetPrimaryVertexTracks(vtx);
    AliDummyHandler *dumH = new AliDummyHandler;//  static_cast<AliDummyHandler*>mgr->GetInputEventHandler();
    dumH->SetEvent(esdE);
    mgr->SetInputEventHandler(dumH);

    //mgr->SetInputEventHandler(new AliDummyHandler());
    AliMCEventHandler *mc = new AliMCEventHandler();
    mc->SetReadTR(kFALSE);
    mgr->SetMCtruthEventHandler(mc); 
    mgr->SetDebugLevel(10);
    
    // compile the class and load the add task macro
    // here we have to differentiate between using the just-in-time compiler
    // from root6, or the interpreter of root5
#if !defined (__CINT__) || defined (__CLING__)
    gInterpreter->LoadMacro("./R5Detector.cxx++g");
    gInterpreter->LoadMacro("./AliAnalysisTaskWeakDecayVertexer_mod.cxx++g");
    gInterpreter->LoadMacro("AliRecoDecayOmegac.cxx++g");
    gInterpreter->LoadMacro("AliRecoDecayOmegacc.cxx++g");
    gInterpreter->LoadMacro("AliRecoDecayOmegaccc.cxx++g");
    gInterpreter->LoadMacro("AliAnalysisTaskSEOmegacccToOmega3Pi.cxx++g");
    //AliAnalysisTaskSEOmegacccToOmega3Pi *task = reinterpret_cast<AliAnalysisTaskSEOmegacccToOmega3Pi*>(gInterpreter->ProcessLine(Form(".x %s",gSystem->ExpandPathName("AddTaskOmegacccToOmega3Pi.C"))));
    AliAnalysisTaskSEOmegacccToOmega3Pi *task = reinterpret_cast<AliAnalysisTaskSEOmegacccToOmega3Pi*>(gInterpreter->ExecuteMacro("AddTaskOmegacccToOmega3Pi.C"));
#else
    gROOT->LoadMacro("R5Detector.cxx++g");
    gROOT->LoadMacro("AliAnalysisTaskWeakDecayVertexer_mod.cxx++g");
    gROOT->LoadMacro("AliRecoDecayOmegac.cxx++g");
    gROOT->LoadMacro("AliRecoDecayOmegacc.cxx++g");
    gROOT->LoadMacro("AliRecoDecayOmegaccc.cxx++g");
    gROOT->LoadMacro("AliAnalysisTaskSEOmegacccToOmega3Pi.cxx++g");
    gROOT->LoadMacro("AddTaskOmegacccToOmega3Pi.C");
    AliAnalysisTaskSEOmegacccToOmega3Pi *task = AddTaskOmegacccToOmega3Pi();
#endif


    if(!mgr->InitAnalysis()) return;
    mgr->SetDebugLevel(11);
    mgr->PrintStatus();
    mgr->SetUseProgressBar(1, 25);

    if(local) {

        // if you want to run locally, we need to define some input
        TChain* chainAOD = new TChain("TE");
        //TChain *chainAODfriend = new TChain("TreeK");

        // add a few files to the chain (change this so that your local files are added)
        chainAOD->Add(Form("%s/galice.root",pathToLocalAODfiles.Data()));
        
        //for(Int_t i=1; i<=50; i++){
        //	chainAOD->Add(Form("%s/%d/galice.root",pathToLocalAODfiles.Data(),i));
        //}
        
        chainAOD->Print();

        // start the analysis locally, reading the events from the tchain
        //mgr->StartAnalysis("local", chainAOD);
        mgr->StartAnalysis("local", chainAOD,100);//, 100);//,2,103);//, 10);//,1,0);//,2,0);



    } else {

        // if we want to run on grid, we create and configure the plugin
        AliAnalysisAlien *alienHandler = new AliAnalysisAlien();

        // also specify the include (header) paths on grid
        alienHandler->AddIncludePath("-I. -I$ROOTSYS/include -I$ALICE_ROOT -I$ALICE_ROOT/include -I$ALICE_PHYSICS/include -I$ALICE_ROOT/PYTHIA6 -I$ALICE_PHYSICS/PWGLF");
        //gSystem->Load("libEG");
        //gSystem->Load("libEGPythia6");
        //gSystem->Load("liblhapdf.so");      // Parton density functions
        //gSystem->Load("libpythia6.so");     // Pythia
        //gSystem->Load("libAliPythia6.so");
        // make sure your source files get copied to grid
        //alienHandler->SetAdditionalLibs("AliHFCutOptTreeHandler.cxx AliHFCutOptTreeHandler.h");
        alienHandler->SetAdditionalLibs("R5Detector.cxx R5Detector.h AliAnalysisTaskWeakDecayVertexer_mod.cxx AliAnalysisTaskWeakDecayVertexer_mod.h AliRecoDecayOmegac.cxx AliRecoDecayOmegac.h AliRecoDecayOmegacc.cxx AliRecoDecayOmegacc.h AliRecoDecayOmegaccc.cxx AliRecoDecayOmegaccc.h AliAnalysisTaskSEOmegacccToOmega3Pi.cxx AliAnalysisTaskSEOmegacccToOmega3Pi.h");
        alienHandler->SetAnalysisSource("R5Detector.cxx AliAnalysisTaskWeakDecayVertexer_mod.cxx AliRecoDecayOmegac.cxx AliRecoDecayOmegacc.cxx AliRecoDecayOmegaccc.cxx AliAnalysisTaskSEOmegacccToOmega3Pi.cxx");

        // select the aliphysics version. all other packages
        // are LOADED AUTOMATICALLY!
        alienHandler->SetAliPhysicsVersion(aliPhysVersion.Data());

        // set the Alien API version
        alienHandler->SetAPIVersion("V1.1x");

        // select the input data
        //alienHandler->SetGridDataDir(gridDataDir.Data());
        //alienHandler->SetDataPattern(Form("%s/*AliAOD.root",gridDataPattern.Data()));
        //alienHandler->SetFriendChainName("AliAOD.VertexingHF.root");
        //alienHandler->SetDataPattern(Form("%s/*galice.root",gridDataPattern.Data()));
        //alienHandler->SetFriendChainName("Kinematics.root");

        // MC has no prefix, data has prefix 000
        //if(!isRunOnMC)alienHandler->SetRunPrefix("000");
        
        alienHandler->AddDataFile("/alice/cern.ch/user/a/afestant/testHIJINGPYTHIAgen_omegaccc_bkg/background_analysis_Kr/input_data_Kr.xml");
        alienHandler->SetUseMCchain();
        //alienHandler->SetNrunsPerMaster(1);
        //for(Int_t k=0; k<nruns; k++){
        //    alienHandler->AddRunNumber(runlist[k]);
        //}
        //alienHandler->SetNrunsPerMaster(nruns);

        // number of files per subjob
        alienHandler->SetSplitMaxInputFileNumber(1);
        alienHandler->SetExecutable("myTask.sh");

        // specify how many seconds your job may take
        alienHandler->SetTTL(10000);
        alienHandler->SetJDLName("myTask.jdl");

        //alienHandler->SetOutputToRunNo(kTRUE);
        alienHandler->SetKeepLogs(kTRUE);

        // merging: run with kTRUE to merge on grid
        // after re-running the jobs in SetRunMode("terminate") 
        // (see below) mode, set SetMergeViaJDL(kFALSE) 
        // to collect final results
        alienHandler->SetMaxMergeStages(3); //2, 3
        alienHandler->SetMergeViaJDL(kTRUE);

        // define the output folders
        alienHandler->SetGridWorkingDir(gridWorkingDir.Data());
        alienHandler->SetGridOutputDir(gridOutputDir.Data());

        // connect the alien plugin to the manager
        mgr->SetGridHandler(alienHandler);

        if(gridTest) {

            // speficy on how many files you want to run
            alienHandler->SetNtestFiles(1);
            // and launch the analysis
            alienHandler->SetRunMode("test");
            mgr->StartAnalysis("grid");
        } 
        else {
            // else launch the full grid analysis
            alienHandler->SetRunMode(runMode.Data()); //terminate
            mgr->StartAnalysis("grid");
        }
    }
}
