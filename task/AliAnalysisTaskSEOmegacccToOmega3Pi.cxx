/**************************************************************************
 * Copyright(c) 1998-2009, ALICE Experiment at CERN, All rights reserved. *
 *                                                                        *
 * Author: The ALICE Off-line Project.                                    *
 * Contributors are mentioned in the code where appropriate.              *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/

/* $Id$ */

/////////////////////////////////////////////////////////////
//
//
//
// \authors: Andrea Festanti
// \email:   andrea.festanti@cern.ch
//
////////////////////////////////////////////////////////////

#include <iostream>
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TList.h"
#include "TChain.h"
#include <THnSparse.h>
#include <TMath.h>
#include <TDatabasePDG.h>
#include "TObjArray.h"
#include "TArrayI.h"
#include <TClonesArray.h>
#include <TObjectTable.h>

#include "AliAnalysisTask.h"
#include "AliAnalysisManager.h"
#include "AliAnalysisTaskSE.h"
#include "AliMCEvent.h"
#include "AliVEvent.h"
#include "AliGenEventHeader.h"
#include "AliVParticle.h"
#include "AliStack.h"
#include "AliInputEventHandler.h"
#include "AliGenCocktailEventHeader.h"

#include "AliAnalysisTaskSE.h"
#include "AliAnalysisManager.h"
#include "AliAnalysisDataContainer.h"
#include "AliESDEvent.h"
#include "AliESDtrackCuts.h"
#include "AliCentrality.h"
#include "AliMCEventHandler.h"
#include "AliMCEvent.h"
#include "AliHeader.h"
#include "AliGenCocktailEventHeader.h"
#include "AliGenHijingEventHeader.h"
#include "AliGenEventHeader.h"
#include "AliCollisionGeometry.h"
#include "AliGenerator.h"
#include "AliVertexingHFUtils.h"
#include "AliVertexerTracks.h"
#include "AliMultiplicity.h"
#include <TParticle.h>
#include <TSystem.h>
#include <TTree.h>
#include <TNtuple.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TH3F.h>
#include <TChain.h>

#include "AliAnalysisTaskSEOmegacccToOmega3Pi.h"

using std::cout;
using std::endl;

/// \cond CLASSIMP
ClassImp(AliAnalysisTaskSEOmegacccToOmega3Pi);
/// \endcond

//________________________________________________________________________
AliAnalysisTaskSEOmegacccToOmega3Pi::AliAnalysisTaskSEOmegacccToOmega3Pi():
AliAnalysisTaskSE(),
fMcEvent(0x0),
fMcHandler(0x0),
fStack(0x0),
fEvent(0x0),
fVertexerTracks(0x0),
fBzkG(0.),
fV1(0x0),
fEtaCut(2.),
fEvtCount(0),
fNentries(0x0),
fOutputGen(0x0),
fOutputReco(0x0),
fITS(0x0),
fHistNcollHFtype(0x0),
fHistNinjectedbvsb(0x0),
fHistNinjectedcvsb(0x0),
fHistoNbVsNcPYTHIA(0x0),
fHistoNbVsNcHIJING(0x0),
fIsMCSignalProd(true),
fRecoPt(0.),
fRecoPhi(0.),
fRecoEta(0.),
fRecoY(0.),
fGenPt(0.),
fGenEta(0.),
fGenRad(0.),
fRecoNhits(-1),
fRecoMClabel(-99),
fRecoMClabelMother(-99),
fGenPtMother(0.),
fRecoPdg(-99),
fRecoPdgMother(-99),
fRecoNReconstructableHits(-1),
fTreeRecoTracks(0x0),
fTreeGenOmegaccc(0x0),
fTreeTrueOmegaccc(0x0),
fTreeCutVar(0x0),
fIsSignal(false),
fTreeVariableDecVtxChi2NdfOmegac(0.),
fTreeVariableDecayLengthOmegac(0.),
fTreeVariableDecayLengthXYOmegac(0.),
fIsSignalOmegac(false),
fTreeCutVarOmegac(0x0),
fTreeGenCascV0Reco(0x0),
fTreeGenVarCascV0RecoInvMass(0.),
fTreeGenV0Reco(0x0),
fTreeGenVarV0RecoInvMass(0.),
fNHitsAssigned(0),
fParticlePdg(0),
fMotherPdg(0),
fParticleVarPdg(0),
fParticleVarPdgMoth(0),
fParticleVarPt(0),
fParticleVarP(0),
fParticleVarEta(0),
fParticleVarRap(0),
fParticleVarPhi(0),
fParticleVarX(0),
fParticleVarY(0),
fParticleVarZ(0),
fParticleVarRxy(0),
fParticleVarNhitsAssigned(0),
fParticleVarNhitsReco(0),
fParticleVarIsReco(false),
fTreeReconstruction(0x0)
{
    
    for(Int_t i=0; i<11; i++){
        fTreeGenVarOmegacccNRHits[i]=-1;
        fTreeGenVarOmegacccPDG[i]=-1;
        fOmegacVariables[i]=0.;
        fOmegaccVariables[i]=0.;
        fOmegacccVariables[i]=0.;
        for(Int_t j=0; j<5; j++){
            fTreeGenVarOmegaccc[i][j]=0.;
            if(i<5){
                fTreeGenVarCascV0Reco[i][j]=0.;
            }
        }
        if(i<5)fTreeGenVarCascV0RecoPDG[i]=0;
        if(i<3){
            fTreeVariableDecVtxChi2Ndf[i]=0.;
            fTreeVariableCosPointingAngle[i]=0.;
            fTreeVariableCosPointingAngleXY[i]=0.;
            fTreeVariableDecayLength[i]=0.;
            fTreeVariableDecayLengthXY[i]=0.;
            fTreeVariableInvMass[i]=0.;
            for(Int_t j=0; j<5; j++){
                fTreeGenVarV0Reco[i][j]=0.;
            }
            fTreeGenVarV0RecoPDG[i]=0;
        }
        if(i==3)fTreeVariableInvMass[i]=0.;
        if(i<6){
            fTreeVariabled0rphi[i]=0.;
        }
        if(i<9){
            fTreeVariablePt[i]=0.;
            fTreeVariableEta[i]=0.;
            fTreeVariablePhi[i]=0.;
            fTreeVariableRap[i]=0.;
            fTreeVariableGenPt[i]=0.;
            fTreeVariableGenEta[i]=0.;
            fTreeVariableGenPhi[i]=0.;
            fTreeVariableGenRap[i]=0.;
            fTreeVariableGenRxy[i]=0.;
        }
        if(i<2){
            fTreeVariableInvMassOmegac[i]=0.;
        }
        if(i<3){
            fTreeVariabled0rphiOmegac[i]=0.;  // omegac, omega, pion
            fTreeVariablePtOmegac[i]=0.;     // omegac, omega, pion
            fTreeVariableEtaOmegac[i]=0.;
            fTreeVariablePhiOmegac[i]=0.;
            fTreeVariableRapOmegac[i]=0.;
            fTreeVariableGenPtOmegac[i]=0.;
            fTreeVariableGenEtaOmegac[i]=0.;
            fTreeVariableGenPhiOmegac[i]=0.;
            fTreeVariableGenRapOmegac[i]=0.;
            fTreeVariableGenRxyOmegac[i]=0.;
        }
    }
    /// Default constructor
    
}
//________________________________________________________________________
AliAnalysisTaskSEOmegacccToOmega3Pi::AliAnalysisTaskSEOmegacccToOmega3Pi(const char *name):
AliAnalysisTaskSE(name),
fMcEvent(0x0),
fMcHandler(0x0),
fStack(0x0),
fEvent(0x0),
fVertexerTracks(0x0),
fBzkG(0.),
fV1(0x0),
fEtaCut(2.),
fEvtCount(0),
fNentries(0x0),
fOutputGen(0x0),
fOutputReco(0x0),
fITS(0x0),
fHistNcollHFtype(0x0),
fHistNinjectedbvsb(0x0),
fHistNinjectedcvsb(0x0),
fHistoNbVsNcPYTHIA(0x0),
fHistoNbVsNcHIJING(0x0),
fIsMCSignalProd(true),
fRecoPt(0.),
fRecoPhi(0.),
fRecoEta(0.),
fRecoY(0.),
fGenPt(0.),
fGenEta(0.),
fGenRad(0.),
fRecoNhits(-1),
fRecoMClabel(-99),
fRecoMClabelMother(-99),
fGenPtMother(0.),
fRecoPdg(-99),
fRecoPdgMother(-99),
fRecoNReconstructableHits(-1),
fTreeRecoTracks(0x0),
fTreeGenOmegaccc(0x0),
fTreeTrueOmegaccc(0x0),
fTreeCutVar(0x0),
fIsSignal(false),
fTreeVariableDecVtxChi2NdfOmegac(0.),
fTreeVariableDecayLengthOmegac(0.),
fTreeVariableDecayLengthXYOmegac(0.),
fIsSignalOmegac(false),
fTreeCutVarOmegac(0x0),
fTreeGenCascV0Reco(0x0),
fTreeGenV0Reco(0x0),
fNHitsAssigned(0),
fParticlePdg(0),
fMotherPdg(0),
fParticleVarPdg(0),
fParticleVarPdgMoth(0),
fParticleVarPt(0),
fParticleVarP(0),
fParticleVarEta(0),
fParticleVarRap(0),
fParticleVarPhi(0),
fParticleVarX(0),
fParticleVarY(0),
fParticleVarZ(0),
fParticleVarRxy(0),
fParticleVarNhitsAssigned(0),
fParticleVarNhitsReco(0),
fParticleVarIsReco(false),
fTreeReconstruction(0x0)
{
    
    for(Int_t i=0; i<11; i++){
        fTreeGenVarOmegacccNRHits[i]=-1;
        fTreeGenVarOmegacccPDG[i]=-1;
        fOmegacVariables[i]=0.;
        fOmegaccVariables[i]=0.;
        fOmegacccVariables[i]=0.;
        for(Int_t j=0; j<5; j++){
            fTreeGenVarOmegaccc[i][j]=0.;
            if(i<5){
                fTreeGenVarCascV0Reco[i][j]=0.;
            }
        }
        if(i<3){
            fTreeVariableDecVtxChi2Ndf[i]=0.;
            fTreeVariableCosPointingAngle[i]=0.;
            fTreeVariableCosPointingAngleXY[i]=0.;
            fTreeVariableDecayLength[i]=0.;
            fTreeVariableDecayLengthXY[i]=0.;
            fTreeVariableInvMass[i]=0.;
            for(Int_t j=0; j<5; j++){
                fTreeGenVarV0Reco[i][j]=0.;
            }
        }
        if(i==3)fTreeVariableInvMass[i]=0.;
        if(i<6){
            fTreeVariabled0rphi[i]=0.;
        }
        if(i<9){
            fTreeVariablePt[i]=0.;
            fTreeVariableEta[i]=0.;
            fTreeVariablePhi[i]=0.;
            fTreeVariableRap[i]=0.;
            fTreeVariableGenPt[i]=0.;
            fTreeVariableGenEta[i]=0.;
            fTreeVariableGenPhi[i]=0.;
            fTreeVariableGenRap[i]=0.;
            fTreeVariableGenRxy[i]=0.;
        }
    }
    
    //cuts
    //Omegac
    fOmegacCuts[0]=0.05;//0.1;     //inv mass window
    fOmegacCuts[1]=-9999.;         //pt min
    fOmegacCuts[2]=-9999.;         //min decL
    fOmegacCuts[3]=-9999.;         //min decLXY
    fOmegacCuts[4]=-9999.;        //min imp par cbaryon
    fOmegacCuts[5]=-9999.;        //min imp par track
    fOmegacCuts[6]=-9999.;        //min pt track
    fOmegacCuts[7]=-9999.;        //cosThetaStar pion
    fOmegacCuts[8]=-9999.;        //min cosThetaPoint
    fOmegacCuts[9]=-9999.;        //min cosThetaPointXY
    fOmegacCuts[10]=5.;          //max chi2/ndf vtx
    
    //Omegac
    fOmegaccCuts[0]=0.1;//0.1;     //inv mass window
    fOmegaccCuts[1]=-9999.;     //pt min
    fOmegaccCuts[2]=-9999.;     //min decL
    fOmegaccCuts[3]=-9999.;     //min decLXY
    fOmegaccCuts[4]=-9999.;        //min imp par cbaryon
    fOmegaccCuts[5]=-9999.;        //min imp par track
    fOmegaccCuts[6]=-9999.;        //min pt track
    fOmegaccCuts[7]=-9999.;        //cosThetaStar pion
    fOmegaccCuts[8]=-9999.;        //min cosThetaPoint
    fOmegaccCuts[9]=-9999.;        //min cosThetaPointXY
    fOmegaccCuts[10]=5.;      //max chi2/ndf vtx
    
    //Omegac
    fOmegacccCuts[0]=0.2;//0.1;         //inv mass window
    fOmegacccCuts[1]=-9999.;         //pt min
    fOmegacccCuts[2]=-9999.;         //min decL
    fOmegacccCuts[3]=-9999.;         //min decLXY
    fOmegacccCuts[4]=-9999.;        //min imp par cbaryon
    fOmegacccCuts[5]=-9999.;        //min imp par track
    fOmegacccCuts[6]=-9999.;        //min pt track
    fOmegacccCuts[7]=-9999.;        //cosThetaStar pion
    fOmegacccCuts[8]=-9999.;        //min cosThetaPoint
    fOmegacccCuts[9]=-9999.;        //min cosThetaPointXY
    fOmegacccCuts[10]=5.;      //max chi2/ndf vtx
    
    
    
    DefineInput(0, TChain::Class());
    // Output slot #1 writes into a TH1F container (number of events)
    DefineOutput(1,TH1F::Class());
    DefineOutput(2,TList::Class());
    DefineOutput(3,TList::Class());
    DefineOutput(4,TTree::Class()); //fTreeGenOmegaccc(0x0),
    DefineOutput(5,TTree::Class());
    DefineOutput(6,TTree::Class()); //fTreeGenOmegaccc(0x0),
    DefineOutput(7,TTree::Class());
    DefineOutput(8,TTree::Class());
    DefineOutput(9,TTree::Class());
    DefineOutput(10,TTree::Class());
}
//________________________________________________________________________
AliAnalysisTaskSEOmegacccToOmega3Pi::~AliAnalysisTaskSEOmegacccToOmega3Pi()
{
    if (fMcEvent){
        delete fMcEvent;
        fMcEvent = 0x0;
    }
    if (fMcHandler){
        delete fMcHandler;
        fMcHandler = 0x0;
    }
    if (fStack){
        delete fStack;
        fStack = 0x0;
    }
    if (fEvent){
        delete fEvent;
        fEvent = 0x0;
    }
    if (fVertexerTracks){
        delete fVertexerTracks;
        fVertexerTracks = 0x0;
    }
    if (fV1){
        delete fV1;
        fV1 = 0x0;
    }
    if (fNentries){
        delete fNentries;
        fNentries = 0x0;
    }
    if (fOutputGen){
        delete fOutputGen;
        fOutputGen = 0x0;
    }
    if (fOutputReco){
        delete fOutputReco;
        fOutputReco = 0x0;
    }
    if (fITS){
        delete fITS;
        fITS = 0x0;
    }
    if (fTreeRecoTracks){
        delete fTreeRecoTracks;
        fTreeRecoTracks = 0x0;
    }
    if (fTreeGenOmegaccc){
        delete fTreeGenOmegaccc;
        fTreeGenOmegaccc = 0x0;
    }
    if (fTreeTrueOmegaccc){
        delete fTreeTrueOmegaccc;
        fTreeTrueOmegaccc = 0x0;
    }
    if (fTreeCutVar){
        delete fTreeCutVar;
        fTreeCutVar = 0x0;
    }
    if (fTreeCutVarOmegac){
        delete fTreeCutVarOmegac;
        fTreeCutVarOmegac = 0x0;
    }
    if (fTreeGenCascV0Reco){
        delete fTreeGenCascV0Reco;
        fTreeGenCascV0Reco = 0x0;
    }
    if (fTreeGenV0Reco){
        delete fTreeGenV0Reco;
        fTreeGenV0Reco = 0x0;
    }
    if (fTreeReconstruction){
        delete fTreeReconstruction;
        fTreeReconstruction = 0x0;
    }
    
}

//________________________________________________________________________
void AliAnalysisTaskSEOmegacccToOmega3Pi::Init()
{
    /// Initialization
    
    if(fDebug > 1) printf("AliAnalysisTaskSEOmegacccToOmega3Pi::Init() \n");
    
}

//________________________________________________________________________
void AliAnalysisTaskSEOmegacccToOmega3Pi::UserCreateOutputObjects()
{
    
    /// Create the output container
    //
    if(fDebug > 1) printf("AliAnalysisTaskSEOmegacccToOmega3Pi::UserCreateOutputObjects() \n");
    
    fEvent = new AliESDEvent();
    fEvent->CreateStdContent();
    
    // create new ITS detector
    fITS = CreateDetector();
    
    fVertexerTracks = new AliVertexerTracks();
    
    const char* nameoutput=GetOutputSlot(1)->GetContainer()->GetName();
    fNentries=new TH1F(nameoutput, "Number of events", 23,-0.5,22.5);
    fNentries->GetXaxis()->SetBinLabel(1,"All gen events");
    fNentries->GetXaxis()->SetBinLabel(2,"All gen particle");
    fNentries->GetXaxis()->SetBinLabel(3,"Physical particle");
    fNentries->GetXaxis()->SetBinLabel(4,"Mother label not -1");
    fNentries->GetXaxis()->SetBinLabel(5,"Excluding charge=0");
    fNentries->GetXaxis()->SetBinLabel(6,"After Kine cuts");
    fNentries->GetXaxis()->SetBinLabel(7,"Reco tracks");
    fNentries->GetXaxis()->SetBinLabel(8,"Not Reco tracks");
    fNentries->GetXaxis()->SetBinLabel(9,"N #pi from #Lambda gen");
    fNentries->GetXaxis()->SetBinLabel(10,"N p from #Lambda gen");
    fNentries->GetXaxis()->SetBinLabel(11,"N #Lambda gen");
    fNentries->GetXaxis()->SetBinLabel(12,"N #Omega gen");
    fNentries->GetXaxis()->SetBinLabel(13,"N #Lambda from #Omega gen");
    fNentries->GetXaxis()->SetBinLabel(14,"N K from #Omega gen");
    fNentries->GetXaxis()->SetBinLabel(15,"N D gen");
    fNentries->GetXaxis()->SetBinLabel(16,"N B gen");
    
    nameoutput=GetOutputSlot(2)->GetContainer()->GetName();
    fOutputGen = new TList();
    fOutputGen->SetName(nameoutput);
    fOutputGen->SetOwner(true);
    
    nameoutput=GetOutputSlot(3)->GetContainer()->GetName();
    fOutputReco = new TList();
    fOutputReco->SetName(nameoutput);
    fOutputReco->SetOwner(true);
    
    fHistNcollHFtype     =new TH2F("hNcollHFtype","",5,-1.5,3.5,110,-0.5,109.5);
    fOutputGen->Add(fHistNcollHFtype);
    fHistNinjectedbvsb   =new TH2F("hNinjectedbvsb","",50,0.,20.,140,-0.5,139.5);
    fOutputGen->Add(fHistNinjectedbvsb);
    fHistNinjectedcvsb   =new TH2F("hNinjectedcvsb","",50,0.,20.,140,-0.5,139.5);
    fOutputGen->Add(fHistNinjectedcvsb);
    
    Int_t nBinscb=200;
    Double_t maxncn=nBinscb-0.5;
    fHistoNbVsNcPYTHIA = new TH2F("fHistoNbVsNcPYTHIA","",nBinscb,-0.5,maxncn,nBinscb,-0.5,maxncn);
    fHistoNbVsNcHIJING = new TH2F("fHistoNbVsNcHIJING","",nBinscb,-0.5,maxncn,nBinscb,-0.5,maxncn);
    fOutputGen->Add(fHistoNbVsNcPYTHIA);
    fOutputGen->Add(fHistoNbVsNcHIJING);
    
    OpenFile(4);
    fTreeRecoTracks = (TTree*)BuildTreeRecoTracks("TreeRecoTracks","TreeRecoTracks");
    OpenFile(5);
    fTreeCutVar = (TTree*)BuildTreeOmegacccCutVar("TreeCutVarOmegaccc","TreeCutVarOmegaccc");
    OpenFile(6);
    fTreeReconstruction  = (TTree*)BuildTreeReconstruction("TreeReconstruction","TreeReconstruction");
    OpenFile(7);
    fTreeCutVarOmegac = BuildTreeOmegacCutVar("TreeCutVarOmegac", "TreeCutVarOmegac");
    if(fIsMCSignalProd){
        OpenFile(8);
        fTreeGenOmegaccc  = (TTree*)BuildTreeOmegacccGen("TreeGenOmegaccc","TreeGenOmegaccc");
        OpenFile(9);
        fTreeTrueOmegaccc = (TTree*)BuildTreeOmegacccGenReco("TreeTrueRecoOmegaccc","TreeTrueRecoOmegaccc");
        OpenFile(10);
        fTreeGenCascV0Reco = (TTree*)BuildTreeCascV0Reco("TreeGenCascV0Reco","TreeGenCascV0Reco");
        OpenFile(11);
        fTreeGenV0Reco = (TTree*)BuildTreeV0Reco("TreeGenV0Reco","TreeGenV0Reco");
    }
    
    
    // Post the data
    PostData(1,fNentries);
    PostData(2,fOutputGen);
    PostData(3,fOutputReco);
    PostData(4,fTreeRecoTracks);
    PostData(5,fTreeCutVar);
    PostData(6,fTreeReconstruction);
    PostData(7,fTreeCutVarOmegac);
    if(fIsMCSignalProd){
        PostData(8,fTreeGenOmegaccc);
        PostData(9,fTreeTrueOmegaccc);
        PostData(10,fTreeGenCascV0Reco);
        PostData(11,fTreeGenV0Reco);
    }
    
    
    return;
}

//________________________________________________________________________
void AliAnalysisTaskSEOmegacccToOmega3Pi::UserExec(Option_t */*option*/)

