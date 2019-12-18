#ifndef AliAnalysisTaskSEOmegacccToOmega3Pi_H
#define AliAnalysisTaskSEOmegacccToOmega3Pi_H

/* Copyright(c) 1998-2009, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice                               */

/* $Id$ */


#include <TROOT.h>
#include <TSystem.h>
#include <TNtuple.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TH3F.h>
#include <THnSparse.h>
#include <TArrayD.h>
#include <TParticle.h>
#include <TClonesArray.h>
#include <TList.h>
#include <TObjArray.h>

#include "AliGenParam.h"
#include "AliGenerator.h"
#include "AliRunLoader.h"
#include "AliRun.h"
#include "AliStack.h"
#include "AliESDEvent.h"
#include "AliESDUtils.h"
#include "AliESDcascade.h"
#include "AliESDVertex.h"

#include "AliAnalysisTaskSE.h"
#include "AliAnalysisDataSlot.h"
#include "AliAnalysisDataContainer.h"
#include "AliInputEventHandler.h"
#include "AliMCEvent.h"
#include "AliStack.h"
#include "AliMCEventHandler.h"
#include "AliAnalysisTaskWeakDecayVertexer_mod.h"
#include "AliRecoDecayOmegac.h"
#include "AliRecoDecayOmegacc.h"
#include "AliRecoDecayOmegaccc.h"
#include "R5Detector.h"


class TH1I;
class TParticle;
class AliStack;
class AliVVertex;
class AliVParticle;


class AliAnalysisTaskSEOmegacccToOmega3Pi : public AliAnalysisTaskSE
{
public:
    
    AliAnalysisTaskSEOmegacccToOmega3Pi();
    AliAnalysisTaskSEOmegacccToOmega3Pi(const char *name);
    virtual ~AliAnalysisTaskSEOmegacccToOmega3Pi();
    
    
    /// Implementation of interface methods
    virtual void UserCreateOutputObjects();
    virtual void Init();
    virtual void LocalInit() {Init();}
    virtual void UserExec(Option_t *option);
    virtual void Terminate(Option_t *option);
    
    
    R5Detector* CreateDetector();
    void RecoEvent();
    
    TString GetGenerator(Int_t label, AliGenCocktailEventHeader* header);
    
    int MakeCandidates();
    bool FillHistoOmegac();
    bool FillHistoOmegacc();
    bool FillHistoOmegaccc();
    AliESDVertex* CallReconstructSecondaryVertexOmegac(Double_t &dispersion);
    AliESDVertex* CallReconstructSecondaryVertexOmegacc(Double_t &dispersion);
    AliESDVertex* CallReconstructSecondaryVertexOmegaccc(Double_t &dispersion);
    AliExternalTrackParam* GetTrackParamForCascade();
    AliESDVertex* ReconstructSecondaryVertex(TObjArray *trkArray, Double_t &dispersion);
    
    TTree* BuildTreeOmegacccGen(TString name, TString title);
    TTree* BuildTreeCutVar(TString name, TString title, bool isforomegac, bool isforomegacc, bool isforomegaccc);
    TTree* BuildTreeRecoTracks(TString name, TString title);
    TTree* BuildTreeReconstruction(TString name, TString title);
    TTree* BuildTreeCascV0Reco(TString name, TString title);
    TTree* BuildTreeV0Reco(TString name, TString title);
    void FillGenTree();
    void FillRecoTrackTree();
    void FillGenTreeRecoCascV0();
    void FillGenTreeRecoV0();
    void SetIsSignalProd(bool opt) {fIsMCSignalProd=opt;}
    
    
private:
    
