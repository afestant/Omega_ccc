//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jun 27 12:04:24 2019 by ROOT version 6.16/00
// from TTree TreeGenOmegaccc/TreeGenOmegaccc
// found on file: signal/AnalysisResults.root
//////////////////////////////////////////////////////////

#ifndef TreeGenOmegaccc_h
#define TreeGenOmegaccc_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class TreeGenOmegaccc {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         fTreeGen_omegaccc_Eta;
   Float_t         fTreeGen_omegaccc_Pt;
   Float_t         fTreeGen_omegaccc_Y;
   Float_t         fTreeGen_omegaccc_Phi;
   Float_t         fTreeGen_omegaccc_Rxy;
   Int_t           fTreeGen_omegaccc_ReconstructableHits;
   Int_t           fTreeGen_omegaccc_Pdg;
   Float_t         fTreeGen_omegacc_Eta;
   Float_t         fTreeGen_omegacc_Pt;
   Float_t         fTreeGen_omegacc_Y;
   Float_t         fTreeGen_omegacc_Phi;
   Float_t         fTreeGen_omegacc_Rxy;
   Int_t           fTreeGen_omegacc_ReconstructableHits;
   Int_t           fTreeGen_omegacc_Pdg;
   Float_t         fTreeGen_pi1_Eta;
   Float_t         fTreeGen_pi1_Pt;
   Float_t         fTreeGen_pi1_Y;
   Float_t         fTreeGen_pi1_Phi;
   Float_t         fTreeGen_pi1_Rxy;
   Int_t           fTreeGen_pi1_ReconstructableHits;
   Int_t           fTreeGen_pi1_Pdg;
   Float_t         fTreeGen_omegac_Eta;
   Float_t         fTreeGen_omegac_Pt;
   Float_t         fTreeGen_omegac_Y;
   Float_t         fTreeGen_omegac_Phi;
   Float_t         fTreeGen_omegac_Rxy;
   Int_t           fTreeGen_omegac_ReconstructableHits;
   Int_t           fTreeGen_omegac_Pdg;
   Float_t         fTreeGen_pi2_Eta;
   Float_t         fTreeGen_pi2_Pt;
   Float_t         fTreeGen_pi2_Y;
   Float_t         fTreeGen_pi2_Phi;
   Float_t         fTreeGen_pi2_Rxy;
   Int_t           fTreeGen_pi2_ReconstructableHits;
   Int_t           fTreeGen_pi2_Pdg;
   Float_t         fTreeGen_omega_Eta;
   Float_t         fTreeGen_omega_Pt;
   Float_t         fTreeGen_omega_Y;
   Float_t         fTreeGen_omega_Phi;
   Float_t         fTreeGen_omega_Rxy;
   Int_t           fTreeGen_omega_ReconstructableHits;
   Int_t           fTreeGen_omega_Pdg;
   Float_t         fTreeGen_pi3_Eta;
   Float_t         fTreeGen_pi3_Pt;
   Float_t         fTreeGen_pi3_Y;
   Float_t         fTreeGen_pi3_Phi;
   Float_t         fTreeGen_pi3_Rxy;
   Int_t           fTreeGen_pi3_ReconstructableHits;
   Int_t           fTreeGen_pi3_Pdg;
   Float_t         fTreeGen_lambda_Eta;
   Float_t         fTreeGen_lambda_Pt;
   Float_t         fTreeGen_lambda_Y;
   Float_t         fTreeGen_lambda_Phi;
   Float_t         fTreeGen_lambda_Rxy;
   Int_t           fTreeGen_lambda_ReconstructableHits;
   Int_t           fTreeGen_lambda_Pdg;
   Float_t         fTreeGen_k_Eta;
   Float_t         fTreeGen_k_Pt;
   Float_t         fTreeGen_k_Y;
   Float_t         fTreeGen_k_Phi;
   Float_t         fTreeGen_k_Rxy;
   Int_t           fTreeGen_k_ReconstructableHits;
   Int_t           fTreeGen_k_Pdg;
   Float_t         fTreeGen_p_Eta;
   Float_t         fTreeGen_p_Pt;
   Float_t         fTreeGen_p_Y;
   Float_t         fTreeGen_p_Phi;
   Float_t         fTreeGen_p_Rxy;
   Int_t           fTreeGen_p_ReconstructableHits;
   Int_t           fTreeGen_p_Pdg;
   Float_t         fTreeGen_pi4_Eta;
   Float_t         fTreeGen_pi4_Pt;
   Float_t         fTreeGen_pi4_Y;
   Float_t         fTreeGen_pi4_Phi;
   Float_t         fTreeGen_pi4_Rxy;
   Int_t           fTreeGen_pi4_ReconstructableHits;
   Int_t           fTreeGen_pi4_Pdg;

   // List of branches
   TBranch        *b_fTreeGen_omegaccc_Eta;   //!
   TBranch        *b_fTreeGen_omegaccc_Pt;   //!
   TBranch        *b_fTreeGen_omegaccc_Y;   //!
   TBranch        *b_fTreeGen_omegaccc_Phi;   //!
   TBranch        *b_fTreeGen_omegaccc_Rxy;   //!
   TBranch        *b_fTreeGen_omegaccc_ReconstructableHits;   //!
   TBranch        *b_fTreeGen_omegaccc_Pdg;   //!
   TBranch        *b_fTreeGen_omegacc_Eta;   //!
   TBranch        *b_fTreeGen_omegacc_Pt;   //!
   TBranch        *b_fTreeGen_omegacc_Y;   //!
   TBranch        *b_fTreeGen_omegacc_Phi;   //!
   TBranch        *b_fTreeGen_omegacc_Rxy;   //!
   TBranch        *b_fTreeGen_omegacc_ReconstructableHits;   //!
   TBranch        *b_fTreeGen_omegacc_Pdg;   //!
   TBranch        *b_fTreeGen_pi1_Eta;   //!
   TBranch        *b_fTreeGen_pi1_Pt;   //!
   TBranch        *b_fTreeGen_pi1_Y;   //!
   TBranch        *b_fTreeGen_pi1_Phi;   //!
   TBranch        *b_fTreeGen_pi1_Rxy;   //!
   TBranch        *b_fTreeGen_pi1_ReconstructableHits;   //!
   TBranch        *b_fTreeGen_pi1_Pdg;   //!
   TBranch        *b_fTreeGen_omegac_Eta;   //!
   TBranch        *b_fTreeGen_omegac_Pt;   //!
   TBranch        *b_fTreeGen_omegac_Y;   //!
   TBranch        *b_fTreeGen_omegac_Phi;   //!
   TBranch        *b_fTreeGen_omegac_Rxy;   //!
   TBranch        *b_fTreeGen_omegac_ReconstructableHits;   //!
   TBranch        *b_fTreeGen_omegac_Pdg;   //!
   TBranch        *b_fTreeGen_pi2_Eta;   //!
   TBranch        *b_fTreeGen_pi2_Pt;   //!
   TBranch        *b_fTreeGen_pi2_Y;   //!
   TBranch        *b_fTreeGen_pi2_Phi;   //!
   TBranch        *b_fTreeGen_pi2_Rxy;   //!
   TBranch        *b_fTreeGen_pi2_ReconstructableHits;   //!
   TBranch        *b_fTreeGen_pi2_Pdg;   //!
   TBranch        *b_fTreeGen_omega_Eta;   //!
   TBranch        *b_fTreeGen_omega_Pt;   //!
   TBranch        *b_fTreeGen_omega_Y;   //!
   TBranch        *b_fTreeGen_omega_Phi;   //!
   TBranch        *b_fTreeGen_omega_Rxy;   //!
   TBranch        *b_fTreeGen_omega_ReconstructableHits;   //!
   TBranch        *b_fTreeGen_omega_Pdg;   //!
   TBranch        *b_fTreeGen_pi3_Eta;   //!
   TBranch        *b_fTreeGen_pi3_Pt;   //!
   TBranch        *b_fTreeGen_pi3_Y;   //!
   TBranch        *b_fTreeGen_pi3_Phi;   //!
   TBranch        *b_fTreeGen_pi3_Rxy;   //!
   TBranch        *b_fTreeGen_pi3_ReconstructableHits;   //!
   TBranch        *b_fTreeGen_pi3_Pdg;   //!
   TBranch        *b_fTreeGen_lambda_Eta;   //!
   TBranch        *b_fTreeGen_lambda_Pt;   //!
   TBranch        *b_fTreeGen_lambda_Y;   //!
   TBranch        *b_fTreeGen_lambda_Phi;   //!
   TBranch        *b_fTreeGen_lambda_Rxy;   //!
   TBranch        *b_fTreeGen_lambda_ReconstructableHits;   //!
   TBranch        *b_fTreeGen_lambda_Pdg;   //!
   TBranch        *b_fTreeGen_k_Eta;   //!
   TBranch        *b_fTreeGen_k_Pt;   //!
   TBranch        *b_fTreeGen_k_Y;   //!
   TBranch        *b_fTreeGen_k_Phi;   //!
   TBranch        *b_fTreeGen_k_Rxy;   //!
   TBranch        *b_fTreeGen_k_ReconstructableHits;   //!
   TBranch        *b_fTreeGen_k_Pdg;   //!
   TBranch        *b_fTreeGen_p_Eta;   //!
   TBranch        *b_fTreeGen_p_Pt;   //!
   TBranch        *b_fTreeGen_p_Y;   //!
   TBranch        *b_fTreeGen_p_Phi;   //!
   TBranch        *b_fTreeGen_p_Rxy;   //!
   TBranch        *b_fTreeGen_p_ReconstructableHits;   //!
   TBranch        *b_fTreeGen_p_Pdg;   //!
   TBranch        *b_fTreeGen_pi4_Eta;   //!
   TBranch        *b_fTreeGen_pi4_Pt;   //!
   TBranch        *b_fTreeGen_pi4_Y;   //!
   TBranch        *b_fTreeGen_pi4_Phi;   //!
   TBranch        *b_fTreeGen_pi4_Rxy;   //!
   TBranch        *b_fTreeGen_pi4_ReconstructableHits;   //!
   TBranch        *b_fTreeGen_pi4_Pdg;   //!

   TreeGenOmegaccc(TTree *tree=0);
   virtual ~TreeGenOmegaccc();
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