{
    /// Execute analysis for current event:
    fEvtCount++;
    cout<< "UserExec " << fEvtCount << endl;
    // Process MC truth
    
    
    AliMCEventHandler* eventHandler = dynamic_cast<AliMCEventHandler*> (AliAnalysisManager::GetAnalysisManager()->GetMCtruthEventHandler());
    if (!eventHandler) {
        Printf("ERROR: Could not retrieve MC event handler");
        return;
    }
    fMcEvent = eventHandler->MCEvent();
    if (!fMcEvent) {
        Printf("ERROR: Could not retrieve MC event");
        return;
    }
    fNentries->Fill(0);
    
    // create dummy vertex for beam diamond
    const double kBeamSig = 3e-4;//50e-4;
    double beamPos[3] = {0.,0.,0.};
    double beamSig[3] = {kBeamSig, kBeamSig, kBeamSig };
    AliESDVertex diamond(beamPos,beamSig,"diamond");
    
    // access the stack
    fStack = ((AliMCEvent*)fMcEvent)->Stack();
    if(!fStack) {Printf("ERROR: Could not retrieve the Stack"); return;}
    
    //check generators
    TString genname=fMcEvent->GenEventHeader()->ClassName();
    Int_t nColl=-1;
    Double_t imppar=-999.;
    Int_t nInjectedb=0;
    Int_t nInjectedc=0;
    Int_t typeHF=-1;
    TList* lgen=0x0;
    if(genname.Contains("CocktailEventHeader")){
        AliGenCocktailEventHeader *cockhead=(AliGenCocktailEventHeader*)fMcEvent->GenEventHeader();
        lgen=cockhead->GetHeaders();
        lgen->ls();
        nColl=lgen->GetEntries();
        for(Int_t ig=0; ig<lgen->GetEntries(); ig++){
            AliGenerator* gen=(AliGenerator*)lgen->At(ig);
            TString title=gen->GetName();
            if(title.Contains("ball")){
                typeHF=1;
                nInjectedb++;
            }else if(title.Contains("call")) {
                typeHF=0;
                nInjectedc++;
            }
            else if(title.Contains("bchadr PYTHIA_1")){
                nInjectedc++;
                typeHF=3;
            }
            else if(title.Contains("hijing") || title.Contains("Hijing")){
                AliGenHijingEventHeader* hijh=(AliGenHijingEventHeader*)lgen->At(ig);
                imppar=hijh->ImpactParameter();
                typeHF=2;
            }
            fHistNcollHFtype->Fill(typeHF,nColl);
        }
        fHistNinjectedbvsb->Fill(imppar,nInjectedb);
        fHistNinjectedcvsb->Fill(imppar,nInjectedc);
    }
    
    
    
    // reset ESD event
    fEvent->Reset();
    fEvent->SetMagneticField(fITS->GetBField()*10.);
    fEvent->SetDiamond(&diamond);
    // fill ESD event
    RecoEvent();
    fBzkG = fEvent->GetMagneticField();
    fV1   = (AliESDVertex*)fEvent->GetPrimaryVertexTracks();
    Double_t sigma[3]={0.,0.,0.};
    Double_t position[3]={0.,0.,0.};
    fV1->GetSigmaXYZ(sigma);
    fV1->GetXYZ(position);
    FillGenTree();
    // fill histos with reco tracks
    FillRecoTrackTree();
    
    // V0 finder
    AliAnalysisTaskWeakDecayVertexer_mod *v0Finder= new AliAnalysisTaskWeakDecayVertexer_mod("v0Finder");
    //v0Finder->SetPreselectDedx(kFALSE);
    v0Finder->SetPreselectDedxLambda(kFALSE);
    v0Finder->SetExtraCleanup(kFALSE);
    v0Finder->SetRevertexAllEvents(kFALSE);
    v0Finder->SetUseExtraEvSels(kFALSE);
    v0Finder->SetCentralityInterval(0,101);
    v0Finder->SetRunV0Vertexer(kTRUE);
    v0Finder->SetRunCascadeVertexer(kTRUE);
    v0Finder->SetDoImprovedDCAV0DauPropagation(kTRUE);
    v0Finder->SetDoImprovedDCACascDauPropagation(kTRUE);
    v0Finder->SetDoV0Refit(kTRUE);
    v0Finder->SetDoCascadeRefit(kTRUE);
    v0Finder->SetV0VertexerDCAFirstToPV(0.05);
    v0Finder->SetV0VertexerDCASecondtoPV(0.05);
    v0Finder->SetV0VertexerDCAV0Daughters(1.40);
    v0Finder->SetV0VertexerCosinePA(0.95);
    v0Finder->SetV0VertexerMinRadius(0.9);
    v0Finder->SetV0VertexerMaxRadius(200);
    v0Finder->SetCascVertexerMinV0ImpactParameter(0.05);
    v0Finder->SetCascVertexerV0MassWindow(0.006);
    v0Finder->SetCascVertexerDCABachToPV(0.05);
    v0Finder->SetCascVertexerDCACascadeDaughters(1.4);
    v0Finder->SetCascVertexerCascadeMinRadius(.5);
    v0Finder->SetCascVertexerCascadeCosinePA(.95);
    v0Finder->Tracks2V0vertices(fEvent);
    delete v0Finder;
    // cascade finder
    AliAnalysisTaskWeakDecayVertexer_mod *cascadeFinder= new AliAnalysisTaskWeakDecayVertexer_mod("cascadeFinder");
    cascadeFinder->SetPreselectDedxLambda(kFALSE);
    cascadeFinder->SetExtraCleanup(kFALSE);
    cascadeFinder->SetRevertexAllEvents(kFALSE);
    cascadeFinder->SetUseExtraEvSels(kFALSE);
    cascadeFinder->SetCentralityInterval(0,101);
    cascadeFinder->SetRunV0Vertexer(kTRUE);
    cascadeFinder->SetRunCascadeVertexer(kTRUE);
    cascadeFinder->SetDoImprovedDCAV0DauPropagation(kTRUE);
    cascadeFinder->SetDoImprovedDCACascDauPropagation(kTRUE);
    cascadeFinder->SetDoV0Refit(kTRUE);
    cascadeFinder->SetDoCascadeRefit(kTRUE);
    cascadeFinder->SetV0VertexerDCAFirstToPV(0.05);
    cascadeFinder->SetV0VertexerDCASecondtoPV(0.05);
    cascadeFinder->SetV0VertexerDCAV0Daughters(1.40);
    cascadeFinder->SetV0VertexerCosinePA(0.95);
    cascadeFinder->SetV0VertexerMinRadius(0.9);
    cascadeFinder->SetV0VertexerMaxRadius(200);
    cascadeFinder->SetCascVertexerMinV0ImpactParameter(0.05);
    cascadeFinder->SetCascVertexerV0MassWindow(0.006);
    cascadeFinder->SetCascVertexerDCABachToPV(0.05);
    cascadeFinder->SetCascVertexerDCACascadeDaughters(1.4);
    cascadeFinder->SetCascVertexerCascadeMinRadius(.5);
    cascadeFinder->SetCascVertexerCascadeCosinePA(.95);
    cascadeFinder->V0sTracks2CascadeVertices(fEvent);
    delete cascadeFinder;
    
    if(fIsMCSignalProd){
        FillGenTreeRecoV0();
        FillGenTreeRecoCascV0();
    }
    
    
    //FillV0Histos();
    //FillCascadeHistos();
    
    MakeOmegac();
    
    // Post output data.
    //PostData(1, fOutputList);
    
    
    
    return;
}
//________________________________________________________________________
void AliAnalysisTaskSEOmegacccToOmega3Pi::Terminate(Option_t */*option*/)
{
    /// Terminate analysis
    //
    if(fDebug > 1) printf("AliAnalysisTaskSEOmegacccToOmega3Pi: Terminate() \n");
    
    
    fNentries = dynamic_cast<TH1F*>(GetOutputData(1));
    if(!fNentries){
        printf("ERROR: fNEntries not available\n");
        return;
    }
    fOutputGen = dynamic_cast<TList*>(GetOutputData(2));
    if(!fOutputGen){
        printf("ERROR: fOutput not available\n");
        return;
    }
    fOutputReco = dynamic_cast<TList*>(GetOutputData(3));
    if(!fOutputReco){
        printf("ERROR: fOutput not available\n");
        return;
    }
    
    return;
    
}
//________________________________________________________________________
Long_t AliAnalysisTaskSEOmegacccToOmega3Pi::MakeOmegac(){
    
    
    //Printf("\n\n\n ********************************* MakeOmegaC");
    Double_t xPrimaryVertex=fV1->GetX();
    Double_t yPrimaryVertex=fV1->GetY();
    Double_t zPrimaryVertex=fV1->GetZ();
    
    Int_t nSecVtx=0;
    // get number of cascades
    Long_t nCascades = fEvent->GetNumberOfCascades();
    if(nCascades==0) return 0;
    
    AliESDcascade *casc=0x0;
    AliESDtrack *pTrackCasc=0x0;
    AliESDtrack *nTrackCasc=0x0;
    AliESDtrack *bachTrackCasc=0x0;
    AliESDtrack *esdtr=0x0;
    AliESDtrack *esdtr2=0x0;
    AliESDtrack *esdtr3=0x0;
    AliESDVertex *sVtxOmegac=0x0;
    AliESDVertex *sVtxOmegacc=0x0;
    AliESDVertex *sVtxOmegaccc=0x0;
    
    Int_t cascCharge = 0;
    Float_t cascInvMass =0.;
    
    
    // loop on cascades
    for(Int_t icasc=0; icasc<nCascades; icasc++){
        casc = (AliESDcascade*)fEvent->GetCascade(icasc);
        if(!casc) continue;
        
        UInt_t lIdxPosCasc     = (UInt_t) TMath::Abs( casc->GetPindex() );
        UInt_t lIdxNegCasc     = (UInt_t) TMath::Abs( casc->GetNindex() );
        UInt_t lBachIdx        = (UInt_t) TMath::Abs( casc->GetBindex() );
        if(!lIdxPosCasc || !lIdxNegCasc || !lBachIdx) continue;
        if(lBachIdx == lIdxNegCasc) {
            //Printf("Pb / Idx(Bach. track) = Idx(Neg. track) ... continue!");
            continue;
        }
        if(lBachIdx == lIdxPosCasc) {
            //Printf("Pb / Idx(Bach. track) = Idx(Pos. track) ... continue!");
            continue;
        }
        pTrackCasc        = (AliESDtrack*)fEvent->GetTrack( lIdxPosCasc );
        nTrackCasc        = (AliESDtrack*)fEvent->GetTrack( lIdxNegCasc );
        bachTrackCasc     = (AliESDtrack*)fEvent->GetTrack( lBachIdx );
        if (!pTrackCasc || !nTrackCasc || !bachTrackCasc ) {
            Printf("ERROR: Could not retrieve one of the 3 ESD daughter tracks of the cascade ...");
            continue;
        }
        cascCharge = bachTrackCasc->Charge();
        //cut on cascade invariant mass
        Double_t lV0quality = 0.;
        if(cascCharge<0){
            casc->ChangeMassHypothesis(lV0quality , 3334);
            cascInvMass = casc->GetEffMassXi();
        }
        else {
            casc->ChangeMassHypothesis(lV0quality , -3334);
            cascInvMass = casc->GetEffMassXi();
        }
        if(TMath::Abs(cascInvMass-TDatabasePDG::Instance()->GetParticle(3334)->Mass())>0.022) continue;
        fTreeVariableInvMass[3]=cascInvMass;
        
        // loop on tracks
        // get number of tracks
        Long_t nentr = (Int_t)fEvent->GetNumberOfTracks();
        for(Int_t i=0; i<nentr; i++){
            //Printf("MakeOmegaC::::  --->track %d",i);
            esdtr = (AliESDtrack*)fEvent->GetTrack(i);
            
            UInt_t lIdxTrack = esdtr->GetID();
            if(!lIdxTrack) continue;
            //Printf("First LOOP %d",i);
            if(lIdxTrack == lIdxNegCasc){
                //Printf("First Loop Pb / Idx(track)=%d = Idx(Neg. track)=%d ... continue!",lIdxTrack,lIdxNegCasc);
                continue;
            }
            if(lIdxTrack == lIdxPosCasc){
                //Printf("First Loop Pb / Idx(track)=%d = Idx(Pos. track)=%d ... continue!",lIdxTrack,lIdxPosCasc);
                continue;
            }
            if(lIdxTrack == lBachIdx){
                //Printf("First Loop Pb / Idx(track)=%d = Idx(Bach. track)=%d ... continue!",lIdxTrack,lBachIdx);
                continue;
            }
            
            //single track cuts
            Int_t esdtrCharge = esdtr->Charge();
            if(esdtrCharge == cascCharge) continue;
            ULong_t status = esdtr->GetStatus();
            if ((status&AliESDtrack::kITSrefit)==0)
                if ((status&AliESDtrack::kTPCrefit)==0) continue;
            //if(esdtr->Pt()<0.5) continue;
            
            //bachCascCTrackLabOrigin = CheckOriginTrack(esdtr);
            //if (TMath::Abs(esdtr->GetD(xPrimaryVertex,yPrimaryVertex,fBzkG))<fOmegacVertexerSels[0]) continue;
            Double_t dispersion=0.;
            //Printf("\n********************************* CallReconstructSecondaryVertexOmegac");
            //Printf("MakeOmegaC --> Before CallReconstructSecondaryVertexOmegac");
            sVtxOmegac = CallReconstructSecondaryVertexOmegac(casc, esdtr, dispersion);
            //Printf("MakeOmegaC --> After CallReconstructSecondaryVertexOmegac");
            if(!sVtxOmegac) { //delete sVtxOmegac; sVtxOmegac=NULL;//Printf("--> no omega c vertex reco");
                //Printf("--> no omega c vertex reco");
                continue;}
            nSecVtx++;
            //Printf("--->FillHistoOmegac");
            //cuts
            //Printf("MakeOmegaC --> Before FillHistoOmegac");
            bool isselOmegac = FillHistoOmegac(casc, esdtr, sVtxOmegac);
            //Printf("MakeOmegaC --> After FillHistoOmegac");
            //if(TMath::Abs(fOmegacVariables[0]-TDatabasePDG::Instance()->GetParticle(4332)->Mass())>0.1) {//Printf("continue, mass cut");
            //continue;}
            //gObjectTable->Print();
            if(!isselOmegac) { //delete sVtxOmegac; sVtxOmegac=NULL;
                continue;  }
            //return nSecVtx;
            
            //second loop on tracks to build omegacc
            for(Int_t ii=0; ii<nentr; ii++){
                esdtr2 = (AliESDtrack*)fEvent->GetTrack(ii);
                UInt_t lIdxTrack2 = esdtr2->GetID();
                if(!lIdxTrack2) continue;
                //Printf("Second LOOP %d",ii);
                if(lIdxTrack2 == lIdxNegCasc){
                    //Printf("Second Loop Pb / Idx(track2)=%d = Idx(Neg. track)=%d ... continue!",lIdxTrack2,lIdxNegCasc);
                    continue;
                }
                if(lIdxTrack2 == lIdxPosCasc){
                    //Printf("Second Loop Pb / Idx(track2)=%d = Idx(Pos. track)=%d ... continue!",lIdxTrack2,lIdxPosCasc);
                    continue;
                }
                if(lIdxTrack2 == lBachIdx){
                    //Printf("Second Loop Pb / Idx(track2)=%d = Idx(Bach. track)=%d ... continue!",lIdxTrack2,lBachIdx);
                    continue;
                }
                if(lIdxTrack2 == lIdxTrack){
                    //Printf("Second Loop Pb / Idx(track2)=%d = Idx(track)=%d ... continue!",lIdxTrack2,lIdxTrack);
                    continue;
                }
                //single track cuts
                Int_t esdtr2Charge = esdtr2->Charge();
                if(esdtr2Charge != esdtrCharge) continue;
                ULong_t status = esdtr2->GetStatus();
                if ((status&AliESDtrack::kITSrefit)==0)
                    if ((status&AliESDtrack::kTPCrefit)==0) continue;
                if(esdtr2->Pt()<0.5) continue;
                
                Double_t dispersion=0.;
                //Printf("\n********************************* CallReconstructSecondaryVertexOmegacc");
                //Printf("MakeOmegaC --> Before CallReconstructSecondaryVertexOmegacc");
                sVtxOmegacc = CallReconstructSecondaryVertexOmegacc(sVtxOmegac, casc, esdtr, esdtr2, dispersion);
                //Printf("MakeOmegaC --> After CallReconstructSecondaryVertexOmegacc");
                if(!sVtxOmegacc) {//Printf("--> no omega cc vertex reco");
                    //delete sVtxOmegacc; sVtxOmegacc=NULL;
                    //delete sVtxOmegac;  sVtxOmegac=NULL;
                    continue;}
                // cuts
                bool isselOmegacc = FillHistoOmegacc(casc, esdtr, esdtr2, sVtxOmegac, sVtxOmegacc);
                //if(TMath::Abs(fOmegaccVariables[0]-TDatabasePDG::Instance()->GetParticle(4432)->Mass())>0.1) {//Printf("Omega c mass cut %f ",fOmegaccVariables[0]);
                //continue;}
                if(!isselOmegacc){
                    //delete sVtxOmegacc; sVtxOmegacc=NULL;
                    //delete sVtxOmegac;  sVtxOmegac=NULL;
                    continue;
                }
                
                
                //third loop on tracks to build omegaccc
                for(Int_t iii=0; iii<nentr; iii++){
                    esdtr3 = (AliESDtrack*)fEvent->GetTrack(iii);
                    UInt_t lIdxTrack3 = esdtr3->GetID();
                    if(!lIdxTrack3) continue;
                    //Printf("Third LOOP %d",iii);
                    if(lIdxTrack3 == lIdxNegCasc){
                        //Printf("Third Loop Pb / Idx(track3)=%d = Idx(Neg. track)=%d ... continue!",lIdxTrack3,lIdxNegCasc);
                        continue;
                    }
                    if(lIdxTrack3 == lIdxPosCasc){
                        //Printf("Third Loop Pb / Idx(track3)=%d = Idx(Pos. track)=%d ... continue!",lIdxTrack3,lIdxPosCasc);
                        continue;
                    }
                    if(lIdxTrack3 == lBachIdx){
                        //Printf("Third Loop Pb / Idx(track3)=%d = Idx(Bach. track)=%d ... continue!",lIdxTrack3,lBachIdx);
                        continue;
                    }
                    if(lIdxTrack3 == lIdxTrack){
                        //Printf("Third Loop Pb / Idx(track3)=%d = Idx(track)=%d ... continue!",lIdxTrack3,lIdxTrack);
                        continue;
                    }
                    if(lIdxTrack3 == lIdxTrack2){
                        //Printf("Third Loop Pb / Idx(track3)=%d = Idx(track2)=%d ... continue!",lIdxTrack3,lIdxTrack2);
                        continue;
                    }
                    //single track cuts
                    Int_t esdtr3Charge = esdtr3->Charge();
                    if(esdtr3Charge != esdtr2Charge) continue;
                    ULong_t status = esdtr3->GetStatus();
                    if ((status&AliESDtrack::kITSrefit)==0)
                        if ((status&AliESDtrack::kTPCrefit)==0) continue;
                    if(esdtr3->Pt()<0.5) continue;
                    
                    Double_t dispersion=0.;
                    //Printf("\n********************************* CallReconstructSecondaryVertexOmegaccc");
                    //gObjectTable->Print();
                    sVtxOmegaccc = CallReconstructSecondaryVertexOmegaccc(sVtxOmegacc,sVtxOmegac,casc,esdtr,esdtr2,esdtr3,dispersion);
                    if(!sVtxOmegaccc) {
                        //delete sVtxOmegaccc;  sVtxOmegaccc=NULL;
                        //delete sVtxOmegacc;   sVtxOmegacc=NULL;
                        //delete sVtxOmegac;    sVtxOmegac=NULL;
                        continue;}
                    bool isselOmegaccc = FillHistoOmegaccc(casc, esdtr, esdtr2, esdtr3, sVtxOmegac, sVtxOmegacc, sVtxOmegaccc);
                    if(!isselOmegaccc)  {
                        //delete sVtxOmegaccc; sVtxOmegaccc=NULL;
                        //delete sVtxOmegacc;  sVtxOmegacc=NULL;
                        //delete sVtxOmegac;   sVtxOmegac=NULL;
                    }
                    //Printf("\n********************************* END CallReconstructSecondaryVertexOmegaccc");
                    //gObjectTable->Print();
                    //cuts
                    //if(TMath::Abs(fOmegacccVariables[0]-TDatabasePDG::Instance()->GetParticle(4444)->Mass())>0.5) continue;
                    //if(TMath::Abs(fOmegacccVariables[0]-TDatabasePDG::Instance()->GetParticle(4444)->Mass())>0.5) continue;
                    
                    //fill histos
                    //FillHisto(fEvent, casc, esdtr, esdtr2, esdtr3, sVtxOmegac, sVtxOmegacc, sVtxOmegaccc);
                    delete sVtxOmegaccc;  sVtxOmegaccc=NULL;
                }// end third loop on tracks
                delete sVtxOmegacc;   sVtxOmegacc=NULL;
            }//end second loop on tracks
            delete sVtxOmegac;    sVtxOmegac=NULL;
        }//end first loop on tracks
        
    }
    
    return nSecVtx;
    
    
}
//_________________________________________
void AliAnalysisTaskSEOmegacccToOmega3Pi::PrintDecayChainTrack(AliESDtrack *track){
    
    // MC label
    Int_t label       = track->GetLabel();
    // MC particle
    TParticle *part   = fMcEvent->Particle(label);
    //Printf("TRACK DECAY CHAIN: track:    label=%10d, pdg=%10d, name=%s, energy=%f, px=%f, py=%f, pz=%f",label,part->GetPdgCode(),part->GetName(),part->Energy(),part->Px(),part->Py(),part->Pz());
    Int_t mother = part->GetFirstMother();
    Int_t istep = 0;
    while (mother>-1){
        istep++;
        TParticle *motherPart = fMcEvent->Particle(mother);
        if(motherPart){
            //Printf("------------------ %d mother: label=%10d, pdg=%10d, name=%s, energy=%f, px=%f, py=%f, pz=%f",istep,mother,motherPart->GetPdgCode(),motherPart->GetName(),motherPart->Energy(),motherPart->Px(),motherPart->Py(),motherPart->Pz());
            mother = motherPart->GetFirstMother();
        }
        else{
            //printf("CheckOrigin: Failed casting the mother particle!");
            break;
        }
    }
    
    
}
//_________________________________________
Int_t AliAnalysisTaskSEOmegacccToOmega3Pi::CheckOriginTrack(AliESDtrack *track, Int_t pdg){
    
    
    //method to get the label of a mother with pdg, if any
    
    // MC label
    Int_t label       = track->GetLabel();
    //MC particle
    TParticle *part   = fMcEvent->Particle(label);
    
    Int_t pdgma = 0;
    Int_t motherlbl = 0;
    // get first mother MC label
    motherlbl = part->GetFirstMother();
    Int_t retvalue = -1;
    Int_t istep = 0;
    Bool_t isFound = false;
    while (motherlbl >-1){ //while the mother label is >-1 --> check the mother
        istep++;
        TParticle* motherPart = fMcEvent->Particle(motherlbl);
        if(motherPart){
            pdgma = motherPart->GetPdgCode();
            if(TMath::Abs(pdgma)==pdg) {isFound=true; retvalue=motherlbl;}
            //Printf("CheckOriginTrack(%d=%s, %d)::: ---->>>> istep=%d, motherlbl=%d, pdgma=%d, namema=%s, isfound=%d, retvalue=%d",label,part->GetName(),pdg,istep,motherlbl,pdgma,motherPart->GetName(),isFound,retvalue);
            motherlbl = motherPart->GetFirstMother();
        }else{
            printf("CheckOrigin: Failed casting the mother particle!");
            break;
        }
    }
    //Printf("final retvalue=%d",retvalue);
    return retvalue;
    
    
}
//_________________________________________
Bool_t AliAnalysisTaskSEOmegacccToOmega3Pi::CheckIsSignalOmegac(AliESDtrack *pTrackCasc, AliESDtrack *nTrackCasc, AliESDtrack *bachTrackCasc, AliESDtrack *track){
    
    Bool_t retval = false;
    
    Int_t lblpTrackCasc      = pTrackCasc->GetLabel();
    Int_t lblnTrackCasc      = nTrackCasc->GetLabel();
    Int_t lblbachTrackCasc   = bachTrackCasc->GetLabel();
    Int_t lblbachTrackCascC  = track->GetLabel();
    
    TParticle *partPosTrackCasc   = fMcEvent->Particle(lblpTrackCasc);
    TParticle *partNegTrackCasc   = fMcEvent->Particle(lblnTrackCasc);
    TParticle *partbachTrackCasc  = fMcEvent->Particle(lblbachTrackCasc);
    TParticle *partbachTrackCascC = fMcEvent->Particle(lblbachTrackCascC);
    
    // - Level of the cascade daughters
    Int_t lblMotherPosV0Dghter = 0;  lblMotherPosV0Dghter = partPosTrackCasc->GetFirstMother();
    Int_t lblMotherNegV0Dghter = 0;  lblMotherNegV0Dghter = partNegTrackCasc->GetFirstMother();
    if(lblMotherPosV0Dghter == lblMotherNegV0Dghter && lblMotherPosV0Dghter > 0 && lblMotherNegV0Dghter > 0){
        // mothers = Lambda candidate ... a priori
        TParticle *mcMotherPosV0Dghter = 0x0; mcMotherPosV0Dghter = fMcEvent->Particle( lblMotherPosV0Dghter );
        TParticle *mcMotherNegV0Dghter = 0x0; mcMotherNegV0Dghter = fMcEvent->Particle( lblMotherNegV0Dghter );
        // - Level of cascade candidate
        Int_t lblGdMotherPosV0Dghter = 0; lblGdMotherPosV0Dghter = mcMotherPosV0Dghter->GetFirstMother() ;
        Int_t lblGdMotherNegV0Dghter = 0; lblGdMotherNegV0Dghter = mcMotherNegV0Dghter->GetFirstMother() ;
        if(lblGdMotherPosV0Dghter == lblGdMotherNegV0Dghter && lblGdMotherPosV0Dghter>0 && lblGdMotherNegV0Dghter>0){
            // Gd mothers = cascade candidate ... a priori
            TParticle *mcGdMotherPosV0Dghter = 0x0; mcGdMotherPosV0Dghter = fMcEvent->Particle( lblGdMotherPosV0Dghter ); //omega
            TParticle *mcGdMotherNegV0Dghter = 0x0; mcGdMotherNegV0Dghter = fMcEvent->Particle( lblGdMotherNegV0Dghter ); //omega
            Int_t lblMotherBach = 0; lblMotherBach = partbachTrackCasc->GetFirstMother();   //label omega
            if(lblMotherBach == lblGdMotherPosV0Dghter && lblMotherBach > 0 &&  lblGdMotherPosV0Dghter > 0){
                // label of the mother of the bachelor == label of the grandmother of the pos/neg V0 daughters
                TParticle *mcMotherBach = 0x0; mcMotherBach = fMcEvent->Particle( lblMotherBach );  //bachelor mother omega part
                Int_t lblGdMotherBach = 0; lblGdMotherBach = mcMotherBach->GetFirstMother();         //label of the grandmother of the bachelor -> omegac label
                Int_t lblMotherBachC = 0;  lblMotherBachC = partbachTrackCascC->GetFirstMother();     //label of the mother of the bachelorC -> omegac label
                if(lblGdMotherBach == lblMotherBachC && lblGdMotherBach>-1 && lblMotherBachC>-1) {
                    //Omegac level
                    //label of the grandmother of the bachelor == label of the mother of the bachelorC
                    TParticle *mcGdMotherBach = 0x0; mcGdMotherBach = fMCEvent->Particle( lblGdMotherBach ); //bachelor grandmother part -> omegac part
                    TParticle *mcMotherBachC = 0x0;  mcMotherBachC = fMCEvent->Particle( lblMotherBachC );   //bachelorC mother part     -> omegac part
                    Int_t pdgGdMotherBach=0; pdgGdMotherBach = TMath::Abs(mcGdMotherBach->GetPdgCode());     //bachelor grandmother pdg -> omegac pdg
                    Int_t pdgMotherBachC=0;  pdgMotherBachC = TMath::Abs(mcMotherBachC->GetPdgCode());       //bachelorC mother pdg     -> omegac pdg
                    if(pdgGdMotherBach==4332 && pdgMotherBachC==4332){ // check if is omegac
                        retval =true;
                    }
                }
            }
        }
    }
    
    return retval;
    
}
//_________________________________________
Bool_t AliAnalysisTaskSEOmegacccToOmega3Pi::CheckIsSignalOmegacc(AliESDtrack *pTrackCasc, AliESDtrack *nTrackCasc, AliESDtrack *bachTrackCasc, AliESDtrack *track, AliESDtrack *track2){
    
    Bool_t retval = false;
    
    Int_t lblpTrackCasc       = pTrackCasc->GetLabel();
    Int_t lblnTrackCasc       = nTrackCasc->GetLabel();
    Int_t lblbachTrackCasc    = bachTrackCasc->GetLabel();
    Int_t lblbachTrackCascC   = track->GetLabel();
    Int_t lblbachTrackCascCC  = track2->GetLabel();
    
    TParticle *partPosTrackCasc    = fMcEvent->Particle(lblpTrackCasc);
    TParticle *partNegTrackCasc    = fMcEvent->Particle(lblnTrackCasc);
    TParticle *partbachTrackCasc   = fMcEvent->Particle(lblbachTrackCasc);
    TParticle *partbachTrackCascC  = fMcEvent->Particle(lblbachTrackCascC);
    TParticle *partbachTrackCascCC = fMcEvent->Particle(lblbachTrackCascCC);
    
    
    // - Level of the cascade daughters
    Int_t lblMotherPosV0Dghter = 0;  lblMotherPosV0Dghter = partPosTrackCasc->GetFirstMother();
    Int_t lblMotherNegV0Dghter = 0;  lblMotherNegV0Dghter = partNegTrackCasc->GetFirstMother();
    if(lblMotherPosV0Dghter == lblMotherNegV0Dghter && lblMotherPosV0Dghter > 0 && lblMotherNegV0Dghter > 0){
        // mothers = Lambda candidate ... a priori
        TParticle *mcMotherPosV0Dghter = 0x0; mcMotherPosV0Dghter = fMcEvent->Particle( lblMotherPosV0Dghter );
        TParticle *mcMotherNegV0Dghter = 0x0; mcMotherNegV0Dghter = fMcEvent->Particle( lblMotherNegV0Dghter );
        // - Level of cascade candidate
        Int_t lblGdMotherPosV0Dghter = 0; lblGdMotherPosV0Dghter = mcMotherPosV0Dghter->GetFirstMother() ;
        Int_t lblGdMotherNegV0Dghter = 0; lblGdMotherNegV0Dghter = mcMotherNegV0Dghter->GetFirstMother() ;
        if(lblGdMotherPosV0Dghter == lblGdMotherNegV0Dghter && lblGdMotherPosV0Dghter>0 && lblGdMotherNegV0Dghter>0){
            // Gd mothers = cascade candidate ... a priori
            TParticle *mcGdMotherPosV0Dghter = 0x0; mcGdMotherPosV0Dghter = fMcEvent->Particle( lblGdMotherPosV0Dghter ); //omega
            TParticle *mcGdMotherNegV0Dghter = 0x0; mcGdMotherNegV0Dghter = fMcEvent->Particle( lblGdMotherNegV0Dghter ); //omega
            Int_t lblMotherBach = 0; lblMotherBach = partbachTrackCasc->GetFirstMother();   //label omega
            if(lblMotherBach == lblGdMotherPosV0Dghter && lblMotherBach > 0 &&  lblGdMotherPosV0Dghter > 0){
                // label of the mother of the bachelor == label of the grandmother of the pos/neg V0 daughters
                TParticle *mcMotherBach = 0x0; mcMotherBach = fMcEvent->Particle( lblMotherBach );  //bachelor mother omega part
                Int_t lblGdMotherBach = 0; lblGdMotherBach = mcMotherBach->GetFirstMother();         //label of the grandmother of the bachelor -> omegac label
                Int_t lblMotherBachC = 0;  lblMotherBachC = partbachTrackCascC->GetFirstMother();     //label of the mother of the bachelorC -> omegac label
                if(lblGdMotherBach == lblMotherBachC && lblGdMotherBach>-1 && lblMotherBachC>-1) {
                    //Omegac level
                    //label of the grandmother of the bachelor == label of the mother of the bachelorC
                    TParticle *mcGdMotherBach = 0x0; mcGdMotherBach = fMCEvent->Particle( lblGdMotherBach ); //bachelor grandmother part -> omegac part
                    TParticle *mcMotherBachC = 0x0;  mcMotherBachC = fMCEvent->Particle( lblMotherBachC );   //bachelorC mother part     -> omegac part
                    Int_t lblMotherBachCC = 0;  lblMotherBachCC  = partbachTrackCascCC->GetFirstMother();    //label of the bachelorCC mother    -> omegacc label
                    Int_t lblGdMotherBachC = 0; lblGdMotherBachC = mcMotherBachC->GetFirstMother();          //label of the bachelorC grandmother-> omegacc label
                    if(lblMotherBachCC==lblGdMotherBachC && lblMotherBachCC>-1){
                        //Omega cc level
                        //label of the bachelorC grandmother == label of the mother of the bachelorCC
                        TParticle *mcGdMotherBachC = 0x0; mcGdMotherBachC = fMCEvent->Particle( lblGdMotherBachC );  //bachelorC grandmother part -> omegacc part
                        TParticle *mcMotherBachCC  = 0x0; mcMotherBachCC  = fMCEvent->Particle( lblMotherBachCC );   //bachelorCC mother part -> omegacc part
                        Int_t pdgGdMotherBachC=0; pdgGdMotherBachC = TMath::Abs(mcGdMotherBachC->GetPdgCode());      //omegacc pdg
                        Int_t pdgMotherBachCC=0;  pdgMotherBachCC  = TMath::Abs(mcMotherBachCC->GetPdgCode());       //omegacc pdg
                        if(pdgGdMotherBachC==4432 && pdgMotherBachCC==4432){
                            retval =true;
                        }
                    }
                }
            }
        }
    }
    
    return retval;
    
}
//_________________________________________
Bool_t AliAnalysisTaskSEOmegacccToOmega3Pi::CheckIsSignalOmegaccc(AliESDtrack *pTrackCasc, AliESDtrack *nTrackCasc, AliESDtrack *bachTrackCasc, AliESDtrack *track, AliESDtrack *track2, AliESDtrack *track3){
    
    Bool_t retval = false;
    
    Int_t lblpTrackCasc        = pTrackCasc->GetLabel();
    Int_t lblnTrackCasc        = nTrackCasc->GetLabel();
    Int_t lblbachTrackCasc     = bachTrackCasc->GetLabel();
    Int_t lblbachTrackCascC    = track->GetLabel();
    Int_t lblbachTrackCascCC   = track2->GetLabel();
    Int_t lblbachTrackCascCCC  = track3->GetLabel();
    
    TParticle *partPosTrackCasc     = fMcEvent->Particle(lblpTrackCasc);
    TParticle *partNegTrackCasc     = fMcEvent->Particle(lblnTrackCasc);
    TParticle *partbachTrackCasc    = fMcEvent->Particle(lblbachTrackCasc);
    TParticle *partbachTrackCascC   = fMcEvent->Particle(lblbachTrackCascC);
    TParticle *partbachTrackCascCC  = fMcEvent->Particle(lblbachTrackCascCC);
    TParticle *partbachTrackCascCCC = fMcEvent->Particle(lblbachTrackCascCCC);
    
    // - Level of the cascade daughters
    Int_t lblMotherPosV0Dghter = 0;  lblMotherPosV0Dghter = partPosTrackCasc->GetFirstMother();
    Int_t lblMotherNegV0Dghter = 0;  lblMotherNegV0Dghter = partNegTrackCasc->GetFirstMother();
    if(lblMotherPosV0Dghter == lblMotherNegV0Dghter && lblMotherPosV0Dghter > 0 && lblMotherNegV0Dghter > 0){
        // mothers = Lambda candidate ... a priori
        TParticle *mcMotherPosV0Dghter = 0x0; mcMotherPosV0Dghter = fMcEvent->Particle( lblMotherPosV0Dghter );
        TParticle *mcMotherNegV0Dghter = 0x0; mcMotherNegV0Dghter = fMcEvent->Particle( lblMotherNegV0Dghter );
        // - Level of cascade candidate
        Int_t lblGdMotherPosV0Dghter = 0; lblGdMotherPosV0Dghter = mcMotherPosV0Dghter->GetFirstMother() ;
        Int_t lblGdMotherNegV0Dghter = 0; lblGdMotherNegV0Dghter = mcMotherNegV0Dghter->GetFirstMother() ;
        if(lblGdMotherPosV0Dghter == lblGdMotherNegV0Dghter && lblGdMotherPosV0Dghter>0 && lblGdMotherNegV0Dghter>0){
            // Gd mothers = cascade candidate ... a priori
            TParticle *mcGdMotherPosV0Dghter = 0x0; mcGdMotherPosV0Dghter = fMcEvent->Particle( lblGdMotherPosV0Dghter ); //omega
            TParticle *mcGdMotherNegV0Dghter = 0x0; mcGdMotherNegV0Dghter = fMcEvent->Particle( lblGdMotherNegV0Dghter ); //omega
            Int_t lblMotherBach = 0; lblMotherBach = partbachTrackCasc->GetFirstMother();   //label omega
            if(lblMotherBach == lblGdMotherPosV0Dghter && lblMotherBach > 0 &&  lblGdMotherPosV0Dghter > 0){
                // label of the mother of the bachelor == label of the grandmother of the pos/neg V0 daughters
                TParticle *mcMotherBach = 0x0; mcMotherBach = fMcEvent->Particle( lblMotherBach );  //bachelor mother omega part
                Int_t lblGdMotherBach = 0; lblGdMotherBach = mcMotherBach->GetFirstMother();         //label of the grandmother of the bachelor -> omegac label
                Int_t lblMotherBachC = 0;  lblMotherBachC = partbachTrackCascC->GetFirstMother();     //label of the mother of the bachelorC -> omegac label
                //Printf("lblGdMotherBach=%d lblMotherBachC=%d",lblGdMotherBach,lblMotherBachC);
                if(lblGdMotherBach == lblMotherBachC && lblGdMotherBach>-1 && lblMotherBachC>-1) {
                    //Printf("lblGdMotherBach=%d lblMotherBachC=%d",lblGdMotherBach,lblMotherBachC);
                    //Omegac level
                    //label of the grandmother of the bachelor == label of the mother of the bachelorC
                    TParticle *mcGdMotherBach = 0x0; mcGdMotherBach = fMCEvent->Particle( lblGdMotherBach ); //bachelor grandmother part -> omegac part
                    TParticle *mcMotherBachC = 0x0;  mcMotherBachC = fMCEvent->Particle( lblMotherBachC );   //bachelorC mother part     -> omegac part
                    Int_t lblMotherBachCC = 0;  lblMotherBachCC  = partbachTrackCascCC->GetFirstMother();    //label of the bachelorCC mother    -> omegacc label
                    Int_t lblGdMotherBachC = 0; lblGdMotherBachC = mcMotherBachC->GetFirstMother();
                    //Printf("lblGdMotherBachC=%d lblMotherBachCC=%d",lblGdMotherBachC,lblMotherBachCC);         //label of the bachelorC grandmother-> omegacc label
                    if(lblMotherBachCC==lblGdMotherBachC && lblMotherBachCC>-1){
                        //Printf("lblGdMotherBachC=%d lblMotherBachCC=%d",lblGdMotherBachC,lblMotherBachCC);
                        //Omega cc level
                        //label of the bachelorC grandmother == label of the mother of the bachelorCC
                        TParticle *mcGdMotherBachC = 0x0; mcGdMotherBachC = fMCEvent->Particle( lblGdMotherBachC );  //bachelorC grandmother part -> omegacc part
                        TParticle *mcMotherBachCC  = 0x0; mcMotherBachCC  = fMCEvent->Particle( lblMotherBachCC );   //bachelorCC mother part -> omegacc part
                        Int_t lblGdMotherBachCC = 0; lblGdMotherBachCC = mcMotherBachCC->GetFirstMother();
                        Int_t lblMotherBachCCC  = 0; lblMotherBachCCC  = partbachTrackCascCCC->GetFirstMother();
                        //Printf("lblGdMotherBachCC=%d lblMotherBachCCC=%d",lblGdMotherBachCC,lblMotherBachCCC);
                        if(lblMotherBachCCC == lblGdMotherBachCC && lblMotherBachCCC>-1){
                            //Printf("lblGdMotherBachCC=%d lblMotherBachCCC=%d",lblGdMotherBachCC,lblMotherBachCCC);
                            TParticle *mcGdMotherBachCC = 0x0; mcGdMotherBachCC = fMCEvent->Particle( lblGdMotherBachCC );
                            TParticle *mcMotherBachCCC  = 0x0; mcMotherBachCCC  = fMCEvent->Particle( lblMotherBachCCC );
                            Int_t pdgGdMotherBachCC=0; pdgGdMotherBachCC = TMath::Abs(mcGdMotherBachCC->GetPdgCode());      //omegaccc pdg
                            Int_t pdgMotherBachCCC=0;  pdgMotherBachCCC  = TMath::Abs(mcMotherBachCCC->GetPdgCode());       //omegaccc pdg
                            //Printf("pdgGdMotherBachCC=%d pdgMotherBachCCC=%d",pdgGdMotherBachCC,pdgMotherBachCCC);
                            if(pdgGdMotherBachCC==4444 && pdgMotherBachCCC==4444){
                                retval =true;
                            }
                        }
                    }
                }
            }
        }
    }
    
    return retval;
    
}
//_________________________________________
Bool_t AliAnalysisTaskSEOmegacccToOmega3Pi::IsTrackFromCharmBaryon(AliESDtrack *track, Int_t pdg){
    
    
    // MC label
    Int_t label       = track->GetLabel();
    
    //MC particle
    TParticle *part   = fMcEvent->Particle(label);
    
    
    Int_t pdgma = 0;
    Int_t motherlbl = 0;
    motherlbl = part->GetFirstMother();
    Int_t istep = 0;
    Bool_t isFound = false;
    
    if(motherlbl > -1){
        TParticle* motherPart = fMcEvent->Particle(motherlbl);
        if(motherPart){
            pdgma = motherPart->GetPdgCode();
            if(TMath::Abs(pdgma)==pdg) {
                isFound=true;
                //Printf("IsTrackFromCharmBaryon(%d=%s, %d)::: ---->>>> motherlbl=%d, pdgma=%d, namema=%s, isfound=%d",label,part->GetName(),pdg,motherlbl,pdgma,motherPart->GetName(),isFound);
            }
        }
    }
    return isFound;
    
    
}
//_________________________________________
bool AliAnalysisTaskSEOmegacccToOmega3Pi::FillHistoOmegac(AliESDcascade *casc, AliESDtrack *track, AliESDVertex *esdVc) {
    
    UInt_t lIdxPosCasc     = (UInt_t) TMath::Abs( casc->GetPindex() );
    UInt_t lIdxNegCasc     = (UInt_t) TMath::Abs( casc->GetNindex() );
    UInt_t lBachIdx        = (UInt_t) TMath::Abs( casc->GetBindex() );
    AliESDtrack *pTrackCasc        = fEvent->GetTrack( lIdxPosCasc );
    AliESDtrack *nTrackCasc        = fEvent->GetTrack( lIdxNegCasc );
    AliESDtrack *bachTrackCasc     = fEvent->GetTrack( lBachIdx );
    //MC
    Int_t lblPosCasc  = pTrackCasc->GetLabel();
    Int_t lblNegCasc  = nTrackCasc->GetLabel();
    Int_t lblBachCasc = bachTrackCasc->GetLabel();
    Int_t lblTrack    = track->GetLabel();
    TParticle* mcPosCascDghter  = fMcEvent->Particle( lblPosCasc );
    TParticle* mcNegCascDghter  = fMcEvent->Particle( lblNegCasc );
    TParticle* mcBachCascDghter = fMcEvent->Particle( lblBachCasc );
    TParticle* mcTrack          = fMcEvent->Particle( lblTrack );
    Int_t lblCasc = mcBachCascDghter->GetFirstMother();
    Int_t lblV0   = mcPosCascDghter->GetFirstMother();
    Int_t lblOmegac   = mcTrack->GetFirstMother();
    
    if(lblOmegac>-1){
        fTreeVariableGenPtOmegac[0]  = ((TParticle*)fMcEvent->Particle( lblOmegac ))->Pt();
        fTreeVariableGenEtaOmegac[0] = ((TParticle*)fMcEvent->Particle( lblOmegac ))->Eta();
        fTreeVariableGenPhiOmegac[0] = ((TParticle*)fMcEvent->Particle( lblOmegac ))->Phi();
        fTreeVariableGenRapOmegac[0] = ((TParticle*)fMcEvent->Particle( lblOmegac ))->Y();
        fTreeVariableGenRxyOmegac[0] = ((TParticle*)fMcEvent->Particle( lblOmegac ))->R();
    }
    if(lblCasc>-1){
        fTreeVariableGenPtOmegac[1]  = ((TParticle*)fMcEvent->Particle( lblCasc ))->Pt();
        fTreeVariableGenEtaOmegac[1] = ((TParticle*)fMcEvent->Particle( lblCasc ))->Eta();
        fTreeVariableGenPhiOmegac[1] = ((TParticle*)fMcEvent->Particle( lblCasc ))->Phi();
        fTreeVariableGenRapOmegac[1] = ((TParticle*)fMcEvent->Particle( lblCasc ))->Y();
        fTreeVariableGenRxyOmegac[1] = ((TParticle*)fMcEvent->Particle( lblCasc ))->R();
    }
    fTreeVariableGenPtOmegac[2]  = mcTrack->Pt();
    fTreeVariableGenEtaOmegac[2] = mcTrack->Eta();
    fTreeVariableGenPhiOmegac[2] = mcTrack->Phi();
    fTreeVariableGenRapOmegac[2] = mcTrack->Y();
    fTreeVariableGenRxyOmegac[2] = mcTrack->R();
    fIsSignalOmegac = CheckIsSignalOmegac(pTrackCasc, nTrackCasc, bachTrackCasc, track);
    
    
    //omega c
    //---> Omega
    //Printf("FillHistoOmegac---> Before GetTrackParamForCascade");
    AliExternalTrackParam *cascTrack = GetTrackParamForCascade(casc);
    //Printf("FillHistoOmegac---> After GetTrackParamForCascade");
    AliExternalTrackParam etpCasc;
    etpCasc.CopyFromVTrack(cascTrack);
    Double_t d0zVert[2],covd0zVert[3];
    cascTrack->PropagateToDCA(esdVc,fBzkG,100.,d0zVert,covd0zVert);
    Double_t d0zVertCasc[2],covd0zVertCasc[3];
    etpCasc.PropagateToDCA(fV1,fBzkG,100.,d0zVertCasc,covd0zVertCasc);
    Int_t pdgomega=3334;
    Double_t massOmega = TDatabasePDG::Instance()->GetParticle(pdgomega)->Mass();
    Double_t pxomega = cascTrack->Px();
    Double_t pyomega = cascTrack->Py();
    Double_t pzomega = cascTrack->Pz();
    Double_t pomega2 = pxomega*pxomega + pyomega*pyomega + pzomega*pzomega;
    Double_t eomega2 = (massOmega*massOmega)+pomega2;
    Double_t eomega = TMath::Sqrt(eomega2);
    Double_t pomega = TMath::Sqrt(pomega2);
    Double_t pxpypzomega[3] = {0.,0.,0.}; pxpypzomega[0]=pxomega; pxpypzomega[1]=pyomega; pxpypzomega[2]=pzomega;
    Double_t poscasc[3] = { -1000.0, -1000.0, -1000.0 };
    casc->GetXYZcascade(poscasc[0],poscasc[1],poscasc[2]);
    Double_t radiusOmega=TMath::Sqrt(poscasc[0]*poscasc[0]+poscasc[1]*poscasc[1]+poscasc[2]*poscasc[2]);
    Double_t lV0quality = 0.;
    Float_t invMassCasc=0.;
    if(bachTrackCasc->Charge()>0){
        casc->ChangeMassHypothesis(lV0quality , -3334);
        invMassCasc=casc->GetEffMassXi();
        lV0quality = 0.;
    }
    else {
        casc->ChangeMassHypothesis(lV0quality , 3334);
        invMassCasc=casc->GetEffMassXi();
        lV0quality = 0.;
    }
    Double_t ptOmega=TMath::Sqrt(pxomega*pxomega + pyomega*pyomega);
    Double_t cosPAOmega=casc->GetCascadeCosineOfPointingAngle(esdVc->GetX(), esdVc->GetY(),esdVc->GetZ());
    //---> track
    Double_t d0zVertT[2],covd0zVertT[3];
    AliExternalTrackParam etp;
    etp.CopyFromVTrack(track);
    etp.PropagateToDCA(esdVc,fBzkG,100.,d0zVertT,covd0zVertT);
    Int_t pdgtrack=211;
    Double_t masspi = TDatabasePDG::Instance()->GetParticle(pdgtrack)->Mass();
    Double_t pxpi1 = etp.Px();
    Double_t pypi1 = etp.Py();
    Double_t pzpi1 = etp.Pz();
    Double_t ppi12 = pxpi1*pxpi1 + pypi1*pypi1 + pzpi1*pzpi1;
    Double_t epi12 = (masspi*masspi)+ppi12;
    Double_t epi1  = TMath::Sqrt(epi12);
    Double_t ppi1  = TMath::Sqrt(ppi12);
    Double_t pxpypzpi[3] = {0.,0.,0.}; pxpypzpi[0]=pxpi1; pxpypzpi[1]=pypi1; pxpypzpi[2]=pzpi1;
    Double_t b[2];
    Double_t bCov[3];
    AliExternalTrackParam etpcp;
    etpcp.CopyFromVTrack(track);
    etpcp.PropagateToDCA(fV1,fBzkG,100.,b,bCov);
    //---> Omegac
    Double_t pxomegac = pxomega+pxpi1;
    Double_t pyomegac = pyomega+pypi1;
    Double_t pzomegac = pzomega+pzpi1;
    Double_t pxpypzomegac[3]; pxpypzomegac[0]=pxomegac; pxpypzomegac[1]=pyomegac; pxpypzomegac[2]=pzomegac;
    Double_t ptomegac = TMath::Sqrt(pxomegac*pxomegac+pyomegac*pyomegac);
    Double_t decLXYomegac  = DecayLengthXY(fV1, esdVc);
    Double_t decLomegac  = DecayLength(fV1, esdVc);
    //Double_t cosPAXYomegac = CosPointingAngleXY(esdVcc, esdVc, pxpypzomegac);
    Double_t impparT1 = b[0];//d0zVertT[0];
    Double_t invmass2omegac = (eomega+epi1)*(eomega+epi1)-(pxomegac*pxomegac+pyomegac*pyomegac+pzomegac*pzomegac);
    Double_t invmassomegac  = TMath::Sqrt(invmass2omegac);
    Double_t eomegac_ = eomega+epi1;
    Double_t pomegac_ = TMath::Sqrt(pxomegac*pxomegac+pyomegac*pyomegac+pzomegac*pzomegac);
    //Printf("FillHistoOmegac---> Before GetTrackParamForOmegac");
    AliExternalTrackParam *omegacTrack = GetTrackParamForOmegac(esdVc, casc, track);
    //Printf("FillHistoOmegac---> After GetTrackParamForOmegac");
    Double_t pxpypz[3] = {0.,0.,0.}; pxpypz[0]=pxomegac; pxpypz[1]=pyomegac; pxpypz[2]=pzomegac;
    Double_t costThetaStar = CosThetaStar(1,4332,3334,211, pxpypz, pxpypzomega, pxpypzpi);
    Double_t d0zVertC[2],covd0zVertC[3];
    omegacTrack->PropagateToDCA(fV1,0,100.,d0zVertC,covd0zVertC);
    Double_t impparC  = d0zVertC[0];
    Double_t vtxchi2ndfc = esdVc->GetChi2toNDF();
    
    
    fOmegacVariables[0] = invmassomegac;
    fOmegacVariables[1] = ptomegac;
    fOmegacVariables[2] = decLomegac;
    fOmegacVariables[3] = decLXYomegac;
    fOmegacVariables[4] = impparC;
    fOmegacVariables[5] = impparT1;
    fOmegacVariables[6] = TMath::Sqrt(pxpi1*pxpi1 + pypi1*pypi1);
    fOmegacVariables[7] = costThetaStar;
    fOmegacVariables[10] = vtxchi2ndfc;
    
    fTreeVariableDecVtxChi2NdfOmegac=vtxchi2ndfc;
    fTreeVariableDecayLengthOmegac=decLomegac;
    fTreeVariableDecayLengthXYOmegac=decLXYomegac;
    fTreeVariableInvMassOmegac[0]=invmassomegac;
    fTreeVariableInvMassOmegac[1]=invMassCasc;
    fTreeVariabled0rphiOmegac[0]=impparC; // omegac
    fTreeVariabled0rphiOmegac[1]=d0zVertCasc[0]; // omega
    fTreeVariabled0rphiOmegac[2]=impparT1; // pion
    fTreeVariablePtOmegac[0]=ptomegac;
    fTreeVariablePtOmegac[1]=casc->Pt();
    fTreeVariablePtOmegac[2]=track->Pt();
    fTreeVariableEtaOmegac[0]=EtaCand(pomegac_, pzomegac);
    fTreeVariableEtaOmegac[1]=casc->Eta();
    fTreeVariableEtaOmegac[2]=track->Eta();
    fTreeVariablePhiOmegac[0]=PhiCand(pxomegac,pyomegac);
    fTreeVariablePhiOmegac[1]=casc->Phi();
    fTreeVariablePhiOmegac[2]=track->Phi();
    fTreeVariableRapOmegac[0]=YCand(eomegac_, pzomegac);
    fTreeVariableRapOmegac[1]=casc->Y();
    fTreeVariableRapOmegac[2]=track->Y();

    fTreeCutVarOmegac->Fill();
    
    //apply cuts
    bool issel = IsSelectedOmegac(fOmegacVariables);
    delete cascTrack;   cascTrack=NULL;
    delete omegacTrack; omegacTrack=NULL;
    return issel;
    
}
//_________________________________________
bool AliAnalysisTaskSEOmegacccToOmega3Pi::FillHistoOmegacc(AliESDcascade *casc, AliESDtrack *track, AliESDtrack *track2, AliESDVertex *esdVc, AliESDVertex *esdVcc) {
    UInt_t lIdxPosCasc     = (UInt_t) TMath::Abs( casc->GetPindex() );
    UInt_t lIdxNegCasc     = (UInt_t) TMath::Abs( casc->GetNindex() );
    UInt_t lBachIdx        = (UInt_t) TMath::Abs( casc->GetBindex() );
    AliESDtrack *pTrackCasc         = fEvent->GetTrack( lIdxPosCasc );
    AliESDtrack *nTrackCasc         = fEvent->GetTrack( lIdxNegCasc );
    AliESDtrack *bachTrackCasc      = fEvent->GetTrack( lBachIdx );
    
    //omega c
    //---> Omega
    //Printf("FillHistoOmegacc---> Before GetTrackParamForCascade");
    AliExternalTrackParam *cascTrack = GetTrackParamForCascade(casc);
    //Printf("FillHistoOmegacc---> After GetTrackParamForCascade");
    Double_t d0zVert[2],covd0zVert[3];
    cascTrack->PropagateToDCA(esdVc,fBzkG,100.,d0zVert,covd0zVert);
    Int_t pdgomega=3334;
    Double_t massOmega = TDatabasePDG::Instance()->GetParticle(pdgomega)->Mass();
    Double_t pxomega = cascTrack->Px();
    Double_t pyomega = cascTrack->Py();
    Double_t pzomega = cascTrack->Pz();
    Double_t pomega2 = pxomega*pxomega + pyomega*pyomega + pzomega*pzomega;
    Double_t eomega2 = (massOmega*massOmega)+pomega2;
    Double_t eomega = TMath::Sqrt(eomega2);
    Double_t pomega = TMath::Sqrt(pomega2);
    Double_t poscasc[3] = { -1000.0, -1000.0, -1000.0 };
    casc->GetXYZcascade(poscasc[0],poscasc[1],poscasc[2]);
    Double_t radiusOmega=TMath::Sqrt(poscasc[0]*poscasc[0]+poscasc[1]*poscasc[1]+poscasc[2]*poscasc[2]);
    Double_t lV0quality = 0.;
    Float_t invMassCasc=0.;
    if(bachTrackCasc->Charge()>0){
        casc->ChangeMassHypothesis(lV0quality , -3334);
        invMassCasc=casc->GetEffMassXi();
        lV0quality = 0.;
    }
    else {
        casc->ChangeMassHypothesis(lV0quality , 3334);
        invMassCasc=casc->GetEffMassXi();
        lV0quality = 0.;
    }
    //Double_t invmassOmega=casc->GetEffMassXi();
    Double_t ptOmega=TMath::Sqrt(pxomega*pxomega + pyomega*pyomega);
    Double_t cosPAOmega=casc->GetCascadeCosineOfPointingAngle(esdVc->GetX(), esdVc->GetY(),esdVc->GetZ());
    //---> track
    Double_t d0zVertT[2],covd0zVertT[3];
    AliExternalTrackParam etp;
    etp.CopyFromVTrack(track);
    etp.PropagateToDCA(esdVc,fBzkG,100.,d0zVertT,covd0zVertT);
    Int_t pdgtrack=211;
    Double_t masspi = TDatabasePDG::Instance()->GetParticle(pdgtrack)->Mass();
    Double_t pxpi1 = etp.Px();
    Double_t pypi1 = etp.Py();
    Double_t pzpi1 = etp.Pz();
    Double_t ppi12 = pxpi1*pxpi1 + pypi1*pypi1 + pzpi1*pzpi1;
    Double_t epi12 = (masspi*masspi)+ppi12;
    Double_t epi1  = TMath::Sqrt(epi12);
    Double_t ppi1  = TMath::Sqrt(ppi12);
    //---> Omegac
    Double_t pxomegac = pxomega+pxpi1;
    Double_t pyomegac = pyomega+pypi1;
    Double_t pzomegac = pzomega+pzpi1;
    Double_t pxpypzomegac[3]; pxpypzomegac[0]=pxomegac; pxpypzomegac[1]=pyomegac; pxpypzomegac[2]=pzomegac;
    Double_t ptomegac = TMath::Sqrt(pxomegac*pxomegac+pyomegac*pyomegac);
    //Double_t decLXYomegac  = DecayLengthXY(esdVcc, esdVc);
    //    Double_t cosPAXYomegac = CosPointingAngleXY(esdVcc, esdVc, pxpypzomegac);
    //    Double_t impparT1 = d0zVertT[0];
    Double_t invmass2omegac = (eomega+epi1)*(eomega+epi1)-(pxomegac*pxomegac+pyomegac*pyomegac+pzomegac*pzomegac);
    Double_t invmassomegac  = TMath::Sqrt(invmass2omegac);
    AliExternalTrackParam *omegacTrack = GetTrackParamForOmegac(esdVc, casc, track);
    Double_t d0zVertC[2],covd0zVertC[3];
    omegacTrack->PropagateToDCA(esdVcc,0,100.,d0zVertC,covd0zVertC);
    
    //omega cc
    //---> omega c
    Int_t pdgomegac=4332;
    Double_t massomegac = TDatabasePDG::Instance()->GetParticle(pdgomegac)->Mass();
    Double_t pxomegacprop = omegacTrack->Px();
    Double_t pyomegacprop = omegacTrack->Py();
    Double_t pzomegacprop = omegacTrack->Pz();
    Double_t pomegac2 = pxomegacprop*pxomegacprop + pyomegacprop*pyomegacprop + pzomegacprop*pzomegacprop;
    Double_t eomegac2 = (invmass2omegac)+pomegac2;
    Double_t eomegac = TMath::Sqrt(eomegac2);
    Double_t pomegac = TMath::Sqrt(pomegac2);
    Double_t pxpypzomegacprop[3]; pxpypzomegacprop[0]=pxomegacprop; pxpypzomegacprop[1]=pyomegacprop; pxpypzomegacprop[2]=pzomegacprop;
    //---> track
    Double_t d0zVertT2[2],covd0zVertT2[3];
    AliExternalTrackParam etp2;
    etp2.CopyFromVTrack(track2);
    etp2.PropagateToDCA(esdVcc,fBzkG,100.,d0zVertT2,covd0zVertT2);
    Double_t pxpi2 = etp2.Px();
    Double_t pypi2 = etp2.Py();
    Double_t pzpi2 = etp2.Pz();
    Double_t ppi22 = pxpi2*pxpi2 + pypi2*pypi2 + pzpi2*pzpi2;
    Double_t epi22 = (masspi*masspi)+ppi22;
    Double_t epi2  = TMath::Sqrt(epi22);
    Double_t ppi2  = TMath::Sqrt(ppi22);
    Double_t pxpypzpi2[3] = {0.,0.,0.}; pxpypzpi2[0]=pxpi2; pxpypzpi2[1]=pypi2; pxpypzpi2[2]=pzpi2;
    Double_t b[2];
    Double_t bCov[3];
    AliExternalTrackParam etpcp;
    etpcp.CopyFromVTrack(track2);
    etpcp.PropagateToDCA(fV1,fBzkG,100.,b,bCov);
    //---> Omegacc
    Double_t pxomegacc = pxomegacprop+pxpi2;
    Double_t pyomegacc = pyomegacprop+pypi2;
    Double_t pzomegacc = pzomegacprop+pzpi2;
    Double_t pxpypzomegacc[3]; pxpypzomegacc[0]=pxomegacc; pxpypzomegacc[1]=pyomegacc; pxpypzomegacc[2]=pzomegacc;
    Double_t ptomegacc = TMath::Sqrt(pxomegacc*pxomegacc+pyomegacc*pyomegacc);
    Double_t decLXYomegacc  = DecayLengthXY(fV1, esdVcc);
    Double_t decLomegacc  = DecayLength(fV1, esdVcc);
    //Double_t cosPAXYomegacc = CosPointingAngleXY(esdVccc, esdVcc, pxpypzomegacc);
    Double_t impparT2 = b[0];//d0zVertT2[0];
    Double_t invmass2omegacc = (eomegac+epi2)*(eomegac+epi2)-(pxomegacc*pxomegacc+pyomegacc*pyomegacc+pzomegacc*pzomegacc);
    Double_t invmassomegacc  = TMath::Sqrt(invmass2omegacc);
    AliExternalTrackParam *omegaccTrack = GetTrackParamForOmegacc(esdVcc, esdVc, casc, track, track2);
    Double_t costThetaStar = CosThetaStar(1,4432,4332,211, pxpypzomegacc, pxpypzomegacprop, pxpypzpi2);
    Double_t d0zVertCC[2],covd0zVertCC[3];
    omegaccTrack->PropagateToDCA(fV1,fBzkG,100.,d0zVertCC,covd0zVertCC);
    Double_t impparCC  = d0zVertCC[0];
    Double_t vtxchi2ndfcc = esdVcc->GetChi2toNDF();
    
    
    fOmegaccVariables[0] = invmassomegacc;
    fOmegaccVariables[1] = ptomegacc;
    fOmegaccVariables[2] = decLomegacc;
    fOmegaccVariables[3] = decLXYomegacc;
    fOmegaccVariables[4] = impparCC;
    fOmegaccVariables[5] = impparT2;
    fOmegaccVariables[6] = track2->Pt();//TMath::Sqrt(pxpi2*pxpi2 + pypi2*pypi2);
    fOmegaccVariables[7] = costThetaStar;
    fOmegaccVariables[10] = vtxchi2ndfcc;
    //apply cuts
    bool issel = IsSelectedOmegacc(fOmegaccVariables);
    
    
    
    delete cascTrack;    cascTrack=NULL;
    delete omegacTrack;  omegacTrack=NULL;
    delete omegaccTrack; omegaccTrack=NULL;
    return issel;
}
//_________________________________________
bool AliAnalysisTaskSEOmegacccToOmega3Pi::FillHistoOmegaccc(AliESDcascade *casc, AliESDtrack *track, AliESDtrack *track2, AliESDtrack *track3, AliESDVertex *esdVc, AliESDVertex *esdVcc, AliESDVertex *esdVccc) {
    
    UInt_t lIdxPosCasc     = (UInt_t) TMath::Abs( casc->GetPindex() );
    UInt_t lIdxNegCasc     = (UInt_t) TMath::Abs( casc->GetNindex() );
    UInt_t lBachIdx        = (UInt_t) TMath::Abs( casc->GetBindex() );
    AliESDtrack *pTrackCasc        = fEvent->GetTrack( lIdxPosCasc );
    AliESDtrack *nTrackCasc        = fEvent->GetTrack( lIdxNegCasc );
    AliESDtrack *bachTrackCasc     = fEvent->GetTrack( lBachIdx );
    Int_t lblPosCasc  = pTrackCasc->GetLabel();
    Int_t lblNegCasc  = nTrackCasc->GetLabel();
    Int_t lblBachCasc = bachTrackCasc->GetLabel();
    TParticle* mcPosCascDghter  = fMcEvent->Particle( lblPosCasc );
    TParticle* mcNegCascDghter  = fMcEvent->Particle( lblNegCasc );
    TParticle* mcBachCascDghter = fMcEvent->Particle( lblBachCasc );
    Int_t lblCasc = mcBachCascDghter->GetFirstMother();
    Int_t lblV0   = mcPosCascDghter->GetFirstMother();
    
    Bool_t issignal=CheckIsSignalOmegaccc(pTrackCasc, nTrackCasc, bachTrackCasc, track, track2, track3);
    
    //variables
    Float_t xVccc=0., yVccc=0., zVccc=0., xVcc=0., yVcc=0., zVcc=0., xVc=0., yVc=0., zVc=0.;
    xVccc = esdVccc->GetX();
    yVccc = esdVccc->GetY();
    zVccc = esdVccc->GetZ();
    xVcc  = esdVcc->GetX();
    yVcc  = esdVcc->GetY();
    zVcc  = esdVcc->GetZ();
    xVc   = esdVc->GetX();
    yVc   = esdVc->GetY();
    zVc   = esdVc->GetZ();
    Double_t vtxchi2ndfccc = esdVccc->GetChi2toNDF();
    Double_t vtxchi2ndfcc  = esdVcc->GetChi2toNDF();
    Double_t vtxchi2ndfc   = esdVc->GetChi2toNDF();
    fTreeVariableDecVtxChi2Ndf[0] = vtxchi2ndfccc;
    fTreeVariableDecVtxChi2Ndf[1] = vtxchi2ndfcc;
    fTreeVariableDecVtxChi2Ndf[2] = vtxchi2ndfc;
    fTreeVariableRecoTrueOmegacccDecVtxReco[0][0] = xVccc;
    fTreeVariableRecoTrueOmegacccDecVtxReco[0][1] = yVccc;
    fTreeVariableRecoTrueOmegacccDecVtxReco[0][2] = zVccc;
    fTreeVariableRecoTrueOmegacccDecVtxReco[1][0] = xVcc;
    fTreeVariableRecoTrueOmegacccDecVtxReco[1][1] = yVcc;
    fTreeVariableRecoTrueOmegacccDecVtxReco[1][2] = zVcc;
    fTreeVariableRecoTrueOmegacccDecVtxReco[2][0] = xVc;
    fTreeVariableRecoTrueOmegacccDecVtxReco[2][1] = yVc;
    fTreeVariableRecoTrueOmegacccDecVtxReco[2][2] = zVc;
    
    //omega c
    //****************************************************    Omega
    AliExternalTrackParam *cascTrack = GetTrackParamForCascade(casc);
    Double_t d0zVert[2],covd0zVert[3];
    //propagate Omega to Omegac decay vertex
    cascTrack->PropagateToDCA(esdVc,fBzkG,100.,d0zVert,covd0zVert);
    Int_t pdgomega=3334;
    Double_t massOmega = TDatabasePDG::Instance()->GetParticle(pdgomega)->Mass();
    Double_t pxomega = cascTrack->Px();
    Double_t pyomega = cascTrack->Py();
    Double_t pzomega = cascTrack->Pz();
    Double_t pomega2 = pxomega*pxomega + pyomega*pyomega + pzomega*pzomega;
    Double_t eomega2 = (massOmega*massOmega)+pomega2;
    Double_t eomega = TMath::Sqrt(eomega2);
    Double_t pomega = TMath::Sqrt(pomega2);
    Double_t poscasc[3] = { -1000.0, -1000.0, -1000.0 };
    casc->GetXYZcascade(poscasc[0],poscasc[1],poscasc[2]);
    Double_t ptOmega=TMath::Sqrt(pxomega*pxomega + pyomega*pyomega);
    fTreeVariableRecoTrueOmegacccMomReco[4][0] = pxomega;
    fTreeVariableRecoTrueOmegacccMomReco[4][1] = pyomega;
    fTreeVariableRecoTrueOmegacccMomReco[4][2] = pzomega;
    fTreeVariableRecoTrueOmegacccDecVtxReco[4][0] = poscasc[0];
    fTreeVariableRecoTrueOmegacccDecVtxReco[4][1] = poscasc[1];
    fTreeVariableRecoTrueOmegacccDecVtxReco[4][2] = poscasc[2];
    if(lblCasc>-1){
        fTreeVariableRecoTrueOmegacccMomGen[4][0] = ((TParticle*)fMcEvent->Particle( lblCasc ))->Px();
        fTreeVariableRecoTrueOmegacccMomGen[4][1] = ((TParticle*)fMcEvent->Particle( lblCasc ))->Py();
        fTreeVariableRecoTrueOmegacccMomGen[4][2] = ((TParticle*)fMcEvent->Particle( lblCasc ))->Pz();
    }
    fTreeVariableRecoTrueOmegacccDecVtxGen[4][0]  = mcBachCascDghter->Vx();
    fTreeVariableRecoTrueOmegacccDecVtxGen[4][1]  = mcBachCascDghter->Vy();
    fTreeVariableRecoTrueOmegacccDecVtxGen[4][2]  = mcBachCascDghter->Vz();
    fTreeVariableGenPt[8]  = mcBachCascDghter->Pt();
    fTreeVariableGenEta[8] = mcBachCascDghter->Eta();
    fTreeVariableGenPhi[8] = mcBachCascDghter->Phi();
    fTreeVariableGenRap[8] = mcBachCascDghter->Y();
    fTreeVariableGenRxy[8] = mcBachCascDghter->R();
    //    Double_t xyz[3];
    //    casc->XvYvZv(xyz);
    //    Double_t cov[6]; //for(int j=0; j<6; j++) cov[j]=0;
    //    casc->GetPosCovXi(cov);
    //    AliESDVertex *vertexcasc = new AliESDVertex(xyz,cov,casc->GetChi2Xi(),0,"VertexCasc");
    //    AliExternalTrackParam etpBach;
    //    etpBach.CopyFromVTrack(bachTrackCasc);
    //    Double_t d0zBach[2],covd0zBach[3];
    //    etpBach.PropagateToDCA(vertexcasc,fBzkG,100.,d0zBach,covd0zBach);
    //    fTreeVariablePt[8]  = etpBach.Pt();
    //    fTreeVariableEta[8] = etpBach.Eta();
    //    fTreeVariablePhi[8] = etpBach.Phi();
    //    fTreeVariableRap[8] = etpBach.Y();
    //    delete vertexcasc; vertexcasc=NULL;
    fTreeVariablePt[8]  = bachTrackCasc->Pt();
    fTreeVariableEta[8] = bachTrackCasc->Eta();
    fTreeVariablePhi[8] = bachTrackCasc->Phi();
    fTreeVariableRap[8] = bachTrackCasc->Y();
    
    //V0
    //-->RECO
    Int_t idxV0FromCascade = -1;
    for(int iv0=0; iv0<fEvent->GetNumberOfV0s(); iv0++){
        UInt_t posCurrentV0 = ((AliESDv0*)fEvent->GetV0(iv0))->GetPindex();
        UInt_t negCurrentV0 = ((AliESDv0*)fEvent->GetV0(iv0))->GetNindex();
        if (posCurrentV0==lIdxPosCasc && negCurrentV0==lIdxNegCasc) {
            idxV0FromCascade = iv0;
            break;
        }
    }
    //V0 momentum and decay vertex reco
    if(idxV0FromCascade>-1){
        fTreeVariableRecoTrueOmegacccMomReco[3][0] = ((AliESDv0*)fEvent->GetV0(idxV0FromCascade))->Px();
        fTreeVariableRecoTrueOmegacccMomReco[3][1] = ((AliESDv0*)fEvent->GetV0(idxV0FromCascade))->Py();
        fTreeVariableRecoTrueOmegacccMomReco[3][2] = ((AliESDv0*)fEvent->GetV0(idxV0FromCascade))->Pz();
        fTreeVariableRecoTrueOmegacccDecVtxReco[3][0] = ((AliESDv0*)fEvent->GetV0(idxV0FromCascade))->Xv();
        fTreeVariableRecoTrueOmegacccDecVtxReco[3][1] = ((AliESDv0*)fEvent->GetV0(idxV0FromCascade))->Yv();
        fTreeVariableRecoTrueOmegacccDecVtxReco[3][2] = ((AliESDv0*)fEvent->GetV0(idxV0FromCascade))->Zv();
        //        AliESDtrack *posVV0track = (AliESDtrack*)(fEvent->GetTrack( ((AliESDv0*)fEvent->GetV0(idxV0FromCascade))->GetPindex() ));
        //        AliESDtrack *negVV0track = (AliESDtrack*)(fEvent->GetTrack( ((AliESDv0*)fEvent->GetV0(idxV0FromCascade))->GetNindex() ));
        //        fTreeVariablePt[6]  = negVV0track->Pt();
        //        fTreeVariableEta[6] = negVV0track->Eta();
        //        fTreeVariablePhi[6] = negVV0track->Phi();
        //        fTreeVariableRap[6] = negVV0track->Y();
        //        fTreeVariablePt[7]  = posVV0track->Pt();
        //        fTreeVariableEta[7] = posVV0track->Eta();
        //        fTreeVariablePhi[7] = posVV0track->Phi();
        //        fTreeVariableRap[7] = posVV0track->Y();
        //        delete posVV0track; posVV0track=NULL;
        //        delete negVV0track; negVV0track=NULL;
        fTreeVariablePt[6]  = nTrackCasc->Pt();
        fTreeVariableEta[6] = nTrackCasc->Eta();
        fTreeVariablePhi[6] = nTrackCasc->Phi();
        fTreeVariableRap[6] = nTrackCasc->Y();
        fTreeVariablePt[7]  = pTrackCasc->Pt();
        fTreeVariableEta[7] = pTrackCasc->Eta();
        fTreeVariablePhi[7] = pTrackCasc->Phi();
        fTreeVariableRap[7] = pTrackCasc->Y();
    }
    if(lblV0>-1){
        fTreeVariableRecoTrueOmegacccMomGen[3][0] = ((TParticle*)fMcEvent->Particle( lblV0 ))->Px();
        fTreeVariableRecoTrueOmegacccMomGen[3][1] = ((TParticle*)fMcEvent->Particle( lblV0 ))->Py();
        fTreeVariableRecoTrueOmegacccMomGen[3][2] = ((TParticle*)fMcEvent->Particle( lblV0 ))->Pz();
    }
    fTreeVariableRecoTrueOmegacccDecVtxGen[3][0]  = mcPosCascDghter->Vx();
    fTreeVariableRecoTrueOmegacccDecVtxGen[3][1]  = mcPosCascDghter->Vy();
    fTreeVariableRecoTrueOmegacccDecVtxGen[3][2]  = mcPosCascDghter->Vz();
    fTreeVariableGenPt[6]  = mcNegCascDghter->Pt();
    fTreeVariableGenEta[6] = mcNegCascDghter->Eta();
    fTreeVariableGenPhi[6] = mcNegCascDghter->Phi();
    fTreeVariableGenRap[6] = mcNegCascDghter->Y();
    fTreeVariableGenRxy[6] = mcNegCascDghter->R();
    fTreeVariableGenPt[7]  = mcPosCascDghter->Pt();
    fTreeVariableGenEta[7] = mcPosCascDghter->Eta();
    fTreeVariableGenPhi[7] = mcPosCascDghter->Phi();
    fTreeVariableGenRap[7] = mcPosCascDghter->Y();
    fTreeVariableGenRxy[7] = mcPosCascDghter->R();
    //Double_t cosPAOmega=casc->GetCascadeCosineOfPointingAngle(esdVc->GetX(), esdVc->GetY(),esdVc->GetZ());
    //---> track
    Double_t d0zVertT[2],covd0zVertT[3];
    AliExternalTrackParam etp;
    etp.CopyFromVTrack(track);
    //propagate track to Omegac decay vertex
    etp.PropagateToDCA(esdVc,fBzkG,100.,d0zVertT,covd0zVertT);
    Int_t pdgtrack=211;
    Double_t masspi = TDatabasePDG::Instance()->GetParticle(pdgtrack)->Mass();
    Double_t pxpi1 = etp.Px();
    Double_t pypi1 = etp.Py();
    Double_t pzpi1 = etp.Pz();
    Double_t ppi12 = pxpi1*pxpi1 + pypi1*pypi1 + pzpi1*pzpi1;
    Double_t epi12 = (masspi*masspi)+ppi12;
    Double_t epi1  = TMath::Sqrt(epi12);
    Double_t ppi1  = TMath::Sqrt(ppi12);
    fTreeVariablePt[5] = track->Pt();//TMath::Sqrt(pxpi1*pxpi1 + pypi1*pypi1);
    fTreeVariableEta[5] = track->Eta();//etp.Eta();
    fTreeVariablePhi[5] = track->Phi();//etp.Phi();
    fTreeVariableRap[5] = track->Y();//YCand(epi1, pzpi1);
    Int_t ltrack1  = track->GetLabel();
    //Printf("ltrack1 = %d", ltrack1);
    if(ltrack1>-1){
        //Printf("%f",((TParticle*)fMcEvent->Particle(ltrack1))->Px());
        fTreeVariableGenPt[5] = ((TParticle*)fMcEvent->Particle(ltrack1))->Pt();
        fTreeVariableGenEta[5] = ((TParticle*)fMcEvent->Particle(ltrack1))->Eta();
        fTreeVariableGenPhi[5] = ((TParticle*)fMcEvent->Particle(ltrack1))->Phi();
        fTreeVariableGenRap[5] = ((TParticle*)fMcEvent->Particle(ltrack1))->Y();
        fTreeVariableGenRxy[5] = ((TParticle*)fMcEvent->Particle(ltrack1))->R();
        Int_t lblmother = ((TParticle*)fMcEvent->Particle(ltrack1))->GetFirstMother();
        if(lblmother>-1){
            fTreeVariableRecoTrueOmegacccDecVtxGen[2][0] = ((TParticle*)fMcEvent->Particle(ltrack1))->Vx();
            fTreeVariableRecoTrueOmegacccDecVtxGen[2][1] = ((TParticle*)fMcEvent->Particle(ltrack1))->Vy();
            fTreeVariableRecoTrueOmegacccDecVtxGen[2][2] = ((TParticle*)fMcEvent->Particle(ltrack1))->Vz();
            fTreeVariableRecoTrueOmegacccMomGen[2][0] = ((TParticle*)fMcEvent->Particle(lblmother))->Px();
            fTreeVariableRecoTrueOmegacccMomGen[2][1] = ((TParticle*)fMcEvent->Particle(lblmother))->Py();
            fTreeVariableRecoTrueOmegacccMomGen[2][2] = ((TParticle*)fMcEvent->Particle(lblmother))->Pz();
            fTreeVariableGenPt[2] = ((TParticle*)fMcEvent->Particle(lblmother))->Pt();
            fTreeVariableGenEta[2] = ((TParticle*)fMcEvent->Particle(lblmother))->Eta();
            fTreeVariableGenPhi[2] = ((TParticle*)fMcEvent->Particle(lblmother))->Phi();
            fTreeVariableGenRap[2] = ((TParticle*)fMcEvent->Particle(lblmother))->Y();
            fTreeVariableGenRxy[2] = ((TParticle*)fMcEvent->Particle(lblmother))->R();
        }
    }
    //impact parameter to the primary vertex
    //propagate track to the primary vertex to compute impact parameter
    Double_t b[2];
    Double_t bCov[3];
    AliExternalTrackParam etpcp;
    etpcp.CopyFromVTrack(track);
    etpcp.PropagateToDCA(fV1,fBzkG,100.,b,bCov);
    fTreeVariabled0rphi[5]=b[0];
    //---> Omegac
    Double_t pxomegac = pxomega+pxpi1;
    Double_t pyomegac = pyomega+pypi1;
    Double_t pzomegac = pzomega+pzpi1;
    Double_t pxpypzomegac[3]; pxpypzomegac[0]=pxomegac; pxpypzomegac[1]=pyomegac; pxpypzomegac[2]=pzomegac;
    Double_t ptomegac = TMath::Sqrt(pxomegac*pxomegac+pyomegac*pyomegac);
    Double_t decLXYomegac  = DecayLengthXY(fV1, esdVc);
    Double_t cosPAXYomegac = CosPointingAngleXY(esdVcc, esdVc, pxpypzomegac);
    Double_t decLomegac  = DecayLength(fV1, esdVc);
    Double_t cosPAomegac = CosPointingAngle(esdVcc, esdVc, pxpypzomegac);
    Double_t eomegac_ = eomega+epi1;
    Double_t pomegac_ = TMath::Sqrt(pxomegac*pxomegac+pyomegac*pyomegac+pzomegac*pzomegac);
    Double_t invmass2omegac = (eomega+epi1)*(eomega+epi1)-(pxomegac*pxomegac+pyomegac*pyomegac+pzomegac*pzomegac);
    Double_t invmassomegac  = TMath::Sqrt(invmass2omegac);
    fTreeVariableInvMass[2] = invmassomegac;
    fTreeVariableCosPointingAngle[2] = cosPAomegac;
    fTreeVariableCosPointingAngleXY[2] = cosPAXYomegac;
    fTreeVariableDecayLength[2] = decLomegac;
    fTreeVariableDecayLengthXY[2] = decLXYomegac;
    fTreeVariablePt[2] = ptomegac;
    fTreeVariableEta[2] = EtaCand(pomegac_, pzomegac);
    fTreeVariablePhi[2] = PhiCand(pxomegac,pyomegac);
    fTreeVariableRap[2] = YCand(eomegac_, pzomegac);
    Double_t d0zVertC[2],covd0zVertC[3];
    AliExternalTrackParam *omegacTrackCp = GetTrackParamForOmegac(esdVc, casc, track);
    //propagate Omegac to the primary vertex to compute impact parameter
    omegacTrackCp->PropagateToDCA(fV1,0,100.,d0zVertC,covd0zVertC);
    fTreeVariabled0rphi[2] = d0zVertC[0];
    //propagate Omegac to the Omegacc vertex
    AliExternalTrackParam *omegacTrack = GetTrackParamForOmegac(esdVc, casc, track);
    omegacTrack->PropagateToDCA(esdVcc,0,100.,d0zVertC,covd0zVertC);
    
    //***************************************omega cc
    //---> omega c
    Int_t pdgomegac=4332;
    Double_t massomegac = TDatabasePDG::Instance()->GetParticle(pdgomegac)->Mass();
    Double_t pxomegacprop = omegacTrack->Px();
    Double_t pyomegacprop = omegacTrack->Py();
    Double_t pzomegacprop = omegacTrack->Pz();
    Double_t pomegac2 = pxomegacprop*pxomegacprop + pyomegacprop*pyomegacprop + pzomegacprop*pzomegacprop;
    Double_t eomegac2 = (invmass2omegac)+pomegac2;
    Double_t eomegac = TMath::Sqrt(eomegac2);
    Double_t pomegac = TMath::Sqrt(pomegac2);
    fTreeVariableRecoTrueOmegacccMomReco[2][0] = pxomegacprop;
    fTreeVariableRecoTrueOmegacccMomReco[2][1] = pyomegacprop;
    fTreeVariableRecoTrueOmegacccMomReco[2][2] = pzomegacprop;
    //---> track
    //propagate track to Omegacc decay vertex
    Double_t d0zVertT2[2],covd0zVertT2[3];
    AliExternalTrackParam etp2;
    etp2.CopyFromVTrack(track2);
    etp2.PropagateToDCA(esdVcc,fBzkG,100.,d0zVertT2,covd0zVertT2);
    Double_t pxpi2 = etp2.Px();
    Double_t pypi2 = etp2.Py();
    Double_t pzpi2 = etp2.Pz();
    Double_t ppi22 = pxpi2*pxpi2 + pypi2*pypi2 + pzpi2*pzpi2;
    Double_t epi22 = (masspi*masspi)+ppi22;
    Double_t epi2  = TMath::Sqrt(epi22);
    Double_t ppi2  = TMath::Sqrt(ppi22);
    fTreeVariablePt[4]  = track2->Pt();//TMath::Sqrt(pxpi2*pxpi2 + pypi2*pypi2);
    fTreeVariableEta[4] = track2->Eta();//etp2.Eta();
    fTreeVariablePhi[4] = track2->Phi();//etp2.Phi();
    fTreeVariableRap[4] = track2->Y();//YCand(epi2, pzpi2);
    Int_t ltrack2  = track2->GetLabel();
    if(ltrack2>-1){
        //Printf("%f",((TParticle*)fMcEvent->Particle(ltrack1))->Px());
        fTreeVariableGenPt[4] = ((TParticle*)fMcEvent->Particle(ltrack2))->Pt();
        fTreeVariableGenEta[4] = ((TParticle*)fMcEvent->Particle(ltrack2))->Eta();
        fTreeVariableGenPhi[4] = ((TParticle*)fMcEvent->Particle(ltrack2))->Phi();
        fTreeVariableGenRap[4] = ((TParticle*)fMcEvent->Particle(ltrack2))->Y();
        fTreeVariableGenRxy[4] = ((TParticle*)fMcEvent->Particle(ltrack2))->R();
        Int_t lblmother = ((TParticle*)fMcEvent->Particle(ltrack2))->GetFirstMother();
        if(lblmother>-1){
            fTreeVariableRecoTrueOmegacccDecVtxGen[1][0] = ((TParticle*)fMcEvent->Particle(ltrack2))->Vx();
            fTreeVariableRecoTrueOmegacccDecVtxGen[1][1] = ((TParticle*)fMcEvent->Particle(ltrack2))->Vy();
            fTreeVariableRecoTrueOmegacccDecVtxGen[1][2] = ((TParticle*)fMcEvent->Particle(ltrack2))->Vz();
            fTreeVariableRecoTrueOmegacccMomGen[1][0] = ((TParticle*)fMcEvent->Particle(lblmother))->Px();
            fTreeVariableRecoTrueOmegacccMomGen[1][1] = ((TParticle*)fMcEvent->Particle(lblmother))->Py();
            fTreeVariableRecoTrueOmegacccMomGen[1][2] = ((TParticle*)fMcEvent->Particle(lblmother))->Pz();
            fTreeVariableGenPt[1] = ((TParticle*)fMcEvent->Particle(lblmother))->Pt();
            fTreeVariableGenEta[1] = ((TParticle*)fMcEvent->Particle(lblmother))->Eta();
            fTreeVariableGenPhi[1] = ((TParticle*)fMcEvent->Particle(lblmother))->Phi();
            fTreeVariableGenRap[1] = ((TParticle*)fMcEvent->Particle(lblmother))->Y();
            fTreeVariableGenRxy[1] = ((TParticle*)fMcEvent->Particle(lblmother))->R();
        }
    }
    //propagate track to the primary vertex to compute impact parameter
    Double_t b2[2];
    Double_t bCov2[3];
    AliExternalTrackParam etp2cp;
    etp2cp.CopyFromVTrack(track2);
    etp2cp.PropagateToDCA(fV1,fBzkG,100.,b2,bCov2);
    fTreeVariabled0rphi[4]=b2[0];
    //---> Omegacc
    Double_t pxomegacc = pxomegacprop+pxpi2;
    Double_t pyomegacc = pyomegacprop+pypi2;
    Double_t pzomegacc = pzomegacprop+pzpi2;
    Double_t pxpypzomegacc[3]; pxpypzomegacc[0]=pxomegacc; pxpypzomegacc[1]=pyomegacc; pxpypzomegacc[2]=pzomegacc;
    Double_t ptomegacc = TMath::Sqrt(pxomegacc*pxomegacc+pyomegacc*pyomegacc);
    Double_t decLXYomegacc  = DecayLengthXY(fV1, esdVcc);
    Double_t cosPAXYomegacc = CosPointingAngleXY(esdVccc, esdVcc, pxpypzomegacc);
    Double_t decLomegacc  = DecayLength(fV1, esdVcc);
    Double_t cosPAomegacc = CosPointingAngle(esdVccc, esdVcc, pxpypzomegacc);
    Double_t eomegacc_ = eomegac+epi2;
    Double_t pomegacc_ = TMath::Sqrt(pxomegacc*pxomegacc+pyomegacc*pyomegacc+pzomegacc*pzomegacc);
    Double_t invmass2omegacc = (eomegac+epi2)*(eomegac+epi2)-(pxomegacc*pxomegacc+pyomegacc*pyomegacc+pzomegacc*pzomegacc);
    Double_t invmassomegacc  = TMath::Sqrt(invmass2omegacc);
    fTreeVariableInvMass[1] = invmassomegacc;
    fTreeVariableCosPointingAngle[1] = cosPAomegacc;
    fTreeVariableCosPointingAngleXY[1] = cosPAXYomegacc;
    fTreeVariableDecayLength[1] = decLomegacc;
    fTreeVariableDecayLengthXY[1] = decLXYomegacc;
    fTreeVariablePt[1] = ptomegacc;
    fTreeVariableEta[1] = EtaCand(pomegacc_, pzomegacc);
    fTreeVariablePhi[1] = PhiCand(pxomegacc,pyomegacc);
    fTreeVariableRap[1] = YCand(eomegacc_, pzomegacc);
    //propagate Omegacc to the primary vertex to compute impact parameter
    Double_t d0zVertCC[2],covd0zVertCC[3];
    AliExternalTrackParam *omegaccTrackCp = GetTrackParamForOmegacc(esdVcc, esdVc, casc, track, track2);
    omegaccTrackCp->PropagateToDCA(fV1,0,100.,d0zVertCC,covd0zVertCC);
    fTreeVariabled0rphi[1] = d0zVertCC[0];
    //propagate Omegacc to the Omegaccc
    AliExternalTrackParam *omegaccTrack = GetTrackParamForOmegacc(esdVcc, esdVc, casc, track, track2);
    omegaccTrack->PropagateToDCA(esdVccc,fBzkG,100.,d0zVertCC,covd0zVertCC);
    //omega ccc
    //---> omega cc
    Int_t pdgomegacc=4432;
    Double_t massomegacc = TDatabasePDG::Instance()->GetParticle(pdgomegacc)->Mass();
    Double_t pxomegaccprop = omegaccTrack->Px();
    Double_t pyomegaccprop = omegaccTrack->Py();
    Double_t pzomegaccprop = omegaccTrack->Pz();
    Double_t pomegacc2 = pxomegaccprop*pxomegaccprop + pyomegaccprop*pyomegaccprop + pzomegaccprop*pzomegaccprop;
    Double_t eomegacc2 = (invmass2omegacc)+pomegacc2;
    Double_t eomegacc = TMath::Sqrt(eomegacc2);
    Double_t pomegacc = TMath::Sqrt(pomegacc2);
    Double_t pxpypzomegaccprop[3]; pxpypzomegaccprop[0]=pxomegaccprop; pxpypzomegaccprop[1]=pyomegaccprop; pxpypzomegaccprop[2]=pzomegaccprop;
    fTreeVariableRecoTrueOmegacccMomReco[1][0] = pxomegaccprop;
    fTreeVariableRecoTrueOmegacccMomReco[1][1] = pyomegaccprop;
    fTreeVariableRecoTrueOmegacccMomReco[1][2] = pzomegaccprop;
    //---> track
    Double_t d0zVertT3[2],covd0zVertT3[3];
    AliExternalTrackParam etp3;
    etp3.CopyFromVTrack(track3);
    etp3.PropagateToDCA(esdVccc,fBzkG,100.,d0zVertT3,covd0zVertT3);
    Double_t pxpi3 = etp3.Px();
    Double_t pypi3 = etp3.Py();
    Double_t pzpi3 = etp3.Pz();
    Double_t ppi32 = pxpi3*pxpi3 + pypi3*pypi3 + pzpi3*pzpi3;
    Double_t epi32 = (masspi*masspi)+ppi32;
    Double_t epi3  = TMath::Sqrt(epi32);
    Double_t ppi3  = TMath::Sqrt(ppi32);
    Double_t pxpypzpi3[3] = {0.,0.,0.}; pxpypzpi3[0]=pxpi3; pxpypzpi3[1]=pypi3; pxpypzpi3[2]=pzpi3;
    Int_t ltrack3  = (Int_t) track3->GetLabel();
    fTreeVariablePt[3]  = track3->Pt();//TMath::Sqrt(pxpi3*pxpi3 + pypi3*pypi3);
    fTreeVariableEta[3] = track3->Eta();//etp3.Eta();
    fTreeVariablePhi[3] = track3->Phi();//etp3.Phi();
    fTreeVariableRap[3] = track3->Y();//YCand(epi3, pzpi3);
    if(ltrack3>-1){
        //Printf("%f",((TParticle*)fMcEvent->Particle(ltrack1))->Px());
        fTreeVariableGenPt[3] = ((TParticle*)fMcEvent->Particle(ltrack3))->Pt();
        fTreeVariableGenEta[3] = ((TParticle*)fMcEvent->Particle(ltrack3))->Eta();
        fTreeVariableGenPhi[3] = ((TParticle*)fMcEvent->Particle(ltrack3))->Phi();
        fTreeVariableGenRap[3] = ((TParticle*)fMcEvent->Particle(ltrack3))->Y();
        fTreeVariableGenRxy[3] = ((TParticle*)fMcEvent->Particle(ltrack3))->R();
        Int_t lblmother = ((TParticle*)fMcEvent->Particle(ltrack3))->GetFirstMother();
        if(lblmother>-1){
            fTreeVariableRecoTrueOmegacccDecVtxGen[0][0] = ((TParticle*)fMcEvent->Particle(ltrack3))->Vx();
            fTreeVariableRecoTrueOmegacccDecVtxGen[0][1] = ((TParticle*)fMcEvent->Particle(ltrack3))->Vy();
            fTreeVariableRecoTrueOmegacccDecVtxGen[0][2] = ((TParticle*)fMcEvent->Particle(ltrack3))->Vz();
            fTreeVariableRecoTrueOmegacccMomGen[0][0] = ((TParticle*)fMcEvent->Particle(lblmother))->Px();
            fTreeVariableRecoTrueOmegacccMomGen[0][1] = ((TParticle*)fMcEvent->Particle(lblmother))->Py();
            fTreeVariableRecoTrueOmegacccMomGen[0][2] = ((TParticle*)fMcEvent->Particle(lblmother))->Pz();
            fTreeVariableGenPt[0] = ((TParticle*)fMcEvent->Particle(lblmother))->Pt();
            fTreeVariableGenEta[0] = ((TParticle*)fMcEvent->Particle(lblmother))->Eta();
            fTreeVariableGenPhi[0] = ((TParticle*)fMcEvent->Particle(lblmother))->Phi();
            fTreeVariableGenRap[0] = ((TParticle*)fMcEvent->Particle(lblmother))->Y();
            fTreeVariableGenRxy[0] = ((TParticle*)fMcEvent->Particle(lblmother))->R();
        }
    }
    //propagation to the primary vertex to get d0
    //propagate track to the primary vertex to compute impact parameter
    Double_t b3[2];
    Double_t bCov3[3];
    AliExternalTrackParam etp3cp;
    etp3cp.CopyFromVTrack(track3);
    etp3cp.PropagateToDCA(fV1,fBzkG,100.,b3,bCov3);
    fTreeVariabled0rphi[3]=b3[0];
    //---> Omegaccc
    Double_t pxomegaccc = pxomegaccprop+pxpi3;
    Double_t pyomegaccc = pyomegaccprop+pypi3;
    Double_t pzomegaccc = pzomegaccprop+pzpi3;
    Double_t pxpypzomegaccc[3]; pxpypzomegaccc[0]=pxomegaccc; pxpypzomegaccc[1]=pyomegaccc; pxpypzomegaccc[2]=pzomegaccc;
    Double_t ptomegaccc = TMath::Sqrt(pxomegaccc*pxomegaccc+pyomegaccc*pyomegaccc);
    Double_t decLXYomegaccc  = DecayLengthXY(fV1, esdVccc);
    Double_t cosPAXYomegaccc = CosPointingAngleXY(fV1, esdVccc, pxpypzomegaccc);
    Double_t decLomegaccc  = DecayLength(fV1, esdVccc);
    Double_t cosPAomegaccc = CosPointingAngle(fV1, esdVccc, pxpypzomegaccc);
    Double_t eomegaccc_ = eomegacc+epi3;
    Double_t pomegaccc_ = TMath::Sqrt(pxomegaccc*pxomegaccc+pyomegaccc*pyomegaccc+pzomegaccc*pzomegaccc);
    Double_t invmass2omegaccc = (eomegacc+epi3)*(eomegacc+epi3)-(pxomegaccc*pxomegaccc+pyomegaccc*pyomegaccc+pzomegaccc*pzomegaccc);
    Double_t invmassomegaccc  = TMath::Sqrt(invmass2omegaccc);
    fTreeVariableInvMass[0] = invmassomegaccc;
    fTreeVariableCosPointingAngle[0] = cosPAomegaccc;
    fTreeVariableCosPointingAngleXY[0] = cosPAXYomegaccc;
    fTreeVariableDecayLength[0] = decLomegaccc;
    fTreeVariableDecayLengthXY[0] = decLXYomegaccc;
    fTreeVariablePt[0] = ptomegaccc;
    fTreeVariableEta[0] = EtaCand(pomegaccc_, pzomegaccc);
    fTreeVariablePhi[0] = PhiCand(pxomegaccc,pyomegaccc);
    fTreeVariableRap[0] = YCand(eomegaccc_, pzomegaccc);
    //propagate Omegaccc to the primary vertex to compute impact parameter
    AliExternalTrackParam *omegacccTrack = GetTrackParamForOmegaccc(esdVccc, esdVcc, esdVcc, casc, track, track2, track3);
    Double_t costThetaStar = CosThetaStar(1,4444,4432,211, pxpypzomegaccc, pxpypzomegaccprop, pxpypzpi3);
    Double_t d0zVertCCC[2],covd0zVertCCC[3];
    omegacccTrack->PropagateToDCA(fV1,fBzkG,100.,d0zVertCCC,covd0zVertCCC);
    fTreeVariableRecoTrueOmegacccMomReco[0][0] = omegacccTrack->Px();
    fTreeVariableRecoTrueOmegacccMomReco[0][1] = omegacccTrack->Py();
    fTreeVariableRecoTrueOmegacccMomReco[0][2] = omegacccTrack->Pz();
    fTreeVariabled0rphi[0] = d0zVertCCC[0];
    
    
    fOmegacccVariables[0] = invmassomegaccc;
    fOmegacccVariables[1] = ptomegaccc;
    fOmegacccVariables[2] = decLomegaccc;
    fOmegacccVariables[3] = decLXYomegaccc;
    fOmegacccVariables[4] = fTreeVariabled0rphi[0];
    fOmegacccVariables[5] = fTreeVariabled0rphi[3];
    fOmegacccVariables[6] = track3->Pt();//TMath::Sqrt(pxpi3*pxpi3 + pypi3*pypi3);
    fOmegacccVariables[7] = costThetaStar;
    fOmegacccVariables[8] = cosPAomegaccc;
    fOmegacccVariables[9] = cosPAXYomegaccc;
    fOmegacccVariables[10] = vtxchi2ndfccc;
    //apply cuts
    bool issel = IsSelectedOmegaccc(fOmegacccVariables);
    fIsSignal = issignal;
    
    if(issel){
        
        if(fIsMCSignalProd && fIsSignal){fTreeTrueOmegaccc->Fill();}
        fTreeCutVar->Fill();
    }
    
    delete cascTrack;    cascTrack=NULL;
    delete omegacTrack;  omegacTrack=NULL;
    delete omegacTrackCp; omegacTrackCp=NULL;
    delete omegaccTrack; omegaccTrack=NULL;
    delete omegaccTrackCp; omegaccTrackCp=NULL;
    delete omegacccTrack;omegacccTrack=NULL;
    return issel;
    
}
//_________________________________________
bool AliAnalysisTaskSEOmegacccToOmega3Pi::IsSelectedOmegaccc(Double_t vars[11]){
    
    bool issel = true;
    
    if(TMath::Abs(vars[0]-TDatabasePDG::Instance()->GetParticle(4444)->Mass())>fOmegacccCuts[0]) return false;
    if(vars[1]<fOmegacccCuts[1]) return false;
    if(vars[2]<fOmegacccCuts[2]) return false;
    if(vars[3]<fOmegacccCuts[3]) return false;
    if(vars[4]<fOmegacccCuts[4]) return false;
    if(vars[5]<fOmegacccCuts[5]) return false;
    if(vars[6]<fOmegacccCuts[6]) return false;
    if(vars[7]<fOmegacccCuts[7]) return false;
    if(vars[8]<fOmegacccCuts[8]) return false;
    if(vars[9]<fOmegacccCuts[9]) return false;
    if(vars[10]>fOmegacccCuts[10]) return false;
    
    return issel;
    
}
//_________________________________________
bool AliAnalysisTaskSEOmegacccToOmega3Pi::IsSelectedOmegacc(Double_t vars[11]){
    
    bool issel = true;
    
    if(TMath::Abs(vars[0]-TDatabasePDG::Instance()->GetParticle(4432)->Mass())>fOmegaccCuts[0]) return false;
    if(vars[1]<fOmegaccCuts[1]) return false;
    if(vars[2]<fOmegaccCuts[2]) return false;
    if(vars[3]<fOmegaccCuts[3]) return false;
    if(vars[4]<fOmegaccCuts[4]) return false;
    if(vars[5]<fOmegaccCuts[5]) return false;
    if(vars[6]<fOmegaccCuts[6]) return false;
    if(vars[7]<fOmegaccCuts[7]) return false;
    if(vars[8]<fOmegaccCuts[8]) return false;
    if(vars[9]<fOmegaccCuts[9]) return false;
    if(vars[10]>fOmegaccCuts[10]) return false;
    
    return issel;
    
}
//_________________________________________
bool AliAnalysisTaskSEOmegacccToOmega3Pi::IsSelectedOmegac(Double_t vars[11]){
    
    bool issel = true;
    
    //Printf("TMath::Abs(vars[0]=%f-TDatabasePDG::Instance()->GetParticle(4332)->Mass()) = %f",vars[0],TMath::Abs(vars[0]-TDatabasePDG::Instance()->GetParticle(4332)->Mass()));
    //for(Int_t i=0; i<8; i++){
    //    Printf("vars[i] = %f < fOmegacCuts[i] = %f",vars[i],fOmegacCuts[i]);
    //}
    
    if(TMath::Abs(vars[0]-TDatabasePDG::Instance()->GetParticle(4332)->Mass())>fOmegacCuts[0]) return false;
    if(vars[1]<fOmegacCuts[1]) return false;
    if(vars[2]<fOmegacCuts[2]) return false;
    if(vars[3]<fOmegacCuts[3]) return false;
    if(vars[4]<fOmegacCuts[4]) return false;
    if(vars[5]<fOmegacCuts[5]) return false;
    if(vars[6]<fOmegacCuts[6]) return false;
    if(vars[7]<fOmegacCuts[7]) return false;
    if(vars[8]<fOmegacCuts[8]) return false;
    if(vars[9]<fOmegacCuts[9]) return false;
    if(vars[10]>fOmegacCuts[10]) return false;
    
    return issel;
    
}
//_________________________________________
AliESDVertex* AliAnalysisTaskSEOmegacccToOmega3Pi::CallReconstructSecondaryVertexOmegac(AliESDcascade *casc, AliESDtrack *track, Double_t &dispersion) {
    //Printf("\n*************************prepare for OMEGA c decay vertex reco");
    
    AliESDVertex *secVertex = 0x0;
    
    TObjArray *trkArray = new TObjArray(2);
    trkArray->AddAt(track,0);
    
    //Printf("CallReconstructSecondaryVertexOmegac --> Before GetTrackParamForCascade");
    AliExternalTrackParam *cascTrack = GetTrackParamForCascade(casc);
    //Printf("CallReconstructSecondaryVertexOmegac --> After GetTrackParamForCascade");
    trkArray->AddAt(cascTrack,1);
    
    //    Printf("---->call reco OMEGA c decay vertex");
    //Printf("CallReconstructSecondaryVertexOmegac --> Before ReconstructSecondaryVertex");
    secVertex = ReconstructSecondaryVertex(trkArray, dispersion);
    //Printf("CallReconstructSecondaryVertexOmegac --> After ReconstructSecondaryVertex");
    //    Printf("*************************end prepare for OMEGA c decay vertex reco");
    //if(secVertex)FillOmegac(casc, cascTrack, track, secVertex, fEvent);
    
    
    trkArray->Clear();
    delete trkArray;  trkArray=NULL;
    delete cascTrack; cascTrack=NULL;
    return secVertex;
    
    
}
//_________________________________________
AliESDVertex* AliAnalysisTaskSEOmegacccToOmega3Pi::CallReconstructSecondaryVertexOmegacc(AliESDVertex *sVtxOmegac, AliESDcascade *casc, AliESDtrack *esdtr, AliESDtrack *esdtr2, Double_t &dispersion){
    //Printf("\n*************************prepare for OMEGA cc decay vertex reco");
    AliESDVertex *secVertex = 0x0;
    
    TObjArray *trkArray = new TObjArray(2);
    trkArray->AddAt(esdtr2,0);
    
    //Printf("CallReconstructSecondaryVertexOmegacc---> Before GetTrackParamForOmegac");
    AliExternalTrackParam *trackOmegac = GetTrackParamForOmegac(sVtxOmegac, casc, esdtr);
    //Printf("CallReconstructSecondaryVertexOmegacc---> After GetTrackParamForOmegac");
    trkArray->AddAt(trackOmegac,1);
    
    //Printf("---->call reco OMEGA cc decay vertex");
    secVertex = ReconstructSecondaryVertex(trkArray, dispersion);
    //Printf("*************************end prepare for OMEGA cc decay vertex reco");
    //if(secVertex)FillOmegacc(casc, cascTrack, track, secVertex, fEvent);
    
    trkArray->Clear();
    delete trkArray;    trkArray=NULL;
    delete trackOmegac; trackOmegac=NULL;
    return secVertex;
    
    
}
//_________________________________________
AliESDVertex* AliAnalysisTaskSEOmegacccToOmega3Pi::CallReconstructSecondaryVertexOmegaccc(AliESDVertex *sVtxOmegacc, AliESDVertex *sVtxOmegac, AliESDcascade *casc, AliESDtrack *esdtr, AliESDtrack *esdtr2, AliESDtrack *esdtr3, Double_t &dispersion){
    //Printf("\n*************************prepare for OMEGA ccc decay vertex reco");
    AliESDVertex *secVertex = 0x0;
    
    TObjArray *trkArray = new TObjArray(2);
    trkArray->AddAt(esdtr3,0);
    
    AliExternalTrackParam *trackOmegacc = GetTrackParamForOmegacc(sVtxOmegacc, sVtxOmegac, casc, esdtr, esdtr2);
    trkArray->AddAt(trackOmegacc,1);
    
    //Printf("---->call reco OMEGA ccc decay vertex");
    secVertex = ReconstructSecondaryVertex(trkArray, dispersion);
    //Printf("*************************end prepare for OMEGA ccc decay vertex reco");
    //if(secVertex)FillOmegacc(casc, cascTrack, track, secVertex, fEvent);
    
    trkArray->Clear();
    delete trkArray;     trkArray=NULL;
    delete trackOmegacc; trackOmegacc=NULL;
    return secVertex;
    
    
}
//____________________________________
AliESDVertex* AliAnalysisTaskSEOmegacccToOmega3Pi::ReconstructSecondaryVertex(TObjArray *trkArray, Double_t &dispersion) {
    
    
    /// Secondary vertex reconstruction with AliVertexerTracks
    //AliDebug(1,"ReconstructSecondaryVertex 0");
    //AliVertexerTracks *fVertexerTracks = new AliVertexerTracks(fBzkG);
    fVertexerTracks->SetFieldkG(fBzkG);
    fVertexerTracks->SetVtxStart(fV1);
    //AliDebug(1,"ReconstructSecondaryVertex 1");
    AliESDVertex *vertexESD = (AliESDVertex*)fVertexerTracks->VertexForSelectedESDTracks(trkArray);
    //AliDebug(1,"ReconstructSecondaryVertex 2");
    
    if(!vertexESD) {AliDebug(1,"no sec vertex reco"); /*delete fVertexerTracks; fVertexerTracks=NULL; */return 0;}
    //vertexESD->Print();
    
    //Printf("ncontr %d  ntracks %d", vertexESD->GetNContributors(),trkArray->GetEntriesFast());
    if(vertexESD->GetNContributors()!=trkArray->GetEntriesFast()) {
        //AliDebug(2,"vertexing failed");
        //delete vertexESD; vertexESD=NULL; delete fVertexerTracks; fVertexerTracks=NULL;
        return 0;
    }
    
    Double_t vertRadius2=vertexESD->GetX()*vertexESD->GetX()+vertexESD->GetY()*vertexESD->GetY();
    //Printf("vertRadius2 %f", vertRadius2);
    if(vertRadius2>8.){
        // vertex outside beam pipe, reject candidate to avoid propagation through material
        //delete vertexESD; vertexESD=NULL; delete fVertexerTracks; fVertexerTracks=NULL;
        return 0;
    }
    
    //delete fVertexerTracks; fVertexerTracks=NULL;
    
    // convert to AliAODVertex
    Double_t pos[3],cov[6],chi2perNDF;
    vertexESD->GetXYZ(pos); // position
    vertexESD->GetCovMatrix(cov); //covariance matrix
    chi2perNDF = vertexESD->GetChi2toNDF();
    dispersion = vertexESD->GetDispersion();
    
    return vertexESD;
    
    
}
//____________________________________
AliExternalTrackParam* AliAnalysisTaskSEOmegacccToOmega3Pi::GetTrackParamForOmegaccc(AliESDVertex *sVtxOmegaccc, AliESDVertex *sVtxOmegacc, AliESDVertex *sVtxOmegac, AliESDcascade *casc, AliESDtrack *esdtr, AliESDtrack *esdtr2, AliESDtrack *esdtr3){
    
    //Omegacc trackParam
    AliExternalTrackParam *omegaccTrack = GetTrackParamForOmegacc(sVtxOmegacc, sVtxOmegac, casc, esdtr, esdtr2);
    //propagate Omegac to Omegacc vertex
    Double_t d0zomegacc[2],covd0zomegacc[3];
    omegaccTrack->PropagateToDCA(sVtxOmegaccc,fBzkG,100.,d0zomegacc,covd0zomegacc);
    Double_t covTrOmegacc[21];
    omegaccTrack->GetCovarianceXYZPxPyPz(covTrOmegacc);
    Double_t pxomegacc = omegaccTrack->Px();
    Double_t pyomegacc = omegaccTrack->Py();
    Double_t pzomegacc = omegaccTrack->Pz();
    
    Double_t d0zbach[2],covd0zbach[3];
    AliExternalTrackParam etp;
    etp.CopyFromVTrack(esdtr3);
    etp.PropagateToDCA(sVtxOmegaccc,fBzkG,100.,d0zbach,covd0zbach);
    Double_t covTrBachOmegaccc[21];
    etp.GetCovarianceXYZPxPyPz(covTrBachOmegaccc);
    Double_t pxtr = etp.Px();
    Double_t pytr = etp.Py();
    Double_t pztr = etp.Pz();
    
    Double_t covTrOmegaccc[21];
    for(Int_t i=0; i<21; i++){
        covTrOmegaccc[i] = covTrOmegacc[i] + covTrBachOmegaccc[i];
    }
    Double_t xyz[3], pxpypz[3];
    xyz[0] = sVtxOmegaccc->GetX();
    xyz[1] = sVtxOmegaccc->GetY();
    xyz[2] = sVtxOmegaccc->GetZ();
    pxpypz[0] = pxomegacc + pxtr;
    pxpypz[1] = pyomegacc + pytr;
    pxpypz[2] = pzomegacc + pztr;
    Short_t charge = esdtr3->Charge();
    AliExternalTrackParam *omegacccTrack = new AliExternalTrackParam(xyz,pxpypz,covTrOmegaccc,charge);
    delete omegaccTrack; omegaccTrack=NULL;
    if(omegacccTrack) return omegacccTrack;
    else { delete omegacccTrack; omegacccTrack=NULL; return 0x0;}
    
}
//____________________________________
AliExternalTrackParam* AliAnalysisTaskSEOmegacccToOmega3Pi::GetTrackParamForOmegacc(AliESDVertex *sVtxOmegacc, AliESDVertex *sVtxOmegac, AliESDcascade *casc, AliESDtrack *esdtr, AliESDtrack *esdtr2){
    
    //Omegac trackParam
    AliExternalTrackParam *omegacTrack = GetTrackParamForOmegac(sVtxOmegac, casc, esdtr);
    //propagate Omegac to Omegacc vertex
    Double_t d0zomegac[2],covd0zomegac[3];
    omegacTrack->PropagateToDCA(sVtxOmegacc,0,100.,d0zomegac,covd0zomegac);
    Double_t covTrOmegac[21];
    omegacTrack->GetCovarianceXYZPxPyPz(covTrOmegac);
    Double_t pxomegac = omegacTrack->Px();
    Double_t pyomegac = omegacTrack->Py();
    Double_t pzomegac = omegacTrack->Pz();
    
    Double_t d0zbach[2],covd0zbach[3];
    AliExternalTrackParam etp;
    etp.CopyFromVTrack(esdtr2);
    etp.PropagateToDCA(sVtxOmegacc,fBzkG,100.,d0zbach,covd0zbach);
    Double_t covTrBachOmegacc[21];
    etp.GetCovarianceXYZPxPyPz(covTrBachOmegacc);
    Double_t pxtr = etp.Px();
    Double_t pytr = etp.Py();
    Double_t pztr = etp.Pz();
    
    Double_t covTrOmegacc[21];
    for(Int_t i=0; i<21; i++){
        covTrOmegacc[i] = covTrOmegac[i] + covTrBachOmegacc[i];
    }
    Double_t xyz[3], pxpypz[3];
    xyz[0] = sVtxOmegacc->GetX();
    xyz[1] = sVtxOmegacc->GetY();
    xyz[2] = sVtxOmegacc->GetZ();
    pxpypz[0] = pxomegac + pxtr;
    pxpypz[1] = pyomegac + pytr;
    pxpypz[2] = pzomegac + pztr;
    Short_t charge = esdtr2->Charge();
    AliExternalTrackParam *omegaccTrack = new AliExternalTrackParam(xyz,pxpypz,covTrOmegacc,charge);
    delete omegacTrack; omegacTrack=NULL;
    if(omegaccTrack) return omegaccTrack;
    else { delete omegaccTrack; omegaccTrack=NULL; return 0x0;}
    
}
//____________________________________
AliExternalTrackParam* AliAnalysisTaskSEOmegacccToOmega3Pi::GetTrackParamForOmegac(AliESDVertex *sVtxOmegac, AliESDcascade *casc, AliESDtrack *esdtr){
    
    //propagate cascade to the Omegac decay vertex
    AliExternalTrackParam *cascTrack = GetTrackParamForCascade(casc);
    Double_t d0zcasc[2],covd0zcasc[3];
    cascTrack->PropagateToDCA(sVtxOmegac,fBzkG,100.,d0zcasc,covd0zcasc);
    Double_t covTrCascade[21];
    cascTrack->GetCovarianceXYZPxPyPz(covTrCascade);
    Double_t pxcasc = cascTrack->Px();
    Double_t pycasc = cascTrack->Py();
    Double_t pzcasc = cascTrack->Pz();
    
    Double_t d0zbach[2],covd0zbach[3];
    AliExternalTrackParam etp;
    etp.CopyFromVTrack(esdtr);
    etp.PropagateToDCA(sVtxOmegac,fBzkG,100.,d0zbach,covd0zbach);
    Double_t covTrBachOmegac[21];
    etp.GetCovarianceXYZPxPyPz(covTrBachOmegac);
    Double_t pxtr = etp.Px();
    Double_t pytr = etp.Py();
    Double_t pztr = etp.Pz();
    
    Double_t covTrOmegac[21];
    for(Int_t i=0; i<21; i++){
        covTrOmegac[i] = covTrCascade[i] + covTrBachOmegac[i];
    }
    Double_t xyz[3], pxpypz[3];
    xyz[0] = sVtxOmegac->GetX();
    xyz[1] = sVtxOmegac->GetY();
    xyz[2] = sVtxOmegac->GetZ();
    pxpypz[0] = pxcasc + pxtr;
    pxpypz[1] = pycasc + pytr;
    pxpypz[2] = pzcasc + pztr;
    AliExternalTrackParam *omegacTrack = new AliExternalTrackParam(xyz,pxpypz,covTrOmegac,1);
    delete cascTrack; cascTrack=NULL;
    if(omegacTrack) return omegacTrack;
    else { delete omegacTrack; omegacTrack=NULL; return 0x0;}
    
}
//____________________________________
AliExternalTrackParam* AliAnalysisTaskSEOmegacccToOmega3Pi::GetTrackParamForCascade(AliESDcascade *casc){
    
    
    
    // cascade vertex and momentum
    Double_t xyz[3], pxpypz[3];
    casc->XvYvZv(xyz);
    casc->PxPyPz(pxpypz);
    Double_t cov[6]; //for(int j=0; j<6; j++) cov[j]=0;
    casc->GetPosCovXi(cov);
    AliESDVertex *vertexcasc = new AliESDVertex(xyz,cov,casc->GetChi2Xi(),0,"VertexCasc");
    //cascade daughters
    Int_t  idxPosFromV0Dghter  = casc->GetPindex();
    Int_t  idxNegFromV0Dghter  = casc->GetNindex();
    Int_t  idxBachFromCascade  = casc->GetBindex();
    
    //get V0 from cascade
    AliESDv0 * currentV0   = 0x0;
    Int_t idxV0FromCascade = -1;
    for(int iv0=0; iv0<fEvent->GetNumberOfV0s(); iv0++){
        currentV0 = fEvent->GetV0(iv0);
        Int_t posCurrentV0 = currentV0->GetPindex();
        Int_t negCurrentV0 = currentV0->GetNindex();
        if (posCurrentV0==idxPosFromV0Dghter && negCurrentV0==idxNegFromV0Dghter) {
            idxV0FromCascade = iv0;
            break;
        }
    }
    if(idxV0FromCascade < 0){
        printf("Cascade - no matching for the V0 (index V0 = -1) ! Skip ... \n");
        return 0x0;
    }
    AliESDv0 *esdV0FromCascade = fEvent->GetV0(idxV0FromCascade);
    Double_t xyzv0[3], pxpypzv0[3];
    esdV0FromCascade->XvYvZv(xyzv0);
    esdV0FromCascade->PxPyPz(pxpypzv0);
    //AliExternalTrackParam *esdCascadePos = (AliExternalTrackParam*)esdV0FromCascade->GetParamP();
    Double_t covTrPos[21];
    //esdCascadePos->GetCovarianceXYZPxPyPz(covTrPos);
    (esdV0FromCascade->GetParamP())->GetCovarianceXYZPxPyPz(covTrPos);
    //AliExternalTrackParam *esdCascadeNeg = (AliExternalTrackParam*)esdV0FromCascade->GetParamN();
    Double_t covTrNeg[21];
    //esdCascadeNeg->GetCovarianceXYZPxPyPz(covTrNeg);
    (esdV0FromCascade->GetParamN())->GetCovarianceXYZPxPyPz(covTrNeg);
    //cov V0
    Double_t covV0[21];
    Double_t covV0prop[21];
    for(int i=0; i<21; i++){
        covV0[i]=covTrPos[i]+covTrNeg[i];
        covV0prop[i]=0;
        //Printf("cotrp =%f, cotrn = %f",covTrPos[i],covTrNeg[i]);
    }
    //Printf("xyz = %f %f %f \t pxpypz = %f %f %f",xyzv0[0],xyzv0[1],xyzv0[2],pxpypzv0[0],pxpypzv0[1],pxpypzv0[2]);
    AliExternalTrackParam *v0track=new AliExternalTrackParam(xyzv0,pxpypzv0,covV0,1);
    //AliNeutralTrackParam *v0track=new AliExternalTrackParam(xyzv0,pxpypzv0,covV0,0);
    //Double_t covv0[21];
    //v0track->GetCovarianceXYZPxPyPz(covv0);
    //for(int kk=0; kk<21; kk++) Printf("cov matrix v0track->GetCovarianceXYZPxPyPz=%f",covv0[kk]);
    Double_t d0zV0[2],covd0zV0[3];
    //vertexcasc->Print();
    v0track->PropagateToDCA(vertexcasc,0.,100.,d0zV0,covd0zV0);
    /*Double_t covyz[2],covxyz[3];
     covxyz[0]=cov[0];
     covxyz[1]=cov[1]; covyz[0]=cov[2];
     covxyz[2]=cov[3]; covyz[1]=cov[4]; covyz[2]=cov[5];
     v0track->PropagateTo(xyz,covyz,covxyz,fBzkG);*/
    v0track->GetCovarianceXYZPxPyPz(covV0prop);
    //cascade bachelor
    //vertexcasc->Print();
    AliESDtrack  *esdCascadeBach = fEvent->GetTrack( idxBachFromCascade);
    Double_t d0zbach[2],covd0zbach[3];
    esdCascadeBach->PropagateToDCA(vertexcasc,fBzkG,100.,d0zbach,covd0zbach);
    Double_t covTrBach[21];
    esdCascadeBach->GetCovarianceXYZPxPyPz(covTrBach);
    // cascade covariance matrix
    Double_t cv[21]; for(int i=0; i<21; i++) cv[i]=0;
    for(int k=0; k<21; k++) {
        //if(k<6) cv[k]=cov[k];
        //else cv[k]=covTrPos[k]+covTrNeg[k]+covTrBach[k];
        cv[k]=covTrBach[k]+covV0prop[k];
        //Printf("cov matrix negV0=%.10f posV0=%.10f V0=%.10f V0prop=%.10f bachelor=%.10f  cascade=%.10f",covTrNeg[k],covTrPos[k],covV0[k],covV0prop[k],covTrBach[k],cv[k]);
    }
    Short_t sign=casc->Charge();
    AliExternalTrackParam *cascTrack = new AliExternalTrackParam(xyz,pxpypz,cv,sign);
    
    delete vertexcasc; vertexcasc=NULL;
    delete v0track; v0track=NULL;
    if(cascTrack) {/*Printf("return casc track");*/ return cascTrack;}
    else { delete cascTrack; cascTrack=NULL; Printf("return casc track=0x0"); return 0x0;}
    
}
//________________________________________________________________________
TString AliAnalysisTaskSEOmegacccToOmega3Pi::GetGenerator(Int_t label, AliGenCocktailEventHeader* header){
    
    Int_t nsumpart=0;
    TList *lh = header->GetHeaders();
    Int_t nh = lh->GetEntries();
    for(Int_t i=0; i<nh; i++){
        AliGenEventHeader *gh = (AliGenEventHeader*)lh->At(i);
        TString genname = gh->GetName();
        Int_t npart = gh->NProduced();
        if(label>=nsumpart && label<(nsumpart+npart)) return genname;
        nsumpart+=npart;
    }
    TString empty="";
    return empty;
    
}
//________________________________________________________________________
void AliAnalysisTaskSEOmegacccToOmega3Pi::RecoEvent(){
    
    
    
    
    int npart = fMcEvent->GetNumberOfTracks();//fStack->GetNprimary();
    const AliVVertex *vtxMC = fMcEvent->GetPrimaryVertex();
    Double_t covmatrix[6]={0.,0.,0.,0.,0.,0.};
    Double_t positiongen[3]={0.,0.,0.};
    //vtxMC->GetSigmaXYZ(sigmagen);
    vtxMC->GetXYZ(positiongen);
    
    
    TParticle *part = 0x0;
    AliESDtrack* esdTr = 0x0;
    fNHitsAssigned.clear();
    fParticlePdg.clear();
    fMotherPdg.clear();
    
    // loop on particles
    Printf("N PARTICLES %d",npart);
    for(int i=0; i<npart; i++){
        
        Int_t pdgPart=-1;
        Int_t lblMoth=-1;
        Int_t pdgMoth=-1;
        Float_t ptPart=0.;
        Float_t pPart=0.;
        Float_t etaPart=0.;
        Float_t rapPart=0.;
        Float_t phiPart=0.;
        Float_t xPart=0.;
        Float_t yPart=0.;
        Float_t zPart=0.;
        Float_t rxyPart=0.;
        Int_t nhistassigned=-1;
        Int_t nhistreco=-1;
        bool isReco=false;
        
        
        //Printf("______");
        part = (TParticle*)fMcEvent->Particle(i);//fStack->Particle(i);
        if(!part) {Printf("no part"); continue;}
        fNentries->Fill(1);
        pdgPart = part->GetPdgCode();
        lblMoth = part->GetFirstMother();
        if(lblMoth>-1)pdgMoth = ((TParticle*)fMcEvent->Particle(lblMoth))->GetPdgCode();
        ptPart=part->Pt();
        pPart=part->P();
        etaPart=part->Eta();
        rapPart=part->Y();
        phiPart=part->Phi();
        xPart=part->Vx();
        yPart=part->Vy();
        zPart=part->Vz();
        rxyPart=part->R();
        //Printf("HERE i=%10d pdg=%5d lblmoth=%10d pt=%.5f, eta=%.5f, phi=%.5f, x=%.5f y=%.5f z=%.5f, rxy=%.5f",i,pdgPart, lblMoth, ptPart, etaPart, phiPart, xPart, yPart, zPart, rxyPart);
        Bool_t res = kFALSE;
        if(ptPart>0.){
            res = fITS->ProcessTrack(part);
            //Printf("after processTrack i=%d  res=%d",i,res);
            nhistassigned = fITS->GetNHitsAssigned();
        }
        fNHitsAssigned.push_back(nhistassigned);
        fParticlePdg.push_back(pdgPart);
        fMotherPdg.push_back(lblMoth);
        //Printf("RECO EVENT: index %d | particle %d particleName=%s | mother %d | n reco hits %d",i,fParticlePdg.at(i),part->GetName(),fMotherPdg.at(i),fNHitsAssigned.at(i));
        /*
        Bool_t isPhysPrimary = fMcEvent->IsPhysicalPrimary(i);
        if(!isPhysPrimary) {Printf("i=%d PDG=%d %s no phys prim",i,part->GetPdgCode(),part->GetName()); continue;}
        if(part->GetStatusCode()<=0) {Printf("i=%d PDG=%d %s status code <0",i,part->GetPdgCode(),part->GetName());  continue;}
        fNentries->Fill(2);
        Int_t motherIndex=part->GetFirstMother();
        if(motherIndex==-1) {Printf("i=%d motherIndex==-1 PDG=%d %s",i,part->GetPdgCode(),part->GetName());  continue;}
        fNentries->Fill(3);
        int charge = TDatabasePDG::Instance()->GetParticle(part->GetPdgCode())->Charge()/3;
        if(charge==0) {Printf("i=%d charge=0 PDG=%d %s",i,part->GetPdgCode(),part->GetName());  continue;}
        fNentries->Fill(4);
        Float_t thisEta = part->Eta();
        //if(TMath::Abs(thisEta) > fEtaCut) continue; //fEtaCut
        fNentries->Fill(5);
        */
        Bool_t isPhysPrimary = fMcEvent->IsPhysicalPrimary(i);
        Int_t statusCode = part->GetStatusCode();
        if(isPhysPrimary && statusCode>0) {
            fNentries->Fill(2);
            if(lblMoth>-1) {
                fNentries->Fill(3);
                if( (TDatabasePDG::Instance()->GetParticle(part->GetPdgCode())->Charge()/3)!=0 ) {
                    fNentries->Fill(4);
                    if(TMath::Abs(part->Eta())<2.){
                        fNentries->Fill(5);
                    }
                }
            }
        }
        if(!isPhysPrimary) continue;
        if(statusCode<=0) continue;
        if(lblMoth==-1) continue;
        if(TDatabasePDG::Instance()->GetParticle(part->GetPdgCode())->Charge()/3==0 ) continue;
        // fast track reco
        //Printf("i track = %d part = %s eta=%f motherindex =%d",i,part->GetName(),thisEta,motherIndex);
        //Bool_t res = fITS->ProcessTrack(part);
        if(res){
            isReco=true;
            esdTr = (AliESDtrack*)fITS->GetProbeTrackInwardAsESDTrack();
            esdTr->SetStatus(AliESDtrack::kTPCin|AliESDtrack::kTPCout|AliESDtrack::kTPCrefit|AliESDtrack::kITSrefit);
            esdTr->SetTRDntracklets((UChar_t)nhistassigned);
            esdTr->SetLabel(i);
            fEvent->AddTrack(esdTr);
            const TBits &hits = esdTr->GetTPCClusterMap();
            Int_t nhits=0;
            for (int ilr=0;ilr<fITS->GetNActiveLayers();ilr++) {
                //printf("%c", hits.TestBitNumber(ilr) ? '+':'-');
                if(hits.TestBitNumber(ilr))nhits++;
            }
            nhistreco=nhits;
            //Printf("nhits reco %d", nhits);
        }
        else {
            fNentries->Fill(7);/* continue;*/
            isReco=false;
        }
        fParticleVarPdg = pdgPart;
        fParticleVarPdgMoth = pdgMoth;
        fParticleVarPt = ptPart;
        fParticleVarP = pPart;
        fParticleVarEta = etaPart;
        fParticleVarRap = rapPart;
        fParticleVarPhi = phiPart;
        fParticleVarX = xPart;
        fParticleVarY = yPart;
        fParticleVarZ = zPart;
        fParticleVarRxy = rxyPart;
        fParticleVarNhitsAssigned = nhistassigned;
        fParticleVarNhitsReco = nhistreco;
        fParticleVarIsReco = isReco;
        //Printf("FILL Tree REconstruction: index=%d res=%d | %d %d | %f %f %f %f %f %f %f %f %f | %d %d %d",i,res,fParticleVarPdg,fParticleVarPdgMoth,fParticleVarPt,fParticleVarP,fParticleVarEta,fParticleVarRap,fParticleVarPhi,fParticleVarX,fParticleVarY,fParticleVarZ,fParticleVarRxy,fParticleVarNhitsAssigned,fParticleVarNhitsReco,fParticleVarIsReco);
        fTreeReconstruction->Fill();
//        esdTr = (AliESDtrack*)fITS->GetProbeTrackInwardAsESDTrack();
//        esdTr->SetStatus(AliESDtrack::kTPCin|AliESDtrack::kTPCout|AliESDtrack::kTPCrefit|AliESDtrack::kITSrefit);
//        esdTr->SetTRDntracklets((UChar_t)nhistassigned);
//        esdTr->SetLabel(i);
//        fEvent->AddTrack(esdTr);
        
        
        
    }// end loop over particles
    //AliESDUtils::RefitESDVertexTracks(esd);
    double posVtx[3]={0,0,0};
    double sigmaVtx[3]={0,0,0};
    double covMatrix[6]={sigmaVtx[0]*sigmaVtx[0],0.,sigmaVtx[1]*sigmaVtx[1],0.,0.,sigmaVtx[2]*sigmaVtx[2]};
    //AliESDVertex *myVtx = new AliESDVertex(posVtx,sigmaVtx,"Vertex");
    AliESDVertex myVtx(posVtx,sigmaVtx,"Vertex");
    fEvent->SetPrimaryVertexTracks(&myVtx);
    
    
    //delete esdVtx;
    //delete myVtx;
    
    
}
//________________________________________________________________________
void AliAnalysisTaskSEOmegacccToOmega3Pi::FillGenTree(){
    
    
    Int_t thisPdgCode = 0;
    Int_t thisPdgCodeAbs = 0;
    Float_t thisEta = 0.;
    Float_t thisPt = 0.;
    Float_t thisy = 0.;
    Float_t thisPhi = 0.;
    Float_t thisRxy = 0.;
    Bool_t isPhysPrimary = kFALSE;
    Int_t npion_fromL=0, np_fromL=0, nL=0, nO=0, nL_fromO=0, nK_fromO=0, nD=0, nB=0;
    Int_t nb_py = 0, nc_py=0;
    Int_t nb_hij = 0, nc_hij=0;
    
    int npart = fMcEvent->GetNumberOfTracks();
    
    TParticle *part=0x0;
    // loop on particles
    for(int i=0; i<npart; i++){
        part = (TParticle*)fMcEvent->Particle(i);
        if(!part) {continue;}
        
        thisPdgCode = part->GetPdgCode();
        thisPdgCodeAbs = TMath::Abs(thisPdgCode);
        thisEta     = part->Eta();
        thisPt      = part->Pt();
        thisy       = part->Y();
        thisPhi       = part->Phi();
        isPhysPrimary = fMcEvent->IsPhysicalPrimary(i);
        thisRxy = part->R();
        //
        if(thisPdgCodeAbs==4) {
            Int_t mlab = part->GetFirstMother();
            if(mlab==-1){
                TString genname=GetGenerator(i,(AliGenCocktailEventHeader*)fMcEvent->GenEventHeader());
                //Printf("%d %s %d %s", i, genname.Data(), mlab, part->GetName());
                if(genname.Contains("Hijing"))nc_hij++;
                if(genname.Contains("PYTHIA"))nc_py++;
            }
        }
        if(thisPdgCodeAbs==5) {
            Int_t mlab = part->GetFirstMother();
            if(mlab==-1){
                TString genname=GetGenerator(i,(AliGenCocktailEventHeader*)fMcEvent->GenEventHeader());
                //Printf("%d %s %d %s", i, genname.Data(), mlab, part->GetName());
                if(genname.Contains("Hijing"))nb_hij++;
                if(genname.Contains("PYTHIA"))nb_py++;
            }
        }
        //omegacc and pi1
        Int_t dau[2] = {-1, -1};
        TParticle *daup[2];
        //        Float_t eta_dau[2] = {-100.,-100.};
        //        Float_t pt_dau[2] = {-100.,-100.};
        //        Float_t y_dau[2] = {-100.,-100.};
        //        Float_t phi_dau[2] = {-100.,-100.};
        //omegac and pi2
        Int_t dau1[2] = {-1, -1};
        TParticle *daup1[2];
        //        Float_t eta_dau1[2] = {-100.,-100.};
        //        Float_t pt_dau1[2] = {-100.,-100.};
        //        Float_t y_dau1[2] = {-100.,-100.};
        //        Float_t phi_dau1[2] = {-100.,-100.};
        //omega and pi3
        Int_t dau2[2] = {-1, -1};
        TParticle *daup2[2];
        //        Float_t eta_dau2[2] = {-100.,-100.};
        //        Float_t pt_dau2[2] = {-100.,-100.};
        //        Float_t y_dau2[2] = {-100.,-100.};
        //        Float_t phi_dau2[2] = {-100.,-100.};
        //Lambda and kaon
        Int_t dau3[2] = {-1, -1};
        TParticle *daup3[2];
        //        Float_t eta_dau3[2] = {-100.,-100.};
        //        Float_t pt_dau3[2] = {-100.,-100.};
        //        Float_t y_dau3[2] = {-100.,-100.};
        //        Float_t phi_dau3[2] = {-100.,-100.};
        //proton and pion
        Int_t dau4[2] = {-1, -1};
        TParticle *daup4[2];
        //        Float_t eta_dau4[2] = {-100.,-100.};
        //        Float_t pt_dau4[2] = {-100.,-100.};
        //        Float_t y_dau4[2] = {-100.,-100.};
        //        Float_t phi_dau4[2] = {-100.,-100.};
        //
        Float_t partVars[11][5]={
            -100.,-100.,-100.,-100.,-100., //Omegaccc
            -100.,-100.,-100.,-100.,-100., //Omegacc
            -100.,-100.,-100.,-100.,-100., //Pi1
            -100.,-100.,-100.,-100.,-100., //Omegac
            -100.,-100.,-100.,-100.,-100., //Pi2
            -100.,-100.,-100.,-100.,-100., //Omega
            -100.,-100.,-100.,-100.,-100., //Pi3
            -100.,-100.,-100.,-100.,-100., //Lambda
            -100.,-100.,-100.,-100.,-100., //Kaon
            -100.,-100.,-100.,-100.,-100., //proton
            -100.,-100.,-100.,-100.,-100.  //Pi4
        };
        Int_t pdgpart[11]={0,0,0,0,0,0,0,0,0,0,0};
        Int_t pdgpartOmegaccc[11]={4444,4432,211,4332,211,3334,211,3122,321,2212,211};
        //Omegaccc: check all daughters in acceptance
        if(thisPdgCodeAbs==4444){
            partVars[0][0] = thisEta;
            partVars[0][1] = thisPt;
            partVars[0][2] = thisy;
            partVars[0][3] = thisPhi;
            partVars[0][4] = thisRxy;
            pdgpart[0] = thisPdgCodeAbs;
            //omegaccc level
            dau[0] = part->GetDaughter(0); //omegacc
            dau[1] = part->GetDaughter(1); //pion
            if(dau[0]>-1 && dau[1]>-1){
                daup[0] = (TParticle*)fMcEvent->Particle(dau[0]); //omegacc
                daup[1] = (TParticle*)fMcEvent->Particle(dau[1]); //pion
                for(Int_t i=0; i<2; i++){
                    partVars[i+1][0] = daup[i]->Eta();
                    partVars[i+1][1] = daup[i]->Pt();
                    partVars[i+1][2] = daup[i]->Y();
                    partVars[i+1][3] = daup[i]->Phi();
                    partVars[i+1][4] = daup[i]->R();
                    pdgpart[i+1] = TMath::Abs(daup[i]->GetPdgCode());
                    //                    eta_dau[i] = daup[i]->Eta();
                    //                    pt_dau[i]  = daup[i]->Pt();
                    //                    y_dau[i]   = daup[i]->Y();
                    //                    phi_dau[i]   = daup[i]->Phi();
                }
                dau1[0] = daup[0]->GetDaughter(0); //omegac
                dau1[1] = daup[0]->GetDaughter(1); //pion
                if(dau1[0]>0 && dau1[1]>0){
                    daup1[0] = (TParticle*)fMcEvent->Particle(dau1[0]); //omegac
                    daup1[1] = (TParticle*)fMcEvent->Particle(dau1[1]); //pion
                    for(Int_t i=0; i<2; i++){
                        partVars[i+3][0] = daup1[i]->Eta();
                        partVars[i+3][1] = daup1[i]->Pt();
                        partVars[i+3][2] = daup1[i]->Y();
                        partVars[i+3][3] = daup1[i]->Phi();
                        partVars[i+3][4] = daup1[i]->R();
                        pdgpart[i+3] = TMath::Abs(daup1[i]->GetPdgCode());
                        //                        eta_dau1[i] = daup1[i]->Eta();
                        //                        pt_dau1[i]  = daup1[i]->Pt();
                        //                        y_dau1[i]   = daup1[i]->Y();
                        //                        phi_dau1[i]   = daup1[i]->Phi();
                    }
                    dau2[0] = daup1[0]->GetDaughter(0); //omega
                    dau2[1] = daup1[0]->GetDaughter(1); //pion
                    if(dau2[0]>0 && dau2[1]>0){
                        daup2[0] = (TParticle*)fMcEvent->Particle(dau2[0]); //omega
                        daup2[1] = (TParticle*)fMcEvent->Particle(dau2[1]); //pion
                        for(Int_t i=0; i<2; i++){
                            partVars[i+5][0] = daup2[i]->Eta();
                            partVars[i+5][1] = daup2[i]->Pt();
                            partVars[i+5][2] = daup2[i]->Y();
                            partVars[i+5][3] = daup2[i]->Phi();
                            partVars[i+5][4] = daup2[i]->R();
                            pdgpart[i+5] = TMath::Abs(daup2[i]->GetPdgCode());
                            //                            eta_dau2[i] = daup2[i]->Eta();
                            //                            pt_dau2[i]  = daup2[i]->Pt();
                            //                            y_dau2[i]   = daup2[i]->Y();
                            //                            phi_dau2[i]   = daup2[i]->Phi();
                        }
                        dau3[0] = daup2[0]->GetDaughter(0); //Lambda
                        dau3[1] = daup2[0]->GetDaughter(1); //kaon
                        if(dau3[0]>0 && dau3[1]>0){
                            daup3[0] = (TParticle*)fMcEvent->Particle(dau3[0]); //Lambda
                            daup3[1] = (TParticle*)fMcEvent->Particle(dau3[1]); //kaon
                            for(Int_t i=0; i<2; i++){
                                partVars[i+7][0] = daup3[i]->Eta();
                                partVars[i+7][1] = daup3[i]->Pt();
                                partVars[i+7][2] = daup3[i]->Y();
                                partVars[i+7][3] = daup3[i]->Phi();
                                partVars[i+7][4] = daup3[i]->R();
                                pdgpart[i+7] = TMath::Abs(daup3[i]->GetPdgCode());
                                //                                eta_dau3[i] = daup3[i]->Eta();
                                //                                pt_dau3[i]  = daup3[i]->Pt();
                                //                                y_dau3[i]   = daup3[i]->Y();
                                //                                phi_dau3[i]   = daup3[i]->Phi();
                            }
                            dau4[0] = daup3[0]->GetDaughter(0); //proton
                            dau4[1] = daup3[0]->GetDaughter(1); //pion
                            if(dau4[0]>0 && dau4[1]>0){
                                daup4[0] = (TParticle*)fMcEvent->Particle(dau4[0]); //proton
                                daup4[1] = (TParticle*)fMcEvent->Particle(dau4[1]); //pion
                                for(Int_t i=0; i<2; i++){
                                    partVars[i+9][0] = daup4[i]->Eta();
                                    partVars[i+9][1] = daup4[i]->Pt();
                                    partVars[i+9][2] = daup4[i]->Y();
                                    partVars[i+9][3] = daup4[i]->Phi();
                                    partVars[i+9][4] = daup4[i]->R();
                                    pdgpart[i+9] = TMath::Abs(daup4[i]->GetPdgCode());
                                    //                                    eta_dau4[i] = daup4[i]->Eta();
                                    //                                    pt_dau4[i]  = daup4[i]->Pt();
                                    //                                    y_dau4[i]   = daup4[i]->Y();
                                    //                                    phi_dau4[i]   = daup4[i]->Phi();
                                }
                                //set values tree gen variables
                                for(int j=0; j<11; j++){
                                    fTreeGenVarOmegacccNRHits[j] = fNHitsAssigned.at(i+j);
                                    fTreeGenVarOmegacccPDG[j]    = fParticlePdg.at(i+j);
                                    //Printf("FILL GEN TREE: index %d | particle %d | mother %d | n reco hits %d",i+j,fParticlePdg.at(i+j),fMotherPdg.at(i+j),fNHitsAssigned.at(i+j));
                                    for(int ii=0; ii<5; ii++){
                                        fTreeGenVarOmegaccc[j][ii] = partVars[j][ii];
                                    }
                                    
                                }
                                if(fIsMCSignalProd){
                                    bool isdecay = true;
                                    for(int ii=0; ii<11; ii++){
                                        //Printf("i=%d",i);
                                        //Printf("IsDecay = %d", isdecay);
                                        isdecay = isdecay && (pdgpart[ii]==pdgpartOmegaccc[ii]);
                                        //Printf("IsDecay = %d | %d ?= %d",isdecay,pdgpart[ii],pdgpartOmegaccc[ii]);
                                        //Printf("____________");
                                    }
                                    if(isdecay)
                                        fTreeGenOmegaccc->Fill();
                                }
                            }
                        }
                    }
                }
            }
        }
        fHistoNbVsNcPYTHIA->Fill(nc_py,nb_py);
        fHistoNbVsNcHIJING->Fill(nc_hij,nb_hij);
        
        
    }
}
//________________________________________________________________________
void AliAnalysisTaskSEOmegacccToOmega3Pi::FillRecoTrackTree(){
    
    int ntr = fEvent->GetNumberOfTracks();
    //printf("Event %d: ntr = %d\n",iev,ntr);
    //printf("Generated vertex: %+e %+e %+e\n",vx,vy,vz);
    //const AliESDVertex *vtxT3D=fEvent->GetPrimaryVertexTracks();
    //vtxT3D->Print();
    AliESDtrack* esdtr=0x0;
    TParticle *mcPart=0x0;
    for (int itr=0;itr<ntr;itr++) {
        fNentries->Fill(6);
        esdtr = fEvent->GetTrack(itr);
        Float_t recoPt=esdtr->Pt();
        Float_t recoEta=esdtr->Eta();
        Float_t recoY=esdtr->Y();
        Float_t recoPhi=esdtr->Phi();
        Int_t recoHits = (Int_t)esdtr->GetTRDNclusterdEdx();
        Int_t lbl=esdtr->GetLabel();
        
        
        //corresponding generated particle
        mcPart=fMcEvent->Particle(lbl);
        Float_t genPt=mcPart->Pt();
        Float_t genEta=mcPart->Eta();
        Float_t genY=mcPart->Y();
        Float_t genRad=mcPart->R();
        Float_t genPtMoth=-1.;
        int pdgCodePart=mcPart->GetPdgCode();
        int lblMother = mcPart->GetFirstMother();
        int pdgCodeMother = -99999;
        if(lblMother>-1) {
            pdgCodeMother = (fMcEvent->Particle(lblMother))->GetPdgCode();
            genPtMoth = (fMcEvent->Particle(lblMother))->Pt();
        }
        //Printf("FILL RECO TREE: track %d , Nreconstructable %d | MC label %d , NReconstructable MC %d, particlePDG %d",itr,recoHits,lbl,fNHitsAssigned.at(lbl),pdgCodePart);
        
        // since esd track has can account for 7 ITS layers pattern at most, I stored
        // the hits pattern info in the TPC data...
        const TBits &hits = esdtr->GetTPCClusterMap();
        //TBits &fakes = esdtr->GetTPCSharedMap(); // here we store fakes, but at the moment they are not set
        Int_t nhits=0;
        //printf(" Hits: ");
        for (int ilr=0;ilr<fITS->GetNActiveLayers();ilr++) {
            //printf("%c", hits.TestBitNumber(ilr) ? '+':'-');
            if(hits.TestBitNumber(ilr))nhits++;
        }
        
        
        //Fill histograms
        fRecoPt        = recoPt;
        fRecoPhi       = recoPhi;
        fRecoEta       = recoEta;
        fRecoY          = recoY;
        fRecoNhits      = nhits;
        fGenPt        = genPt;
        fGenEta       = genEta;
        fGenRad       = genRad;
        fRecoMClabel    = lbl;
        fRecoPdg        = pdgCodePart;
        fRecoPdgMother  = pdgCodeMother;
        fRecoNReconstructableHits  = recoHits;
        fRecoMClabelMother = lblMother;
        fGenPtMother = genPtMoth;
        //if(TMath::Abs(fRecoPdg)==2212 && TMath::Abs(fRecoPdgMother)==3122){
        //Printf("track label=%d, track pdg=%d xVtx=%f | mother label=%d, mother pdg=%d",fRecoMClabel,fRecoPdg,mcPart->Vz(),fRecoMClabelMother,fRecoPdgMother);
        //}
        fTreeRecoTracks->Fill();
        
        
        ////
        ULong_t status=esdtr->GetStatus();
        //Printf("status %ld", status);
        //if ((status&AliESDtrack::kTPCin)==0) {Printf("NO TPC in"); return;}
        //if ((status&AliESDtrack::kTPCout)==0) {Printf("NO TPC out"); return;}
        //if ((status&AliESDtrack::kTPCrefit)==0) {Printf("NO TPC refit"); return;}
    }
    
    
}
//________________________________________________________________________
void AliAnalysisTaskSEOmegacccToOmega3Pi::FillGenTreeRecoCascV0(){
/*
    gerated values of the variables taken from reconstructed (true) cascades
    fTreeGenVarCascV0Reco[5][4]
    TString part[5] = {"omega","lambda","k","p","pi4"};
    TString var[4]   = {"Eta", "Pt", "Y", "Phi"};
*/
    UInt_t lIdxPosCasc, lIdxNegCasc, lBachIdx;
    AliESDtrack *pTrackCasc, *nTrackCasc, *bachTrackCasc;
    Int_t lblPosCasc, lblNegCasc, lblBachCasc;
    TParticle *mcPosCascDghter, *mcNegCascDghter, *mcBachCascDghter;
    Int_t lblMothPosCasc, lblMothNegCasc, lblMothBachCasc;
    TParticle *mcMothPosCascDghter, *mcMothNegCascDghter, *mcMothBachCascDghter;
    Int_t lblGdMothPosCasc, lblGdMothNegCasc;
    TParticle *mcGdMothPosCascDghter, *mcGdMothNegCascDghter;
    
    Float_t lInvMassOmegaMinus=0.;
    Float_t lInvMassOmegaPlus=0.;
    
    Int_t nCasc=(Int_t)fEvent->GetNumberOfCascades();
    for(Int_t i=0; i<nCasc; i++){
        AliESDcascade *casc=fEvent->GetCascade(i);
        if (!casc) continue;
        
        lIdxPosCasc     = (UInt_t) TMath::Abs( casc->GetPindex() );
        lIdxNegCasc     = (UInt_t) TMath::Abs( casc->GetNindex() );
        lBachIdx        = (UInt_t) TMath::Abs( casc->GetBindex() );
        
        if(lBachIdx == lIdxNegCasc) {  AliWarning("Pb / Idx(Bach. track) = Idx(Neg. track) ... continue!");   continue;  }
        if(lBachIdx == lIdxPosCasc) {  AliWarning("Pb / Idx(Bach. track) = Idx(Pos. track) ... continue!");   continue;  }
        
        pTrackCasc        = (AliESDtrack*)fEvent->GetTrack( lIdxPosCasc );
        nTrackCasc        = (AliESDtrack*)fEvent->GetTrack( lIdxNegCasc );
        bachTrackCasc     = (AliESDtrack*)fEvent->GetTrack( lBachIdx );
        if (!pTrackCasc || !nTrackCasc || !bachTrackCasc) {
            Printf("ERROR: Could not retreive one of the daughter track");
            continue;
        }
        
        Double_t lV0quality = 0.;
        casc->ChangeMassHypothesis(lV0quality , 3334);
        lInvMassOmegaMinus = casc->GetEffMassXi();
        lV0quality = 0.;
        casc->ChangeMassHypothesis(lV0quality , -3334);
        lInvMassOmegaPlus = casc->GetEffMassXi();
        
        //label and MC particles daughters
        lblPosCasc  = pTrackCasc->GetLabel();
        lblNegCasc  = nTrackCasc->GetLabel();
        lblBachCasc = bachTrackCasc->GetLabel();
        mcPosCascDghter  = (TParticle*)fMcEvent->Particle( lblPosCasc );
        mcNegCascDghter  = (TParticle*)fMcEvent->Particle( lblNegCasc );
        mcBachCascDghter = (TParticle*)fMcEvent->Particle( lblBachCasc );
        //label and MC particles mother --> V0, casc
        lblMothPosCasc    = mcPosCascDghter->GetFirstMother();
        lblMothNegCasc    = mcNegCascDghter->GetFirstMother();
        lblMothBachCasc   = mcBachCascDghter->GetFirstMother();
        mcMothPosCascDghter  = (TParticle*)fMcEvent->Particle( lblMothPosCasc ); //v0
        mcMothNegCascDghter  = (TParticle*)fMcEvent->Particle( lblMothNegCasc ); //v0
        mcMothBachCascDghter = (TParticle*)fMcEvent->Particle( lblMothBachCasc ); //casc
        //label and MC particles grand mother --> casc
        lblGdMothPosCasc    = mcMothPosCascDghter->GetFirstMother();
        lblGdMothNegCasc    = mcMothNegCascDghter->GetFirstMother();
        mcGdMothPosCascDghter  = (TParticle*)fMcEvent->Particle( lblGdMothPosCasc ); //casc
        mcGdMothNegCascDghter  = (TParticle*)fMcEvent->Particle( lblGdMothNegCasc ); //casc
        
        if(lblMothPosCasc==lblMothNegCasc){
            Int_t pdgV0 = mcMothPosCascDghter->GetPdgCode();
            if(TMath::Abs(pdgV0)==3122){
                if(lblGdMothPosCasc==lblGdMothNegCasc && lblGdMothNegCasc==lblMothBachCasc){
                    Int_t pdgCasc = mcMothBachCascDghter->GetPdgCode();
                    if(TMath::Abs(pdgCasc)==3334){
                        //                TString part[5] = {"omega","lambda","k","p","pi4"}; "p","pi4"--> pos, neg
                        //                TString var[4]   = {"Eta", "Pt", "Y", "Phi"};
                        fTreeGenVarCascV0Reco[0][0] = mcMothBachCascDghter->Eta();
                        fTreeGenVarCascV0Reco[1][0] = mcMothPosCascDghter->Eta();
                        fTreeGenVarCascV0Reco[2][0] = mcBachCascDghter->Eta();
                        fTreeGenVarCascV0Reco[3][0] = mcPosCascDghter->Eta();
                        fTreeGenVarCascV0Reco[4][0] = mcNegCascDghter->Eta();
                        fTreeGenVarCascV0Reco[0][1] = mcMothBachCascDghter->Pt();
                        fTreeGenVarCascV0Reco[1][1] = mcMothPosCascDghter->Pt();
                        fTreeGenVarCascV0Reco[2][1] = mcBachCascDghter->Pt();
                        fTreeGenVarCascV0Reco[3][1] = mcPosCascDghter->Pt();
                        fTreeGenVarCascV0Reco[4][1] = mcNegCascDghter->Pt();
                        fTreeGenVarCascV0Reco[0][2] = mcMothBachCascDghter->Y();
                        fTreeGenVarCascV0Reco[1][2] = mcMothPosCascDghter->Y();
                        fTreeGenVarCascV0Reco[2][2] = mcBachCascDghter->Y();
                        fTreeGenVarCascV0Reco[3][2] = mcPosCascDghter->Y();
                        fTreeGenVarCascV0Reco[4][2] = mcNegCascDghter->Y();
                        fTreeGenVarCascV0Reco[0][3] = mcMothBachCascDghter->Phi();
                        fTreeGenVarCascV0Reco[1][3] = mcMothPosCascDghter->Phi();
                        fTreeGenVarCascV0Reco[2][3] = mcBachCascDghter->Phi();
                        fTreeGenVarCascV0Reco[3][3] = mcPosCascDghter->Phi();
                        fTreeGenVarCascV0Reco[4][3] = mcNegCascDghter->Phi();
                        fTreeGenVarCascV0Reco[0][4] = mcMothBachCascDghter->R();
                        fTreeGenVarCascV0Reco[1][4] = mcMothPosCascDghter->R();
                        fTreeGenVarCascV0Reco[2][4] = mcBachCascDghter->R();
                        fTreeGenVarCascV0Reco[3][4] = mcPosCascDghter->R();
                        fTreeGenVarCascV0Reco[4][4] = mcNegCascDghter->R();
                        fTreeGenVarCascV0RecoPDG[0] = mcMothBachCascDghter->GetPdgCode();
                        fTreeGenVarCascV0RecoPDG[1] = mcMothPosCascDghter->GetPdgCode();
                        fTreeGenVarCascV0RecoPDG[2] = mcBachCascDghter->GetPdgCode();
                        fTreeGenVarCascV0RecoPDG[3] = mcPosCascDghter->GetPdgCode();
                        fTreeGenVarCascV0RecoPDG[4] = mcNegCascDghter->GetPdgCode();
                        if(pdgCasc==3334){
                            fTreeGenVarCascV0RecoInvMass=lInvMassOmegaMinus;
                        }
                        else if(pdgCasc==-3334){
                            fTreeGenVarCascV0RecoInvMass=lInvMassOmegaPlus;
                        }
                        fTreeGenCascV0Reco->Fill();
                    }
                }
            }
        }
        
    }
    
    
    
    
    
}
//________________________________________________________________________
void AliAnalysisTaskSEOmegacccToOmega3Pi::FillGenTreeRecoV0(){
    /*
     gerated values of the variables taken from reconstructed (true) cascades
     fTreeGenVarV0Reco[3][5]
     TString part[] = {"lambda","p","pi4"};
     TString var[]   = {"Eta", "Pt", "Y", "Phi", "Rxy"};
     */
    UInt_t lIdxPosV0, lIdxNegV0;
    AliESDtrack *pTrack, *nTrack;
    Int_t lblPosV0, lblNegV0;
    TParticle *mcPosV0Dghter, *mcNegV0Dghter;
    Int_t lblMothPosV0, lblMothNegV0;
    TParticle *mcMothPosV0Dghter, *mcMothNegV0Dghter;
    
    Double_t lInvMassK0s =0.;
    Double_t lInvMassLambda =0.;
    Double_t lInvMassAntiLambda =0.;
    
    Int_t nV0=(Int_t)fEvent->GetNumberOfV0s();
    for(Int_t i=0; i<nV0; i++){
        AliESDv0 *v0=fEvent->GetV0(i);
        if (!v0) continue;
        
        lIdxPosV0     = (UInt_t) TMath::Abs( v0->GetPindex() );
        lIdxNegV0     = (UInt_t) TMath::Abs( v0->GetNindex() );
        pTrack        = (AliESDtrack*)fEvent->GetTrack( lIdxPosV0 );
        nTrack        = (AliESDtrack*)fEvent->GetTrack( lIdxNegV0 );
        if (!pTrack || !nTrack) {
            Printf("ERROR: Could not retreive one of the daughter track");
            continue;
        }
        
        // Getting invariant mass infos directly from ESD
        v0->ChangeMassHypothesis(310);
        lInvMassK0s = v0->GetEffMass();
        v0->ChangeMassHypothesis(3122);
        lInvMassLambda = v0->GetEffMass();
        v0->ChangeMassHypothesis(-3122);
        lInvMassAntiLambda = v0->GetEffMass();
        
        //label and MC particles daughters
        lblPosV0  = pTrack->GetLabel();
        lblNegV0  = nTrack->GetLabel();
        mcPosV0Dghter  = (TParticle*)fMcEvent->Particle( lblPosV0 );
        mcNegV0Dghter  = (TParticle*)fMcEvent->Particle( lblNegV0 );
        //label and MC particles mother --> V0, casc
        lblMothPosV0    = mcPosV0Dghter->GetFirstMother();
        lblMothNegV0    = mcNegV0Dghter->GetFirstMother();
        mcMothPosV0Dghter  = (TParticle*)fMcEvent->Particle( lblMothPosV0 ); //v0
        mcMothNegV0Dghter  = (TParticle*)fMcEvent->Particle( lblMothNegV0 ); //v0
    
        if(lblMothPosV0==lblMothNegV0){
            Int_t pdgV0pos = mcMothPosV0Dghter->GetPdgCode();
            Int_t pdgV0neg = mcMothNegV0Dghter->GetPdgCode();
            if(TMath::Abs(pdgV0pos)==3122 && pdgV0pos==pdgV0neg){
                fTreeGenVarV0Reco[0][0] = mcMothNegV0Dghter->Eta();
                fTreeGenVarV0Reco[1][0] = mcPosV0Dghter->Eta();
                fTreeGenVarV0Reco[2][0] = mcNegV0Dghter->Eta();
                
                fTreeGenVarV0Reco[0][1] = mcMothNegV0Dghter->Pt();
                fTreeGenVarV0Reco[1][1] = mcPosV0Dghter->Pt();
                fTreeGenVarV0Reco[2][1] = mcNegV0Dghter->Pt();
                
                fTreeGenVarV0Reco[0][2] = mcMothNegV0Dghter->Y();
                fTreeGenVarV0Reco[1][2] = mcPosV0Dghter->Y();
                fTreeGenVarV0Reco[2][2] = mcNegV0Dghter->Y();
                
                fTreeGenVarV0Reco[0][3] = mcMothNegV0Dghter->Phi();
                fTreeGenVarV0Reco[1][3] = mcPosV0Dghter->Phi();
                fTreeGenVarV0Reco[2][3] = mcNegV0Dghter->Phi();
                
                fTreeGenVarV0Reco[0][4] = mcMothNegV0Dghter->R();
                fTreeGenVarV0Reco[1][4] = mcPosV0Dghter->R();
                fTreeGenVarV0Reco[2][4] = mcNegV0Dghter->R();
                
                fTreeGenVarV0RecoPDG[0] = mcMothNegV0Dghter->GetPdgCode();
                fTreeGenVarV0RecoPDG[1] = mcPosV0Dghter->GetPdgCode();
                fTreeGenVarV0RecoPDG[2] = mcNegV0Dghter->GetPdgCode();
                
                if(mcMothNegV0Dghter->GetPdgCode()==3122){
                    fTreeGenVarV0RecoInvMass = lInvMassLambda;
                }
                else if(mcMothNegV0Dghter->GetPdgCode()==-3122){
                    fTreeGenVarV0RecoInvMass = lInvMassAntiLambda;
                }
                
                fTreeGenV0Reco->Fill();
            }
        }
        
    }
    
    
}

