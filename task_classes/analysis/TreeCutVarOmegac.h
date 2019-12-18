//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jun 27 12:04:24 2019 by ROOT version 6.16/00
// from TTree TreeCutVarOmegac/TreeCutVarOmegac
// found on file: signal/AnalysisResults.root
//////////////////////////////////////////////////////////

#ifndef TreeCutVarOmegac_h
#define TreeCutVarOmegac_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class TreeCutVarOmegac {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         fPt_V0neg;
   Float_t         fEta_V0neg;
   Float_t         fPhi_V0neg;
   Float_t         fRap_V0neg;
   Float_t         fGenPt_V0neg;
   Float_t         fGenEta_V0neg;
   Float_t         fGenPhi_V0neg;
   Float_t         fGenRap_V0neg;
   Float_t         fGenRxy_V0neg;
   Float_t         fPt_V0pos;
   Float_t         fEta_V0pos;
   Float_t         fPhi_V0pos;
   Float_t         fRap_V0pos;
   Float_t         fGenPt_V0pos;
   Float_t         fGenEta_V0pos;
   Float_t         fGenPhi_V0pos;
   Float_t         fGenRap_V0pos;
   Float_t         fGenRxy_V0pos;
   Float_t         fPtV0;
   Float_t         fEtaV0;
   Float_t         fPhiV0;
   Float_t         fRapV0;
   Float_t         fGenPtV0;
   Float_t         fGenEtaV0;
   Float_t         fGenPhiV0;
   Float_t         fGenRapV0;
   Float_t         fGenRxyV0;
   Float_t         fPt_CascBach;
   Float_t         fEta_CascBach;
   Float_t         fPhi_CascBach;
   Float_t         fRap_CascBach;
   Float_t         fGenPt_CascBach;
   Float_t         fGenEta_CascBach;
   Float_t         fGenPhi_CascBach;
   Float_t         fGenRap_CascBach;
   Float_t         fGenRxy_CascBach;
   Float_t         fPtomega;
   Float_t         fEtaomega;
   Float_t         fPhiomega;
   Float_t         fRapomega;
   Float_t         fGenPtomega;
   Float_t         fGenEtaomega;
   Float_t         fGenPhiomega;
   Float_t         fGenRapomega;
   Float_t         fGenRxyomega;
   Float_t         fPt_pi3;
   Float_t         fEta_pi3;
   Float_t         fPhi_pi3;
   Float_t         fRap_pi3;
   Float_t         fGenPt_pi3;
   Float_t         fGenEta_pi3;
   Float_t         fGenPhi_pi3;
   Float_t         fGenRap_pi3;
   Float_t         fGenRxy_pi3;
   Float_t         fPt_omegac;
   Float_t         fEta_omegac;
   Float_t         fPhi_omegac;
   Float_t         fRap_omegac;
   Float_t         fGenPt_omegac;
   Float_t         fGenEta_omegac;
   Float_t         fGenPhi_omegac;
   Float_t         fGenRap_omegac;
   Float_t         fGenRxy_omegac;
   Float_t         fChi2ndf_omegac;
   Float_t         fCosPA_omegac;
   Float_t         fCosPAXY_omegac;
   Float_t         fDecayLength_omegac;
   Float_t         fDecayLengthXY_omegac;
   Float_t         fInvMass_omegac;
   Float_t         fImpParRPhi_omegac;
   Float_t         fImpParZ_omegac;
   Bool_t          fIsSignal_omegac;
   Float_t         fImpParRPhi_pi3;
   Float_t         fImpParZ_pi3;

   // List of branches
   TBranch        *b_fPt_V0neg;   //!
   TBranch        *b_fEta_V0neg;   //!
   TBranch        *b_fPhi_V0neg;   //!
   TBranch        *b_fRap_V0neg;   //!
   TBranch        *b_fGenPt_V0neg;   //!
   TBranch        *b_fGenEta_V0neg;   //!
   TBranch        *b_fGenPhi_V0neg;   //!
   TBranch        *b_fGenRap_V0neg;   //!
   TBranch        *b_fGenRxy_V0neg;   //!
   TBranch        *b_fPt_V0pos;   //!
   TBranch        *b_fEta_V0pos;   //!
   TBranch        *b_fPhi_V0pos;   //!
   TBranch        *b_fRap_V0pos;   //!
   TBranch        *b_fGenPt_V0pos;   //!
   TBranch        *b_fGenEta_V0pos;   //!
   TBranch        *b_fGenPhi_V0pos;   //!
   TBranch        *b_fGenRap_V0pos;   //!
   TBranch        *b_fGenRxy_V0pos;   //!
   TBranch        *b_fPtV0;   //!
   TBranch        *b_fEtaV0;   //!
   TBranch        *b_fPhiV0;   //!
   TBranch        *b_fRapV0;   //!
   TBranch        *b_fGenPtV0;   //!
   TBranch        *b_fGenEtaV0;   //!
   TBranch        *b_fGenPhiV0;   //!
   TBranch        *b_fGenRapV0;   //!
   TBranch        *b_fGenRxyV0;   //!
   TBranch        *b_fPt_CascBach;   //!
   TBranch        *b_fEta_CascBach;   //!
   TBranch        *b_fPhi_CascBach;   //!
   TBranch        *b_fRap_CascBach;   //!
   TBranch        *b_fGenPt_CascBach;   //!
   TBranch        *b_fGenEta_CascBach;   //!
   TBranch        *b_fGenPhi_CascBach;   //!
   TBranch        *b_fGenRap_CascBach;   //!
   TBranch        *b_fGenRxy_CascBach;   //!
   TBranch        *b_fPtomega;   //!
   TBranch        *b_fEtaomega;   //!
   TBranch        *b_fPhiomega;   //!
   TBranch        *b_fRapomega;   //!
   TBranch        *b_fGenPtomega;   //!
   TBranch        *b_fGenEtaomega;   //!
   TBranch        *b_fGenPhiomega;   //!
   TBranch        *b_fGenRapomega;   //!
   TBranch        *b_fGenRxyomega;   //!
   TBranch        *b_fPt_pi3;   //!
   TBranch        *b_fEta_pi3;   //!
   TBranch        *b_fPhi_pi3;   //!
   TBranch        *b_fRap_pi3;   //!
   TBranch        *b_fGenPt_pi3;   //!
   TBranch        *b_fGenEta_pi3;   //!
   TBranch        *b_fGenPhi_pi3;   //!
   TBranch        *b_fGenRap_pi3;   //!
   TBranch        *b_fGenRxy_pi3;   //!
   TBranch        *b_fPt_omegac;   //!
   TBranch        *b_fEta_omegac;   //!
   TBranch        *b_fPhi_omegac;   //!
   TBranch        *b_fRap_omegac;   //!
   TBranch        *b_fGenPt_omegac;   //!
   TBranch        *b_fGenEta_omegac;   //!
   TBranch        *b_fGenPhi_omegac;   //!
   TBranch        *b_fGenRap_omegac;   //!
   TBranch        *b_fGenRxy_omegac;   //!
   TBranch        *b_fChi2ndf_omegac;   //!
   TBranch        *b_fCosPA_omegac;   //!
   TBranch        *b_fCosPAXY_omegac;   //!
   TBranch        *b_fDecayLength_omegac;   //!
   TBranch        *b_fDecayLengthXY_omegac;   //!
   TBranch        *b_fInvMass_omegac;   //!
   TBranch        *b_fImpParRPhi_omegac;   //!
   TBranch        *b_fImpParZ_omegac;   //!
   TBranch        *b_fIsSignal_omegac;   //!
   TBranch        *b_fImpParRPhi_pi3;   //!
   TBranch        *b_fImpParZ_pi3;   //!

   TreeCutVarOmegac(TTree *tree=0);
   virtual ~TreeCutVarOmegac();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Int_t    GetEntriesFast();
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   //virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef TreeCutVarOmegac_cxx
TreeCutVarOmegac::TreeCutVarOmegac(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("signal/AnalysisResults.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("signal/AnalysisResults.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("signal/AnalysisResults.root:/MCanalysis");
      dir->GetObject("TreeCutVarOmegac",tree);

   }
   Init(tree);
}