    AliAnalysisTaskSEOmegacccToOmega3Pi(const AliAnalysisTaskSEOmegacccToOmega3Pi&);
    AliAnalysisTaskSEOmegacccToOmega3Pi& operator=(const AliAnalysisTaskSEOmegacccToOmega3Pi&);
    
    
    AliMCEvent              *fMcEvent;              //!<! MC event
    AliInputEventHandler    *fMcHandler;            //!<! MCEventHandler
    AliStack                *fStack;                //!<!
    AliESDEvent             *fEvent;                //!<!
    AliVertexerTracks       *fVertexerTracks;       //!<!
    Float_t                 fBzkG;
    AliESDVertex            *fPrimVtx;              //!<!
    Float_t                 fEtaCut;
    Int_t                   fEvtCount;
    TH1F                    *fNentries;             //!<!   histogram with number of events on output slot 1
    TList                   *fOutputGen;            //!<!   list on output slot 2
    TList                   *fOutputReco;           //!<!   list on output slot 2
    R5Detector              *fITS;                  //!<!
    TH2F                    *fHistNcollHFtype;      //!<!
    TH2F                    *fHistNinjectedbvsb;    //!<!
    TH2F                    *fHistNinjectedcvsb;    //!<!
    TH2F                    *fHistoNbVsNcPYTHIA;    //!<! histo of n. b quarks vs. n c. quarks
    TH2F                    *fHistoNbVsNcHIJING;    //!<! histo of n. b quarks vs. n c. quarks
    bool                    fIsMCSignalProd;
    
    //daughters
    AliESDcascade *fCasc;                       //!<! ok
    AliESDv0      *fV0;                         //!<! ok
    AliESDtrack   *fPosTrackCasc;               //!<! ok
    AliESDtrack   *fNegTrackCasc;               //!<! ok
    AliESDtrack   *fBachTrackCasc;              //!<! ok
    AliESDtrack   *fEsdTr1;                     //!<! ok
    AliESDtrack   *fEsdTr2;                     //!<! ok
    AliESDtrack   *fEsdTr3;                     //!<!
    //decay vertices
    AliESDVertex  *fVtxOmegac;                  //!<! ok
    AliESDVertex  *fVtxOmegacc;                 //!<! ok
    AliESDVertex  *fVtxOmegaccc;                //!<!
    //track params
    AliExternalTrackParam *fCascTrackParam;     //!<! ok
    AliExternalTrackParam *fOmegacTrackParam;   //!<! ok
    AliExternalTrackParam *fOmegaccTrackParam;  //!<!
    AliExternalTrackParam *fOmegacccTrackParam; //!<!
    //indexes
    int fIdxPosCasc;  //ok
    int fIdxNegCasc;  //ok
    int fIdxBachCasc; //ok
    int fIdxTrack1;   //ok
    int fIdxTrack2;   //ok
    int fIdxTrack3;
    //variables
    Float_t fCascInvMass; //ok
    Short_t fCascCharge;  //ok
    
    //MC particles
    TParticle* fmcPosCascDghter; //!<! ok
    TParticle* fmcNegCascDghter; //!<! ok
    TParticle* fmcBachCascDghter;//!<! ok
    TParticle* fmcTrack1;        //!<! ok
    TParticle* fmcTrack2;        //!<! ok
    TParticle* fmcTrack3;        //!<!
    //MC labels
    int flblPosCasc;  //ok
    int flblNegCasc;  //ok
    int flblBachCasc; //ok
    int flblTrack1;   //ok
    int flblTrack2;   //ok
    int flblTrack3;
    int flblCasc;     //ok
    int flblV0;       //ok
    int flblOmegac;   //ok
    int flblOmegacc;  //ok
    int flblOmegaccc; //ok
    
    
    //Reco tracks tree, filled once per reco track
    Float_t                 fRecoPt;
    Float_t                 fRecoPhi;
    Float_t                 fRecoEta;
    Float_t                 fRecoY;
    Float_t                 fGenPt;
    Float_t                 fGenEta;
    Float_t                 fGenRad;
    Int_t                   fRecoNhits;
    Int_t                   fRecoMClabel;
    Int_t                   fRecoMClabelMother;
    Float_t                 fGenPtMother;
    Int_t                   fRecoPdg;
    Int_t                   fRecoPdgMother;
    Int_t                   fRecoNReconstructableHits;
    TTree                   *fTreeRecoTracks; //!<!
    
