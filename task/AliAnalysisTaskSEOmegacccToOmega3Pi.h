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
    //void FillTrackDistributions();
    //void FillV0Histos();
    //void FillCascadeHistos();
    
    TString GetGenerator(Int_t label, AliGenCocktailEventHeader* header);
    
    Long_t MakeOmegac();
    bool FillHistoOmegac(AliESDcascade *casc, AliESDtrack *track, AliESDVertex *esdVc);
    bool FillHistoOmegacc(AliESDcascade *casc, AliESDtrack *track, AliESDtrack *track2, AliESDVertex *esdVc, AliESDVertex *esdVcc);
    bool FillHistoOmegaccc(AliESDcascade *casc, AliESDtrack *track, AliESDtrack *track2, AliESDtrack *track3, AliESDVertex *esdVc, AliESDVertex *esdVcc, AliESDVertex *esdVccc);
    bool IsSelectedOmegaccc(Double_t vars[11]);
    bool IsSelectedOmegacc(Double_t vars[11]);
    bool IsSelectedOmegac(Double_t vars[11]);
    AliESDVertex* CallReconstructSecondaryVertexOmegac(AliESDcascade *casc, AliESDtrack *track, Double_t &dispersion);
    AliESDVertex* CallReconstructSecondaryVertexOmegacc(AliESDVertex *sVtxOmegac, AliESDcascade *casc, AliESDtrack *esdtr, AliESDtrack *esdtr2, Double_t &dispersion);
    AliESDVertex* CallReconstructSecondaryVertexOmegaccc(AliESDVertex *sVtxOmegacc, AliESDVertex *sVtxOmegac, AliESDcascade *casc, AliESDtrack *esdtr, AliESDtrack *esdtr2, AliESDtrack *esdtr3, Double_t &dispersion);
    AliExternalTrackParam* GetTrackParamForCascade(AliESDcascade *casc);
    AliExternalTrackParam* GetTrackParamForOmegac(AliESDVertex *sVtxOmegac, AliESDcascade *casc, AliESDtrack *esdtr);
    AliExternalTrackParam* GetTrackParamForOmegacc(AliESDVertex *sVtxOmegacc, AliESDVertex *sVtxOmegac, AliESDcascade *casc, AliESDtrack *esdtr, AliESDtrack *esdtr2);
    AliExternalTrackParam* GetTrackParamForOmegaccc(AliESDVertex *sVtxOmegaccc, AliESDVertex *sVtxOmegacc, AliESDVertex *sVtxOmegac, AliESDcascade *casc, AliESDtrack *esdtr, AliESDtrack *esdtr2, AliESDtrack *esdtr3);
    AliESDVertex* ReconstructSecondaryVertex(TObjArray *trkArray, Double_t &dispersion);
    Bool_t CheckIsSignalOmegac(AliESDtrack *pTrackCasc, AliESDtrack *nTrackCasc, AliESDtrack *bachTrackCasc, AliESDtrack *track);
    Bool_t CheckIsSignalOmegacc(AliESDtrack *pTrackCasc, AliESDtrack *nTrackCasc, AliESDtrack *bachTrackCasc, AliESDtrack *track, AliESDtrack *track2);
    Bool_t CheckIsSignalOmegaccc(AliESDtrack *pTrackCasc, AliESDtrack *nTrackCasc, AliESDtrack *bachTrackCasc, AliESDtrack *track, AliESDtrack *track2, AliESDtrack *track3);
    Int_t CheckOriginTrack(AliESDtrack *track, Int_t pdg);
    Bool_t IsTrackFromCharmBaryon(AliESDtrack *track, Int_t pdg);
    void PrintDecayChainTrack(AliESDtrack *track);
    Double_t DecayLength(AliESDVertex *primV, AliESDVertex *secV) const;
    Double_t DecayLengthXY(AliESDVertex *primV, AliESDVertex *secV) const;
    Double_t CosPointingAngle(AliESDVertex *primV, AliESDVertex *secV, Double_t p[3]) const;
    Double_t CosPointingAngleXY(AliESDVertex *primV, AliESDVertex *secV, Double_t p[3]) const;
    Double_t CosThetaStar(Int_t ip,UInt_t pdgvtx,UInt_t pdgprong0,UInt_t pdgprong1, Double_t pvtx[3], Double_t pprong0[3], Double_t pprong1[3]) const;
    Double_t QlProng(Double_t pvtx[3], Double_t pprong[3]) const;
    Double_t EtaCand(Double_t p, Double_t pz) const {return 0.5*TMath::Log((p+pz)/(p-pz+1.e-13));}
    Double_t YCand(Double_t e, Double_t pz) const {return 0.5*TMath::Log((e+pz)/(e-pz+1.e-13));}
    Double_t PhiCand(Double_t px, Double_t py) const {return TMath::Pi()+TMath::ATan2(-py,-px);}
    //TTree* BuildTree(TString name, TString title);
    //void SetTreeVarV0Casc(AliESDcascade *casc, AliESDVertex *esdVc);
    TTree* BuildTreeOmegacccGenReco(TString name, TString title);
    TTree* BuildTreeOmegacccGen(TString name, TString title);
    TTree* BuildTreeCascV0Reco(TString name, TString title);
    TTree* BuildTreeV0Reco(TString name, TString title);
    TTree* BuildTreeOmegacccCutVar(TString name, TString title);
    TTree* BuildTreeOmegacCutVar(TString name, TString title);
    TTree* BuildTreeRecoTracks(TString name, TString title);
    TTree* BuildTreeReconstruction(TString name, TString title);
    void FillGenTree();
    void FillRecoTrackTree();
    void FillGenTreeRecoCascV0();
    void FillGenTreeRecoV0();
    void SetIsSignalProd(bool opt) {fIsMCSignalProd=opt;}
    
    
