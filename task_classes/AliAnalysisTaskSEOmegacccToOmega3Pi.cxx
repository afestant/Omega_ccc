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

#include "AliRecoDecayOmegac.h"
#include "AliRecoDecayOmegacc.h"
#include "AliRecoDecayOmegaccc.h"

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
fPrimVtx(0x0),
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
fTreeGenOmegaccc(0x0),
fOmegacCand(0x0),
fOmegaccCand(0x0),
fOmegacccCand(0x0),
fTreeRecoTracks(0x0),
fTreeCutVarOmegac(0x0),
fTreeCutVarOmegacc(0x0),
fTreeCutVarOmegaccc(0x0),
fCasc(0x0),
fPosTrackCasc(0x0),
fNegTrackCasc(0x0),
fBachTrackCasc(0x0),
fEsdTr1(0x0),
fEsdTr2(0x0),
fEsdTr3(0x0),
fVtxOmegac(0x0),
fVtxOmegacc(0x0),
fVtxOmegaccc(0x0),
fCascTrackParam(0x0),
fOmegacTrackParam(0x0),
fOmegaccTrackParam(0x0),
fOmegacccTrackParam(0x0),
fIdxPosCasc(-99999),
fIdxNegCasc(-99999),
fIdxBachCasc(-99999),
fIdxTrack1(-99999),
fIdxTrack2(-99999),
fIdxTrack3(-99999),
fCascInvMass(0.),
fCascCharge(0),
fmcPosCascDghter(0x0),
fmcNegCascDghter(0x0),
fmcBachCascDghter(0x0),
fmcTrack1(0x0),
fmcTrack2(0x0),
fmcTrack3(0x0),
flblPosCasc(-99999),
flblNegCasc(-99999),
flblBachCasc(-99999),
flblTrack1(-99999),
flblTrack2(-99999),
flblTrack3(-99999),
flblCasc(-99999),
flblV0(-99999),
flblOmegac(-99999),
flblOmegacc(-99999),
flblOmegaccc(-99999),
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
fNHitsAssigned(0),
fParticlePdg(0),
fMotherPdg(0),
fParticleVarPdg(-99),
fParticleVarPdgMoth(-99),
fParticleVarPt(0.),
fParticleVarP(0.),
fParticleVarEta(0.),
fParticleVarRap(0.),
fParticleVarPhi(0.),
fParticleVarX(0.),
fParticleVarY(0.),
fParticleVarZ(0.),
fParticleVarRxy(0.),
fParticleVarNhitsAssigned(-99),
fParticleVarNhitsReco(-99),
fParticleVarIsReco(false),
fTreeReconstruction(0x0),
fTreeGenCascV0Reco(0x0),
fTreeGenV0Reco(0x0),
fTreeGenVarCascV0RecoInvMass(0.),
fTreeGenVarV0RecoInvMass(0.)
{
    /// Default constructor
    for(Int_t i=0; i<11; i++){
        for(Int_t j=0; j<5; j++){
            fTreeGenVarOmegaccc[i][j]=0.;
        }
        fTreeGenVarOmegacccNRHits[i]=-1;
        fTreeGenVarOmegacccPDG[i]=-1;
        fTreeVariablePt[i]=0.;
        fTreeVariableEta[i]=0.;
        fTreeVariablePhi[i]=0.;
        fTreeVariableRap[i]=0.;
        fTreeVariableGenPt[i]=0.;
        fTreeVariableGenEta[i]=0.;
        fTreeVariableGenPhi[i]=0.;
        fTreeVariableGenRap[i]=0.;
        fTreeVariableGenRxy[i]=0.;
        if(i<3){
            fTreeVariableImpParRPhi[i]=0.;
            fTreeVariableImpParZ[i]=0.;
        }
        if(i<3){
            fTreeVariableDecVtxChi2Ndf[i]=0.;
            fTreeVariableCosPointingAngle[i]=0.;
            fTreeVariableCosPointingAngleXY[i]=0.;
            fTreeVariableDecayLength[i]=0.;
            fTreeVariableDecayLengthXY[i]=0.;
            fTreeVariableNormDecayLength[i]=0.;
            fTreeVariableNormDecayLengthXY[i]=0.;
            fTreeVariableInvMass[i]=0.;
            fIsSignal[i]=false;
        }
    }
    
    for(int j=0; j<5; j++){
        fTreeGenVarCascV0RecoPDG[j]=0.;
        for(int k=0; k<5; k++){
            fTreeGenVarCascV0Reco[j][k]=0.;
        }
    }
    for(int j=0; j<3; j++){
        fTreeGenVarV0RecoPDG[j]=0.;
        for(int k=0; k<5; k++){
            fTreeGenVarV0Reco[j][k]=0.;
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
    fOmegacCuts[6]=5.;          //max chi2/ndf vtx
    
    //Omegacc
    fOmegaccCuts[0]=0.05;//0.1;     //inv mass window
    fOmegaccCuts[1]=-9999.;         //pt min
    fOmegaccCuts[2]=-9999.;         //min decL
    fOmegaccCuts[3]=-9999.;         //min decLXY
    fOmegaccCuts[4]=-9999.;        //min imp par cbaryon
    fOmegaccCuts[5]=-9999.;        //min imp par track
    fOmegaccCuts[6]=5.;          //max chi2/ndf vtx
    
    //Omegaccc
    fOmegacccCuts[0]=0.05;//0.1;     //inv mass window
    fOmegacccCuts[1]=-9999.;         //pt min
    fOmegacccCuts[2]=-9999.;         //min decL
    fOmegacccCuts[3]=-9999.;         //min decLXY
    fOmegacccCuts[4]=-9999.;        //min imp par cbaryon
    fOmegacccCuts[5]=-9999.;        //min imp par track
    fOmegacccCuts[6]=5.;          //max chi2/ndf vtx
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
fPrimVtx(0x0),
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
fTreeGenOmegaccc(0x0),
fOmegacCand(0x0),
fOmegaccCand(0x0),
fOmegacccCand(0x0),
fTreeRecoTracks(0x0),
fTreeCutVarOmegac(0x0),
fTreeCutVarOmegacc(0x0),
fTreeCutVarOmegaccc(0x0),
fCasc(0x0),
fPosTrackCasc(0x0),
fNegTrackCasc(0x0),
fBachTrackCasc(0x0),
fEsdTr1(0x0),
fEsdTr2(0x0),
fEsdTr3(0x0),
fVtxOmegac(0x0),
fVtxOmegacc(0x0),
fVtxOmegaccc(0x0),
fCascTrackParam(0x0),
fOmegacTrackParam(0x0),
fOmegaccTrackParam(0x0),
fOmegacccTrackParam(0x0),
fIdxPosCasc(-99999),
fIdxNegCasc(-99999),
fIdxBachCasc(-99999),
fIdxTrack1(-99999),
fIdxTrack2(-99999),
fIdxTrack3(-99999),
fCascInvMass(0.),
fCascCharge(0),
fmcPosCascDghter(0x0),
fmcNegCascDghter(0x0),
fmcBachCascDghter(0x0),
fmcTrack1(0x0),
fmcTrack2(0x0),
fmcTrack3(0x0),
flblPosCasc(-99999),
flblNegCasc(-99999),
flblBachCasc(-99999),
flblTrack1(-99999),
flblTrack2(-99999),
flblTrack3(-99999),
flblCasc(-99999),
flblV0(-99999),
flblOmegac(-99999),
flblOmegacc(-99999),
flblOmegaccc(-99999),
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
fNHitsAssigned(0),
fParticlePdg(0),
fMotherPdg(0),
fParticleVarPdg(-99),
fParticleVarPdgMoth(-99),
fParticleVarPt(0.),
fParticleVarP(0.),
fParticleVarEta(0.),
fParticleVarRap(0.),
fParticleVarPhi(0.),
fParticleVarX(0.),
fParticleVarY(0.),
fParticleVarZ(0.),
fParticleVarRxy(0.),
fParticleVarNhitsAssigned(-99),
fParticleVarNhitsReco(-99),
fParticleVarIsReco(false),
fTreeReconstruction(0x0),
fTreeGenCascV0Reco(0x0),
fTreeGenV0Reco(0x0),
fTreeGenVarCascV0RecoInvMass(0.),
fTreeGenVarV0RecoInvMass(0.)
{
    /// Default constructor
    for(Int_t i=0; i<11; i++){
        for(Int_t j=0; j<5; j++){
            fTreeGenVarOmegaccc[i][j]=0.;
        }
        fTreeGenVarOmegacccNRHits[i]=-1;
        fTreeGenVarOmegacccPDG[i]=-1;
        fTreeVariablePt[i]=0.;
        fTreeVariableEta[i]=0.;
        fTreeVariablePhi[i]=0.;
        fTreeVariableRap[i]=0.;
        fTreeVariableGenPt[i]=0.;
        fTreeVariableGenEta[i]=0.;
        fTreeVariableGenPhi[i]=0.;
        fTreeVariableGenRap[i]=0.;
        fTreeVariableGenRxy[i]=0.;
        if(i<3){
            fTreeVariableImpParRPhi[i]=0.;
            fTreeVariableImpParZ[i]=0.;
        }
        if(i<3){
            fTreeVariableDecVtxChi2Ndf[i]=0.;
            fTreeVariableCosPointingAngle[i]=0.;
            fTreeVariableCosPointingAngleXY[i]=0.;
            fTreeVariableDecayLength[i]=0.;
            fTreeVariableDecayLengthXY[i]=0.;
            fTreeVariableNormDecayLength[i]=0.;
            fTreeVariableNormDecayLengthXY[i]=0.;
            fTreeVariableInvMass[i]=0.;
            fIsSignal[i]=false;
        }
    }
    for(int j=0; j<5; j++){
        fTreeGenVarCascV0RecoPDG[j]=0.;
        for(int k=0; k<5; k++){
            fTreeGenVarCascV0Reco[j][k]=0.;
        }
    }
    for(int j=0; j<3; j++){
        fTreeGenVarV0RecoPDG[j]=0.;
        for(int k=0; k<5; k++){
            fTreeGenVarV0Reco[j][k]=0.;
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
    fOmegacCuts[6]=5.;          //max chi2/ndf vtx
    
    //Omegacc
    fOmegaccCuts[0]=0.05;//0.1;     //inv mass window
    fOmegaccCuts[1]=-9999.;         //pt min
    fOmegaccCuts[2]=-9999.;         //min decL
    fOmegaccCuts[3]=-9999.;         //min decLXY
    fOmegaccCuts[4]=-9999.;        //min imp par cbaryon
    fOmegaccCuts[5]=-9999.;        //min imp par track
    fOmegaccCuts[6]=5.;          //max chi2/ndf vtx
    
    //Omegaccc
    fOmegacccCuts[0]=0.05;//0.1;     //inv mass window
    fOmegacccCuts[1]=-9999.;         //pt min
    fOmegacccCuts[2]=-9999.;         //min decL
    fOmegacccCuts[3]=-9999.;         //min decLXY
    fOmegacccCuts[4]=-9999.;        //min imp par cbaryon
    fOmegacccCuts[5]=-9999.;        //min imp par track
    fOmegacccCuts[6]=5.;          //max chi2/ndf vtx
    
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
    DefineOutput(11,TTree::Class());
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
    if (fPrimVtx){
        delete fPrimVtx;
        fPrimVtx = 0x0;
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
    if (fTreeGenOmegaccc){
        delete fTreeGenOmegaccc;
        fTreeGenOmegaccc = 0x0;
    }
    if (fTreeRecoTracks){
        delete fTreeRecoTracks;
        fTreeRecoTracks = 0x0;
    }
    if (fTreeCutVarOmegac){
        delete fTreeCutVarOmegac;
        fTreeCutVarOmegac = 0x0;
    }
    if (fTreeCutVarOmegacc){
        delete fTreeCutVarOmegacc;
        fTreeCutVarOmegacc = 0x0;
    }
    if (fTreeCutVarOmegaccc){
        delete fTreeCutVarOmegaccc;
        fTreeCutVarOmegaccc = 0x0;
    }
    if (fTreeReconstruction){
        delete fTreeReconstruction;
        fTreeReconstruction = 0x0;
    }
    if (fTreeGenCascV0Reco){
        delete fTreeGenCascV0Reco;
        fTreeGenCascV0Reco = 0x0;
    }
    if (fTreeGenV0Reco){
        delete fTreeGenV0Reco;
        fTreeGenV0Reco = 0x0;
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
    fTreeCutVarOmegaccc = (TTree*)BuildTreeCutVar("TreeCutVarOmegaccc","TreeCutVarOmegaccc", false, false, true);
    fTreeCutVarOmegaccc->SetAutoFlush(100000);
    if(fIsMCSignalProd){
        OpenFile(5);
        fTreeCutVarOmegac = (TTree*)BuildTreeCutVar("TreeCutVarOmegac","TreeCutVarOmegac", true, false, false);
        fTreeCutVarOmegac->SetAutoFlush(100000);
        OpenFile(6);
        fTreeCutVarOmegacc = (TTree*)BuildTreeCutVar("TreeCutVarOmegacc","TreeCutVarOmegacc", false, true, false);
        fTreeCutVarOmegacc->SetAutoFlush(100000);
        OpenFile(7);
        fTreeGenOmegaccc  = (TTree*)BuildTreeOmegacccGen("TreeGenOmegaccc","TreeGenOmegaccc");
        fTreeGenOmegaccc->SetAutoFlush(100000);
        OpenFile(8);
        fTreeGenCascV0Reco = (TTree*)BuildTreeCascV0Reco("TreeGenCascV0Reco","TreeGenCascV0Reco");
        fTreeGenCascV0Reco->SetAutoFlush(100000);
        OpenFile(9);
        fTreeGenV0Reco = (TTree*)BuildTreeV0Reco("TreeGenV0Reco","TreeGenV0Reco");
        fTreeGenV0Reco->SetAutoFlush(100000);
        OpenFile(10);
        fTreeReconstruction  = (TTree*)BuildTreeReconstruction("TreeReconstruction","TreeReconstruction");
        fTreeReconstruction->SetAutoFlush(100000);
        OpenFile(11);
        fTreeRecoTracks = (TTree*)BuildTreeRecoTracks("TreeRecoTracks","TreeRecoTracks");
        fTreeRecoTracks->SetAutoFlush(100000);
        
    }
    
    // Post the data
    PostData(1,fNentries);
    PostData(2,fOutputGen);
    PostData(3,fOutputReco);
    PostData(4,fTreeCutVarOmegaccc);
    if(fIsMCSignalProd){
        PostData(5,fTreeCutVarOmegac);
        PostData(6,fTreeCutVarOmegacc);
        PostData(7,fTreeGenOmegaccc);
        PostData(8,fTreeGenCascV0Reco);
        PostData(9,fTreeGenV0Reco);
        PostData(10,fTreeReconstruction);
        PostData(11,fTreeRecoTracks);
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
    fPrimVtx   = (AliESDVertex*)fEvent->GetPrimaryVertexTracks();
    Double_t sigma[3]={0.,0.,0.};
    Double_t position[3]={0.,0.,0.};
    fPrimVtx->GetSigmaXYZ(sigma);
    fPrimVtx->GetXYZ(position);
    if(fIsMCSignalProd){
        FillGenTree();
        FillRecoTrackTree();
    }
    
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
    
    
    MakeCandidates();
    
    
    
    
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
    Printf("Nevents analysed = %d", fEvtCount);
    return;
    
}
//________________________________________________________________________
int AliAnalysisTaskSEOmegacccToOmega3Pi::MakeCandidates(){
    
    
    //Printf("\n\n\n ********************************* MakeCandidates");
    Double_t xPrimaryVertex=fPrimVtx->GetX();
    Double_t yPrimaryVertex=fPrimVtx->GetY();
    Double_t zPrimaryVertex=fPrimVtx->GetZ();
    
    // get number of cascades
    Long_t nCascades = fEvent->GetNumberOfCascades();
    if(nCascades==0) return 0;
    
    // loop on cascades
    for(Int_t icasc=0; icasc<nCascades; icasc++){
        fCasc = (AliESDcascade*)fEvent->GetCascade(icasc);
        if(!fCasc) continue;
        
        fIdxPosCasc         = fCasc->GetPindex();
        fIdxNegCasc         = fCasc->GetNindex();
        fIdxBachCasc        = fCasc->GetBindex();
        if(!fIdxPosCasc || !fIdxNegCasc || !fIdxBachCasc) continue;
        if(fIdxBachCasc == fIdxNegCasc) {
            continue;
        }
        if(fIdxBachCasc == fIdxPosCasc) {
            continue;
        }
        fPosTrackCasc        = (AliESDtrack*)fEvent->GetTrack( fIdxPosCasc );
        fNegTrackCasc        = (AliESDtrack*)fEvent->GetTrack( fIdxNegCasc );
        fBachTrackCasc       = (AliESDtrack*)fEvent->GetTrack( fIdxBachCasc );
        if (!fPosTrackCasc || !fNegTrackCasc || !fBachTrackCasc ) {
            Printf("ERROR: Could not retrieve one of the 3 ESD daughter tracks of the cascade ...");
            continue;
        }
        fCascCharge = fBachTrackCasc->Charge();
        //cut on cascade invariant mass
        Double_t lV0quality = 0.;
        if(fCascCharge<0){
            fCasc->ChangeMassHypothesis(lV0quality , 3334);
            fCascInvMass = fCasc->GetEffMassXi();
        }
        else {
            fCasc->ChangeMassHypothesis(lV0quality , -3334);
            fCascInvMass = fCasc->GetEffMassXi();
        }
        if(TMath::Abs(fCascInvMass-TDatabasePDG::Instance()->GetParticle(3334)->Mass())>0.022) continue;
        //get V0 from cascade
        Int_t idxV0FromCascade = -1;
        for(int iv0=0; iv0<fEvent->GetNumberOfV0s(); iv0++){
            fV0 = fEvent->GetV0(iv0);
            Int_t posCurrentV0 = fV0->GetPindex();
            Int_t negCurrentV0 = fV0->GetNindex();
            if (posCurrentV0==fIdxPosCasc && negCurrentV0==fIdxNegCasc) {
                idxV0FromCascade = iv0;
                break;
            }
        }
        if(idxV0FromCascade < 0){
            printf("Cascade - no matching for the V0 (index V0 = -1) ! Skip ... \n");
            continue;
        }
        // loop on tracks
        // get number of tracks
        Long_t nentr = (Int_t)fEvent->GetNumberOfTracks();
        // omegac step
        for(Int_t i=0; i<nentr; i++){
            fEsdTr1 = (AliESDtrack*)fEvent->GetTrack(i);
            fIdxTrack1 = fEsdTr1->GetID();
            if(!fIdxTrack1) continue;
            if(fIdxTrack1 == fIdxNegCasc){
                continue;
            }
            if(fIdxTrack1 == fIdxPosCasc){
                continue;
            }
            if(fIdxTrack1 == fIdxBachCasc){
                continue;
            }
            //single track cuts
            Int_t esdtrCharge1 = fEsdTr1->Charge();
            if(esdtrCharge1 == fCascCharge) continue;
            ULong_t status = fEsdTr1->GetStatus();
            if ((status&AliESDtrack::kITSrefit)==0)
                if ((status&AliESDtrack::kTPCrefit)==0) continue;
            if(fEsdTr1->Pt()<0.5) continue;
            Double_t dispersion=0.;
            fVtxOmegac = CallReconstructSecondaryVertexOmegac(dispersion);
            if(!fVtxOmegac) {
                continue;
            }
            fOmegacCand = new AliRecoDecayOmegac(*fCasc,*fEsdTr1,*fVtxOmegac,*fV0,*fBachTrackCasc);
            fOmegacCand->SetMagneticField(fBzkG);
            bool isselOmegac = FillHistoOmegac();
            if(!isselOmegac) {
                //Printf("Omegac not sel");
                continue;
            }
            // omegacc step
            for(Int_t j=0; j<nentr; j++){
                fEsdTr2 = (AliESDtrack*)fEvent->GetTrack(j);
                fIdxTrack2 = fEsdTr2->GetID();
                if(!fIdxTrack2) continue;
                if(fIdxTrack2 == fIdxNegCasc){
                    continue;
                }
                if(fIdxTrack2 == fIdxPosCasc){
                    continue;
                }
                if(fIdxTrack2 == fIdxBachCasc){
                    continue;
                }
                if(fIdxTrack2 == fIdxTrack1){
                    continue;
                }
                //single track cuts
                Int_t esdtr2Charge = fEsdTr2->Charge();
                if(esdtr2Charge != esdtrCharge1) continue;
                status = fEsdTr2->GetStatus();
                if ((status&AliESDtrack::kITSrefit)==0)
                    if ((status&AliESDtrack::kTPCrefit)==0) continue;
                if(fEsdTr2->Pt()<0.5) continue;
                Double_t dispersion=0.;
                fVtxOmegacc = CallReconstructSecondaryVertexOmegacc(dispersion);
                if(!fVtxOmegacc) {
                    continue;
                }
                fOmegaccCand = new AliRecoDecayOmegacc(*fOmegacCand,*fEsdTr2,*fVtxOmegacc);
                fOmegaccCand->SetMagneticField(fBzkG);
                bool isselOmegacc = FillHistoOmegacc();
                if(!isselOmegacc) {
                    //Printf("Omegacc not sel");
                    continue;
                }
                // omegaccc step
                for(Int_t k=0; k<nentr; k++){
                    fEsdTr3 = (AliESDtrack*)fEvent->GetTrack(k);
                    fIdxTrack3 = fEsdTr3->GetID();
                    if(!fIdxTrack3) continue;
                    if(fIdxTrack3 == fIdxNegCasc){
                        continue;
                    }
                    if(fIdxTrack3 == fIdxPosCasc){
                        continue;
                    }
                    if(fIdxTrack3 == fIdxBachCasc){
                        continue;
                    }
                    if(fIdxTrack3 == fIdxTrack1){
                        continue;
                    }
                    if(fIdxTrack3 == fIdxTrack2){
                        continue;
                    }
                    //single track cuts
                    Int_t esdtr3Charge = fEsdTr3->Charge();
                    if(esdtr3Charge != esdtr2Charge) continue;
                    status = fEsdTr3->GetStatus();
                    if ((status&AliESDtrack::kITSrefit)==0)
                        if ((status&AliESDtrack::kTPCrefit)==0) continue;
                    if(fEsdTr3->Pt()<0.5) continue;
                    Double_t dispersion=0.;
                    //Printf("\n********************************* CallReconstructSecondaryVertexOmegaccc");
                    //gObjectTable->Print();
                    fVtxOmegaccc = CallReconstructSecondaryVertexOmegaccc(dispersion);
                    if(!fVtxOmegaccc) {
                        continue;
                    }
                    fOmegacccCand = new AliRecoDecayOmegaccc(*fOmegaccCand,*fEsdTr3,*fVtxOmegaccc);
                    fOmegacccCand->SetMagneticField(fBzkG);
                    bool isselOmegaccc = FillHistoOmegaccc();
                    //if(!isselOmegaccc)  {
                    //}
                    delete fVtxOmegaccc;  fVtxOmegaccc=NULL;
                    delete fOmegacccCand;   fOmegacccCand=NULL;
                    //Printf("\n********************************* END CallReconstructSecondaryVertexOmegaccc");
                    //gObjectTable->Print();
                }
                delete fVtxOmegacc;    fVtxOmegacc=NULL;
                delete fOmegaccCand;   fOmegaccCand=NULL;
            }//end second loop on tracks
            delete fVtxOmegac;    fVtxOmegac=NULL;
            delete fOmegacCand;   fOmegacCand=NULL;
        }//end first loop on tracks
        
    }
    
    return 1;
    
    
}
//_________________________________________
bool AliAnalysisTaskSEOmegacccToOmega3Pi::FillHistoOmegac() {
    //MC
    
    fOmegacCand->FillCand(*fPrimVtx);
    
    //setting tree variables
    fTreeVariableDecVtxChi2Ndf[0]         = fOmegacCand->GetDecVtxChi2();
    fTreeVariableDecayLength[0]           = fOmegacCand->DecayLength(fPrimVtx, fVtxOmegac);
    fTreeVariableDecayLengthXY[0]         = fOmegacCand->DecayLengthXY(fPrimVtx, fVtxOmegac);
    
    fTreeVariableInvMass[0] = fOmegacCand->GetInvMass();
    
    fTreeVariableImpParRPhi[0] = fOmegacCand->GetImpParRPhiCand();
    fTreeVariableImpParRPhi[3] = fOmegacCand->GetImpParRPhiBach();
    
    fTreeVariableImpParZ[0] = fOmegacCand->GetImpParZCand();
    fTreeVariableImpParZ[3] = fOmegacCand->GetImpParZBach();
    
    fIsSignal[0] = fOmegacCand->CheckIsSignal(fEvent, fMcEvent);
    
    fTreeVariablePt[6]  = fOmegacCand->GetPt();
    fTreeVariableEta[6] = fOmegacCand->GetEta();
    fTreeVariableRap[6] = fOmegacCand->GetRap();
    fTreeVariablePhi[6] = fOmegacCand->GetPhi();
    
    fTreeVariablePt[5]  = fEsdTr1->Pt();
    fTreeVariableEta[5] = fEsdTr1->Eta();
    fTreeVariableRap[5] = fEsdTr1->Y();
    fTreeVariablePhi[5] = fEsdTr1->Phi();
    
    fTreeVariablePt[4]  = fCasc->Pt();
    fTreeVariableEta[4] = fCasc->Eta();
    fTreeVariableRap[4] = fCasc->Y();
    fTreeVariablePhi[4] = fCasc->Phi();
    
    fTreeVariablePt[3]  = fBachTrackCasc->Pt();
    fTreeVariableEta[3] = fBachTrackCasc->Eta();
    fTreeVariableRap[3] = fBachTrackCasc->Y();
    fTreeVariablePhi[3] = fBachTrackCasc->Phi();
    
    fTreeVariablePt[2]  = fV0->Pt();
    fTreeVariableEta[2] = fV0->Eta();
    fTreeVariableRap[2] = fV0->Y();
    fTreeVariablePhi[2] = fV0->Phi();
    
    fTreeVariablePt[1]  = fPosTrackCasc->Pt();
    fTreeVariableEta[1] = fPosTrackCasc->Eta();
    fTreeVariableRap[1] = fPosTrackCasc->Y();
    fTreeVariablePhi[1] = fPosTrackCasc->Phi();
    
    fTreeVariablePt[0]  = fNegTrackCasc->Pt();
    fTreeVariableEta[0] = fNegTrackCasc->Eta();
    fTreeVariableRap[0] = fNegTrackCasc->Y();
    fTreeVariablePhi[0] = fNegTrackCasc->Phi();
    
    //MC
    if(fIsMCSignalProd){
        flblPosCasc  = fPosTrackCasc->GetLabel();
        flblNegCasc  = fNegTrackCasc->GetLabel();
        flblBachCasc = fBachTrackCasc->GetLabel();
        flblTrack1   = fEsdTr1->GetLabel();
        fmcPosCascDghter  = fMcEvent->Particle( flblPosCasc );
        fmcNegCascDghter  = fMcEvent->Particle( flblNegCasc );
        fmcBachCascDghter = fMcEvent->Particle( flblBachCasc );
        fmcTrack1         = fMcEvent->Particle( flblTrack1 );
        flblCasc          = fmcBachCascDghter->GetFirstMother();
        flblV0            = fmcPosCascDghter->GetFirstMother();
        //flblOmegac        = fmcTrack1->GetFirstMother();
        flblOmegac        = fOmegacCand->GetCandMCLabel();
        
        //Printf("*********** AliAnalysisTaskSEOmegacccToOmega3Pi::FillHistoOmegac ***********");
        //Printf("lblpTrackCasc = %d lblnTrackCasc = %d lblbachTrackCasc = %d lblbachTrackCascC = %d",flblPosCasc,flblNegCasc,flblBachCasc,flblTrack1);
        
        if(flblOmegac>-1){
            fTreeVariableGenPt[6]  = ((TParticle*)fMcEvent->Particle( flblOmegac ))->Pt();
            fTreeVariableGenEta[6] = ((TParticle*)fMcEvent->Particle( flblOmegac ))->Eta();
            fTreeVariableGenPhi[6] = ((TParticle*)fMcEvent->Particle( flblOmegac ))->Phi();
            fTreeVariableGenRap[6] = ((TParticle*)fMcEvent->Particle( flblOmegac ))->Y();
            fTreeVariableGenRxy[6] = ((TParticle*)fMcEvent->Particle( flblOmegac ))->R();
        }
        if(flblCasc>-1){
            fTreeVariableGenPt[4]  = ((TParticle*)fMcEvent->Particle( flblCasc ))->Pt();
            fTreeVariableGenEta[4] = ((TParticle*)fMcEvent->Particle( flblCasc ))->Eta();
            fTreeVariableGenPhi[4] = ((TParticle*)fMcEvent->Particle( flblCasc ))->Phi();
            fTreeVariableGenRap[4] = ((TParticle*)fMcEvent->Particle( flblCasc ))->Y();
            fTreeVariableGenRxy[4] = ((TParticle*)fMcEvent->Particle( flblCasc ))->R();
        }
        if(flblV0>-1){
            fTreeVariableGenPt[2]  = ((TParticle*)fMcEvent->Particle( flblV0 ))->Pt();
            fTreeVariableGenEta[2] = ((TParticle*)fMcEvent->Particle( flblV0 ))->Eta();
            fTreeVariableGenPhi[2] = ((TParticle*)fMcEvent->Particle( flblV0 ))->Phi();
            fTreeVariableGenRap[2] = ((TParticle*)fMcEvent->Particle( flblV0 ))->Y();
            fTreeVariableGenRxy[2] = ((TParticle*)fMcEvent->Particle( flblV0 ))->R();
        }
        fTreeVariableGenPt[3]  = fmcBachCascDghter->Pt();
        fTreeVariableGenEta[3] = fmcBachCascDghter->Eta();
        fTreeVariableGenPhi[3] = fmcBachCascDghter->Phi();
        fTreeVariableGenRap[3] = fmcBachCascDghter->Y();
        fTreeVariableGenRxy[3] = fmcBachCascDghter->R();
        
        fTreeVariableGenPt[5]  = fmcTrack1->Pt();
        fTreeVariableGenEta[5] = fmcTrack1->Eta();
        fTreeVariableGenPhi[5] = fmcTrack1->Phi();
        fTreeVariableGenRap[5] = fmcTrack1->Y();
        fTreeVariableGenRxy[5] = fmcTrack1->R();
        
        fTreeVariableGenPt[1]  = fmcPosCascDghter->Pt();
        fTreeVariableGenEta[1] = fmcPosCascDghter->Eta();
        fTreeVariableGenPhi[1] = fmcPosCascDghter->Phi();
        fTreeVariableGenRap[1] = fmcPosCascDghter->Y();
        fTreeVariableGenRxy[1] = fmcPosCascDghter->R();
        
        fTreeVariableGenPt[0]  = fmcNegCascDghter->Pt();
        fTreeVariableGenEta[0] = fmcNegCascDghter->Eta();
        fTreeVariableGenPhi[0] = fmcNegCascDghter->Phi();
        fTreeVariableGenRap[0] = fmcNegCascDghter->Y();
        fTreeVariableGenRxy[0] = fmcNegCascDghter->R();
    }
    
    //apply cuts
    bool issel = fOmegacCand->IsSelected(fOmegacCuts);
    if(issel){
        if(fIsMCSignalProd){
            if(fIsSignal[0]==true){
                fTreeCutVarOmegac->Fill();
            }
        }
        //else fTreeCutVarOmegac->Fill();
    }
    
    
    return issel;
    
}
//_________________________________________
bool AliAnalysisTaskSEOmegacccToOmega3Pi::FillHistoOmegacc() {
    //MC
    
    fOmegaccCand->FillCand(*fPrimVtx);
    
    //setting tree variables
    fTreeVariableDecVtxChi2Ndf[1]         = fOmegaccCand->GetDecVtxChi2();
    fTreeVariableDecayLength[1]           = fOmegaccCand->DecayLength(fPrimVtx, fVtxOmegacc);
    fTreeVariableDecayLengthXY[1]         = fOmegaccCand->DecayLengthXY(fPrimVtx, fVtxOmegacc);
    
    fTreeVariableInvMass[1] = fOmegaccCand->GetInvMass();
    
    fTreeVariableImpParRPhi[1] = fOmegaccCand->GetImpParRPhiCand();
    fTreeVariableImpParRPhi[4] = fOmegaccCand->GetImpParRPhiBach();
    
    fTreeVariableImpParZ[1] = fOmegaccCand->GetImpParZCand();
    fTreeVariableImpParZ[4] = fOmegaccCand->GetImpParZBach();
    
    fIsSignal[1] = fOmegaccCand->CheckIsSignal(fEvent, fMcEvent);
    
    fTreeVariablePt[8]  = fOmegaccCand->GetPt();
    fTreeVariableEta[8] = fOmegaccCand->GetEta();
    fTreeVariableRap[8] = fOmegaccCand->GetRap();
    fTreeVariablePhi[8] = fOmegaccCand->GetPhi();
    
    fTreeVariablePt[7]  = fEsdTr2->Pt();
    fTreeVariableEta[7] = fEsdTr2->Eta();
    fTreeVariableRap[7] = fEsdTr2->Y();
    fTreeVariablePhi[7] = fEsdTr2->Phi();
    
    //MC
    if(fIsMCSignalProd){
        flblTrack2        = fEsdTr2->GetLabel();
        fmcTrack2         = fMcEvent->Particle( flblTrack2 );
        //flblOmegacc       = fmcTrack2->GetFirstMother();
        flblOmegacc       = fOmegaccCand->GetCandMCLabel();
        
        //Printf("*********** AliAnalysisTaskSEOmegacccToOmega3Pi::FillHistoOmegacc ***********");
        //Printf("flblOmegacc = %d flblTrack2 = %d",flblOmegacc,flblTrack2);
        
        if(flblOmegacc>-1){
            fTreeVariableGenPt[8]  = ((TParticle*)fMcEvent->Particle( flblOmegacc ))->Pt();
            fTreeVariableGenEta[8] = ((TParticle*)fMcEvent->Particle( flblOmegacc ))->Eta();
            fTreeVariableGenPhi[8] = ((TParticle*)fMcEvent->Particle( flblOmegacc ))->Phi();
            fTreeVariableGenRap[8] = ((TParticle*)fMcEvent->Particle( flblOmegacc ))->Y();
            fTreeVariableGenRxy[8] = ((TParticle*)fMcEvent->Particle( flblOmegacc ))->R();
        }
        fTreeVariableGenPt[7]   = fmcTrack2->Pt();
        fTreeVariableGenEta[7]  = fmcTrack2->Eta();
        fTreeVariableGenPhi[7]  = fmcTrack2->Phi();
        fTreeVariableGenRap[7]  = fmcTrack2->Y();
        fTreeVariableGenRxy[7] = fmcTrack2->R();
    }
    
    //apply cuts
    bool issel = fOmegaccCand->IsSelected(fOmegaccCuts);
    if(issel){
        if(fIsMCSignalProd){
            if(fIsSignal[1]==true){
                fTreeCutVarOmegacc->Fill();
            }
        }
        //else fTreeCutVarOmegacc->Fill();
    }
    
    
    return issel;
    
}
//_________________________________________
bool AliAnalysisTaskSEOmegacccToOmega3Pi::FillHistoOmegaccc() {
    //MC
    
    fOmegacccCand->FillCand(*fPrimVtx);
    
    //setting tree variables
    fTreeVariableDecVtxChi2Ndf[2]             = fOmegacccCand->GetDecVtxChi2();
    fTreeVariableDecayLength[2]               = fOmegacccCand->DecayLength(fPrimVtx, fVtxOmegaccc);
    fTreeVariableDecayLengthXY[2]             = fOmegacccCand->DecayLengthXY(fPrimVtx, fVtxOmegaccc);
    fTreeVariableNormDecayLength[2]           = fOmegacccCand->NormalizedDecayLength(fPrimVtx, fVtxOmegaccc);
    fTreeVariableNormDecayLengthXY[2]         = fOmegacccCand->NormalizedDecayLengthXY(fPrimVtx, fVtxOmegaccc);
    
    Double_t pxpypz[3];
    pxpypz[0]=fOmegacccCand->GetPx();
    pxpypz[1]=fOmegacccCand->GetPy();
    pxpypz[2]=fOmegacccCand->GetPz();
    fTreeVariableCosPointingAngle[2]      = fOmegacccCand->CosPointingAngle(fPrimVtx, fVtxOmegaccc, pxpypz);
    fTreeVariableCosPointingAngleXY[2]    = fOmegacccCand->CosPointingAngleXY(fPrimVtx, fVtxOmegaccc, pxpypz);
    
    Double_t pxpypzc[3];
    pxpypzc[0]=fOmegacCand->GetPx();
    pxpypzc[1]=fOmegacCand->GetPy();
    pxpypzc[2]=fOmegacCand->GetPz();
    fTreeVariableCosPointingAngle[0]      = fOmegaccCand->CosPointingAngle(fVtxOmegacc, fVtxOmegac, pxpypzc);
    fTreeVariableCosPointingAngleXY[0]    = fOmegaccCand->CosPointingAngleXY(fVtxOmegacc, fVtxOmegac, pxpypzc);
    
    Double_t pxpypzcc[3];
    pxpypzcc[0]=fOmegaccCand->GetPx();
    pxpypzcc[1]=fOmegaccCand->GetPy();
    pxpypzcc[2]=fOmegaccCand->GetPz();
    fTreeVariableCosPointingAngle[1]      = fOmegacCand->CosPointingAngle(fVtxOmegaccc, fVtxOmegacc, pxpypzcc);
    fTreeVariableCosPointingAngleXY[1]    = fOmegacCand->CosPointingAngleXY(fVtxOmegaccc, fVtxOmegacc, pxpypzcc);
    
    fTreeVariableInvMass[2] = fOmegacccCand->GetInvMass();
    
    fTreeVariableImpParRPhi[2] = fOmegacccCand->GetImpParRPhiCand();
    fTreeVariableImpParRPhi[5] = fOmegacccCand->GetImpParRPhiBach();
    
    fTreeVariableImpParZ[2] = fOmegacccCand->GetImpParZCand();
    fTreeVariableImpParZ[5] = fOmegacccCand->GetImpParZBach();
    
    fIsSignal[2] = fOmegacccCand->CheckIsSignal(fEvent, fMcEvent);
    
    fTreeVariablePt[10]  = fOmegacccCand->GetPt();
    fTreeVariableEta[10] = fOmegacccCand->GetEta();
    fTreeVariableRap[10] = fOmegacccCand->GetRap();
    fTreeVariablePhi[10] = fOmegacccCand->GetPhi();
    
    fTreeVariablePt[9]  = fEsdTr3->Pt();
    fTreeVariableEta[9] = fEsdTr3->Eta();
    fTreeVariableRap[9] = fEsdTr3->Y();
    fTreeVariablePhi[9] = fEsdTr3->Phi();
    
    //MC
    if(fIsMCSignalProd){
        flblTrack3        = fEsdTr3->GetLabel();
        fmcTrack3         = fMcEvent->Particle( flblTrack3 );
        //flblOmegaccc      = fmcTrack3->GetFirstMother();
        flblOmegaccc      = fOmegacccCand->GetCandMCLabel();
        
        //Printf("*********** AliAnalysisTaskSEOmegacccToOmega3Pi::FillHistoOmegacc ***********");
        //Printf("flblOmegacc = %d flblTrack2 = %d",flblOmegacc,flblTrack2);
        
        if(flblOmegacc>-1){
            fTreeVariableGenPt[10]  = ((TParticle*)fMcEvent->Particle( flblOmegaccc ))->Pt();
            fTreeVariableGenEta[10] = ((TParticle*)fMcEvent->Particle( flblOmegaccc ))->Eta();
            fTreeVariableGenPhi[10] = ((TParticle*)fMcEvent->Particle( flblOmegaccc ))->Phi();
            fTreeVariableGenRap[10] = ((TParticle*)fMcEvent->Particle( flblOmegaccc ))->Y();
            fTreeVariableGenRxy[10] = ((TParticle*)fMcEvent->Particle( flblOmegaccc ))->R();
        }
        fTreeVariableGenPt[9]   = fmcTrack3->Pt();
        fTreeVariableGenEta[9]  = fmcTrack3->Eta();
        fTreeVariableGenPhi[9]  = fmcTrack3->Phi();
        fTreeVariableGenRap[9]  = fmcTrack3->Y();
        fTreeVariableGenRxy[9]  = fmcTrack3->R();
    }
    
    //apply cuts
    bool issel = fOmegacccCand->IsSelected(fOmegacccCuts);
    if(issel){
        if(fIsMCSignalProd){
            if(fIsSignal[2]==true){
                //Printf("filling Omegaccc tree signal");
                fTreeCutVarOmegaccc->Fill();
            }
        }
        else {
            //Printf("filling Omegaccc tree bkg");
            fTreeCutVarOmegaccc->Fill();
        }
    }
    
    
    return issel;
    
}
//_________________________________________
AliESDVertex* AliAnalysisTaskSEOmegacccToOmega3Pi::CallReconstructSecondaryVertexOmegac(Double_t &dispersion) {
    
    AliESDVertex *secVertex = 0x0;
    
    TObjArray *trkArray = new TObjArray(2);
    trkArray->AddAt(fEsdTr1,0);
    fCascTrackParam = GetTrackParamForCascade();
    trkArray->AddAt(fCascTrackParam,1);
    
    secVertex = ReconstructSecondaryVertex(trkArray, dispersion);

    trkArray->Clear();
    delete trkArray;  trkArray=NULL;
    return secVertex;
    
    
}
//_________________________________________
AliESDVertex* AliAnalysisTaskSEOmegacccToOmega3Pi::CallReconstructSecondaryVertexOmegacc(Double_t &dispersion) {
    
    AliESDVertex *secVertex = 0x0;
    
    TObjArray *trkArray = new TObjArray(2);
    trkArray->AddAt(fEsdTr2,0);
    AliExternalTrackParam tmp = (fOmegacCand->GetTrackParamForCand());
    fOmegacTrackParam = &tmp;
    trkArray->AddAt(fOmegacTrackParam,1);
    
    secVertex = ReconstructSecondaryVertex(trkArray, dispersion);
    
    trkArray->Clear();
    delete trkArray;  trkArray=NULL;
    return secVertex;
    
    
}
//_________________________________________
AliESDVertex* AliAnalysisTaskSEOmegacccToOmega3Pi::CallReconstructSecondaryVertexOmegaccc(Double_t &dispersion){
    //Printf("\n*************************prepare for OMEGA ccc decay vertex reco");
    AliESDVertex *secVertex = 0x0;
    
    TObjArray *trkArray = new TObjArray(2);
    trkArray->AddAt(fEsdTr3,0);
    AliExternalTrackParam tmp = (fOmegaccCand->GetTrackParamForCand());
    fOmegaccTrackParam = &tmp;
    //fOmegaccTrackParam = &(fOmegaccCand->GetTrackParamForCand());
    trkArray->AddAt(fOmegaccTrackParam,1);
    
    secVertex = ReconstructSecondaryVertex(trkArray, dispersion);
    
    trkArray->Clear();
    delete trkArray;     trkArray=NULL;
    return secVertex;
    
    
}
//____________________________________
AliESDVertex* AliAnalysisTaskSEOmegacccToOmega3Pi::ReconstructSecondaryVertex(TObjArray *trkArray, Double_t &dispersion) {
    
    
    /// Secondary vertex reconstruction with AliVertexerTracks
    fVertexerTracks->SetFieldkG(fBzkG);
    fVertexerTracks->SetVtxStart(fPrimVtx);
    AliESDVertex *vertexESD = (AliESDVertex*)fVertexerTracks->VertexForSelectedESDTracks(trkArray);
    
    if(!vertexESD) {AliDebug(1,"no sec vertex reco"); /*delete fVertexerTracks; fVertexerTracks=NULL; */return 0;}
   
    if(vertexESD->GetNContributors()!=trkArray->GetEntriesFast()) {
        //AliDebug(2,"vertexing failed");
        //delete vertexESD; vertexESD=NULL; delete fVertexerTracks; fVertexerTracks=NULL;
        return 0;
    }
    
    Double_t vertRadius2=vertexESD->GetX()*vertexESD->GetX()+vertexESD->GetY()*vertexESD->GetY();
    if(vertRadius2>8.){
        // vertex outside beam pipe, reject candidate to avoid propagation through material
        //delete vertexESD; vertexESD=NULL; delete fVertexerTracks; fVertexerTracks=NULL;
        return 0;
    }
    
    
    
    // convert to AliAODVertex
    Double_t pos[3],cov[6],chi2perNDF;
    vertexESD->GetXYZ(pos); // position
    vertexESD->GetCovMatrix(cov); //covariance matrix
    chi2perNDF = vertexESD->GetChi2toNDF();
    dispersion = vertexESD->GetDispersion();
    
    return vertexESD;
    
    
}
//____________________________________
AliExternalTrackParam* AliAnalysisTaskSEOmegacccToOmega3Pi::GetTrackParamForCascade(){
    
    // cascade vertex and momentum
    Double_t xyz[3], pxpypz[3];
    fCasc->XvYvZv(xyz);
    fCasc->PxPyPz(pxpypz);
    Double_t cov[6]; //for(int j=0; j<6; j++) cov[j]=0;
    fCasc->GetPosCovXi(cov);
    AliESDVertex *vertexcasc = new AliESDVertex(xyz,cov,fCasc->GetChi2Xi(),0,"VertexCasc");
    
    Double_t xyzv0[3], pxpypzv0[3];
    fV0->XvYvZv(xyzv0);
    fV0->PxPyPz(pxpypzv0);
    Double_t covTrPos[21];
    (fV0->GetParamP())->GetCovarianceXYZPxPyPz(covTrPos);
    Double_t covTrNeg[21];
    (fV0->GetParamN())->GetCovarianceXYZPxPyPz(covTrNeg);
    //cov V0
    Double_t covV0[21];
    Double_t covV0prop[21];
    for(int i=0; i<21; i++){
        covV0[i]=covTrPos[i]+covTrNeg[i];
        covV0prop[i]=0;
    }
    AliExternalTrackParam *v0track=new AliExternalTrackParam(xyzv0,pxpypzv0,covV0,1);
    Double_t d0zV0[2],covd0zV0[3];
    v0track->PropagateToDCA(vertexcasc,0.,100.,d0zV0,covd0zV0);
    v0track->GetCovarianceXYZPxPyPz(covV0prop);
    //cascade bachelor
    Double_t d0zbach[2],covd0zbach[3];
    AliExternalTrackParam esdCascadeBach;
    esdCascadeBach.CopyFromVTrack(fBachTrackCasc);
    esdCascadeBach.PropagateToDCA(vertexcasc,fBzkG,100.,d0zbach,covd0zbach);
    Double_t covTrBach[21];
    esdCascadeBach.GetCovarianceXYZPxPyPz(covTrBach);
    // cascade covariance matrix
    Double_t cv[21]; for(int i=0; i<21; i++) cv[i]=0;
    for(int k=0; k<21; k++) {
        cv[k]=covTrBach[k]+covV0prop[k];
    }
    AliExternalTrackParam *cascTrack = new AliExternalTrackParam(xyz,pxpypz,cv,fCascCharge);
    
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
        if(fIsMCSignalProd) fTreeReconstruction->Fill();
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
TTree* AliAnalysisTaskSEOmegacccToOmega3Pi::BuildTreeCutVar(TString name, TString title, bool isforomegac, bool isforomegacc, bool isforomegaccc)
{
    TTree *tree = new TTree(name.Data(),title.Data());
    TString particle[11]={"_V0neg","_V0pos","V0","_CascBach","omega","_pi3","_omegac","_pi2","_omegacc","_pi1","_omegaccc"};
    TString particle_weakDecay[3]={"_omegac","_omegacc","_omegaccc"};
    TString particle_pi[3]={"_pi3","_pi2","_pi1"};
    
    if(isforomegac){
        for(int i=0; i<7; i++){
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
        for(int j=0; j<1; j++){
            tree->Branch(Form("fChi2ndf%s",      particle_weakDecay[j].Data()),&fTreeVariableDecVtxChi2Ndf[j],     Form("fChi2ndf%s/F",      particle_weakDecay[j].Data()));
            tree->Branch(Form("fCosPA%s",        particle_weakDecay[j].Data()),&fTreeVariableCosPointingAngle[j],  Form("fCosPA%s/F",        particle_weakDecay[j].Data()));
            tree->Branch(Form("fCosPAXY%s",      particle_weakDecay[j].Data()),&fTreeVariableCosPointingAngleXY[j],Form("fCosPAXY%s/F",      particle_weakDecay[j].Data()));
            tree->Branch(Form("fDecayLength%s",  particle_weakDecay[j].Data()),&fTreeVariableDecayLength[j],       Form("fDecayLength%s/F",  particle_weakDecay[j].Data()));
            tree->Branch(Form("fDecayLengthXY%s",particle_weakDecay[j].Data()),&fTreeVariableDecayLengthXY[j],     Form("fDecayLengthXY%s/F",particle_weakDecay[j].Data()));
            tree->Branch(Form("fInvMass%s",      particle_weakDecay[j].Data()),&fTreeVariableInvMass[j],           Form("fInvMass%s/F",      particle_weakDecay[j].Data()));
            tree->Branch(Form("fImpParRPhi%s",   particle_weakDecay[j].Data()),&fTreeVariableImpParRPhi[j],        Form("fImpParRPhi%s/F",   particle_weakDecay[j].Data()));
            tree->Branch(Form("fImpParZ%s",      particle_weakDecay[j].Data()),&fTreeVariableImpParZ[j],           Form("fImpParZ%s/F",      particle_weakDecay[j].Data()));
            tree->Branch(Form("fIsSignal%s",     particle_weakDecay[j].Data()),&fIsSignal[j],                      Form("fIsSignal%s/O",     particle_weakDecay[j].Data()));
            tree->Branch(Form("fImpParRPhi%s",   particle_pi[j].Data()),&fTreeVariableImpParRPhi[j+3],        Form("fImpParRPhi%s/F",   particle_pi[j].Data()));
            tree->Branch(Form("fImpParZ%s",      particle_pi[j].Data()),&fTreeVariableImpParZ[j+3],           Form("fImpParZ%s/F",      particle_pi[j].Data()));
        }
    }
    
    if(isforomegacc){
        for(int i=0; i<9; i++){
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
        for(int j=0; j<2; j++){
            tree->Branch(Form("fChi2ndf%s",      particle_weakDecay[j].Data()),&fTreeVariableDecVtxChi2Ndf[j],     Form("fChi2ndf%s/F",      particle_weakDecay[j].Data()));
            tree->Branch(Form("fCosPA%s",        particle_weakDecay[j].Data()),&fTreeVariableCosPointingAngle[j],  Form("fCosPA%s/F",        particle_weakDecay[j].Data()));
            tree->Branch(Form("fCosPAXY%s",      particle_weakDecay[j].Data()),&fTreeVariableCosPointingAngleXY[j],Form("fCosPAXY%s/F",      particle_weakDecay[j].Data()));
            tree->Branch(Form("fDecayLength%s",  particle_weakDecay[j].Data()),&fTreeVariableDecayLength[j],       Form("fDecayLength%s/F",  particle_weakDecay[j].Data()));
            tree->Branch(Form("fDecayLengthXY%s",particle_weakDecay[j].Data()),&fTreeVariableDecayLengthXY[j],     Form("fDecayLengthXY%s/F",particle_weakDecay[j].Data()));
            tree->Branch(Form("fInvMass%s",      particle_weakDecay[j].Data()),&fTreeVariableInvMass[j],           Form("fInvMass%s/F",      particle_weakDecay[j].Data()));
            tree->Branch(Form("fImpParRPhi%s",   particle_weakDecay[j].Data()),&fTreeVariableImpParRPhi[j],        Form("fImpParRPhi%s/F",   particle_weakDecay[j].Data()));
            tree->Branch(Form("fImpParZ%s",      particle_weakDecay[j].Data()),&fTreeVariableImpParZ[j],           Form("fImpParZ%s/F",      particle_weakDecay[j].Data()));
            tree->Branch(Form("fIsSignal%s",     particle_weakDecay[j].Data()),&fIsSignal[j],                      Form("fIsSignal%s/O",     particle_weakDecay[j].Data()));
            tree->Branch(Form("fImpParRPhi%s",   particle_pi[j].Data()),&fTreeVariableImpParRPhi[j+3],        Form("fImpParRPhi%s/F",   particle_pi[j].Data()));
            tree->Branch(Form("fImpParZ%s",      particle_pi[j].Data()),&fTreeVariableImpParZ[j+3],           Form("fImpParZ%s/F",      particle_pi[j].Data()));
        }
    }
    
    if(isforomegaccc){
        for(int i=0; i<11; i++){
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
        for(int j=0; j<3; j++){
            tree->Branch(Form("fChi2ndf%s",      particle_weakDecay[j].Data()),&fTreeVariableDecVtxChi2Ndf[j],     Form("fChi2ndf%s/F",      particle_weakDecay[j].Data()));
            tree->Branch(Form("fCosPA%s",        particle_weakDecay[j].Data()),&fTreeVariableCosPointingAngle[j],  Form("fCosPA%s/F",        particle_weakDecay[j].Data()));
            tree->Branch(Form("fCosPAXY%s",      particle_weakDecay[j].Data()),&fTreeVariableCosPointingAngleXY[j],Form("fCosPAXY%s/F",      particle_weakDecay[j].Data()));
            tree->Branch(Form("fDecayLength%s",  particle_weakDecay[j].Data()),&fTreeVariableDecayLength[j],       Form("fDecayLength%s/F",  particle_weakDecay[j].Data()));
            tree->Branch(Form("fDecayLengthXY%s",particle_weakDecay[j].Data()),&fTreeVariableDecayLengthXY[j],     Form("fDecayLengthXY%s/F",particle_weakDecay[j].Data()));
            tree->Branch(Form("fNormDecayLength%s",  particle_weakDecay[j].Data()),&fTreeVariableNormDecayLength[j],       Form("fNormDecayLength%s/F",  particle_weakDecay[j].Data()));
            tree->Branch(Form("fNormDecayLengthXY%s",particle_weakDecay[j].Data()),&fTreeVariableNormDecayLengthXY[j],     Form("fNormDecayLengthXY%s/F",particle_weakDecay[j].Data()));
            tree->Branch(Form("fInvMass%s",      particle_weakDecay[j].Data()),&fTreeVariableInvMass[j],           Form("fInvMass%s/F",      particle_weakDecay[j].Data()));
            tree->Branch(Form("fImpParRPhi%s",   particle_weakDecay[j].Data()),&fTreeVariableImpParRPhi[j],        Form("fImpParRPhi%s/F",   particle_weakDecay[j].Data()));
            tree->Branch(Form("fImpParZ%s",      particle_weakDecay[j].Data()),&fTreeVariableImpParZ[j],           Form("fImpParZ%s/F",      particle_weakDecay[j].Data()));
            tree->Branch(Form("fIsSignal%s",     particle_weakDecay[j].Data()),&fIsSignal[j],                      Form("fIsSignal%s/O",     particle_weakDecay[j].Data()));
            tree->Branch(Form("fImpParRPhi%s",   particle_pi[j].Data()),&fTreeVariableImpParRPhi[j+3],             Form("fImpParRPhi%s/F",   particle_pi[j].Data()));
            tree->Branch(Form("fImpParZ%s",      particle_pi[j].Data()),&fTreeVariableImpParZ[j+3],                Form("fImpParZ%s/F",      particle_pi[j].Data()));
        }
    }
   
    
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
