/*
gfan.h Interface to gfan.cc

$Author: monerjan $
$Date: 2009-10-01 07:57:24 $
$Header: /exports/cvsroot-2/cvsroot/kernel/gfan.h,v 1.8 2009-10-01 07:57:24 monerjan Exp $
$Id: gfan.h,v 1.8 2009-10-01 07:57:24 monerjan Exp $
*/
#ifdef HAVE_GFAN
#include "intvec.h"

#define p800
#ifdef p800
#include "../../cddlib/include/setoper.h"
#include "../../cddlib/include/cdd.h"
#include "../../cddlib/include/cddmp.h"
#endif
//ideal getGB(ideal inputIdeal);
ideal gfan(ideal inputIdeal);
//int dotProduct(intvec a, intvec b);
//bool isParallel(intvec a, intvec b);

class facet
{
	private:
		/** \brief Inner normal of the facet, describing it uniquely up to isomorphism */
		intvec *fNormal;
		
		/** \brief An interior point of the facet*/
		intvec *interiorPoint;
		
		/** \brief Universal Cone Number
		 * The number of the cone the facet belongs to, Set in getConeNormals()
		 */
		int UCN;
		
		/** \brief The codim of the facet
		 */
		int codim;
		
		/** \brief The Groebner basis on the other side of a shared facet
		 *
		 * In order not to have to compute the flipped GB twice we store the basis we already get
		 * when identifying search facets. Thus in the next step of the reverse search we can 
		 * just copy the old cone and update the facet and the gcBasis.
		 * facet::flibGB is set via facet::setFlipGB() and printed via facet::printFlipGB
		 */
		ideal flipGB;		//The Groebner Basis on the other side, computed via gcone::flip
		
	public:	
		/** \brief Boolean value to indicate whether a facet is flippable or not
	 	* This is also used to mark facets that nominally are flippable but which do
	 	* not intersect with the positive orthant. This check is done in gcone::getCodim2Normals
		 */	
		bool isFlippable;	//**flippable facet? */
		bool isIncoming;	//Is the facet incoming or outgoing in the reverse search?
		facet *next;		//Pointer to next facet
		facet *prev;		//Pointer to predecessor. Needed for the SearchList in noRevS
		facet *codim2Ptr;	//Pointer to (codim-2)-facet. Bit of recursion here ;-)
		int numCodim2Facets;	//#of (codim-2)-facets of this facet. Set in getCodim2Normals()
		ring flipRing;		//the ring on the other side of the facet
					
		/** The default constructor. Do I need a constructor of type facet(intvec)? */
		facet();
		facet(int const &n);
		/** \brief The copy constructor
		 */
		facet(const facet& f);
		
		/** The default destructor */
		~facet();
				
		/** \brief Comparison of facets*/
		bool areEqual(facet &f, facet &g);
		/** Stores the facet normal \param intvec*/
		void setFacetNormal(intvec *iv);
		/** Hopefully returns the facet normal */
		intvec *getFacetNormal();
		/** Method to print the facet normal*/
		void printNormal();
		/** Store the flipped GB*/
		void setFlipGB(ideal I);
		/** Return the flipped GB*/
		ideal getFlipGB();
		/** Print the flipped GB*/
		void printFlipGB();
		/** Set the UCN */
		void setUCN(int n);
		/** \brief Get the UCN 
		 * Returns the UCN iff this != NULL, else -1
		 */
		int getUCN();
		/** Store an interior point of the facet */
		void setInteriorPoint(intvec *iv);
		intvec *getInteriorPoint();
		/** \brief Debugging function
		 * prints the facet normal an all (codim-2)-facets that belong to it
		 */
		void fDebugPrint();
		friend class gcone;		
};

/**
 *\brief Implements the cone structure
 *
 * A cone is represented by a linked list of facet normals
 * @see facet
 */

class gcone
{
	private:		
		ring rootRing;		//good to know this -> generic walk
		ideal inputIdeal;	//the original
		ring baseRing;		//the basering of the cone				
		intvec *ivIntPt;	//an interior point of the cone
		int UCN;		//unique number of the cone
		static int counter;
		
	public:	
		/** \brief Pointer to the first facet */
		facet *facetPtr;	//Will hold the adress of the first facet; set by gcone::getConeNormals
		
		/** # of variables in the ring */
		int numVars;		//#of variables in the ring
		
		/** # of facets of the cone
		 * This value is set by gcone::getConeNormals
		 */
		int numFacets;		//#of facets of the cone
		
		/**
		 * At least as a workaround we store the irredundant facets of a matrix here.
		 * Otherwise, since we throw away non-flippable facets, facets2Matrix will not 
		 * yield all the necessary information
		 */
		dd_MatrixPtr ddFacets;	//Matrix to store irredundant facets of the cone
		
		/** Contains the Groebner basis of the cone. Is set by gcone::getGB(ideal I)*/
		ideal gcBasis;		//GB of the cone, set by gcone::getGB();
		gcone *next;		//Pointer to *previous* cone in search tree	
		
		
		gcone();
		gcone(ring r, ideal I);
		gcone(const gcone& gc, const facet &f);
		~gcone();
		void setIntPoint(intvec *iv);
		intvec *getIntPoint();
		void showIntPoint();
		void showFacets(short codim=1);
		void showSLA(facet &f);
		void idDebugPrint(ideal const &I);
		void setNumFacets();
		int getNumFacets();
		int getUCN();
		void getConeNormals(ideal const &I, bool compIntPoint=FALSE);
		void getCodim2Normals(gcone const &gc);
		void flip(ideal gb, facet *f);
		poly restOfDiv(poly const &f, ideal const &I);
		ideal ffG(ideal const &H, ideal const &G);
		void getGB(ideal const &inputIdeal);
		intvec *ivNeg(const intvec *iv);
		int dotProduct(intvec const &iva, intvec const &ivb);
		bool isParallel(intvec const &a, intvec const &b);
		void interiorPoint(dd_MatrixPtr const &M, intvec &iv);
		ring rCopyAndAddWeight(ring const &r, intvec const *ivw);
		ring rCopyAndChangeWeight(ring const &r, intvec *ivw);
		bool isSearchFacet(gcone &gcTmp, facet *testfacet);
		bool areEqual(intvec const &a, intvec const &b);
		void reverseSearch(gcone *gcAct);
		void noRevS(gcone &gcRoot, bool usingIntPoint=FALSE);
		void makeInt(dd_MatrixPtr const &M, int const line, intvec &n);
		void normalize();
		facet * enqueueNewFacets(facet &f);
		int intgcd(int a, int b);
		dd_MatrixPtr facets2Matrix(gcone const &gc);
		void writeConeToFile(gcone const &gc, bool usingIntPoints=FALSE);
		void readConeFromFile(int gcNum);
		friend class facet;	
};

#endif
