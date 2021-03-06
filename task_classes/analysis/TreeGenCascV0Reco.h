//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jun 27 12:04:24 2019 by ROOT version 6.16/00
// from TTree TreeGenCascV0Reco/TreeGenCascV0Reco
// found on file: signal/AnalysisResults.root
//////////////////////////////////////////////////////////

#ifndef TreeGenCascV0Reco_h
#define TreeGenCascV0Reco_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class TreeGenCascV0Reco {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         fTreeGen_omega_Eta;
   Float_t         fTreeGen_omega_Pt;
   Float_t         fTreeGen_omega_Y;
   Float_t         fTreeGen_omega_Phi;
   Float_t         fTreeGen_omega_Rxy;
   Int_t           fTreeGen_omega_Pdg;
   Float_t         fTreeGen_lambda_Eta;
   Float_t         fTreeGen_lambda_Pt;
   Float_t         fTreeGen_lambda_Y;
   Float_t         fTreeGen_lambda_Phi;
   Float_t         fTreeGen_lambda_Rxy;
   Int_t           fTreeGen_lambda_Pdg;
   Float_t         fTreeGen_k_Eta;
   Float_t         fTreeGen_k_Pt;
   Float_t         fTreeGen_k_Y;
   Float_t         fTreeGen_k_Phi;
   Float_t         fTreeGen_k_Rxy;
   Int_t           fTreeGen_k_Pdg;
   Float_t         fTreeGen_p_Eta;
   Float_t         fTreeGen_p_Pt;
   Float_t         fTreeGen_p_Y;
   Float_t         fTreeGen_p_Phi;
   Float_t         fTreeGen_p_Rxy;
   Int_t           fTreeGen_p_Pdg;
   Float_t         fTreeGen_pi4_Eta;
   Float_t         fTreeGen_pi4_Pt;
   Float_t         fTreeGen_pi4_Y;
   Float_t         fTreeGen_pi4_Phi;
   Float_t         fTreeGen_pi4_Rxy;
   Int_t           fTreeGen_pi4_Pdg;
   Float_t         fTreeGen_omega_InvMass;

   // List of branches
   TBranch        *b_fTreeGen_omega_Eta;   //!
   TBranch        *b_fTreeGen_omega_Pt;   //!
   TBranch        *b_fTreeGen_omega_Y;   //!
   TBranch        *b_fTreeGen_omega_Phi;   //!
   TBranch        *b_fTreeGen_omega_Rxy;   //!
   TBranch        *b_fTreeGen_omega_Pdg;   //!
   TBranch        *b_fTreeGen_lambda_Eta;   //!
   TBranch        *b_fTreeGen_lambda_Pt;   //!
   TBranch        *b_fTreeGen_lambda_Y;   //!
   TBranch        *b_fTreeGen_lambda_Phi;   //!
   TBranch        *b_fTreeGen_lambda_Rxy;   //!
   TBranch        *b_fTreeGen_lambda_Pdg;   //!
   TBranch        *b_fTreeGen_k_Eta;   //!
   TBranch        *b_fTreeGen_k_Pt;   //!
   TBranch        *b_fTreeGen_k_Y;   //!
   TBranch        *b_fTreeGen_k_Phi;   //!
   TBranch        *b_fTreeGen_k_Rxy;   //!
   TBranch        *b_fTreeGen_k_Pdg;   //!
   TBranch        *b_fTreeGen_p_Eta;   //!
   TBranch        *b_fTreeGen_p_Pt;   //!
   TBranch        *b_fTreeGen_p_Y;   //!
   TBranch        *b_fTreeGen_p_Phi;   //!
   TBranch        *b_fTreeGen_p_Rxy;   //!
   TBranch        *b_fTreeGen_p_Pdg;   //!
   TBranch        *b_fTreeGen_pi4_Eta;   //!
   TBranch        *b_fTreeGen_pi4_Pt;   //!
   TBranch        *b_fTreeGen_pi4_Y;   //!
   TBranch        *b_fTreeGen_pi4_Phi;   //!
   TBranch        *b_fTreeGen_pi4_Rxy;   //!
   TBranch        *b_fTreeGen_pi4_Pdg;   //!
   TBranch        *b_fTreeGen_omega_InvMass;   //!

   TreeGenCascV0Reco(TTree *tree=0);
   virtual ~TreeGenCascV0Reco();
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

#ifdef TreeGenCascV0Reco_cxx
TreeGenCascV0Reco::TreeGenCascV0Reco(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("signal/AnalysisResults.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("signal/AnalysisResults.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("signal/AnalysisResults.root:/MCanalysis");
      dir->GetObject("TreeGenCascV0Reco",tree);

   }
   Init(tree);
}

TreeGenCascV0Reco::~TreeGenCascV0Reco()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t TreeGenCascV0Reco::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Int_t TreeGenCascV0Reco::GetEntriesFast()
{
    // Read contents of entry.
    if (!fChain) return 0;
    return fChain->GetEntriesFast();
}
Long64_t TreeGenCascV0Reco::LoadTree(Long64_t entry)
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