//________________________________________________________________________
//void AliAnalysisTaskSEOmegacccToOmega3Pi::FillCascadeHistos(){
//
//    //const AliESDVertex *lPrimaryBestESDVtx = esd->GetPrimaryVertex();
//    Double_t lBestPrimaryVtxPos[3]          = {-100.0, -100.0, -100.0};
//    fV1->GetXYZ( lBestPrimaryVtxPos );
//
//    Double_t lMagneticField = -10;
//    lMagneticField = fEvent->GetMagneticField( );
//
//    UInt_t lIdxPosXi, lIdxNegXi, lBachIdx;
//    AliESDtrack *pTrackXi, *nTrackXi, *bachTrackXi;
//    Double_t lV0quality;
//    Double_t lInvMassXiMinus, lInvMassOmega, lInvMassXiPlus, lXiCosineOfPointingAngle, lXiRadius, lrecoPt;
//    lInvMassOmega=0.;
//    Double_t lPosXi[3];
//    Int_t lblPosV0Dghter, lblNegV0Dghter, lblMotherPosV0Dghter, lblMotherNegV0Dghter, lblBach, lblGdMotherPosV0Dghter, lblGdMotherNegV0Dghter, lblMotherBach;
//    TParticle *mcBachForPID, *mcPosV0Dghter, *mcNegV0Dghter, *mcMotherPosV0Dghter, *mcMotherNegV0Dghter, *mcGdMotherPosV0Dghter, *mcGdMotherNegV0Dghter, *mcMotherBach, *mcBach;
//    Bool_t   lAssoXiMinus, lAssoXiPlus, lAssoOmegaMinus, lAssoOmegaPlus;
//
//    Int_t nCasc=(Int_t)fEvent->GetNumberOfCascades();
//    Long_t i;
//    for(i=0; i<nCasc; i++){
//        AliESDcascade *casc=fEvent->GetCascade(i);
//        if (!casc) continue;
//        // - Connection to daughter tracks of the current cascade
//        lIdxPosXi = 0x0;  lIdxPosXi = (UInt_t) TMath::Abs( casc->GetPindex() );
//        lIdxNegXi = 0x0;  lIdxNegXi = (UInt_t) TMath::Abs( casc->GetNindex() );
//        lBachIdx  = 0x0;  lBachIdx  = (UInt_t) TMath::Abs( casc->GetBindex() );
//        // - Rejection of a double use of a daughter track (nothing but just a crosscheck of what is done in the cascade vertexer)
//        if(lBachIdx == lIdxNegXi) {  AliWarning("Pb / Idx(Bach. track) = Idx(Neg. track) ... continue!");   continue;  }
//        if(lBachIdx == lIdxPosXi) {  AliWarning("Pb / Idx(Bach. track) = Idx(Pos. track) ... continue!");   continue;  }
//        // - Get the daughter tracks
//        pTrackXi = 0x0;  pTrackXi    = fEvent->GetTrack( lIdxPosXi );
//        nTrackXi = 0x0;  nTrackXi    = fEvent->GetTrack( lIdxNegXi );
//        bachTrackXi = 0x0;  bachTrackXi = fEvent->GetTrack( lBachIdx  );
//        if (!pTrackXi || !nTrackXi || !bachTrackXi ) { AliWarning("ERROR: Could not retrieve one of the 3 daughter tracks of the cascade ..."); continue; }
//        // - Info over reconstructed cascades
//        lV0quality = 0.;
//        if( bachTrackXi->Charge() < 0 ) {
//            //Calculate the effective mass of the Xi- candidate: Xi- hyp. (pdg code 3312)
//            lV0quality = 0.;
//            casc->ChangeMassHypothesis(lV0quality , 3312);
//            lInvMassXiMinus = casc->GetEffMassXi();
//            //Calculate the effective mass of the Xi- candidate: Omega- hyp. (pdg code 3334)
//            lV0quality = 0.;
//            casc->ChangeMassHypothesis(lV0quality , 3334);
//            //lInvMassOmegaMinus = casc->GetEffMassXi();
//            lInvMassOmega = casc->GetEffMassXi();
//            //Back to "default" hyp. (Xi-)
//            lV0quality = 0.;
//            casc->ChangeMassHypothesis(lV0quality , 3312);
//        }
//        if( bachTrackXi->Charge() >  0 ){
//            //Calculate the effective mass of the Xi- candidate: Xi+ hyp. (pdg code -3312)
//            lV0quality = 0.;
//            casc->ChangeMassHypothesis(lV0quality , -3312);
//            lInvMassXiPlus = casc->GetEffMassXi();
//            //Calculate the effective mass of the Xi- candidate: Omega+ hyp. (pdg code -3334)
//            lV0quality = 0.;
//            casc->ChangeMassHypothesis(lV0quality , -3334);
//            //lInvMassOmegaPlus = casc->GetEffMassXi();
//            lInvMassOmega = casc->GetEffMassXi();
//            //Back to "default" hyp. (Xi-)
//            lV0quality = 0.;
//            casc->ChangeMassHypothesis(lV0quality , -3312);
//        }
//        casc->GetXYZcascade( lPosXi[0], lPosXi[1], lPosXi[2] );
//        lXiCosineOfPointingAngle   = casc->GetCascadeCosineOfPointingAngle( lBestPrimaryVtxPos[0], lBestPrimaryVtxPos[1], lBestPrimaryVtxPos[2] );
//        lXiRadius = TMath::Sqrt( lPosXi[0]*lPosXi[0] + lPosXi[1]*lPosXi[1] );
//        lrecoPt = casc->Pt();
//
//        Double_t etagen=-99.;
//        Double_t ptgen=-99.;
//        Double_t etadau_0=-99.;
//        Double_t etadau_1=-99.;
//        // - Level of the V0 daughters
//        lblPosV0Dghter = 0;  lblPosV0Dghter = (Int_t) TMath::Abs( pTrackXi->GetLabel() );
//        lblNegV0Dghter = 0;  lblNegV0Dghter = (Int_t) TMath::Abs( nTrackXi->GetLabel() );
//        mcPosV0Dghter = 0x0; mcPosV0Dghter = fMcEvent->Particle( lblPosV0Dghter );
//        mcNegV0Dghter = 0x0; mcNegV0Dghter = fMcEvent->Particle( lblNegV0Dghter );
//        // - Level of the cascade daughters
//        lblMotherPosV0Dghter = 0.;  lblMotherPosV0Dghter = mcPosV0Dghter->GetFirstMother();
//        lblMotherNegV0Dghter = 0.;  lblMotherNegV0Dghter = mcNegV0Dghter->GetFirstMother();
//        //if (lblMotherPosV0Dghter != lblMotherNegV0Dghter) continue; // same mother
//        //if (lblMotherPosV0Dghter < 0) continue;                     // this particle is primary, no mother
//        //if (lblMotherNegV0Dghter < 0) continue;                     // this particle is primary, no mother
//        if(lblMotherPosV0Dghter == lblMotherNegV0Dghter && lblMotherPosV0Dghter > 0 && lblMotherNegV0Dghter > 0){
//            // mothers = Lambda candidate ... a priori
//            mcMotherPosV0Dghter = 0x0; mcMotherPosV0Dghter = fMcEvent->Particle( lblMotherPosV0Dghter );
//            mcMotherNegV0Dghter = 0x0; mcMotherNegV0Dghter = fMcEvent->Particle( lblMotherNegV0Dghter );  // MN: redundant?? already checked that labels are the same...-->same part from stack
//            lblBach = 0; lblBach = (Int_t) TMath::Abs( bachTrackXi->GetLabel() );
//            mcBach = 0x0; mcBach = fMcEvent->Particle( lblBach );
//            // - Level of cascade candidate
//            lblGdMotherPosV0Dghter = 0; lblGdMotherPosV0Dghter = mcMotherPosV0Dghter->GetFirstMother() ;
//            lblGdMotherNegV0Dghter = 0; lblGdMotherNegV0Dghter = mcMotherNegV0Dghter->GetFirstMother() ;
//            //if(lblGdMotherPosV0Dghter != lblGdMotherNegV0Dghter) continue;
//            //if(lblGdMotherPosV0Dghter < 0) continue;                  // primary lambda ...
//            //if(lblGdMotherNegV0Dghter < 0) continue;                  // primary lambda ...
//            if(lblGdMotherPosV0Dghter == lblGdMotherNegV0Dghter && lblGdMotherPosV0Dghter>0 && lblGdMotherNegV0Dghter>0){
//                // Gd mothers = cascade candidate ... a priori
//                mcGdMotherPosV0Dghter = 0x0; mcGdMotherPosV0Dghter = fMcEvent->Particle( lblGdMotherPosV0Dghter );
//                mcGdMotherNegV0Dghter = 0x0; mcGdMotherNegV0Dghter = fMcEvent->Particle( lblGdMotherNegV0Dghter );
//                lblMotherBach = 0; lblMotherBach = (Int_t) TMath::Abs( mcBach->GetFirstMother() );
//                //if(lblMotherBach != lblGdMotherPosV0Dghter) continue; //same mother for bach and V0 daughters
//                if(lblMotherBach == lblGdMotherPosV0Dghter){
//                    mcMotherBach = 0x0; mcMotherBach = fMcEvent->Particle( lblMotherBach );
//                    etagen=mcMotherBach->Eta();
//                    ptgen=mcMotherBach->Pt();
//                    etadau_0=((TParticle*)fMcEvent->Particle((mcMotherBach->GetDaughter(0))))->Eta();
//                    etadau_1=((TParticle*)fMcEvent->Particle((mcMotherBach->GetDaughter(1))))->Eta();
//                    // - Manage boolean for association
//                    if      (mcMotherBach->GetPdgCode() == 3312  && mcGdMotherPosV0Dghter->GetPdgCode() == 3312  && mcGdMotherNegV0Dghter->GetPdgCode() == 3312)  {lAssoXiMinus    = kTRUE;}
//                    else if (mcMotherBach->GetPdgCode() == -3312 && mcGdMotherPosV0Dghter->GetPdgCode() == -3312 && mcGdMotherNegV0Dghter->GetPdgCode() == -3312) {lAssoXiPlus     = kTRUE;}
//                    else if (mcMotherBach->GetPdgCode() == 3334  && mcGdMotherPosV0Dghter->GetPdgCode() == 3334  && mcGdMotherNegV0Dghter->GetPdgCode() == 3334)  {lAssoOmegaMinus = kTRUE;}
//                    else if (mcMotherBach->GetPdgCode() == -3334 && mcGdMotherPosV0Dghter->GetPdgCode() == -3334 && mcGdMotherNegV0Dghter->GetPdgCode() == -3334) {lAssoOmegaPlus  = kTRUE;}
//                }
//            }
//        }
//        if(lAssoXiMinus  || lAssoXiPlus   || lAssoOmegaMinus || lAssoOmegaPlus ){
//            fCascInvMassS      ->Fill(lInvMassOmega);
//            fCascRadiusS       ->Fill(lXiRadius);
//            fCascPtS           ->Fill(lrecoPt);
//            fCascCosPointAngleS->Fill(lXiCosineOfPointingAngle);
//            fhOmegaRecoVsPtGen->Fill(ptgen);
//            fhPtGenEtaGen_OmegaReco->Fill(ptgen,etagen);
//            fhEtaDauVsEtaMoth_Rec[6]->Fill(etagen,etadau_0);//Omega vs Lambda
//            fhEtaDauVsEtaMoth_Rec[7]->Fill(etagen,etadau_1);//Omega vs kaon
//        }
//        else{
//            fCascInvMassB      ->Fill(lInvMassOmega);
//            fCascRadiusB       ->Fill(lXiRadius);
//            fCascPtB           ->Fill(lrecoPt);
//            fCascCosPointAngleB->Fill(lXiCosineOfPointingAngle);
//        }
//    }
//
//}
//________________________________________________________________________
//void AliAnalysisTaskSEOmegacccToOmega3Pi::FillV0Histos(){
//
//
//    //const AliESDVertex *lPrimaryBestESDVtx = esd->GetPrimaryVertex();
//    Double_t lBestPrimaryVtxPos[3]          = {-100.0, -100.0, -100.0};
//    fV1->GetXYZ( lBestPrimaryVtxPos );
//
//    Double_t lMagneticField = -10;
//    lMagneticField = fEvent->GetMagneticField( );
//
//
//    Int_t nV0=(Int_t)fEvent->GetNumberOfV0s();
//    Long_t i;
//    //Printf("V0pointangle \t DCA+toPV \t DCA-toPV \t V0radius \t decayVx \t decayVy \t decayVz \t eta+ \t eta- \t label+ \t label-");
//    for(i=0; i<nV0; i++){
//        AliESDv0 *v0=fEvent->GetV0(i);
//
//        UInt_t lKeyPos = (UInt_t)TMath::Abs(v0->GetPindex());
//        UInt_t lKeyNeg = (UInt_t)TMath::Abs(v0->GetNindex());
//
//        AliESDtrack *pTrack=((AliESDEvent*)fEvent)->GetTrack(lKeyPos);
//        AliESDtrack *nTrack=((AliESDEvent*)fEvent)->GetTrack(lKeyNeg);
//        if (!pTrack || !nTrack) {
//            Printf("ERROR: Could not retreive one of the daughter track");
//            continue;
//        }
//        // MC labels daughters
//        Int_t lblPosV0Dghter = (Int_t) TMath::Abs( pTrack->GetLabel() );
//        Int_t lblNegV0Dghter = (Int_t) TMath::Abs( nTrack->GetLabel() );
//
//        TParticle* mcPosV0Dghter = fMcEvent->Particle( lblPosV0Dghter );
//        TParticle* mcNegV0Dghter = fMcEvent->Particle( lblNegV0Dghter );
//
//        Int_t lPIDPositive = mcPosV0Dghter -> GetPdgCode();
//        Int_t lPIDNegative = mcNegV0Dghter -> GetPdgCode();
//
//        Int_t lblMotherPosV0Dghter = mcPosV0Dghter->GetFirstMother();
//        Int_t lblMotherNegV0Dghter = mcNegV0Dghter->GetFirstMother();
//
//        Bool_t isSignalLambda=kFALSE;
//        Bool_t isSignalAntiLambda=kFALSE;
//        Double_t etagen=-99.;
//        Double_t ptgen=-99.;
//        Double_t etadau_0=-99.;
//        Double_t etadau_1=-99.;
//        if( lblMotherPosV0Dghter == lblMotherNegV0Dghter && lblMotherPosV0Dghter > -1 ) {
//            TParticle* pThisV0 = fMcEvent->Particle( lblMotherPosV0Dghter );
//            Int_t pidV0 = pThisV0->GetPdgCode(); //PDG Code
//            //Printf("Reco Lambda signal--> V0=%d-%d %s mother= %d,  d+=%d %s d-=%d %s",lblMotherPosV0Dghter,lblMotherNegV0Dghter,pThisV0->GetName(),pThisV0->GetFirstMother(),lblPosV0Dghter,mcPosV0Dghter->GetName(),lblNegV0Dghter,mcNegV0Dghter->GetName());
//            if(pidV0==3122) isSignalLambda=kTRUE;
//            if(pidV0==-3122) isSignalAntiLambda=kTRUE;
//            etagen=pThisV0->Eta();
//            ptgen=pThisV0->Pt();
//            etadau_0=((TParticle*)fMcEvent->Particle((pThisV0->GetDaughter(0))))->Eta();
//            etadau_1=((TParticle*)fMcEvent->Particle((pThisV0->GetDaughter(1))))->Eta();
//        }
//
//
//        Double_t tDecayVertexV0[3];
//        v0->GetXYZ(tDecayVertexV0[0],tDecayVertexV0[1],tDecayVertexV0[2]);
//
//        Double_t tV0mom[3];
//        v0->GetPxPyPz( tV0mom[0],tV0mom[1],tV0mom[2] );
//        Double_t lV0TotalMomentum = TMath::Sqrt(
//                                                tV0mom[0]*tV0mom[0]+tV0mom[1]*tV0mom[1]+tV0mom[2]*tV0mom[2] );
//
//        Double_t lV0Radius = TMath::Sqrt(tDecayVertexV0[0]*tDecayVertexV0[0]+tDecayVertexV0[1]*tDecayVertexV0[1]);
//
//        Double_t lPt = v0->Pt();
//        Double_t lRapK0Short = v0->RapK0Short();
//        Double_t lRapLambda = v0->RapLambda();
//
//        Double_t lMomPos[3];
//        v0->GetPPxPyPz(lMomPos[0],lMomPos[1],lMomPos[2]);
//        Double_t lMomNeg[3];
//        v0->GetNPxPyPz(lMomNeg[0],lMomNeg[1],lMomNeg[2]);
//
//
//        //Daughter Eta for Eta selection
//        //Double_t fTreeVariableNegEta = nTrack->Eta();
//        //Double_t fTreeVariablePosEta = pTrack->Eta();
//
//        Double_t lDcaPosToPrimVertex = TMath::Abs(pTrack->GetD(lBestPrimaryVtxPos[0],
//                                                               lBestPrimaryVtxPos[1],
//                                                               lMagneticField) );
//
//        Double_t lDcaNegToPrimVertex = TMath::Abs(nTrack->GetD(lBestPrimaryVtxPos[0],
//                                                               lBestPrimaryVtxPos[1],
//                                                               lMagneticField) );
//
//
//
//        //lOnFlyStatus = v0->GetOnFlyStatus();
//        //lChi2V0 = v0->GetChi2V0();
//        Double_t lDcaV0Daughters = v0->GetDcaV0Daughters();
//        Double_t lDcaV0ToPrimVertex = v0->GetD(lBestPrimaryVtxPos[0],lBestPrimaryVtxPos[1],lBestPrimaryVtxPos[2]);
//        Double_t lV0CosineOfPointingAngle = v0->GetV0CosineOfPointingAngle(lBestPrimaryVtxPos[0],lBestPrimaryVtxPos[1],lBestPrimaryVtxPos[2]);
//
//        // Getting invariant mass infos directly from ESD
//        v0->ChangeMassHypothesis(310);
//        Double_t lInvMassK0s = v0->GetEffMass();
//        v0->ChangeMassHypothesis(3122);
//        Double_t lInvMassLambda = v0->GetEffMass();
//        v0->ChangeMassHypothesis(-3122);
//        Double_t lInvMassAntiLambda = v0->GetEffMass();
//        Double_t lAlphaV0 = v0->AlphaV0();
//        Double_t lPtArmV0 = v0->PtArmV0();
//
//        if (isSignalLambda) {
//            fhV0radiusS->Fill(lV0Radius);
//            fhDCAnegToPVS->Fill(lDcaNegToPrimVertex);
//            fhDCAposToPVS->Fill(lDcaPosToPrimVertex);
//            fhDCAV0DaughtersS->Fill(lDcaV0Daughters);
//            fhCosinePointAS->Fill(lV0CosineOfPointingAngle);
//            //hProperLifetime->Fill();
//            fHistMassLambdaS->Fill(lInvMassLambda);
//            fhV0ptS->Fill(lPt);
//            fhLambdaRecoVsPtGen->Fill(ptgen);
//            fhPtGenEtaGen_LambdaReco->Fill(ptgen,etagen);
//            fhEtaDauVsEtaMoth_Rec[8]->Fill(etagen,etadau_1);//Lambda vs pion
//            fhEtaDauVsEtaMoth_Rec[9]->Fill(etagen,etadau_0);//Lambda vs proton
//        }
//        else if(isSignalAntiLambda){
//            fhV0radiusS->Fill(lV0Radius);
//            fhDCAnegToPVS->Fill(lDcaNegToPrimVertex);
//            fhDCAposToPVS->Fill(lDcaPosToPrimVertex);
//            fhDCAV0DaughtersS->Fill(lDcaV0Daughters);
//            fhCosinePointAS->Fill(lV0CosineOfPointingAngle);
//            //hProperLifetime->Fill();
//            fHistMassAntiLambdaS->Fill(lInvMassAntiLambda);
//            fhV0ptS->Fill(lPt);
//            fhLambdaRecoVsPtGen->Fill(ptgen);
//            fhPtGenEtaGen_LambdaReco->Fill(ptgen,etagen);
//            fhEtaDauVsEtaMoth_Rec[8]->Fill(etagen,etadau_1);//Lambda vs pion
//            fhEtaDauVsEtaMoth_Rec[9]->Fill(etagen,etadau_0);//Lambda vs proton
//        }
//        else {
//            fhV0radiusB->Fill(lV0Radius);
//            fhDCAnegToPVB->Fill(lDcaNegToPrimVertex);
//            fhDCAposToPVB->Fill(lDcaPosToPrimVertex);
//            fhDCAV0DaughtersB->Fill(lDcaV0Daughters);
//            fhCosinePointAB->Fill(lV0CosineOfPointingAngle);
//            //hProperLifetime->Fill();
//            fHistMassLambdaB->Fill(lInvMassLambda);
//            fhV0ptB->Fill(lPt);
//        }
//    }
//}
//----------------------------------------------------------------------------
Double_t AliAnalysisTaskSEOmegacccToOmega3Pi::DecayLength(AliESDVertex *primV, AliESDVertex *secV) const
{
    /// Decay length assuming it is produced at "point" [cm]
    
    return TMath::Sqrt((primV->GetX()-secV->GetX())
                       *(primV->GetX()-secV->GetX())
                       +(primV->GetY()-secV->GetY())
                       *(primV->GetY()-secV->GetY())
                       +(primV->GetZ()-secV->GetZ())
                       *(primV->GetZ()-secV->GetZ()));
}
//----------------------------------------------------------------------------
Double_t AliAnalysisTaskSEOmegacccToOmega3Pi::DecayLengthXY(AliESDVertex *primV, AliESDVertex *secV) const
{
    /// Decay length in XY assuming it is produced at "point" [cm]
    
    return TMath::Sqrt((primV->GetX()-secV->GetX())
                       *(primV->GetX()-secV->GetX())
                       +(primV->GetY()-secV->GetY())
                       *(primV->GetY()-secV->GetY()));
}
//----------------------------------------------------------------------------
Double_t AliAnalysisTaskSEOmegacccToOmega3Pi::CosPointingAngle(AliESDVertex *primV, AliESDVertex *secV, Double_t p[3]) const
{
    /// Cosine of pointing angle in space assuming it is produced at "point"
    
    TVector3 mom(p[0],p[1],p[2]);
    TVector3 fline(secV->GetX()-primV->GetX(),
                   secV->GetY()-primV->GetY(),
                   secV->GetZ()-primV->GetZ());
    
    Double_t ptot2 = mom.Mag2()*fline.Mag2();
    if(ptot2 <= 0) {
        return 0.0;
    } else {
        Double_t cos = mom.Dot(fline)/TMath::Sqrt(ptot2);
        if(cos >  1.0) cos =  1.0;
        if(cos < -1.0) cos = -1.0;
        return cos;
    }
}
//----------------------------------------------------------------------------
Double_t AliAnalysisTaskSEOmegacccToOmega3Pi::CosPointingAngleXY(AliESDVertex *primV, AliESDVertex *secV, Double_t p[3]) const
{
    /// Cosine of pointing angle in transverse plane assuming it is produced
    /// at "point"
    
    TVector3 momXY(p[0],p[1],0.);
    TVector3 flineXY(secV->GetX()-primV->GetX(),
                     secV->GetY()-primV->GetY(),
                     0.);
    
    Double_t ptot2 = momXY.Mag2()*flineXY.Mag2();
    if(ptot2 <= 0) {
        return 0.0;
    } else {
        Double_t cos = momXY.Dot(flineXY)/TMath::Sqrt(ptot2);
        if(cos >  1.0) cos =  1.0;
        if(cos < -1.0) cos = -1.0;
        return cos;
    }
}
//----------------------------------------------------------------------------
Double_t AliAnalysisTaskSEOmegacccToOmega3Pi::CosThetaStar(Int_t ip,UInt_t pdgvtx,UInt_t pdgprong0,UInt_t pdgprong1, Double_t pvtx[3], Double_t pprong0[3], Double_t pprong1[3]) const
{
    /// Only for 2-prong decays:
    /// Cosine of decay angle (theta*) in the rest frame of the mother particle
    /// for prong ip (0 or 1) with mass hypotheses pdgvtx for mother particle,
    /// pdgprong0 for prong 0 and pdgprong1 for prong1
    
    
    Double_t massvtx = TDatabasePDG::Instance()->GetParticle(pdgvtx)->Mass();
    Double_t massp[2];
    massp[0] = TDatabasePDG::Instance()->GetParticle(pdgprong0)->Mass();
    massp[1] = TDatabasePDG::Instance()->GetParticle(pdgprong1)->Mass();
    
    Double_t pStar = TMath::Sqrt((massvtx*massvtx-massp[0]*massp[0]-massp[1]*massp[1])*(massvtx*massvtx-massp[0]*massp[0]-massp[1]*massp[1])-4.*massp[0]*massp[0]*massp[1]*massp[1])/(2.*massvtx);
    
    Double_t e=TMath::Sqrt((pvtx[0]*pvtx[0]+pvtx[1]*pvtx[1]+pvtx[2]*pvtx[2])+massvtx*massvtx);
    Double_t beta = TMath::Sqrt((pvtx[0]*pvtx[0]+pvtx[1]*pvtx[1]+pvtx[2]*pvtx[2]))/e;
    Double_t gamma = e/massvtx;
    
    Double_t cts0 = (QlProng(pvtx, pprong0)/gamma-beta*TMath::Sqrt(pStar*pStar+massp[0]*massp[0]))/pStar;
    Double_t cts1 = (QlProng(pvtx, pprong1)/gamma-beta*TMath::Sqrt(pStar*pStar+massp[1]*massp[1]))/pStar;
    
    Double_t cts = 0.;
    if(ip==0) cts = cts0;
    else cts = cts1;
    
    return cts;
}
//----------------------------------------------------------------------------
Double_t AliAnalysisTaskSEOmegacccToOmega3Pi::QlProng(Double_t pvtx[3], Double_t pprong[3]) const
{
    /// Longitudinal momentum of prong w.r.t. to total momentum
    
    TVector3 mom(pvtx[0],pvtx[1],pvtx[2]);
    TVector3 momTot(pprong[0],pprong[1],pprong[2]);
    
    return mom.Dot(momTot)/momTot.Mag();
}