private:
    
    AliAnalysisTaskSEOmegacccToOmega3Pi(const AliAnalysisTaskSEOmegacccToOmega3Pi&);
    AliAnalysisTaskSEOmegacccToOmega3Pi& operator=(const AliAnalysisTaskSEOmegacccToOmega3Pi&);
    
    
    AliMCEvent              *fMcEvent;    //!<! MC event
    AliInputEventHandler    *fMcHandler; //!<! MCEventHandler
    AliStack                *fStack;     //!<!
    AliESDEvent             *fEvent; //!<!
    AliVertexerTracks       *fVertexerTracks; //!<!
    Float_t                 fBzkG;
    AliESDVertex            *fV1;            //!<!
    Float_t                 fEtaCut;
    Int_t                   fEvtCount;
    TH1F                    *fNentries;                  //!<!   histogram with number of events on output slot 1
    TList                   *fOutputGen;                  //!<!   list on output slot 2
    TList                   *fOutputReco;                  //!<!   list on output slot 2
    R5Detector              *fITS;       //!<!
    TH2F                    *fHistNcollHFtype; //!<!
    TH2F                    *fHistNinjectedbvsb; //!<!
    TH2F                    *fHistNinjectedcvsb; //!<!
    TH2F                    *fHistoNbVsNcPYTHIA;     //!<! histo of n. b quarks vs. n c. quarks
    TH2F                    *fHistoNbVsNcHIJING;     //!<! histo of n. b quarks vs. n c. quarks
    bool                    fIsMCSignalProd;
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
    // tre to compare gen and reco, filled for every omegaccc reco
    Float_t fTreeVariableRecoTrueOmegacccDecVtxGen[5][3];
    Float_t fTreeVariableRecoTrueOmegacccDecVtxReco[5][3];
    Float_t fTreeVariableRecoTrueOmegacccMomGen[5][3];
    Float_t fTreeVariableRecoTrueOmegacccMomReco[5][3];
    TTree  *fTreeTrueOmegaccc; //!<!
    // tree for cut variation, filled for every reco Omegaccc
    Float_t fTreeVariableDecVtxChi2Ndf[3];
    Float_t fTreeVariableCosPointingAngle[3];
    Float_t fTreeVariableCosPointingAngleXY[3];
    Float_t fTreeVariableDecayLength[3];
    Float_t fTreeVariableDecayLengthXY[3];
    Float_t fTreeVariableInvMass[4];
    Float_t fTreeVariabled0rphi[6];
    Float_t fTreeVariablePt[9];
    Float_t fTreeVariableEta[9];
    Float_t fTreeVariablePhi[9];
    Float_t fTreeVariableRap[9];
    Float_t fTreeVariableGenPt[9];
    Float_t fTreeVariableGenEta[9];
    Float_t fTreeVariableGenPhi[9];
    Float_t fTreeVariableGenRap[9];
    Float_t fTreeVariableGenRxy[9];
    bool    fIsSignal;
    TTree  *fTreeCutVar; //!<!
    
    // tree omegac reco
    Float_t fTreeVariableDecVtxChi2NdfOmegac;
    Float_t fTreeVariableDecayLengthOmegac;
    Float_t fTreeVariableDecayLengthXYOmegac;
    Float_t fTreeVariableInvMassOmegac[2]; // omegac and omega
    Float_t fTreeVariabled0rphiOmegac[3];  // omegac, omega, pion
    Float_t fTreeVariablePtOmegac[3];      // omegac, omega, pion
    Float_t fTreeVariableEtaOmegac[3];
    Float_t fTreeVariablePhiOmegac[3];
    Float_t fTreeVariableRapOmegac[3];
    Float_t fTreeVariableGenPtOmegac[3];
    Float_t fTreeVariableGenEtaOmegac[3];
    Float_t fTreeVariableGenPhiOmegac[3];
    Float_t fTreeVariableGenRapOmegac[3];
    Float_t fTreeVariableGenRxyOmegac[3];
    bool    fIsSignalOmegac;
    TTree  *fTreeCutVarOmegac; //!<!
    
    
    Float_t fTreeGenVarCascV0Reco[5][5];
    Float_t fTreeGenVarCascV0RecoInvMass;
    Int_t   fTreeGenVarCascV0RecoPDG[5];
    TTree  *fTreeGenCascV0Reco; //!<!
    
    Float_t fTreeGenVarV0Reco[3][5];
    Float_t fTreeGenVarV0RecoInvMass;
    Int_t   fTreeGenVarV0RecoPDG[3];
    TTree  *fTreeGenV0Reco; //!<!
    
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
    
    
    Double_t fOmegacVariables[11]; //inv mass, pt, decL, decLXY, impparOmegac, impparT, pt track, cosTheta*Pion, cosThetaPointing, cosThetaPointingXY, vtxchi2perNDF
    Double_t fOmegaccVariables[11]; //inv mass, pt, decL, decLXY, impparOmegac, impparT, pt track, cosTheta*Pion, cosThetaPointing, cosThetaPointingXY, vtxchi2perNDF
    Double_t fOmegacccVariables[11]; //inv mass, pt, decL, decLXY, impparOmegac, impparT, pt track, cosTheta*Pion, cosThetaPointing, cosThetaPointingXY, vtxchi2perNDF
    Double_t fOmegacCuts[11]; //inv mass, pt, decL, decLXY, impparOmegac, impparT, pt track, cosTheta*Pion, cosThetaPointing, cosThetaPointingXY, vtxchi2perNDF
    Double_t fOmegaccCuts[11]; //inv mass, pt, decL, decLXY, impparOmegac, impparT, pt track, cosTheta*Pion, cosThetaPointing, cosThetaPointingXY, vtxchi2perNDF
    Double_t fOmegacccCuts[11]; //inv mass, pt, decL, decLXY, impparOmegac, impparT, pt track, cosTheta*Pion, cosThetaPointing, cosThetaPointingXY, vtxchi2perNDF
    
    
    
    
    /// \cond CLASSIMP
    ClassDef(AliAnalysisTaskSEOmegacccToOmega3Pi,1);
    /// \endcond
};

#endif

