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

/// \cond CLASSIMP
ClassImp(AliRecoDecayOmegac)
/// \endcond

AliRecoDecayOmegac::AliRecoDecayOmegac() :
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
fCascImpParRPhi(0),
fCascImpParZ(0),
fBachImpParRPhi(0),
fBachImpParZ(0),
fDecayLength(0),
fDecayLengthXY(0),
fCosThetaP(0),
fCosThetaPXY(0),
fCandTrackParam(),
fCascTrackParam(),
fCasc(),
fV0TrackParam(),
fV0(),
fCascBachelor(),
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
AliRecoDecayOmegac::AliRecoDecayOmegac(const AliRecoDecayOmegac &omegac) :
fDecayVtx(omegac.fDecayVtx),
fChi2NdfVtx(omegac.fChi2NdfVtx),
fPx(omegac.fPx),
fPy(omegac.fPy),
fPz(omegac.fPz),
fPt(omegac.fPt),
fP(omegac.fP),
fE(omegac.fE),
fInvMass(omegac.fInvMass),
fEta(omegac.fEta),
fRap(omegac.fRap),
fPhi(omegac.fPhi),
fImpParRPhi(omegac.fImpParRPhi),
fImpParZ(omegac.fImpParZ),
fCascImpParRPhi(omegac.fCascImpParRPhi),
fCascImpParZ(omegac.fCascImpParZ),
fBachImpParRPhi(omegac.fBachImpParRPhi),
fBachImpParZ(omegac.fBachImpParZ),
fDecayLength(omegac.fDecayLength),
fDecayLengthXY(omegac.fDecayLengthXY),
fCosThetaP(omegac.fCosThetaP),
fCosThetaPXY(omegac.fCosThetaPXY),
fCandTrackParam(omegac.fCandTrackParam),
fCascTrackParam(omegac.fCascTrackParam),
fCasc(omegac.fCasc),
fV0TrackParam(omegac.fV0TrackParam),
fV0(omegac.fV0),
fCascBachelor(omegac.fCascBachelor),
fBachelor(omegac.fBachelor),
fBzkG(omegac.fBzkG),
fLblCand(omegac.fLblCand),
fIsTrueSignal(omegac.fIsTrueSignal)
{
    //
    // Copy Constructor
    //
}
//-------------------------------------------
AliRecoDecayOmegac::AliRecoDecayOmegac(const AliESDcascade &casc, const AliESDtrack &t, const AliESDVertex &vtx, const AliESDv0 &v, const AliESDtrack &tBachCasc) :
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
fCascImpParRPhi(0),
fCascImpParZ(0),
fBachImpParRPhi(0),
fBachImpParZ(0),
fDecayLength(0),
fDecayLengthXY(0),
fCosThetaP(0),
fCosThetaPXY(0),
fCandTrackParam(),
fCascTrackParam(),
fCasc(casc),
fV0TrackParam(),
fV0(v),
fCascBachelor(tBachCasc),
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
AliRecoDecayOmegac &AliRecoDecayOmegac::operator=(const AliRecoDecayOmegac &source)
{
    //
    /// assignment operator
    //
    if(&source == this) return *this;
    
    AliRecoDecayOmegac::operator=(source);
    
    return *this;
}
//-------------------------------------------
void AliRecoDecayOmegac::SetTrackParamForCascade(){ //set fV0TrackParam, fCascTrackParam
    
    // cascade vertex and momentum
    Double_t xyz[3], pxpypz[3];
    fCasc.XvYvZv(xyz);
    fCasc.PxPyPz(pxpypz);
    Double_t cov[6];
    fCasc.GetPosCovXi(cov);
    AliESDVertex vertexcasc;
    vertexcasc.SetXYZ(xyz);
    vertexcasc.SetCovarianceMatrix(cov);
    vertexcasc.SetChi2(fCasc.GetChi2Xi());
    vertexcasc.SetNContributors(0);
    //= new AliESDVertex(xyz,cov,fCasc.GetChi2Xi(),0,"VertexCasc");
    
    Double_t xyzv0[3], pxpypzv0[3];
    fV0.XvYvZv(xyzv0);
    fV0.PxPyPz(pxpypzv0);
    Double_t covTrPos[21];
    (fV0.GetParamP())->GetCovarianceXYZPxPyPz(covTrPos);
    Double_t covTrNeg[21];
    (fV0.GetParamN())->GetCovarianceXYZPxPyPz(covTrNeg);
    //cov V0
    Double_t covV0[21];
    Double_t covV0prop[21];
    for(int i=0; i<21; i++){
        covV0[i]=covTrPos[i]+covTrNeg[i];
        covV0prop[i]=0;
    }
    //fV0TrackParam = new AliExternalTrackParam(xyzv0,pxpypzv0,covV0,1);
    fV0TrackParam.Set(xyzv0,pxpypzv0,covV0,1);
    Double_t d0zV0[2],covd0zV0[3];
    fV0TrackParam.PropagateToDCA(&vertexcasc,0.,100.,d0zV0,covd0zV0);
    fV0TrackParam.GetCovarianceXYZPxPyPz(covV0prop);
    //cascade bachelor
    Double_t d0zbach[2],covd0zbach[3];
    AliExternalTrackParam esdCascadeBach;
    esdCascadeBach.CopyFromVTrack(&fCascBachelor);
    esdCascadeBach.PropagateToDCA(&vertexcasc,fBzkG,100.,d0zbach,covd0zbach);
    Double_t covTrBach[21];
    esdCascadeBach.GetCovarianceXYZPxPyPz(covTrBach);
    // cascade covariance matrix
    Double_t cv[21]; for(int i=0; i<21; i++) cv[i]=0;
    for(int k=0; k<21; k++) {
        cv[k]=covTrBach[k]+covV0prop[k];
    }
    Short_t chargeCasc = fCascBachelor.Charge();
    //Printf("OMEGA charge %d",chargeCasc);
    //fCascTrackParam = new AliExternalTrackParam(xyz,pxpypz,cv,chargeCasc);
    fCascTrackParam.Set(xyz,pxpypz,cv,chargeCasc);
    
}
//-------------------------------------------
void AliRecoDecayOmegac::SetTrackParamForCand(){ //set fCandTrackParam
    
    AliExternalTrackParam cascTrack;
    cascTrack.CopyFromVTrack(&fCascTrackParam);
    Double_t d0zcasc[2],covd0zcasc[3];
    cascTrack.PropagateToDCA(&fDecayVtx,fBzkG,100.,d0zcasc,covd0zcasc);
    Double_t covTrCascade[21];
    cascTrack.GetCovarianceXYZPxPyPz(covTrCascade);
    Double_t pxcasc = cascTrack.Px();
    Double_t pycasc = cascTrack.Py();
    Double_t pzcasc = cascTrack.Pz();
    
    Double_t d0zbach[2],covd0zbach[3];
    AliExternalTrackParam etp;
    etp.CopyFromVTrack(&fBachelor);
    etp.PropagateToDCA(&fDecayVtx,fBzkG,100.,d0zbach,covd0zbach);
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
    xyz[0] = fDecayVtx.GetX();
    xyz[1] = fDecayVtx.GetY();
    xyz[2] = fDecayVtx.GetZ();
    pxpypz[0] = pxcasc + pxtr;
    pxpypz[1] = pycasc + pytr;
    pxpypz[2] = pzcasc + pztr;
    fCandTrackParam.Set(xyz,pxpypz,covTrOmegac,1);
    
}
//-------------------------------------------
void AliRecoDecayOmegac::FillCand(const AliESDVertex &primvtx){ //set fChi2NdfVtx, fPx, fPy, fPz, fP, fE, fInvMass, fEta, fRap, fPhi, fImpParRPhi, fImpParZ, fCascImpParRPhi, fCascImpParZ, fBachImpParRPhi, fBachImpParZ
    
    SetTrackParamForCascade();
    
    fChi2NdfVtx = fDecayVtx.GetChi2toNDF();
    
    //omega
    AliExternalTrackParam etpCasc;
    etpCasc.CopyFromVTrack(&fCascTrackParam);
    //propagate cascade to omegac decay vertex
    Double_t d0zVert[2],covd0zVert[3];
    etpCasc.PropagateToDCA(&fDecayVtx,fBzkG,100.,d0zVert,covd0zVert);
    Int_t pdgomega=3334;
    Double_t massOmega = TDatabasePDG::Instance()->GetParticle(pdgomega)->Mass();
    Double_t pxomega = etpCasc.Px();
    Double_t pyomega = etpCasc.Py();
    Double_t pzomega = etpCasc.Pz();
    Double_t pomega2 = pxomega*pxomega + pyomega*pyomega + pzomega*pzomega;
    Double_t eomega2 = (massOmega*massOmega)+pomega2;
    Double_t eomega = TMath::Sqrt(eomega2);
    Double_t pomega = TMath::Sqrt(pomega2);
    Double_t pxpypzomega[3] = {0.,0.,0.};
    pxpypzomega[0]=pxomega; pxpypzomega[1]=pyomega; pxpypzomega[2]=pzomega;
    Double_t poscasc[3] = { -1000.0, -1000.0, -1000.0 };
    fCasc.GetXYZcascade(poscasc[0],poscasc[1],poscasc[2]);
    Double_t radiusOmega=TMath::Sqrt(poscasc[0]*poscasc[0]+poscasc[1]*poscasc[1]+poscasc[2]*poscasc[2]);
    Double_t ptOmega=TMath::Sqrt(pxomega*pxomega + pyomega*pyomega);
    Double_t cosPAOmega=fCasc.GetCascadeCosineOfPointingAngle(fDecayVtx.GetX(), fDecayVtx.GetY(),fDecayVtx.GetZ());
    //---> track
    Double_t d0zVertT[2],covd0zVertT[3];
    AliExternalTrackParam etp;
    etp.CopyFromVTrack(&fBachelor);
    etp.PropagateToDCA(&fDecayVtx,fBzkG,100.,d0zVertT,covd0zVertT);
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
    fPx = pxomega+pxpi;
    fPy = pyomega+pypi;
    fPz = pzomega+pzpi;
    Double_t pxpypzomegac[3]; pxpypzomegac[0]=fPx; pxpypzomegac[1]=fPy; pxpypzomegac[2]=fPz;
    fPt = TMath::Sqrt(fPx*fPx+fPy*fPy);
    Double_t invmass2omegac = (eomega+epi)*(eomega+epi)-(fPx*fPx+fPy*fPy+fPz*fPz);
    fInvMass  = TMath::Sqrt(invmass2omegac);
    fE = eomega+epi;
    fP = TMath::Sqrt(fPx*fPx+fPy*fPy+fPz*fPz);
    fEta = EtaCand(fP, fPz);
    fPhi = PhiCand(fPx, fPy);
    fRap = YCand(fE, fPz);
    
    //propagate to primary vertex
    //omega
    AliExternalTrackParam etpCascPrimVtx;
    etpCascPrimVtx.CopyFromVTrack(&fCascTrackParam);
    etpCascPrimVtx.PropagateToDCA(&primvtx,fBzkG,100.,d0zVert,covd0zVert);
    //pion
    AliExternalTrackParam etpPrimVtx;
    etpPrimVtx.CopyFromVTrack(&fBachelor);
    etpPrimVtx.PropagateToDCA(&primvtx,fBzkG,100.,d0zVertT,covd0zVertT);
    //omegac
    Double_t d0zVertC[2],covd0zVertC[3];
    SetTrackParamForCand();
    AliExternalTrackParam etpOmegac;
    etpOmegac.CopyFromVTrack(&fCandTrackParam);
    etpOmegac.PropagateToDCA(&primvtx,0,100.,d0zVertC,covd0zVertC);
    
    fImpParRPhi = d0zVertC[0];
    fImpParZ    = d0zVertC[1];
    fCascImpParRPhi = d0zVert[0];
    fCascImpParZ    = d0zVert[1];
    fBachImpParRPhi = d0zVertT[0];
    fBachImpParZ    = d0zVertT[1];

}
//----------------------------------------------------------------------------
float AliRecoDecayOmegac::DecayLength(AliESDVertex *primV, AliESDVertex *secV)
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
float AliRecoDecayOmegac::DecayLengthXY(AliESDVertex *primV, AliESDVertex *secV)
{
    /// Decay length in XY assuming it is produced at "point" [cm]
    
    fDecayLength = TMath::Sqrt((primV->GetX()-secV->GetX())
                       *(primV->GetX()-secV->GetX())
                       +(primV->GetY()-secV->GetY())
                       *(primV->GetY()-secV->GetY()));
    return fDecayLength;
}
//----------------------------------------------------------------------------
float AliRecoDecayOmegac::CosPointingAngle(AliESDVertex *primV, AliESDVertex *secV, Double_t p[3])
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
float AliRecoDecayOmegac::CosPointingAngleXY(AliESDVertex *primV, AliESDVertex *secV, Double_t p[3])
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
bool AliRecoDecayOmegac::CheckIsSignal(AliESDEvent *evt, AliMCEvent *mcevt){
    
    Bool_t retval = false;
    
    Int_t idxPosCasc     = fCasc.GetPindex();
    Int_t idxNegCasc     = fCasc.GetNindex();
    
    //Printf("*********** AliRecoDecayOmegac::CheckIsSignalOmegac ***********");
    //Printf("idxPosCasc = %d idxNegCasc = %d",idxPosCasc,idxNegCasc);
    
    AliESDtrack *pTrackCasc          = (AliESDtrack*)evt->GetTrack( idxPosCasc );
    AliESDtrack *nTrackCasc          = (AliESDtrack*)evt->GetTrack( idxNegCasc );
    
    Int_t lblpTrackCasc      = pTrackCasc->GetLabel();
    Int_t lblnTrackCasc      = nTrackCasc->GetLabel();
    Int_t lblbachTrackCasc   = fCascBachelor.GetLabel();
    Int_t lblbachTrackCascC  = fBachelor.GetLabel();
    
    //Printf("lblpTrackCasc = %d lblnTrackCasc = %d lblbachTrackCasc = %d lblbachTrackCascC = %d",lblpTrackCasc,lblnTrackCasc,lblbachTrackCasc,lblbachTrackCascC);
    
    TParticle *partPosTrackCasc   = (TParticle*)mcevt->Particle(lblpTrackCasc);
    TParticle *partNegTrackCasc   = (TParticle*)mcevt->Particle(lblnTrackCasc);
    TParticle *partbachTrackCasc  = (TParticle*)mcevt->Particle(lblbachTrackCasc);
    TParticle *partbachTrackCascC = (TParticle*)mcevt->Particle(lblbachTrackCascC);
    fLblCand = partbachTrackCascC->GetFirstMother();
    
    // - Level of the cascade daughters
    Int_t lblMotherPosV0Dghter = 0;  lblMotherPosV0Dghter = partPosTrackCasc->GetFirstMother();
    Int_t lblMotherNegV0Dghter = 0;  lblMotherNegV0Dghter = partNegTrackCasc->GetFirstMother();
    if(lblMotherPosV0Dghter == lblMotherNegV0Dghter && lblMotherPosV0Dghter > 0 && lblMotherNegV0Dghter > 0){
        // mothers = Lambda candidate ... a priori
        TParticle *mcMotherPosV0Dghter = 0x0; mcMotherPosV0Dghter = mcevt->Particle( lblMotherPosV0Dghter );
        TParticle *mcMotherNegV0Dghter = 0x0; mcMotherNegV0Dghter = mcevt->Particle( lblMotherNegV0Dghter );
        // - Level of cascade candidate
        Int_t lblGdMotherPosV0Dghter = 0; lblGdMotherPosV0Dghter = mcMotherPosV0Dghter->GetFirstMother() ;
        Int_t lblGdMotherNegV0Dghter = 0; lblGdMotherNegV0Dghter = mcMotherNegV0Dghter->GetFirstMother() ;
        if(lblGdMotherPosV0Dghter == lblGdMotherNegV0Dghter && lblGdMotherPosV0Dghter>0 && lblGdMotherNegV0Dghter>0){
            // Gd mothers = cascade candidate ... a priori
            TParticle *mcGdMotherPosV0Dghter = 0x0; mcGdMotherPosV0Dghter = mcevt->Particle( lblGdMotherPosV0Dghter ); //omega
            TParticle *mcGdMotherNegV0Dghter = 0x0; mcGdMotherNegV0Dghter = mcevt->Particle( lblGdMotherNegV0Dghter ); //omega
            Int_t lblMotherBach = 0; lblMotherBach = partbachTrackCasc->GetFirstMother();   //label omega
            if(lblMotherBach == lblGdMotherPosV0Dghter && lblMotherBach > 0 &&  lblGdMotherPosV0Dghter > 0){
                // label of the mother of the bachelor == label of the grandmother of the pos/neg V0 daughters
                TParticle *mcMotherBach = 0x0; mcMotherBach = mcevt->Particle( lblMotherBach );  //bachelor mother omega part
                Int_t lblGdMotherBach = 0; lblGdMotherBach = mcMotherBach->GetFirstMother();         //label of the grandmother of the bachelor -> omegac label
                Int_t lblMotherBachC = 0;  lblMotherBachC = partbachTrackCascC->GetFirstMother();     //label of the mother of the bachelorC -> omegac label
                if(lblGdMotherBach == lblMotherBachC && lblGdMotherBach>-1 && lblMotherBachC>-1) {
                    //Omegac level
                    //label of the grandmother of the bachelor == label of the mother of the bachelorC
                    TParticle *mcGdMotherBach = 0x0; mcGdMotherBach = mcevt->Particle( lblGdMotherBach ); //bachelor grandmother part -> omegac part
                    TParticle *mcMotherBachC = 0x0;  mcMotherBachC = mcevt->Particle( lblMotherBachC );   //bachelorC mother part     -> omegac part
                    Int_t pdgGdMotherBach=0; pdgGdMotherBach = TMath::Abs(mcGdMotherBach->GetPdgCode());     //bachelor grandmother pdg -> omegac pdg
                    Int_t pdgMotherBachC=0;  pdgMotherBachC = TMath::Abs(mcMotherBachC->GetPdgCode());       //bachelorC mother pdg     -> omegac pdg
                    if(pdgGdMotherBach==4332 && pdgMotherBachC==4332){ // check if is omegac
                        retval =true;
                    }
                }
            }
        }
    }
    fIsTrueSignal = retval;
    return retval;
    
}
//_________________________________________
bool AliRecoDecayOmegac::IsSelected(double *cuts){
    
    bool issel = true;
    
    //Printf("%f %f",TMath::Abs(fInvMass-TDatabasePDG::Instance()->GetParticle(4332)->Mass()), cuts[0]);
    
    if(TMath::Abs(fInvMass-TDatabasePDG::Instance()->GetParticle(4332)->Mass())>cuts[0]) issel = false;
    if(fPt            <cuts[1])  issel = false;
    if(fDecayLength   <cuts[2])  issel = false;
    if(fDecayLengthXY <cuts[3])  issel = false;
    if(fImpParRPhi    <cuts[4])  issel = false;
    if(fBachImpParRPhi<cuts[5])  issel = false;
    if(fChi2NdfVtx    >cuts[6])  issel = false;
    
    return issel;
    
}
