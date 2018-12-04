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
    void RecoEvent(AliESDEvent *esd);
    void FillTrackDistributions(AliESDEvent *esd);
    void FillV0Histos(AliESDEvent *esd);
    void FillCascadeHistos(AliESDEvent *esd);
    void FillGenDistrib();
    TString GetGenerator(Int_t label, AliGenCocktailEventHeader* header);
    
    Long_t MakeOmegac(AliESDEvent *esdEv);
    bool FillHistoOmegac(AliESDEvent *esdEv, AliESDcascade *casc, AliESDtrack *track, AliESDVertex *esdVc);
    bool FillHistoOmegacc(AliESDEvent *esdEv, AliESDcascade *casc, AliESDtrack *track, AliESDtrack *track2, AliESDVertex *esdVc, AliESDVertex *esdVcc);
    bool FillHistoOmegaccc(AliESDEvent *esdEv, AliESDcascade *casc, AliESDtrack *track, AliESDtrack *track2, AliESDtrack *track3, AliESDVertex *esdVc, AliESDVertex *esdVcc, AliESDVertex *esdVccc);
    bool IsSelectedOmegaccc(Double_t vars[8]);
    bool IsSelectedOmegacc(Double_t vars[8]);
    bool IsSelectedOmegac(Double_t vars[8]);
    AliESDVertex* CallReconstructSecondaryVertexOmegac(AliESDEvent *esdEv, AliESDcascade *casc, AliESDtrack *track, Double_t &dispersion);
    AliESDVertex* CallReconstructSecondaryVertexOmegacc(AliESDEvent *esdEv, AliESDVertex *sVtxOmegac, AliESDcascade *casc, AliESDtrack *esdtr, AliESDtrack *esdtr2, Double_t &dispersion);
    AliESDVertex* CallReconstructSecondaryVertexOmegaccc(AliESDEvent *esdEv, AliESDVertex *sVtxOmegacc, AliESDVertex *sVtxOmegac, AliESDcascade *casc, AliESDtrack *esdtr, AliESDtrack *esdtr2, AliESDtrack *esdtr3, Double_t &dispersion);
    AliExternalTrackParam* GetTrackParamForCascade(AliESDEvent *esdEv, AliESDcascade *casc);
    AliExternalTrackParam* GetTrackParamForOmegac(AliESDEvent *esdEv, AliESDVertex *sVtxOmegac, AliESDcascade *casc, AliESDtrack *esdtr);
    AliExternalTrackParam* GetTrackParamForOmegacc(AliESDEvent *esdEv, AliESDVertex *sVtxOmegacc, AliESDVertex *sVtxOmegac, AliESDcascade *casc, AliESDtrack *esdtr, AliESDtrack *esdtr2);
    AliExternalTrackParam* GetTrackParamForOmegaccc(AliESDEvent *esdEv, AliESDVertex *sVtxOmegaccc, AliESDVertex *sVtxOmegacc, AliESDVertex *sVtxOmegac, AliESDcascade *casc, AliESDtrack *esdtr, AliESDtrack *esdtr2, AliESDtrack *esdtr3);
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
    