TreeCutVarOmegac::~TreeCutVarOmegac()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t TreeCutVarOmegac::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Int_t TreeCutVarOmegac::GetEntriesFast()
{
    // Read contents of entry.
    if (!fChain) return 0;
    return fChain->GetEntriesFast();
}
Long64_t TreeCutVarOmegac::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void TreeCutVarOmegac::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("fPt_V0neg", &fPt_V0neg, &b_fPt_V0neg);
   fChain->SetBranchAddress("fEta_V0neg", &fEta_V0neg, &b_fEta_V0neg);
   fChain->SetBranchAddress("fPhi_V0neg", &fPhi_V0neg, &b_fPhi_V0neg);
   fChain->SetBranchAddress("fRap_V0neg", &fRap_V0neg, &b_fRap_V0neg);
   fChain->SetBranchAddress("fGenPt_V0neg", &fGenPt_V0neg, &b_fGenPt_V0neg);
   fChain->SetBranchAddress("fGenEta_V0neg", &fGenEta_V0neg, &b_fGenEta_V0neg);
   fChain->SetBranchAddress("fGenPhi_V0neg", &fGenPhi_V0neg, &b_fGenPhi_V0neg);
   fChain->SetBranchAddress("fGenRap_V0neg", &fGenRap_V0neg, &b_fGenRap_V0neg);
   fChain->SetBranchAddress("fGenRxy_V0neg", &fGenRxy_V0neg, &b_fGenRxy_V0neg);
   fChain->SetBranchAddress("fPt_V0pos", &fPt_V0pos, &b_fPt_V0pos);
   fChain->SetBranchAddress("fEta_V0pos", &fEta_V0pos, &b_fEta_V0pos);
   fChain->SetBranchAddress("fPhi_V0pos", &fPhi_V0pos, &b_fPhi_V0pos);
   fChain->SetBranchAddress("fRap_V0pos", &fRap_V0pos, &b_fRap_V0pos);
   fChain->SetBranchAddress("fGenPt_V0pos", &fGenPt_V0pos, &b_fGenPt_V0pos);
   fChain->SetBranchAddress("fGenEta_V0pos", &fGenEta_V0pos, &b_fGenEta_V0pos);
   fChain->SetBranchAddress("fGenPhi_V0pos", &fGenPhi_V0pos, &b_fGenPhi_V0pos);
   fChain->SetBranchAddress("fGenRap_V0pos", &fGenRap_V0pos, &b_fGenRap_V0pos);
   fChain->SetBranchAddress("fGenRxy_V0pos", &fGenRxy_V0pos, &b_fGenRxy_V0pos);
   fChain->SetBranchAddress("fPtV0", &fPtV0, &b_fPtV0);
   fChain->SetBranchAddress("fEtaV0", &fEtaV0, &b_fEtaV0);
   fChain->SetBranchAddress("fPhiV0", &fPhiV0, &b_fPhiV0);
   fChain->SetBranchAddress("fRapV0", &fRapV0, &b_fRapV0);
   fChain->SetBranchAddress("fGenPtV0", &fGenPtV0, &b_fGenPtV0);
   fChain->SetBranchAddress("fGenEtaV0", &fGenEtaV0, &b_fGenEtaV0);
   fChain->SetBranchAddress("fGenPhiV0", &fGenPhiV0, &b_fGenPhiV0);
   fChain->SetBranchAddress("fGenRapV0", &fGenRapV0, &b_fGenRapV0);
   fChain->SetBranchAddress("fGenRxyV0", &fGenRxyV0, &b_fGenRxyV0);
   fChain->SetBranchAddress("fPt_CascBach", &fPt_CascBach, &b_fPt_CascBach);
   fChain->SetBranchAddress("fEta_CascBach", &fEta_CascBach, &b_fEta_CascBach);
   fChain->SetBranchAddress("fPhi_CascBach", &fPhi_CascBach, &b_fPhi_CascBach);
   fChain->SetBranchAddress("fRap_CascBach", &fRap_CascBach, &b_fRap_CascBach);
   fChain->SetBranchAddress("fGenPt_CascBach", &fGenPt_CascBach, &b_fGenPt_CascBach);
   fChain->SetBranchAddress("fGenEta_CascBach", &fGenEta_CascBach, &b_fGenEta_CascBach);
   fChain->SetBranchAddress("fGenPhi_CascBach", &fGenPhi_CascBach, &b_fGenPhi_CascBach);
   fChain->SetBranchAddress("fGenRap_CascBach", &fGenRap_CascBach, &b_fGenRap_CascBach);
   fChain->SetBranchAddress("fGenRxy_CascBach", &fGenRxy_CascBach, &b_fGenRxy_CascBach);
   fChain->SetBranchAddress("fPtomega", &fPtomega, &b_fPtomega);
   fChain->SetBranchAddress("fEtaomega", &fEtaomega, &b_fEtaomega);
   fChain->SetBranchAddress("fPhiomega", &fPhiomega, &b_fPhiomega);
   fChain->SetBranchAddress("fRapomega", &fRapomega, &b_fRapomega);
   fChain->SetBranchAddress("fGenPtomega", &fGenPtomega, &b_fGenPtomega);
   fChain->SetBranchAddress("fGenEtaomega", &fGenEtaomega, &b_fGenEtaomega);
   fChain->SetBranchAddress("fGenPhiomega", &fGenPhiomega, &b_fGenPhiomega);
   fChain->SetBranchAddress("fGenRapomega", &fGenRapomega, &b_fGenRapomega);
   fChain->SetBranchAddress("fGenRxyomega", &fGenRxyomega, &b_fGenRxyomega);
   fChain->SetBranchAddress("fPt_pi3", &fPt_pi3, &b_fPt_pi3);
   fChain->SetBranchAddress("fEta_pi3", &fEta_pi3, &b_fEta_pi3);
   fChain->SetBranchAddress("fPhi_pi3", &fPhi_pi3, &b_fPhi_pi3);
   fChain->SetBranchAddress("fRap_pi3", &fRap_pi3, &b_fRap_pi3);
   fChain->SetBranchAddress("fGenPt_pi3", &fGenPt_pi3, &b_fGenPt_pi3);
   fChain->SetBranchAddress("fGenEta_pi3", &fGenEta_pi3, &b_fGenEta_pi3);
   fChain->SetBranchAddress("fGenPhi_pi3", &fGenPhi_pi3, &b_fGenPhi_pi3);
   fChain->SetBranchAddress("fGenRap_pi3", &fGenRap_pi3, &b_fGenRap_pi3);
   fChain->SetBranchAddress("fGenRxy_pi3", &fGenRxy_pi3, &b_fGenRxy_pi3);
   fChain->SetBranchAddress("fPt_omegac", &fPt_omegac, &b_fPt_omegac);
   fChain->SetBranchAddress("fEta_omegac", &fEta_omegac, &b_fEta_omegac);
   fChain->SetBranchAddress("fPhi_omegac", &fPhi_omegac, &b_fPhi_omegac);
   fChain->SetBranchAddress("fRap_omegac", &fRap_omegac, &b_fRap_omegac);
   fChain->SetBranchAddress("fGenPt_omegac", &fGenPt_omegac, &b_fGenPt_omegac);
   fChain->SetBranchAddress("fGenEta_omegac", &fGenEta_omegac, &b_fGenEta_omegac);
   fChain->SetBranchAddress("fGenPhi_omegac", &fGenPhi_omegac, &b_fGenPhi_omegac);
   fChain->SetBranchAddress("fGenRap_omegac", &fGenRap_omegac, &b_fGenRap_omegac);
   fChain->SetBranchAddress("fGenRxy_omegac", &fGenRxy_omegac, &b_fGenRxy_omegac);
   fChain->SetBranchAddress("fChi2ndf_omegac", &fChi2ndf_omegac, &b_fChi2ndf_omegac);
   fChain->SetBranchAddress("fCosPA_omegac", &fCosPA_omegac, &b_fCosPA_omegac);
   fChain->SetBranchAddress("fCosPAXY_omegac", &fCosPAXY_omegac, &b_fCosPAXY_omegac);
   fChain->SetBranchAddress("fDecayLength_omegac", &fDecayLength_omegac, &b_fDecayLength_omegac);
   fChain->SetBranchAddress("fDecayLengthXY_omegac", &fDecayLengthXY_omegac, &b_fDecayLengthXY_omegac);
   fChain->SetBranchAddress("fInvMass_omegac", &fInvMass_omegac, &b_fInvMass_omegac);
   fChain->SetBranchAddress("fImpParRPhi_omegac", &fImpParRPhi_omegac, &b_fImpParRPhi_omegac);
   fChain->SetBranchAddress("fImpParZ_omegac", &fImpParZ_omegac, &b_fImpParZ_omegac);
   fChain->SetBranchAddress("fIsSignal_omegac", &fIsSignal_omegac, &b_fIsSignal_omegac);
   fChain->SetBranchAddress("fImpParRPhi_pi3", &fImpParRPhi_pi3, &b_fImpParRPhi_pi3);
   fChain->SetBranchAddress("fImpParZ_pi3", &fImpParZ_pi3, &b_fImpParZ_pi3);
   Notify();
}

Bool_t TreeCutVarOmegac::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void TreeCutVarOmegac::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t TreeCutVarOmegac::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef TreeCutVarOmegac_cxx