#ifdef TreeGenOmegaccc_cxx
TreeGenOmegaccc::TreeGenOmegaccc(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("signal/AnalysisResults.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("signal/AnalysisResults.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("signal/AnalysisResults.root:/MCanalysis");
      dir->GetObject("TreeGenOmegaccc",tree);

   }
   Init(tree);
}

TreeGenOmegaccc::~TreeGenOmegaccc()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t TreeGenOmegaccc::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Int_t TreeGenOmegaccc::GetEntriesFast()
{
    // Read contents of entry.
    if (!fChain) return 0;
    return fChain->GetEntriesFast();
}
Long64_t TreeGenOmegaccc::LoadTree(Long64_t entry)
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

void TreeGenOmegaccc::Init(TTree *tree)
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

   fChain->SetBranchAddress("fTreeGen_omegaccc_Eta", &fTreeGen_omegaccc_Eta, &b_fTreeGen_omegaccc_Eta);
   fChain->SetBranchAddress("fTreeGen_omegaccc_Pt", &fTreeGen_omegaccc_Pt, &b_fTreeGen_omegaccc_Pt);
   fChain->SetBranchAddress("fTreeGen_omegaccc_Y", &fTreeGen_omegaccc_Y, &b_fTreeGen_omegaccc_Y);
   fChain->SetBranchAddress("fTreeGen_omegaccc_Phi", &fTreeGen_omegaccc_Phi, &b_fTreeGen_omegaccc_Phi);
   fChain->SetBranchAddress("fTreeGen_omegaccc_Rxy", &fTreeGen_omegaccc_Rxy, &b_fTreeGen_omegaccc_Rxy);
   fChain->SetBranchAddress("fTreeGen_omegaccc_ReconstructableHits", &fTreeGen_omegaccc_ReconstructableHits, &b_fTreeGen_omegaccc_ReconstructableHits);
   fChain->SetBranchAddress("fTreeGen_omegaccc_Pdg", &fTreeGen_omegaccc_Pdg, &b_fTreeGen_omegaccc_Pdg);
   fChain->SetBranchAddress("fTreeGen_omegacc_Eta", &fTreeGen_omegacc_Eta, &b_fTreeGen_omegacc_Eta);
   fChain->SetBranchAddress("fTreeGen_omegacc_Pt", &fTreeGen_omegacc_Pt, &b_fTreeGen_omegacc_Pt);
   fChain->SetBranchAddress("fTreeGen_omegacc_Y", &fTreeGen_omegacc_Y, &b_fTreeGen_omegacc_Y);
   fChain->SetBranchAddress("fTreeGen_omegacc_Phi", &fTreeGen_omegacc_Phi, &b_fTreeGen_omegacc_Phi);
   fChain->SetBranchAddress("fTreeGen_omegacc_Rxy", &fTreeGen_omegacc_Rxy, &b_fTreeGen_omegacc_Rxy);
   fChain->SetBranchAddress("fTreeGen_omegacc_ReconstructableHits", &fTreeGen_omegacc_ReconstructableHits, &b_fTreeGen_omegacc_ReconstructableHits);
   fChain->SetBranchAddress("fTreeGen_omegacc_Pdg", &fTreeGen_omegacc_Pdg, &b_fTreeGen_omegacc_Pdg);
   fChain->SetBranchAddress("fTreeGen_pi1_Eta", &fTreeGen_pi1_Eta, &b_fTreeGen_pi1_Eta);
   fChain->SetBranchAddress("fTreeGen_pi1_Pt", &fTreeGen_pi1_Pt, &b_fTreeGen_pi1_Pt);
   fChain->SetBranchAddress("fTreeGen_pi1_Y", &fTreeGen_pi1_Y, &b_fTreeGen_pi1_Y);
   fChain->SetBranchAddress("fTreeGen_pi1_Phi", &fTreeGen_pi1_Phi, &b_fTreeGen_pi1_Phi);
   fChain->SetBranchAddress("fTreeGen_pi1_Rxy", &fTreeGen_pi1_Rxy, &b_fTreeGen_pi1_Rxy);
   fChain->SetBranchAddress("fTreeGen_pi1_ReconstructableHits", &fTreeGen_pi1_ReconstructableHits, &b_fTreeGen_pi1_ReconstructableHits);
   fChain->SetBranchAddress("fTreeGen_pi1_Pdg", &fTreeGen_pi1_Pdg, &b_fTreeGen_pi1_Pdg);
   fChain->SetBranchAddress("fTreeGen_omegac_Eta", &fTreeGen_omegac_Eta, &b_fTreeGen_omegac_Eta);
   fChain->SetBranchAddress("fTreeGen_omegac_Pt", &fTreeGen_omegac_Pt, &b_fTreeGen_omegac_Pt);
   fChain->SetBranchAddress("fTreeGen_omegac_Y", &fTreeGen_omegac_Y, &b_fTreeGen_omegac_Y);
   fChain->SetBranchAddress("fTreeGen_omegac_Phi", &fTreeGen_omegac_Phi, &b_fTreeGen_omegac_Phi);
   fChain->SetBranchAddress("fTreeGen_omegac_Rxy", &fTreeGen_omegac_Rxy, &b_fTreeGen_omegac_Rxy);
   fChain->SetBranchAddress("fTreeGen_omegac_ReconstructableHits", &fTreeGen_omegac_ReconstructableHits, &b_fTreeGen_omegac_ReconstructableHits);
   fChain->SetBranchAddress("fTreeGen_omegac_Pdg", &fTreeGen_omegac_Pdg, &b_fTreeGen_omegac_Pdg);
   fChain->SetBranchAddress("fTreeGen_pi2_Eta", &fTreeGen_pi2_Eta, &b_fTreeGen_pi2_Eta);
   fChain->SetBranchAddress("fTreeGen_pi2_Pt", &fTreeGen_pi2_Pt, &b_fTreeGen_pi2_Pt);
   fChain->SetBranchAddress("fTreeGen_pi2_Y", &fTreeGen_pi2_Y, &b_fTreeGen_pi2_Y);
   fChain->SetBranchAddress("fTreeGen_pi2_Phi", &fTreeGen_pi2_Phi, &b_fTreeGen_pi2_Phi);
   fChain->SetBranchAddress("fTreeGen_pi2_Rxy", &fTreeGen_pi2_Rxy, &b_fTreeGen_pi2_Rxy);
   fChain->SetBranchAddress("fTreeGen_pi2_ReconstructableHits", &fTreeGen_pi2_ReconstructableHits, &b_fTreeGen_pi2_ReconstructableHits);
   fChain->SetBranchAddress("fTreeGen_pi2_Pdg", &fTreeGen_pi2_Pdg, &b_fTreeGen_pi2_Pdg);
   fChain->SetBranchAddress("fTreeGen_omega_Eta", &fTreeGen_omega_Eta, &b_fTreeGen_omega_Eta);
   fChain->SetBranchAddress("fTreeGen_omega_Pt", &fTreeGen_omega_Pt, &b_fTreeGen_omega_Pt);
   fChain->SetBranchAddress("fTreeGen_omega_Y", &fTreeGen_omega_Y, &b_fTreeGen_omega_Y);
   fChain->SetBranchAddress("fTreeGen_omega_Phi", &fTreeGen_omega_Phi, &b_fTreeGen_omega_Phi);
   fChain->SetBranchAddress("fTreeGen_omega_Rxy", &fTreeGen_omega_Rxy, &b_fTreeGen_omega_Rxy);
   fChain->SetBranchAddress("fTreeGen_omega_ReconstructableHits", &fTreeGen_omega_ReconstructableHits, &b_fTreeGen_omega_ReconstructableHits);
   fChain->SetBranchAddress("fTreeGen_omega_Pdg", &fTreeGen_omega_Pdg, &b_fTreeGen_omega_Pdg);
   fChain->SetBranchAddress("fTreeGen_pi3_Eta", &fTreeGen_pi3_Eta, &b_fTreeGen_pi3_Eta);
   fChain->SetBranchAddress("fTreeGen_pi3_Pt", &fTreeGen_pi3_Pt, &b_fTreeGen_pi3_Pt);
   fChain->SetBranchAddress("fTreeGen_pi3_Y", &fTreeGen_pi3_Y, &b_fTreeGen_pi3_Y);
   fChain->SetBranchAddress("fTreeGen_pi3_Phi", &fTreeGen_pi3_Phi, &b_fTreeGen_pi3_Phi);
   fChain->SetBranchAddress("fTreeGen_pi3_Rxy", &fTreeGen_pi3_Rxy, &b_fTreeGen_pi3_Rxy);
   fChain->SetBranchAddress("fTreeGen_pi3_ReconstructableHits", &fTreeGen_pi3_ReconstructableHits, &b_fTreeGen_pi3_ReconstructableHits);
   fChain->SetBranchAddress("fTreeGen_pi3_Pdg", &fTreeGen_pi3_Pdg, &b_fTreeGen_pi3_Pdg);
   fChain->SetBranchAddress("fTreeGen_lambda_Eta", &fTreeGen_lambda_Eta, &b_fTreeGen_lambda_Eta);
   fChain->SetBranchAddress("fTreeGen_lambda_Pt", &fTreeGen_lambda_Pt, &b_fTreeGen_lambda_Pt);
   fChain->SetBranchAddress("fTreeGen_lambda_Y", &fTreeGen_lambda_Y, &b_fTreeGen_lambda_Y);
   fChain->SetBranchAddress("fTreeGen_lambda_Phi", &fTreeGen_lambda_Phi, &b_fTreeGen_lambda_Phi);
   fChain->SetBranchAddress("fTreeGen_lambda_Rxy", &fTreeGen_lambda_Rxy, &b_fTreeGen_lambda_Rxy);
   fChain->SetBranchAddress("fTreeGen_lambda_ReconstructableHits", &fTreeGen_lambda_ReconstructableHits, &b_fTreeGen_lambda_ReconstructableHits);
   fChain->SetBranchAddress("fTreeGen_lambda_Pdg", &fTreeGen_lambda_Pdg, &b_fTreeGen_lambda_Pdg);
   fChain->SetBranchAddress("fTreeGen_k_Eta", &fTreeGen_k_Eta, &b_fTreeGen_k_Eta);
   fChain->SetBranchAddress("fTreeGen_k_Pt", &fTreeGen_k_Pt, &b_fTreeGen_k_Pt);
   fChain->SetBranchAddress("fTreeGen_k_Y", &fTreeGen_k_Y, &b_fTreeGen_k_Y);
   fChain->SetBranchAddress("fTreeGen_k_Phi", &fTreeGen_k_Phi, &b_fTreeGen_k_Phi);
   fChain->SetBranchAddress("fTreeGen_k_Rxy", &fTreeGen_k_Rxy, &b_fTreeGen_k_Rxy);
   fChain->SetBranchAddress("fTreeGen_k_ReconstructableHits", &fTreeGen_k_ReconstructableHits, &b_fTreeGen_k_ReconstructableHits);
   fChain->SetBranchAddress("fTreeGen_k_Pdg", &fTreeGen_k_Pdg, &b_fTreeGen_k_Pdg);
   fChain->SetBranchAddress("fTreeGen_p_Eta", &fTreeGen_p_Eta, &b_fTreeGen_p_Eta);
   fChain->SetBranchAddress("fTreeGen_p_Pt", &fTreeGen_p_Pt, &b_fTreeGen_p_Pt);
   fChain->SetBranchAddress("fTreeGen_p_Y", &fTreeGen_p_Y, &b_fTreeGen_p_Y);
   fChain->SetBranchAddress("fTreeGen_p_Phi", &fTreeGen_p_Phi, &b_fTreeGen_p_Phi);
   fChain->SetBranchAddress("fTreeGen_p_Rxy", &fTreeGen_p_Rxy, &b_fTreeGen_p_Rxy);
   fChain->SetBranchAddress("fTreeGen_p_ReconstructableHits", &fTreeGen_p_ReconstructableHits, &b_fTreeGen_p_ReconstructableHits);
   fChain->SetBranchAddress("fTreeGen_p_Pdg", &fTreeGen_p_Pdg, &b_fTreeGen_p_Pdg);
   fChain->SetBranchAddress("fTreeGen_pi4_Eta", &fTreeGen_pi4_Eta, &b_fTreeGen_pi4_Eta);
   fChain->SetBranchAddress("fTreeGen_pi4_Pt", &fTreeGen_pi4_Pt, &b_fTreeGen_pi4_Pt);
   fChain->SetBranchAddress("fTreeGen_pi4_Y", &fTreeGen_pi4_Y, &b_fTreeGen_pi4_Y);
   fChain->SetBranchAddress("fTreeGen_pi4_Phi", &fTreeGen_pi4_Phi, &b_fTreeGen_pi4_Phi);
   fChain->SetBranchAddress("fTreeGen_pi4_Rxy", &fTreeGen_pi4_Rxy, &b_fTreeGen_pi4_Rxy);
   fChain->SetBranchAddress("fTreeGen_pi4_ReconstructableHits", &fTreeGen_pi4_ReconstructableHits, &b_fTreeGen_pi4_ReconstructableHits);
   fChain->SetBranchAddress("fTreeGen_pi4_Pdg", &fTreeGen_pi4_Pdg, &b_fTreeGen_pi4_Pdg);
   Notify();
}

Bool_t TreeGenOmegaccc::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void TreeGenOmegaccc::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t TreeGenOmegaccc::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef TreeGenOmegaccc_cxx
