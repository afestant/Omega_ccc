#if !defined(__CINT__) || defined(__MAKECINT__)

#include <Riostream.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TStyle.h>
#include <TString.h>
#include <TList.h>
#include <TTree.h>
#include <TDatabasePDG.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

//#include "cling/Interpreter/InvocationOptions.h"

//#include "llvm/ADT/StringRef.h"
#define TreeRecoTracks_cxx
#define TreeGenOmegaccc_cxx
#define TreeGenV0Reco_cxx
#define TreeGenCascV0Reco_cxx
#define TreeReconstruction_cxx
#define TreeCutVarOmegaccc_cxx
#define TreeCutVarOmegacc_cxx
#define TreeCutVarOmegac_cxx
#include "TreeCutVarOmegaccc.h"
#include "TreeCutVarOmegacc.h"
#include "TreeCutVarOmegac.h"
#include "TreeGenCascV0Reco.h"
#include "TreeGenOmegaccc.h"
#include "TreeGenV0Reco.h"
#include "TreeRecoTracks.h"
#include "TreeReconstruction.h"

#endif
void DrawCorrelationPlots(TreeGenOmegaccc &t, TreeRecoTracks &t_rec, TreeGenV0Reco &t_rec_v0, TreeGenCascV0Reco &t_rec_casc, TreeCutVarOmegaccc &t_rec_omegaccc, TreeCutVarOmegacc &t_rec_omegacc, TreeCutVarOmegac &t_rec_omegac);
void DrawReconstructionPlots(TreeReconstruction &t);