    // tree to check MC gen., filled for every generated Omegaccc
    Float_t fTreeGenVarOmegaccc[11][5];
    Int_t   fTreeGenVarOmegacccNRHits[11];
    Int_t   fTreeGenVarOmegacccPDG[11];
    TTree  *fTreeGenOmegaccc; //!<!
    
    AliRecoDecayOmegac   *fOmegacCand; //!<!
    AliRecoDecayOmegacc  *fOmegaccCand; //!<!
    AliRecoDecayOmegaccc *fOmegacccCand; //!<!
    
    // tree omegac reco
    Float_t fTreeVariablePt[11];
    Float_t fTreeVariableEta[11];
    Float_t fTreeVariablePhi[11];
    Float_t fTreeVariableRap[11]; // omegac and omega
    Float_t fTreeVariableGenPt[11];  // omegac, omega, pion
    Float_t fTreeVariableGenEta[11];      // omegac, omega, pion
    Float_t fTreeVariableGenPhi[11];
    Float_t fTreeVariableGenRap[11];
    Float_t fTreeVariableGenRxy[11];
    Float_t fTreeVariableDecVtxChi2Ndf[3];
    Float_t fTreeVariableCosPointingAngle[3];
    Float_t fTreeVariableCosPointingAngleXY[3];
    Float_t fTreeVariableDecayLength[3];
    Float_t fTreeVariableDecayLengthXY[3];
    Float_t fTreeVariableNormDecayLength[3];
    Float_t fTreeVariableNormDecayLengthXY[3];
    Float_t fTreeVariableInvMass[3];
    Float_t fTreeVariableImpParRPhi[6];
    Float_t fTreeVariableImpParZ[6];
    bool fIsSignal[3];
    TTree  *fTreeCutVarOmegac; //!<!
    TTree  *fTreeCutVarOmegacc; //!<!
    TTree  *fTreeCutVarOmegaccc; //!<!
    
    vector<int> fNHitsAssigned;
    vector<int> fParticlePdg;
    vector<int> fMotherPdg;
    
    Int_t fParticleVarPdg;
    Int_t fParticleVarPdgMoth;
    Float_t fParticleVarPt;
    Float_t fParticleVarP;
    Float_t fParticleVarEta;
    Float_t fParticleVarRap;
    Float_t fParticleVarPhi;
    Float_t fParticleVarX;
    Float_t fParticleVarY;
    Float_t fParticleVarZ;
    Float_t fParticleVarRxy;
    Int_t fParticleVarNhitsAssigned;
    Int_t fParticleVarNhitsReco;
    bool fParticleVarIsReco;
    TTree  *fTreeReconstruction; //!<!
    
    Float_t fTreeGenVarCascV0Reco[5][5];
    Float_t fTreeGenVarCascV0RecoInvMass;
    Int_t   fTreeGenVarCascV0RecoPDG[5];
    TTree  *fTreeGenCascV0Reco; //!<!
    
    Float_t fTreeGenVarV0Reco[3][5];
    Float_t fTreeGenVarV0RecoInvMass;
    Int_t   fTreeGenVarV0RecoPDG[3];
    TTree  *fTreeGenV0Reco; //!<!
    
    
    Double_t fOmegacCuts[7];         //inv mass, pt, decL, decLXY, impparOmegac, impparT, vtxchi2perNDF
    Double_t fOmegaccCuts[7];        //inv mass, pt, decL, decLXY, impparOmegac, impparT, vtxchi2perNDF
    Double_t fOmegacccCuts[7];       //inv mass, pt, decL, decLXY, impparOmegac, impparT, vtxchi2perNDF
    
    
    /// \cond CLASSIMP
    ClassDef(AliAnalysisTaskSEOmegacccToOmega3Pi,1);
    /// \endcond
};

#endif

