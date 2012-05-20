// Copyright (c) 1995-1999 Matra Datavision
// Copyright (c) 1999-2012 OPEN CASCADE SAS
//
// The content of this file is subject to the Open CASCADE Technology Public
// License Version 6.5 (the "License"). You may not use the content of this file
// except in compliance with the License. Please obtain a copy of the License
// at http://www.opencascade.org and read it completely before using this file.
//
// The Initial Developer of the Original Code is Open CASCADE S.A.S., having its
// main offices at: 1, place des Freres Montgolfier, 78280 Guyancourt, France.
//
// The Original Code and all software distributed under the License is
// distributed on an "AS IS" basis, without warranty of any kind, and the
// Initial Developer hereby disclaims all such warranties, including without
// limitation, any warranties of merchantability, fitness for a particular
// purpose or non-infringement. Please see the License for the specific terms
// and conditions governing the rights and limitations under the License.

//============================================ IntAna2d_AnaIntersection_8.cxx
//============================================================================
#include <IntAna2d_AnaIntersection.jxx>

#include <IntAna2d_Outils.hxx>

// -----------------------------------------------------------------
// ------ Verification de la validite des points obtenus  ----------
// --- Methode a implementer dans les autres routines si on constate
// --- des problemes d'instabilite numerique sur
// ---      * la construction des polynomes en t (t:parametre)
// ---      * la resolution du polynome
// ---      * le retour : parametre t -> point d'intersection
// --- Probleme : A partir de quelle Tolerance un point n'est
// ---            plus un point de la courbe. (f(x,y)=1e-10 ??)
// ---            ne donne pas d'info. sur la dist. du pt a la courbe
// -----------------------------------------------------------------
// ------ Methode non implementee pour les autres Intersections
// --- Si un probleme est constate : Dupliquer le code entre les
// --- commentaires VERIF-VALID
// -----------------------------------------------------------------

void IntAna2d_AnaIntersection::Perform(const gp_Hypr2d& H,
				       const IntAna2d_Conic& Conic)
  {
    Standard_Boolean HIsDirect = H.IsDirect();
    Standard_Real A,B,C,D,E,F;
    Standard_Real px0,px1,px2,px3,px4;
    Standard_Real minor_radius=H.MinorRadius();
    Standard_Real major_radius=H.MajorRadius();
    Standard_Integer i;
    Standard_Real tx,ty,S;

    done = Standard_False;
    nbp = 0;
    para = Standard_False;
    iden = Standard_False;
    empt = Standard_False;

    gp_Ax2d Axe_rep(H.XAxis());
    Conic.Coefficients(A,B,C,D,E,F);
    Conic.NewCoefficients(A,B,C,D,E,F,Axe_rep);
  
    Standard_Real A_major_radiusP2=A*major_radius*major_radius;
    Standard_Real B_minor_radiusP2=B*minor_radius*minor_radius;
    Standard_Real C_2_major_minor_radius=C*2.0*major_radius*minor_radius;

    // Parametre : t avec x=MajorRadius*Ch(t)  y=:minorRadius*Sh(t)
    // Le polynome est reecrit en Exp(t)
    // Suivent les Coeffs du polynome P multiplie par 4*Exp(t)^2

    px0=A_major_radiusP2 - C_2_major_minor_radius + B_minor_radiusP2;
    px1=4.0*(D*major_radius-E*minor_radius);
    px2=2.0*(A_major_radiusP2 + 2.0*F - B_minor_radiusP2);
    px3=4.0*(D*major_radius+E*minor_radius);
    px4=A_major_radiusP2 + C_2_major_minor_radius + B_minor_radiusP2;

    MyDirectPolynomialRoots Sol(px4,px3,px2,px1,px0);

    if(!Sol.IsDone()) {
      //-- cout<<" Done = False ds IntAna2d_AnaIntersection_8.cxx "<<endl;
      done=Standard_False;
      return;
    }
    else { 
      if(Sol.InfiniteRoots()) { 
	iden=Standard_True;
	done=Standard_True;
	return;
      }
      // On a X=(CosH(t)*major_radius)/2 , Y=(SinH(t)*minor_radius)/2
      //      la Resolution est en S=Exp(t)
      nbp=Sol.NbSolutions();
      Standard_Integer nb_sol_valides=0;
      for(i=1;i<=nbp;i++) {
	S=Sol.Value(i);
	if(S>RealEpsilon()) {
	  tx=0.5*major_radius*(S+1/S);	
	  ty=0.5*minor_radius*(S-1/S);

          //--- Est-on sur la bonne branche de l'Hyperbole
          //--------------- VERIF-VALIDITE-INTERSECTION ----------
	  //--- On Suppose que l'ecart sur la courbe1 est nul
          //--- (le point a ete obtenu par parametrage)
          //--- ??? la tolerance a ete fixee a 1e-10 ?????????????

#if 0 
          Standard_Real ecart_sur_courbe2;
          ecart_sur_courbe2=Conic.Value(tx,ty);
          if(ecart_sur_courbe2<=1e-10 && ecart_sur_courbe2>=-1e-10) {
	    nb_sol_valides++;
	    Coord_Ancien_Repere(tx,ty,Axe_rep);
	    lpnt[nb_sol_valides-1].SetValue(tx,ty,Log(S));
          }
#else 
	
	  nb_sol_valides++;
	  Coord_Ancien_Repere(tx,ty,Axe_rep);
	  S = Log(S);
	  if(!HIsDirect)
	    S = -S;
	  lpnt[nb_sol_valides-1].SetValue(tx,ty,S);
#endif
        }   
      }
      nbp=nb_sol_valides;
      Traitement_Points_Confondus(nbp,lpnt);
    }
    done=Standard_True;
  }





