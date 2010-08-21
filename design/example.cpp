
#define with(abr,src)	\#define abr (src)\
			\#define {{\
			\#define }} \\\#undef abr

class CStatistics : public CObject {
	DECLARE_SERIAL (CStatistics);
public:
	rtbyte	Mean;
	rtbyte	Sigma;
	...
}

void @Islets_Calculate () {
	// #### FEATURE 1: Special helper classes
	CMeasure msr;
	CStatistics stat;

	CStorageDoc *pDoc = Dias.Documents.Open ("");

	uvar32_64 n, cnt, cell;
	CSurvey *pSrv = pDoc->Surveis.Add ("Cells");

	// #### FEATURE 2: VB-like 'with' blocks
	with (A, pSrv->Fields.Add) {
		A ("ImgNo", n);
		A ("CellNo", cell);
		A ("Mean", msr.Mean);
	} endwith (A);

	with (A, pDoc->Images.Add) {
		A ("Clear");
		A ("Background Mask");
		A ("IR");
		A ("IR Mask");
		A ("Markers");
		A ("Dilated Cells");
		A ("Cells Mask");
	        A ("Islt Mask");
	} endwith (A);

        for (n = 0, cnt = pDoc->Images.GetCount(); n < cnt; ++n) {
		if (pDoc->Images[n].GetName().Find ("Islet") != -1)
			continue;

        	Dias.DensScales["1:1 Scale"].Activate ();
        	pDoc->Images["Clear"] = pDoc->Images[n] - pDoc->Images["Background"];

        	// #### FEATURE 3: Shortcuts to channels as img[][], to fields as srv[][]
        	pDoc->Images["Clear"][0].Statistics (stat);
        	pDoc->Images["Clear"][0].Segmentate (0x07, 0x00, 0xFF);
        	pDoc->Images["Clear"][0].DilateSegs (dilateOctagon, 1);
        	pDoc->Images["Background Mask"] = ~(pDoc->Images["Clear]);

        	// #### FEATURE 4, 5: Special measure function; Shortcut for Patches(aimAll). in Patches.
		pDoc->Images["Clear"].Patches.Measure  (0 /*chnl*/,
							msr, *pSrv);
        }
}
