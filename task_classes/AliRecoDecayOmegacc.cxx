/**************************************************************************
 * Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
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
#include <TDatabasePDG.h>
#include "AliGenParam.h"
#include "AliGenerator.h"
#include "AliRunLoader.h"
#include "AliRun.h"
#include "AliStack.h"
#include "AliMCEvent.h"
#include "AliESDEvent.h"
#include "AliESDUtils.h"
#include "AliESDcascade.h"
#include "AliESDVertex.h"
#include "AliESDtrack.h"
#include "AliExternalTrackParam.h"
#include "AliVTrack.h"
#include "AliKalmanTrack.h"
#include "AliRecoDecayOmegac.h"
#include "AliRecoDecayOmegacc.h"

/// \cond CLASSIMP
ClassImp(AliRecoDecayOmegacc)
/// \endcond

AliRecoDecayOmegacc::AliRecoDecayOmegacc() :
fDecayVtx(),
fChi2NdfVtx(0),
fPx(0),
fPy(0),
fPz(0),
fPt(0),
fP(0),
fE(0),
fInvMass(0),
fEta(0),
fRap(0),
fPhi(0),
fImpParRPhi(0),
fImpParZ(0),
fWeakDauImpParRPhi(0.),
fWeakDauImpParZ(0.),
fBachImpParRPhi(0),
fBachImpParZ(0),
fDecayLength(0),
fDecayLengthXY(0),
fCosThetaP(0),
fCosThetaPXY(0),
fCandTrackParam(),
fWeakDauTrackParam(),
fWeakDau(),
fBachelor(),
fBzkG(0),
fLblCand(-99),
fIsTrueSignal(false)
{
    //
    // Default Constructor
    //
}
//-------------------------------------------
AliRecoDecayOmegacc::AliRecoDecayOmegacc(const AliRecoDecayOmegacc &omegacc) :
fDecayVtx(omegacc.fDecayVtx),
fChi2NdfVtx(omegacc.fChi2NdfVtx),
fPx(omegacc.fPx),
fPy(omegacc.fPy),
fPz(omegacc.fPz),
fPt(omegacc.fPt),
fP(omegacc.fP),
fE(omegacc.fE),
fInvMass(omegacc.fInvMass),
fEta(omegacc.fEta),
fRap(omegacc.fRap),
fPhi(omegacc.fPhi),
fImpParRPhi(omegacc.fImpParRPhi),
fImpParZ(omegacc.fImpParZ),
fWeakDauImpParRPhi(omegacc.fWeakDauImpParRPhi),
fWeakDauImpParZ(omegacc.fWeakDauImpParZ),
fBachImpParRPhi(omegacc.fBachImpParRPhi),
fBachImpParZ(omegacc.fBachImpParZ),
fDecayLength(omegacc.fDecayLength),
fDecayLengthXY(omegacc.fDecayLengthXY),
fCosThetaP(omegacc.fCosThetaP),
fCosThetaPXY(omegacc.fCosThetaPXY),
fCandTrackParam(omegacc.fCandTrackParam),
fWeakDauTrackParam(omegacc.fWeakDauTrackParam),
fWeakDau(omegacc.fWeakDau),
fBachelor(omegacc.fBachelor),
fBzkG(omegacc.fBzkG),
fLblCand(omegacc.fLblCand),
fIsTrueSignal(omegacc.fIsTrueSignal)
{
    //
    // Copy Constructor
    //
}
//-------------------------------------------
AliRecoDecayOmegacc::AliRecoDecayOmegacc(const AliRecoDecayOmegac &omegac, const AliESDtrack &t, const AliESDVertex &vtx) :
fDecayVtx(vtx),
fChi2NdfVtx(0),
fPx(0),
fPy(0),
fPz(0),
fPt(0),
fP(0),
fE(0),
fInvMass(0),
fEta(0),
fRap(0),
fPhi(0),
fImpParRPhi(0),
fImpParZ(0),
fWeakDauImpParRPhi(0),
fWeakDauImpParZ(0),
fBachImpParRPhi(0),
fBachImpParZ(0),
fDecayLength(0),
fDecayLengthXY(0),
fCosThetaP(0),
fCosThetaPXY(0),
fCandTrackParam(),
fWeakDauTrackParam(),
fWeakDau(omegac),
fBachelor(t),
fBzkG(0.5),
fLblCand(-99),
fIsTrueSignal(false)
{
    //
    // Main Constructor
    //
    
}
//--------------------------------------------------------------------------
AliRecoDecayOmegacc &AliRecoDecayOmegacc::operator=(const AliRecoDecayOmegacc &source)
{
    //
    /// assignment operator
    //
    if(&source == this) return *this;
    
    AliRecoDecayOmegacc::operator=(source);
    
    return *this;
}
//-------------------------------------------
void AliRecoDecayOmegacc::SetTrackParamForCand(){ //set fWeakDauTrackParam
    
    //Omegac trackParam
    AliExternalTrackParam weakDauTrack;
    weakDauTrack.CopyFromVTrack(&fWeakDauTrackParam);
    Double_t d0[2],covd0[3];
    weakDauTrack.PropagateToDCA(&fDecayVtx,0,100.,d0,covd0);
    Double_t covTrWeakDau[21];
    weakDauTrack.GetCovarianceXYZPxPyPz(covTrWeakDau);
    Double_t px = weakDauTrack.Px();
    Double_t py = weakDauTrack.Py();
    Double_t pz = weakDauTrack.Pz();
    
    Double_t d0bach[2],covd0bach[3];
    AliExternalTrackParam etp;
    etp.CopyFromVTrack(&fBachelor);
    etp.PropagateToDCA(&fDecayVtx,fBzkG,100.,d0bach,covd0bach);
    Double_t covTrBach[21];
    etp.GetCovarianceXYZPxPyPz(covTrBach);
    Double_t pxtr = etp.Px();
    Double_t pytr = etp.Py();
    Double_t pztr = etp.Pz();
    
    Double_t covTrCand[21];
    for(Int_t i=0; i<21; i++){
        covTrCand[i] = covTrWeakDau[i] + covTrBach[i];
    }
    Double_t xyz[3], pxpypz[3];
    xyz[0] = fDecayVtx.GetX();
    xyz[1] = fDecayVtx.GetY();
    xyz[2] = fDecayVtx.GetZ();
    pxpypz[0] = px + pxtr;
    pxpypz[1] = py + pytr;
    pxpypz[2] = pz + pztr;
    Short_t charge = fBachelor.Charge();
    fCandTrackParam.Set(xyz,pxpypz,covTrCand,charge);
    
}
//-------------------------------------------
void AliRecoDecayOmegacc::FillCand(const AliESDVertex &primvtx){ //set fChi2NdfVtx, fPx, fPy, fPz, fP, fE, fInvMass, fEta, fRap, fPhi, fImpParRPhi, fImpParZ, fCascImpParRPhi, fCascImpParZ, fBachImpParRPhi, fBachImpParZ
    
    fChi2NdfVtx = fDecayVtx.GetChi2toNDF();
    fWeakDauTrackParam = fWeakDau.GetTrackParamForCand();
    
    //omegac
    AliExternalTrackParam etpWeakDau;
    etpWeakDau.CopyFromVTrack(&fWeakDauTrackParam);
    //propagate omegac to omegacc decay vertex
    Double_t d0Vert[2],covd0Vert[3];
    etpWeakDau.PropagateToDCA(&fDecayVtx,0,100.,d0Vert,covd0Vert);
    Int_t pdgWeakDau=4332;
    Double_t massWeakDau = TDatabasePDG::Instance()->GetParticle(pdgWeakDau)->Mass();
    Double_t pxWeakDau = etpWeakDau.Px();
    Double_t pyWeakDau = etpWeakDau.Py();
    Double_t pzWeakDau = etpWeakDau.Pz();
    Double_t pWeakDau2 = pxWeakDau*pxWeakDau + pyWeakDau*pyWeakDau + pzWeakDau*pzWeakDau;
    Double_t eWeakDau2 = (massWeakDau*massWeakDau)+pWeakDau2;
    Double_t eWeakDau = TMath::Sqrt(eWeakDau2);
    Double_t pWeakDau = TMath::Sqrt(pWeakDau2);
    Double_t pxpypzWeakDau[3] = {0.,0.,0.};
    //---> track
    Double_t d0VertT[2],covd0VertT[3];
    AliExternalTrackParam etp;
    etp.CopyFromVTrack(&fBachelor);
    etp.PropagateToDCA(&fDecayVtx,fBzkG,100.,d0VertT,covd0VertT);
    Int_t pdgtrack=211;
    Double_t masspi = TDatabasePDG::Instance()->GetParticle(pdgtrack)->Mass();
    Double_t pxpi = etp.Px();
    Double_t pypi = etp.Py();
    Double_t pzpi = etp.Pz();
    Double_t ppi2 = pxpi*pxpi + pypi*pypi + pzpi*pzpi;
    Double_t epi2 = (masspi*masspi)+ppi2;
    Double_t epi  = TMath::Sqrt(epi2);
    Double_t ppi  = TMath::Sqrt(ppi2);
    Double_t pxpypzpi[3] = {0.,0.,0.};
    pxpypzpi[0]=pxpi; pxpypzpi[1]=pypi; pxpypzpi[2]=pzpi;
    //---> Omegac
    fPx = pxWeakDau+pxpi;
    fPy = pyWeakDau+pypi;
    fPz = pzWeakDau+pzpi;
    Double_t pxpypzCand[3]; pxpypzCand[0]=fPx; pxpypzCand[1]=fPy; pxpypzCand[2]=fPz;
    fPt = TMath::Sqrt(fPx*fPx+fPy*fPy);
    Double_t invmass2Cand = (eWeakDau+epi)*(eWeakDau+epi)-(fPx*fPx+fPy*fPy+fPz*fPz);
    fInvMass  = TMath::Sqrt(invmass2Cand);
    fE = eWeakDau+epi;
    fP = TMath::Sqrt(fPx*fPx+fPy*fPy+fPz*fPz);
    fEta = EtaCand(fP, fPz);
    fPhi = PhiCand(fPx, fPy);
    fRap = YCand(fE, fPz);
    
    //propagate to primary vertex
    //pion
    AliExternalTrackParam etpPrimVtx;
    etpPrimVtx.CopyFromVTrack(&fBachelor);
    etpPrimVtx.PropagateToDCA(&primvtx,fBzkG,100.,d0VertT,covd0VertT);
    //omegacc
    Double_t d0VertC[2],covd0VertC[3];
    SetTrackParamForCand();
    AliExternalTrackParam etpCand;
    etpCand.CopyFromVTrack(&fCandTrackParam);
    etpCand.PropagateToDCA(&primvtx,fBzkG,100.,d0VertC,covd0VertC);
    
    fImpParRPhi = d0VertC[0];
    fImpParZ    = d0VertC[1];
    fBachImpParRPhi = d0VertT[0];
    fBachImpParZ    = d0VertT[1];
    
}
//----------------------------------------------------------------------------
float AliRecoDecayOmegacc::DecayLength(AliESDVertex *primV, AliESDVertex *secV)
{
    /// Decay length assuming it is produced at "point" [cm]
    fDecayLength = TMath::Sqrt((primV->GetX()-secV->GetX())
                               *(primV->GetX()-secV->GetX())
                               +(primV->GetY()-secV->GetY())
                               *(primV->GetY()-secV->GetY())
                               +(primV->GetZ()-secV->GetZ())
                               *(primV->GetZ()-secV->GetZ()));
    return fDecayLength;
}
//----------------------------------------------------------------------------
float AliRecoDecayOmegacc::DecayLengthXY(AliESDVertex *primV, AliESDVertex *secV)
{
    /// Decay length in XY assuming it is produced at "point" [cm]
    
    fDecayLength = TMath::Sqrt((primV->GetX()-secV->GetX())
                               *(primV->GetX()-secV->GetX())
                               +(primV->GetY()-secV->GetY())
                               *(primV->GetY()-secV->GetY()));
    return fDecayLength;
}
//----------------------------------------------------------------------------
float AliRecoDecayOmegacc::CosPointingAngle(AliESDVertex *primV, AliESDVertex *secV, Double_t p[3])
{
    /// Cosine of pointing angle in space assuming it is produced at "point"
    
    TVector3 mom(p[0],p[1],p[2]);
    TVector3 fline(secV->GetX()-primV->GetX(),
                   secV->GetY()-primV->GetY(),
                   secV->GetZ()-primV->GetZ());
    
    float ptot2 = mom.Mag2()*fline.Mag2();
    if(ptot2 <= 0) {
        fCosThetaP = 0.0;
        return fCosThetaP;
    } else {
        float cos = mom.Dot(fline)/TMath::Sqrt(ptot2);
        if(cos >  1.0) cos =  1.0;
        if(cos < -1.0) cos = -1.0;
        fCosThetaP = cos;
        return fCosThetaP;
    }
}
//----------------------------------------------------------------------------
float AliRecoDecayOmegacc::CosPointingAngleXY(AliESDVertex *primV, AliESDVertex *secV, Double_t p[3])
{
    /// Cosine of pointing angle in transverse plane assuming it is produced
    /// at "point"
    
    TVector3 momXY(p[0],p[1],0.);
    TVector3 flineXY(secV->GetX()-primV->GetX(),
                     secV->GetY()-primV->GetY(),
                     0.);
    
    float ptot2 = momXY.Mag2()*flineXY.Mag2();
    if(ptot2 <= 0) {
        fCosThetaPXY = 0.0;
        return fCosThetaPXY;
    } else {
        float cos = momXY.Dot(flineXY)/TMath::Sqrt(ptot2);
        if(cos >  1.0) cos =  1.0;
        if(cos < -1.0) cos = -1.0;
        fCosThetaPXY = cos;
        return fCosThetaPXY;
    }
}
//_________________________________________
bool AliRecoDecayOmegacc::CheckIsSignal(AliESDEvent *evt, AliMCEvent *mcevt){
    
    Bool_t retval = false;
    
    //bachelor
    Int_t lblbachTrack  = fBachelor.GetLabel();
    TParticle *partbachTrack = (TParticle*)mcevt->Particle(lblbachTrack);
    //weak decay daughter
    int lblweakDau = fWeakDau.GetCandMCLabel();
    TParticle *partweakDau = (TParticle*)mcevt->Particle(lblweakDau);
    bool isTrueSignalWeakDau = fWeakDau.GetIsTrueSignal();
    //mothers
    int lblMotherWeakDau=0;   lblMotherWeakDau  =partweakDau  ->GetFirstMother();
    int lblMotherBachTrack=0; lblMotherBachTrack=partbachTrack->GetFirstMother();
    fLblCand = lblMotherBachTrack;
    
    if(isTrueSignalWeakDau){
        if(lblMotherWeakDau>-1 && lblMotherWeakDau==lblMotherBachTrack){
            TParticle *mcMotherWeakDau  = 0x0; mcMotherWeakDau  = mcevt->Particle( lblMotherWeakDau );   //bachelorCC mother part -> omegacc part
            Int_t pdgMotherWeakDau=0;  pdgMotherWeakDau  = TMath::Abs(mcMotherWeakDau->GetPdgCode());       //omegacc pdg
            if(pdgMotherWeakDau==4432){
                retval =true;
            }
        }
    }
    fIsTrueSignal = retval;
    return retval;
    
}
//_________________________________________
bool AliRecoDecayOmegacc::IsSelected(double *cuts){
    
    bool issel = true;
    
    if(TMath::Abs(fInvMass-TDatabasePDG::Instance()->GetParticle(4432)->Mass())>cuts[0]) issel = false;
    if(fPt            <cuts[1])  issel = false;
    if(fDecayLength   <cuts[2])  issel = false;
    if(fDecayLengthXY <cuts[3])  issel = false;
    if(fImpParRPhi    <cuts[4])  issel = false;
    if(fBachImpParRPhi<cuts[5])  issel = false;
    if(fChi2NdfVtx    >cuts[6])  issel = false;
    
    return issel;
    
}
