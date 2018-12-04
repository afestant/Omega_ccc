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
fNentries(0x0),
fOutputGen(0x0),
fOutputReco(0x0),
fITS(0x0),
fHistNcollHFtype(0x0),
fHistNinjectedbvsb(0x0),
fHistNinjectedcvsb(0x0),
fHistGenVertexX(0x0), 
fHistGenVertexY(0x0), 
fHistGenVertexZ(0x0), 
fHistRecoVertexX(0x0),
fHistRecoVertexY(0x0),
fHistRecoVertexZ(0x0),
fHistGenVertexSigmaX(0x0), 
fHistGenVertexSigmaY(0x0), 
fHistGenVertexSigmaZ(0x0), 
fHistRecoVertexSigmaX(0x0),
fHistRecoVertexSigmaY(0x0),
fHistRecoVertexSigmaZ(0x0),
fhPtGenEtaGenNhits_pi(0x0),  
fhPtGenEtaGenNhits_p(0x0),   
fhPtGenEtaGenNhits_k(0x0),   
fhPtRecoEtaRecoNhits_pi(0x0),
fhPtRecoEtaRecoNhits_p(0x0), 
fhPtRecoEtaRecoNhits_k(0x0),
fhPtGenEtaGen_piReco(0x0),
fhPtGenEtaGen_pReco(0x0), 
fhPtGenEtaGen_kReco(0x0),
fhPtGenEtaGen_LambdaReco(0x0),
fhPtGenEtaGen_OmegaReco(0x0),
fhPtGenEtaGen_OmegacReco(0x0),
fhPtGenEtaGen_OmegaccReco(0x0),
fhPtGenEtaGen_OmegacccReco(0x0),
fhV0radiusS(0x0),
fhDCAnegToPVS(0x0), 
fhDCAposToPVS(0x0), 
fhDCAV0DaughtersS(0x0), 
fhCosinePointAS(0x0), 
fhProperLifetimeS(0x0), 
fHistMassLambdaS(0x0), 
fHistMassAntiLambdaS(0x0),
fhV0ptS(0x0), 
fhV0radiusB(0x0), 
fhDCAnegToPVB(0x0), 
fhDCAposToPVB(0x0), 
fhDCAV0DaughtersB(0x0), 
fhCosinePointAB(0x0),
fhProperLifetimeB(0x0), 
fHistMassLambdaB(0x0), 
fHistMassAntiLambdaB(0x0),
fhV0ptB(0x0),
fHistoNbVsNcPYTHIA(0x0),
fHistoNbVsNcHIJING(0x0),
fBzkG(0.),
fV1(0x0),
fCascInvMassS(0x0),
fCascRadiusS(0x0),
fCascPtS(0x0),
fCascCosPointAngleS(0x0),
fCascInvMassB(0x0),
fCascRadiusB(0x0),
fCascPtB(0x0),
fCascCosPointAngleB(0x0),
fOmegacInvMassS(0x0),
fOmegacPtS(0x0),
fOmegacDecayLenghtXYS(0x0),
fOmegacCosPointAngleXYS(0x0), 
fOmegacPiond0S(0x0),
fOmegacd0S(0x0),
fOmegacPionCosThetaStarS(0x0),
fOmegacInvMassB(0x0),
fOmegacPtB(0x0),
fOmegacDecayLenghtXYB(0x0),
fOmegacCosPointAngleXYB(0x0),  
fOmegacPiond0B(0x0),
fOmegacd0B(0x0),
fOmegacPionCosThetaStarB(0x0),
fOmegaccInvMassS(0x0),
fOmegaccPtS(0x0),
fOmegaccDecayLenghtXYS(0x0),
fOmegaccCosPointAngleXYS(0x0),
fOmegaccPiond0S(0x0),
fOmegaccd0S(0x0),
fOmegaccPionCosThetaStarS(0x0),
fOmegaccInvMassB(0x0),
fOmegaccPtB(0x0),
fOmegaccDecayLenghtXYB(0x0),
fOmegaccCosPointAngleXYB(0x0),
fOmegaccPiond0B(0x0),
fOmegaccd0B(0x0),
fOmegaccPionCosThetaStarB(0x0),
fOmegacccInvMassS(0x0),
fOmegacccPtS(0x0),
fOmegacccDecayLenghtXYS(0x0),  
fOmegacccCosPointAngleXYS(0x0),
fOmegacccPiond0S(0x0),
fOmegacccd0S(0x0),
fOmegacccPionCosThetaStarS(0x0),
fOmegacccInvMassB(0x0),
fOmegacccPtB(0x0),
fOmegacccDecayLenghtXYB(0x0),  
fOmegacccCosPointAngleXYB(0x0),
fOmegacccPiond0B(0x0),
fOmegacccd0B(0x0),
fOmegacccPionCosThetaStarB(0x0),
fOmegacVtxXGen(0x0),
fOmegacVtxYGen(0x0),
fOmegacVtxZGen(0x0),
fOmegaccVtxXGen(0x0),
fOmegaccVtxYGen(0x0),
fOmegaccVtxZGen(0x0),
fOmegacccVtxXGen(0x0),
fOmegacccVtxYGen(0x0),
fOmegacccVtxZGen(0x0),
fOmegacVtxXReco(0x0),
fOmegacVtxYReco(0x0),
fOmegacVtxZReco(0x0),
fOmegaccVtxXReco(0x0),
fOmegaccVtxYReco(0x0),
fOmegaccVtxZReco(0x0),
fOmegacccVtxXReco(0x0),
fOmegacccVtxYReco(0x0),
fOmegacccVtxZReco(0x0),
fOmegacGenVsPtGen(0x0),
fOmegacRecoVsPtGen(0x0),
fOmegaccGenVsPtGen(0x0),
fOmegaccRecoVsPtGen(0x0), 
fOmegacccGenVsPtGen(0x0), 
fOmegacccRecoVsPtGen(0x0),
fKGenVsPtGen(0x0),
fPGenVsPtGen(0x0),
fKRecoVsPtGen(0x0),
fPRecoVsPtGen(0x0),
fEtaCut(-99.),
fhOmegaGenVsPtGen(0x0),  
fhLambdaGenVsPtGen(0x0), 
fhOmegaRecoVsPtGen(0x0), 
fhLambdaRecoVsPtGen(0x0)
{
   for(Int_t ih=0; ih<10; ih++){
        	fhEtaDauVsEtaMoth_Gen[ih] =0x0; 
			fhEtaDauVsEtaMoth_Rec[ih]=0x0;
        }
  
  for(Int_t i=0; i<8; i++){
  		fOmegacVariables[i]=0.;
  		fOmegaccVariables[i]=0.;
  		fOmegacccVariables[i]=0.;
  	if(i<6){
  		fhEtaOmegacccVsEta_gen[i] = 0x0;
		fhPtOmegacccVsPt_gen[i] = 0x0;
		fhYOmegacccVsY_gen[i] = 0x0;
	}
	if(i<5){
		fhEtaOmegaccVsEta_gen[i] = 0x0;
		fhPtOmegaccVsPt_gen[i] = 0x0;
		fhYOmegaccVsY_gen[i] = 0x0;
	}
	if(i<4){
		fhEtaOmegacVsEta_gen[i] = 0x0;
		fhPtOmegacVsPt_gen[i] = 0x0;
		fhYOmegacVsY_gen[i] = 0x0;
		fPiGenFromVsPtGen[i] = 0x0;
		fPiRecoFromVsPtGen[i] = 0x0;
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
fNentries(0x0),
fOutputGen(0x0),
fOutputReco(0x0),
fITS(0x0),
fHistNcollHFtype(0x0),
fHistNinjectedbvsb(0x0),
fHistNinjectedcvsb(0x0),
fHistGenVertexX(0x0), 
fHistGenVertexY(0x0), 
fHistGenVertexZ(0x0), 
fHistRecoVertexX(0x0),
fHistRecoVertexY(0x0),
fHistRecoVertexZ(0x0),
fHistGenVertexSigmaX(0x0), 
fHistGenVertexSigmaY(0x0), 
fHistGenVertexSigmaZ(0x0), 
fHistRecoVertexSigmaX(0x0),
fHistRecoVertexSigmaY(0x0),
fHistRecoVertexSigmaZ(0x0),
fhPtGenEtaGenNhits_pi(0x0),  
fhPtGenEtaGenNhits_p(0x0),   
fhPtGenEtaGenNhits_k(0x0),   
fhPtRecoEtaRecoNhits_pi(0x0),
fhPtRecoEtaRecoNhits_p(0x0), 
fhPtRecoEtaRecoNhits_k(0x0),
fhPtGenEtaGen_piReco(0x0),
fhPtGenEtaGen_pReco(0x0), 
fhPtGenEtaGen_kReco(0x0),
fhPtGenEtaGen_LambdaReco(0x0),
fhPtGenEtaGen_OmegaReco(0x0),
fhPtGenEtaGen_OmegacReco(0x0),
fhPtGenEtaGen_OmegaccReco(0x0),
fhPtGenEtaGen_OmegacccReco(0x0),
fhV0radiusS(0x0),
fhDCAnegToPVS(0x0), 
fhDCAposToPVS(0x0), 
fhDCAV0DaughtersS(0x0), 
fhCosinePointAS(0x0), 
fhProperLifetimeS(0x0), 
fHistMassLambdaS(0x0), 
fHistMassAntiLambdaS(0x0),
fhV0ptS(0x0), 
fhV0radiusB(0x0), 
fhDCAnegToPVB(0x0), 
fhDCAposToPVB(0x0), 
fhDCAV0DaughtersB(0x0), 
fhCosinePointAB(0x0),
fhProperLifetimeB(0x0), 
fHistMassLambdaB(0x0), 
fHistMassAntiLambdaB(0x0),
fhV0ptB(0x0),
fHistoNbVsNcPYTHIA(0x0),
fHistoNbVsNcHIJING(0x0),
fBzkG(0.),
fV1(0x0),
fCascInvMassS(0x0),
fCascRadiusS(0x0),
fCascPtS(0x0),
fCascCosPointAngleS(0x0),
fCascInvMassB(0x0),
fCascRadiusB(0x0),
fCascPtB(0x0),
fCascCosPointAngleB(0x0),
fOmegacInvMassS(0x0),
fOmegacPtS(0x0),
fOmegacDecayLenghtXYS(0x0),
fOmegacCosPointAngleXYS(0x0), 
fOmegacPiond0S(0x0),
fOmegacd0S(0x0),
fOmegacPionCosThetaStarS(0x0),
fOmegacInvMassB(0x0),
fOmegacPtB(0x0),
fOmegacDecayLenghtXYB(0x0),
fOmegacCosPointAngleXYB(0x0),  
fOmegacPiond0B(0x0),
fOmegacd0B(0x0),
fOmegacPionCosThetaStarB(0x0),
fOmegaccInvMassS(0x0),
fOmegaccPtS(0x0),
fOmegaccDecayLenghtXYS(0x0),
fOmegaccCosPointAngleXYS(0x0),
fOmegaccPiond0S(0x0),
fOmegaccd0S(0x0),
fOmegaccPionCosThetaStarS(0x0),
fOmegaccInvMassB(0x0),
fOmegaccPtB(0x0),
fOmegaccDecayLenghtXYB(0x0),
fOmegaccCosPointAngleXYB(0x0),
fOmegaccPiond0B(0x0),
fOmegaccd0B(0x0),
fOmegaccPionCosThetaStarB(0x0),
fOmegacccInvMassS(0x0),
fOmegacccPtS(0x0),
fOmegacccDecayLenghtXYS(0x0),  
fOmegacccCosPointAngleXYS(0x0),
fOmegacccPiond0S(0x0),
fOmegacccd0S(0x0),
fOmegacccPionCosThetaStarS(0x0),
fOmegacccInvMassB(0x0),
fOmegacccPtB(0x0),
fOmegacccDecayLenghtXYB(0x0),  
fOmegacccCosPointAngleXYB(0x0),
fOmegacccPiond0B(0x0),
fOmegacccd0B(0x0),
fOmegacccPionCosThetaStarB(0x0),
fOmegacVtxXGen(0x0),
fOmegacVtxYGen(0x0),
fOmegacVtxZGen(0x0),
fOmegaccVtxXGen(0x0),
fOmegaccVtxYGen(0x0),
fOmegaccVtxZGen(0x0),
fOmegacccVtxXGen(0x0),
fOmegacccVtxYGen(0x0),
fOmegacccVtxZGen(0x0),
fOmegacVtxXReco(0x0),
fOmegacVtxYReco(0x0),
fOmegacVtxZReco(0x0),
fOmegaccVtxXReco(0x0),
fOmegaccVtxYReco(0x0),
fOmegaccVtxZReco(0x0),
fOmegacccVtxXReco(0x0),
fOmegacccVtxYReco(0x0),
fOmegacccVtxZReco(0x0),
fOmegacGenVsPtGen(0x0),
fOmegacRecoVsPtGen(0x0),
fOmegaccGenVsPtGen(0x0),
fOmegaccRecoVsPtGen(0x0), 
fOmegacccGenVsPtGen(0x0), 
fOmegacccRecoVsPtGen(0x0),
fKGenVsPtGen(0x0),
fPGenVsPtGen(0x0),
fKRecoVsPtGen(0x0),
fPRecoVsPtGen(0x0),
fEtaCut(1.),
fhOmegaGenVsPtGen(0x0),  
fhLambdaGenVsPtGen(0x0), 
fhOmegaRecoVsPtGen(0x0), 
fhLambdaRecoVsPtGen(0x0)
{
    /// Standard constructor


    for(Int_t ih=0; ih<10; ih++){
        	fhEtaDauVsEtaMoth_Gen[ih] =0x0; 
			fhEtaDauVsEtaMoth_Rec[ih]=0x0;
        }
    for(Int_t i=0; i<8; i++){
  		fOmegacVariables[i]=0.;
  		fOmegaccVariables[i]=0.;
  		fOmegacccVariables[i]=0.;
  	if(i<6){
  		fhEtaOmegacccVsEta_gen[i] = 0x0;
		fhPtOmegacccVsPt_gen[i] = 0x0;
		fhYOmegacccVsY_gen[i] = 0x0;
	}
	if(i<5){
		fhEtaOmegaccVsEta_gen[i] = 0x0;
		fhPtOmegaccVsPt_gen[i] = 0x0;
		fhYOmegaccVsY_gen[i] = 0x0;
	}
	if(i<4){
		fhEtaOmegacVsEta_gen[i] = 0x0;
		fhPtOmegacVsPt_gen[i] = 0x0;
		fhYOmegacVsY_gen[i] = 0x0;
		fPiGenFromVsPtGen[i] = 0x0;
		fPiRecoFromVsPtGen[i] = 0x0;
	}
 	}

//cuts 
//Omegac
fOmegacCuts[0]=0.1;//0.1; 	//inv mass window
fOmegacCuts[1]=-9999.; 		//pt min
fOmegacCuts[2]=-9999.; 		//min decLXY
fOmegacCuts[3]=-9999.;		//min imp par cbaryon
fOmegacCuts[4]=-9999.;		//min imp par track
fOmegacCuts[5]=-9999.;		//min pt track
fOmegacCuts[6]=-9999.;		//cosThetaStar pion
fOmegacCuts[7]=-9999.;		//min cosThetaPointXY

//Omegac
fOmegaccCuts[0]=0.3;//0.1; 	//inv mass window
fOmegaccCuts[1]=-9999.; 	//pt min
fOmegaccCuts[2]=-9999.; 	//min decLXY
fOmegaccCuts[3]=-9999.;		//min imp par cbaryon
fOmegaccCuts[4]=-9999.;		//min imp par track
fOmegaccCuts[5]=-9999.;		//min pt track
fOmegaccCuts[6]=-9999.;		//cosThetaStar pion
fOmegaccCuts[7]=-9999.;		//min cosThetaPointXY

//Omegac
fOmegacccCuts[0]=0.5;//0.1; 	    //inv mass window
fOmegacccCuts[1]=-9999.; 		//pt min
fOmegacccCuts[2]=-9999.; 		//min decLXY
fOmegacccCuts[3]=-9999.;		//min imp par cbaryon
fOmegacccCuts[4]=-9999.;		//min imp par track
fOmegacccCuts[5]=-9999.;		//min pt track
fOmegacccCuts[6]=-9999.;		//cosThetaStar pion
fOmegacccCuts[7]=-9999.;		//min cosThetaPointXY


    
    DefineInput(0, TChain::Class());
    // Output slot #1 writes into a TH1F container (number of events)
    DefineOutput(1,TH1F::Class());
    DefineOutput(2,TList::Class());
    DefineOutput(3,TList::Class());
}
//________________________________________________________________________
AliAnalysisTaskSEOmegacccToOmega3Pi::~AliAnalysisTaskSEOmegacccToOmega3Pi()
{
   
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
    fOutputGen->SetOwner();
    
    nameoutput=GetOutputSlot(3)->GetContainer()->GetName();
    fOutputReco = new TList();
    fOutputReco->SetName(nameoutput);
    fOutputReco->SetOwner();
    
    fHistNcollHFtype     =new TH2F("hNcollHFtype","",5,-1.5,3.5,110,-0.5,109.5);
    fOutputGen->Add(fHistNcollHFtype);
    fHistNinjectedbvsb   =new TH2F("hNinjectedbvsb","",50,0.,20.,140,-0.5,139.5);
    fOutputGen->Add(fHistNinjectedbvsb);
    fHistNinjectedcvsb   =new TH2F("hNinjectedcvsb","",50,0.,20.,140,-0.5,139.5);
    fOutputGen->Add(fHistNinjectedcvsb);
   
    fHistnHitsVsGenPt    =new TH2F("fHistnHitsVsGenPt","RecoTracks;gen p_{T} (GeV/c);n hits",200,0.,20.,11,-0.5,10.5);
    fHistnHitsVsGenY     =new TH2F("fHistnHitsVsGenY","RecoTracks;gen y;n hits",100,-5.,5.,11,-0.5,10.5);
    fHistnHitsVsGenEta   =new TH2F("fHistnHitsVsGenEta","RecoTracks;gen #eta;n hints",100,-5.,5.,11,-0.5,10.5);
    fHistnHitsVsProdRad  =new TH2F("fHistnHitsVsProdRad","RecoTracks;prod radius (cm);n hits",1000,0.,100.,11,-0.5,10.5);
    fHistRecoPtVsGenPt   =new TH2F("fHistRecoPtVsGenPt","RecoTracks;gen p_{T} (GeV/c);reco p_{T} (GeV/c)",200,0.,20,200,0.,20);
    fHistRecoYVsGenY     =new TH2F("fHistRecoYVsGenY","RecoTracks;gen y;reco y",100,-5.,5.,100,-5.,5.);
    fHistRecoEtaVsGenEta =new TH2F("fHistRecoEtaVsGenEta","RecoTracks;gen #eta;reco #eta",100,-5.,5.,100,-5.,5.);
    
    fOutputReco->Add(fHistnHitsVsGenPt);
    fOutputReco->Add(fHistnHitsVsGenY);
    fOutputReco->Add(fHistnHitsVsGenEta);
    fOutputReco->Add(fHistnHitsVsProdRad);
    fOutputReco->Add(fHistRecoPtVsGenPt);
    fOutputReco->Add(fHistRecoYVsGenY);
    fOutputReco->Add(fHistRecoEtaVsGenEta);
    
    fHistGenVertexX    = new TH1F("fHistGenVertexX","fHistGenVertexX;entries;x vtx",2000,-0.2,0.2);
    fHistGenVertexY    = new TH1F("fHistGenVertexY","fHistGenVertexY;entries;y vtx",2000,-0.2,0.2);
    fHistGenVertexZ    = new TH1F("fHistGenVertexZ","fHistGenVertexZ;entries;z vtx",2000,-0.2,0.2);
    fHistRecoVertexX   = new TH1F("fHistRecoVertexX","fHistRecoVertexX;entries;x vtx",2000,-0.2,0.2);
    fHistRecoVertexY   = new TH1F("fHistRecoVertexY","fHistRecoVertexY;entries;y vtx",2000,-0.2,0.2);
    fHistRecoVertexZ   = new TH1F("fHistRecoVertexZ","fHistRecoVertexZ;entries;z vtx",2000,-0.2,0.2);
    fHistGenVertexSigmaX = new TH1F("fHistGenVertexSigmaX","fHistGenVertexSigmaX;entries;sigma x vtx",2000,-0.2,0.2);
    fHistGenVertexSigmaY = new TH1F("fHistGenVertexSigmaY","fHistGenVertexSigmaY;entries;sigma y vtx",2000,-0.2,0.2);
    fHistGenVertexSigmaZ = new TH1F("fHistGenVertexSigmaZ","fHistGenVertexSigmaZ;entries;sigma z vtx",2000,-0.2,0.2);
    fHistRecoVertexSigmaX = new TH1F("fHistRecoVertexSigmaX","fHistRecoVertexSigmaX;entries;sigma x vtx",2000,-0.2,0.2);
    fHistRecoVertexSigmaY = new TH1F("fHistRecoVertexSigmaY","fHistRecoVertexSigmaY;entries;sigma y vtx",2000,-0.2,0.2);
    fHistRecoVertexSigmaZ = new TH1F("fHistRecoVertexSigmaZ","fHistRecoVertexSigmaZ;entries;sigma z vtx",2000,-0.2,0.2);

    fOutputGen->Add(fHistGenVertexX); 
    fOutputGen->Add(fHistGenVertexY);
    fOutputGen->Add(fHistGenVertexZ); 
    fOutputReco->Add(fHistRecoVertexX);
    fOutputReco->Add(fHistRecoVertexY);
    fOutputReco->Add(fHistRecoVertexZ);
    fOutputGen->Add(fHistGenVertexSigmaX); 
    fOutputGen->Add(fHistGenVertexSigmaY);
    fOutputGen->Add(fHistGenVertexSigmaZ); 
    fOutputReco->Add(fHistRecoVertexSigmaX);
    fOutputReco->Add(fHistRecoVertexSigmaY);
    fOutputReco->Add(fHistRecoVertexSigmaZ);
    
    //reco tracks
    fhPtGenEtaGenNhits_pi    = new TH3F("hPtGenEtaGenNhits_pi","hPtGenEtaGenNhits_pi;pt gen;eta gen;n hits",200,0.,20,100,-5.,5.,11,-0.5,10.5);
    fhPtGenEtaGenNhits_p     = new TH3F("hPtGenEtaGenNhits_p","hPtGenEtaGenNhits_p;pt gen;eta gen;n hits",200,0.,20,100,-5.,5.,11,-0.5,10.5);
    fhPtGenEtaGenNhits_k     = new TH3F("hPtGenEtaGenNhits_k","hPtGenEtaGenNhits_k;pt gen;eta gen;n hits",200,0.,20,100,-5.,5.,11,-0.5,10.5);
    fhPtRecoEtaRecoNhits_pi  = new TH3F("hPtRecoEtaRecoNhits_pi","hPtRecoEtaRecoNhits_pi;pt gen;eta gen;n hits",200,0.,20.,100,-5.,5.,11,-0.5,10.5);
    fhPtRecoEtaRecoNhits_p   = new TH3F("hPtRecoEtaRecoNhits_p","hPtRecoEtaRecoNhits_p;pt gen;eta gen;n hits",200,0.,20.,100,-5.,5.,11,-0.5,10.5);
    fhPtRecoEtaRecoNhits_k   = new TH3F("hPtRecoEtaRecoNhits_k","hPtRecoEtaRecoNhits_k;pt gen;eta gen;n hits",200,0.,20.,100,-5.,5.,11,-0.5,10.5);
    
    //pt eta distrib gen reco
    fhPtGenEtaGen_piReco   = new TH2F("hPtGenEtaGen_piReco","hPtGenEtaGen_piReco;pt gen;eta gen",200,0.,20.,100,-5.,5.);
    fhPtGenEtaGen_pReco    = new TH2F("hPtGenEtaGen_pReco","hPtGenEtaGen_pReco;pt gen;eta gen",200,0.,20.,100,-5.,5.);
    fhPtGenEtaGen_kReco    = new TH2F("hPtGenEtaGen_kReco","hPtGenEtaGen_kReco;pt gen;eta gen",200,0.,20.,100,-5.,5.);
    fhPtGenEtaGen_LambdaReco        = new TH2F("hPtGenEtaGen_LambdaReco","hPtGenEtaGen_LambdaReco;pt gen;eta gen",200,0.,20.,100,-5.,5.);
    fhPtGenEtaGen_OmegaReco         = new TH2F("hPtGenEtaGen_OmegaReco","hPtGenEtaGen_OmegaReco;pt gen;eta gen",200,0.,20.,100,-5.,5.);
    fhPtGenEtaGen_OmegacReco        = new TH2F("hPtGenEtaGen_OmegacReco","hPtGenEtaGen_OmegacReco;pt gen;eta gen",200,0.,20.,100,-5.,5.);
    fhPtGenEtaGen_OmegaccReco       = new TH2F("hPtGenEtaGen_OmegaccReco","hPtGenEtaGen_OmegaccReco;pt gen;eta gen",200,0.,20.,100,-5.,5.);
    fhPtGenEtaGen_OmegacccReco      = new TH2F("hPtGenEtaGen_OmegacccReco","hPtGenEtaGen_OmegacccReco;pt gen;eta gen",200,0.,20.,100,-5.,5.);
     
    fOutputReco->Add(fhPtGenEtaGenNhits_pi);
    fOutputReco->Add(fhPtGenEtaGenNhits_p);   
    fOutputReco->Add(fhPtGenEtaGenNhits_k);   
    fOutputReco->Add(fhPtRecoEtaRecoNhits_pi);
    fOutputReco->Add(fhPtRecoEtaRecoNhits_p); 
    fOutputReco->Add(fhPtRecoEtaRecoNhits_k); 
    fOutputReco->Add(fhPtGenEtaGen_piReco);
    fOutputReco->Add(fhPtGenEtaGen_pReco); 
    fOutputReco->Add(fhPtGenEtaGen_kReco); 
    fOutputReco->Add(fhPtGenEtaGen_LambdaReco);     
    fOutputReco->Add(fhPtGenEtaGen_OmegaReco); 
    fOutputReco->Add(fhPtGenEtaGen_OmegacReco); 
    fOutputReco->Add(fhPtGenEtaGen_OmegaccReco); 
    fOutputReco->Add(fhPtGenEtaGen_OmegacccReco);     
    

    Int_t nBinscb=200;
    Double_t maxncn=nBinscb-0.5;
    fHistoNbVsNcPYTHIA = new TH2F("fHistoNbVsNcPYTHIA","",nBinscb,-0.5,maxncn,nBinscb,-0.5,maxncn);
    fHistoNbVsNcHIJING = new TH2F("fHistoNbVsNcHIJING","",nBinscb,-0.5,maxncn,nBinscb,-0.5,maxncn);
    fOutputGen->Add(fHistoNbVsNcPYTHIA);
    fOutputGen->Add(fHistoNbVsNcHIJING);
    
    
    //Histograms for signal
    fhV0radiusS          = new TH1D("fhV0radiusS",";V0 radius (cm)",200,0.,20.);
    fhDCAnegToPVS        = new TH1D("fhDCAnegToPVS",";DCA neg to PV (cm)",20,0.,2.);
    fhDCAposToPVS        = new TH1D("fhDCAposToPVS",";DCA pos to PV (cm)",20,0.,2.);
    fhDCAV0DaughtersS    = new TH1D("fhDCAV0DaughtersS",";DCA V0 daughters (cm)",200,0.,2.);
    fhCosinePointAS      = new TH1D("fhCosinePointAS",";Cosine PA",100,0.,1.);
    fhProperLifetimeS    = new TH1D("fhProperLifetimeS",";Proper Lifetime (cm/c)",200,0.,20.);
    fHistMassLambdaS     = new TH1F("fHistMassLambdaS","#Lambda candidates;M( #Lambda) (GeV/c^{2});Counts", 500,0.5,1.5);
    fHistMassAntiLambdaS = new TH1F("fHistMassAntiLambdaS","#bar{#Lambda} candidates;M( #bar{#Lambda}) (GeV/c^{2});Counts", 500,0.5,1.5);
    fhV0ptS              = new TH1D("fhV0ptS",";V0 pt (GeV/c)",200,0.,20.);
    fOutputReco->Add(fhV0radiusS);
    fOutputReco->Add(fhDCAnegToPVS);
    fOutputReco->Add(fhDCAposToPVS);
    fOutputReco->Add(fhDCAV0DaughtersS);
    fOutputReco->Add(fhCosinePointAS);
    fOutputReco->Add(fHistMassLambdaS);
    fOutputReco->Add(fHistMassAntiLambdaS);
    fOutputReco->Add(fhV0ptS);
    
    //Histograms for background
    fhV0radiusB          = new TH1D("fhV0radiusB",";V0 radius (cm)",200,0.,20.);
    fhDCAnegToPVB        = new TH1D("fhDCAnegToPVB",";DCA neg to PV (cm)",20,0.,2.);
    fhDCAposToPVB        = new TH1D("fhDCAposToPVB",";DCA pos to PV (cm)",20,0.,2.);
    fhDCAV0DaughtersB    = new TH1D("fhDCAV0DaughtersB",";DCA V0 daughters (cm)",200,0.,2.);
    fhCosinePointAB      = new TH1D("fhCosinePointAB",";Cosine PA",100,0.,1.);
    fhProperLifetimeB    = new TH1D("fhProperLifetimeB",";Proper Lifetime (cm/c)",200,0.,20.);
    fHistMassLambdaB     = new TH1F("fHistMassLambdaB","#Lambda candidates;M( #Lambda) (GeV/c^{2});Counts", 500,0.5,1.5);
    fHistMassAntiLambdaB = new TH1F("fHistMassAntiLambdaB","#bar{#Lambda} candidates;M( #bar{#Lambda}) (GeV/c^{2});Counts", 500,0.5,1.5);
    fhV0ptB              = new TH1D("fhV0ptB",";V0 pt (GeV/c)",200,0.,20.);
    fOutputReco->Add(fhV0radiusB);
    fOutputReco->Add(fhDCAnegToPVB);
    fOutputReco->Add(fhDCAposToPVB);
    fOutputReco->Add(fhDCAV0DaughtersB);
    fOutputReco->Add(fhCosinePointAB);
    fOutputReco->Add(fHistMassLambdaB);
    fOutputReco->Add(fHistMassAntiLambdaB);
    fOutputReco->Add(fhV0ptB);
    
    
    //cascades
    fCascInvMassS           = new TH1F("fCascInvMassS","#Omega candidates;M(#Omega) (GeV/c^{2});Counts", 2000,0.,2.);
	fCascRadiusS            = new TH1F("fCascRadiusS",";casc radius (cm)",200,0.,20.);
	fCascPtS                = new TH1F("fCascPtS",";pt",100,0.,20.);
	fCascCosPointAngleS     = new TH1F("fCascCosPointAngleS",";Cosine PA",100,0.,1.);
	fCascInvMassB           = new TH1F("fCascInvMassB","#Omega candidates;M(#Omega) (GeV/c^{2});Counts", 2000,0.,2.);
	fCascRadiusB            = new TH1F("fCascRadiusB",";casc radius (cm)",200,0.,20.);
	fCascPtB                = new TH1F("fCascPtB",";pt",100,0.,20.);
	fCascCosPointAngleB     = new TH1F("fCascCosPointAngleB",";Cosine PA",100,0.,1.);
	//Omegac
	fOmegacInvMassS          = new TH1F("fOmegacInvMassS","#Omega_{c} candidates;M(#Omega#pi) (GeV/c^{2});Counts", 2000,1.,3.);
	fOmegacPtS               = new TH1F("fOmegacPtS",";pt",100,0.,20.);
	fOmegacDecayLenghtXYS    = new TH1F("fOmegacDecayLenghtXYS",";decl XY",500,0.,5.);
	fOmegacCosPointAngleXYS  = new TH1F("fOmegacCosPointAngleXYS",";Cosine PA",200,-1.,1.); 
	fOmegacPiond0S           = new TH1F("fOmegacPiond0S",";DCA pion (cm)",400,-1.,1.);
	fOmegacd0S               = new TH1F("fOmegacd0S",";DCA omegac (cm)",400,-1.,1.);
	fOmegacPionCosThetaStarS = new TH1F("fOmegacPionCosThetaStarS",";Cosine #theta^{*}",200,-1.,1.);
	fOmegacInvMassB          = new TH1F("fOmegacInvMassB","#Omega_{c} candidates;M(#Omega#pi) (GeV/c^{2});Counts", 2000,1.,3.);
	fOmegacPtB               = new TH1F("fOmegacPtB",";pt",100,0.,20.);
	fOmegacDecayLenghtXYB    = new TH1F("fOmegacDecayLenghtXYB",";decl XY",500,0.,5.);
	fOmegacCosPointAngleXYB  = new TH1F("fOmegacCosPointAngleXYB",";Cosine PA",200,-1.,1.); 
	fOmegacPiond0B           = new TH1F("fOmegacPiond0B",";DCA pion (cm)",400,-1.,1.);
	fOmegacd0B               = new TH1F("fOmegacd0B",";DCA omegac (cm)",400,-1.,1.);
	fOmegacPionCosThetaStarB = new TH1F("fOmegacPionCosThetaStarB",";Cosine #theta^{*}",200,-1.,1.);
	//Omegacc
	fOmegaccInvMassS          = new TH1F("fOmegaccInvMassS","#Omega_{cc} candidates;M(#Omega_{c}#pi) (GeV/c^{2});Counts", 2000,2.5,4.5);
	fOmegaccPtS               = new TH1F("fOmegaccPtS",";pt",100,0.,20.);
	fOmegaccDecayLenghtXYS    = new TH1F("fOmegaccDecayLenghtXYS",";decl XY",500,0.,5.);
	fOmegaccCosPointAngleXYS  = new TH1F("fOmegaccCosPointAngleXYS",";Cosine PA",200,-1.,1.); 
	fOmegaccPiond0S           = new TH1F("fOmegaccPiond0S",";DCA pion (cm)",400,-1.,1.);
	fOmegaccd0S               = new TH1F("fOmegaccd0S",";DCA omegacc (cm)",400,-1.,1.);
	fOmegaccPionCosThetaStarS = new TH1F("fOmegaccPionCosThetaStarS",";Cosine #theta^{*}",200,-1.,1.);
	fOmegaccInvMassB          = new TH1F("fOmegaccInvMassB","#Omega_{cc} candidates;M(#Omega_{c}#pi) (GeV/c^{2});Counts", 2000,2.5,4.5);
	fOmegaccPtB               = new TH1F("fOmegaccPtB",";pt",100,0.,20.);
	fOmegaccDecayLenghtXYB    = new TH1F("fOmegaccDecayLenghtXYB",";decl XY",500,0.,5.);
	fOmegaccCosPointAngleXYB  = new TH1F("fOmegaccCosPointAngleXYB",";Cosine PA",200,-1.,1.); 
	fOmegaccPiond0B           = new TH1F("fOmegaccPiond0B",";DCA pion (cm)",400,-1.,1.);
	fOmegaccd0B               = new TH1F("fOmegaccd0B",";DCA omegacc (cm)",400,-1.,1.);
	fOmegaccPionCosThetaStarB = new TH1F("fOmegaccPionCosThetaStarB",";Cosine #theta^{*}",200,-1.,1.);
	//Omegaccc
	fOmegacccInvMassS          = new TH1F("fOmegacccInvMassS","#Omega_{ccc} candidates;M(#Omega_{cc}#pi) (GeV/c^{2});Counts", 2000,3.5,5.5);
	fOmegacccPtS               = new TH1F("fOmegacccPtS",";pt",100,0.,20.);
	fOmegacccDecayLenghtXYS    = new TH1F("fOmegacccDecayLenghtXYS",";decl XY",500,0.,5.);
	fOmegacccCosPointAngleXYS  = new TH1F("fOmegacccCosPointAngleXYS",";Cosine PA",200,-1.,1.); 
	fOmegacccPiond0S           = new TH1F("fOmegacccPiond0S",";DCA pion (cm)",400,-1.,1.);
	fOmegacccd0S               = new TH1F("fOmegacccd0S",";DCA omegaccc (cm)",400,-1.,1.);
	fOmegacccPionCosThetaStarS = new TH1F("fOmegacccPionCosThetaStarS",";Cosine #theta^{*}",200,-1.,1.);
	fOmegacccInvMassB          = new TH1F("fOmegacccInvMassB","#Omega_{ccc} candidates;M(#Omega_{cc}#pi) (GeV/c^{2});Counts", 2000,3.5,5.5);
	fOmegacccPtB               = new TH1F("fOmegacccPtB",";pt",100,0.,20.);
	fOmegacccDecayLenghtXYB    = new TH1F("fOmegacccDecayLenghtXYB",";decl XY",500,0.,5.);
	fOmegacccCosPointAngleXYB  = new TH1F("fOmegacccCosPointAngleXYB",";Cosine PA",200,-1.,1.); 
	fOmegacccPiond0B           = new TH1F("fOmegacccPiond0B",";DCA pion (cm)",400,-1.,1.);
	fOmegacccd0B               = new TH1F("fOmegacccd0B",";DCA omegaccc (cm)",400,-1.,1.);
	fOmegacccPionCosThetaStarB = new TH1F("fOmegacccPionCosThetaStarB",";Cosine #theta^{*}",200,-1.,1.);
    
    fOutputReco->Add(fCascInvMassS);           
    fOutputReco->Add(fCascRadiusS);            
	fOutputReco->Add(fCascPtS);                
	fOutputReco->Add(fCascCosPointAngleS);     
	fOutputReco->Add(fCascInvMassB);           
	fOutputReco->Add(fCascRadiusB);            
	fOutputReco->Add(fCascPtB);                
	fOutputReco->Add(fCascCosPointAngleB);     
	fOutputReco->Add(fOmegacInvMassS);         
	fOutputReco->Add(fOmegacPtS);              
	fOutputReco->Add(fOmegacDecayLenghtXYS);   
	fOutputReco->Add(fOmegacCosPointAngleXYS); 
	fOutputReco->Add(fOmegacPiond0S); 
	fOutputReco->Add(fOmegacd0S);
	fOutputReco->Add(fOmegacPionCosThetaStarS);          
	fOutputReco->Add(fOmegacInvMassB);         
	fOutputReco->Add(fOmegacPtB);              
	fOutputReco->Add(fOmegacDecayLenghtXYB);   
	fOutputReco->Add(fOmegacCosPointAngleXYB); 
	fOutputReco->Add(fOmegacPiond0B);
	fOutputReco->Add(fOmegacd0B);  
	fOutputReco->Add(fOmegacPionCosThetaStarB);         
	fOutputReco->Add(fOmegaccInvMassS);        
	fOutputReco->Add(fOmegaccPtS);             
	fOutputReco->Add(fOmegaccDecayLenghtXYS);  
	fOutputReco->Add(fOmegaccCosPointAngleXYS);
	fOutputReco->Add(fOmegaccPiond0S);    
	fOutputReco->Add(fOmegaccd0S); 
	fOutputReco->Add(fOmegaccPionCosThetaStarS);         
	fOutputReco->Add(fOmegaccInvMassB);        
	fOutputReco->Add(fOmegaccPtB);             
	fOutputReco->Add(fOmegaccDecayLenghtXYB);  
	fOutputReco->Add(fOmegaccCosPointAngleXYB);
	fOutputReco->Add(fOmegaccPiond0B); 
	fOutputReco->Add(fOmegaccd0B); 
	fOutputReco->Add(fOmegaccPionCosThetaStarB);        
	fOutputReco->Add(fOmegacccInvMassS);        
	fOutputReco->Add(fOmegacccPtS);             
	fOutputReco->Add(fOmegacccDecayLenghtXYS);  
	fOutputReco->Add(fOmegacccCosPointAngleXYS);
	fOutputReco->Add(fOmegacccPiond0S);
	fOutputReco->Add(fOmegacccd0S);
	fOutputReco->Add(fOmegacccPionCosThetaStarS);          
	fOutputReco->Add(fOmegacccInvMassB);        
	fOutputReco->Add(fOmegacccPtB);        
	fOutputReco->Add(fOmegacccDecayLenghtXYB);  
	fOutputReco->Add(fOmegacccCosPointAngleXYB);
	fOutputReco->Add(fOmegacccPiond0B);  
	fOutputReco->Add(fOmegacccd0B);  
	fOutputReco->Add(fOmegacccPionCosThetaStarB); 
	
	
	fOmegacVtxXGen     			= new TH1F("fOmegacVtxXGen",";x (cm);counts",4000,-2.,2.);
	fOmegacVtxYGen     			= new TH1F("fOmegacVtxYGen",";y (cm);counts",4000,-2.,2.);
	fOmegacVtxZGen 	   			= new TH1F("fOmegacVtxZGen",";z (cm);counts",4000,-2.,2.);
	fOmegaccVtxXGen    			= new TH1F("fOmegaccVtxXGen",";x (cm);counts",4000,-2.,2.);
	fOmegaccVtxYGen    			= new TH1F("fOmegaccVtxYGen",";y (cm);counts",4000,-2.,2.);
	fOmegaccVtxZGen    			= new TH1F("fOmegaccVtxZGen",";z (cm);counts",4000,-2.,2.);
	fOmegacccVtxXGen   			= new TH1F("fOmegacccVtxXGen",";x (cm);counts",4000,-2.,2.);
	fOmegacccVtxYGen   			= new TH1F("fOmegacccVtxYGen",";y (cm);counts",4000,-2.,2.);
	fOmegacccVtxZGen   			= new TH1F("fOmegacccVtxZGen",";z (cm);counts",4000,-2.,2.);
	fOmegacVtxXReco    			= new TH1F("fOmegacVtxXReco",";x (cm);counts",4000,-2.,2.);
	fOmegacVtxYReco    			= new TH1F("fOmegacVtxYReco",";y (cm);counts",4000,-2.,2.);
	fOmegacVtxZReco    			= new TH1F("fOmegacVtxZReco",";z (cm);counts",4000,-2.,2.);
	fOmegaccVtxXReco   			= new TH1F("fOmegaccVtxXReco",";x (cm);counts",4000,-2.,2.);
	fOmegaccVtxYReco   			= new TH1F("fOmegaccVtxYReco",";y (cm);counts",4000,-2.,2.);
	fOmegaccVtxZReco   			= new TH1F("fOmegaccVtxZReco",";z (cm);counts",4000,-2.,2.);
	fOmegacccVtxXReco  			= new TH1F("fOmegacccVtxXReco",";x (cm);counts",4000,-2.,2.);
	fOmegacccVtxYReco  			= new TH1F("fOmegacccVtxYReco",";y (cm);counts",4000,-2.,2.);
	fOmegacccVtxZReco  			= new TH1F("fOmegacccVtxZReco",";z (cm);counts",4000,-2.,2.);
	fOmegacGenVsPtGen					= new TH1F("fOmegacGenVsPtGen",";pt (GeV/c);counts",200,0.,20.);
	fOmegacRecoVsPtGen					= new TH1F("fOmegacRecoVsPtGen",";pt (GeV/c);counts",200,0.,20.);
	fOmegaccGenVsPtGen					= new TH1F("fOmegaccGenVsPtGen",";pt (GeV/c);counts",200,0.,20.);
	fOmegaccRecoVsPtGen 				= new TH1F("fOmegaccRecoVsPtGen",";pt (GeV/c);counts",200,0.,20.);
	fOmegacccGenVsPtGen 				= new TH1F("fOmegacccGenVsPtGen",";pt (GeV/c);counts",200,0.,20.);
	fOmegacccRecoVsPtGen   				= new TH1F("fOmegacccRecoVsPtGen",";pt (GeV/c);counts",200,0.,20.);
	fKGenVsPtGen				= new TH1F("fKGenVsPtGen",";pt (GeV/c);counts",200,0.,20.);
	fPGenVsPtGen				= new TH1F("fPGenVsPtGen",";pt (GeV/c);counts",200,0.,20.);
	fKRecoVsPtGen				= new TH1F("fKRecoVsPtGen",";pt (GeV/c);counts",200,0.,20.);
	fPRecoVsPtGen				= new TH1F("fPRecoVsPtGen",";pt (GeV/c);counts",200,0.,20.);
	
	
	fOutputReco->Add(fOmegacVtxXGen); 
	fOutputReco->Add(fOmegacVtxYGen); 
	fOutputReco->Add(fOmegacVtxZGen); 
	fOutputReco->Add(fOmegaccVtxXGen); 
	fOutputReco->Add(fOmegaccVtxYGen); 
	fOutputReco->Add(fOmegaccVtxZGen); 
	fOutputReco->Add(fOmegacccVtxXGen); 
	fOutputReco->Add(fOmegacccVtxYGen); 
	fOutputReco->Add(fOmegacccVtxZGen); 
	fOutputReco->Add(fOmegacVtxXReco); 
	fOutputReco->Add(fOmegacVtxYReco); 
	fOutputReco->Add(fOmegacVtxZReco); 
	fOutputReco->Add(fOmegaccVtxXReco); 
	fOutputReco->Add(fOmegaccVtxYReco); 
	fOutputReco->Add(fOmegaccVtxZReco); 
	fOutputReco->Add(fOmegacccVtxXReco); 
	fOutputReco->Add(fOmegacccVtxYReco); 
	fOutputReco->Add(fOmegacccVtxZReco); 
	fOutputReco->Add(fOmegacGenVsPtGen); 
	fOutputReco->Add(fOmegacRecoVsPtGen); 
	fOutputReco->Add(fOmegaccGenVsPtGen); 
	fOutputReco->Add(fOmegaccRecoVsPtGen); 
	fOutputReco->Add(fOmegacccGenVsPtGen); 
	fOutputReco->Add(fOmegacccRecoVsPtGen); 
	fOutputReco->Add(fKGenVsPtGen); 
	fOutputReco->Add(fPGenVsPtGen); 
	fOutputReco->Add(fKRecoVsPtGen); 
	fOutputReco->Add(fPRecoVsPtGen); 
	  
	TString mother[10] = {"Omegaccc","Omegaccc","Omegacc","Omegacc","Omegac","Omegac","Omega", "Omega","Lambda","Lambda"};
	TString daught[10] = {"Omegac",  "pion",    "Omegac", "pion",   "Omega", "pion",  "Lambda","Kaon", "pion",  "proton"};
	
	for(Int_t n=0; n<10; n++){
    	fhEtaDauVsEtaMoth_Gen[n] =new TH2F(Form("hEta%sVs%s_gen",mother[n].Data(),daught[n].Data()),Form("hEta%sVs%s;#eta gen %s;#eta gen %s",mother[n].Data(),daught[n].Data(),mother[n].Data(),daught[n].Data()),100,-5.,5.,100,-5.,5.); 
    	fOutputGen->Add(fhEtaDauVsEtaMoth_Gen[n]);
		fhEtaDauVsEtaMoth_Rec[n]=new TH2F(Form("hEta%sVs%s_rec",mother[n].Data(),daught[n].Data()),Form("hEta%sVs%s;#eta gen %s;#eta gen %s",mother[n].Data(),daught[n].Data(),mother[n].Data(),daught[n].Data()),100,-5.,5.,100,-5.,5.);
    	fOutputReco->Add(fhEtaDauVsEtaMoth_Rec[n]);
    }
    
    
    TString motherr[4] = {"Omegaccc","Omegacc","Omegac","Lambda"};
    for(Int_t i=0; i<4; i++){
       fPiGenFromVsPtGen[i]  = new TH1F(Form("fPiGenFrom%sVsPtGen",motherr[i].Data()),Form("gen #pi from %s;pt (GeV/c);counts",motherr[i].Data()),200,0.,20.);
       fPiRecoFromVsPtGen[i] = new TH1F(Form("fPiRecoFrom%sVsPtGen",motherr[i].Data()),Form("reco #pi from %s;pt (GeV/c);counts",motherr[i].Data()),200,0.,20.);
       fOutputGen->Add(fPiGenFromVsPtGen[i]);
       fOutputReco->Add(fPiRecoFromVsPtGen[i]);
    }
    fhOmegaGenVsPtGen   = new TH1F("fhOmegaGenVsPtGen","Omega gen;pt (GeV/c);counts",200,0.,20.);
    fhLambdaGenVsPtGen  = new TH1F("fhLambdaGenVsPtGen","Lambda gen;pt (GeV/c);counts",200,0.,20.);
    fhOmegaRecoVsPtGen  = new TH1F("fhOmegaRecoVsPtGen","Omega reco;pt (GeV/c);counts",200,0.,20.);
    fhLambdaRecoVsPtGen = new TH1F("fhLambdaRecoVsPtGen","Lambda reco;pt (GeV/c);counts",200,0.,20.);
    fOutputGen->Add(fhOmegaGenVsPtGen);
    fOutputGen->Add(fhLambdaGenVsPtGen);
    fOutputReco->Add(fhOmegaRecoVsPtGen);
    fOutputReco->Add(fhLambdaRecoVsPtGen);
            	        	
    TString omegaccc[6] = {"OmegacccVsPiccc","OmegacccVsPicc","OmegacccVsPic","OmegacccVsK","OmegacccVsPiL","OmegacccVsPL"};
    TString omegacc[5]  = {"OmegaccVsPicc","OmegaccVsPic","OmegaccVsK","OmegaccVsPiL","OmegaccVsPL"};
    TString omegac[4]   = {"OmegacVsPic","OmegacVsK","OmegacVsPiL","OmegacVsPL"};
    TString cbaryon[3]  = {"#Omega_{ccc}","#Omega_{cc}","#Omega_{c}"};
    TString daugh[6]    = {"#pi_{ccc}","#pi_{cc}","#pi_{c}","k","#pi_{#Lambda}","p_{#Lambda}"};
             
    for(Int_t iii=0; iii<6; iii++){
             	fhEtaOmegacccVsEta_gen[iii] = new TH2F(Form("fhEta%s_gen",omegaccc[iii].Data()), Form("fhEta%s_gen;#eta gen %s; #eta gen %s",omegaccc[iii].Data(),cbaryon[0].Data(),daugh[iii].Data()),100,-5.,5.,100,-5.,5.);
             	fOutputGen->Add(fhEtaOmegacccVsEta_gen[iii]);
             	fhPtOmegacccVsPt_gen[iii]   = new TH2F(Form("fhPt%s_gen",omegaccc[iii].Data()), Form("fhPt%s_gen;pt gen %s; pt gen %s",omegaccc[iii].Data(),cbaryon[0].Data(),daugh[iii].Data()),200,0.,20.,200,0.,20.);
             	fOutputGen->Add(fhPtOmegacccVsPt_gen[iii]);
             	fhYOmegacccVsY_gen[iii]     = new TH2F(Form("fhY%s_gen",omegaccc[iii].Data()), Form("fhY%s_gen;y gen %s; y gen %s",omegaccc[iii].Data(),cbaryon[0].Data(),daugh[iii].Data()),100,-5.,5.,100,-5.,5.);
             	fOutputGen->Add(fhYOmegacccVsY_gen[iii]);
    }
    for(Int_t ii=0; ii<5; ii++){
             	fhEtaOmegaccVsEta_gen[ii] = new TH2F(Form("fhEta%s_gen",omegacc[ii].Data()), Form("fhEta%s_gen;#eta gen %s; #eta gen %s",omegacc[ii].Data(),cbaryon[1].Data(),daugh[ii+1].Data()),100,-5.,5.,100,-5.,5.);
             	fOutputGen->Add(fhEtaOmegaccVsEta_gen[ii]);
             	fhPtOmegaccVsPt_gen[ii]   = new TH2F(Form("fhPt%s_gen",omegacc[ii].Data()), Form("fhPt%s_gen;pt gen %s; pt gen %s",omegacc[ii].Data(),cbaryon[1].Data(),daugh[ii+1].Data()),200,0.,20.,200,0.,20.);
             	fOutputGen->Add(fhPtOmegaccVsPt_gen[ii]);
             	fhYOmegaccVsY_gen[ii]     = new TH2F(Form("fhY%s_gen",omegacc[ii].Data()), Form("fhY%s_gen;y gen %s; y gen %s",omegacc[ii].Data(),cbaryon[1].Data(),daugh[ii+1].Data()),100,-5.,5.,100,-5.,5.);
             	fOutputGen->Add(fhYOmegaccVsY_gen[ii]);
    }
    for(Int_t i=0; i<4; i++){
             	fhEtaOmegacVsEta_gen[i]   = new TH2F(Form("fhEta%s_gen",omegac[i].Data()), Form("fhEta%s_gen;#eta gen %s; #eta gen %s",omegac[i].Data(),cbaryon[2].Data(),daugh[i+2].Data()),100,-5.,5.,100,-5.,5.);
             	fOutputGen->Add(fhEtaOmegacVsEta_gen[i]);
             	fhPtOmegacVsPt_gen[i]     = new TH2F(Form("fhPt%s_gen",omegac[i].Data()), Form("fhPt%s_gen;pt gen %s; pt gen %s",omegac[i].Data(),cbaryon[2].Data(),daugh[i+2].Data()),200,0.,20.,200,0.,20.);
             	fOutputGen->Add(fhPtOmegacVsPt_gen[i]);
             	fhYOmegacVsY_gen[i]       = new TH2F(Form("fhY%s_gen",omegac[i].Data()), Form("fhY%s_gen;y gen %s; y gen %s",omegac[i].Data(),cbaryon[2].Data(),daugh[i+2].Data()),100,-5.,5.,100,-5.,5.);
             	fOutputGen->Add(fhYOmegacVsY_gen[i]);
    }
    
    // Post the data
    PostData(1,fNentries);
    PostData(2,fOutputGen);
    PostData(3,fOutputReco);
    
   
    return;
}

//________________________________________________________________________
void AliAnalysisTaskSEOmegacccToOmega3Pi::UserExec(Option_t */*option*/)

{
    /// Execute analysis for current event:
    
    cout<< "UserExec" << endl;
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
    // create new ITS detector
    fITS = CreateDetector();
    
    // create dummy vertex for beam diamond
    const double kBeamSig = 3e-4;//50e-4;
    //const double beamPos[3] = {0.,0.,0.};
    //const double beamSig[3] = {kBeamSig, kBeamSig, 6. };
    double beamPos[3] = {0.,0.,0.};
    double beamSig[3] = {kBeamSig, kBeamSig, kBeamSig };
    AliESDVertex diamond(beamPos,beamSig,"diamond");
  
    // access the stack
    fStack = ((AliMCEvent*)fMcEvent)->Stack();
    if(!fStack) {Printf("ERROR: Could not retrieve the Stack"); return;}
    //Printf("MC particles: %d %d", fStack->GetNprimary(),fMcEvent->GetNumberOfTracks());
    
    //check generators
    TString genname=fMcEvent->GenEventHeader()->ClassName();
    //Printf("%s",genname.Data());
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
    
    FillGenDistrib();
    
    // create ESD event
    AliESDEvent *esdEv = new AliESDEvent();
    esdEv->CreateStdContent();
    esdEv->Reset();
    esdEv->SetMagneticField(fITS->GetBField()*10.);
    esdEv->SetDiamond(&diamond);
     
    // fill ESD event
    RecoEvent(esdEv);
    fBzkG = esdEv->GetMagneticField();
    fV1   = (AliESDVertex*)esdEv->GetPrimaryVertexTracks();
    // fill histos with reco tracks
    FillTrackDistributions(esdEv);    
     
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
    v0Finder->Tracks2V0vertices(esdEv);
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
    cascadeFinder->V0sTracks2CascadeVertices(esdEv);
    
    FillV0Histos(esdEv);
    FillCascadeHistos(esdEv);
    
    MakeOmegac(esdEv);

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
Long_t AliAnalysisTaskSEOmegacccToOmega3Pi::MakeOmegac(AliESDEvent *esdEv){


 Printf("\n\n\n ********************************* MakeOmegaC");
 Double_t xPrimaryVertex=fV1->GetX();
 Double_t yPrimaryVertex=fV1->GetY();
 Double_t zPrimaryVertex=fV1->GetZ();

 Int_t nSecVtx=0;
 // get number of cascades
 Long_t nCascades = esdEv->GetNumberOfCascades();
 if(nCascades==0) return 0;
 
 // loop on cascades
 for(Int_t icasc=0; icasc<nCascades; icasc++){
    AliESDcascade *casc = esdEv->GetCascade(icasc);
    if(!casc) continue;
    
    UInt_t lIdxPosCasc 	= (UInt_t) TMath::Abs( casc->GetPindex() );
    UInt_t lIdxNegCasc 	= (UInt_t) TMath::Abs( casc->GetNindex() );
    UInt_t lBachIdx     = (UInt_t) TMath::Abs( casc->GetBindex() );
    if(!lIdxPosCasc || !lIdxNegCasc || !lBachIdx) continue;
    if(lBachIdx == lIdxNegCasc) {
            //Printf("Pb / Idx(Bach. track) = Idx(Neg. track) ... continue!");
            continue;
    }
    if(lBachIdx == lIdxPosCasc) {
            //Printf("Pb / Idx(Bach. track) = Idx(Pos. track) ... continue!");
            continue;
    }
    AliESDtrack *pTrackCasc		= esdEv->GetTrack( lIdxPosCasc );
    AliESDtrack *nTrackCasc		= esdEv->GetTrack( lIdxNegCasc );
    AliESDtrack *bachTrackCasc  = esdEv->GetTrack( lBachIdx );
    if (!pTrackCasc || !nTrackCasc || !bachTrackCasc ) {
            Printf("ERROR: Could not retrieve one of the 3 ESD daughter tracks of the cascade ...");
            continue;
    }
    //Printf("MakeOmegaC::::  --->cascade %d",icasc);
  	//Int_t negV0TrackLabOrigin     = CheckOriginTrack(nTrackCasc);
 	//Int_t posV0TrackLabOrigin     = CheckOriginTrack(pTrackCasc);
 	//Int_t bachCascTrackLabOrigin  = CheckOriginTrack(bachTrackCasc);
 	//Int_t bachCascCTrackLabOrigin = 0;
 	//Int_t bachCascCCTrackLabOrigin = 0;
 	//Int_t bachCascCCCTrackLabOrigin = 0;
 
   
    
    // loop on tracks
    // get number of tracks
    Long_t nentr = (Int_t)esdEv->GetNumberOfTracks();
    for(Int_t i=0; i<nentr; i++){
        //Printf("MakeOmegaC::::  --->track %d",i);
        AliESDtrack *esdtr = esdEv->GetTrack(i);
        
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
        
        ULong_t status = esdtr->GetStatus();
    
        if ((status&AliESDtrack::kITSrefit)==0)
            if ((status&AliESDtrack::kTPCrefit)==0) continue; 
            
        //bachCascCTrackLabOrigin = CheckOriginTrack(esdtr);
        //if (TMath::Abs(esdtr->GetD(xPrimaryVertex,yPrimaryVertex,fBzkG))<fOmegacVertexerSels[0]) continue;
        Double_t dispersion=0.;
        //Printf("\n********************************* CallReconstructSecondaryVertexOmegac");
        AliESDVertex *sVtxOmegac = CallReconstructSecondaryVertexOmegac(esdEv, casc, esdtr, dispersion);
        if(!sVtxOmegac) {//Printf("--> no omega c vertex reco"); 
        	continue;}
        nSecVtx++;
        //Printf("--->FillHistoOmegac");
        //cuts
        bool isselOmegac = FillHistoOmegac(esdEv, casc, esdtr, sVtxOmegac);
        //if(TMath::Abs(fOmegacVariables[0]-TDatabasePDG::Instance()->GetParticle(4332)->Mass())>0.1) {//Printf("continue, mass cut"); 
        //continue;}
        if(!isselOmegac) continue;       
        
        
        //second loop on tracks to build omegacc
        for(Int_t ii=0; ii<nentr; ii++){
        	AliESDtrack *esdtr2 = esdEv->GetTrack(ii);
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
        	ULong_t status = esdtr2->GetStatus();
    
        	if ((status&AliESDtrack::kITSrefit)==0)
            	if ((status&AliESDtrack::kTPCrefit)==0) continue; 
            Double_t dispersion=0.;	
            //Printf("\n********************************* CallReconstructSecondaryVertexOmegacc");
            AliESDVertex *sVtxOmegacc = CallReconstructSecondaryVertexOmegacc(esdEv, sVtxOmegac, casc, esdtr, esdtr2, dispersion);
            if(!sVtxOmegacc) {//Printf("--> no omega cc vertex reco"); 
            	continue;}
            // cuts
            bool isselOmegacc = FillHistoOmegacc(esdEv, casc, esdtr, esdtr2, sVtxOmegac, sVtxOmegacc);
            //if(TMath::Abs(fOmegaccVariables[0]-TDatabasePDG::Instance()->GetParticle(4432)->Mass())>0.1) {//Printf("Omega c mass cut %f ",fOmegaccVariables[0]); 
            //continue;}
            if(!isselOmegacc) continue;
            
            
            //third loop on tracks to build omegaccc
            for(Int_t iii=0; iii<nentr; iii++){
            	AliESDtrack *esdtr3 = esdEv->GetTrack(iii);
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
        		ULong_t status = esdtr3->GetStatus();
    
        		if ((status&AliESDtrack::kITSrefit)==0)
            		if ((status&AliESDtrack::kTPCrefit)==0) continue; 
            	Double_t dispersion=0.;	
            	//Printf("\n********************************* CallReconstructSecondaryVertexOmegaccc");
             	AliESDVertex *sVtxOmegaccc = CallReconstructSecondaryVertexOmegaccc(esdEv,sVtxOmegacc,sVtxOmegac,casc,esdtr,esdtr2,esdtr3,dispersion);
            	if(!sVtxOmegaccc) {//Printf("--> no omega ccc vertex reco"); 
            		continue;}
            	bool isselOmegaccc = FillHistoOmegaccc(esdEv, casc, esdtr, esdtr2, esdtr3, sVtxOmegac, sVtxOmegacc, sVtxOmegaccc);	
            	//cuts
            	//if(TMath::Abs(fOmegacccVariables[0]-TDatabasePDG::Instance()->GetParticle(4444)->Mass())>0.5) continue;
            	//if(TMath::Abs(fOmegacccVariables[0]-TDatabasePDG::Instance()->GetParticle(4444)->Mass())>0.5) continue;
            	
            	//fill histos
            	//FillHisto(esdEv, casc, esdtr, esdtr2, esdtr3, sVtxOmegac, sVtxOmegacc, sVtxOmegaccc);
            
            }// end third loop on tracks
            	
        }//end second loop on tracks
        
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
        			Int_t lblGdMotherBach = 0; lblGdMotherBach = mcMotherBach->GetFirstMother(); 		//label of the grandmother of the bachelor -> omegac label
        			Int_t lblMotherBachC = 0;  lblMotherBachC = partbachTrackCascC->GetFirstMother(); 	//label of the mother of the bachelorC -> omegac label
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
        			Int_t lblGdMotherBach = 0; lblGdMotherBach = mcMotherBach->GetFirstMother(); 		//label of the grandmother of the bachelor -> omegac label
        			Int_t lblMotherBachC = 0;  lblMotherBachC = partbachTrackCascC->GetFirstMother(); 	//label of the mother of the bachelorC -> omegac label
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
	
	Int_t lblpTrackCasc       = pTrackCasc->GetLabel();
	Int_t lblnTrackCasc       = nTrackCasc->GetLabel();
	Int_t lblbachTrackCasc    = bachTrackCasc->GetLabel();
	Int_t lblbachTrackCascC   = track->GetLabel();
	Int_t lblbachTrackCascCC  = track2->GetLabel();
	Int_t lblbachTrackCascCCC  = track3->GetLabel();
	
	TParticle *partPosTrackCasc    = fMcEvent->Particle(lblpTrackCasc);
	TParticle *partNegTrackCasc    = fMcEvent->Particle(lblnTrackCasc);
	TParticle *partbachTrackCasc   = fMcEvent->Particle(lblbachTrackCasc);
	TParticle *partbachTrackCascC  = fMcEvent->Particle(lblbachTrackCascC);
	TParticle *partbachTrackCascCC = fMcEvent->Particle(lblbachTrackCascCC);
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
        			Int_t lblGdMotherBach = 0; lblGdMotherBach = mcMotherBach->GetFirstMother(); 		//label of the grandmother of the bachelor -> omegac label
        			Int_t lblMotherBachC = 0;  lblMotherBachC = partbachTrackCascC->GetFirstMother(); 	//label of the mother of the bachelorC -> omegac label
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
    
 /*
  while (motherlbl >-1){
    istep++;
    TParticle* motherPart = fMcEvent->Particle(motherlbl);
    if(motherPart){
      pdgma = motherPart->GetPdgCode();
      if(TMath::Abs(pdgma)==pdg) {
      	isFound=true;
      	Printf("IsTrackFromCharmBaryon(%d=%s, %d)::: ---->>>> istep=%d, motherlbl=%d, pdgma=%d, namema=%s, isfound=%d",label,part->GetName(),pdg,istep,motherlbl,pdgma,motherPart->GetName(),isFound);
        break;
      }
      else isFound=false;
      motherlbl = motherPart->GetFirstMother();
    }else{
      printf("CheckOrigin: Failed casting the mother particle!");
      break;
    }
  }
  Printf("IsTrackFromCharmBaryon(%d=%s, %d)::: ---> final iFound=%d\n",label,part->GetName(),pdg,isFound);*/
  return isFound;
 

}
//_________________________________________
bool AliAnalysisTaskSEOmegacccToOmega3Pi::FillHistoOmegac(AliESDEvent *esdEv, AliESDcascade *casc, AliESDtrack *track, AliESDVertex *esdVc) {
		
		UInt_t lIdxPosCasc 	= (UInt_t) TMath::Abs( casc->GetPindex() );
        UInt_t lIdxNegCasc 	= (UInt_t) TMath::Abs( casc->GetNindex() );
        UInt_t lBachIdx     = (UInt_t) TMath::Abs( casc->GetBindex() );
        AliESDtrack *pTrackCasc		= esdEv->GetTrack( lIdxPosCasc );
        AliESDtrack *nTrackCasc		= esdEv->GetTrack( lIdxNegCasc );
        AliESDtrack *bachTrackCasc  = esdEv->GetTrack( lBachIdx );
 	    Int_t bachCascCTrackLabOrigin = CheckOriginTrack(track,4332);
 	    Bool_t issignal=CheckIsSignalOmegac(pTrackCasc, nTrackCasc, bachTrackCasc, track);
 	    //omega c
        //---> Omega
        AliExternalTrackParam *cascTrack = GetTrackParamForCascade(esdEv, casc);
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
	 	Double_t pxpypzomega[3] = {0.,0.,0.}; pxpypzomega[0]=pxomega; pxpypzomega[1]=pyomega; pxpypzomega[2]=pzomega;
	 	Double_t poscasc[3] = { -1000.0, -1000.0, -1000.0 };
	 	casc->GetXYZcascade(poscasc[0],poscasc[1],poscasc[2]);
	 	Double_t radiusOmega=TMath::Sqrt(poscasc[0]*poscasc[0]+poscasc[1]*poscasc[1]+poscasc[2]*poscasc[2]);
	 	Double_t V0quality = 0.;
        casc->ChangeMassHypothesis(V0quality , 3334);
	 	Double_t invmassOmega=casc->GetEffMassXi();
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
	 	//Double_t cosPAXYomegac = CosPointingAngleXY(esdVcc, esdVc, pxpypzomegac);
	 	Double_t impparT1 = b[0];//d0zVertT[0];
	 	Double_t invmass2omegac = (eomega+epi1)*(eomega+epi1)-(pxomegac*pxomegac+pyomegac*pyomegac+pzomegac*pzomegac);
	 	Double_t invmassomegac  = TMath::Sqrt(invmass2omegac);
	 	AliExternalTrackParam *omegacTrack = GetTrackParamForOmegac(esdEv, esdVc, casc, track);
	 	Double_t pxpypz[3] = {0.,0.,0.}; pxpypz[0]=pxomegac; pxpypz[1]=pyomegac; pxpypz[2]=pzomegac;
	 	Double_t costThetaStar = CosThetaStar(1,4332,3334,211, pxpypz, pxpypzomega, pxpypzpi);
	 	Double_t d0zVertC[2],covd0zVertC[3];
	 	omegacTrack->PropagateToDCA(fV1,0,100.,d0zVertC,covd0zVertC);
	 	Double_t impparC  = d0zVertC[0];
	 	
	 	
	 	fOmegacVariables[0] = invmassomegac;
 	    fOmegacVariables[1] = ptomegac;
 	    fOmegacVariables[2] = decLXYomegac;
 	    fOmegacVariables[3] = impparC;
 	    fOmegacVariables[4] = impparT1;
 	    fOmegacVariables[5] = TMath::Sqrt(pxpi1*pxpi1 + pypi1*pypi1);
 	    fOmegacVariables[6] = costThetaStar;
 	    //apply cuts
 	    bool issel = IsSelectedOmegac(fOmegacVariables);
	 	
	 	
	 	//fill histograms
	 	if(issel){
	 	 if(issignal){
	 	//if(negV0TrackLabOrigin==posV0TrackLabOrigin && posV0TrackLabOrigin==bachCascTrackLabOrigin && bachCascTrackLabOrigin==bachCascCTrackLabOrigin) {//true signal
	 		//Printf("FillHisto::::OMEGAC  ID of the tracks: lIdxNegCasc=%10d lIdxNPosCasc=%10d lBachIdx=%10d",lIdxNegCasc,lIdxPosCasc,lBachIdx);
        	//Printf("FillHisto::::OMEGAC  label first mother -->  negV0Track=%5d  posV0Track=%5d  bachCascTrack=%5d  bachCascCTrack=%5d  ",negV0TrackLabOrigin,posV0TrackLabOrigin,bachCascTrackLabOrigin,bachCascCTrackLabOrigin);
        	//Printf("FillHisto::::OMEGAC  Decay chain");
        	//PrintDecayChainTrack(pTrackCasc);
        	//PrintDecayChainTrack(nTrackCasc);
        	//PrintDecayChainTrack(bachTrackCasc);
        	//PrintDecayChainTrack(track);
	 		fOmegacInvMassS->Fill(invmassomegac);
	 		fOmegacPtS->Fill(ptomegac);
			fOmegacDecayLenghtXYS->Fill(decLXYomegac);  
			//fOmegacCosPointAngleXYS->Fill(cosPAXYomegac); 
			fOmegacPiond0S->Fill(b[0]); 
			fOmegacd0S->Fill(impparC); 
			fOmegacPionCosThetaStarS->Fill(costThetaStar); 
			
			fOmegacVtxXReco->Fill(esdVc->GetX());
			fOmegacVtxYReco->Fill(esdVc->GetY());
			fOmegacVtxZReco->Fill(esdVc->GetZ());
			if(bachCascCTrackLabOrigin>-1){
				TParticle *part = (TParticle*)fMcEvent->Particle(bachCascCTrackLabOrigin);
				fOmegacRecoVsPtGen->Fill(part->Pt());
				fhPtGenEtaGen_OmegacReco->Fill(part->Pt(),part->Eta());
				TParticle *dau_0 = (TParticle*)fMcEvent->Particle(part->GetDaughter(0));
				TParticle *dau_1 = (TParticle*)fMcEvent->Particle(part->GetDaughter(1));
				fhEtaDauVsEtaMoth_Rec[4]->Fill(part->Eta(),dau_0->Eta());//omegac vs omega
        		fhEtaDauVsEtaMoth_Rec[5]->Fill(part->Eta(),dau_1->Eta());//omegac vs pion
				
			}

	 	 }
	 	 else{ //background
	 		fOmegacInvMassB->Fill(invmassomegac);
	 		fOmegacPtB->Fill(ptomegac);
			fOmegacDecayLenghtXYB->Fill(decLXYomegac);  
			//fOmegacCosPointAngleXYB->Fill(cosPAXYomegac); 
			fOmegacPiond0B->Fill(impparT1); 
			fOmegacd0B->Fill(impparC);  
			fOmegacPionCosThetaStarB->Fill(costThetaStar);
			
	 	 }
	 	}
	 	
	 	return issel;
	 	
}
//_________________________________________
bool AliAnalysisTaskSEOmegacccToOmega3Pi::FillHistoOmegacc(AliESDEvent *esdEv, AliESDcascade *casc, AliESDtrack *track, AliESDtrack *track2, AliESDVertex *esdVc, AliESDVertex *esdVcc) {
		UInt_t lIdxPosCasc 	= (UInt_t) TMath::Abs( casc->GetPindex() );
        UInt_t lIdxNegCasc 	= (UInt_t) TMath::Abs( casc->GetNindex() );
        UInt_t lBachIdx     = (UInt_t) TMath::Abs( casc->GetBindex() );
        AliESDtrack *pTrackCasc		= esdEv->GetTrack( lIdxPosCasc );
        AliESDtrack *nTrackCasc		= esdEv->GetTrack( lIdxNegCasc );
        AliESDtrack *bachTrackCasc  = esdEv->GetTrack( lBachIdx );
        Int_t bachCascCCTrackLabOrigin  = CheckOriginTrack(track2,4432);
 	    Bool_t issignalOmegac=CheckIsSignalOmegac(pTrackCasc, nTrackCasc, bachTrackCasc, track);
 	    Bool_t issignal=CheckIsSignalOmegacc(pTrackCasc, nTrackCasc, bachTrackCasc, track, track2);
 	    
 	     //omega c
        //---> Omega
        AliExternalTrackParam *cascTrack = GetTrackParamForCascade(esdEv, casc);
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
	 	Double_t V0quality = 0.;
        casc->ChangeMassHypothesis(V0quality , 3334);
	 	Double_t invmassOmega=casc->GetEffMassXi();
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
	 	Double_t cosPAXYomegac = CosPointingAngleXY(esdVcc, esdVc, pxpypzomegac);
	 	Double_t impparT1 = d0zVertT[0];
	 	Double_t invmass2omegac = (eomega+epi1)*(eomega+epi1)-(pxomegac*pxomegac+pyomegac*pyomegac+pzomegac*pzomegac);
	 	Double_t invmassomegac  = TMath::Sqrt(invmass2omegac);
	 	AliExternalTrackParam *omegacTrack = GetTrackParamForOmegac(esdEv, esdVc, casc, track);
	 	Double_t d0zVertC[2],covd0zVertC[3];
	 	omegacTrack->PropagateToDCA(esdVcc,0,100.,d0zVertC,covd0zVertC);
	 	//Double_t impparC  = d0zVertC[0];
	 	if(issignalOmegac){
			//fOmegacCosPointAngleXYS->Fill(cosPAXYomegac); 
			//fOmegacVariables[7] = cosPAXYomegac;
			
	 	}
	 	else{ //background  
			//fOmegacCosPointAngleXYB->Fill(cosPAXYomegac); 
		}
	 	
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
	 	//Double_t cosPAXYomegacc = CosPointingAngleXY(esdVccc, esdVcc, pxpypzomegacc);
	 	Double_t impparT2 = b[0];//d0zVertT2[0];
	 	Double_t invmass2omegacc = (eomegac+epi2)*(eomegac+epi2)-(pxomegacc*pxomegacc+pyomegacc*pyomegacc+pzomegacc*pzomegacc);
	 	Double_t invmassomegacc  = TMath::Sqrt(invmass2omegacc);
	 	AliExternalTrackParam *omegaccTrack = GetTrackParamForOmegacc(esdEv, esdVcc, esdVc, casc, track, track2);
	 	Double_t costThetaStar = CosThetaStar(1,4432,4332,211, pxpypzomegacc, pxpypzomegacprop, pxpypzpi2);
	 	Double_t d0zVertCC[2],covd0zVertCC[3];
	 	omegaccTrack->PropagateToDCA(fV1,fBzkG,100.,d0zVertCC,covd0zVertCC);
	 	Double_t impparCC  = d0zVertCC[0];
	 	
	 	
	 	fOmegaccVariables[0] = invmassomegacc;
 	    fOmegaccVariables[1] = ptomegacc;
 	    fOmegaccVariables[2] = decLXYomegacc;
 	    fOmegaccVariables[3] = impparCC;
 	    fOmegaccVariables[4] = impparT2;
 	    fOmegaccVariables[5] = TMath::Sqrt(pxpi2*pxpi2 + pypi2*pypi2);
 	    fOmegaccVariables[6] = costThetaStar;
 	     //apply cuts
 	    bool issel = IsSelectedOmegacc(fOmegaccVariables);
	 	
	 	
	 	//fill histograms
	 	if(issel){
	 	 if(issignal){
	 	//if(negV0TrackLabOrigin==posV0TrackLabOrigin && posV0TrackLabOrigin==bachCascTrackLabOrigin && bachCascTrackLabOrigin==bachCascCTrackLabOrigin && bachCascCTrackLabOrigin==bachCascCCTrackLabOrigin) {//true signal
	 		//Printf("FillHisto::::OMEGACC  ID of the tracks: lIdxNegCasc=%10d lIdxNPosCasc=%10d lBachIdx=%10d",lIdxNegCasc,lIdxPosCasc,lBachIdx);
        	//Printf("FillHisto::::OMEGACC  label first mother -->  negV0Track=%5d  posV0Track=%5d  bachCascTrack=%5d  bachCascCTrack=%5d  ",negV0TrackLabOrigin,posV0TrackLabOrigin,bachCascTrackLabOrigin,bachCascCTrackLabOrigin);
        	//Printf("FillHisto::::OMEGACC  Decay chain");
        	//PrintDecayChainTrack(pTrackCasc);
        	//PrintDecayChainTrack(nTrackCasc);
        	//PrintDecayChainTrack(bachTrackCasc);
        	//PrintDecayChainTrack(track);
        	//PrintDecayChainTrack(track2);
	 		fOmegaccInvMassS->Fill(invmassomegacc);
	 		fOmegaccPtS->Fill(ptomegacc);
			fOmegaccDecayLenghtXYS->Fill(decLXYomegacc);  
			//fOmegaccCosPointAngleXYS->Fill(cosPAXYomegacc); 
			fOmegaccPiond0S->Fill(impparT2); 
			fOmegaccd0S->Fill(impparCC); 
			fOmegaccPionCosThetaStarS->Fill(costThetaStar); 
			fOmegaccVtxXReco->Fill(esdVcc->GetX());
			fOmegaccVtxYReco->Fill(esdVcc->GetY());
			fOmegaccVtxZReco->Fill(esdVcc->GetZ());
			if(bachCascCCTrackLabOrigin>-1){
				TParticle *part = (TParticle*)fMcEvent->Particle(bachCascCCTrackLabOrigin);
				fOmegaccRecoVsPtGen->Fill(part->Pt());
				fhPtGenEtaGen_OmegaccReco->Fill(part->Pt(),part->Eta());
				TParticle *dau_0 = (TParticle*)fMcEvent->Particle(part->GetDaughter(0));
				TParticle *dau_1 = (TParticle*)fMcEvent->Particle(part->GetDaughter(1));
				fhEtaDauVsEtaMoth_Rec[2]->Fill(part->Eta(),dau_0->Eta());//omegacc vs omegac
        		fhEtaDauVsEtaMoth_Rec[3]->Fill(part->Eta(),dau_1->Eta());//omegacc vs pion
			}
	 	 }
	 	 else{ //background
	 		fOmegaccInvMassB->Fill(invmassomegacc);
	 		fOmegaccPtB->Fill(ptomegacc);
			fOmegaccDecayLenghtXYB->Fill(decLXYomegacc);  
			//fOmegaccCosPointAngleXYB->Fill(cosPAXYomegacc); 
			fOmegaccPiond0B->Fill(impparT2); 
			fOmegaccd0B->Fill(impparCC);
			fOmegaccPionCosThetaStarB->Fill(costThetaStar); 
	 	 }
	 	}
	 	
return issel;
}
//_________________________________________
bool AliAnalysisTaskSEOmegacccToOmega3Pi::FillHistoOmegaccc(AliESDEvent *esdEv, AliESDcascade *casc, AliESDtrack *track, AliESDtrack *track2, AliESDtrack *track3, AliESDVertex *esdVc, AliESDVertex *esdVcc, AliESDVertex *esdVccc) {
		
		UInt_t lIdxPosCasc 	= (UInt_t) TMath::Abs( casc->GetPindex() );
        UInt_t lIdxNegCasc 	= (UInt_t) TMath::Abs( casc->GetNindex() );
        UInt_t lBachIdx     = (UInt_t) TMath::Abs( casc->GetBindex() );
        AliESDtrack *pTrackCasc		= esdEv->GetTrack( lIdxPosCasc );
        AliESDtrack *nTrackCasc		= esdEv->GetTrack( lIdxNegCasc );
        AliESDtrack *bachTrackCasc  = esdEv->GetTrack( lBachIdx );
        
 	    
        Int_t bachCascCCCTrackLabOrigin = CheckOriginTrack(track3,4444);
 	    Bool_t issignalOmegacc=CheckIsSignalOmegacc(pTrackCasc, nTrackCasc, bachTrackCasc, track, track2);
 	    Bool_t issignal=CheckIsSignalOmegaccc(pTrackCasc, nTrackCasc, bachTrackCasc, track, track2, track3);
 	    
 	    //omega c
        //---> Omega
        AliExternalTrackParam *cascTrack = GetTrackParamForCascade(esdEv, casc);
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
	 	Double_t V0quality = 0.;
        casc->ChangeMassHypothesis(V0quality , 3334);
	 	Double_t invmassOmega=casc->GetEffMassXi();
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
	 	//Double_t cosPAXYomegac = CosPointingAngleXY(esdVcc, esdVc, pxpypzomegac);
	 	Double_t impparT1 = d0zVertT[0];
	 	Double_t invmass2omegac = (eomega+epi1)*(eomega+epi1)-(pxomegac*pxomegac+pyomegac*pyomegac+pzomegac*pzomegac);
	 	Double_t invmassomegac  = TMath::Sqrt(invmass2omegac);
	 	AliExternalTrackParam *omegacTrack = GetTrackParamForOmegac(esdEv, esdVc, casc, track);
	 	Double_t d0zVertC[2],covd0zVertC[3];
	 	omegacTrack->PropagateToDCA(esdVcc,0,100.,d0zVertC,covd0zVertC);
	 	//Double_t impparC  = d0zVertC[0];
	 	
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
	 	//---> Omegacc
	 	Double_t pxomegacc = pxomegacprop+pxpi2;
	 	Double_t pyomegacc = pyomegacprop+pypi2;
	 	Double_t pzomegacc = pzomegacprop+pzpi2;
	 	Double_t pxpypzomegacc[3]; pxpypzomegacc[0]=pxomegacc; pxpypzomegacc[1]=pyomegacc; pxpypzomegacc[2]=pzomegacc;
	 	Double_t ptomegacc = TMath::Sqrt(pxomegacc*pxomegacc+pyomegacc*pyomegacc);
	 	//Double_t decLXYomegacc  = DecayLengthXY(esdVccc, esdVcc);
	 	Double_t cosPAXYomegacc = CosPointingAngleXY(esdVccc, esdVcc, pxpypzomegacc);
	 	Double_t impparT2 = d0zVertT2[0];
	 	Double_t invmass2omegacc = (eomegac+epi2)*(eomegac+epi2)-(pxomegacc*pxomegacc+pyomegacc*pyomegacc+pzomegacc*pzomegacc);
	 	Double_t invmassomegacc  = TMath::Sqrt(invmass2omegacc);
	 	AliExternalTrackParam *omegaccTrack = GetTrackParamForOmegacc(esdEv, esdVcc, esdVc, casc, track, track2);
	 	Double_t d0zVertCC[2],covd0zVertCC[3];
	 	omegaccTrack->PropagateToDCA(esdVccc,fBzkG,100.,d0zVertCC,covd0zVertCC);
	 	//Double_t impparCC  = d0zVertCC[0];
	 	//fill histograms
	 	if(issignalOmegacc){
			//fOmegaccCosPointAngleXYS->Fill(cosPAXYomegacc); 
			//fOmegaccVariables[7] = cosPAXYomegacc;
	 	}
	 	else{ //background
	 		//fOmegaccCosPointAngleXYB->Fill(cosPAXYomegacc); 
	 	}
	 	
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
	 	Double_t b[2];
        Double_t bCov[3];
		AliExternalTrackParam etpcp;
	 	etpcp.CopyFromVTrack(track3);
	 	etpcp.PropagateToDCA(fV1,fBzkG,100.,b,bCov);
	 	//---> Omegacc
	 	Double_t pxomegaccc = pxomegaccprop+pxpi3;
	 	Double_t pyomegaccc = pyomegaccprop+pypi3;
	 	Double_t pzomegaccc = pzomegaccprop+pzpi3;
	 	Double_t pxpypzomegaccc[3]; pxpypzomegaccc[0]=pxomegaccc; pxpypzomegaccc[1]=pyomegaccc; pxpypzomegaccc[2]=pzomegaccc;
	 	Double_t ptomegaccc = TMath::Sqrt(pxomegaccc*pxomegaccc+pyomegaccc*pyomegaccc);
	 	Double_t decLXYomegaccc  = DecayLengthXY(fV1, esdVccc);
	 	Double_t cosPAXYomegaccc = CosPointingAngleXY(fV1, esdVccc, pxpypzomegaccc);
	 	Double_t impparT3 = b[0];//d0zVertT3[0];
	 	Double_t invmass2omegaccc = (eomegacc+epi3)*(eomegacc+epi3)-(pxomegaccc*pxomegaccc+pyomegaccc*pyomegaccc+pzomegaccc*pzomegaccc);
	 	Double_t invmassomegaccc  = TMath::Sqrt(invmass2omegaccc);
	 	AliExternalTrackParam *omegacccTrack = GetTrackParamForOmegaccc(esdEv, esdVccc, esdVcc, esdVcc, casc, track, track2, track3);
	 	Double_t costThetaStar = CosThetaStar(1,4444,4432,211, pxpypzomegaccc, pxpypzomegaccprop, pxpypzpi3);
	 	Double_t d0zVertCCC[2],covd0zVertCCC[3];
	 	omegacccTrack->PropagateToDCA(fV1,fBzkG,100.,d0zVertCCC,covd0zVertCCC);
	 	Double_t impparCCC  = d0zVertCCC[0];
	 	
	 	
	 	fOmegacccVariables[0] = invmassomegaccc;
 	    fOmegacccVariables[1] = ptomegaccc;
 	    fOmegacccVariables[2] = decLXYomegaccc;
 	    fOmegacccVariables[3] = impparCCC;
 	    fOmegacccVariables[4] = impparT3;
 	    fOmegacccVariables[5] = TMath::Sqrt(pxpi3*pxpi3 + pypi3*pypi3);
 	    fOmegacccVariables[6] = costThetaStar;
 	    fOmegacccVariables[7] = cosPAXYomegaccc;
 	    //apply cuts
	 	bool issel = IsSelectedOmegaccc(fOmegacccVariables);
 	    //fill histograms
 	    if(issel){
 	     if(issignal){
	 	//if(negV0TrackLabOrigin==posV0TrackLabOrigin && posV0TrackLabOrigin==bachCascTrackLabOrigin && bachCascTrackLabOrigin==bachCascCTrackLabOrigin && bachCascCTrackLabOrigin==bachCascCCTrackLabOrigin && bachCascCCTrackLabOrigin==bachCascCCCTrackLabOrigin) {//true signal
	 		//Printf("FillHisto::::OMEGACCC  ID of the tracks: lIdxNegCasc=%10d lIdxNPosCasc=%10d lBachIdx=%10d",lIdxNegCasc,lIdxPosCasc,lBachIdx);
        	//Printf("FillHisto::::OMEGACCC  label first mother -->  negV0Track=%5d  posV0Track=%5d  bachCascTrack=%5d  bachCascCTrack=%5d  ",negV0TrackLabOrigin,posV0TrackLabOrigin,bachCascTrackLabOrigin,bachCascCTrackLabOrigin);
        	//Printf("FillHisto::::OMEGACCC  Decay chain");
        	//PrintDecayChainTrack(pTrackCasc);
        	//PrintDecayChainTrack(nTrackCasc);
        	//PrintDecayChainTrack(bachTrackCasc);
        	//PrintDecayChainTrack(track);
        	//PrintDecayChainTrack(track2);
        	//PrintDecayChainTrack(track3);
	 		fOmegacccInvMassS->Fill(invmassomegaccc);
	 		fOmegacccPtS->Fill(ptomegaccc);
			fOmegacccDecayLenghtXYS->Fill(decLXYomegaccc);  
			fOmegacccCosPointAngleXYS->Fill(cosPAXYomegaccc); 
			fOmegacccPiond0S->Fill(impparT3); 
			fOmegacccd0S->Fill(impparCCC);
			fOmegacccPionCosThetaStarS->Fill(costThetaStar);  
			fOmegacccVtxXReco->Fill(esdVccc->GetX());
			fOmegacccVtxYReco->Fill(esdVccc->GetY());
			fOmegacccVtxZReco->Fill(esdVccc->GetZ());
			if(bachCascCCCTrackLabOrigin>-1){
				TParticle *part = (TParticle*)fMcEvent->Particle(bachCascCCCTrackLabOrigin);
				fOmegacccRecoVsPtGen->Fill(part->Pt());
				fhPtGenEtaGen_OmegacccReco->Fill(part->Pt(),part->Eta());
				TParticle *dau_0 = (TParticle*)fMcEvent->Particle(part->GetDaughter(0));
				TParticle *dau_1 = (TParticle*)fMcEvent->Particle(part->GetDaughter(1));
				fhEtaDauVsEtaMoth_Rec[0]->Fill(part->Eta(),dau_0->Eta());//omegaccc vs omegacc
        		fhEtaDauVsEtaMoth_Rec[1]->Fill(part->Eta(),dau_1->Eta());//omegaccc vs pion
			}
			
	 	 }
	 	 else{ //background
	 		fOmegacccInvMassB->Fill(invmassomegaccc);
	 		fOmegacccPtB->Fill(ptomegaccc);
			fOmegacccDecayLenghtXYB->Fill(decLXYomegaccc);  
			fOmegacccCosPointAngleXYB->Fill(cosPAXYomegaccc); 
			fOmegacccPiond0B->Fill(impparT3); 
			fOmegacccd0B->Fill(impparCCC);
			fOmegacccPionCosThetaStarB->Fill(costThetaStar);
	 	 }
	 	}
	 
	 return issel;	

}
//_________________________________________
bool AliAnalysisTaskSEOmegacccToOmega3Pi::IsSelectedOmegaccc(Double_t vars[8]){

	bool issel = true;
	
	if(TMath::Abs(vars[0]-TDatabasePDG::Instance()->GetParticle(4444)->Mass())>fOmegacccCuts[0]) return false;
	if(vars[1]<fOmegacccCuts[1]) return false;
	if(vars[2]<fOmegacccCuts[2]) return false;
	if(vars[3]<fOmegacccCuts[3]) return false;
	if(vars[4]<fOmegacccCuts[4]) return false;
	if(vars[5]<fOmegacccCuts[5]) return false;
	if(vars[6]<fOmegacccCuts[6]) return false;
	if(vars[7]<fOmegacccCuts[7]) return false;

	return issel;

}
//_________________________________________
bool AliAnalysisTaskSEOmegacccToOmega3Pi::IsSelectedOmegacc(Double_t vars[8]){

	bool issel = true;
	
	if(TMath::Abs(vars[0]-TDatabasePDG::Instance()->GetParticle(4432)->Mass())>fOmegaccCuts[0]) return false;
	if(vars[1]<fOmegaccCuts[1]) return false;
	if(vars[2]<fOmegaccCuts[2]) return false;
	if(vars[3]<fOmegaccCuts[3]) return false;
	if(vars[4]<fOmegaccCuts[4]) return false;
	if(vars[5]<fOmegaccCuts[5]) return false;
	if(vars[6]<fOmegaccCuts[6]) return false;
	if(vars[7]<fOmegaccCuts[7]) return false;

	return issel;

}
//_________________________________________
bool AliAnalysisTaskSEOmegacccToOmega3Pi::IsSelectedOmegac(Double_t vars[8]){

	bool issel = true;
	
	//Printf("TMath::Abs(vars[0]=%f-TDatabasePDG::Instance()->GetParticle(4332)->Mass()) = %f",vars[0],TMath::Abs(vars[0]-TDatabasePDG::Instance()->GetParticle(4332)->Mass()));
	//for(Int_t i=0; i<8; i++){
	//	Printf("vars[i] = %f < fOmegacCuts[i] = %f",vars[i],fOmegacCuts[i]);
	//}
	
	if(TMath::Abs(vars[0]-TDatabasePDG::Instance()->GetParticle(4332)->Mass())>fOmegacCuts[0]) return false;
	if(vars[1]<fOmegacCuts[1]) return false;
	if(vars[2]<fOmegacCuts[2]) return false;
	if(vars[3]<fOmegacCuts[3]) return false;
	if(vars[4]<fOmegacCuts[4]) return false;
	if(vars[5]<fOmegacCuts[5]) return false;
	if(vars[6]<fOmegacCuts[6]) return false;
	if(vars[7]<fOmegacCuts[7]) return false;
	
	return issel;

}
//_________________________________________
AliESDVertex* AliAnalysisTaskSEOmegacccToOmega3Pi::CallReconstructSecondaryVertexOmegac(AliESDEvent *esdEv, AliESDcascade *casc, AliESDtrack *track, Double_t &dispersion) {
//Printf("\n*************************prepare for OMEGA c decay vertex reco");

	AliESDVertex *secVertex = 0x0;

	TObjArray *trkArray = new TObjArray(2);
	trkArray->AddAt(track,0);

	AliExternalTrackParam *cascTrack = GetTrackParamForCascade(esdEv, casc);
	trkArray->AddAt(cascTrack,1);
	
//	Printf("---->call reco OMEGA c decay vertex");
	secVertex = ReconstructSecondaryVertex(trkArray, dispersion);
//	Printf("*************************end prepare for OMEGA c decay vertex reco");
	//if(secVertex)FillOmegac(casc, cascTrack, track, secVertex, esdEv);


	trkArray->Clear();
	delete trkArray;
	return secVertex;


}
//_________________________________________
AliESDVertex* AliAnalysisTaskSEOmegacccToOmega3Pi::CallReconstructSecondaryVertexOmegacc(AliESDEvent *esdEv, AliESDVertex *sVtxOmegac, AliESDcascade *casc, AliESDtrack *esdtr, AliESDtrack *esdtr2, Double_t &dispersion){
    //Printf("\n*************************prepare for OMEGA cc decay vertex reco");
	AliESDVertex *secVertex = 0x0;

	TObjArray *trkArray = new TObjArray(2);
	trkArray->AddAt(esdtr2,0);
	
	AliExternalTrackParam *trackOmegac = GetTrackParamForOmegac(esdEv, sVtxOmegac, casc, esdtr);
	trkArray->AddAt(trackOmegac,1);

	//Printf("---->call reco OMEGA cc decay vertex");
	secVertex = ReconstructSecondaryVertex(trkArray, dispersion);
	//Printf("*************************end prepare for OMEGA cc decay vertex reco");
	//if(secVertex)FillOmegacc(casc, cascTrack, track, secVertex, esdEv);

	trkArray->Clear();
	delete trkArray;
	return secVertex;


}
//_________________________________________
AliESDVertex* AliAnalysisTaskSEOmegacccToOmega3Pi::CallReconstructSecondaryVertexOmegaccc(AliESDEvent *esdEv, AliESDVertex *sVtxOmegacc, AliESDVertex *sVtxOmegac, AliESDcascade *casc, AliESDtrack *esdtr, AliESDtrack *esdtr2, AliESDtrack *esdtr3, Double_t &dispersion){
    //Printf("\n*************************prepare for OMEGA ccc decay vertex reco");
	AliESDVertex *secVertex = 0x0;

	TObjArray *trkArray = new TObjArray(2);
	trkArray->AddAt(esdtr3,0);
		
	AliExternalTrackParam *trackOmegacc = GetTrackParamForOmegacc(esdEv, sVtxOmegacc, sVtxOmegac, casc, esdtr, esdtr2);
	trkArray->AddAt(trackOmegacc,1);

	//Printf("---->call reco OMEGA ccc decay vertex");
	secVertex = ReconstructSecondaryVertex(trkArray, dispersion);
	//Printf("*************************end prepare for OMEGA ccc decay vertex reco");
	//if(secVertex)FillOmegacc(casc, cascTrack, track, secVertex, esdEv);

	trkArray->Clear();
	delete trkArray;
	return secVertex;


}
//____________________________________
AliESDVertex* AliAnalysisTaskSEOmegacccToOmega3Pi::ReconstructSecondaryVertex(TObjArray *trkArray, Double_t &dispersion) {


  /// Secondary vertex reconstruction with AliVertexerTracks
  //AliDebug(1,"ReconstructSecondaryVertex 0");
    AliVertexerTracks *fVertexerTracks = new AliVertexerTracks(fBzkG);
    fVertexerTracks->SetVtxStart(fV1);
  //AliDebug(1,"ReconstructSecondaryVertex 1");
    AliESDVertex *vertexESD = (AliESDVertex*)fVertexerTracks->VertexForSelectedESDTracks(trkArray);
  //AliDebug(1,"ReconstructSecondaryVertex 2");

    if(!vertexESD) {AliDebug(1,"no sec vertex reco"); return 0;}
    //vertexESD->Print();

    //Printf("ncontr %d  ntracks %d", vertexESD->GetNContributors(),trkArray->GetEntriesFast());
    if(vertexESD->GetNContributors()!=trkArray->GetEntriesFast()) {
      //AliDebug(2,"vertexing failed");
      delete vertexESD; vertexESD=NULL;
      return 0;
    }

    Double_t vertRadius2=vertexESD->GetX()*vertexESD->GetX()+vertexESD->GetY()*vertexESD->GetY();
    //Printf("vertRadius2 %f", vertRadius2);
    if(vertRadius2>8.){
      // vertex outside beam pipe, reject candidate to avoid propagation through material
      delete vertexESD; vertexESD=NULL;
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
AliExternalTrackParam* AliAnalysisTaskSEOmegacccToOmega3Pi::GetTrackParamForOmegaccc(AliESDEvent *esdEv, AliESDVertex *sVtxOmegaccc, AliESDVertex *sVtxOmegacc, AliESDVertex *sVtxOmegac, AliESDcascade *casc, AliESDtrack *esdtr, AliESDtrack *esdtr2, AliESDtrack *esdtr3){

	//Omegacc trackParam	
	AliExternalTrackParam *omegaccTrack = GetTrackParamForOmegacc(esdEv, sVtxOmegacc, sVtxOmegac, casc, esdtr, esdtr2);
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
	if(omegacccTrack) return omegacccTrack;
	else return 0x0;

}
//____________________________________
AliExternalTrackParam* AliAnalysisTaskSEOmegacccToOmega3Pi::GetTrackParamForOmegacc(AliESDEvent *esdEv, AliESDVertex *sVtxOmegacc, AliESDVertex *sVtxOmegac, AliESDcascade *casc, AliESDtrack *esdtr, AliESDtrack *esdtr2){

	//Omegac trackParam	
	AliExternalTrackParam *omegacTrack = GetTrackParamForOmegac(esdEv, sVtxOmegac, casc, esdtr);
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
	if(omegaccTrack) return omegaccTrack;
	else return 0x0;

}
//____________________________________
AliExternalTrackParam* AliAnalysisTaskSEOmegacccToOmega3Pi::GetTrackParamForOmegac(AliESDEvent *esdEv, AliESDVertex *sVtxOmegac, AliESDcascade *casc, AliESDtrack *esdtr){

	//propagate cascade to the Omegac decay vertex	
	AliExternalTrackParam *cascTrack = GetTrackParamForCascade(esdEv, casc);
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
	if(omegacTrack) return omegacTrack;
	else return 0x0;

}
//____________________________________
AliExternalTrackParam* AliAnalysisTaskSEOmegacccToOmega3Pi::GetTrackParamForCascade(AliESDEvent *esdEv, AliESDcascade *casc){



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
	AliESDtrack  *esdCascadePos  = esdEv->GetTrack( idxPosFromV0Dghter);
	Double_t covTrPos[21];
	esdCascadePos->GetCovarianceXYZPxPyPz(covTrPos);
	AliESDtrack  *esdCascadeNeg  = esdEv->GetTrack( idxNegFromV0Dghter);
	Double_t covTrNeg[21];
	esdCascadeNeg->GetCovarianceXYZPxPyPz(covTrNeg);
	//cov V0
	Double_t covV0[21];
	Double_t covV0prop[21];
	for(int i=0; i<21; i++){
		covV0[i]=covTrPos[i]+covTrNeg[i];
		covV0prop[i]=0;
	}
	//get V0 from cascade
	AliESDv0 * currentV0   = 0x0;
	Int_t idxV0FromCascade = -1;
	for(int iv0=0; iv0<esdEv->GetNumberOfV0s(); iv0++){
		currentV0 = esdEv->GetV0(iv0);
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
	AliESDv0 *esdV0FromCascade = esdEv->GetV0(idxV0FromCascade);
	Double_t xyzv0[3], pxpypzv0[3];
	esdV0FromCascade->XvYvZv(xyzv0);
	esdV0FromCascade->PxPyPz(pxpypzv0);
	//Printf("xyz = %f %f %f \t pxpypz = %f %f %f",xyzv0[0],xyzv0[1],xyzv0[2],pxpypzv0[0],pxpypzv0[1],pxpypzv0[2]);
	AliExternalTrackParam *v0track=new AliExternalTrackParam(xyzv0,pxpypzv0,covV0,1);
	//AliNeutralTrackParam *v0track=new AliExternalTrackParam(xyzv0,pxpypzv0,covV0,0);
	Double_t covv0[21];
	v0track->GetCovarianceXYZPxPyPz(covv0);
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
	AliESDtrack  *esdCascadeBach = esdEv->GetTrack( idxBachFromCascade);
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

	if(cascTrack) return cascTrack;
	else return 0x0;

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
void AliAnalysisTaskSEOmegacccToOmega3Pi::FillGenDistrib(){

    
    Int_t thisPdgCode = 0;
    Float_t thisEta = 0.;
    Float_t thisPt = 0.; 
    Float_t thisy = 0.;
    Bool_t isPhysPrimary = kFALSE; 
    Int_t npion_fromL=0, np_fromL=0, nL=0, nO=0, nL_fromO=0, nK_fromO=0, nD=0, nB=0;
    Int_t nb_py = 0, nc_py=0;
    Int_t nb_hij = 0, nc_hij=0;
    
    int npart = fMcEvent->GetNumberOfTracks();
    // loop on particles
    for(int i=0; i<npart; i++){
    
     TParticle *part = (TParticle*)fMcEvent->Particle(i);
     if(!part) {continue;}
     
     thisPdgCode = part->GetPdgCode();
     thisEta     = part->Eta();
     thisPt      = part->Pt();
     thisy       = part->Y();
     isPhysPrimary = fMcEvent->IsPhysicalPrimary(i);
     //
     
     if(TMath::Abs(thisPdgCode)==4) {
        Int_t mlab = part->GetFirstMother();
        if(mlab==-1){
     	TString genname=GetGenerator(i,(AliGenCocktailEventHeader*)fMcEvent->GenEventHeader());
     	//Printf("%d %s %d %s", i, genname.Data(), mlab, part->GetName());
     	if(genname.Contains("Hijing"))nc_hij++;
     	if(genname.Contains("PYTHIA"))nc_py++;
     	}
     }	
     if(TMath::Abs(thisPdgCode)==5) {
        Int_t mlab = part->GetFirstMother();
        if(mlab==-1){
        TString genname=GetGenerator(i,(AliGenCocktailEventHeader*)fMcEvent->GenEventHeader());
        //Printf("%d %s %d %s", i, genname.Data(), mlab, part->GetName());
     	if(genname.Contains("Hijing"))nb_hij++;
     	if(genname.Contains("PYTHIA"))nb_py++;
     	}
     }
     
     
     //Omegaccc: check all daughters in acceptance
     if(TMath::Abs(thisPdgCode)==4444){
     //omegaccc level
      Int_t dau[2] = {-1, -1};
      dau[0] = part->GetDaughter(0); //omegacc
      dau[1] = part->GetDaughter(1); //pion
       if(dau[0]>-1 && dau[1]>-1){
        TParticle *daup[2];
        daup[0] = (TParticle*)fMcEvent->Particle(dau[0]); //omegacc
        daup[1] = (TParticle*)fMcEvent->Particle(dau[1]); //pion
        Float_t eta_dau[2] = {-100.,-100.};
        Float_t pt_dau[2] = {-100.,-100.};
        Float_t y_dau[2] = {-100.,-100.};
        for(Int_t i=0; i<2; i++){
        	eta_dau[i] = daup[i]->Eta();
        	pt_dau[i]  = daup[i]->Pt();
        	y_dau[i]   = daup[i]->Y(); 
        	//Printf("i=%d eta dau = %f pt dau = %f y dau = %f dau = %s",i,eta_dau[i],pt_dau[i],y_dau[i],daup[i]->GetName());
        }
        Int_t dau1[2] = {-1, -1};
      	dau1[0] = daup[0]->GetDaughter(0); //omegac
      	dau1[1] = daup[0]->GetDaughter(1); //pion
      	 if(dau1[0]>0 && dau1[1]>0){
         TParticle *daup1[2];
         daup1[0] = (TParticle*)fMcEvent->Particle(dau1[0]); //omegac
         daup1[1] = (TParticle*)fMcEvent->Particle(dau1[1]); //pion
         Float_t eta_dau1[2] = {-100.,-100.};
         Float_t pt_dau1[2] = {-100.,-100.};
         Float_t y_dau1[2] = {-100.,-100.};
          for(Int_t i=0; i<2; i++){
        	  eta_dau1[i] = daup1[i]->Eta();
        	  pt_dau1[i]  = daup1[i]->Pt();
        	  y_dau1[i]   = daup1[i]->Y(); 
          }  
          Int_t dau2[2] = {-1, -1};
      	  dau2[0] = daup1[0]->GetDaughter(0); //omega
      	  dau2[1] = daup1[0]->GetDaughter(1); //pion
      	  if(dau2[0]>0 && dau2[1]>0){
           TParticle *daup2[2];
           daup2[0] = (TParticle*)fMcEvent->Particle(dau2[0]); //omega
           daup2[1] = (TParticle*)fMcEvent->Particle(dau2[1]); //pion
           Float_t eta_dau2[2] = {-100.,-100.};
           Float_t pt_dau2[2] = {-100.,-100.};
           Float_t y_dau2[2] = {-100.,-100.};
           for(Int_t i=0; i<2; i++){
        	  eta_dau2[i] = daup2[i]->Eta();
        	  pt_dau2[i]  = daup2[i]->Pt();
        	  y_dau2[i]   = daup2[i]->Y(); 
           }
           Int_t dau3[2] = {-1, -1};
      	   dau3[0] = daup2[0]->GetDaughter(0); //Lambda
      	   dau3[1] = daup2[0]->GetDaughter(1); //kaon
      	   if(dau3[0]>0 && dau3[1]>0){
            TParticle *daup3[2];
            daup3[0] = (TParticle*)fMcEvent->Particle(dau3[0]); //Lambda
            daup3[1] = (TParticle*)fMcEvent->Particle(dau3[1]); //kaon
            Float_t eta_dau3[2] = {-100.,-100.};
            Float_t pt_dau3[2] = {-100.,-100.};
            Float_t y_dau3[2] = {-100.,-100.};
            for(Int_t i=0; i<2; i++){
            //Lambda and kaon
        	  eta_dau3[i] = daup3[i]->Eta();
        	  pt_dau3[i]  = daup3[i]->Pt();
        	  y_dau3[i]   = daup3[i]->Y(); 
            }
            Int_t dau4[2] = {-1, -1};
      	   	dau4[0] = daup3[0]->GetDaughter(0); //proton
      	   	dau4[1] = daup3[0]->GetDaughter(1); //pion
      	    if(dau4[0]>0 && dau4[1]>0){
             TParticle *daup4[2];
             daup4[0] = (TParticle*)fMcEvent->Particle(dau4[0]); //proton
             daup4[1] = (TParticle*)fMcEvent->Particle(dau4[1]); //pion
             Float_t eta_dau4[2] = {-100.,-100.};
             Float_t pt_dau4[2] = {-100.,-100.};
             Float_t y_dau4[2] = {-100.,-100.};
             for(Int_t i=0; i<2; i++){
             //Lambda and kaon
        	   eta_dau4[i] = daup4[i]->Eta();
        	   pt_dau4[i]  = daup4[i]->Pt();
        	   y_dau4[i]   = daup4[i]->Y(); 
             }
            
             //eta
             fhEtaOmegacccVsEta_gen[0]->Fill(thisEta,eta_dau[1]);
             fhEtaOmegacccVsEta_gen[1]->Fill(thisEta,eta_dau1[1]);
             fhEtaOmegacccVsEta_gen[2]->Fill(thisEta,eta_dau2[1]);
             fhEtaOmegacccVsEta_gen[3]->Fill(thisEta,eta_dau3[1]);
             fhEtaOmegacccVsEta_gen[4]->Fill(thisEta,eta_dau4[1]);
             fhEtaOmegacccVsEta_gen[5]->Fill(thisEta,eta_dau4[0]);
             
             fhEtaOmegaccVsEta_gen[0]->Fill(eta_dau[0],eta_dau1[1]);
             fhEtaOmegaccVsEta_gen[1]->Fill(eta_dau[0],eta_dau2[1]);
             fhEtaOmegaccVsEta_gen[2]->Fill(eta_dau[0],eta_dau3[1]);
             fhEtaOmegaccVsEta_gen[3]->Fill(eta_dau[0],eta_dau4[1]);
             fhEtaOmegaccVsEta_gen[4]->Fill(eta_dau[0],eta_dau4[0]);
             
             fhEtaOmegacVsEta_gen[0]->Fill(eta_dau1[0],eta_dau2[1]);
             fhEtaOmegacVsEta_gen[1]->Fill(eta_dau1[0],eta_dau3[1]);
             fhEtaOmegacVsEta_gen[2]->Fill(eta_dau1[0],eta_dau4[1]);
             fhEtaOmegacVsEta_gen[3]->Fill(eta_dau1[0],eta_dau4[0]);
             //pt
             fhPtOmegacccVsPt_gen[0]->Fill(thisPt,pt_dau[1]);
             fhPtOmegacccVsPt_gen[1]->Fill(thisPt,pt_dau1[1]);
             fhPtOmegacccVsPt_gen[2]->Fill(thisPt,pt_dau2[1]);
             fhPtOmegacccVsPt_gen[3]->Fill(thisPt,pt_dau3[1]);
             fhPtOmegacccVsPt_gen[4]->Fill(thisPt,pt_dau4[1]);
             fhPtOmegacccVsPt_gen[5]->Fill(thisPt,pt_dau4[0]);
             
             fhPtOmegaccVsPt_gen[0]->Fill(pt_dau[0],pt_dau1[1]);
             fhPtOmegaccVsPt_gen[1]->Fill(pt_dau[0],pt_dau2[1]);
             fhPtOmegaccVsPt_gen[2]->Fill(pt_dau[0],pt_dau3[1]);
             fhPtOmegaccVsPt_gen[3]->Fill(pt_dau[0],pt_dau4[1]);
             fhPtOmegaccVsPt_gen[4]->Fill(pt_dau[0],pt_dau4[0]);
             
             //Printf("Filling %s %f %f",fhPtOmegacVsPt_gen[0]->GetName(), pt_dau1[0],pt_dau2[1]); 
             fhPtOmegacVsPt_gen[0]->Fill(pt_dau1[0],pt_dau2[1]);
             fhPtOmegacVsPt_gen[1]->Fill(pt_dau1[0],pt_dau3[1]);
             fhPtOmegacVsPt_gen[2]->Fill(pt_dau1[0],pt_dau4[1]);
             fhPtOmegacVsPt_gen[3]->Fill(pt_dau1[0],pt_dau4[0]);
             //y
             fhYOmegacccVsY_gen[0]->Fill(thisy,y_dau[1]);
             fhYOmegacccVsY_gen[1]->Fill(thisy,y_dau1[1]);
             fhYOmegacccVsY_gen[2]->Fill(thisy,y_dau2[1]);
             fhYOmegacccVsY_gen[3]->Fill(thisy,y_dau3[1]);
             fhYOmegacccVsY_gen[4]->Fill(thisy,y_dau4[1]);
             fhYOmegacccVsY_gen[5]->Fill(thisy,y_dau4[0]);
             
             fhYOmegaccVsY_gen[0]->Fill(y_dau[0],y_dau1[1]);
             fhYOmegaccVsY_gen[1]->Fill(y_dau[0],y_dau2[1]);
             fhYOmegaccVsY_gen[2]->Fill(y_dau[0],y_dau3[1]);
             fhYOmegaccVsY_gen[3]->Fill(y_dau[0],y_dau4[1]);
             fhYOmegaccVsY_gen[4]->Fill(y_dau[0],y_dau4[0]);
             
             fhYOmegacVsY_gen[0]->Fill(y_dau1[0],y_dau2[1]);
             fhYOmegacVsY_gen[1]->Fill(y_dau1[0],y_dau3[1]);
             fhYOmegacVsY_gen[2]->Fill(y_dau1[0],y_dau4[1]);
             fhYOmegacVsY_gen[3]->Fill(y_dau1[0],y_dau4[0]);
            
            // histograms for efficiency
            if(TMath::Abs(eta_dau[1])<fEtaCut && 
            	TMath::Abs(eta_dau1[1])<fEtaCut && 
            	 TMath::Abs(eta_dau2[1])<fEtaCut && 
            	  TMath::Abs(eta_dau3[1])<fEtaCut && 
            	  	TMath::Abs(eta_dau4[0])<fEtaCut && 
            	  	 TMath::Abs(eta_dau4[1])<fEtaCut){
            	fOmegacccGenVsPtGen->Fill(thisPt);
            	fOmegacccVtxXGen->Fill((Float_t)part->Vx());
	   			fOmegacccVtxYGen->Fill((Float_t)part->Vy());
       			fOmegacccVtxZGen->Fill((Float_t)part->Vz());
            }
            if(TMath::Abs(eta_dau1[1])<fEtaCut && 
            	TMath::Abs(eta_dau2[1])<fEtaCut && 
            	 TMath::Abs(eta_dau3[1])<fEtaCut && 
            	  TMath::Abs(eta_dau4[0])<fEtaCut && 
            	  	TMath::Abs(eta_dau4[1])<fEtaCut){
				fOmegaccGenVsPtGen->Fill(pt_dau[0]);
				fOmegaccVtxXGen->Fill((Float_t)daup[0]->Vx());
	   			fOmegaccVtxYGen->Fill((Float_t)daup[0]->Vy());
       			fOmegaccVtxZGen->Fill((Float_t)daup[0]->Vz());
			}
            if(TMath::Abs(eta_dau2[1])<fEtaCut && 
            	TMath::Abs(eta_dau3[1])<fEtaCut && 
            	 TMath::Abs(eta_dau4[0])<fEtaCut && 
            	  TMath::Abs(eta_dau4[1])<fEtaCut){
				fOmegacGenVsPtGen->Fill(pt_dau1[0]);
				fOmegacVtxXGen->Fill((Float_t)daup1[0]->Vx());
	   			fOmegacVtxYGen->Fill((Float_t)daup1[0]->Vy());
       			fOmegacVtxZGen->Fill((Float_t)daup1[0]->Vz());
			}
            if(TMath::Abs(eta_dau3[1])<fEtaCut && 
            	TMath::Abs(eta_dau4[0])<fEtaCut && 
            	 TMath::Abs(eta_dau4[1])<fEtaCut){	
            	fhOmegaGenVsPtGen->Fill(pt_dau2[0]);
            }
            if(TMath::Abs(eta_dau4[0])<fEtaCut && 
            	TMath::Abs(eta_dau4[1])<fEtaCut){
            	fhLambdaGenVsPtGen->Fill(pt_dau3[0]);
            }
            
            //Printf("filling %s->Fill()",fPiGenFromVsPtGen[0]->GetName());
            if(TMath::Abs(eta_dau[1]) <fEtaCut){/*Printf("filling %s->Fill(%f)",fPiGenFromVsPtGen[0]->GetName(),pt_dau[1]);*/ fPiGenFromVsPtGen[0]->Fill(pt_dau[1]);} //pi from omegaccc
            if(TMath::Abs(eta_dau1[1])<fEtaCut)fPiGenFromVsPtGen[1]->Fill(pt_dau1[1]);//pi from omegacc
            if(TMath::Abs(eta_dau2[1])<fEtaCut)fPiGenFromVsPtGen[2]->Fill(pt_dau2[1]);//pi from omegac
            if(TMath::Abs(eta_dau4[1])<fEtaCut)fPiGenFromVsPtGen[3]->Fill(pt_dau4[1]);//pi from Lambda
            if(TMath::Abs(eta_dau4[0])<fEtaCut)fPGenVsPtGen->Fill(pt_dau4[0]);
      		if(TMath::Abs(eta_dau3[1])<fEtaCut)fKGenVsPtGen->Fill(pt_dau3[1]);
            
            //Printf("%f %f %f %f %f %f %f %f %f %f",eta_dau[0],eta_dau[1],eta_dau1[0],eta_dau1[1],eta_dau2[0],eta_dau2[1],eta_dau3[0],eta_dau3[1],eta_dau4[0],eta_dau4[1]);

            //no eta cut	
            fhEtaDauVsEtaMoth_Gen[0]->Fill(thisEta,eta_dau[0]);//omegaccc vs omegacc
        	fhEtaDauVsEtaMoth_Gen[1]->Fill(thisEta,eta_dau[1]);//omegaccc vs pion
        	fhEtaDauVsEtaMoth_Gen[2]->Fill(eta_dau[0],eta_dau1[0]);//omegacc vs omegac
        	fhEtaDauVsEtaMoth_Gen[3]->Fill(eta_dau[0],eta_dau1[1]);//omegacc vs pion
        	fhEtaDauVsEtaMoth_Gen[4]->Fill(eta_dau1[0],eta_dau2[0]);//omegac vs omega
        	fhEtaDauVsEtaMoth_Gen[5]->Fill(eta_dau1[0],eta_dau2[1]);//omegac vs pion
        	fhEtaDauVsEtaMoth_Gen[6]->Fill(eta_dau2[0],eta_dau3[0]);//Omega vs Lambda
        	fhEtaDauVsEtaMoth_Gen[7]->Fill(eta_dau2[0],eta_dau3[1]);//Omega vs kaon
        	fhEtaDauVsEtaMoth_Gen[8]->Fill(eta_dau3[0],eta_dau4[1]);//Lambda vs pion
        	fhEtaDauVsEtaMoth_Gen[9]->Fill(eta_dau3[0],eta_dau4[0]);//Lambda vs proton
            
            //Printf("%f %f %f %f %f %f %f %f %f %f",eta_dau[0],eta_dau[1],eta_dau1[0],eta_dau1[1],eta_dau2[0],eta_dau2[1],eta_dau3[0],eta_dau3[1],eta_dau4[0],eta_dau4[1]);
            
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
//________________________________________________________________________
void AliAnalysisTaskSEOmegacccToOmega3Pi::RecoEvent(AliESDEvent *esd){

   


    int npart = fMcEvent->GetNumberOfTracks();//fStack->GetNprimary();
    const AliVVertex *vtxMC = fMcEvent->GetPrimaryVertex();
    Double_t covmatrix[6]={0.,0.,0.,0.,0.,0.};
    Double_t positiongen[3]={0.,0.,0.};
    //vtxMC->GetSigmaXYZ(sigmagen);
    vtxMC->GetXYZ(positiongen);
    //fHistGenVertexSigmaX->Fill(sigmagen[0]);
    //fHistGenVertexSigmaY->Fill(sigmagen[1]); 
    //fHistGenVertexSigmaZ->Fill(sigmagen[2]); 
    fHistGenVertexX->Fill(positiongen[0]);
    fHistGenVertexY->Fill(positiongen[1]);
    fHistGenVertexZ->Fill(positiongen[2]);
    
 
    
    // loop on particles
    for(int i=0; i<npart; i++){
    
     TParticle *part = (TParticle*)fMcEvent->Particle(i);//fStack->Particle(i);
     if(!part) {/*Printf("no part"); */continue;}
     fNentries->Fill(1);
     Bool_t isPhysPrimary = fMcEvent->IsPhysicalPrimary(i);
     if(!isPhysPrimary) {/*Printf("i=%d  no phys prim",i); */continue;}
     if(part->GetStatusCode()<=0) {/*Printf("status code <0"); */continue;}
     fNentries->Fill(2);
     Int_t motherIndex=part->GetFirstMother();
     if(motherIndex==-1) {/*Printf("i=%d motherIndex==-1",i); */continue;}
     fNentries->Fill(3);
     int charge = TDatabasePDG::Instance()->GetParticle(part->GetPdgCode())->Charge()/3;
     if(charge==0) continue;
     fNentries->Fill(4);
     Float_t thisEta = part->Eta();
     if(TMath::Abs(thisEta) > fEtaCut) continue;
     fNentries->Fill(5);
    
     // fast track reco
     Bool_t res = fITS->ProcessTrack(part);
     if(!res) {fNentries->Fill(7); continue;}
     AliESDtrack* esdTr = (AliESDtrack*)fITS->GetProbeTrackInwardAsESDTrack();
     esdTr->SetStatus(AliESDtrack::kTPCin|AliESDtrack::kTPCout|AliESDtrack::kTPCrefit|AliESDtrack::kITSrefit);
     esdTr->SetLabel(i);
     esd->AddTrack(esdTr);
    
    }// end loop over particles
    //AliESDUtils::RefitESDVertexTracks(esd);
    double posVtx[3]={0,0,0};
    double sigmaVtx[3]={0,0,0};
    double covMatrix[6]={sigmaVtx[0]*sigmaVtx[0],0.,sigmaVtx[1]*sigmaVtx[1],0.,0.,sigmaVtx[2]*sigmaVtx[2]};
    AliESDVertex *myVtx = new AliESDVertex(posVtx,sigmaVtx,"Vertex");
    esd->SetPrimaryVertexTracks(myVtx);
    AliESDVertex *esdVtx=(AliESDVertex*)esd->GetPrimaryVertexTracks();
    //esdVtx->Print();
    Double_t sigma[3]={0.,0.,0.};
    Double_t position[3]={0.,0.,0.};
    esdVtx->GetSigmaXYZ(sigma);
    esdVtx->GetXYZ(position);
    fHistRecoVertexSigmaX->Fill(sigma[0]);
    fHistRecoVertexSigmaY->Fill(sigma[1]); 
    fHistRecoVertexSigmaZ->Fill(sigma[2]); 
    fHistRecoVertexX->Fill(position[0]);
    fHistRecoVertexY->Fill(position[1]);
    fHistRecoVertexZ->Fill(position[2]);

    
}
//________________________________________________________________________
void AliAnalysisTaskSEOmegacccToOmega3Pi::FillTrackDistributions(AliESDEvent *esd){

    int ntr = esd->GetNumberOfTracks();
     //printf("Event %d: ntr = %d\n",iev,ntr);
     //printf("Generated vertex: %+e %+e %+e\n",vx,vy,vz);
     //const AliESDVertex *vtxT3D=esdEv->GetPrimaryVertexTracks();
     //vtxT3D->Print();
        
    for (int itr=0;itr<ntr;itr++) {
        fNentries->Fill(6);
        AliESDtrack* esdtr = esd->GetTrack(itr);
        Float_t recoPt=esdtr->Pt();
        Float_t recoEta=esdtr->Eta();
        Float_t recoY=esdtr->Y();
        Int_t lbl=esdtr->GetLabel();
        
        //corresponding generated particle
        TParticle *mcPart=fMcEvent->Particle(lbl);
        Float_t genPt=mcPart->Pt();
        Float_t genEta=mcPart->Eta();
        Float_t genY=mcPart->Y();
        Float_t genRad=mcPart->Rho();
        int pdgCodePart=TMath::Abs(mcPart->GetPdgCode());
        
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
        //printf("\n");
        
        //Fill histograms
        fHistnHitsVsGenPt->Fill(genPt,nhits);
        fHistnHitsVsGenY->Fill(genY,nhits);
        fHistnHitsVsGenEta->Fill(genEta,nhits);
        fHistnHitsVsProdRad->Fill(genRad,nhits);
        fHistRecoPtVsGenPt->Fill(genPt,recoPt);
        fHistRecoYVsGenY->Fill(genY,recoY);
        fHistRecoEtaVsGenEta->Fill(genEta,recoEta);
        
    
        
        switch (pdgCodePart) {
        case 211: //pion
        fhPtRecoEtaRecoNhits_pi->Fill(recoPt,recoEta,nhits);
        fhPtGenEtaGenNhits_pi->Fill(genPt,genEta,nhits);  
        fhPtGenEtaGen_piReco->Fill(genPt,genEta);
        //if(genEta < 1.){
        	if(IsTrackFromCharmBaryon(esdtr, 4444))fPiRecoFromVsPtGen[0]->Fill(genPt);
        	if(IsTrackFromCharmBaryon(esdtr, 4432))fPiRecoFromVsPtGen[1]->Fill(genPt);
        	if(IsTrackFromCharmBaryon(esdtr, 4332))fPiRecoFromVsPtGen[2]->Fill(genPt);
        	if(IsTrackFromCharmBaryon(esdtr, 3122))fPiRecoFromVsPtGen[3]->Fill(genPt);
        //}
        break;
        case 2212: //proton
        fhPtRecoEtaRecoNhits_p->Fill(recoPt,recoEta,nhits); 
        fhPtGenEtaGenNhits_p->Fill(genPt,genEta,nhits);   
        fhPtGenEtaGen_pReco->Fill(genPt,genEta);  
        fPRecoVsPtGen->Fill(genPt);
        break;
        case 321: //kaon
        fhPtRecoEtaRecoNhits_k->Fill(recoPt,recoEta,nhits); 
        fhPtGenEtaGenNhits_k->Fill(genPt,genEta,nhits); 
        fhPtGenEtaGen_kReco->Fill(genPt,genEta);  
        fKRecoVsPtGen->Fill(genPt);  
        break;
        }
            
        ////
        ULong_t status=esdtr->GetStatus();
        //Printf("status %ld", status);
        //if ((status&AliESDtrack::kTPCin)==0) {Printf("NO TPC in"); return;}
        //if ((status&AliESDtrack::kTPCout)==0) {Printf("NO TPC out"); return;}
        //if ((status&AliESDtrack::kTPCrefit)==0) {Printf("NO TPC refit"); return;}
    }
        
        
}
//________________________________________________________________________
void AliAnalysisTaskSEOmegacccToOmega3Pi::FillCascadeHistos(AliESDEvent *esd){ 

	const AliESDVertex *lPrimaryBestESDVtx = esd->GetPrimaryVertex();
    Double_t lBestPrimaryVtxPos[3]          = {-100.0, -100.0, -100.0};
    lPrimaryBestESDVtx->GetXYZ( lBestPrimaryVtxPos );
    
    Double_t lMagneticField = -10;
    lMagneticField = esd->GetMagneticField( );
    
    UInt_t lIdxPosXi, lIdxNegXi, lBachIdx;
    AliESDtrack *pTrackXi, *nTrackXi, *bachTrackXi;
    Double_t lV0quality;
    Double_t lInvMassXiMinus, lInvMassOmega, lInvMassXiPlus, lXiCosineOfPointingAngle, lXiRadius, lrecoPt;
    Double_t lPosXi[3];
	Int_t lblPosV0Dghter, lblNegV0Dghter, lblMotherPosV0Dghter, lblMotherNegV0Dghter, lblBach, lblGdMotherPosV0Dghter, lblGdMotherNegV0Dghter, lblMotherBach;
    TParticle *mcBachForPID, *mcPosV0Dghter, *mcNegV0Dghter, *mcMotherPosV0Dghter, *mcMotherNegV0Dghter, *mcGdMotherPosV0Dghter, *mcGdMotherNegV0Dghter, *mcMotherBach, *mcBach; 
	Bool_t   lAssoXiMinus, lAssoXiPlus, lAssoOmegaMinus, lAssoOmegaPlus;
    
    Int_t nCasc=(Int_t)esd->GetNumberOfCascades();
    Long_t i;
    for(i=0; i<nCasc; i++){
        AliESDcascade *casc=esd->GetCascade(i);
        if (!casc) continue;
	     // - Connection to daughter tracks of the current cascade		
        lIdxPosXi = 0x0;  lIdxPosXi = (UInt_t) TMath::Abs( casc->GetPindex() );
        lIdxNegXi = 0x0;  lIdxNegXi = (UInt_t) TMath::Abs( casc->GetNindex() );
        lBachIdx  = 0x0;  lBachIdx  = (UInt_t) TMath::Abs( casc->GetBindex() );
        // - Rejection of a double use of a daughter track (nothing but just a crosscheck of what is done in the cascade vertexer)
        if(lBachIdx == lIdxNegXi) {  AliWarning("Pb / Idx(Bach. track) = Idx(Neg. track) ... continue!");   continue;  }
        if(lBachIdx == lIdxPosXi) {  AliWarning("Pb / Idx(Bach. track) = Idx(Pos. track) ... continue!");   continue;  }
        // - Get the daughter tracks
	     pTrackXi = 0x0;  pTrackXi    = esd->GetTrack( lIdxPosXi );
	     nTrackXi = 0x0;  nTrackXi    = esd->GetTrack( lIdxNegXi );
	     bachTrackXi = 0x0;  bachTrackXi = esd->GetTrack( lBachIdx  );
		if (!pTrackXi || !nTrackXi || !bachTrackXi ) { AliWarning("ERROR: Could not retrieve one of the 3 daughter tracks of the cascade ..."); continue; }
		// - Info over reconstructed cascades
	    lV0quality = 0.;
	    if( bachTrackXi->Charge() < 0 ) {
                  //Calculate the effective mass of the Xi- candidate: Xi- hyp. (pdg code 3312)
	        lV0quality = 0.;
		  	casc->ChangeMassHypothesis(lV0quality , 3312);  	
		  	lInvMassXiMinus = casc->GetEffMassXi();
                  //Calculate the effective mass of the Xi- candidate: Omega- hyp. (pdg code 3334)
		  	lV0quality = 0.;
		  	casc->ChangeMassHypothesis(lV0quality , 3334); 	
		  	//lInvMassOmegaMinus = casc->GetEffMassXi();
		  	lInvMassOmega = casc->GetEffMassXi();
                  //Back to "default" hyp. (Xi-)	
		  	lV0quality = 0.;
		  	casc->ChangeMassHypothesis(lV0quality , 3312);
	    }
	    if( bachTrackXi->Charge() >  0 ){
                  //Calculate the effective mass of the Xi- candidate: Xi+ hyp. (pdg code -3312)
	        lV0quality = 0.;
		  	casc->ChangeMassHypothesis(lV0quality , -3312); 	
		  	lInvMassXiPlus = casc->GetEffMassXi();
                  //Calculate the effective mass of the Xi- candidate: Omega+ hyp. (pdg code -3334)
            lV0quality = 0.;
            casc->ChangeMassHypothesis(lV0quality , -3334); 	
            //lInvMassOmegaPlus = casc->GetEffMassXi();
            lInvMassOmega = casc->GetEffMassXi();
		  		  //Back to "default" hyp. (Xi-)
            lV0quality = 0.;
            casc->ChangeMassHypothesis(lV0quality , -3312);
	    }
	    casc->GetXYZcascade( lPosXi[0], lPosXi[1], lPosXi[2] ); 
        lXiCosineOfPointingAngle   = casc->GetCascadeCosineOfPointingAngle( lBestPrimaryVtxPos[0], lBestPrimaryVtxPos[1], lBestPrimaryVtxPos[2] );
        lXiRadius = TMath::Sqrt( lPosXi[0]*lPosXi[0] + lPosXi[1]*lPosXi[1] );
        lrecoPt = casc->Pt();
		
		Double_t etagen=-99.;
        Double_t ptgen=-99.;
        Double_t etadau_0=-99.;
        Double_t etadau_1=-99.;
		// - Level of the V0 daughters
        lblPosV0Dghter = 0;  lblPosV0Dghter = (Int_t) TMath::Abs( pTrackXi->GetLabel() );  
        lblNegV0Dghter = 0;  lblNegV0Dghter = (Int_t) TMath::Abs( nTrackXi->GetLabel() );  		
        mcPosV0Dghter = 0x0; mcPosV0Dghter = fMcEvent->Particle( lblPosV0Dghter );
        mcNegV0Dghter = 0x0; mcNegV0Dghter = fMcEvent->Particle( lblNegV0Dghter );
        // - Level of the cascade daughters	
        lblMotherPosV0Dghter = 0.;  lblMotherPosV0Dghter = mcPosV0Dghter->GetFirstMother(); 
        lblMotherNegV0Dghter = 0.;  lblMotherNegV0Dghter = mcNegV0Dghter->GetFirstMother();
        //if (lblMotherPosV0Dghter != lblMotherNegV0Dghter) continue; // same mother
        //if (lblMotherPosV0Dghter < 0) continue;                     // this particle is primary, no mother   
        //if (lblMotherNegV0Dghter < 0) continue;                     // this particle is primary, no mother
        if(lblMotherPosV0Dghter == lblMotherNegV0Dghter && lblMotherPosV0Dghter > 0 && lblMotherNegV0Dghter > 0){
        	// mothers = Lambda candidate ... a priori
        	mcMotherPosV0Dghter = 0x0; mcMotherPosV0Dghter = fMcEvent->Particle( lblMotherPosV0Dghter );
        	mcMotherNegV0Dghter = 0x0; mcMotherNegV0Dghter = fMcEvent->Particle( lblMotherNegV0Dghter );  // MN: redundant?? already checked that labels are the same...-->same part from stack
        	lblBach = 0; lblBach = (Int_t) TMath::Abs( bachTrackXi->GetLabel() );
        	mcBach = 0x0; mcBach = fMcEvent->Particle( lblBach );	
        	// - Level of cascade candidate
        	lblGdMotherPosV0Dghter = 0; lblGdMotherPosV0Dghter = mcMotherPosV0Dghter->GetFirstMother() ;
        	lblGdMotherNegV0Dghter = 0; lblGdMotherNegV0Dghter = mcMotherNegV0Dghter->GetFirstMother() ;
        	//if(lblGdMotherPosV0Dghter != lblGdMotherNegV0Dghter) continue;
        	//if(lblGdMotherPosV0Dghter < 0) continue;                  // primary lambda ...   
        	//if(lblGdMotherNegV0Dghter < 0) continue;                  // primary lambda ...
        	if(lblGdMotherPosV0Dghter == lblGdMotherNegV0Dghter && lblGdMotherPosV0Dghter>0 && lblGdMotherNegV0Dghter>0){   				
        		// Gd mothers = cascade candidate ... a priori
        		mcGdMotherPosV0Dghter = 0x0; mcGdMotherPosV0Dghter = fMcEvent->Particle( lblGdMotherPosV0Dghter );
        		mcGdMotherNegV0Dghter = 0x0; mcGdMotherNegV0Dghter = fMcEvent->Particle( lblGdMotherNegV0Dghter );				
        		lblMotherBach = 0; lblMotherBach = (Int_t) TMath::Abs( mcBach->GetFirstMother() );  
        		//if(lblMotherBach != lblGdMotherPosV0Dghter) continue; //same mother for bach and V0 daughters
        		if(lblMotherBach == lblGdMotherPosV0Dghter){
        			mcMotherBach = 0x0; mcMotherBach = fMcEvent->Particle( lblMotherBach );  
        			etagen=mcMotherBach->Eta();
            		ptgen=mcMotherBach->Pt();
            		etadau_0=((TParticle*)fMcEvent->Particle((mcMotherBach->GetDaughter(0))))->Eta();
            		etadau_1=((TParticle*)fMcEvent->Particle((mcMotherBach->GetDaughter(1))))->Eta();
        			// - Manage boolean for association
        			if      (mcMotherBach->GetPdgCode() == 3312  && mcGdMotherPosV0Dghter->GetPdgCode() == 3312  && mcGdMotherNegV0Dghter->GetPdgCode() == 3312)  {lAssoXiMinus    = kTRUE;}
        			else if (mcMotherBach->GetPdgCode() == -3312 && mcGdMotherPosV0Dghter->GetPdgCode() == -3312 && mcGdMotherNegV0Dghter->GetPdgCode() == -3312) {lAssoXiPlus     = kTRUE;}
        			else if (mcMotherBach->GetPdgCode() == 3334  && mcGdMotherPosV0Dghter->GetPdgCode() == 3334  && mcGdMotherNegV0Dghter->GetPdgCode() == 3334)  {lAssoOmegaMinus = kTRUE;}
        			else if (mcMotherBach->GetPdgCode() == -3334 && mcGdMotherPosV0Dghter->GetPdgCode() == -3334 && mcGdMotherNegV0Dghter->GetPdgCode() == -3334) {lAssoOmegaPlus  = kTRUE;}
        		}
        	}	
        }
        if(lAssoXiMinus  || lAssoXiPlus   || lAssoOmegaMinus || lAssoOmegaPlus ){
        	fCascInvMassS      ->Fill(lInvMassOmega); 
    		fCascRadiusS       ->Fill(lXiRadius);    
    		fCascPtS           ->Fill(lrecoPt);         
    		fCascCosPointAngleS->Fill(lXiCosineOfPointingAngle);  
    		fhOmegaRecoVsPtGen->Fill(ptgen);
    		fhPtGenEtaGen_OmegaReco->Fill(ptgen,etagen);
    		fhEtaDauVsEtaMoth_Rec[6]->Fill(etagen,etadau_0);//Omega vs Lambda
        	fhEtaDauVsEtaMoth_Rec[7]->Fill(etagen,etadau_1);//Omega vs kaon
        }
        else{
         	fCascInvMassB      ->Fill(lInvMassOmega);    
    		fCascRadiusB       ->Fill(lXiRadius);    
    		fCascPtB           ->Fill(lrecoPt);         
    		fCascCosPointAngleB->Fill(lXiCosineOfPointingAngle);
        }
      }  

}    
//________________________________________________________________________
void AliAnalysisTaskSEOmegacccToOmega3Pi::FillV0Histos(AliESDEvent *esd){
    
    
    const AliESDVertex *lPrimaryBestESDVtx = esd->GetPrimaryVertex();
    Double_t lBestPrimaryVtxPos[3]          = {-100.0, -100.0, -100.0};
    lPrimaryBestESDVtx->GetXYZ( lBestPrimaryVtxPos );
    
    Double_t lMagneticField = -10;
    lMagneticField = esd->GetMagneticField( );
    
    
    Int_t nV0=(Int_t)esd->GetNumberOfV0s();
    Long_t i;
    //Printf("V0pointangle \t DCA+toPV \t DCA-toPV \t V0radius \t decayVx \t decayVy \t decayVz \t eta+ \t eta- \t label+ \t label-");
    for(i=0; i<nV0; i++){
        AliESDv0 *v0=esd->GetV0(i);
        
        UInt_t lKeyPos = (UInt_t)TMath::Abs(v0->GetPindex());
        UInt_t lKeyNeg = (UInt_t)TMath::Abs(v0->GetNindex());
        
        AliESDtrack *pTrack=((AliESDEvent*)esd)->GetTrack(lKeyPos);
        AliESDtrack *nTrack=((AliESDEvent*)esd)->GetTrack(lKeyNeg);
        if (!pTrack || !nTrack) {
            Printf("ERROR: Could not retreive one of the daughter track");
            continue;
        }
        // MC labels daughters
        Int_t lblPosV0Dghter = (Int_t) TMath::Abs( pTrack->GetLabel() );
        Int_t lblNegV0Dghter = (Int_t) TMath::Abs( nTrack->GetLabel() );
        
        TParticle* mcPosV0Dghter = fMcEvent->Particle( lblPosV0Dghter );
        TParticle* mcNegV0Dghter = fMcEvent->Particle( lblNegV0Dghter );
        
        Int_t lPIDPositive = mcPosV0Dghter -> GetPdgCode();
        Int_t lPIDNegative = mcNegV0Dghter -> GetPdgCode();
        
        Int_t lblMotherPosV0Dghter = mcPosV0Dghter->GetFirstMother();
        Int_t lblMotherNegV0Dghter = mcNegV0Dghter->GetFirstMother();
        
        Bool_t isSignalLambda=kFALSE;
        Bool_t isSignalAntiLambda=kFALSE;
        Double_t etagen=-99.;
        Double_t ptgen=-99.;
        Double_t etadau_0=-99.;
        Double_t etadau_1=-99.;
        if( lblMotherPosV0Dghter == lblMotherNegV0Dghter && lblMotherPosV0Dghter > -1 ) {
            TParticle* pThisV0 = fMcEvent->Particle( lblMotherPosV0Dghter );
            Int_t pidV0 = pThisV0->GetPdgCode(); //PDG Code
            //Printf("Reco Lambda signal--> V0=%d-%d %s mother= %d,  d+=%d %s d-=%d %s",lblMotherPosV0Dghter,lblMotherNegV0Dghter,pThisV0->GetName(),pThisV0->GetFirstMother(),lblPosV0Dghter,mcPosV0Dghter->GetName(),lblNegV0Dghter,mcNegV0Dghter->GetName());
            if(pidV0==3122) isSignalLambda=kTRUE;
            if(pidV0==-3122) isSignalAntiLambda=kTRUE;
            etagen=pThisV0->Eta();
            ptgen=pThisV0->Pt();
            etadau_0=((TParticle*)fMcEvent->Particle((pThisV0->GetDaughter(0))))->Eta();
            etadau_1=((TParticle*)fMcEvent->Particle((pThisV0->GetDaughter(1))))->Eta();
        }
        
        
        Double_t tDecayVertexV0[3];
        v0->GetXYZ(tDecayVertexV0[0],tDecayVertexV0[1],tDecayVertexV0[2]);
        
        Double_t tV0mom[3];
        v0->GetPxPyPz( tV0mom[0],tV0mom[1],tV0mom[2] );
        Double_t lV0TotalMomentum = TMath::Sqrt(
                                                tV0mom[0]*tV0mom[0]+tV0mom[1]*tV0mom[1]+tV0mom[2]*tV0mom[2] );
        
        Double_t lV0Radius = TMath::Sqrt(tDecayVertexV0[0]*tDecayVertexV0[0]+tDecayVertexV0[1]*tDecayVertexV0[1]);
        
        Double_t lPt = v0->Pt();
        Double_t lRapK0Short = v0->RapK0Short();
        Double_t lRapLambda = v0->RapLambda();
        
        Double_t lMomPos[3];
        v0->GetPPxPyPz(lMomPos[0],lMomPos[1],lMomPos[2]);
        Double_t lMomNeg[3];
        v0->GetNPxPyPz(lMomNeg[0],lMomNeg[1],lMomNeg[2]);
        
        
        //Daughter Eta for Eta selection
        Double_t fTreeVariableNegEta = nTrack->Eta();
        Double_t fTreeVariablePosEta = pTrack->Eta();
        
        Double_t lDcaPosToPrimVertex = TMath::Abs(pTrack->GetD(lBestPrimaryVtxPos[0],
                                                               lBestPrimaryVtxPos[1],
                                                               lMagneticField) );
        
        Double_t lDcaNegToPrimVertex = TMath::Abs(nTrack->GetD(lBestPrimaryVtxPos[0],
                                                               lBestPrimaryVtxPos[1],
                                                               lMagneticField) );
        
        
        
        //lOnFlyStatus = v0->GetOnFlyStatus();
        //lChi2V0 = v0->GetChi2V0();
        Double_t lDcaV0Daughters = v0->GetDcaV0Daughters();
        Double_t lDcaV0ToPrimVertex = v0->GetD(lBestPrimaryVtxPos[0],lBestPrimaryVtxPos[1],lBestPrimaryVtxPos[2]);
        Double_t lV0CosineOfPointingAngle = v0->GetV0CosineOfPointingAngle(lBestPrimaryVtxPos[0],lBestPrimaryVtxPos[1],lBestPrimaryVtxPos[2]);
        
        // Getting invariant mass infos directly from ESD
        v0->ChangeMassHypothesis(310);
        Double_t lInvMassK0s = v0->GetEffMass();
        v0->ChangeMassHypothesis(3122);
        Double_t lInvMassLambda = v0->GetEffMass();
        v0->ChangeMassHypothesis(-3122);
        Double_t lInvMassAntiLambda = v0->GetEffMass();
        Double_t lAlphaV0 = v0->AlphaV0();
        Double_t lPtArmV0 = v0->PtArmV0();
        
        if (isSignalLambda) {
            fhV0radiusS->Fill(lV0Radius);
            fhDCAnegToPVS->Fill(lDcaNegToPrimVertex);
            fhDCAposToPVS->Fill(lDcaPosToPrimVertex);
            fhDCAV0DaughtersS->Fill(lDcaV0Daughters);
            fhCosinePointAS->Fill(lV0CosineOfPointingAngle);
            //hProperLifetime->Fill();
            fHistMassLambdaS->Fill(lInvMassLambda);
            fhV0ptS->Fill(lPt);
            fhLambdaRecoVsPtGen->Fill(ptgen);
            fhPtGenEtaGen_LambdaReco->Fill(ptgen,etagen);
            fhEtaDauVsEtaMoth_Rec[8]->Fill(etagen,etadau_1);//Lambda vs pion
        	fhEtaDauVsEtaMoth_Rec[9]->Fill(etagen,etadau_0);//Lambda vs proton
        }
        else if(isSignalAntiLambda){
            fhV0radiusS->Fill(lV0Radius);
            fhDCAnegToPVS->Fill(lDcaNegToPrimVertex);
            fhDCAposToPVS->Fill(lDcaPosToPrimVertex);
            fhDCAV0DaughtersS->Fill(lDcaV0Daughters);
            fhCosinePointAS->Fill(lV0CosineOfPointingAngle);
            //hProperLifetime->Fill();
            fHistMassAntiLambdaS->Fill(lInvMassAntiLambda);
            fhV0ptS->Fill(lPt);
            fhLambdaRecoVsPtGen->Fill(ptgen);
            fhPtGenEtaGen_LambdaReco->Fill(ptgen,etagen);
            fhEtaDauVsEtaMoth_Rec[8]->Fill(etagen,etadau_1);//Lambda vs pion
        	fhEtaDauVsEtaMoth_Rec[9]->Fill(etagen,etadau_0);//Lambda vs proton
        }
        else {
            fhV0radiusB->Fill(lV0Radius);
            fhDCAnegToPVB->Fill(lDcaNegToPrimVertex);
            fhDCAposToPVB->Fill(lDcaPosToPrimVertex);
            fhDCAV0DaughtersB->Fill(lDcaV0Daughters);
            fhCosinePointAB->Fill(lV0CosineOfPointingAngle);
            //hProperLifetime->Fill();
            fHistMassLambdaB->Fill(lInvMassLambda);
            fhV0ptB->Fill(lPt);
        }
    }
}
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
    return det;


}