void tree_analysis_new(){
    //TFile *fout = new TFile("tree_reco.root","RECREATE");
    TFile *f=TFile::Open("signal/AnalysisResults.root");
    TDirectoryFile *d=(TDirectoryFile*)f->Get("MCanalysis");
    
    TTree    *treeGenOmegaccc       = (TTree*)d->Get("TreeGenOmegaccc");
    TTree    *treeRecoTracks        = (TTree*)d->Get("TreeRecoTracks");
    TTree    *treeCutVarOmegaccc    = (TTree*)d->Get("TreeCutVarOmegaccc");
    TTree    *treeCutVarOmegacc     = (TTree*)d->Get("TreeCutVarOmegacc");
    TTree    *treeCutVarOmegac      = (TTree*)d->Get("TreeCutVarOmegac");
    TTree    *treeGenCascV0Reco     = (TTree*)d->Get("TreeGenCascV0Reco");
    TTree    *treeGenV0Reco         = (TTree*)d->Get("TreeGenV0Reco");
    TTree    *treeReconstruction    = (TTree*)d->Get("TreeReconstruction");
    
//    treeReconstruction->SetDirectory(fout);
//    fout->cd();
//    treeReconstruction->Write();
//    fout->Close();
    
//}
    
    TreeGenOmegaccc t_gen(treeGenOmegaccc);
    TreeRecoTracks  t_rec(treeRecoTracks);
    int ngen=t_gen.GetEntriesFast();
    int nrec=t_rec.GetEntriesFast();
    Printf("ngen %d nrec %d ",ngen,nrec);
    TreeReconstruction t_reconstruction(treeReconstruction);
    TH1::AddDirectory(kFALSE);
    DrawReconstructionPlots(t_reconstruction);
    
    
//    const int npart = 11;
//    TString part[npart] = {"pi_from_l", "p_from_l", "k_from_o", "l", "o","omegaccc","pi_from_omegaccc","pi_from_omegacc","pi_from_omegac","omegacc","omegac"};
//    TH1F* hPt_gen[npart];
//    TH2F* hRxyVsPt_gen[npart];
//    TH1F* hPt_rec[npart];
//    TH2F* hRxyVsPt_rec[npart];
//    TH1F* hEff[npart];
//    TH2F* hEff2d[npart];
//    const int nbins_rad = 10;
//    TH1F* hEffVsRad[npart][nbins_rad];
//    float minx[npart]={0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.};
//    float maxx[npart]={10.,10.,10.,10.,10.,20.,20.,20.,20.,20.,20.};
//    float miny[npart]={0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.};
//    float maxy[npart]={100.,100.,100.,100.,2.,0.1,0.5,0.5,0.5,0.5,0.5};
//    int nbinsx[npart]={100,100,100,100,100,100,100,100,100,100,100};
//    int nbinsy[npart]={1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000};
//    for(int j=0; j<npart; j++){
//        hPt_gen[j] = new TH1F(Form("hpt_gen_%s",part[j].Data()),Form("gen_%s;pt (GeV/c)",part[j].Data()),nbinsx[j],minx[j],maxx[j]);
//        hPt_rec[j] = new TH1F(Form("hpt_rec_%s",part[j].Data()),Form("rec_%s;pt (GeV/c)",part[j].Data()),nbinsx[j],minx[j],maxx[j]);
//        hRxyVsPt_gen[j] = new TH2F(Form("hRxy_vs_pt_gen_%s",part[j].Data()),Form("gen_%s;pt (GeV/c);Rxy (cm)",part[j].Data()),nbinsx[j],minx[j],maxx[j],nbinsy[j],miny[j],maxy[j]);
//        hRxyVsPt_rec[j] = new TH2F(Form("hRxy_vs_pt_rec_%s",part[j].Data()),Form("rec_%s;pt (GeV/c);Rxy (cm)",part[j].Data()),nbinsx[j],minx[j],maxx[j],nbinsy[j],miny[j],maxy[j]);
//        hEff[j] = new TH1F(Form("hEff_%s",part[j].Data()),Form("eff_%s;pt (GeV/c)",part[j].Data()),nbinsx[j],minx[j],maxx[j]);
//        hEff2d[j] = new TH2F(Form("hEff2d_%s",part[j].Data()),Form("eff_%s;pt (GeV/c);Rxy (cm)",part[j].Data()),nbinsx[j],minx[j],maxx[j],nbinsy[j],miny[j],maxy[j]);
//    }
//    //generated particles histograms
//    for(int igen = 0; igen<ngen; igen++){
//        t_gen.GetEntry(igen);
//        //Printf("%f %f %f %f %f %f %f %f %f %f %f",t_gen.fTreeGen_p_Pt,t_gen.fTreeGen_pi4_Pt,t_gen.fTreeGen_k_Pt,t_gen.fTreeGen_lambda_Pt,t_gen.fTreeGen_omega_Pt,t_gen.fTreeGen_pi3_Pt,t_gen.fTreeGen_omegac_Pt,t_gen.fTreeGen_pi2_Pt,t_gen.fTreeGen_omegacc_Pt,t_gen.fTreeGen_pi1_Pt,t_gen.fTreeGen_omegaccc_Pt);
//        //pion from L + acceptance
//        if(TMath::Abs(t_gen.fTreeGen_pi4_Eta)<1. && t_gen.fTreeGen_pi4_ReconstructableHits>=4){
//            //fill histo N vs pT
//            hPt_gen[0]->Fill(t_gen.fTreeGen_pi4_Pt);
//            //fill histo Rxy vs pT
//            hRxyVsPt_gen[0]->Fill(t_gen.fTreeGen_pi4_Pt,t_gen.fTreeGen_pi4_Rxy);
//            //Printf("%f %f ",t_gen.fTreeGen_pi4_Pt, t_gen.fTreeGen_pi4_Rxy);
//        }
//        //proton from L + acceptance
//        if(TMath::Abs(t_gen.fTreeGen_p_Eta)<1. && t_gen.fTreeGen_p_ReconstructableHits>=4){
//            //fill histo N vs pT
//            hPt_gen[1]->Fill(t_gen.fTreeGen_p_Pt);
//            //fill histo Rxy vs pT
//            hRxyVsPt_gen[1]->Fill(t_gen.fTreeGen_p_Pt,t_gen.fTreeGen_p_Rxy);
//        }
//        //kaon from O + acceptance
//        if(TMath::Abs(t_gen.fTreeGen_k_Eta)<1. && t_gen.fTreeGen_k_ReconstructableHits>=4){
//            //fill histo N vs pT
//            hPt_gen[2]->Fill(t_gen.fTreeGen_k_Pt);
//            //fill histo Rxy vs pT
//            hRxyVsPt_gen[2]->Fill(t_gen.fTreeGen_k_Pt,t_gen.fTreeGen_k_Rxy);
//        }
//        //V0 + daughter acceptance
//        if(TMath::Abs(t_gen.fTreeGen_pi4_Eta)<1. && TMath::Abs(t_gen.fTreeGen_p_Eta)<1. && t_gen.fTreeGen_p_ReconstructableHits>=4 && t_gen.fTreeGen_pi4_ReconstructableHits>=4){
//            //fill histo N vs pT
//            hPt_gen[3]->Fill(t_gen.fTreeGen_lambda_Pt);
//            //fill histo Rxy vs pT
//            hRxyVsPt_gen[3]->Fill(t_gen.fTreeGen_lambda_Pt,t_gen.fTreeGen_lambda_Rxy);
//        }
//        //Casc + daughter acceptance
//        if(TMath::Abs(t_gen.fTreeGen_pi4_Eta)<1. && TMath::Abs(t_gen.fTreeGen_p_Eta)<1. && TMath::Abs(t_gen.fTreeGen_k_Eta)<1. && t_gen.fTreeGen_pi4_ReconstructableHits>=4 && t_gen.fTreeGen_p_ReconstructableHits>=4 && t_gen.fTreeGen_k_ReconstructableHits>=4){
//            //fill histo N vs pT
//            hPt_gen[4]->Fill(t_gen.fTreeGen_omega_Pt);
//            //fill histo Rxy vs pT
//            hRxyVsPt_gen[4]->Fill(t_gen.fTreeGen_omega_Pt,t_gen.fTreeGen_omega_Rxy);
//        }
//        //Omegaccc + daughter acceptance
//        if(TMath::Abs(t_gen.fTreeGen_pi1_Eta)<1. && TMath::Abs(t_gen.fTreeGen_pi2_Eta)<1. && TMath::Abs(t_gen.fTreeGen_pi3_Eta)<1. && TMath::Abs(t_gen.fTreeGen_pi4_Eta)<1. && TMath::Abs(t_gen.fTreeGen_p_Eta)<1. && TMath::Abs(t_gen.fTreeGen_k_Eta)<1. /*&& t_gen.fTreeGen_pi1_Pt>0.5 && t_gen.fTreeGen_pi2_Pt>0.5  && t_gen.fTreeGen_pi3_Pt>0.5 */&& TMath::Abs(t_gen.fTreeGen_omegaccc_Y)<1. && t_gen.fTreeGen_pi4_ReconstructableHits>=4 && t_gen.fTreeGen_pi3_ReconstructableHits>=4 && t_gen.fTreeGen_pi2_ReconstructableHits>=4 && t_gen.fTreeGen_pi1_ReconstructableHits>=4 && t_gen.fTreeGen_p_ReconstructableHits>=4 && t_gen.fTreeGen_k_ReconstructableHits>=4){
//            //fill histo N vs pT
//            hPt_gen[5]->Fill(t_gen.fTreeGen_omegaccc_Pt);
//            //fill histo Rxy vs pT
//            hRxyVsPt_gen[5]->Fill(t_gen.fTreeGen_omegaccc_Pt,t_gen.fTreeGen_omegaccc_Rxy);
//        }
//        //pion from Omegaccc + acceptance
//        if(TMath::Abs(t_gen.fTreeGen_pi1_Eta)<1. && t_gen.fTreeGen_pi1_ReconstructableHits>=4){
//            //fill histo N vs pT
//            hPt_gen[6]->Fill(t_gen.fTreeGen_pi1_Pt);
//            //fill histo Rxy vs pT
//            hRxyVsPt_gen[6]->Fill(t_gen.fTreeGen_pi1_Pt,t_gen.fTreeGen_pi1_Rxy);
//        }
//        //pion from Omegacc + acceptance
//        if(TMath::Abs(t_gen.fTreeGen_pi2_Eta)<1. && t_gen.fTreeGen_pi2_ReconstructableHits>=4){
//            //fill histo N vs pT
//            hPt_gen[7]->Fill(t_gen.fTreeGen_pi2_Pt);
//            //fill histo Rxy vs pT
//            hRxyVsPt_gen[7]->Fill(t_gen.fTreeGen_pi2_Pt,t_gen.fTreeGen_pi2_Rxy);
//        }
//        //pion from Omegac + acceptance
//        if(TMath::Abs(t_gen.fTreeGen_pi3_Eta)<1. && t_gen.fTreeGen_pi3_ReconstructableHits>=4){
//            //fill histo N vs pT
//            hPt_gen[8]->Fill(t_gen.fTreeGen_pi3_Pt);
//            //fill histo Rxy vs pT
//            hRxyVsPt_gen[8]->Fill(t_gen.fTreeGen_pi3_Pt,t_gen.fTreeGen_pi3_Rxy);
//        }
//        //Omegacc + daughter acceptance
//        if(TMath::Abs(t_gen.fTreeGen_pi2_Eta)<1. && TMath::Abs(t_gen.fTreeGen_pi3_Eta)<1. && TMath::Abs(t_gen.fTreeGen_pi4_Eta)<1. && TMath::Abs(t_gen.fTreeGen_p_Eta)<1. && TMath::Abs(t_gen.fTreeGen_k_Eta)<1. /*&& t_gen.fTreeGen_pi1_Pt>0.5 && t_gen.fTreeGen_pi2_Pt>0.5  && t_gen.fTreeGen_pi3_Pt>0.5 */&& TMath::Abs(t_gen.fTreeGen_omegacc_Y)<1. && t_gen.fTreeGen_pi4_ReconstructableHits>=4 && t_gen.fTreeGen_pi3_ReconstructableHits>=4 && t_gen.fTreeGen_pi2_ReconstructableHits>=4 && t_gen.fTreeGen_p_ReconstructableHits>=4 && t_gen.fTreeGen_k_ReconstructableHits>=4){
//            //fill histo N vs pT
//            hPt_gen[9]->Fill(t_gen.fTreeGen_omegacc_Pt);
//            //fill histo Rxy vs pT
//            hRxyVsPt_gen[9]->Fill(t_gen.fTreeGen_omegacc_Pt,t_gen.fTreeGen_omegacc_Rxy);
//        }
//        //Omegac + daughter acceptance
//        if(TMath::Abs(t_gen.fTreeGen_pi3_Eta)<1. && TMath::Abs(t_gen.fTreeGen_pi4_Eta)<1. && TMath::Abs(t_gen.fTreeGen_p_Eta)<1. && TMath::Abs(t_gen.fTreeGen_k_Eta)<1. /*&& t_gen.fTreeGen_pi1_Pt>0.5 && t_gen.fTreeGen_pi2_Pt>0.5  && t_gen.fTreeGen_pi3_Pt>0.5 */&& TMath::Abs(t_gen.fTreeGen_omegac_Y)<1. && t_gen.fTreeGen_pi4_ReconstructableHits>=4 && t_gen.fTreeGen_pi3_ReconstructableHits>=4 && t_gen.fTreeGen_p_ReconstructableHits>=4 && t_gen.fTreeGen_k_ReconstructableHits>=4){
//            //fill histo N vs pT
//            hPt_gen[10]->Fill(t_gen.fTreeGen_omegac_Pt);
//            //fill histo Rxy vs pT
//            hRxyVsPt_gen[10]->Fill(t_gen.fTreeGen_omegac_Pt,t_gen.fTreeGen_omegac_Rxy);
//        }
//    }
//    //reconstructed tracks histograms
//    for(int irec = 0; irec<nrec; irec++){
//        t_rec.GetEntry(irec);
//        //pion from L + acceptance
//        if(TMath::Abs(t_rec.fGen_eta)<1. && TMath::Abs(t_rec.fReco_pdg)==211 && TMath::Abs(t_rec.fReco_pdgMother)==3122){
//            //fill histo N vs pT
//            hPt_rec[0]->Fill(t_rec.fGen_pt);
//            hEff[0]->Fill(t_rec.fGen_pt);
//            //fill histo Rxy vs pT
//            hRxyVsPt_rec[0]->Fill(t_rec.fGen_pt,t_rec.fGen_rxy);
//            hEff2d[0]->Fill(t_rec.fGen_pt,t_rec.fGen_rxy);
//        }
//        //proton from L + acceptance
//        if(TMath::Abs(t_rec.fGen_eta)<1. && TMath::Abs(t_rec.fReco_pdg)==2212 && TMath::Abs(t_rec.fReco_pdgMother)==3122){
//            //fill histo N vs pT
//            hPt_rec[1]->Fill(t_rec.fGen_pt);
//            hEff[1]->Fill(t_rec.fGen_pt);
//            //fill histo Rxy vs pT
//            hRxyVsPt_rec[1]->Fill(t_rec.fGen_pt,t_rec.fGen_rxy);
//            hEff2d[1]->Fill(t_rec.fGen_pt,t_rec.fGen_rxy);
//        }
//        //kaon from O + acceptance
//        if(TMath::Abs(t_rec.fGen_eta)<1. && TMath::Abs(t_rec.fReco_pdg)==321 && TMath::Abs(t_rec.fReco_pdgMother)==3334){
//            //fill histo N vs pT
//            hPt_rec[2]->Fill(t_rec.fGen_pt);
//            hEff[2]->Fill(t_rec.fGen_pt);
//            //fill histo Rxy vs pT
//            hRxyVsPt_rec[2]->Fill(t_rec.fGen_pt,t_rec.fGen_rxy);
//            hEff2d[2]->Fill(t_rec.fGen_pt,t_rec.fGen_rxy);
//        }
//        //pion from Omegaccc
//        if(TMath::Abs(t_rec.fGen_eta)<1. && TMath::Abs(t_rec.fReco_pdg)==211 && TMath::Abs(t_rec.fReco_pdgMother)==4444){
//            //fill histo N vs pT
//            hPt_rec[6]->Fill(t_rec.fGen_pt);
//            hEff[6]->Fill(t_rec.fGen_pt);
//            //fill histo Rxy vs pT
//            hRxyVsPt_rec[6]->Fill(t_rec.fGen_pt,t_rec.fGen_rxy);
//            hEff2d[6]->Fill(t_rec.fGen_pt,t_rec.fGen_rxy);
//        }
//        //pion from Omegacc
//        if(TMath::Abs(t_rec.fGen_eta)<1. && TMath::Abs(t_rec.fReco_pdg)==211 && TMath::Abs(t_rec.fReco_pdgMother)==4432){
//            //fill histo N vs pT
//            hPt_rec[7]->Fill(t_rec.fGen_pt);
//            hEff[7]->Fill(t_rec.fGen_pt);
//            //fill histo Rxy vs pT
//            hRxyVsPt_rec[7]->Fill(t_rec.fGen_pt,t_rec.fGen_rxy);
//            hEff2d[7]->Fill(t_rec.fGen_pt,t_rec.fGen_rxy);
//        }
//        //pion from Omegac
//        if(TMath::Abs(t_rec.fGen_eta)<1. && TMath::Abs(t_rec.fReco_pdg)==211 && TMath::Abs(t_rec.fReco_pdgMother)==4332){
//            //fill histo N vs pT
//            hPt_rec[8]->Fill(t_rec.fGen_pt);
//            hEff[8]->Fill(t_rec.fGen_pt);
//            //fill histo Rxy vs pT
//            hRxyVsPt_rec[8]->Fill(t_rec.fGen_pt,t_rec.fGen_rxy);
//            hEff2d[8]->Fill(t_rec.fGen_pt,t_rec.fGen_rxy);
//        }
//    }
//    TreeGenV0Reco  t_rec_v0(treeGenV0Reco);
//    int nrecv0=t_rec_v0.GetEntriesFast();
//    Printf("nrecv0 %d",nrecv0);
//    for(int irecv0 = 0; irecv0<nrecv0; irecv0++){
//        t_rec_v0.GetEntry(irecv0);
//        //v0 + daughter acceptance
//        if(TMath::Abs(t_rec_v0.fTreeGen_p_Eta)<1. && TMath::Abs(t_rec_v0.fTreeGen_pi4_Eta)<1.){
//            //fill histo N vs pT
//            hPt_rec[3]->Fill(t_rec_v0.fTreeGen_lambda_Pt);
//            hEff[3]->Fill(t_rec_v0.fTreeGen_lambda_Pt);
//            //fill histo Rxy vs pT
//            hRxyVsPt_rec[3]->Fill(t_rec_v0.fTreeGen_lambda_Pt,t_rec_v0.fTreeGen_lambda_Rxy);
//            hEff2d[3]->Fill(t_rec_v0.fTreeGen_lambda_Pt,t_rec_v0.fTreeGen_lambda_Rxy);
//        }
//    }
//    TreeGenCascV0Reco  t_rec_casc(treeGenCascV0Reco);
//    int nreccasc=t_rec_casc.GetEntriesFast();
//    Printf("nreccasc %d",nreccasc);
//    for(int ireccasc = 0; ireccasc<nreccasc; ireccasc++){
//        t_rec_casc.GetEntry(ireccasc);
//        //Casc + daughter acceptance
//        if(TMath::Abs(t_rec_casc.fTreeGen_pi4_Eta)<1. && TMath::Abs(t_rec_casc.fTreeGen_p_Eta)<1. && TMath::Abs(t_rec_casc.fTreeGen_k_Eta)<1.){
//            //fill histo N vs pT
//            hPt_rec[4]->Fill(t_rec_casc.fTreeGen_omega_Pt);
//            hEff[4]->Fill(t_rec_casc.fTreeGen_omega_Pt);
//            //fill histo Rxy vs pT
//            hRxyVsPt_rec[4]->Fill(t_rec_casc.fTreeGen_omega_Pt,t_rec_casc.fTreeGen_omega_Rxy);
//            hEff2d[4]->Fill(t_rec_casc.fTreeGen_omega_Pt,t_rec_casc.fTreeGen_omega_Rxy);
//        }
//    }
//    //reco Omegaccc
//    TreeCutVarOmegaccc  t_rec_omegaccc(treeCutVarOmegaccc);
//    int nrecomegaccc=t_rec_omegaccc.GetEntriesFast();
//    Printf("nrecomegaccc cand %d",nrecomegaccc);
//    for(int irecomegaccc = 0; irecomegaccc<nrecomegaccc; irecomegaccc++){
//        t_rec_omegaccc.GetEntry(irecomegaccc);
//        //Omegaccc + daughter acceptance
//        if(TMath::Abs(t_rec_omegaccc.fGenEta_pi1)<1. && TMath::Abs(t_rec_omegaccc.fGenEta_pi2)<1. && TMath::Abs(t_rec_omegaccc.fGenEta_pi3)<1. && TMath::Abs(t_rec_omegaccc.fGenEta_V0neg)<1. && TMath::Abs(t_rec_omegaccc.fGenEta_V0pos)<1. && TMath::Abs(t_rec_omegaccc.fGenEta_CascBach)<1. && TMath::Abs(t_rec_omegaccc.fGenRap_omegaccc)<1. && t_rec_omegaccc.fIsSignal_omegaccc==true){
//            //fill histo N vs pT
//            hPt_rec[5]->Fill(t_rec_omegaccc.fGenPt_omegaccc);
//            hEff[5]->Fill(t_rec_omegaccc.fGenPt_omegaccc);
//            //fill histo Rxy vs pT
//            hRxyVsPt_rec[5]->Fill(t_rec_omegaccc.fGenPt_omegaccc,t_rec_omegaccc.fGenRxy_omegaccc);
//            hEff2d[5]->Fill(t_rec_omegaccc.fGenPt_omegaccc,t_rec_omegaccc.fGenRxy_omegaccc);
//        }
//    }
//    //reco Omegacc
//    TreeCutVarOmegacc  t_rec_omegacc(treeCutVarOmegacc);
//    int nrecomegacc=t_rec_omegacc.GetEntriesFast();
//    Printf("nrecomegacc cand %d",nrecomegacc);
//    for(int irecomegacc = 0; irecomegacc<nrecomegacc; irecomegacc++){
//        t_rec_omegacc.GetEntry(irecomegacc);
//        //Omegacc + daughter acceptance
//        if(TMath::Abs(t_rec_omegacc.fGenEta_pi2)<1. && TMath::Abs(t_rec_omegacc.fGenEta_pi3)<1. && TMath::Abs(t_rec_omegacc.fGenEta_V0neg)<1. && TMath::Abs(t_rec_omegacc.fGenEta_V0pos)<1. && TMath::Abs(t_rec_omegacc.fGenEta_CascBach)<1. && TMath::Abs(t_rec_omegacc.fGenRap_omegacc)<1. && t_rec_omegacc.fIsSignal_omegacc==true){
//            //fill histo N vs pT
//            hPt_rec[9]->Fill(t_rec_omegacc.fGenPt_omegacc);
//            hEff[9]->Fill(t_rec_omegacc.fGenPt_omegacc);
//            //fill histo Rxy vs pT
//            hRxyVsPt_rec[9]->Fill(t_rec_omegacc.fGenPt_omegacc,t_rec_omegacc.fGenRxy_omegacc);
//            hEff2d[9]->Fill(t_rec_omegacc.fGenPt_omegacc,t_rec_omegacc.fGenRxy_omegacc);
//        }
//    }
//    //reco Omegac
//    TreeCutVarOmegac  t_rec_omegac(treeCutVarOmegac);
//    int nrecomegac=t_rec_omegac.GetEntriesFast();
//    Printf("nrecomegac cand %d",nrecomegac);
//    for(int irecomegac = 0; irecomegac<nrecomegac; irecomegac++){
//        t_rec_omegac.GetEntry(irecomegac);
//        //Omegacc + daughter acceptance
//        if(TMath::Abs(t_rec_omegac.fGenEta_pi3)<1. && TMath::Abs(t_rec_omegac.fGenEta_V0neg)<1. && TMath::Abs(t_rec_omegac.fGenEta_V0pos)<1. && TMath::Abs(t_rec_omegac.fGenEta_CascBach)<1. && TMath::Abs(t_rec_omegac.fGenRap_omegac)<1. && t_rec_omegac.fIsSignal_omegac==true){
//            //fill histo N vs pT
//            hPt_rec[10]->Fill(t_rec_omegac.fGenPt_omegac);
//            hEff[10]->Fill(t_rec_omegac.fGenPt_omegac);
//            //fill histo Rxy vs pT
//            hRxyVsPt_rec[10]->Fill(t_rec_omegac.fGenPt_omegac,t_rec_omegac.fGenRxy_omegac);
//            hEff2d[10]->Fill(t_rec_omegac.fGenPt_omegac,t_rec_omegac.fGenRxy_omegac);
//        }
//    }
//
//
//
//    for(int k=0; k<npart; k++){
//        TCanvas *c = new TCanvas(Form("c_%s",part[k].Data()),Form("c_%s",part[k].Data()),0,45,2560,1395);
//        c->Divide(3,2);
//        c->cd(1);
//        gPad->SetLogy();
//        hPt_gen[k]->Draw("same");
//        c->cd(2);
//        gPad->SetLogy();
//        hPt_rec[k]->Draw("same");
//
//        hEff[k]->Divide(hPt_rec[k],hPt_gen[k],1.,1.,"B");
//        hEff2d[k]->Divide(hRxyVsPt_rec[k],hRxyVsPt_gen[k],1.,1.,"B");
//        if(k!=5){
//            for(int i=0; i<nbins_rad; i++){
//                int min = 1+i*nbinsy[k]/nbins_rad;
//                int max = (i+1)*nbinsy[k]/nbins_rad;
//                float minn = (hRxyVsPt_rec[k])->GetYaxis()->GetBinLowEdge(min);
//                float maxx = (hRxyVsPt_rec[k])->GetYaxis()->GetBinUpEdge(max);
//                //Printf("min=%f max=%f",minn, maxx);
//                TH1F *hNum = (TH1F*)hRxyVsPt_rec[k]->ProjectionX(Form("hNum_%s_%d",part[k].Data(),i),min,max);
//                hNum->SetTitle(Form("Rxy=%.1f-%.1f",minn,maxx));
//                hNum->SetLineColor(kRed-i);
//                hNum->SetMarkerColor(kRed-i);
//                hNum->SetMarkerStyle(20+i);
//                c->cd(2);
//                hNum->Draw("samehistp");
//                TH1F *hDen = (TH1F*)hRxyVsPt_gen[k]->ProjectionX(Form("hDen_%s_%d",part[k].Data(),i),min,max);
//                hDen->SetTitle(Form("Rxy=%.1f-%.1f",minn,maxx));
//                hDen->SetLineColor(kRed-i);
//                hDen->SetMarkerColor(kRed-i);
//                hDen->SetMarkerStyle(20+i);
//                c->cd(1);
//                hDen->Draw("samehistp");
//                hEffVsRad[k][i] = (TH1F*)hNum->Clone(Form("hEffVsRad_%s_%d",part[k].Data(),i));
//                hEffVsRad[k][i]->Divide(hNum,hDen,1.,1.,"B");
//                hEffVsRad[k][i]->SetNameTitle(Form("hEffVsRad_%s_%d",part[k].Data(),i),Form("Rxy=%.1f-%.1f",minn,maxx));
//                hEffVsRad[k][i]->SetLineColor(kRed-i);
//                hEffVsRad[k][i]->SetMarkerColor(kRed-i);
//                hEffVsRad[k][i]->SetMarkerStyle(20+i);
//            }
//        }
//
//        c->cd(1);
//        gPad->BuildLegend();
//        c->cd(2);
//        gPad->BuildLegend();
//        c->cd(3);
//        gPad->SetLogy();
//        hEff[k]->Draw();
//        if(k!=5){
//            for(int ii=0; ii<nbins_rad; ii++){
//                hEffVsRad[k][ii]->Draw("samehistp");
//            }
//        }
//        gPad->BuildLegend();
//        c->cd(4);
//        hRxyVsPt_gen[k]->Draw("colz");
//        //hRxyVsPt_gen[k]->Draw("sametext");
//        c->cd(5);
//        hRxyVsPt_rec[k]->Draw("colz");
//        //hRxyVsPt_rec[k]->Draw("sametext");
//        c->cd(6);
//        hEff2d[k]->Draw("colz");
//        //hEff2d[k]->Draw("sametext");
//    }

    //DrawCorrelationPlots(t_gen, t_rec, t_rec_v0, t_rec_casc, t_rec_omegaccc, t_rec_omegacc, t_rec_omegac);
}
///___________________________
void DrawCorrelationPlots(TreeGenOmegaccc &t, TreeRecoTracks &t_rec, TreeGenV0Reco &t_rec_v0, TreeGenCascV0Reco &t_rec_casc, TreeCutVarOmegaccc &t_rec_omegaccc, TreeCutVarOmegacc &t_rec_omegacc, TreeCutVarOmegac &t_rec_omegac){

    const int npar = 11;
    TString particles[npar] = {"p_from_l","pi_from_l","k_from_o","lambda","omega","pi_from_c","omegac","pi_from_cc","omegacc","pi_from_ccc","omegaccc"};
    const int nbinspt = 50;
    float minpt=0.;
    float maxpt=10.;
    //n particles generated
    //n particles generated with at least 4 reconstructable points
    TH1D *hNPartGen[npar];
    TH1D *hNPartReconstructable[npar];
    TH1D *hNPartReconstructable2[npar];
    TH1D *hNPartRec[npar];
    TH1D *hNPartReconstructableOverGen[npar];
    TH1D *hNPartReconstructedOverRec[npar];
    TH1D *hNPartReconstructedOverRec2[npar];

    TH2D *hNParticlesGen = new TH2D("hNParticlesGen","Generated; ;pt",11,0.,11.,nbinspt,minpt,maxpt);
    TH2D *hNParticlesReconstructable = new TH2D("hNParticlesReconstructable","Reconstructable; ;pt",11,0.,11.,nbinspt,minpt,maxpt);
    TH2D *hNParticlesReconstructable2 = new TH2D("hNParticlesReconstructable2","Reconstructable2; ;pt",11,0.,11.,nbinspt,minpt,maxpt);
    TH2D *hNParticlesReconstructableOverGen = new TH2D("hNParticlesReconstructableOverGen","Reconstructable/Gen; ;pt",11,0.,11.,nbinspt,minpt,maxpt);
    TH2D *hNParticlesReconstructed = new TH2D("hNParticlesReconstructed","Reconstructed; ;pt",11,0.,11.,nbinspt,minpt,maxpt);
    TH2D *hNParticlesReconstructedOverReconstructable = new TH2D("hNParticlesReconstructedOverReconstructable","Reconstructed/Reconstructable; ;pt",11,0.,11.,nbinspt,minpt,maxpt);
    TH2D *hNParticlesReconstructedOverReconstructable2 = new TH2D("hNParticlesReconstructedOverReconstructable2","Reconstructed/Reconstructable2; ;pt",11,0.,11.,nbinspt,minpt,maxpt);
    for(int i=0; i<npar; i++){
        hNParticlesGen->GetXaxis()->SetBinLabel(i+1,particles[i].Data());
        hNParticlesReconstructable->GetXaxis()->SetBinLabel(i+1,particles[i].Data());
        hNParticlesReconstructable2->GetXaxis()->SetBinLabel(i+1,particles[i].Data());
        hNParticlesReconstructableOverGen->GetXaxis()->SetBinLabel(i+1,particles[i].Data());
        hNParticlesReconstructed->GetXaxis()->SetBinLabel(i+1,particles[i].Data());
        hNParticlesReconstructedOverReconstructable->GetXaxis()->SetBinLabel(i+1,particles[i].Data());
        hNParticlesReconstructedOverReconstructable2->GetXaxis()->SetBinLabel(i+1,particles[i].Data());
    }
//    hNParticlesGen->LabelsOption("v");
//    hNParticlesReconstructable->LabelsOption("v");
//    hNParticlesReconstructableOverGen->LabelsOption("v");
//    hNParticlesReconstructed->LabelsOption("v");

    //Nreconstructable lambdas alternative definition: number of reconstructed track pairs coming from the same Lambda
    //Nreconstructable omegas alternative definition: number of reconstructed track-V0 pairs coming from the same Omega
    //TH2D *hNParticlesReconstructable2 = new TH2D("hNParticlesReconstructable2","; ;pt",2,0.,2.,nbinspt,minpt,maxpt);
    //hNParticlesReconstructable2->GetXaxis()->SetBinLabel(1,"lambda");
    //hNParticlesReconstructable2->GetXaxis()->SetBinLabel(2,"omega");
    vector<int> p_moth_pdg;
    vector<int> pi_moth_pdg;
    vector<int> k_moth_pdg;
    vector<float> p_moth_pt;
    vector<float> pi_moth_pt;
    vector<float> k_moth_pt;
    vector<float> p_rad;
    vector<float> pi_rad;
    vector<float> k_rad;


    //pt p vs pt lambda per ogni lambda generata
    //pt p vs pt lambda per ogni p ricostruibile
    //pt p vs pt lambda per ogni p ricostruito
    // pVsL, piVsL, kVsO, LVsO
    const int ncorr = 4;
    TString corr[ncorr] = {"pVsL", "piVsL", "kVsO", "LVsO"};
    TH2D *hPtDauVsPtMothGen[ncorr];
    TH2D *hPtDauVsPtMothReconstructable[ncorr];
    TH2D *hPtDauVsPtMothRec[ncorr];
    for(int g=0; g<ncorr; g++){
        hPtDauVsPtMothGen[g] = new TH2D(Form("hPtDauVsPtMothGen_%s",corr[g].Data()),"gen;pt moth;pt dau",nbinspt,minpt,maxpt,nbinspt,minpt,maxpt);
        hPtDauVsPtMothReconstructable[g] = new TH2D(Form("hPtDauVsPtMothReconstructable_%s",corr[g].Data()),"reconstructable;pt moth;pt dau",nbinspt,minpt,maxpt,nbinspt,minpt,maxpt);
        hPtDauVsPtMothRec[g] = new TH2D(Form("hPtDauVsPtMothRec_%s",corr[g].Data()),"rec;pt moth;pt dau",nbinspt,minpt,maxpt,nbinspt,minpt,maxpt);
    }

    const int nnotrecon = 4;
    TString partnotrecon[nnotrecon] = {"LbcOfp", "LbcOfpi", "ObcOfL", "ObcOfk"};
    TH1D *hPtDistribNotReconstructable[nnotrecon];
    for(int g=0; g<nnotrecon; g++){
        hPtDistribNotReconstructable[g] = new TH1D(Form("hPtNotReconstructable_%s",partnotrecon[g].Data()),"NotReconstructable;pt moth",nbinspt,minpt,maxpt);
    }

    //pt gen vs nrecosntructable hits
    const int ncorrhits = 6;
    TString partcorrnhits[ncorrhits] = {"p_from_l", "pi_from_l", "k_from_o", "pi_from_c", "pi_from_cc", "pi_from_ccc"};
    TH2D *hPtVsReconstructableHits[ncorrhits];
    TH2D *hPtVsRecoeHits[ncorrhits];
    TH2D *hNReconstructableHitsVsRecHits[ncorrhits];
    for(int g=0; g<ncorrhits; g++){
        hPtVsReconstructableHits[g] = new TH2D(Form("hPtVsReconstructableHits_%s",partcorrnhits[g].Data()),"gen tracks;pt;n reconstructable hits",nbinspt,minpt,maxpt,10,0,10);
        hPtVsRecoeHits[g] = new TH2D(Form("hPtVsRecoeHits_%s",partcorrnhits[g].Data()),"rec tracks;pt;n reco hits",nbinspt,minpt,maxpt,10,0,10);
        hNReconstructableHitsVsRecHits[g] = new TH2D(Form("hNReconstructableHitsVsRecHits_%s",partcorrnhits[g].Data()),"rec tracks;n reconstructable hits;n reco hits",10,0,10,10,0,10);
    }



    Float_t n_particles_gen[npar][nbinspt];
    Float_t n_particles_reconstructable[npar][nbinspt];
    Float_t n_particles_reconstructable2[npar][nbinspt];
    Float_t n_particles_reconstructed[npar][nbinspt];
    Float_t ratio_particles_reconstructable_over_gen[npar][nbinspt];
    Float_t ratio_particles_reconstructed_over_reconstructable[npar][nbinspt];
    Float_t ratio_particles_reconstructed_over_reconstructable2[npar][nbinspt];
    for(int ii=0; ii<npar; ii++){
        for(int jj=0; jj<nbinspt; jj++){
            n_particles_gen[ii][jj]=0;
            n_particles_reconstructable[ii][jj]=0;
            n_particles_reconstructable2[ii][jj]=0;
            ratio_particles_reconstructable_over_gen[ii][jj]=0;
            n_particles_reconstructed[ii][jj]=0;
            ratio_particles_reconstructed_over_reconstructable[ii][jj]=0;
            ratio_particles_reconstructed_over_reconstructable2[ii][jj]=0;
        }
    }
    Printf("HERE");
    int ngen=t.GetEntriesFast();
    for(int igen = 0; igen<ngen; igen++){
        t.GetEntry(igen);
        //Printf("%f %f %f %f %f %f %f %f %f %f %f",t.fTreeGen_p_Pt,t.fTreeGen_pi4_Pt,t.fTreeGen_k_Pt,t.fTreeGen_lambda_Pt,t.fTreeGen_omega_Pt,t.fTreeGen_pi3_Pt,t.fTreeGen_omegac_Pt,t.fTreeGen_pi2_Pt,t.fTreeGen_omegacc_Pt,t.fTreeGen_pi1_Pt,t.fTreeGen_omegaccc_Pt);
        //p_from_l
        hNParticlesGen->Fill(0.,t.fTreeGen_p_Pt); //Printf("pt proton %f N reco hits proton = %d",t.fTreeGen_p_Pt,t.fTreeGen_p_ReconstructableHits);
        if(t.fTreeGen_p_ReconstructableHits>=4) hNParticlesReconstructable->Fill(0.,t.fTreeGen_p_Pt);
        //pi_from_l
        hNParticlesGen->Fill(1.,t.fTreeGen_pi4_Pt);
        if(t.fTreeGen_pi4_ReconstructableHits>=4) hNParticlesReconstructable->Fill(1.,t.fTreeGen_pi4_Pt);
        //k_from_o
        hNParticlesGen->Fill(2.,t.fTreeGen_k_Pt);
        if(t.fTreeGen_k_ReconstructableHits>=4) hNParticlesReconstructable->Fill(2.,t.fTreeGen_k_Pt);
        //lambda
        hNParticlesGen->Fill(3.,t.fTreeGen_lambda_Pt);
        if(t.fTreeGen_pi4_ReconstructableHits>=4 && t.fTreeGen_p_ReconstructableHits>=4) hNParticlesReconstructable->Fill(3.,t.fTreeGen_lambda_Pt);
        //omega
        hNParticlesGen->Fill(4.,t.fTreeGen_omega_Pt);
        if(t.fTreeGen_pi4_ReconstructableHits>=4 && t.fTreeGen_p_ReconstructableHits>=4 && t.fTreeGen_k_ReconstructableHits>=4) hNParticlesReconstructable->Fill(4.,t.fTreeGen_omega_Pt);
        //pi_from_c
        hNParticlesGen->Fill(5.,t.fTreeGen_pi3_Pt);
        if(t.fTreeGen_pi3_ReconstructableHits>=4) hNParticlesReconstructable->Fill(5.,t.fTreeGen_pi3_Pt);
        //omegac
        hNParticlesGen->Fill(6.,t.fTreeGen_omegac_Pt);
        if(t.fTreeGen_pi3_ReconstructableHits>=4 && t.fTreeGen_pi4_ReconstructableHits>=4 && t.fTreeGen_p_ReconstructableHits>=4 && t.fTreeGen_k_ReconstructableHits>=4) hNParticlesReconstructable->Fill(6.,t.fTreeGen_omegac_Pt);
        //pi_from_cc
        hNParticlesGen->Fill(7.,t.fTreeGen_pi2_Pt);
        if(t.fTreeGen_pi2_ReconstructableHits>=4) hNParticlesReconstructable->Fill(7.,t.fTreeGen_pi2_Pt);
        //omegacc
        hNParticlesGen->Fill(8.,t.fTreeGen_omegacc_Pt);
        if(t.fTreeGen_pi2_ReconstructableHits>=4 && t.fTreeGen_pi3_ReconstructableHits>=4 && t.fTreeGen_pi4_ReconstructableHits>=4 && t.fTreeGen_p_ReconstructableHits>=4 && t.fTreeGen_k_ReconstructableHits>=4) hNParticlesReconstructable->Fill(8.,t.fTreeGen_omegacc_Pt);
        //pi_from_ccc
        hNParticlesGen->Fill(9.,t.fTreeGen_pi1_Pt);
        if(t.fTreeGen_pi1_ReconstructableHits>=4) hNParticlesReconstructable->Fill(9.,t.fTreeGen_pi1_Pt);
        //omegaccc
        hNParticlesGen->Fill(10.,t.fTreeGen_omegaccc_Pt);
        if(t.fTreeGen_pi1_ReconstructableHits>=4 && t.fTreeGen_pi2_ReconstructableHits>=4 && t.fTreeGen_pi3_ReconstructableHits>=4 && t.fTreeGen_pi4_ReconstructableHits>=4 && t.fTreeGen_p_ReconstructableHits>=4 && t.fTreeGen_k_ReconstructableHits>=4) hNParticlesReconstructable->Fill(10.,t.fTreeGen_omegaccc_Pt);

        //correlations
        hPtDauVsPtMothGen[0]->Fill(t.fTreeGen_lambda_Pt,t.fTreeGen_p_Pt);
        hPtDauVsPtMothGen[1]->Fill(t.fTreeGen_lambda_Pt,t.fTreeGen_pi4_Pt);
        hPtDauVsPtMothGen[2]->Fill(t.fTreeGen_omega_Pt,t.fTreeGen_k_Pt);
        hPtDauVsPtMothGen[3]->Fill(t.fTreeGen_omega_Pt,t.fTreeGen_lambda_Pt);
        if(t.fTreeGen_p_ReconstructableHits>=4 && t.fTreeGen_pi4_ReconstructableHits>=4)  hPtDauVsPtMothReconstructable[0]->Fill(t.fTreeGen_lambda_Pt,t.fTreeGen_p_Pt);
        if(t.fTreeGen_p_ReconstructableHits>=4 &&t.fTreeGen_pi4_ReconstructableHits>=4)hPtDauVsPtMothReconstructable[1]->Fill(t.fTreeGen_lambda_Pt,t.fTreeGen_pi4_Pt);
        if(t.fTreeGen_p_ReconstructableHits>=4 && t.fTreeGen_pi4_ReconstructableHits>=4 && t.fTreeGen_k_ReconstructableHits>=4)  hPtDauVsPtMothReconstructable[2]->Fill(t.fTreeGen_omega_Pt,t.fTreeGen_k_Pt);
        if(t.fTreeGen_p_ReconstructableHits>=4 && t.fTreeGen_pi4_ReconstructableHits>=4 && t.fTreeGen_k_ReconstructableHits>=4)hPtDauVsPtMothReconstructable[3]->Fill(t.fTreeGen_omega_Pt,t.fTreeGen_lambda_Pt);

        //not reconstructable
        if(t.fTreeGen_p_ReconstructableHits<4)  hPtDistribNotReconstructable[0]->Fill(t.fTreeGen_lambda_Pt);
        if(t.fTreeGen_pi4_ReconstructableHits<4)hPtDistribNotReconstructable[1]->Fill(t.fTreeGen_lambda_Pt);
        if(t.fTreeGen_k_ReconstructableHits<4)  hPtDistribNotReconstructable[2]->Fill(t.fTreeGen_omega_Pt);
        if(t.fTreeGen_p_ReconstructableHits<4 && t.fTreeGen_pi4_ReconstructableHits<4)hPtDistribNotReconstructable[3]->Fill(t.fTreeGen_omega_Pt);
        //Printf("HERE 4 but LAST %d %d %d %d",igen,t.fTreeGen_p_ReconstructableHits,t.fTreeGen_pi4_ReconstructableHits,t.fTreeGen_k_ReconstructableHits);
        //correlations vs hits
        hPtVsReconstructableHits[0]->Fill(t.fTreeGen_p_Pt,  t.fTreeGen_p_ReconstructableHits);
        hPtVsReconstructableHits[1]->Fill(t.fTreeGen_pi4_Pt,t.fTreeGen_pi4_ReconstructableHits);
        hPtVsReconstructableHits[2]->Fill(t.fTreeGen_k_Pt,  t.fTreeGen_k_ReconstructableHits);
        hPtVsReconstructableHits[3]->Fill(t.fTreeGen_pi3_Pt,t.fTreeGen_pi3_ReconstructableHits);
        hPtVsReconstructableHits[4]->Fill(t.fTreeGen_pi2_Pt,t.fTreeGen_pi2_ReconstructableHits);
        hPtVsReconstructableHits[5]->Fill(t.fTreeGen_pi1_Pt,t.fTreeGen_pi1_ReconstructableHits);
    }
    Printf("HERE 3 but LAST");
    int nrec=t_rec.GetEntriesFast();
    for(int irec = 0; irec<nrec; irec++){
        t_rec.GetEntry(irec);
        //proton from L + acceptance
        if(TMath::Abs(t_rec.fReco_pdg)==2212 && TMath::Abs(t_rec.fReco_pdgMother)==3122){
            hNParticlesReconstructed->Fill(0.,t_rec.fGen_pt);
            hPtVsRecoeHits[0]->Fill(t_rec.fGen_pt,t_rec.fReco_nhits);
            hNReconstructableHitsVsRecHits[0]->Fill(t_rec.fReco_nReconstructableHits,t_rec.fReco_nhits);
            p_moth_pdg.push_back(t_rec.fReco_pdgMother);
            p_moth_pt.push_back(t_rec.fGen_ptMother);
            p_rad.push_back(t_rec.fGen_rxy);
        }
        if(TMath::Abs(t_rec.fReco_pdg)==211 && TMath::Abs(t_rec.fReco_pdgMother)==3122){
            hNParticlesReconstructed->Fill(1.,t_rec.fGen_pt);
            hPtVsRecoeHits[1]->Fill(t_rec.fGen_pt,t_rec.fReco_nhits);
            hNReconstructableHitsVsRecHits[1]->Fill(t_rec.fReco_nReconstructableHits,t_rec.fReco_nhits);
            pi_moth_pdg.push_back(t_rec.fReco_pdgMother);
            pi_moth_pt.push_back(t_rec.fGen_ptMother);
            pi_rad.push_back(t_rec.fGen_rxy);
        }
        //kaon from O + acceptance
        if(TMath::Abs(t_rec.fReco_pdg)==321 && TMath::Abs(t_rec.fReco_pdgMother)==3334){
            hNParticlesReconstructed->Fill(2.,t_rec.fGen_pt);
            hPtVsRecoeHits[2]->Fill(t_rec.fGen_pt,t_rec.fReco_nhits);
            hNReconstructableHitsVsRecHits[2]->Fill(t_rec.fReco_nReconstructableHits,t_rec.fReco_nhits);
            k_moth_pdg.push_back(t_rec.fReco_pdgMother);
            k_moth_pt.push_back(t_rec.fGen_ptMother);
            k_rad.push_back(t_rec.fGen_rxy);
        }
        //pion from Omegac
        if(TMath::Abs(t_rec.fReco_pdg)==211 && TMath::Abs(t_rec.fReco_pdgMother)==4332){
            hNParticlesReconstructed->Fill(5.,t_rec.fGen_pt);
            hPtVsRecoeHits[3]->Fill(t_rec.fGen_pt,t_rec.fReco_nhits);
            hNReconstructableHitsVsRecHits[3]->Fill(t_rec.fReco_nReconstructableHits,t_rec.fReco_nhits);
        }
        //pion from Omegacc
        if(TMath::Abs(t_rec.fReco_pdg)==211 && TMath::Abs(t_rec.fReco_pdgMother)==4432){
            hNParticlesReconstructed->Fill(7.,t_rec.fGen_pt);
            hPtVsRecoeHits[4]->Fill(t_rec.fGen_pt,t_rec.fReco_nhits);
            hNReconstructableHitsVsRecHits[4]->Fill(t_rec.fReco_nReconstructableHits,t_rec.fReco_nhits);
        }
        //pion from Omegaccc
        if(TMath::Abs(t_rec.fReco_pdg)==211 && TMath::Abs(t_rec.fReco_pdgMother)==4444){
            hNParticlesReconstructed->Fill(9.,t_rec.fGen_pt);
            hPtVsRecoeHits[5]->Fill(t_rec.fGen_pt,t_rec.fReco_nhits);
            hNReconstructableHitsVsRecHits[5]->Fill(t_rec.fReco_nReconstructableHits,t_rec.fReco_nhits);
        }

    }
    int npireco=pi_moth_pdg.size();
    int npreco =p_moth_pdg.size();
    Printf("nreco pi =%d nreco p = %d",npireco,npreco);
    for(int ip=0; ip<npreco; ip++){
        int pdg_moth_prot = p_moth_pdg[ip];
        float pt_moth_prot = p_moth_pt[ip];
        float rxy_prot = p_rad[ip];
        for(int ipi=0; ipi<npireco; ipi++){
            int pdg_moth_pion = pi_moth_pdg[ipi];
            float pt_moth_pion = pi_moth_pt[ipi];
            float rxy_pion = pi_rad[ipi];
            if(pdg_moth_prot==pdg_moth_pion && pt_moth_prot==pt_moth_pion && rxy_prot==rxy_pion){
                //Printf("index_prot=%d pdg_moth_prot=%d pt_moth_prot=%f r_xy_prot=%f | index_pion=%d pdg_moth_pion=%d pt_moth_pion=%f r_xy_pi=%f",ip,pdg_moth_prot,pt_moth_prot,rxy_prot,ipi,pdg_moth_pion,pt_moth_pion,rxy_pion);
                hNParticlesReconstructable2->Fill(3.,pt_moth_pion);
            }
        }
    }

    Printf("HERE 2 but LAST");
    int nrecv0=t_rec_v0.GetEntriesFast();
    for(int irecv0 = 0; irecv0<nrecv0; irecv0++){
        t_rec_v0.GetEntry(irecv0);
        hNParticlesReconstructed->Fill(3.,t_rec_v0.fTreeGen_lambda_Pt);
        //correlations
        if(TMath::Abs(t_rec_v0.fTreeGen_p_Pdg)==2212)hPtDauVsPtMothRec[0]->Fill(t_rec_v0.fTreeGen_lambda_Pt,t_rec_v0.fTreeGen_p_Pt);
        if(TMath::Abs(t_rec_v0.fTreeGen_pi4_Pdg)==2212)hPtDauVsPtMothRec[0]->Fill(t_rec_v0.fTreeGen_lambda_Pt,t_rec_v0.fTreeGen_pi4_Pt);
        if(TMath::Abs(t_rec_v0.fTreeGen_pi4_Pdg)==211)hPtDauVsPtMothRec[1]->Fill(t_rec_v0.fTreeGen_lambda_Pt,t_rec_v0.fTreeGen_pi4_Pt);
        if(TMath::Abs(t_rec_v0.fTreeGen_p_Pdg)==211)hPtDauVsPtMothRec[1]->Fill(t_rec_v0.fTreeGen_lambda_Pt,t_rec_v0.fTreeGen_p_Pt);
    }
    int nreccasc=t_rec_casc.GetEntriesFast();
    for(int ireccasc = 0; ireccasc<nreccasc; ireccasc++){
        t_rec_casc.GetEntry(ireccasc);
        hNParticlesReconstructed->Fill(4.,t_rec_casc.fTreeGen_omega_Pt);
        //correlations
        if(TMath::Abs(t_rec_casc.fTreeGen_k_Pdg)==321)hPtDauVsPtMothRec[2]->Fill(t_rec_casc.fTreeGen_omega_Pt,t_rec_casc.fTreeGen_k_Pt);
        if(TMath::Abs(t_rec_casc.fTreeGen_lambda_Pdg)==3122)hPtDauVsPtMothRec[3]->Fill(t_rec_casc.fTreeGen_omega_Pt,t_rec_casc.fTreeGen_lambda_Pt);
    }
    //reco Omegaccc
    int nrecomegaccc=t_rec_omegaccc.GetEntriesFast();
    for(int irecomegaccc = 0; irecomegaccc<nrecomegaccc; irecomegaccc++){
        t_rec_omegaccc.GetEntry(irecomegaccc);
        if(t_rec_omegaccc.fIsSignal_omegaccc==true)
            hNParticlesReconstructed->Fill(10.,t_rec_omegaccc.fGenPt_omegaccc);
    }
    //reco Omegacc
    int nrecomegacc=t_rec_omegacc.GetEntriesFast();
    for(int irecomegacc = 0; irecomegacc<nrecomegacc; irecomegacc++){
        t_rec_omegacc.GetEntry(irecomegacc);
        if(t_rec_omegacc.fIsSignal_omegacc==true)
            hNParticlesReconstructed->Fill(8.,t_rec_omegacc.fGenPt_omegacc);
    }
    //reco Omegac
    int nrecomegac=t_rec_omegac.GetEntriesFast();
    for(int irecomegac = 0; irecomegac<nrecomegac; irecomegac++){
        t_rec_omegac.GetEntry(irecomegac);
        if(t_rec_omegac.fIsSignal_omegac==true)
            hNParticlesReconstructed->Fill(6.,t_rec_omegac.fGenPt_omegac);
    }

    Printf("HERE one but LAST");
    for(int ii=0; ii<npar; ii++){
        for(int jj=0; jj<nbinspt; jj++){
            n_particles_gen[ii][jj]=hNParticlesGen->GetBinContent(ii+1,jj+1);
            n_particles_reconstructable[ii][jj]=hNParticlesReconstructable->GetBinContent(ii+1,jj+1);
            if(ii==3)n_particles_reconstructable2[ii][jj]=hNParticlesReconstructable2->GetBinContent(ii+1,jj+1);
            n_particles_reconstructed[ii][jj]=hNParticlesReconstructed->GetBinContent(ii+1,jj+1);
            if(n_particles_gen[ii][jj]>0.){
                ratio_particles_reconstructable_over_gen[ii][jj]=n_particles_reconstructable[ii][jj]/n_particles_gen[ii][jj];
            }
            if(n_particles_reconstructable[ii][jj]>0.){
                ratio_particles_reconstructed_over_reconstructable[ii][jj]=n_particles_reconstructed[ii][jj]/n_particles_reconstructable[ii][jj];
            }
            if(n_particles_reconstructable2[ii][jj]>0.){
                ratio_particles_reconstructed_over_reconstructable2[ii][jj]=n_particles_reconstructed[ii][jj]/n_particles_reconstructable2[ii][jj];
            }
            hNParticlesReconstructableOverGen->SetBinContent(ii+1,jj+1,ratio_particles_reconstructable_over_gen[ii][jj]);
            hNParticlesReconstructedOverReconstructable->SetBinContent(ii+1,jj+1,ratio_particles_reconstructed_over_reconstructable[ii][jj]);
            hNParticlesReconstructedOverReconstructable2->SetBinContent(ii+1,jj+1,ratio_particles_reconstructed_over_reconstructable2[ii][jj]);
        }
        hNPartGen[ii]=(TH1D*)hNParticlesGen->ProjectionY(Form("hGen_%s",particles[ii].Data()),ii+1,ii+1);
        hNPartReconstructable[ii]=(TH1D*)hNParticlesReconstructable->ProjectionY(Form("hReconstructable_%s",particles[ii].Data()),ii+1,ii+1);
        hNPartReconstructable2[ii]=(TH1D*)hNParticlesReconstructable2->ProjectionY(Form("hReconstructable2_%s",particles[ii].Data()),ii+1,ii+1);
        hNPartRec[ii]=(TH1D*)hNParticlesReconstructed->ProjectionY(Form("hRec_%s",particles[ii].Data()),ii+1,ii+1);
        hNPartReconstructableOverGen[ii]=(TH1D*)hNParticlesReconstructableOverGen->ProjectionY(Form("hReconstructableOverGen_%s",particles[ii].Data()),ii+1,ii+1);
        hNPartReconstructedOverRec[ii]=(TH1D*)hNParticlesReconstructedOverReconstructable->ProjectionY(Form("hRecOverReconstructable_%s",particles[ii].Data()),ii+1,ii+1);
        hNPartReconstructedOverRec2[ii]=(TH1D*)hNParticlesReconstructedOverReconstructable2->ProjectionY(Form("hRecOverReconstructable2_%s",particles[ii].Data()),ii+1,ii+1);
        TCanvas *c=new TCanvas(Form("%s",particles[ii].Data()),Form("%s",particles[ii].Data()),0,45,2560,1395);
        c->Divide(4,2);
        c->cd(1);
        hNPartGen[ii]->Draw();
        c->cd(2);
        hNPartReconstructable[ii]->Draw();
        c->cd(3);
        hNPartRec[ii]->Draw();
        if(ii==3){
            c->cd(4);
            hNPartReconstructable2[ii]->Draw();
        }
        c->cd(5);
        hNPartReconstructableOverGen[ii]->Draw();
        c->cd(6);
        hNPartReconstructedOverRec[ii]->Draw();
        if(ii==3){
            c->cd(7);
            hNPartReconstructedOverRec2[ii]->Draw();
        }
        c->SaveAs(Form("summary_%s.png",c->GetName()),"RECREATE");

    }
    TCanvas *c_gen=new TCanvas("c_gen","c_gen",900,800);
    c_gen->SetTicks();
    c_gen->SetGrid();
    hNParticlesGen->Draw("colz");
    hNParticlesGen->Draw("sametext");
    c_gen->SaveAs(Form("%s.png",c_gen->GetName()),"RECREATE");
    TCanvas *c_reconstructable=new TCanvas("c_reconstructable","c_reconstructable",900,800);
    c_reconstructable->SetTicks();
    c_reconstructable->SetGrid();
    hNParticlesReconstructable->Draw("colz");
    hNParticlesReconstructable->Draw("sametext");
    c_reconstructable->SaveAs(Form("%s.png",c_reconstructable->GetName()),"RECREATE");
    TCanvas *c_reconstructable2=new TCanvas("c_reconstructable2","c_reconstructable2",900,800);
    c_reconstructable2->SetTicks();
    c_reconstructable2->SetGrid();
    hNParticlesReconstructable2->Draw("colz");
    hNParticlesReconstructable2->Draw("sametext");
    c_reconstructable2->SaveAs(Form("%s.png",c_reconstructable2->GetName()),"RECREATE");
    TCanvas *c_reconstructed=new TCanvas("c_reconstructed","c_reconstructed",900,800);
    c_reconstructed->SetTicks();
    c_reconstructed->SetGrid();
    hNParticlesReconstructed->Draw("colz");
    hNParticlesReconstructed->Draw("sametext");
    c_reconstructed->SaveAs(Form("%s.png",c_reconstructed->GetName()),"RECREATE");
    TCanvas *c_reconstructable_over_gen=new TCanvas("c_reconstructable_over_gen","c_reconstructable_over_gen",900,800);
    c_reconstructable_over_gen->SetTicks();
    c_reconstructable_over_gen->SetGrid();
    hNParticlesReconstructableOverGen->Draw("colz");
    hNParticlesReconstructableOverGen->Draw("sametext");
    c_reconstructable_over_gen->SaveAs(Form("%s.png",c_reconstructable_over_gen->GetName()),"RECREATE");
    TCanvas *c_reconstructed_over_reconstructable=new TCanvas("c_reconstructed_over_reconstructable","c_reconstructed_over_reconstructable",900,800);
    c_reconstructed_over_reconstructable->SetTicks();
    c_reconstructed_over_reconstructable->SetGrid();
    hNParticlesReconstructedOverReconstructable->Draw("colz");
    hNParticlesReconstructedOverReconstructable->Draw("sametext");
    c_reconstructed_over_reconstructable->SaveAs(Form("%s.png",c_reconstructed_over_reconstructable->GetName()),"RECREATE");
    TCanvas *c_reconstructed_over_reconstructable2=new TCanvas("c_reconstructed_over_reconstructable2","c_reconstructed_over_reconstructable2",900,800);
    c_reconstructed_over_reconstructable2->SetTicks();
    c_reconstructed_over_reconstructable2->SetGrid();
    hNParticlesReconstructedOverReconstructable2->Draw("colz");
    hNParticlesReconstructedOverReconstructable2->Draw("sametext");
    c_reconstructed_over_reconstructable2->SaveAs(Form("%s.png",c_reconstructed_over_reconstructable2->GetName()),"RECREATE");

    Printf("HERE LAST");


    for(int t=0; t<ncorr; t++){
        TCanvas *c=new TCanvas(Form("c_corr_%s",corr[t].Data()),Form("c_corr_%s",corr[t].Data()),0,45,2560,1395);
        c->Divide(3,1);
        c->cd(1);
        hPtDauVsPtMothGen[t]->Draw("colz");
        //hPtDauVsPtMothGen[t]->Draw("sametext");
        c->cd(2);
        hPtDauVsPtMothReconstructable[t]->Draw("colz");
        //hPtDauVsPtMothReconstructable[t]->Draw("sametext");
        c->cd(3);
        hPtDauVsPtMothRec[t]->Draw("colz");
        //hPtDauVsPtMothRec[t]->Draw("sametext");
        c->SaveAs(Form("%s.png",c->GetName()),"RECREATE");
    }


    for(int t=0; t<nnotrecon; t++){
        TCanvas *c=new TCanvas(Form("c_not_reconstructable_%s",partnotrecon[t].Data()),Form("c_not_reconstructable_%s",partnotrecon[t].Data()),1200,800);
        hPtDistribNotReconstructable[t]->Draw();
        c->SaveAs(Form("%s.png",c->GetName()),"RECREATE");
    }

    //pt gen vs nrecosntructable hits
    for(int t=0; t<ncorrhits; t++){
        TCanvas *c=new TCanvas(Form("c_hits_correlation%s",partcorrnhits[t].Data()),Form("c_hits_correlation%s",partcorrnhits[t].Data()),0,45,2560,1395);
        c->Divide(3,1);
        c->cd(1);
        hPtVsReconstructableHits[t]->Draw("colz");
        c->cd(2);
        hPtVsRecoeHits[t]->Draw("colz");
        c->cd(3);
        hNReconstructableHitsVsRecHits[t]->Draw("colz");
        c->SaveAs(Form("%s.png",c->GetName()),"RECREATE");
    }


    //per ogni lambda generata plot pt p reconstructable vs pt L gen
    //per ogni lambda generata plot pt pi reconstructable vs pt L gen

    //per ogni lambda generata plot pt p gen vs pt pi gen
    //per ogni lambda reco plot pt p reconstructable vs pt pi reconstructable



}
///___________________________
void DrawReconstructionPlots(TreeReconstruction &t){

    const int nbinspt = 50;
    float minpt=0.;
    float maxpt=10.;
    const int npart = 6;
    TString part[npart] = {"p_from_l", "pi_from_l", "k_from_o", "pi_from_c", "pi_from_cc", "pi_from_ccc"};
    TString reco[2]     = {"reco", "not_reco"};
    TH2D *hPtVsRxy[2][npart];
    TH2D *hPtVsZ[2][npart];
    TH2D *hPtVsEta[2][npart];
    TH2D *hPtVsRap[2][npart];
    TH2D *hPtVsPhi[2][npart];
    TH2D *hPtVsReconstructableHits[2][npart];
    for(int i=0; i<2; i++){
        for(int g=0; g<npart; g++){
            TString name = Form("_%s_%s",reco[i].Data(),part[g].Data());

            hPtVsRxy[i][g]                 = new TH2D(Form("ptVsRxy_%s",name.Data()),Form("%s %s;pt (GeV/c);r_xy (cm)",part[g].Data(),reco[i].Data()),nbinspt,minpt,maxpt,10000,0.,100.);
            hPtVsZ[i][g]                   = new TH2D(Form("ptVsZ_%s",name.Data()),Form("%s %s;pt (GeV/c);z (cm)",part[g].Data(),reco[i].Data()),nbinspt,minpt,maxpt,500,0.,50.);
            hPtVsEta[i][g]                 = new TH2D(Form("ptVsEta_%s",name.Data()),Form("%s %s;pt (GeV/c);eta (cm)",part[g].Data(),reco[i].Data()),nbinspt,minpt,maxpt,300,-3.,3.);
            hPtVsRap[i][g]                 = new TH2D(Form("ptVsRap_%s",name.Data()),Form("%s %s;pt (GeV/c);rap (cm)",part[g].Data(),reco[i].Data()),nbinspt,minpt,maxpt,300,-3.,3.);
            hPtVsPhi[i][g]                 = new TH2D(Form("ptVsPhi_%s",name.Data()),Form("%s %s;pt (GeV/c);phi (cm)",part[g].Data(),reco[i].Data()),nbinspt,minpt,maxpt,100,0.,2.*TMath::Pi());
            hPtVsReconstructableHits[i][g] = new TH2D(Form("ptVsNhits_%s",name.Data()),Form("%s %s;pt (GeV/c);n reconstructable hits (cm)",part[g].Data(),reco[i].Data()),nbinspt,minpt,maxpt,10,0.,10.);
        }
    }
    int n=t.GetEntriesFast();
    for(int i = 0; i<n; i++){
        t.GetEntry(i);
        bool isrec = t.fParticle_isReco;
        int j=0;
        if(isrec) j=0;
        else j=1;
        //proton from L + acceptance
        if(TMath::Abs(t.fParticle_pdg)==2212 && TMath::Abs(t.fParticle_pdgMoth)==3122){
            hPtVsRxy[j][0]->Fill(t.fParticle_pt,t.fParticle_rxy);
            hPtVsZ[j][0]->Fill(t.fParticle_pt,t.fParticle_z);
            hPtVsEta[j][0]->Fill(t.fParticle_pt,t.fParticle_eta);
            hPtVsRap[j][0]->Fill(t.fParticle_pt,t.fParticle_rap);
            hPtVsPhi[j][0]->Fill(t.fParticle_pt,t.fParticle_phi);
            hPtVsReconstructableHits[j][0]->Fill(t.fParticle_pt,t.fParticle_NhitsAss);
        }
        if(TMath::Abs(t.fParticle_pdg)==211 && TMath::Abs(t.fParticle_pdgMoth)==3122){
            hPtVsRxy[j][1]->Fill(t.fParticle_pt,t.fParticle_rxy);
            hPtVsZ[j][1]->Fill(t.fParticle_pt,t.fParticle_z);
            hPtVsEta[j][1]->Fill(t.fParticle_pt,t.fParticle_eta);
            hPtVsRap[j][1]->Fill(t.fParticle_pt,t.fParticle_rap);
            hPtVsPhi[j][1]->Fill(t.fParticle_pt,t.fParticle_phi);
            hPtVsReconstructableHits[j][1]->Fill(t.fParticle_pt,t.fParticle_NhitsAss);
        }
        //kaon from O
        if(TMath::Abs(t.fParticle_pdg)==321 && TMath::Abs(t.fParticle_pdgMoth)==3334){
            hPtVsRxy[j][2]->Fill(t.fParticle_pt,t.fParticle_rxy);
            hPtVsZ[j][2]->Fill(t.fParticle_pt,t.fParticle_z);
            hPtVsEta[j][2]->Fill(t.fParticle_pt,t.fParticle_eta);
            hPtVsRap[j][2]->Fill(t.fParticle_pt,t.fParticle_rap);
            hPtVsPhi[j][2]->Fill(t.fParticle_pt,t.fParticle_phi);
            hPtVsReconstructableHits[j][2]->Fill(t.fParticle_pt,t.fParticle_NhitsAss);
        }
        //pion from Omegac
        if(TMath::Abs(t.fParticle_pdg)==211 && TMath::Abs(t.fParticle_pdgMoth)==4332){
            hPtVsRxy[j][3]->Fill(t.fParticle_pt,t.fParticle_rxy);
            hPtVsZ[j][3]->Fill(t.fParticle_pt,t.fParticle_z);
            hPtVsEta[j][3]->Fill(t.fParticle_pt,t.fParticle_eta);
            hPtVsRap[j][3]->Fill(t.fParticle_pt,t.fParticle_rap);
            hPtVsPhi[j][3]->Fill(t.fParticle_pt,t.fParticle_phi);
            hPtVsReconstructableHits[j][3]->Fill(t.fParticle_pt,t.fParticle_NhitsAss);
        }
        //pion from Omegacc
        if(TMath::Abs(t.fParticle_pdg)==211 && TMath::Abs(t.fParticle_pdgMoth)==4432){
            hPtVsRxy[j][4]->Fill(t.fParticle_pt,t.fParticle_rxy);
            hPtVsZ[j][4]->Fill(t.fParticle_pt,t.fParticle_z);
            hPtVsEta[j][4]->Fill(t.fParticle_pt,t.fParticle_eta);
            hPtVsRap[j][4]->Fill(t.fParticle_pt,t.fParticle_rap);
            hPtVsPhi[j][4]->Fill(t.fParticle_pt,t.fParticle_phi);
            hPtVsReconstructableHits[j][4]->Fill(t.fParticle_pt,t.fParticle_NhitsAss);
        }
        //pion from Omegaccc
        if(TMath::Abs(t.fParticle_pdg)==211 && TMath::Abs(t.fParticle_pdgMoth)==4444){
            hPtVsRxy[j][5]->Fill(t.fParticle_pt,t.fParticle_rxy);
            hPtVsZ[j][5]->Fill(t.fParticle_pt,t.fParticle_z);
            hPtVsEta[j][5]->Fill(t.fParticle_pt,t.fParticle_eta);
            hPtVsRap[j][5]->Fill(t.fParticle_pt,t.fParticle_rap);
            hPtVsPhi[j][5]->Fill(t.fParticle_pt,t.fParticle_phi);
            hPtVsReconstructableHits[j][5]->Fill(t.fParticle_pt,t.fParticle_NhitsAss);
        }

    }
    for(int i=0; i<npart; i++){
        TCanvas *c_rxy= new TCanvas(Form("c_PtVsRxy_%s",part[i].Data()),Form("c_PtVsRxy_%s",part[i].Data()),0,45,2560,1395);
        c_rxy->Divide(2,1);
        TCanvas *c_z= new TCanvas(Form("c_PtVsZ_%s",part[i].Data()),Form("c_PtVsZ_%s",part[i].Data()),0,45,2560,1395);
        c_z->Divide(2,1);
        TCanvas *c_eta= new TCanvas(Form("c_PtVsEta_%s",part[i].Data()),Form("c_PtVsEta_%s",part[i].Data()),0,45,2560,1395);
        c_eta->Divide(2,1);
        TCanvas *c_rap= new TCanvas(Form("c_PtVsRap_%s",part[i].Data()),Form("c_PtVsRap_%s",part[i].Data()),0,45,2560,1395);
        c_rap->Divide(2,1);
        TCanvas *c_phi= new TCanvas(Form("c_PtVsPhi_%s",part[i].Data()),Form("c_PtVsPhi_%s",part[i].Data()),0,45,2560,1395);
        c_phi->Divide(2,1);
        TCanvas *c_nreconstructable= new TCanvas(Form("c_PtVsNreconstructable_%s",part[i].Data()),Form("c_PtVsNreconstructable_%s",part[i].Data()),0,45,2560,1395);
        c_nreconstructable->Divide(2,1);
        for(int o=0; o<2; o++){
            c_rxy->cd(o+1);
            hPtVsRxy[o][i]->Draw("colz");
            c_z->cd(o+1);
            hPtVsZ[o][i]->Draw("colz");
            c_eta->cd(o+1);
            hPtVsEta[o][i]->Draw("colz");
            c_rap->cd(o+1);
            hPtVsRap[o][i]->Draw("colz");
            c_phi->cd(o+1);
            hPtVsPhi[o][i]->Draw("colz");
            c_nreconstructable->cd(o+1);
            hPtVsReconstructableHits[o][i]->Draw("colz");
        }
        c_rxy->SaveAs(Form("reconotreco_%s.png",c_rxy->GetName()),"RECREATE");
        c_z->SaveAs(Form("reconotreco_%s.png",c_z->GetName()),"RECREATE");
        c_eta->SaveAs(Form("reconotreco_%s.png",c_eta->GetName()),"RECREATE");
        c_rap->SaveAs(Form("reconotreco_%s.png",c_rap->GetName()),"RECREATE");
        c_phi->SaveAs(Form("reconotreco_%s.png",c_phi->GetName()),"RECREATE");
        c_nreconstructable->SaveAs(Form("reconotreco_%s.png",c_nreconstructable->GetName()),"RECREATE");
    }


}