private:
    
    AliAnalysisTaskSEOmegacccToOmega3Pi(const AliAnalysisTaskSEOmegacccToOmega3Pi&);
    AliAnalysisTaskSEOmegacccToOmega3Pi& operator=(const AliAnalysisTaskSEOmegacccToOmega3Pi&);
    
    
    AliMCEvent*              fMcEvent;    //! MC event
    AliInputEventHandler*    fMcHandler; //! MCEventHandler
    AliStack                *fStack;     //!
    TH1F                    *fNentries;                  //!<!   histogram with number of events on output slot 1
    TList                   *fOutputGen;                  //!<!   list on output slot 2
    TList                   *fOutputReco;                  //!<!   list on output slot 2
    R5Detector              *fITS;       //!
    TH2F                    *fHistNcollHFtype; //!
    TH2F                    *fHistNinjectedbvsb; //!
    TH2F                    *fHistNinjectedcvsb; //!
    TH2F *fHistnHitsVsGenPt; //!
    TH2F *fHistnHitsVsGenY; //!
    TH2F *fHistnHitsVsGenEta; //!
    TH2F *fHistnHitsVsProdRad; //!
    TH2F *fHistRecoPtVsGenPt; //!
    TH2F *fHistRecoYVsGenY; //!
    TH2F *fHistRecoEtaVsGenEta; //!
    TH1F *fHistGenVertexX; //! 
    TH1F *fHistGenVertexY; //! 
    TH1F *fHistGenVertexZ; //! 
    TH1F *fHistRecoVertexX; //!
    TH1F *fHistRecoVertexY; //!
    TH1F *fHistRecoVertexZ; //!
    TH1F *fHistGenVertexSigmaX; //! 
    TH1F *fHistGenVertexSigmaY; //! 
    TH1F *fHistGenVertexSigmaZ; //! 
    TH1F *fHistRecoVertexSigmaX; //!
    TH1F *fHistRecoVertexSigmaY; //!
    TH1F *fHistRecoVertexSigmaZ; //!
    TH3F *fhPtGenEtaGenNhits_pi; //!
    TH3F *fhPtGenEtaGenNhits_p; //!   
    TH3F *fhPtGenEtaGenNhits_k; //!  
    TH3F *fhPtRecoEtaRecoNhits_pi; //!
    TH3F *fhPtRecoEtaRecoNhits_p; //!
    TH3F *fhPtRecoEtaRecoNhits_k; //!
    
    TH2F *fhPtGenEtaGen_piReco; //!
    TH2F *fhPtGenEtaGen_pReco; //! 
    TH2F *fhPtGenEtaGen_kReco; //!  
    TH2F *fhPtGenEtaGen_LambdaReco; //!
    TH2F *fhPtGenEtaGen_OmegaReco; //!  
    TH2F *fhPtGenEtaGen_OmegacReco; //!  
    TH2F *fhPtGenEtaGen_OmegaccReco; //!  
    TH2F *fhPtGenEtaGen_OmegacccReco; //!  
    
    TH1D *fhV0radiusS; //! 
    TH1D *fhDCAnegToPVS; //! 
    TH1D *fhDCAposToPVS; //! 
    TH1D *fhDCAV0DaughtersS; //! 
    TH1D *fhCosinePointAS; //! 
    TH1D *fhProperLifetimeS; //! 
    TH1F *fHistMassLambdaS; //! 
    TH1F *fHistMassAntiLambdaS; //! 
    TH1D *fhV0ptS; //! 
    TH1D *fhV0radiusB; //! 
    TH1D *fhDCAnegToPVB; //! 
    TH1D *fhDCAposToPVB; //! 
    TH1D *fhDCAV0DaughtersB; //! 
    TH1D *fhCosinePointAB; //!
    TH1D *fhProperLifetimeB; //! 
    TH1F *fHistMassLambdaB; //! 
    TH1F *fHistMassAntiLambdaB; //! 
    TH1D *fhV0ptB; //! 
    
    //TH2D *fHistPtGenEtaGen_Gen[12]; //!
    TH2F* fHistoNbVsNcPYTHIA;     //!<! histo of n. b quarks vs. n c. quarks
    TH2F* fHistoNbVsNcHIJING;     //!<! histo of n. b quarks vs. n c. quarks
    
    Float_t fBzkG; 
    AliESDVertex* fV1;            //!
    
    TH1F *fCascInvMassS;   //!
    TH1F *fCascRadiusS;    //!
    TH1F *fCascPtS;        //!
    TH1F *fCascCosPointAngleS; //!
    TH1F *fCascInvMassB;   //!
    TH1F *fCascRadiusB;    //!
    TH1F *fCascPtB;        //!
    TH1F *fCascCosPointAngleB; //!
    
    TH1F *fOmegacInvMassS;  //!
    TH1F *fOmegacPtS;  //!
    TH1F *fOmegacDecayLenghtXYS;  //!
    TH1F *fOmegacCosPointAngleXYS;  //!
    TH1F *fOmegacPiond0S; //!
    TH1F *fOmegacd0S; //! 
    TH1F *fOmegacPionCosThetaStarS; //!    
    TH1F *fOmegacInvMassB;  //!
    TH1F *fOmegacPtB;  //!
    TH1F *fOmegacDecayLenghtXYB;  //!
    TH1F *fOmegacCosPointAngleXYB;  //!
    TH1F *fOmegacPiond0B; //!
    TH1F *fOmegacd0B; //!
    TH1F *fOmegacPionCosThetaStarB; //!  
    
    TH1F *fOmegaccInvMassS;  //!
    TH1F *fOmegaccPtS;  //!
    TH1F *fOmegaccDecayLenghtXYS;  //!
    TH1F *fOmegaccCosPointAngleXYS;  //!
    TH1F *fOmegaccPiond0S; //!
    TH1F *fOmegaccd0S; //! 
    TH1F *fOmegaccPionCosThetaStarS; //! 
    TH1F *fOmegaccInvMassB;  //!
    TH1F *fOmegaccPtB;  //!
    TH1F *fOmegaccDecayLenghtXYB;  //!
    TH1F *fOmegaccCosPointAngleXYB;  //!
    TH1F *fOmegaccPiond0B; //
    TH1F *fOmegaccd0B; //! 
    TH1F *fOmegaccPionCosThetaStarB; //! 
    
    TH1F *fOmegacccInvMassS;  //!
    TH1F *fOmegacccPtS;  //!
    TH1F *fOmegacccDecayLenghtXYS;  //!
    TH1F *fOmegacccCosPointAngleXYS;  //!
    TH1F *fOmegacccPiond0S; //!
    TH1F *fOmegacccd0S; //! 
    TH1F *fOmegacccPionCosThetaStarS; //! 
    TH1F *fOmegacccInvMassB;  //!
    TH1F *fOmegacccPtB;  //!
    TH1F *fOmegacccDecayLenghtXYB;  //!
    TH1F *fOmegacccCosPointAngleXYB;  //!
    TH1F *fOmegacccPiond0B; //!
    TH1F *fOmegacccd0B; //! 
    TH1F *fOmegacccPionCosThetaStarB; //! 
    
    TH1F *fOmegacVtxXGen; //!ok
    TH1F *fOmegacVtxYGen; //!ok
    TH1F *fOmegacVtxZGen; //!ok
    TH1F *fOmegaccVtxXGen; //!ok
    TH1F *fOmegaccVtxYGen; //!ok
    TH1F *fOmegaccVtxZGen; //!ok
    TH1F *fOmegacccVtxXGen; //!ok
    TH1F *fOmegacccVtxYGen; //!ok
    TH1F *fOmegacccVtxZGen; //!ok
    TH1F *fOmegacVtxXReco; //!ok
    TH1F *fOmegacVtxYReco; //!ok
    TH1F *fOmegacVtxZReco; //!ok
    TH1F *fOmegaccVtxXReco; //!ok
    TH1F *fOmegaccVtxYReco; //!ok
    TH1F *fOmegaccVtxZReco; //!ok
    TH1F *fOmegacccVtxXReco; //!ok
    TH1F *fOmegacccVtxYReco; //!ok
    TH1F *fOmegacccVtxZReco; //!ok
    TH1F *fOmegacGenVsPtGen; //!ok
    TH1F *fOmegacRecoVsPtGen; //!
    TH1F *fOmegaccGenVsPtGen; //!ok
    TH1F *fOmegaccRecoVsPtGen; //!
    TH1F *fOmegacccGenVsPtGen; //!ok
    TH1F *fOmegacccRecoVsPtGen; //!
     
    TH1F *fKGenVsPtGen; //!ok
    TH1F *fPGenVsPtGen; //!ok
    TH1F *fKRecoVsPtGen; //!ok
    TH1F *fPRecoVsPtGen; //!ok
    
    Double_t fOmegacVariables[8]; //inv mass, pt, decLXY, impparOmegac, impparT, pt track, cosTheta*Pion, cosThetaPointing
    Double_t fOmegaccVariables[8]; //inv mass, pt, decLXY, impparOmegacc, impparT, pt track, cosTheta*Pion, cosThetaPointing
    Double_t fOmegacccVariables[8]; //inv mass, pt, decLXY, impparOmegacc, impparT, pt track, cosTheta*Pion, cosThetaPointing
    
    Double_t fOmegacCuts[8]; //inv mass, pt, decLXY, impparOmegac, impparT, pt track, cosTheta*Pion, cosThetaPointing
    Double_t fOmegaccCuts[8]; //inv mass, pt, decLXY, impparOmegacc, impparT, pt track, cosTheta*Pion, cosThetaPointing
    Double_t fOmegacccCuts[8]; //inv mass, pt, decLXY, impparOmegacc, impparT, pt track, cosTheta*Pion, cosThetaPointing
    
    TH2F *fhEtaDauVsEtaMoth_Gen[10]; //!
    TH2F *fhEtaDauVsEtaMoth_Rec[10]; //!
    
    Float_t fEtaCut;
	TH1F *fhOmegaGenVsPtGen; //! 
	TH1F *fhLambdaGenVsPtGen; //! 
	TH1F *fhOmegaRecoVsPtGen; //! 
	TH1F *fhLambdaRecoVsPtGen; //!
	
	TH2F *fhEtaOmegacccVsEta_gen[6]; //!
    TH2F *fhPtOmegacccVsPt_gen[6]; //!  
    TH2F *fhYOmegacccVsY_gen[6]; //!    
    TH2F *fhEtaOmegaccVsEta_gen[5]; //!
    TH2F *fhPtOmegaccVsPt_gen[5]; //!  
    TH2F *fhYOmegaccVsY_gen[5]; //!  
    TH2F *fhEtaOmegacVsEta_gen[4]; //!
    TH2F *fhPtOmegacVsPt_gen[4]; //!  
    TH2F *fhYOmegacVsY_gen[4]; //!    
    TH1F *fPiGenFromVsPtGen[4]; //!   
    TH1F *fPiRecoFromVsPtGen[4]; //!  
  

    
    
    
    

    
    /// \cond CLASSIMP
    ClassDef(AliAnalysisTaskSEOmegacccToOmega3Pi,1);
    /// \endcond
};

#endif