//----------------------------------------------------------------------------
TTree* AliAnalysisTaskSEOmegacccToOmega3Pi::BuildTreeRecoTracks(TString name, TString title)
{
    TTree *tree = new TTree(name.Data(),title.Data());
    tree->Branch("fReco_pt",&fRecoPt,"fReco_pt/F");
    tree->Branch("fReco_phi",&fRecoPhi,"fReco_phi/F");
    tree->Branch("fReco_eta",&fRecoEta,"fReco_eta/F");
    tree->Branch("fReco_y",&fRecoY,"fReco_y/F");
    tree->Branch("fGen_pt",&fGenPt,"fGen_pt/F");
    tree->Branch("fGen_eta",&fGenEta,"fGen_eta/F");
    tree->Branch("fGen_rxy",&fGenRad,"fGen_rxy/F");
    tree->Branch("fReco_nhits",&fRecoNhits,"fReco_nhits/I");
    tree->Branch("fReco_MClabel",&fRecoMClabel,"fReco_MClabel/I");
    tree->Branch("fReco_MClabelMother",&fRecoMClabelMother,"fReco_MClabelMother/I");
    tree->Branch("fGen_ptMother",&fGenPtMother,"fGen_ptMother/F");
    tree->Branch("fReco_pdg",&fRecoPdg,"fReco_pdg/I");
    tree->Branch("fReco_pdgMother",&fRecoPdgMother,"fReco_pdgMother/I");
    tree->Branch("fReco_nReconstructableHits",&fRecoNReconstructableHits,"fReco_nReconstructableHits/I");
    
    return tree;
    
}
//----------------------------------------------------------------------------
TTree* AliAnalysisTaskSEOmegacccToOmega3Pi::BuildTreeReconstruction(TString name, TString title)
{
    TTree *tree = new TTree(name.Data(),title.Data());
    tree->Branch("fParticle_pdg",&fParticleVarPdg,"fParticle_pdg/I");
    tree->Branch("fParticle_pdgMoth",&fParticleVarPdgMoth,"fParticle_pdgMoth/I");
    tree->Branch("fParticle_pt",&fParticleVarPt,"fParticle_pt/F");
    tree->Branch("fParticle_p",&fParticleVarP,"fParticle_p/F");
    tree->Branch("fParticle_eta",&fParticleVarEta,"fParticle_eta/F");
    tree->Branch("fParticle_rap",&fParticleVarRap,"fParticle_Rap/F");
    tree->Branch("fParticle_phi",&fParticleVarPhi,"fParticle_phi/F");
    tree->Branch("fParticle_x",&fParticleVarX,"fParticle_x/F");
    tree->Branch("fParticle_y",&fParticleVarY,"fParticle_y/F");
    tree->Branch("fParticle_z",&fParticleVarZ,"fParticle_z/F");
    tree->Branch("fParticle_rxy",&fParticleVarRxy,"fParticle_rxy/F");
    tree->Branch("fParticle_NhitsAss",&fParticleVarNhitsAssigned,"fParticle_NhitsAss/I");
    tree->Branch("fParticle_NhitsReco",&fParticleVarNhitsReco,"fParticle_NhitsReco/I");
    tree->Branch("fParticle_isReco",&fParticleVarIsReco,"fParticle_isReco/O");
    
    return tree;
    
}
//----------------------------------------------------------------------------
TTree* AliAnalysisTaskSEOmegacccToOmega3Pi::BuildTreeOmegacccGenReco(TString name, TString title)
{
    TTree *tree = new TTree(name.Data(),title.Data());
    TString particle[5] = {"_omegaccc", "_omegacc", "_omegac", "_V0", "_Casc"};
    TString coord[3] = {"x","y","z"};
    for(Int_t i=0; i<3; i++){
        for(int j=0; j<5; j++){
            tree->Branch(Form("fDecVtxGen_%s%s",coord[i].Data(),particle[j].Data()),&fTreeVariableRecoTrueOmegacccDecVtxGen[j][i],Form("fDecVtxGen_%s%s/F",coord[i].Data(),particle[j].Data()));
            tree->Branch(Form("fDecVtxReco_%s%s",coord[i].Data(),particle[j].Data()),&fTreeVariableRecoTrueOmegacccDecVtxReco[j][i],Form("fDecVtxReco_%s%s/F",coord[i].Data(),particle[j].Data()));
            tree->Branch(Form("fPGen_%s%s",coord[i].Data(),particle[j].Data()),&fTreeVariableRecoTrueOmegacccMomGen[j][i],Form("fPGen_%s%s/F",coord[i].Data(),particle[j].Data()));
            tree->Branch(Form("fPReco_%s%s",coord[i].Data(),particle[j].Data()),&fTreeVariableRecoTrueOmegacccMomReco[j][i],Form("fPReco_%s%s/F",coord[i].Data(),particle[j].Data()));
        }
    }
    return tree;
}
//----------------------------------------------------------------------------
TTree* AliAnalysisTaskSEOmegacccToOmega3Pi::BuildTreeOmegacccGen(TString name, TString title)
{
    TTree *tree = new TTree(name.Data(),title.Data());
    TString part[11] = {"omegaccc","omegacc","pi1","omegac","pi2","omega","pi3","lambda","k","p","pi4"};
    TString var[]   = {"Eta", "Pt", "Y", "Phi","Rxy","ReconstructableHits","Pdg"};
    for(int i=0; i<11; i++){
        for(int j=0; j<5; j++){
            tree->Branch(Form("fTreeGen_%s_%s",part[i].Data(),var[j].Data()),&fTreeGenVarOmegaccc[i][j],Form("fTreeGen_%s_%s/F",part[i].Data(),var[j].Data()));
        }
        tree->Branch(Form("fTreeGen_%s_%s",part[i].Data(),var[5].Data()),&fTreeGenVarOmegacccNRHits[i],Form("fTreeGen_%s_%s/I",part[i].Data(),var[5].Data()));
        tree->Branch(Form("fTreeGen_%s_%s",part[i].Data(),var[6].Data()),&fTreeGenVarOmegacccPDG[i],Form("fTreeGen_%s_%s/I",part[i].Data(),var[6].Data()));
    }
    return tree;
}