void TreeGenCascV0Reco::Init(TTree *tree)
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

   fChain->SetBranchAddress("fTreeGen_omega_Eta", &fTreeGen_omega_Eta, &b_fTreeGen_omega_Eta);
   fChain->SetBranchAddress("fTreeGen_omega_Pt", &fTreeGen_omega_Pt, &b_fTreeGen_omega_Pt);
   fChain->SetBranchAddress("fTreeGen_omega_Y", &fTreeGen_omega_Y, &b_fTreeGen_omega_Y);
   fChain->SetBranchAddress("fTreeGen_omega_Phi", &fTreeGen_omega_Phi, &b_fTreeGen_omega_Phi);
   fChain->SetBranchAddress("fTreeGen_omega_Rxy", &fTreeGen_omega_Rxy, &b_fTreeGen_omega_Rxy);
   fChain->SetBranchAddress("fTreeGen_omega_Pdg", &fTreeGen_omega_Pdg, &b_fTreeGen_omega_Pdg);
   fChain->SetBranchAddress("fTreeGen_lambda_Eta", &fTreeGen_lambda_Eta, &b_fTreeGen_lambda_Eta);
   fChain->SetBranchAddress("fTreeGen_lambda_Pt", &fTreeGen_lambda_Pt, &b_fTreeGen_lambda_Pt);
   fChain->SetBranchAddress("fTreeGen_lambda_Y", &fTreeGen_lambda_Y, &b_fTreeGen_lambda_Y);
   fChain->SetBranchAddress("fTreeGen_lambda_Phi", &fTreeGen_lambda_Phi, &b_fTreeGen_lambda_Phi);
   fChain->SetBranchAddress("fTreeGen_lambda_Rxy", &fTreeGen_lambda_Rxy, &b_fTreeGen_lambda_Rxy);
   fChain->SetBranchAddress("fTreeGen_lambda_Pdg", &fTreeGen_lambda_Pdg, &b_fTreeGen_lambda_Pdg);
   fChain->SetBranchAddress("fTreeGen_k_Eta", &fTreeGen_k_Eta, &b_fTreeGen_k_Eta);
   fChain->SetBranchAddress("fTreeGen_k_Pt", &fTreeGen_k_Pt, &b_fTreeGen_k_Pt);
   fChain->SetBranchAddress("fTreeGen_k_Y", &fTreeGen_k_Y, &b_fTreeGen_k_Y);
   fChain->SetBranchAddress("fTreeGen_k_Phi", &fTreeGen_k_Phi, &b_fTreeGen_k_Phi);
   fChain->SetBranchAddress("fTreeGen_k_Rxy", &fTreeGen_k_Rxy, &b_fTreeGen_k_Rxy);
   fChain->SetBranchAddress("fTreeGen_k_Pdg", &fTreeGen_k_Pdg, &b_fTreeGen_k_Pdg);
   fChain->SetBranchAddress("fTreeGen_p_Eta", &fTreeGen_p_Eta, &b_fTreeGen_p_Eta);
   fChain->SetBranchAddress("fTreeGen_p_Pt", &fTreeGen_p_Pt, &b_fTreeGen_p_Pt);
   fChain->SetBranchAddress("fTreeGen_p_Y", &fTreeGen_p_Y, &b_fTreeGen_p_Y);
   fChain->SetBranchAddress("fTreeGen_p_Phi", &fTreeGen_p_Phi, &b_fTreeGen_p_Phi);
   fChain->SetBranchAddress("fTreeGen_p_Rxy", &fTreeGen_p_Rxy, &b_fTreeGen_p_Rxy);
   fChain->SetBranchAddress("fTreeGen_p_Pdg", &fTreeGen_p_Pdg, &b_fTreeGen_p_Pdg);
   fChain->SetBranchAddress("fTreeGen_pi4_Eta", &fTreeGen_pi4_Eta, &b_fTreeGen_pi4_Eta);
   fChain->SetBranchAddress("fTreeGen_pi4_Pt", &fTreeGen_pi4_Pt, &b_fTreeGen_pi4_Pt);
   fChain->SetBranchAddress("fTreeGen_pi4_Y", &fTreeGen_pi4_Y, &b_fTreeGen_pi4_Y);
   fChain->SetBranchAddress("fTreeGen_pi4_Phi", &fTreeGen_pi4_Phi, &b_fTreeGen_pi4_Phi);
   fChain->SetBranchAddress("fTreeGen_pi4_Rxy", &fTreeGen_pi4_Rxy, &b_fTreeGen_pi4_Rxy);
   fChain->SetBranchAddress("fTreeGen_pi4_Pdg", &fTreeGen_pi4_Pdg, &b_fTreeGen_pi4_Pdg);
   fChain->SetBranchAddress("fTreeGen_omega_InvMass", &fTreeGen_omega_InvMass, &b_fTreeGen_omega_InvMass);
   Notify();
}

Bool_t TreeGenCascV0Reco::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void TreeGenCascV0Reco::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t TreeGenCascV0Reco::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef TreeGenCascV0Reco_cxx