//----------------------------------------------------------------------------
TTree* AliAnalysisTaskSEOmegacccToOmega3Pi::BuildTreeCascV0Reco(TString name, TString title)
{
    //save gen Eta, Pt, Y, Phi of V0 and Cascades reconstructed
    TTree *tree = new TTree(name.Data(),title.Data());
    TString part[5] = {"omega","lambda","k","p","pi4"};
    TString var[]   = {"Eta", "Pt", "Y", "Phi","Rxy","Pdg"};
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            tree->Branch(Form("fTreeGen_%s_%s",part[i].Data(),var[j].Data()),&fTreeGenVarCascV0Reco[i][j],Form("fTreeGen_%s_%s/F",part[i].Data(),var[j].Data()));
        }
        tree->Branch(Form("fTreeGen_%s_%s",part[i].Data(),var[5].Data()),&fTreeGenVarCascV0RecoPDG[i],Form("fTreeGen_%s_%s/I",part[i].Data(),var[5].Data()));
    }
    tree->Branch(Form("fTreeGen_%s_InvMass",part[0].Data()),&fTreeGenVarCascV0RecoInvMass,Form("fTreeGen_%s_InvMass/F",part[0].Data()));
    return tree;
}
//----------------------------------------------------------------------------
TTree* AliAnalysisTaskSEOmegacccToOmega3Pi::BuildTreeV0Reco(TString name, TString title)
{
    //save gen Eta, Pt, Y, Phi of V0 and Cascades reconstructed
    TTree *tree = new TTree(name.Data(),title.Data());
    TString part[] = {"lambda","p","pi4"};
    TString var[]   = {"Eta", "Pt", "Y", "Phi","Rxy","Pdg"};
    for(int i=0; i<3; i++){
        for(int j=0; j<5; j++){
            tree->Branch(Form("fTreeGen_%s_%s",part[i].Data(),var[j].Data()),&fTreeGenVarV0Reco[i][j],Form("fTreeGen_%s_%s/F",part[i].Data(),var[j].Data()));
        }
        tree->Branch(Form("fTreeGen_%s_%s",part[i].Data(),var[5].Data()),&fTreeGenVarV0RecoPDG[i],Form("fTreeGen_%s_%s/I",part[i].Data(),var[5].Data()));
    }
    tree->Branch(Form("fTreeGen_%s_InvMass",part[0].Data()),&fTreeGenVarV0RecoInvMass,Form("fTreeGen_%s_InvMass/F",part[0].Data()));
    return tree;
}
//----------------------------------------------------------------------------
TTree* AliAnalysisTaskSEOmegacccToOmega3Pi::BuildTreeOmegacccCutVar(TString name, TString title)
{
    TTree *tree = new TTree(name.Data(),title.Data());
    
    TString particle[9] = {"_omegaccc","_omegacc","_omegac","_pi1","_pi2","_pi3","_V0neg","_V0pos","_CascBach"};
    for(int i=0; i<9; i++){
        if(i<3){
            tree->Branch(Form("fChi2ndf%s",particle[i].Data()),&fTreeVariableDecVtxChi2Ndf[i],Form("fChi2ndf%s/F",particle[i].Data()));
            tree->Branch(Form("fCosPA%s",particle[i].Data()),&fTreeVariableCosPointingAngle[i],Form("fCosPA%s/F",particle[i].Data()));
            tree->Branch(Form("fCosPAXY%s",particle[i].Data()),&fTreeVariableCosPointingAngleXY[i],Form("fCosPAXY%s/F",particle[i].Data()));
            tree->Branch(Form("fDecayLength%s",particle[i].Data()),&fTreeVariableDecayLength[i],Form("fDecayLength%s/F",particle[i].Data()));
            tree->Branch(Form("fDecayLengthXY%s",particle[i].Data()),&fTreeVariableDecayLengthXY[i],Form("fDecayLengthXY%s/F",particle[i].Data()));
            tree->Branch(Form("fInvMass%s",particle[i].Data()),&fTreeVariableInvMass[i],Form("fInvMass%s/F",particle[i].Data()));
        }
        if(i<6){
            tree->Branch(Form("fd0%s",particle[i].Data()),&fTreeVariabled0rphi[i],Form("fd0%s/F",particle[i].Data()));
        }
        tree->Branch(Form("fPt%s",particle[i].Data()),&fTreeVariablePt[i],Form("fPt%s/F",particle[i].Data()));
        tree->Branch(Form("fEta%s",particle[i].Data()),&fTreeVariableEta[i],Form("fEta%s/F",particle[i].Data()));
        tree->Branch(Form("fPhi%s",particle[i].Data()),&fTreeVariablePhi[i],Form("fPhi%s/F",particle[i].Data()));
        tree->Branch(Form("fRap%s",particle[i].Data()),&fTreeVariableRap[i],Form("fRap%s/F",particle[i].Data()));
        if(fIsMCSignalProd){ //variables for efficiency
            tree->Branch(Form("fGenPt%s",particle[i].Data()),&fTreeVariableGenPt[i],Form("fGenPt%s/F",particle[i].Data()));
            tree->Branch(Form("fGenEta%s",particle[i].Data()),&fTreeVariableGenEta[i],Form("fGenEta%s/F",particle[i].Data()));
            tree->Branch(Form("fGenPhi%s",particle[i].Data()),&fTreeVariableGenPhi[i],Form("fGenPhi%s/F",particle[i].Data()));
            tree->Branch(Form("fGenRap%s",particle[i].Data()),&fTreeVariableGenRap[i],Form("fGenRap%s/F",particle[i].Data()));
            tree->Branch(Form("fGenRxy%s",particle[i].Data()),&fTreeVariableGenRxy[i],Form("fGenRxy%s/F",particle[i].Data()));
        }
        
    }
    tree->Branch("fInvMass_omega",&fTreeVariableInvMass[3],"fInvMass_omega/F");
    tree->Branch("fIsSignal",&fIsSignal,"fIsSignal/O");
    
    return tree;
}
//----------------------------------------------------------------------------
TTree* AliAnalysisTaskSEOmegacccToOmega3Pi::BuildTreeOmegacCutVar(TString name, TString title)
{
    TTree *tree = new TTree(name.Data(),title.Data());
    
    TString particle[3] = {"_omegac","_omega","_pi3"};
    tree->Branch(Form("fChi2ndf%s",particle[0].Data()),&fTreeVariableDecVtxChi2NdfOmegac,Form("fChi2ndf%s/F",particle[0].Data()));
    tree->Branch(Form("fDecayLength%s",particle[0].Data()),&fTreeVariableDecayLengthOmegac,Form("fDecayLength%s/F",particle[0].Data()));
    tree->Branch(Form("fDecayLengthXY%s",particle[0].Data()),&fTreeVariableDecayLengthXYOmegac,Form("fDecayLengthXY%s/F",particle[0].Data()));
    tree->Branch(Form("fInvMass%s",particle[0].Data()),&fTreeVariableInvMassOmegac[0],Form("fInvMass%s/F",particle[0].Data()));
    tree->Branch(Form("fInvMass%s",particle[1].Data()),&fTreeVariableInvMassOmegac[1],Form("fInvMass%s/F",particle[1].Data()));
    for(int i=0; i<3; i++){
        tree->Branch(Form("fd0%s",particle[i].Data()),&fTreeVariabled0rphiOmegac[i],Form("fd0%s/F",particle[i].Data()));
        tree->Branch(Form("fPt%s",particle[i].Data()),&fTreeVariablePtOmegac[i],Form("fPt%s/F",particle[i].Data()));
        tree->Branch(Form("fEta%s",particle[i].Data()),&fTreeVariableEtaOmegac[i],Form("fEta%s/F",particle[i].Data()));
        tree->Branch(Form("fPhi%s",particle[i].Data()),&fTreeVariablePhiOmegac[i],Form("fPhi%s/F",particle[i].Data()));
        tree->Branch(Form("fRap%s",particle[i].Data()),&fTreeVariableRapOmegac[i],Form("fRap%s/F",particle[i].Data()));
        if(fIsMCSignalProd){ //variables for efficiency
            tree->Branch(Form("fGenPt%s",particle[i].Data()),&fTreeVariableGenPtOmegac[i],Form("fGenPt%s/F",particle[i].Data()));
            tree->Branch(Form("fGenEta%s",particle[i].Data()),&fTreeVariableGenEtaOmegac[i],Form("fGenEta%s/F",particle[i].Data()));
            tree->Branch(Form("fGenPhi%s",particle[i].Data()),&fTreeVariableGenPhiOmegac[i],Form("fGenPhi%s/F",particle[i].Data()));
            tree->Branch(Form("fGenRap%s",particle[i].Data()),&fTreeVariableGenRapOmegac[i],Form("fGenRap%s/F",particle[i].Data()));
            tree->Branch(Form("fGenRxy%s",particle[i].Data()),&fTreeVariableGenRxyOmegac[i],Form("fGenRxy%s/F",particle[i].Data()));
        }
        
    }
    tree->Branch("fIsSignal",&fIsSignalOmegac,"fIsSignal/O");
    
    return tree;
}
//________________________________________________________________________
R5Detector* AliAnalysisTaskSEOmegacccToOmega3Pi::CreateDetector(){
    
    AliESDtrack::OnlineMode(kTRUE); // to avoid friend track creation
    R5Detector* det = new R5Detector("ALICE","ITS");
    
    det->SetPropagateToOrigin(kTRUE); // if we want all tracks to be propagated to DCA to 0/0/0.
    
    det->SetBField(1.);
    // new ideal Pixel properties?
    Double_t x0IB     = 0.001;
    Double_t x0OB     = 0.005;
    Double_t xRho     = 0.;
    Double_t resRPhiIB     = 0.0001;
    Double_t resZIB        = 0.0001;
    Double_t resRPhiOB     = 0.0005;
    Double_t resZOB        = 0.0005;
    Double_t eff           = 0.98;
    //
    // select Z span in such a way to have +-1 unit eta coverage for vertex at 2sigmaZ (~12cm) from nominal IP
    // i.e. Zmax >= 12 + R/tan( 2*atan(exp(-1.)) ) = 12 + R/0.851
    
    det->AddLayer((char*)"vertex",  0.0,  0.1, 0, 0); // dummy vertex for matrix calculation
    
    det->AddLayer((char*)"bpipe",   1.6,  200., 0.0022);
    /* |eta|<1
     det->AddLayer((char*)"ddd1",    1.8,  21.0, x0IB, xRho, resRPhiIB, resZIB,eff);
     det->AddLayer((char*)"ddd2",    2.8,  21.0, x0IB, xRho, resRPhiIB, resZIB,eff);
     det->AddLayer((char*)"ddd3",    3.8,  21.0, x0IB, xRho, resRPhiIB, resZIB,eff);
     det->AddLayer((char*)"ddd3a",   8.0,  21.0, x0IB, xRho, resRPhiOB, resZOB,eff);
     det->AddLayer((char*)"ddd4",   20.0,  42.0, x0OB, xRho, resRPhiOB, resZOB,eff);
     det->AddLayer((char*)"ddd5",   25.0,  42.0, x0OB, xRho, resRPhiOB, resZOB,eff);
     
     //det->AddLayer((char*)"ddd6",  35.0, 80.0, x0OB, xRho, resRPhiOB, resZOB,eff);
     det->AddLayer((char*)"ddd7",   40.0,  80.0, x0OB, xRho, resRPhiOB, resZOB,eff);
     det->AddLayer((char*)"ddd8",   55.0,  80.0, x0OB, xRho, resRPhiOB, resZOB,eff);
     
     //  det->AddLayer((char*)"dddZ",  90., 130., x0OB, xRho, resRPhiOB, resZOB,eff);
     det->AddLayer((char*)"dddY",   80.0, 130.0, x0OB, xRho, resRPhiOB, resZOB,eff);
     det->AddLayer((char*)"dddX",  100.0, 130.0, x0OB, xRho, resRPhiOB, resZOB,eff);
     */
    //|eta|<2
    det->AddLayer((char*)"ddd1",    1.8,  63.0, x0IB, xRho, resRPhiIB, resZIB,eff);
    det->AddLayer((char*)"ddd2",    2.8,  63.0, x0IB, xRho, resRPhiIB, resZIB,eff);
    det->AddLayer((char*)"ddd3",    3.8,  63.0, x0IB, xRho, resRPhiIB, resZIB,eff);
    det->AddLayer((char*)"ddd3a",   8.0,  63.0, x0IB, xRho, resRPhiOB, resZOB,eff);
    det->AddLayer((char*)"ddd4",   20.0,  126.0, x0OB, xRho, resRPhiOB, resZOB,eff);
    det->AddLayer((char*)"ddd5",   25.0,  126.0, x0OB, xRho, resRPhiOB, resZOB,eff);
    
    //det->AddLayer((char*)"ddd6",  35.0, 80.0, x0OB, xRho, resRPhiOB, resZOB,eff);
    det->AddLayer((char*)"ddd7",   40.0,  240.0, x0OB, xRho, resRPhiOB, resZOB,eff);
    det->AddLayer((char*)"ddd8",   55.0,  240.0, x0OB, xRho, resRPhiOB, resZOB,eff);
    
    //  det->AddLayer((char*)"dddZ",  90., 130., x0OB, xRho, resRPhiOB, resZOB,eff);
    det->AddLayer((char*)"dddY",   80.0, 390.0, x0OB, xRho, resRPhiOB, resZOB,eff);
    det->AddLayer((char*)"dddX",  100.0, 390.0, x0OB, xRho, resRPhiOB, resZOB,eff);
    
    //det->Print("opt");
    
    return det;
    
    
    //rescale second param by facto3 --> eta+-2
}
